bb/** @file sys_main.c 
*   @brief Application main file
*   @date 28.Aug.2015
*   @version 04.05.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2015 Texas Instruments Incorporated - www.ti.com 
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

int RTI_TIMEOUT = 0;

void SetCS3forWake();
void SetWakeHigh();
void SetWakeLow();


/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */

unsigned int g_ui32PollingChannelRestore =0;
unsigned int g_ui32HostStatus =0;
extern unsigned int g_ui32HostTxReady, g_ui32HostRxReady;
extern unsigned int g_ui32SCIRxReady, g_ui32SCITxReady;
extern unsigned int g_ui32ACBEnabled;
extern void PollingChannelRestore();
extern unsigned int ActiveBalancing(unsigned int flag);
extern void ActiveBalancingInit();


/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */
	register unsigned int temp;
	systemInit();
	gioInit();
#ifdef 0 //code for testing
	initEMB1428Interface(0);
	gioSetBit(gioPORTA, 4, 0); //CS_Store low
		gioSetBit(gioPORTA, 4, 1); //CS_Store high for testing
		gioSetBit(gioPORTA, 4, 0); //CS_Store low for testing
	gioSetBit(gioPORTA, 7, 1); //CS_OE high
		gioSetBit(gioPORTA, 7, 0); //CS_OE low for testing
		gioSetBit(gioPORTA, 7, 1); //CS_OE high for testing

	gioSetBit(gioPORTA, 6, 1); //RS_EMB128 high, Keep 1428 in reset.
		gioSetBit(gioPORTA, 6, 0); //RS_EMB128low for testing
		gioSetBit(gioPORTA, 6, 1); //RS_EMB128 high for testing
	spiInit();
	EMB_Vset(0, 2); // Set the DAC output to control charge/discharege current, use here for testing
#endif
	sciInit();
	sciSetBaudrate(scilinREG, 250000);
	rtiInit();
	vimInit();
	hetInit();
	_enable_IRQ();
	hetREG1->GCR = 0x01030001;
	g_ui32HostRxReady = 0;
	g_ui32HostTxReady = 1;
	g_ui32SCIRxReady = 0;
	g_ui32SCITxReady = 1;

	g_ui32ACBEnabled = 0;
	g_ui32PollingChannelRestore =0;
	HetUART1Config();

//Wakeup Pl455
	SetCS3forWake();
	SetWakeLow();
	delayms(100);
	SetWakeHigh();
	delayms(100);

	ActiveBalancingInit();
	rtiEnableNotification(rtiNOTIFICATION_COMPARE1);
	rtiStartCounter(rtiCOUNTER_BLOCK0);

	while(1)
	{
		if (g_ui32PollingChannelRestore) // need to restore PL455 channel registers after disabling ACB
		{
			PollingChannelRestore();
			g_ui32PollingChannelRestore =0;
		}

		if (g_ui32HostRxReady)   // host communicated with PLL when ACB is in disable state
		{
			g_ui32HostStatus = HostMessageProcess();
			g_ui32HostRxReady =0;
		}

		temp = ActiveBalancing(g_ui32ACBEnabled); // running ACB function. The operation is controlled by the ACB time tick
		if(temp)
		{
			while(1);
		}
	}
/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */
