/*
 * phantom_vcu.c
 *
 *  Created on: Feb 25, 2020
 *      Author: XingLu Wang
 */
#include "phantom_can.h"
#include "can.h"
#include "stdlib.h"
#include "sys_main.h"

#define D_COUNT 8
uint32 cnt = 0, error = 0, tx_done = 0;
//const uint8 tx_data[D_COUNT] = { 21,32,54,2,0,21,3,200 };
char vcu_data[D_COUNT] = { 0 };
//const uint8 *tx_ptr = &tx_data[0];
char *vcu_ptr = &vcu_data[0];
uint8 vcuint = 0;
int timeout;

volatile uint32_t transmitCounter = 0;
volatile uint32_t receiveVCUCounter = 0;

void CANSend(uint8 can_msg[]){
    uint8 tx_data[D_COUNT] = {0};
    memcpy(tx_data, can_msg, 8);

    const uint8 *tx_ptr = &tx_data[0];

    for (cnt = 0; cnt < D_COUNT; cnt++)
        {
            canTransmit(canREG1, canMESSAGE_BOX1, tx_ptr); /* transmitting 8 different chunks 1 by 1 */
            while (timeout != 1U)
            {
              timeout = GetTimeout(); /* ... wait until transmit request is through */
            }

            timeout = 0U;
            tx_done = 0;
            tx_ptr += 8; /* next chunk ...*/
        }
}

void canMessageNotification(canBASE_t *node, uint32 messageBox)
{

    //The following is executed when transmission is successful
    if ((node == canREG1) && (messageBox == canMESSAGE_BOX1))
    {
        tx_done = 1;
        transmitCounter++;
    }

    //The following is executed when reception is successful
    if ((node == canREG1) && (messageBox == canMESSAGE_BOX2))
    {
        while (!canIsRxMessageArrived(canREG1, canMESSAGE_BOX2))
            ;

        canGetData(canREG1, canMESSAGE_BOX2, vcu_ptr); /* copy to RAM */
        vcu_ptr += 8;
        receiveVCUCounter++;

    }
}
void getVCUMSG(void)
{
    return vcu_data;
}


