/* --COPYRIGHT--,BSD
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
#include "HET_EMU.h"
#include "HET.h"
#include <stdio.h>
#include "sci.h"
#include "pl455.h"

unsigned int g_ui32HostRxIndex, g_ui32HostRxCount;
unsigned int g_ui32HostTxIndex, g_ui32HostTxCount;
unsigned int g_ui32HostRxSize, g_ui32HostTxSize;
unsigned int g_ui32HostRxSize0, g_ui32HostRxSize1;
unsigned char *g_ui8HostRxPtr, *g_ui8HostTxPtr;
unsigned char g_ui8HostRxBuf0[32], g_ui8HostRxBuf1[32];
unsigned char g_ui8HostTxBuf[124];
unsigned short g_ui16PL455Addr;
unsigned char g_ui8SCITXBuf[32];
unsigned char g_ui8SCIRXBuf[124];
unsigned int g_ui32HostTxReady, g_ui32HostRxReady;
unsigned int g_ui32SCIRxReady, g_ui32SCITxReady;
extern unsigned int g_ui32PollingChannelRestore;
extern unsigned char g_ui8PL455Registers[];
extern unsigned char g_ui8PL455Data[];
extern unsigned int g_ui32ACBEnabled;

void HetUART1TxStart(unsigned char* data, unsigned int bytes);
void HostRegReturn(unsigned int reg_address, unsigned int size);
void HostDataReturn();
void HostRegWrite(unsigned char *msg_ptr, unsigned int reg_address, unsigned int size);
unsigned int HostMessageProcess2();
extern void sciSend(sciBASE_t *sci, uint32 length, uint8 * data);
extern void sciReceive(sciBASE_t *sci, uint32 length, uint8 * data);


void HetUART1RxISR()
{
	register unsigned char temp;

	g_ui32HostRxCount++;
	if(g_ui32HostRxCount==1)
	{
		if(g_ui32HostRxIndex == 1)
		{
			g_ui8HostRxPtr = g_ui8HostRxBuf0;
		}
		else
		{
			g_ui8HostRxPtr = g_ui8HostRxBuf1;
		}
		temp = hetRAM1->Instruction[25].Data; //read received data
		*g_ui8HostRxPtr++ = temp; //save received data to buffer
		g_ui32HostRxSize = 4; //frame_init + reg addrLSB + 2 CRC bytes
		if( temp & 0x8) g_ui32HostRxSize++; //add reg addr MSB for 16 bit address
		if( (temp & 0xF0) != 0xF0) g_ui32HostRxSize++; //add device addrss for single device access
 		g_ui32HostRxSize += temp &0x7;  //add data bytes
		if( (temp &0x7) == 0x7) g_ui32HostRxSize++; //data bytes cannot be 7

	}
    else
	{
		temp = hetRAM1->Instruction[25].Data; //read received data
		*g_ui8HostRxPtr++ = temp;
	}
	
	if(g_ui32HostRxCount == g_ui32HostRxSize)
	{

		g_ui32HostRxCount= 0;
		if(g_ui32HostRxIndex == 1)
		{
			g_ui32HostRxIndex = 0;
			g_ui32HostRxSize0= g_ui32HostRxSize;
		}
		else
		{
			g_ui32HostRxIndex = 1;
			g_ui32HostRxSize1= g_ui32HostRxSize;
		}
		if(g_ui32ACBEnabled)
		{
			HostMessageProcess2();
		}
		else
		{
			g_ui32HostRxReady = 1;
		}
	}
}

void HetUART1TxISR()
{
	g_ui32HostTxCount++;
	if(g_ui32HostTxCount < g_ui32HostTxSize)
	{
		HetUART1PutChar(*g_ui8HostTxPtr++);
	}
	else
	{
		g_ui32HostTxReady = 1;		//set the transmit completion flag
   		hetREG1->INTENAC = 0x8; 		//disable the transmit interrupt
	}
}

void HetUART1TxStart(unsigned char* data, unsigned int bytes)
{
	g_ui32HostTxReady = 0;
	g_ui32HostTxCount = 0;
	g_ui32HostTxSize = bytes;
	g_ui8HostTxPtr = data;
	HetUART1PutChar(*g_ui8HostTxPtr++);
	hetREG1->INTENAS = 0x8; 		//endable the transmit interrupt

}

void HetUART1Config()
{
	g_ui32HostTxIndex =0;
	g_ui32HostTxReady = 1;
	g_ui32HostTxCount = 0;
	g_ui32HostTxSize = 0;
	g_ui32HostRxIndex =0;
	g_ui32HostRxReady = 0;
	g_ui32HostRxCount = 0;
	g_ui32HostRxSize = 0;
	hetREG1->INTENAC = 0xFFFFFFFF;
	hetREG1->FLG = 0xFFFFFFFF;
    hetREG1->INTENAS = 1<<23;//enable Receive interrupt
}
// HostMessageProcess() for processing GUI message
// return 0: return register data (other than address 0x2)
// return 1: return comaad data (address 0x2)
// return 2: group write
// return 3: signle write (not command)
// return 4: signle write (command)
// return 5: host message CRC error
// return 6: host message not for module 0

extern unsigned int g_ui32ACBEnabled;

/****************************************************************************************/
/* When ACB is in disabled state, this function is called to process the host command 	*/
/* and initiate SCI communication with PL455. It will also send to PL455 data back    	*/
/* to the host.                                                                       	*/
/* HostMessageProcess() for processing GUI message										*/
/* return 0: return register data (other than address 0x2)								*/
/* return 1: return comaad data (address 0x2)											*/
/* return 2: group write																*/
/* return 3: signle write (not command)													*/
/* return 4: signle write (command)														*/
/* return 5: host message CRC error														*/
/* return 6: host message not for module 0												*/
/****************************************************************************************/

