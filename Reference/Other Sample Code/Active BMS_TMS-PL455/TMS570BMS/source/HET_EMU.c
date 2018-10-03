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

/** @fn void HetUART1PutChar(unsigned char Data)
*   @brief Sends a character of characters over HET emulated SCI
*
*   @param[in]  Data		The character to send
*/
void HetUART1PutChar(char Data)
{
  unsigned int Tmp = Data;

  Tmp <<= 1;                                    // Shift in start bit (0)
  Tmp |= 0x00000200;                            // Add stop bit (1)
  while(hetRAM1->Instruction[2].Data != 0);
  hetRAM1->Instruction[4].Data = Tmp << 7;  // Load TX buffer
  hetRAM1->Instruction[2].Data =  10 << 7;  // Load bit count
}

/** @fn void HetUART1PutText(unsigned char *text)
*   @brief Sends a string of characters over HET emulated SCI
*
*   @param[in]  text		The string of characters to send
*/
void HetUART1PutText(char *text)
{
	while(*text != 0)
	{
		HetUART1PutChar(*text++);
	}
}

/** @fn unsigned HetUART1Printf(const char *_format, ...)
*   @brief sends data to terminal (HET emulated SCI)
*
*   @param[in]  _format - string with format argument
*   @return      length of sent string
*
*   Sends formated string to terminal on HET emulated SCI
*/

unsigned HetUART1Printf(const char *_format, ...)
{
   char str[128];
   int length = -1, k = 0;

   va_list argList;
   va_start( argList, _format );

   length = vsnprintf(str, sizeof(str), _format, argList);

   va_end( argList );

   if (length > 0)
   {
      for(k=0; k<length; k++)
      {
    	  HetUART1PutChar(str[k]);
      }
   }

   return (unsigned)length;
}


/** @fn char HetUART1GetChar()
*   @brief		Gets a character from the HET Emulated SCI Receive Buffer if one is available
*
*	@return		The character in the receive buffer, if one is available. If not, 0.
*/
char HetUART1GetChar(void)
{
	unsigned int HetFlag;
	HetFlag = hetREG1->FLG;
	if(HetFlag & (1<<23))
	{
		hetREG1->FLG = (1<<23); // clear this bit
		return((char)(hetRAM1->Instruction[25].Data));
	}
	else
		return 0;
}

char HetUART1GetCharPoll(void)
{
	unsigned int HetFlag;

	HetFlag = hetREG1->FLG;
	while (!(HetFlag & (1<<23)))
	{
		HetFlag = hetREG1->FLG;
	}
	hetREG1->FLG = (1<<23); // clear this bit
	return((char)(hetRAM1->Instruction[25].Data));

}
