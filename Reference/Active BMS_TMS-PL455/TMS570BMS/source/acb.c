#define BalanceToAverage // BalanceToAverage, Charge or Discharge
#define ACB_CHARGE_TIME 10 //1sec for 100ms RTI COMP1 tick
#define ACB_PERIOD 40  //3sec for 100ms RTI COMP1 tick
unsigned int g_ui32ACBChargeTime = ACB_CHARGE_TIME;
unsigned int g_ui32ACBPeriod = ACB_PERIOD;
unsigned int g_ui32ACBTimeTick =0;
unsigned int g_ui32ACBStatus = 0;
unsigned int g_ui32ACBEnabled = 0;
unsigned char g_ui8PL455Data[64];
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include "gio.h"
#include "sci.h"
#include "spi.h"
#include "rti.h"
#include "sys_vim.h"
#include "swi_util.h"
#include "pl455.h"
#include "emb1428.h"
#include "HET.h"
#include "HET_EMU.h"

void SetCS3forWake();
void SetWakeHigh();
void SetWakeLow();
void PL455Sampling();
unsigned int ActiveBalancing(unsigned int cmd);
void ActiveBalancingInit();


extern unsigned char g_ui8PL455Registers[];
extern void HetUART1TxStart(unsigned char *buf, unsigned int msg_size);

unsigned int host_status;
unsigned int balancing_time_stamp;

/* USER CODE END */

// Gloabal balancing variables

float cellSample;
//int incCount, decCount;
float maxCell = 0, minCell = 5, maxCellDelta, cellAverage;
int maxCellNum, minCellNum, cellToBalance, cellBalanceDir;