unsigned int HostMessageProcess()
{
	register unsigned char *msg_ptr, *data_ptr;
	register unsigned int msg_size, reg_size, i;
	register unsigned short wCRC = 0, wCRC16;
	register unsigned int channels;
	register unsigned int balancing_en_channels;

	register unsigned char temp;
// Select the buffer with received data
	if(g_ui32HostRxIndex == 1)
	{
		msg_ptr = g_ui8HostRxBuf1;
		msg_size = g_ui32HostRxSize1;
	}
	else
	{
		msg_ptr = g_ui8HostRxBuf0;
		msg_size = g_ui32HostRxSize0;
	}
// Check CRC
	wCRC = msg_ptr[msg_size-2];
	temp = msg_ptr[msg_size-1];
	wCRC |= temp << 8;
	wCRC16 = CRC16(msg_ptr, msg_size-2);
	if (wCRC != wCRC16)
	{
		return(5) ;		//return 5 with CRC error
	}
// save the data for debugging

//	for (i=0;i<msg_size;i++)
//	{
//		rxbuf[rxcount][i] = msg_ptr[i];
//	}

	for (i=0;i<msg_size;i++)
	{
		g_ui8HostTxBuf[i] = msg_ptr[i];
	}

//	while (sci_tx_in_use); //check if the sci port is free
//	sci_tx_in_use =1;      //Mark that SCI port is in use
//	sciSend(scilinREG, msg_size,g_ui8HostTxBuf) //send host command to SCI

	if ((*msg_ptr & (0xf0)) == 0xF0)
	{
		//group write without response



		reg_size = msg_ptr[0] & (0x7); //read write zise
		if( (msg_ptr[0]) & 0x8)
		{
			g_ui16PL455Addr = msg_ptr[2] |(msg_ptr[1]<<8); //16 bit address
			data_ptr = &msg_ptr[3];
		}
		else
		{
			g_ui16PL455Addr = msg_ptr[1]; //8 bit address
			data_ptr= &msg_ptr[2];
		}

		HostRegWrite(data_ptr, g_ui16PL455Addr, reg_size);
		if(g_ui16PL455Addr== 0x2)
		{
			g_ui32SCITxReady = 0; //Mark that SCI port is in use
			sciSend(scilinREG, msg_size,g_ui8HostTxBuf); //send host command to SCI
			while(g_ui32SCITxReady == 0U)
			{
			}
		}
#if 0
		while (!g_ui32SCITxReady); //check if the sci port is free
		sciEnableNotification(scilinREG, SCI_TX_INT);
		g_ui32SCITxReady = 0; //Mark that SCI port is in use
		sciSend(scilinREG, msg_size,g_ui8HostTxBuf); //send host command to SCI
		while(g_ui32SCITxReady == 0U)
		{
		}
#endif
		return(2);
	}
	else if ((*msg_ptr & (0xf0)) == 0x90)
	{
		//single  write without response
		if(msg_ptr[1])
		{
			return (2); //return 2 if not for device 0
		}
		else
		{
			reg_size = msg_ptr[0] & (0x7); //read write zise
			if( (msg_ptr[0]) & 0x8)
			{
				g_ui16PL455Addr = msg_ptr[3] |(msg_ptr[2]<<8); //16 bit address
				data_ptr = &msg_ptr[4];
			}
			else
			{
				g_ui16PL455Addr = msg_ptr[2]; //8 bit address
				data_ptr = &msg_ptr[3];
			}

			HostRegWrite(data_ptr, g_ui16PL455Addr, reg_size);

			if(g_ui16PL455Addr== 0x2)
			{
				while(1);
			}


			if(g_ui16PL455Addr== 0x14)
			{
				balancing_en_channels = (g_ui8PL455Registers[0x14]<<8)|g_ui8PL455Registers[0x15];
				if( balancing_en_channels)
				{
					g_ui32ACBEnabled = 1;
				}
				else
				{
					g_ui32ACBEnabled = 0;
				}
			}
			else
			{
				while (!g_ui32SCITxReady); //check if the sci port is free
				sciEnableNotification(scilinREG, SCI_TX_INT);
				g_ui32SCITxReady = 0; //Mark that SCI port is in use
				sciSend(scilinREG, msg_size,g_ui8HostTxBuf); //send host command to SCI
				while(g_ui32SCITxReady == 0U)
				{
				}
			}

			return(3);
		}
	}
	else if((*msg_ptr & (0xf0)) == 0x80)
	{
//      single write with response

		if(msg_ptr[1])
		{
			return (2); //return 2 if not for device 0
		}
		else
		{
			if( (msg_ptr[0]) & 0x8)
			{
				g_ui16PL455Addr = msg_ptr[3] |(msg_ptr[2]<<8); //16 bit address
				reg_size = msg_ptr[4]+1; //read return size
				data_ptr = &msg_ptr[4];
			}
			else
			{
				g_ui16PL455Addr = msg_ptr[2]; //8 bit address
				reg_size = msg_ptr[3]+1; //read return size
				data_ptr = &msg_ptr[3];
			}

			while (!g_ui32SCITxReady); //check if the sci port is free
			sciEnableNotification(scilinREG, SCI_TX_INT);
			g_ui32SCITxReady = 0; //Mark that SCI port is in use
			sciSend(scilinREG, msg_size,g_ui8HostTxBuf); //send host command to SCI
//			while(g_ui32SCITxReady == 0U)
//			{
//			}

			if (g_ui16PL455Addr == 0x2)
			{

				channels = (g_ui8PL455Registers[3]<<24)|(g_ui8PL455Registers[4]<<16)|(g_ui8PL455Registers[5]<<8)|g_ui8PL455Registers[6];
				msg_size = 0;
				for (i=0;i<32;i++)
				{
					if(channels & (1<<i))
					{
						msg_size+=2;
					}
				}

				sciEnableNotification(scilinREG, SCI_RX_INT);
				g_ui32SCIRxReady =0;
				sciReceive(scilinREG, msg_size+3,g_ui8SCIRXBuf);
				while(!g_ui32SCIRxReady);
				g_ui32SCIRxReady = 0;
				g_ui32SCITxReady == 0;
				for (i=0; i<msg_size+3;i++)
				{
					g_ui8HostTxBuf[i] = g_ui8SCIRXBuf[i];
				}
				while(!g_ui32HostTxReady);
				HetUART1TxStart(g_ui8HostTxBuf, msg_size+3);
				return (1);
			}
			else
			{
//				HostRegReturn(g_ui16PL455Addr, reg_size);

				sciEnableNotification(scilinREG, SCI_RX_INT);
				g_ui32SCIRxReady =0;
				sciReceive(scilinREG, reg_size+3,g_ui8SCIRXBuf);
				while(!g_ui32SCIRxReady);
				g_ui32SCIRxReady = 0;
				g_ui32SCITxReady == 0;
				for (i=0; i<reg_size+3;i++)
				{
					g_ui8HostTxBuf[i] = g_ui8SCIRXBuf[i];
				}
				g_ui32HostTxReady = 0;
				HetUART1TxStart(g_ui8HostTxBuf, reg_size+3);
				HostRegWrite(&g_ui8HostTxBuf[1], g_ui16PL455Addr, reg_size);

				if(g_ui16PL455Addr== 0x14)
				{
					balancing_en_channels = (g_ui8PL455Registers[0x14]<<8)|g_ui8PL455Registers[0x15];
					if( balancing_en_channels)
					{
						g_ui32ACBEnabled = 1;
					}
					if( balancing_en_channels)
					{
						g_ui32ACBEnabled = 0;
						channels = (g_ui8PL455Registers[3]<<24)|(g_ui8PL455Registers[4]<<16)|(g_ui8PL455Registers[5]<<8)|g_ui8PL455Registers[6];
						WriteReg(0, 3, channels, 4, FRMWRT_SGL_NR); // upadte the channel registers
					}
				}
				return (0);
			}
		}
	}
}


