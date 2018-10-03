/**
 *
 *  @file emb1428.c
 *
 *  @author Stephen Holland - Texas Instruments Inc.
 *  @date June 2015
 *  @version 1.0 Initial version
 *  @note Built with CCS for Hercules Version: 5.4.0
 */

#include "string.h"

#include "sci.h"
#include "rti.h"
#include "reg_rti.h"

#include "pl455.h"
#include "emb1428.h"
#include "datatypes.h"
#include "spi.h"
#include "gio.h"
extern int UART_RX_RDY;
extern int RTI_TIMEOUT;

// internal function prototype
uint16 CRC16(BYTE *pBuf, int nLen);
uint32 g_ui32EMB1428Status = 0;
uint32 spiTransferByte(spiBASE_t *spi, unsigned char byte);
uint32 spiTransfer16bit(spiBASE_t *spi, unsigned short data);

void initEMB1428Interface(int nDev_ID)
{
	/* Bit-banged SPI for EMB1428 */
	//nDev_ID = 0;
	int packet,nRead;
	unsigned char temp, temp1, temp2;
#ifndef TMS570SPI
	if(nDev_ID == 0)
		packet = FRMWRT_ALL_NR;
	else
		packet = FRMWRT_SGL_NR;

	/**
	*     CS: 0x00 or 0x01 = bottom EMB1428, 0x02 = middle EMB1428, 0x03 = top EMB1428
	*     bit 0 = nCS_OE - SN75AHC595 output enable
	*     bit 1 = nCS_STORE - SN75AHC595 RCLK (rising edge stores)
	*     bit 2 = SCLK
	*     bit 3 = SDO
	*     bit 4 = SDI
	*     bit 5 = EMB1428_RESET
	*     AUX 6 = EM1428_FAULT_INT
	*/

	WriteReg(nDev_ID, 121, 0x01, 1, FRMWRT_SGL_NR); // set GPIO initial outputs
	WriteReg(nDev_ID, 122, 0x00, 1, FRMWRT_SGL_NR); // set GPIO pull up
	WriteReg(nDev_ID, 123, 0x00, 1, FRMWRT_SGL_NR); // set GPIO pull down
	WriteReg(nDev_ID, 120, 0x0C, 1, FRMWRT_SGL_NR); // set GPIO direction
	delayus(250);
#else
//	nRead = ReadReg(0, 124, &temp, 1, 0); // Read GPIO input register
	WriteReg(nDev_ID, 120, 0x00, 1, FRMWRT_SGL_NR); // set GPIO direction to inputs
	WriteReg(nDev_ID, 122, 0x3F, 1, FRMWRT_SGL_NR); // enable GPIO pull up
	WriteReg(nDev_ID, 123, 0x00, 1, FRMWRT_SGL_NR); // disable GPIO pull down
//	nRead = ReadReg(0, 124, &temp1, 1, 0); // Read GPIO register

	gioSetDirection(gioPORTA, (1<<4)|(1<<6)|(1<<7)); //set GIO 4,6,7 as output
	gioSetPort(gioPORTA, (1<<6)|(1<<7)); //set GIO 6 & 7 high
	delayus(250);
//	spiInit();
//	nRead = ReadReg(0, 124, &temp2, 1, 0); // Read GPIO register
	spiInit();

#endif
#if 0
    while(1)
    {
#if 0
    	EMB_SetCS(0, 0x8);
    	delayus(10);
    	EMB_SetCS(0, 0x0);

    	EMB_SetCS(0, 0x4);
    	delayus(10);
    	EMB_SetCS(0, 0x0);

    	EMB_SetCS(0, 0x2);
    	delayus(10);
    	EMB_SetCS(0, 0x0);

    	EMB_SetCS(0, 0x1);
    	delayus(10);
    	EMB_SetCS(0, 0x0);
#endif
    	EMB_Start(0, 2, 0x8);
    	EMB_Stop(0, 2);
       	EMB_Start(0, 5, 0x8);
        EMB_Stop(0, 5);
     	EMB_Start(0, 10, 0x8);
        EMB_Stop(0, 10);
   }
#endif
}

/*
 * EMB_Start(int nDev_ID, int channel, int direction, int current)
 * channel = 1 - 16
 * direction = charge or discharge
 * current =
 * #define charge			0x00
	#define discharge		0x08
 *
 */