/*******************************************************************************/
/* function to initialize PL455, EB1428, and balancing parameters              */
/*******************************************************************************/
void ActiveBalancingInit()
{

	// initialize local variables
	int nSent, nRead, nTopFound = 0, nTopID = 0, tempCount;
	int nDev_ID = 0, nGrp_ID = 0;
	BYTE  bFrame[132];
	uint32  wTemp = 0;
	BYTE bTemp;
	register unsigned int i;

//	nSent = WriteReg(0, 12, 0x40, 1, FRMWRT_ALL_NR);	// send out broadcast pwrdown command
//	delayms(5); //~5ms
//	WakePL455();

//	CommClear();

//	CommReset();

//	gioSetBit(gioPORTA, 7, 1); // enable TOP
#if 0
	SetCS3forWake();
	SetWakeLow();
	delayms(100);
	SetWakeHigh();
	delayms(100);
#endif

	// Wake all devices
	// The wake tone will awaken any device that is already in shutdown and the pwrdown will shutdown any device
	// that is already awake. The least number of times to sequence wake and pwrdown will be half the number of
	// boards to cover the worst case combination of boards already awake or shutdown.
	for(nDev_ID = 0; nDev_ID < TOTALBOARDS; nDev_ID++) {
		nSent = WriteReg(nDev_ID, 12, 0x40, 1, FRMWRT_ALL_NR);	// send out broadcast pwrdown command
		delayms(5); //~5ms
		WakePL455();
		delayms(5); //~5ms
	}

	nRead = ReadReg(0, 96, &bTemp, 1, 0); // Read System Fault register

	// Mask Customer Checksum Fault bit
	nSent = WriteReg(0, 107, 0x8000, 2, FRMWRT_ALL_NR); // set mask for customer checksum fault

	// Clear all faults
//	nSent = WriteReg(0, 82, 0xFFC0, 2, FRMWRT_ALL_NR); // clear all fault summary flags
//	nSent = WriteReg(0, 81, 0x38, 1, FRMWRT_ALL_NR); // clear fault flags in the system status register

	// Auto-address all boards
	nSent = WriteReg(0, 14, 0x18, 1, FRMWRT_ALL_NR); // set auto-address mode on all boards
	nSent = WriteReg(0, 12, 0x08, 1, FRMWRT_ALL_NR); // enter auto address mode on all boards, the next write to this ID will be its address

	for (nDev_ID = 0; nDev_ID < TOTALBOARDS; nDev_ID++)
	{
		nSent = WriteReg(nDev_ID, 10, nDev_ID, 1, FRMWRT_ALL_NR); // send address to each board
	}

	/* Enable all communication interfaces on all boards in the stack */
	nSent = WriteReg(0, 16, 0x10F8, 2, FRMWRT_ALL_NR);	// set communications baud rate and enable all interfaces on all boards in stack

	/* Change to final baud rate used in the application (set by BAUDRATE define in pl455.h).
	 * Up to this point, all communication is at 250Kb, as the COMM_RESET done at the initial
	 * startup resets the bq76PL455 UART to 250Kb. */
	switch(BAUDRATE)
	{
	case 125000:
		nSent = WriteReg(0, 16, 0x00F8, 2, FRMWRT_ALL_NR);	// set communications baud rate and enable all interfaces
		delayus(100);
		sciSetBaudrate(scilinREG, BAUDRATE);
		break;
	case 250000:
		delayus(100);
		break;
	case 500000:
		nSent = WriteReg(0, 16, 0x20F8, 2, FRMWRT_ALL_NR);	// set communications baud rate and enable all interfaces
		delayus(100);
		sciSetBaudrate(scilinREG, BAUDRATE);
		break;
	case 1000000:
		nSent = WriteReg(0, 16, 0x30F8, 2, FRMWRT_ALL_NR);	// set communications baud rate and enable all interfaces
		delayus(100);
		sciSetBaudrate(scilinREG, BAUDRATE);
		break;
	}

	/* Set communications interfaces appropriately for their position in the stack, and
	 * for baud rate used in the application (set by BAUDRATE define in pl455.h).
	 */
	for (nDev_ID = TOTALBOARDS - 1; nDev_ID >= 0; --nDev_ID)
	{
		// read device ID to see if there is a response
		nRead = ReadReg(nDev_ID, 10, &wTemp, 1, 0); // 0ms timeout

		if(nRead == 0) // if nothing is read then this board doesn't exist
			nTopFound = 0;
		else // a response was received
		{
			if(nTopFound == 0)
			{ // if the last board was not present but this one is, this is the top board
				if(nDev_ID == 0) // this is the only board
				{
					switch(BAUDRATE)
						{
						case 125000:
							nSent = WriteReg(nDev_ID, 16, 0x0080, 2, FRMWRT_SGL_NR);	// enable only single-end comm port on board
							break;
						case 250000:
							nSent = WriteReg(nDev_ID, 16, 0x1080, 2, FRMWRT_SGL_NR);	// enable only single-end comm port on board
							break;
						case 500000:
							nSent = WriteReg(nDev_ID, 16, 0x2080, 2, FRMWRT_SGL_NR);	// enable only single-end comm port on board
							break;
						case 1000000:
							nSent = WriteReg(nDev_ID, 16, 0x3080, 2, FRMWRT_SGL_NR);	// enable only single-end comm port on board
							break;
						}
				}
				else // this is the top board of a stack
				{
					switch(BAUDRATE)
					{
					case 125000:
						nSent = WriteReg(nDev_ID, 16, 0x0028, 2, FRMWRT_SGL_NR);	// enable only comm-low and fault-low for the top board
						break;
					case 250000:
						nSent = WriteReg(nDev_ID, 16, 0x1028, 2, FRMWRT_SGL_NR);	// enable only comm-low and fault-low for the top board
						break;
					case 500000:
						nSent = WriteReg(nDev_ID, 16, 0x2028, 2, FRMWRT_SGL_NR);	// enable only comm-low and fault-low for the top board
						break;
					case 1000000:
						nSent = WriteReg(nDev_ID, 16, 0x3028, 2, FRMWRT_SGL_NR);	// enable only comm-low and fault-low for the top board
						break;
					}
					nTopFound = 1;
					nTopID = nDev_ID;
				}
			}
			else // this is a middle or bottom board
			{
				if(nDev_ID == 0) // this is a bottom board of a stack
				{
					switch(BAUDRATE)
					{
					case 125000:
						nSent = WriteReg(nDev_ID, 16, 0x00D0, 2, FRMWRT_SGL_NR);	// enable comm-high, fault-high and single-end comm port on bottom board
						break;
					case 250000:
						nSent = WriteReg(nDev_ID, 16, 0x10D0, 2, FRMWRT_SGL_NR);	// enable comm-high, fault-high and single-end comm port on bottom board
						break;
					case 500000:
						nSent = WriteReg(nDev_ID, 16, 0x20D0, 2, FRMWRT_SGL_NR);	// enable comm-high, fault-high and single-end comm port on bottom board
						break;
					case 1000000:
						nSent = WriteReg(nDev_ID, 16, 0x30D0, 2, FRMWRT_SGL_NR);	// enable comm-high, fault-high and single-end comm port on bottom board
						break;
					}
				}
				else // this is a middle board
				{
					switch(BAUDRATE)
					{
					case 125000:
						nSent = WriteReg(nDev_ID, 16, 0x0078, 2, FRMWRT_SGL_NR);	// enable comm-high, fault-high, comm-low and fault-low on all middle boards
						break;
					case 250000:
						nSent = WriteReg(nDev_ID, 16, 0x1078, 2, FRMWRT_SGL_NR);	// enable comm-high, fault-high, comm-low and fault-low on all middle boards
						break;
					case 500000:
						nSent = WriteReg(nDev_ID, 16, 0x2078, 2, FRMWRT_SGL_NR);	// enable comm-high, fault-high, comm-low and fault-low on all middle boards
						break;
					case 1000000:
						nSent = WriteReg(nDev_ID, 16, 0x3078, 2, FRMWRT_SGL_NR);	// enable comm-high, fault-high, comm-low and fault-low on all middle boards
						break;
					}
				}
			}
		}
	}

	delayus(100);

	nSent = WriteReg(0, 40, 0x00, 1, FRMWRT_ALL_NR);	// clear communications timeout register

	// Clear all faults
	nSent = WriteReg(0, 82, 0xFFC0, 2, FRMWRT_ALL_NR); // clear all fault summary flags
	nSent = WriteReg(0, 81, 0x38, 1, FRMWRT_ALL_NR); // clear fault flags in the system status register

	delayms(5);

	nRead = ReadReg(0, 82, &bTemp, 2, 0); // Read Fault Summary register
	nRead = ReadReg(0, 96, &bTemp, 1, 0); // Read System Fault register
	nRead = ReadReg(0, 97, &bTemp, 2, 0); // Read Chip Fault register

	/* Configure sample period and oversampling
	 * Best results are:
	 * cells/AUX
	 * 	- 60us ADC sample period (ADC_PERIOD_VOL = 0xB)
	 * 	- staying on a channel to oversample (CMD_OVS_CYCLE = 0)
	 * 	- 12.6us ADC sample period when oversampling (CMD_OVS_HPER/CMD_OVS_GPER = 3)
	 * 	- 8 oversamples (CMD_OVSMP = 3)
	 * 	- total sample time for all cell and AUX6 channels to be 16 cell channels only:
	 * 		100us + (60us + (12.6us x 7)) x 16  = 2.47ms
	 * Internal temperatures
	 * 	- 100us initial sample delay (ADC_PERIOD_VOL = 0xC)
	 */
	// Configure AFE
	nSent = WriteReg(0, 61, 0x00, 1, FRMWRT_ALL_NR); // set 0 initial delay
	// Configure cell voltage and internal temp sample period
	nSent = WriteReg(0, 62, 0xBC, 1, FRMWRT_ALL_NR); // set 60us cell and 100us temp ADC sample period
	// Configure AUX voltage sample period AUX0-5 are external thermistor, AUX6 is current sense
	nSent = WriteReg(0, 63, 0x44444444, 4, FRMWRT_ALL_NR); // set 12.6us AUX sample period
	// Configure the oversampling rate
	nSent = WriteReg(0, 7, 0x7B, 1, FRMWRT_ALL_NR); // set 8x oversampling, stay on channel for oversample and 12.6us oversample period for cell and AUX
	// Set AFE_PCTL
	nSent = WriteReg(0, 15, 0x80, 1, FRMWRT_ALL_NR); // set AFE_PCTL bit to on (only enable AFE when sampling)

	// Clear all faults
	nSent = WriteReg(0, 81, 0x38, 1, FRMWRT_ALL_NR); // clear fault flags in the system status register
	nSent = WriteReg(0, 82, 0xFFC0, 2, FRMWRT_ALL_NR); // clear all fault summary flags

	// Select identical number of cells and channels on all modules simultaneously
	nSent = WriteReg(0, 13, 0x10, 1, FRMWRT_ALL_NR); // set number of cells to 16
	nSent = WriteReg(0, 3, 0xFFFF0000, 4, FRMWRT_ALL_NR); // select 16 cell, AUX channel 6
//	nSent = WriteReg(0, 3, 0xFFFFFF00, 4, FRMWRT_ALL_NR); // select 16 cell, all AUX

	// Set cell over-voltage and cell under-voltage thresholds on a single board
	nSent = WriteReg(0, 144, 0xD1EC, 2, FRMWRT_ALL_NR); // set OV threshold = 4.1000V
	nSent = WriteReg(0, 142, 0x6148, 2, FRMWRT_ALL_NR); // set UV threshold = 1.9000V

	// Set cell over-voltage and cell under-voltage thresholds on all boards simultaneously
	nSent = WriteReg(0, 144, 0xD1EC, 2, FRMWRT_ALL_NR); // set OV threshold = 4.1000V
	nSent = WriteReg(0, 142, 0x6148, 2, FRMWRT_ALL_NR); // set UV threshold = 1.9000V

	delayms(1);

	/* Main loop */
	for(nDev_ID = 0; nDev_ID < TOTALBOARDS; nDev_ID++) {
		nRead = ReadReg(nDev_ID, 0, &bTemp, 2, 0); // Read SREV register
		nRead = ReadReg(nDev_ID, 40, &bTemp, 1, 0); // Read communication timeout register
		nRead = ReadReg(nDev_ID, 250, &bTemp, 1, 0); // Read burn count register
	}
	delayus(100);
#if 0
	// Send broadcast request to board 1 to sample and store results
//	nSent = WriteReg(0, 2, 0, 1, FRMWRT_ALL_NR); // send sync sample and store command
	nSent = WriteReg(0, 2, 0, 1, FRMWRT_SGL_NR); // send sync sample and store command

	delayus(2800); // still need to wait for sampling to complete

	// Read stored sample data from boards
//	nSent = WriteReg(0, 2, (0x20 | (nTopID & 0x0F)), 1, FRMWRT_ALL_R); // send read stored values command
	nSent = WriteReg(0, 2, 0x20, 1, FRMWRT_SGL_R); // send read stored values command
//	nSent = WaitRespFrame(bFrame, (35 * (nTopID + 1)), 0); // 32 bytes data + packet header + CRC, 0ms timeout
	nSent = WaitRespFrame(bFrame, 35, 0); // 32 bytes data + packet header + CRC, 0ms timeout
#endif
	PL455Sampling();
	nSent = WriteReg(0, 13, 0x10, 1, FRMWRT_ALL_NR); // set number of cells to 16
	nSent = WriteReg(0, 3, 0xFFFF0000, 4, FRMWRT_ALL_NR); // select 16 cell, AUX channel 6
	delayms(5);

	/*
	 * Find the max and min cell channels and their voltages. It's pretty self-explanatory ;-)
	 */

	// Initialize variables
	maxCell = 0;
	minCell = 5;
	maxCellNum = 0;
	minCellNum = 0;
	maxCellDelta = 0;
	cellAverage = 0;
	cellToBalance = 0;

	initEMB1428Interface(0);

	EMB_Vset(0, 2); // Set the DAC output to control charge/discharege current
}