/**************************************************************************************/
/* When ACB is enabled, the host cannot initiate any communication with PL455 due to  */
/* GUI timing reuqirement. This function returns cell data or registers saved in      */
/* system RAM to the host. It is called by the by the host UART recevie interrupt     */
/* service routine HetUART1RxISR().                                                   */
/**************************************************************************************/
unsigned int HostMessageProcess2()
{
	register unsigned char *msg_ptr, *data_ptr;
	register unsigned int msg_size, reg_size, i;
	register unsigned short wCRC = 0, wCRC16;
	register unsigned int channels;
	register unsigned int balancing_en_channels;

	register unsigned char temp;
// Select the buffer with received data
	if(g_ui32HostRxIndex == 1)
	{
		msg_ptr = g_ui8HostRxBuf1;
		msg_size = g_ui32HostRxSize1;
	}
	else
	{
		msg_ptr = g_ui8HostRxBuf0;
		msg_size = g_ui32HostRxSize0;
	}
// Check CRC
	wCRC = msg_ptr[msg_size-2];
	temp = msg_ptr[msg_size-1];
	wCRC |= temp << 8;
	wCRC16 = CRC16(msg_ptr, msg_size-2);
	if (wCRC != wCRC16)
	{
		return(5) ;		//return 5 with CRC error
	}

	if ((*msg_ptr & (0xf0)) == 0xF0)
	{
		//group write without response
		reg_size = msg_ptr[0] & (0x7); //read write zise
		if( (msg_ptr[0]) & 0x8)
		{
			g_ui16PL455Addr = msg_ptr[2] |(msg_ptr[1]<<8); //16 bit address
			data_ptr = &msg_ptr[3];
		}
		else
		{
			g_ui16PL455Addr = msg_ptr[1]; //8 bit address
			data_ptr= &msg_ptr[2];
		}

		HostRegWrite(data_ptr, g_ui16PL455Addr, reg_size);
#if 0
		if(g_ui16PL455Addr== 0x2)
		{
			g_ui32SCITxReady = 0; //Mark that SCI port is in use
			sciSend(scilinREG, msg_size,g_ui8HostTxBuf); //send host command to SCI
			while(g_ui32SCITxReady == 0U)
			{
			}
		}
#endif
		return(2);
	}
	else if ((*msg_ptr & (0xf0)) == 0x90)
	{
		//single  write without response
		if(msg_ptr[1])
		{
			return (2); //return 2 if not for device 0
		}
		else
		{
			reg_size = msg_ptr[0] & (0x7); //read write zise
			if( (msg_ptr[0]) & 0x8)
			{
				g_ui16PL455Addr = msg_ptr[3] |(msg_ptr[2]<<8); //16 bit address
				data_ptr = &msg_ptr[4];
			}
			else
			{
				g_ui16PL455Addr = msg_ptr[2]; //8 bit address
				data_ptr = &msg_ptr[3];
			}

			HostRegWrite(data_ptr, g_ui16PL455Addr, reg_size);

			if(g_ui16PL455Addr== 0x14)
			{
				balancing_en_channels = (g_ui8PL455Registers[0x14]<<8)|g_ui8PL455Registers[0x15];
				if( balancing_en_channels)
				{
					g_ui32ACBEnabled = 1;
					g_ui32PollingChannelRestore =0;
				}
				else
				{
					g_ui32ACBEnabled = 0;
					g_ui32PollingChannelRestore =1;
				}
			}

			return(3);
		}
	}
	else if((*msg_ptr & (0xf0)) == 0x80)
	{
//      single write with response

		if(msg_ptr[1])
		{
			return (2); //return 2 if not for device 0
		}
		else
		{
			if( (msg_ptr[0]) & 0x8)
			{
				g_ui16PL455Addr = msg_ptr[3] |(msg_ptr[2]<<8); //16 bit address
				reg_size = msg_ptr[4]+1; //read return size
				data_ptr = &msg_ptr[4];
			}
			else
			{
				g_ui16PL455Addr = msg_ptr[2]; //8 bit address
				reg_size = msg_ptr[3]+1; //read return size
				data_ptr = &msg_ptr[3];
			}

			if (g_ui16PL455Addr == 0x2)
			{
				HostDataReturn();
			}
			else
			{
				HostRegReturn(g_ui16PL455Addr, reg_size);
			}
			return (0);
		}
	}
}