void EMB_Start(int nDev_ID, int channel, int direction)
{
	switch(channel)
	{
	case 1:
		EMB_Start_Command(nDev_ID, nCS_BOTSTACK, direction|0x01);
		break;
	case 2:
		EMB_Start_Command(nDev_ID, nCS_BOTSTACK, direction|0x03);
		break;
	case 3:
		EMB_Start_Command(nDev_ID, nCS_MIDSTACK, direction|0x01);
		break;
	case 4:
		EMB_Start_Command(nDev_ID, nCS_MIDSTACK, direction|0x02);
		break;
	case 5:
		EMB_Start_Command(nDev_ID, nCS_MIDSTACK, direction|0x03);
		break;
	case 6:
		EMB_Start_Command(nDev_ID, nCS_MIDSTACK, direction|0x04);
		break;
	case 7:
		EMB_Start_Command(nDev_ID, nCS_MIDSTACK, direction|0x05);
		break;
	case 8:
		EMB_Start_Command(nDev_ID, nCS_MIDSTACK, direction|0x06);
		break;
	case 9:
		EMB_Start_Command(nDev_ID, nCS_MIDSTACK, direction|0x07);
		break;
	case 10:
		EMB_Start_Command(nDev_ID, nCS_TOPSTACK, direction|0x01);
		break;
	case 11:
		EMB_Start_Command(nDev_ID, nCS_TOPSTACK, direction|0x02);
		break;
	case 12:
		EMB_Start_Command(nDev_ID, nCS_TOPSTACK, direction|0x03);
		break;
	case 13:
		EMB_Start_Command(nDev_ID, nCS_TOPSTACK, direction|0x04);
		break;
	case 14:
		EMB_Start_Command(nDev_ID, nCS_TOPSTACK, direction|0x05);
		break;
	case 15:
		EMB_Start_Command(nDev_ID, nCS_TOPSTACK, direction|0x06);
		break;
	case 16:
		EMB_Start_Command(nDev_ID, nCS_TOPSTACK, direction|0x07);
		break;
	}
}

