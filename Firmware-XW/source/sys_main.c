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
#include "Phantom_sci.h"

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
uint16 counter;

void my_sciInit(void);
void my_rtiInit(void);
void BMS_init(void);
void BMS_Read(void);
void setBMSTimerPeriod(uint32 timems);

int nSent, nRead, nTopFound = 0;
int nDev_ID, nGrp_ID;
BYTE  bFrame[55];
uint32  wTemp = 0;
bool BMS_READ_FLAG = false;
bool THERMISTOR_READ_FLAG = false;
bool CHARGING_FLAG = false;

bool CELL_OVERVOLTAGE_FLAG[16] = {0};
bool CELL_UNDERVOLTAGE_FLAG[16] = {0};
bool CELL_HIGH_TEMPRATURE_FLAG[16] = {0};
uint16 CELL_VOLTAGE_ERROR_COUNTER[16] = {0};
uint8 TOTAL_CELL_ERROR_COUNTER = 0;
bool TOTAL_CELL_ERROR_FLAG = false;
bool CELL_3SECOND_FLAG = false;

uint16 OverVoltageCount = 0;
uint16 UnderVoltageCount = 0;

#define TMS570_CLK 80000000
// #define BMS_READ 100000

#define STATE_HANDLING 0
#define BMS_READ 1
#define THERMISTOR_READ 2
#define CAN_COMM 3
#define CHARGING 4
#define ERROR_HANDLING 5
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    my_sciInit();

//    UARTSend(scilinREG, "HEllo it's me mahmoud\n\r");

    BMS_init();


    rtiEnableNotification(rtiNOTIFICATION_COMPARE3);

    setBMSTimerPeriod(10000);

    rtiStartCounter(rtiCOUNTER_BLOCK1);

    // PRINTING
    uint8 STATE = STATE_HANDLING;

    while(1){
        switch(STATE){
            case STATE_HANDLING:
                if(CHARGING_FLAG == true){
                    STATE = CHARGING;
                    break;
                }
                if(BMS_READ_FLAG == true){
                    STATE = BMS_READ;
                    break;
                }
                if(THERMISTOR_READ_FLAG == true){
                    STATE = THERMISTOR_READ;
                    break;
                }

                break;
            case BMS_READ:
                BMS_Read();
                BMS_READ_FLAG = false;

                STATE = ERROR_HANDLING;
                break;
            case THERMISTOR_READ:

                STATE = ERROR_HANDLING;
                break;
            case CAN_COMM:
                STATE = STATE_HANDLING;
                break;
            case ERROR_HANDLING:

                STATE = CAN_COMM;
                break;
            case CHARGING:

                STATE = ERROR_HANDLING;
                break;
            default:
                STATE = STATE_HANDLING;
            }
        }
}



/* USER CODE BEGIN (4) */
void BMS_init(){
    _enable_IRQ();
    gioInit();
    my_sciInit();
    while ((sciREG->FLR & 0x4) == 4);
    my_rtiInit();

    sciEnableNotification(sciREG, SCI_RX_INT);

    char buf[50];



//    printf("log: WakeBit:%d FaultBit:%d\n", gioGetBit(gioPORTA, 0), gioGetBit(gioPORTA, 1));
    snprintf(buf, 29, "log: WakeBit:%d FaultBit:%d\n\r", gioGetBit(gioPORTA, 0), gioGetBit(gioPORTA, 1));
    UARTSend(scilinREG, buf);
    WakePL455();
    snprintf(buf, 29, "log: WakeBit:%d FaultBit:%d\n\r", gioGetBit(gioPORTA, 0), gioGetBit(gioPORTA, 1));
    UARTSend(scilinREG, buf);

    UARTSend(scilinREG, "eyo\n\r");

    CommClear();
    CommReset();


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
//    nSent = WriteReg(nDev_ID, 13, 0x10, 1, FRMWRT_SGL_NR); // set number of cells to 16
//    nSent = WriteReg(nDev_ID, 3, 0xFFFF03C0, 4, FRMWRT_SGL_NR); // select all cell, AUX channels 0 and 1, and internal digital die and internal analog die temperatures




    // Select identical number of cells and channels on all modules simultaneously (section 2.2.5.2)

//    nSent = WriteReg(0, 13, 0x10, 1, FRMWRT_ALL_NR); // set number of cells to 16
//    nSent = WriteReg(0, 3, 0xFFFF03C0, 4, FRMWRT_ALL_NR); // select all cell, AUX channels 0 and 1, and internal digital die and internal analog die temperatures
//    nSent = WriteReg(0, 13, 0x08, 1, FRMWRT_ALL_NR); // set number of cells to 8
//    nSent = WriteReg(0, 3, 0x00FF03C0, 4, FRMWRT_ALL_NR); // select all cell channels 1-8, AUX channels 0 and 1, and internal digital die and internal analog die temperatures


    nSent = WriteReg(nDev_ID, 13, 0x10, 1, FRMWRT_ALL_NR); // set number of cells to 16
    nSent = WriteReg(nDev_ID, 3, 0xFFFFFFC0, 4, FRMWRT_ALL_NR); // select all cell, all AUX channe1s, internal digital die and internal analog die temperatures



    // Set cell over-voltage and cell under-voltage thresholds on a single board (section 2.2.6.1)

    nDev_ID = 0;
    nSent = WriteReg(nDev_ID, 144, 0xD70A, 2, FRMWRT_SGL_NR); // set OV threshold = 4.2000V
    nSent = WriteReg(nDev_ID, 142, 0xA3D6, 2, FRMWRT_SGL_NR); // set UV threshold = 3.2000V

}