/************************************************************************************/
/* function to return register data  saved in system RAM to the host                */
/************************************************************************************/
void HostRegReturn(unsigned int reg_address, unsigned int size)
{
	register unsigned int i;
	register unsigned char *ptr = &g_ui8HostTxBuf[1];
	register unsigned short wCRC16;

	while(!g_ui32HostTxReady); //wait for the tx is ready

	g_ui8HostTxBuf[0] = (unsigned char)(size -1);

	for(i=0;i<size;i++)
	{
		ptr[i] = g_ui8PL455Registers[reg_address+i];
	}
	wCRC16 = CRC16(g_ui8HostTxBuf, size+1);
	g_ui8HostTxBuf[size+2] = (unsigned char)(wCRC16>>8);
	g_ui8HostTxBuf[size+1] = (unsigned char)(wCRC16&0xff);
	while(!g_ui32HostTxReady);
	HetUART1TxStart(g_ui8HostTxBuf, size+3);

}

/************************************************************************************/
/* function to save PL455 register value from SCI message to system RAM             */
/************************************************************************************/
void HostRegWrite(unsigned char *msg_ptr, unsigned int reg_address, unsigned int size)
{
	register unsigned int i;

	for(i=0;i<size;i++)
	{
		g_ui8PL455Registers[reg_address+i] = msg_ptr[i];
	}
}