void EMB_Start_Command(int nDev_ID, int EMB_CS, int EMB_COMMAND)
{
	//EMB_COMMAND = 0x01; //0b1xxx = discharge, 0b0xxx = charge

	/*
	 * EMB_CS: 0x08 = nCS_DAC, 0x04 = nCS_BOTSTACK, 0x02 = nCS_MIDSTACK, 0x01 = nCS_TOPSTACK, 0x00 = off
	 * EMB_COMMAND: 0b1xxx = discharge, 0b0xxx = charge
	 * EMB_Start(nDev_ID, EMB_CS, EMB_COMMAND)
	 *
	 * Valid commands are:
	 * Cell 1 charge: 		EMB_Start(nDev_ID, nCS_BOTSTACK, 0x01);
	 * Cell 1 discharge: 	EMB_Start(nDev_ID, nCS_BOTSTACK, 0x09);
	 * Cell 2 charge: 		EMB_Start(nDev_ID, nCS_BOTSTACK, 0x03); ** NOTE: BOTSTACK does not support a 0x02 gate command
	 * Cell 2 discharge: 	EMB_Start(nDev_ID, nCS_BOTSTACK, 0x0B);
	 * Cell 3 charge: 		EMB_Start(nDev_ID, nCS_MIDSTACK, 0x01);
	 * Cell 3 discharge: 	EMB_Start(nDev_ID, nCS_MIDSTACK, 0x09);
	 * Cell 4 charge: 		EMB_Start(nDev_ID, nCS_MIDSTACK, 0x02);
	 * Cell 4 discharge: 	EMB_Start(nDev_ID, nCS_MIDSTACK, 0x0A);
	 * Cell 5 charge: 		EMB_Start(nDev_ID, nCS_MIDSTACK, 0x03);
	 * Cell 5 discharge: 	EMB_Start(nDev_ID, nCS_MIDSTACK, 0x0B);
	 * Cell 6 charge: 		EMB_Start(nDev_ID, nCS_MIDSTACK, 0x04);
	 * Cell 6 discharge: 	EMB_Start(nDev_ID, nCS_MIDSTACK, 0x0C);
	 * Cell 7 charge: 		EMB_Start(nDev_ID, nCS_MIDSTACK, 0x05);
	 * Cell 7 discharge: 	EMB_Start(nDev_ID, nCS_MIDSTACK, 0x0D);
	 * Cell 8 charge: 		EMB_Start(nDev_ID, nCS_MIDSTACK, 0x06);
	 * Cell 8 discharge: 	EMB_Start(nDev_ID, nCS_MIDSTACK, 0x0E);
	 * Cell 9 charge: 		EMB_Start(nDev_ID, nCS_MIDSTACK, 0x07);
	 * Cell 9 discharge: 	EMB_Start(nDev_ID, nCS_MIDSTACK, 0x0F);
	 * Cell 10 charge: 		EMB_Start(nDev_ID, nCS_TOPSTACK, 0x01);
	 * Cell 10 discharge: 	EMB_Start(nDev_ID, nCS_TOPSTACK, 0x09);
	 * Cell 11 charge: 		EMB_Start(nDev_ID, nCS_TOPSTACK, 0x02);
	 * Cell 11 discharge: 	EMB_Start(nDev_ID, nCS_TOPSTACK, 0x0A);
	 * Cell 12 charge: 		EMB_Start(nDev_ID, nCS_TOPSTACK, 0x03);
	 * Cell 12 discharge: 	EMB_Start(nDev_ID, nCS_TOPSTACK, 0x0B);
	 * Cell 13 charge: 		EMB_Start(nDev_ID, nCS_TOPSTACK, 0x04);
	 * Cell 13 discharge: 	EMB_Start(nDev_ID, nCS_TOPSTACK, 0x0C);
	 * Cell 14 charge: 		EMB_Start(nDev_ID, nCS_TOPSTACK, 0x05);
	 * Cell 14 discharge: 	EMB_Start(nDev_ID, nCS_TOPSTACK, 0x0D);
	 * Cell 15 charge: 		EMB_Start(nDev_ID, nCS_TOPSTACK, 0x06);
	 * Cell 15 discharge: 	EMB_Start(nDev_ID, nCS_TOPSTACK, 0x0E);
	 * Cell 16 charge: 		EMB_Start(nDev_ID, nCS_TOPSTACK, 0x07);
	 * Cell 16 discharge: 	EMB_Start(nDev_ID, nCS_TOPSTACK, 0x0F);
	 */


#ifndef TMS570SPI
	EMB_SetCS(nDev_ID, EMB_CS);
	WriteReg(nDev_ID, 120, 0x2E, 1, FRMWRT_SGL_NR); // set GPIO dir - EMB1428_RST low by changing bit 5 to output
	delayms(10);
	WriteReg(nDev_ID, 121, (EMB_COMMAND>>3&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SDO bit 3 - charge=0/discharge=1)
	WriteReg(nDev_ID, 121, (EMB_COMMAND>>3&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high)
	WriteReg(nDev_ID, 121, (EMB_COMMAND>>2&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK low, SDO bit 2 - channel bit 2)
	WriteReg(nDev_ID, 121, (EMB_COMMAND>>2&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high)
	WriteReg(nDev_ID, 121, (EMB_COMMAND>>1&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK low, SDO bit 1 - channel bit 1)
	WriteReg(nDev_ID, 121, (EMB_COMMAND>>1&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high)
	WriteReg(nDev_ID, 121, (EMB_COMMAND&0x01)<<3, 1, FRMWRT_SGL_NR);    // set GPIO output (SCLK low, SDO bit 0 - channel bit 0)
	WriteReg(nDev_ID, 121, (EMB_COMMAND&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR);      // set GPIO output (SCLK high)
	WriteReg(nDev_ID, 121, 0, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK low, SDO 0)
	WriteReg(nDev_ID, 121, EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high)
	WriteReg(nDev_ID, 121, 0, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK low, SDO 0)
	WriteReg(nDev_ID, 121, EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high)
	WriteReg(nDev_ID, 121, 0, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK low, SDO 0)
	WriteReg(nDev_ID, 121, EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high)
	WriteReg(nDev_ID, 121, 0, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK low, SDO 0)
	WriteReg(nDev_ID, 121, EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high)
	WriteReg(nDev_ID, 121, 0, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK low, SDO 0)
	delayus(200);
#else
	gioSetBit(gioPORTA, 6, 0); //RS_EMB128 low, Release EMB1428 from reset.
	delayms(10);
	EMB_SetCS(nDev_ID, EMB_CS);
	g_ui32EMB1428Status = spiTransferByte(spiREG1, (EMB_COMMAND<<4));
	if((g_ui32EMB1428Status &(0xF0)) != 0xA0)
	{
		while (1);
	}
#endif
	EMB_SetCS(nDev_ID, 0);
}

void EMB_Stop(int nDev_ID, int channel)
{
	int nRead;
	BYTE bTemp;

	switch(channel)
	{
	case 1:
		EMB_SetCS(nDev_ID, nCS_BOTSTACK);
		break;
	case 2:
		EMB_SetCS(nDev_ID, nCS_BOTSTACK);
		break;
	case 3:
		EMB_SetCS(nDev_ID, nCS_MIDSTACK);
		break;
	case 4:
		EMB_SetCS(nDev_ID, nCS_MIDSTACK);
		break;
	case 5:
		EMB_SetCS(nDev_ID, nCS_MIDSTACK);
		break;
	case 6:
		EMB_SetCS(nDev_ID, nCS_MIDSTACK);
		break;
	case 7:
		EMB_SetCS(nDev_ID, nCS_MIDSTACK);
		break;
	case 8:
		EMB_SetCS(nDev_ID, nCS_MIDSTACK);
		break;
	case 9:
		EMB_SetCS(nDev_ID, nCS_MIDSTACK);
		break;
	case 10:
		EMB_SetCS(nDev_ID, nCS_TOPSTACK);
		break;
	case 11:
		EMB_SetCS(nDev_ID, nCS_TOPSTACK);
		break;
	case 12:
		EMB_SetCS(nDev_ID, nCS_TOPSTACK);
		break;
	case 13:
		EMB_SetCS(nDev_ID, nCS_TOPSTACK);
		break;
	case 14:
		EMB_SetCS(nDev_ID, nCS_TOPSTACK);
		break;
	case 15:
		EMB_SetCS(nDev_ID, nCS_TOPSTACK);
		break;
	case 16:
		EMB_SetCS(nDev_ID, nCS_TOPSTACK);
		break;
	}

	int EMB_COMMAND = 0x00;

#ifndef TMS570SPI
	WriteReg(nDev_ID, 121, (EMB_COMMAND>>3&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SDO bit 3 - charge=0/discharge=1)
	WriteReg(nDev_ID, 121, (EMB_COMMAND>>3&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high)
	WriteReg(nDev_ID, 121, (EMB_COMMAND>>2&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK low, SDO bit 2 - channel bit 2)
	WriteReg(nDev_ID, 121, (EMB_COMMAND>>2&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high)
	WriteReg(nDev_ID, 121, (EMB_COMMAND>>1&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK low, SDO bit 1 - channel bit 1)
	WriteReg(nDev_ID, 121, (EMB_COMMAND>>1&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high)
	WriteReg(nDev_ID, 121, (EMB_COMMAND&0x01)<<3, 1, FRMWRT_SGL_NR);    // set GPIO output (SCLK low, SDO bit 0 - channel bit 0)
	WriteReg(nDev_ID, 121, (EMB_COMMAND&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR);      // set GPIO output (SCLK high)
	WriteReg(nDev_ID, 121, 0, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK low, SDO 0)
	WriteReg(nDev_ID, 121, EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high)
	WriteReg(nDev_ID, 121, 0, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK low, SDO 0)
	WriteReg(nDev_ID, 121, EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high)
	WriteReg(nDev_ID, 121, 0, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK low, SDO 0)
	WriteReg(nDev_ID, 121, EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high)
	WriteReg(nDev_ID, 121, 0, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK low, SDO 0)
	WriteReg(nDev_ID, 121, EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high)
	WriteReg(nDev_ID, 121, 0, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK low, SDO 0)
	delayus(200);
	EMB_SetCS(nDev_ID, 0);
	delayms(2); // required to let current ramp down
	// set GPIO dir - EMB1428_RST high by changing bit 5 to input (ensure bit 1 is still set to input, since CS is disabled above)
	nRead = ReadReg(nDev_ID, 120, &bTemp, 2, 0); // Read GPIO dir register
	WriteReg(nDev_ID, 120, (bTemp & 0x0C), 1, FRMWRT_SGL_NR);
#else
	g_ui32EMB1428Status = spiTransferByte(spiREG1, 0);
//	delayus(200);
	EMB_SetCS(nDev_ID, 0);
	delayms(2); // required to let current ramp down
	gioSetBit(gioPORTA, 6, 1); //RS_EMB128 high, Put 1428 in reset.
	if((g_ui32EMB1428Status &(0xF0)) != 0xA0)
	{
		while (1);
	}
#endif
	delayus(200);
}

void EMB_SetCS(int nDev_ID, int CS)
{
	int nRead;
	BYTE bTemp;
#ifndef TMS570SPI
	if(CS)
	{
		CS ^= 0xFF;
		WriteReg(nDev_ID, 121, (CS>>7&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SDO bit 7)
		WriteReg(nDev_ID, 121, (CS>>7&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK high)
		WriteReg(nDev_ID, 121, (CS>>6&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK low, SDO bit 6)
		WriteReg(nDev_ID, 121, (CS>>6&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK high)
		WriteReg(nDev_ID, 121, (CS>>5&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK low, SDO bit 5)
		WriteReg(nDev_ID, 121, (CS>>5&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK high)
		WriteReg(nDev_ID, 121, (CS>>4&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK low, SDO bit 4)
		WriteReg(nDev_ID, 121, (CS>>4&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK high)
		WriteReg(nDev_ID, 121, (CS>>3&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SDO bit 3)
		WriteReg(nDev_ID, 121, (CS>>3&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK high)
		WriteReg(nDev_ID, 121, (CS>>2&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK low, SDO bit 2)
		WriteReg(nDev_ID, 121, (CS>>2&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK high)
		WriteReg(nDev_ID, 121, (CS>>1&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK low, SDO bit 1)
		WriteReg(nDev_ID, 121, (CS>>1&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK high)
		WriteReg(nDev_ID, 121, (CS&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK low, SDO bit 0)
		WriteReg(nDev_ID, 121, (CS&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK high)
		WriteReg(nDev_ID, 121, 0x01, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK low, SDO 0), preset nCS_STORE bit high

		nRead = ReadReg(nDev_ID, 120, &bTemp, 2, 0); // Read GPIO dir register
		WriteReg(nDev_ID, 120, (bTemp | 0x01), 1, FRMWRT_SGL_NR); // set GPIO dir - nCS_STORE high by changing bit 0 to output
		WriteReg(nDev_ID, 120, (bTemp | 0x02), 1, FRMWRT_SGL_NR); // set GPIO dir - nCS_OE low by changing bit 1 to output, nCS_STORE low by changing bit 0 to input
		//WriteReg(nDev_ID, 120, (bTemp & 0x0E), 1, FRMWRT_SGL_NR); // set GPIO dir - , keep nCS_OE low
	}
	else
	{
		nRead = ReadReg(nDev_ID, 120, &bTemp, 2, 0); // Read GPIO dir register
		WriteReg(nDev_ID, 120, (bTemp & 0x2C), 1, FRMWRT_SGL_NR); // set GPIO dir - nCS_OE high by changing bit 1 to input
	}
	delayus(200);
#else
	if(CS)
		{
			CS ^= 0xFF;
			g_ui32EMB1428Status = spiTransferByte(spiREG1, (unsigned char)CS);
			gioSetBit(gioPORTA, 4, 1); //CS_Store high
			gioSetBit(gioPORTA, 7, 0); //CS_OE low
		}
		else
		{
			gioSetBit(gioPORTA, 7, 1); //CS_OE high
			gioSetBit(gioPORTA, 4, 0); //CS_Store low
		}
	delayus(10);
#endif

}

/*
 * Setpoint = Amps
 */
void EMB_Vset(int nDev_ID, float Amps)
{
	//EMB_CS: 0x08 = nCS_DAC, 0x04 = nCS_BOTSTACK, 0x02 = nCS_MIDSTACK, 0x01 = nCS_TOPSTACK, 0x00 = off
	// @VIO = 3.3V, nCS_DAC = 0x61 = 1.20V, 0xA4 = 2.01V, 0xB1 = 2.19V
	// @VIO = 5.3V, nCS_DAC = 0x3A = 1.20V, 0x61 = 2.01V, 0x6A = 2.19V
#ifdef VIO_3V3
	int Setpoint = (int)(Amps/2.5/(3.2/256)) + 5;
#endif
#ifdef VIO_5V3
	int Setpoint = (int)(Amps/2.5/(5.2/256)) + 1;
#endif

	EMB_SetCS(nDev_ID, 0x08);
#ifndef TMS570SPI
	WriteReg(nDev_ID, 121, EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high)
	WriteReg(nDev_ID, 121, 0, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK low, SDO bit 15)
	WriteReg(nDev_ID, 121, EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high)
	WriteReg(nDev_ID, 121, 0, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK low, SDO bit 14)
	WriteReg(nDev_ID, 121, EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high)
	WriteReg(nDev_ID, 121, 0, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK low, SDO bit 13)
	WriteReg(nDev_ID, 121, EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high)
	WriteReg(nDev_ID, 121, 0, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK low, SDO bit 12)
	WriteReg(nDev_ID, 121, (Setpoint>>7&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK high, DAC bit 7)
	WriteReg(nDev_ID, 121, (Setpoint>>7&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK low)
	WriteReg(nDev_ID, 121, (Setpoint>>6&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK high, DAC bit 6)
	WriteReg(nDev_ID, 121, (Setpoint>>6&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK low)
	WriteReg(nDev_ID, 121, (Setpoint>>5&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK high, DAC bit 5)
	WriteReg(nDev_ID, 121, (Setpoint>>5&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK low)
	WriteReg(nDev_ID, 121, (Setpoint>>4&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK high, DAC bit 4)
	WriteReg(nDev_ID, 121, (Setpoint>>4&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK low)
	WriteReg(nDev_ID, 121, (Setpoint>>3&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK high, DAC bit 3)
	WriteReg(nDev_ID, 121, (Setpoint>>3&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK low)
	WriteReg(nDev_ID, 121, (Setpoint>>2&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK high, DAC bit 2)
	WriteReg(nDev_ID, 121, (Setpoint>>2&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK low)
	WriteReg(nDev_ID, 121, (Setpoint>>1&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK high, DAC bit 1)
	WriteReg(nDev_ID, 121, (Setpoint>>1&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK low)
	WriteReg(nDev_ID, 121, (Setpoint&0x01)<<3 | EMB_SCLK, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK high, DAC bit 0)
	WriteReg(nDev_ID, 121, (Setpoint&0x01)<<3, 1, FRMWRT_SGL_NR); // set GPIO output (SCLK low)
	WriteReg(nDev_ID, 121, EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high, SDO bit 3)
	WriteReg(nDev_ID, 121, 0, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK low)
	WriteReg(nDev_ID, 121, EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high, SDO bit 2)
	WriteReg(nDev_ID, 121, 0, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK low)
	WriteReg(nDev_ID, 121, EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high, SDO bit 1)
	WriteReg(nDev_ID, 121, 0, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK low)
	WriteReg(nDev_ID, 121, EMB_SCLK, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK high, SDO bit 0)
	WriteReg(nDev_ID, 121, 0, 1, FRMWRT_SGL_NR);   // set GPIO output (SCLK low)
	delayus(200);
#else
	g_ui32EMB1428Status = spiTransfer16bit(spiREG1, (unsigned short)((Setpoint<<4)&0xffff));
#endif
	EMB_SetCS(nDev_ID, 0);
}

uint32 spiTransferByte(spiBASE_t *spi, unsigned char byte)
{
    volatile uint32 SpiBuf;

    spi->DAT1 = byte;

    while((spi->FLG & 0x00000100U) != 0x00000100U)
    {
    } /* Wait */
    SpiBuf = spi->BUF;

    return (SpiBuf);
}

uint32 spiTransfer16bit(spiBASE_t *spi, unsigned short data)
{
    volatile uint32 SpiBuf;

    spi->DAT1 = data |(1<<24) ;

    while((spi->FLG & 0x00000100U) != 0x00000100U)
    {
    } /* Wait */
    SpiBuf = spi->BUF;

    return (SpiBuf);
}

//EOF

