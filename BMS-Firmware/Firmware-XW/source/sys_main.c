/** @file sys_main.c 
*   @brief Application main file
*   @date 07-July-2017
*   @version 04.07.00
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2016 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */

/*
 *
 *  3V3         -> bq76PL455A-Q1 EVM J3 pin 3 (VIO)
 *  SCI1_RX     -> bq76PL455A-Q1 EVM J3 pin 5 (TX) **remove R8 from TMS570LS04x Launchpad
 *  SCI1_TX     -> bq76PL455A-Q1 EVM J3 pin 4 (RX)
 *  GND         -> bq76PL455A-Q1 EVM J3 pin 1 (DGND)
 *  GIOA0       -> bq76PL455A-Q1 EVM J3 pin 6 (nWAKE)
 *  GIOA1       -> bq76PL455A-Q1 EVM J3 pin 2 (nFAULT)
 *
 */


















#include "gio.h"
#include "sci.h"
//#include "a_tp_sci.h"
#include "rti.h"
#include "system.h"
#include "sys_vim.h"
#include "pl455.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */

int UART_RX_RDY = 0;
int RTI_TIMEOUT = 0;


void my_sciInit(void);
void my_rtiInit(void);


/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */

    _enable_IRQ();
    gioInit();
    my_sciInit();
    while ((sciREG->FLR & 0x4) == 4);
    my_rtiInit();

    sciEnableNotification(sciREG, SCI_RX_INT);





    printf("log: WakeBit:%d FaultBit:%d\n", gioGetBit(gioPORTA, 0), gioGetBit(gioPORTA, 1));
    WakePL455();
    printf("log: WakeBit:%d FaultBit:%d\n", gioGetBit(gioPORTA, 0), gioGetBit(gioPORTA, 1));



    CommClear();
    CommReset();



    // initialize local variables
    int nSent, nRead, nTopFound = 0;
    int nDev_ID, nGrp_ID;
    BYTE  bFrame[43];
    uint32  wTemp = 0;



    for(nDev_ID = 0; nDev_ID < TOTALBOARDS>>1; nDev_ID++) {
            nSent = WriteReg(nDev_ID, 12, 0x40, 1, FRMWRT_ALL_NR);  // send out broadcast pwrdown command
            delayms(5); //~5ms
            WakePL455();
            delayms(5); //~5ms
        }


    delayms(100);





        // Mask Customer Checksum Fault bit
        nSent = WriteReg(0, 107, 0x8000, 2, FRMWRT_ALL_NR); // clear all fault summary flags

        // Clear all faults
        nSent = WriteReg(0, 82, 0xFFC0, 2, FRMWRT_ALL_NR);      // clear all fault summary flags
        nSent = WriteReg(0, 81, 0x38, 1, FRMWRT_ALL_NR); // clear fault flags in the system status register


















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






    delayms(1);