/*******************************************************************************/
/* function to start and stop active balancing                                 */
/* ACB enabled:  cmd = 1, ACB disabled: cmd =0                                 */
/*ACB time tick is set by RTI compare 1 interrupt at 100 ms                    */
/*******************************************************************************/
unsigned char acb_trace[1000];
unsigned int acb_trace_number = 0;
unsigned int ActiveBalancing(unsigned int cmd)
{

	// initialize local variables
	int nSent, nRead, nTopFound = 0, nTopID = 0, tempCount, channels, number_of_channels,start;
	int nDev_ID = 0, nGrp_ID = 0;
	int incCount, decCount;
	BYTE  bFrame[132];
//	BYTE  *bFrame = g_ui8PL455Data;
	uint32  wTemp = 0;
	BYTE bTemp;

	if (cmd)
	{
//		if(g_ui32ACBTimeTick == (g_ui32ACBPeriod-1)) // sample cells at end of the ACB period
		if((g_ui32ACBTimeTick%5) == 0) // sample cells every 500 ms
		{
			PL455Sampling();
		}

		if(g_ui32ACBTimeTick == 0) //start ACB at the beginning of the ACB period
		{
			for (incCount = 0; incCount<33;incCount++)
			{
				bFrame[incCount]=g_ui8PL455Data[incCount];
			}

			if (!g_ui32ACBStatus)
			{
				g_ui32ACBStatus =1;
				channels = (g_ui8PL455Registers[0x14]<<8)|g_ui8PL455Registers[0x15];
				number_of_channels =0;
				maxCell = 0;
				minCell = 0;
				cellAverage = 0;
				start = 0;

				for(decCount = 16, incCount = 1; incCount < 17; incCount ++, decCount--)
				{

					if (channels & (1<<(decCount -1)))
					{
						cellSample = (bFrame[incCount*2-1]<<8|bFrame[incCount*2]) * 0.000076295;
						number_of_channels++;
						if(!start)
						{
							maxCell = cellSample;
							minCell = cellSample;
							cellAverage = cellSample;
							maxCellNum = decCount;
							minCellNum = decCount;
							start = 1;
						}
						else
						{
							cellAverage += cellSample;
							if(cellSample > maxCell)
							{
								maxCell = cellSample;
								maxCellNum = decCount;
							}
							else
							{
								if(cellSample < minCell)
								{
									minCell = cellSample;
									minCellNum = decCount;
								}
							}
						}
					}
				}
				cellAverage /= number_of_channels;

				maxCellDelta = maxCell - cellAverage;
				if((cellAverage - minCell) > maxCellDelta)
				{
					maxCellDelta = cellAverage - minCell;
				}

		/*
		 * Choose cell to balance
		 */

		// Balance to average
				if(maxCellDelta > 0.005)
				{
					if((cellAverage - minCell) > (maxCell - cellAverage))
					{
						maxCellDelta = cellAverage - minCell;
						cellToBalance = minCellNum;
						cellBalanceDir = charge;
					}
					else
					{
						maxCellDelta = maxCell - cellAverage;
						cellToBalance = maxCellNum;
						cellBalanceDir = discharge;
					}
				}
				else
				{
				cellToBalance = 0;
				}

			    if(minCell < 2.5)
			    {
			    	while(1);
			    }// Min threshold for discharge

			    if(maxCell > 4.2)
			    {
			    	while(1); // Max th
			    }
#if 0
		//Chooes cell 1 for charge/discharge current measurement
			    cellToBalance = 1;
			    cellBalanceDir = discharge;
#endif
	 //Balance target cell for 1 second, then relax for 3 seconds
			    if(cellToBalance) // Only balance if celToBalance is not set to 0
				{
					EMB_Start(0, cellToBalance, cellBalanceDir);
				}

			}

			if(acb_trace_number < 1000 )
			{
				acb_trace[acb_trace_number] = (unsigned char)((cellBalanceDir<<4)|cellToBalance);
				acb_trace_number++;
			}
		}
	}

	//Balance target cell for 1 second, then relax for 3 seconds
	if(g_ui32ACBTimeTick == g_ui32ACBChargeTime)
	{
		if (g_ui32ACBStatus) // stop balancing
		{
			g_ui32ACBStatus =0;
			EMB_Stop(0, cellToBalance);
		}
	}
	return(0);
}

/* USER CODE END */


/* USER CODE BEGIN (4) */
void SetCS3forWake()
{
	spiREG1->GCR0 = 1; //Bring SPI 3 out of reset
	spiREG1->PC1 = 1<<SPI_PIN_CS3; //CS3 as output
}

void SetWakeHigh()
{
	spiREG1->PC4 = 1<<SPI_PIN_CS3; //set CS3 high
}

void SetWakeLow()
{
	spiREG1->PC5 = 1<<SPI_PIN_CS3; //set CS3 low
}

void PL455Sampling()
{
	register int nSent, nRead;
	nSent = WriteReg(0, 3, 0xFFFFFFE0, 4, FRMWRT_SGL_NR); // select 16 cell, all AUX, and temperature
	nSent = WriteReg(0, 2, 0, 1, FRMWRT_SGL_NR); // send sync sample and store command
	nRead = ReadReg(0, 82, &g_ui8PL455Registers[82], 2, 0); // Read Fault Summary register
	nRead = ReadReg(0, 96, &g_ui8PL455Registers[96], 1, 0); // Read System Fault register
	nRead = ReadReg(0, 97, &g_ui8PL455Registers[97], 2, 0); // Read Chip Fault register
    delayus(5600);
	// Read stored sample data from boards
	nSent = WriteReg(0, 2, 0x20, 1, FRMWRT_SGL_R); // send read stored values command
	nSent = WaitRespFrame(g_ui8PL455Data, 57, 0); // 54 bytes data + packet header + CRC, 0ms timeout
}

/* USER CODE END */