/************************************************************************************/
/* function to return cell data saved in system RAM to the host                     */
/************************************************************************************/
void HostDataReturn()
{
	register unsigned int i, i1, channels,msg_size ;
	register unsigned char *ptr = &g_ui8HostTxBuf[1];
	register unsigned short wCRC16;

	channels = (g_ui8PL455Registers[3]<<24)|(g_ui8PL455Registers[4]<<16)|(g_ui8PL455Registers[5]<<8)|g_ui8PL455Registers[6];
	msg_size = 0;
	for (i=1;i<=(32-5);i++)
	{
		i1=32-i;
		if(channels & (1<<i1))
		{
			msg_size+=2;
			*ptr++ = g_ui8PL455Data[2*i-1];
			*ptr++ = g_ui8PL455Data[2*i];
		}
	}
	g_ui8HostTxBuf[0] = (unsigned char)(msg_size -1);

	wCRC16 = CRC16(g_ui8HostTxBuf, msg_size+1);
	g_ui8HostTxBuf[msg_size+2] = (unsigned char)(wCRC16>>8);
	g_ui8HostTxBuf[msg_size+1] = (unsigned char)(wCRC16&0xff);
	while(!g_ui32HostTxReady); //wait for the tx is ready
	HetUART1TxStart(g_ui8HostTxBuf, msg_size+3);
}
/************************************************************************************/
/* function to restore the PL455 channels registers with values saved in system RAM */
/************************************************************************************/
void PollingChannelRestore()
{
	register unsigned int channels;
	channels = (g_ui8PL455Registers[3]<<24)|(g_ui8PL455Registers[4]<<16)|(g_ui8PL455Registers[5]<<8)|g_ui8PL455Registers[6];
	WriteReg(0, 3, channels, 4, FRMWRT_SGL_NR); // upadte the channel registers

}