/*
    while(1){

        nRead = ReadReg(0, 14, &wTemp, 1, 0); // 0ms timeout
        printf("reg 14 : %x\n", wTemp);
        delayms(100);
    }*/








    /* Set communications interfaces appropriately for their position in the stack, and
     * for baud rate used in the application (set by BAUDRATE define in pl455.h).
     * (section 1.2.4)
     */
    for (nDev_ID = TOTALBOARDS - 1; nDev_ID >= 0; --nDev_ID)
    {
        // read device ID to see if there is a response


            //nRead = ReadReg(nDev_ID, 10, &wTemp, 1, 0); // 0ms timeout
            //delayms(100);

        nRead = ReadReg(nDev_ID, 10, &wTemp, 1, 0); // 0ms timeout
        printf("addr : %d\n", wTemp);


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






    //while(1);
    //TESTING POINT #1-----------------------------------------------------------------------------------------------------------------------







    // Configure AFE (section 2.2.1)-------------------------------------------------------------------------------------------------

    nDev_ID = 0;
    nSent = WriteReg(nDev_ID, 60, 0x00, 1, FRMWRT_SGL_NR); // set 0 mux delay
    nSent = WriteReg(nDev_ID, 61, 0x00, 1, FRMWRT_SGL_NR); // set 0 initial delay

    // Configure voltage and internal sample period (section 2.2.2)
    nDev_ID = 0;
    nSent = WriteReg(nDev_ID, 62, 0xCC, 1, FRMWRT_SGL_NR); // set 99.92us ADC sampling period

    // Configure the oversampling rate (section 2.2.3)
    nDev_ID = 0;
    nSent = WriteReg(nDev_ID, 7, 0x00, 1, FRMWRT_SGL_NR); // set no oversampling period

    // Clear and check faults (section 2.2.4)
    nDev_ID = 0;
    nSent = WriteReg(nDev_ID, 81, 0x38, 1, FRMWRT_SGL_NR); // clear fault flags in the system status register
    nSent = WriteReg(nDev_ID, 82, 0xFFC0, 2, FRMWRT_SGL_NR); // clear all fault summary flags
    nRead = ReadReg(nDev_ID, 81, &wTemp, 1, 0); // 0ms timeout
    nRead = ReadReg(nDev_ID, 82, &wTemp, 2, 0); // 0ms timeout

    // Select number of cells and channels to sample (section 2.2.5.1)
    nDev_ID = 0;
    nSent = WriteReg(nDev_ID, 13, 0x10, 1, FRMWRT_SGL_NR); // set number of cells to 16
    nSent = WriteReg(nDev_ID, 3, 0xFFFF03C0, 4, FRMWRT_SGL_NR); // select all cell, AUX channels 0 and 1, and internal digital die and internal analog die temperatures




    // Select identical number of cells and channels on all modules simultaneously (section 2.2.5.2)

//    nSent = WriteReg(0, 13, 0x10, 1, FRMWRT_ALL_NR); // set number of cells to 16
//    nSent = WriteReg(0, 3, 0xFFFF03C0, 4, FRMWRT_ALL_NR); // select all cell, AUX channels 0 and 1, and internal digital die and internal analog die temperatures
//    nSent = WriteReg(0, 13, 0x08, 1, FRMWRT_ALL_NR); // set number of cells to 8
//    nSent = WriteReg(0, 3, 0x00FF03C0, 4, FRMWRT_ALL_NR); // select all cell channels 1-8, AUX channels 0 and 1, and internal digital die and internal analog die temperatures


//    nSent = WriteReg(0, 13, 0x10, 1, FRMWRT_ALL_NR); // set number of cells to 16
//    nSent = WriteReg(0, 3, 0xFFFFFFC0, 4, FRMWRT_ALL_NR); // select all cell, all AUX channe1s, internal digital die and internal analog die temperatures



    // Set cell over-voltage and cell under-voltage thresholds on a single board (section 2.2.6.1)

    nDev_ID = 0;
    nSent = WriteReg(nDev_ID, 144, 0xD1EC, 2, FRMWRT_SGL_NR); // set OV threshold = 4.1000V
    nSent = WriteReg(nDev_ID, 142, 0x6148, 2, FRMWRT_SGL_NR); // set UV threshold = 1.9000V


    // Set cell over-voltage and cell under-voltage thresholds on all boards simultaneously (section 2.2.6.2)
    /*nSent = WriteReg(0, 144, 0xD1EC, 2, FRMWRT_ALL_NR); // set OV threshold = 4.1000V
    nSent = WriteReg(0, 142, 0x6148, 2, FRMWRT_ALL_NR); // set UV threshold = 1.9000V*/


    delayms(100);



    /*Reading Cell (section 3) ------------------------------------------------------------------*/


    // Send broadcast request to all boards to sample and send results (section 3.2)

    //nSent = WriteReg(0, 2, 0x02, 1, FRMWRT_ALL_NR); // send sync sample command
    //nSent = WaitRespFrame(bFrame, 81, 0); // 24 bytes data (x3) + packet header (x3) + CRC (x3), 0ms timeout

    //nSent = WriteReg(0, 0, 0x02, 1, FRMWRT_ALL_NR); // send sync sample command
    //nSent = WaitRespFrame(bFrame, 81, 0); // 24 bytes data (x3) + packet header (x3) + CRC (x3), 0ms timeout



    // PRINTING

    while(1){


        //memset(bFrame, 0, 43);

        //sciEnableNotification(sciREG, SCI_RX_INT);
        int_en = 1;

        nSent = WriteReg(0, 2, 0x02, 1, FRMWRT_SGL_R); // send sync sample command

        //nSent = WaitRespFrame(bFrame, 43, 0); // 24 bytes data (x3) + packet header (x3) + CRC (x3), 0ms timeout


        sciReceive(sciREG, 43, bFrame);


        delayms(100); // for the tms to record all the data first


        int i;
        for(i = 0; i < 50; ++i){ //i < 43    1 header, 16x2 cells, 2 A0, 2 A1, 2 dig die, 2 ana die, 2 CRC
            printf("%x ", bFrame[i]);
        }
        putchar('\n');putchar('\n');

//        int arrayLength = sizeof(bFrame) / sizeof(int);
        int j;
        int cellCount = 1;
        for (j = 0; j < 33; j++) {
            if (j == 0) {
                printf("Header -> Decimal: %d, Hex: %X\n", bFrame[j], bFrame[j]);
                continue;
            }

            int tempVal = bFrame[j]*16*16 + bFrame[j+1];
            double div = tempVal/65535.0; //FFFF
            double fin = div * 5.0;


            printf("Cell %d: Hex: %X%X Voltage: %f \n", cellCount, bFrame[j], bFrame[j+1], fin);
            cellCount++;
            j++;
        }


        // Wait 5 seconds
        delayms(5000);
    }








    //while(1);
































































    // Send broadcast request to all boards to sample and store results (section 3.3.1)
    nSent = WriteReg(0, 2, 0x00, 1, FRMWRT_ALL_NR); // send sync sample command



    // Read sampled data from boards (section 3.3.2)
    // 24 bytes - still configured for 8 AFE channels plus 2 AUX channels plus internal digital and analog die
    // temperatures (see code for section 2.2.5.2)
    nDev_ID = 2;
    nSent = WriteReg(nDev_ID, 2, 0x20, 1, FRMWRT_SGL_R); // send read sampled values command
    nSent = WaitRespFrame(bFrame, 27, 0); // 24 bytes data + packet header + CRC, 0ms timeout
    nDev_ID = 1;
    nSent = WriteReg(nDev_ID, 2, 0x20, 1, FRMWRT_SGL_R); // send read sampled values command
    nSent = WaitRespFrame(bFrame, 27, 0); // 24 bytes data + packet header + CRC, 0ms timeout
    nDev_ID = 0;
    nSent = WriteReg(nDev_ID, 2, 0x20, 1, FRMWRT_SGL_R); // send read sampled values command
    nSent = WaitRespFrame(bFrame, 27, 0); // 24 bytes data + packet header + CRC, 0ms timeout

    // Send sample request to single board to sample and send results (section 4.2)
    nDev_ID = 1;
    nSent = WriteReg(nDev_ID, 2, 0x01, 1, FRMWRT_SGL_NR); // send sync sample command
    nSent = WaitRespFrame(bFrame, 27, 0); // 24 bytes data + packet header + CRC, 0ms timeout

    // Send sample request with embedded channel and oversample information (section 4.3.1)
    nDev_ID = 3;
    nSent = WriteReg(nDev_ID, 2, 0x0000FF03C000, 6, FRMWRT_SGL_NR); // send sync sample command with channel
    // selection and oversample selection embedded

    // Read previously sampled data from single board (section 4.3.2)
    nDev_ID = 0;
    nSent = WriteReg(nDev_ID, 2, 0x20, 1, FRMWRT_SGL_R); // send read sampled values command
    nSent = WaitRespFrame(bFrame, 27, 0); // 24 bytes data + packet header + CRC, 0ms timeout

    // Configure GPIO pin direction and set new pin values (section 5.2.1)
    nDev_ID = 0;
    nSent = WriteReg(nDev_ID, 123, 0x00, 1, FRMWRT_SGL_NR); // turn off all GPIO pull downs
    nSent = WriteReg(nDev_ID, 122, 0x00, 1, FRMWRT_SGL_NR); // turn off all GPIO pull ups
    nSent = WriteReg(nDev_ID, 120, 0x07, 1, FRMWRT_SGL_NR); // set GPIO[2:0] to output direction
    nSent = WriteReg(nDev_ID, 122, 0x07, 1, FRMWRT_SGL_NR); // turn off GPIO[5:4] pull ups and turn on GPIO[2:0] pull ups
    nSent = WriteReg(nDev_ID, 121, 0x01, 1, FRMWRT_SGL_NR); // set GPIO outputs (pattern b001)
    nSent = WriteReg(nDev_ID, 121, 0x02, 1, FRMWRT_SGL_NR); // set GPIO outputs (pattern b010)
    nSent = WriteReg(nDev_ID, 121, 0x04, 1, FRMWRT_SGL_NR); // set GPIO outputs (pattern b100)
    nSent = WriteReg(nDev_ID, 121, 0x07, 1, FRMWRT_SGL_NR); // set GPIO outputs (pattern b111)
    nSent = WriteReg(nDev_ID, 121, 0x00, 1, FRMWRT_SGL_NR); // set GPIO outputs (pattern b000)

    // Configure GPIO inputs with or without pull ups or pull downs (section 5.2.2)
    nDev_ID = 0;
    nSent = WriteReg(nDev_ID, 123, 0x04, 1, FRMWRT_SGL_NR); // enable pull down for GPIO2, turn off all other GPIO pull downs
    nSent = WriteReg(nDev_ID, 122, 0x03, 1, FRMWRT_SGL_NR); // enable pull ups for GPIO[1:0], turn off all other GPIO pull ups
    nSent = WriteReg(0, 122, 0x03, 1, FRMWRT_ALL_NR);   // broadcast to all boards to enable pull ups for GPIO[1:0] and turn off all other GPIO pull ups

    // Setting a GPIO output value (section 5.2.3.1)
    nDev_ID = 0;
    nSent = WriteReg(nDev_ID, 120, 0x17, 1, FRMWRT_SGL_NR); // set GPIO direction for GPIO4 and GPIO[2:0] as outputs, GPIO3 and GPIO5 as inputs
    nSent = WriteReg(nDev_ID, 121, 0x12, 1, FRMWRT_SGL_NR); // set GPIO4 and GPIO1, clear GPIO2 and GPIO0

    // Reading a GPIO input value (section 5.2.3.2)
    nDev_ID = 0;
    nSent = WriteReg(nDev_ID, 120, 0x30, 1, FRMWRT_SGL_NR); // set GPIO direction for GPIO[5:4] as outputs, GPIO[3:0] as inputs
    nRead = ReadReg(nDev_ID, 124, &wTemp, 1, 0);    // read GPIO inputs, 0ms timeout

    // Steps for saving register configuration to EEPROM (sections 6.2.1 to 6.2.4)
    // ** the code is commented out below to avoid accidental use - uncomment to use
    nDev_ID = 0;
    //nSent = WriteReg(nDev_ID, 130, 0x8C2DB194, 4, FRMWRT_SGL_NR); // write Magic Number 1
    //nSent = WriteReg(nDev_ID, 252, 0xA375E60F, 4, FRMWRT_SGL_NR); // write Magic Number 2
    //nSent = WriteReg(nDev_ID, 12, 0x10, 1, FRMWRT_SGL_NR);    // send Write RAM to EEPROM command
    nRead = ReadReg(nDev_ID, 12, &wTemp, 1, 0); // read WRITE_EEPROM status bit, 0ms timeout
    //test WRITE_EEPROM bit to check for completion

    // Steps for saving register configuration to EEPROM in all devices in stack (sections 6.2.5)
    // ** the code is commented out below to avoid accidental use - uncomment to use
    //nSent = WriteReg(0, 130, 0x8C2DB194, 4, FRMWRT_ALL_NR);   // write Magic Number 1
    //nSent = WriteReg(0, 252, 0xA375E60F, 4, FRMWRT_ALL_NR);   // write Magic Number 2
    //nSent = WriteReg(0, 12, 0x10, 1, FRMWRT_ALL_NR);  // send Write RAM to EEPROM command
    nDev_ID = 0;
    nRead = ReadReg(nDev_ID, 12, &wTemp, 1, 0); // read WRITE_EEPROM status bit, 0ms timeout
    //test WRITE_EEPROM bit to check for completion
    nDev_ID = 1;
    nRead = ReadReg(nDev_ID, 12, &wTemp, 1, 0); // read WRITE_EEPROM status bit, 0ms timeout
    //test WRITE_EEPROM bit to check for completion
    nDev_ID = 2;
    nRead = ReadReg(nDev_ID, 12, &wTemp, 1, 0); // read WRITE_EEPROM status bit, 0ms timeout
    //test WRITE_EEPROM bit to check for completion

    // Assign devices to specific group IDs (section 7)
    nDev_ID = 1;
    nSent = WriteReg(nDev_ID, 11, 0x01, 1, FRMWRT_SGL_NR); // assign Dev ID 1 to Group ID 1
    nDev_ID = 2;
    nSent = WriteReg(nDev_ID, 11, 0x01, 1, FRMWRT_SGL_NR); // assign Dev ID 1 to Group ID 1

    delayms(1);
    nRead = ReadReg(1, 11, &wTemp, 1, 0);   // read group ID register, 0ms timeout
    nRead = ReadReg(2, 11, &wTemp, 1, 0);   // read group ID register, 0ms timeout

    // Send group sample request with embedded channel and oversample information (section 7.1)
    // send sync sample command (first data byte = command (b[7:5] = 0) | highest device to respond (0x01)) with
    // channel selection and oversample selection embedded
    nGrp_ID = 1;
    nSent = WriteReg(nGrp_ID, 2, 0x02FFFF550000, 6, FRMWRT_GRP_R);
    nSent = WaitRespFrame(bFrame, 86, 0); // 40 bytes data (x2) + packet header (x2) + CRC (x2), 0ms timeout

    // Send group sample request - 1 byte method (section 7.2)
    // send sync sample command with channel (data byte = command (b[7:5] = 0) | highest device to respond (0x01))
    // sampling parameters are taken from values already stored in Command Channel Select and Oversampling registers
    nGrp_ID = 1;
    nSent = WriteReg(nGrp_ID, 2, 0x02, 1, FRMWRT_GRP_R);
    nSent = WaitRespFrame(bFrame, 86, 0); // 40 bytes data (x2) + packet header (x2) + CRC (x2), 0ms timeout

    // Send group register read - 2 byte method (section 7.3)
    // read Command Channel Select register (first data byte = highest device to respond (0x01), second data byte
    // = number of data bytes - 1 (4 bytes = 0x03))
    // sampling parameters are taken from values already stored in Command Channel Select and Oversampling registers
    nGrp_ID = 1;
    nSent = WriteReg(nGrp_ID, 3, 0x0203, 2, FRMWRT_GRP_R);
    nSent = WaitRespFrame(bFrame, 14, 0); // 4 bytes data (x2) + packet header (x2) + CRC (x2), 0ms timeout

    // Send group register read - 1 byte method (section 7.4)
    // read Command Channel Select register (data byte = number of data bytes - 1 (4 bytes = b011) | highest device
    // to respond (0x01))
    // sampling parameters are taken from values already stored in Command Channel Select and Oversampling registers
    nGrp_ID = 1;
    nSent = WriteReg(nGrp_ID, 3, 0x62, 1, FRMWRT_GRP_R);
    nSent = WaitRespFrame(bFrame, 14, 0); // 4 bytes data (x2) + packet header (x2) + CRC (x2), 0ms timeout

    // Send general broadcast register read - 2 byte method (section 8.1)
    // read Command Channel Select register (first data byte = highest device to respond (0x01), second data byte
    // = number of data bytes - 1 (0x03))
    nSent = WriteReg(0, 3, 0x0203, 2, FRMWRT_ALL_R);
    nSent = WaitRespFrame(bFrame, 14, 0); // 4 bytes data (x2) + packet header (x2) + CRC (x2), 0ms timeout

    // Send general broadcast register read - 1 byte method (section 8.2)
    // read Command Channel Select register (data byte = number of data bytes - 1 (4 bytes = b011) | highest device
    // to respond (0x01))
    nSent = WriteReg(0, 3, 0x62, 1, FRMWRT_ALL_R);
    nSent = WaitRespFrame(bFrame, 14, 0); // 4 bytes data (x2) + packet header (x2) + CRC (x2), 0ms timeout




























    while(1);
/* USER CODE END */


}


/* USER CODE BEGIN (4) */
/* USER CODE END */