void BMS_Read(void){

    int_en = 1;

    nSent = WriteReg(0, 2, 0x02, 1, FRMWRT_SGL_R); // send sync sample command

    sciReceive(sciREG, 55, bFrame); //1 header, 16x2 cells, 2x8 AUX, 2 dig die, 2 ana die, 2 CRC

    delayms(100); // for the tms to record all the data first

    uint8 i;

    for(i = 0; i < 55; ++i){
        printf("%X ", bFrame[i]);
    }
    putchar('\n');putchar('\n');

    uint8 j;
    uint8 cellCount = 16;
    for (j = 0; j < 33; j++) {
        if (j == 0) {
            printf("Header -> Decimal: %d, Hex: %X\n", bFrame[j], bFrame[j]);
            putchar('\n');
            continue;
        }

        uint32 tempVal = bFrame[j]*16*16 + bFrame[j+1];
        double div = tempVal/65535.0; //FFFF
        double fin = div * 5.0;


        printf("Cell %d: Hex: %X %X Voltage: %fV \n", cellCount, bFrame[j], bFrame[j+1], fin);
        if(fin > 4.2){
            printf("Cell %d Overvoltage\n", cellCount);
            CELL_OVERVOLTAGE_FLAG[cellCount] = true;
            TOTAL_CELL_ERROR_COUNTER++;
        }
        else if(fin < 3.2){
            printf("Cell %d Undervoltage\n", cellCount);
            CELL_UNDERVOLTAGE_FLAG[cellCount] = true;
            TOTAL_CELL_ERROR_COUNTER++;
        }

        if(CELL_OVERVOLTAGE_FLAG[cellCount] == true || CELL_UNDERVOLTAGE_FLAG[cellCount] == true){
            CELL_VOLTAGE_ERROR_COUNTER[cellCount]++;
        }
        else{
            CELL_VOLTAGE_ERROR_COUNTER[cellCount] = 0;
        }

        if(CELL_VOLTAGE_ERROR_COUNTER[cellCount] > 300){
            CELL_3SECOND_FLAG = true;
        }

        cellCount--;
        j++;
     }

     if(TOTAL_CELL_ERROR_COUNTER > 4){
         TOTAL_CELL_ERROR_FLAG = true;
     }

     TOTAL_CELL_ERROR_COUNTER = 0;
     putchar('\n');

     int auxCount = 7;
     for (j = 33; j < 49; j++) {
         int tempVal = bFrame[j]*16*16 + bFrame[j+1];
         double div = tempVal/65535.0; //FFFF
         double fin = div * 5.0;

         double resistance = 10000*(fin/(4.56-fin));

         printf("AUX %d: Hex: %X %X Voltage: %fV Resistance: %f Ohms\n", auxCount, bFrame[j], bFrame[j+1], fin, resistance);
         j++;
         auxCount--;
     }
     putchar('\n');

     double digDieTemp = ((((bFrame[49]*16*16 + bFrame[50])/65535.0)*5) - 2.287) * 131.944;
     printf("Digital Die: Hex: %X %X Temp: %f degrees C\n", bFrame[49], bFrame[50], digDieTemp);

     double anaDieTemp = ((((bFrame[51]*16*16 + bFrame[52])/65535.0)*5) - 1.8078) * 147.514;
     printf("Analog Die: Hex: %X %X Temp: %f degrees C\n", bFrame[51], bFrame[52], anaDieTemp);
     putchar('\n');

     printf("CRC: Hex: %X %X \n", bFrame[53], bFrame[54]);
}

void rtiNotification(uint32 notification)
{
    if(notification == rtiNOTIFICATION_COMPARE3){
        counter++;
        printf("RTI eyy %d\n", counter);
        BMS_READ_FLAG = true;
    }
}

void setBMSTimerPeriod(uint32 timems){
    rtiSetPeriod(rtiCOMPARE3, (TMS570_CLK/10000)*timems);
}
/* USER CODE END */
