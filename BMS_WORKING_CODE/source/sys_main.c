//**********************************************************************************************
// Team Phantom Battery Management System
//
// For the TMS570LS1224PGE
// Based on the software reference code
//
// XingLu Wang
// Joe Xu
//**********************************************************************************************

#include "gio.h"
#include "sci.h"
#include "rti.h"
#include "system.h"
#include "sys_vim.h"
#include "pl455.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sys_common.h"

/* USER CODE BEGIN (2) */

int UART_RX_RDY = 0;
int RTI_TIMEOUT = 0;

// Modified SCI module code
void my_sciInit(void);
void my_rtiInit(void);


/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */

    //**********************************************************************************************
    // Initialization
    //**********************************************************************************************

    _enable_IRQ();

    gioInit();

    my_sciInit();
    my_rtiInit();

    WakePL455();

    CommClear();

    CommReset();

    int nSent, nRead, nTopFound = 0;
    //int nDev_ID, nGrp_ID;
    BYTE  bFrame[132];
    uint32  wTemp = 0;

    // Wake all devices
    for(nDev_ID = 0; nDev_ID < TOTALBOARDS>>1; nDev_ID++) {
        nSent = WriteReg(nDev_ID, 12, 0x40, 1, FRMWRT_ALL_NR);  // send out broadcast pwrdown command
        delayms(5); //~5ms
        WakePL455();
        delayms(5); //~5ms
    }

    // Mask Customer Checksum Fault bit
    nSent = WriteReg(0, 107, 0x8000, 2, FRMWRT_ALL_NR); // clear all fault summary flags

    // Clear all faults
    nSent = WriteReg(0, 82, 0xFFC0, 2, FRMWRT_ALL_NR);      // clear all fault summary flags
    nSent = WriteReg(0, 81, 0x38, 1, FRMWRT_ALL_NR); // clear fault flags in the system status register



    //**********************************************************************************************
    // Section 1
    //**********************************************************************************************

    // Auto-address all boards (section 1.2.2)
    nSent = WriteReg(0, 14, 0x19, 1, FRMWRT_ALL_NR); // set auto-address mode on all boards
    nSent = WriteReg(0, 12, 0x08, 1, FRMWRT_ALL_NR); // enter auto address mode on all boards, the next write to this ID will be its address

    // Set addresses for all boards in daisy-chain (section 1.2.3)
    for (nDev_ID = 0; nDev_ID < TOTALBOARDS; nDev_ID++)
    {
        nSent = WriteReg(nDev_ID, 10, nDev_ID, 1, FRMWRT_ALL_NR); // send address to each board
    }

    // Enable all communication interfaces on all boards in the stack (section 1.2.1)
    nSent = WriteReg(0, 16, 0x10F8, 2, FRMWRT_ALL_NR);  // set communications baud rate and enable all interfaces on all boards in stack

    /* Change to final baud rate used in the application (set by BAUDRATE define in pl455.h).
     * Up to this point, all communication is at 250Kb, as the COMM_RESET done at the initial
     * startup resets the bq76PL455A-Q1 UART to 250Kb. */
    switch(BAUDRATE)
    {
    case 125000:
        nSent = WriteReg(0, 16, 0x00F8, 2, FRMWRT_ALL_NR);  // set communications baud rate and enable all interfaces
        delayms(1);
        sciSetBaudrate(scilinREG, BAUDRATE);
        break;
    case 250000:
        delayms(1);
        break;
    case 500000:
        nSent = WriteReg(0, 16, 0x20F8, 2, FRMWRT_ALL_NR);  // set communications baud rate and enable all interfaces
        delayms(1);
        sciSetBaudrate(scilinREG, BAUDRATE);
        break;
    case 1000000:
        nSent = WriteReg(0, 16, 0x30F8, 2, FRMWRT_ALL_NR);  // set communications baud rate and enable all interfaces
        delayms(1);
        sciSetBaudrate(scilinREG, BAUDRATE);
        break;
    }

    /* Set communications interfaces appropriately for their position in the stack, and
     * for baud rate used in the application (set by BAUDRATE define in pl455.h).
     * (section 1.2.4)
     */
    for (nDev_ID = TOTALBOARDS - 1; nDev_ID >= 0; --nDev_ID)
    {
        // read device ID to see if there is a response
        nRead = ReadReg(nDev_ID, 10, &wTemp, 1, 0); // 0ms timeout

        printf("%d\n", nRead);

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
                            nSent = WriteReg(nDev_ID, 16, 0x0080, 2, FRMWRT_SGL_NR);    // enable only single-end comm port on board
                            break;
                        case 250000:
                            nSent = WriteReg(nDev_ID, 16, 0x1080, 2, FRMWRT_SGL_NR);    // enable only single-end comm port on board
                            break;
                        case 500000:
                            nSent = WriteReg(nDev_ID, 16, 0x2080, 2, FRMWRT_SGL_NR);    // enable only single-end comm port on board
                            break;
                        case 1000000:
                            nSent = WriteReg(nDev_ID, 16, 0x3080, 2, FRMWRT_SGL_NR);    // enable only single-end comm port on board
                            break;
                        }
                }
                else // this is the top board of a stack (section 1.2.5)
                {
                    switch(BAUDRATE)
                    {
                    case 125000:
                        nSent = WriteReg(nDev_ID, 16, 0x0028, 2, FRMWRT_SGL_NR);    // enable only comm-low and fault-low for the top board
                        break;
                    case 250000:
                        nSent = WriteReg(nDev_ID, 16, 0x1028, 2, FRMWRT_SGL_NR);    // enable only comm-low and fault-low for the top board
                        break;
                    case 500000:
                        nSent = WriteReg(nDev_ID, 16, 0x2028, 2, FRMWRT_SGL_NR);    // enable only comm-low and fault-low for the top board
                        break;
                    case 1000000:
                        nSent = WriteReg(nDev_ID, 16, 0x3028, 2, FRMWRT_SGL_NR);    // enable only comm-low and fault-low for the top board
                        break;
                    }
                    nTopFound = 1;
                }
            }
            else // this is a middle or bottom board
            {
                if(nDev_ID == 0) // this is a bottom board of a stack (section 1.2.6)
                {
                    switch(BAUDRATE)
                    {
                    case 125000:
                        nSent = WriteReg(nDev_ID, 16, 0x00D0, 2, FRMWRT_SGL_NR);    // enable comm-high, fault-high and single-end comm port on bottom board
                        break;
                    case 250000:
                        nSent = WriteReg(nDev_ID, 16, 0x10D0, 2, FRMWRT_SGL_NR);    // enable comm-high, fault-high and single-end comm port on bottom board
                        break;
                    case 500000:
                        nSent = WriteReg(nDev_ID, 16, 0x20D0, 2, FRMWRT_SGL_NR);    // enable comm-high, fault-high and single-end comm port on bottom board
                        break;
                    case 1000000:
                        nSent = WriteReg(nDev_ID, 16, 0x30D0, 2, FRMWRT_SGL_NR);    // enable comm-high, fault-high and single-end comm port on bottom board
                        break;
                    }
                }
                else // this is a middle board
                {
                    switch(BAUDRATE)
                    {
                    case 125000:
                        nSent = WriteReg(nDev_ID, 16, 0x0078, 2, FRMWRT_SGL_NR);    // enable comm-high, fault-high, comm-low and fault-low on all middle boards
                        break;
                    case 250000:
                        nSent = WriteReg(nDev_ID, 16, 0x1078, 2, FRMWRT_SGL_NR);    // enable comm-high, fault-high, comm-low and fault-low on all middle boards
                        break;
                    case 500000:
                        nSent = WriteReg(nDev_ID, 16, 0x2078, 2, FRMWRT_SGL_NR);    // enable comm-high, fault-high, comm-low and fault-low on all middle boards
                        break;
                    case 1000000:
                        nSent = WriteReg(nDev_ID, 16, 0x3078, 2, FRMWRT_SGL_NR);    // enable comm-high, fault-high, comm-low and fault-low on all middle boards
                        break;
                    }
                }
            }
        }
    }

    // Clear all faults (section 1.2.7)
    nSent = WriteReg(0, 82, 0xFFC0, 2, FRMWRT_ALL_NR); // clear all fault summary flags
    nSent = WriteReg(0, 81, 0x38, 1, FRMWRT_ALL_NR); // clear fault flags in the system status register

    delayms(10);

    printf("Finished \n");


    while(1);
/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */
