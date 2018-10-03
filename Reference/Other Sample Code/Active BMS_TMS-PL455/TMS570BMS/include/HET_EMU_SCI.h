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
#ifndef __HET_EMU_SCI_h
#define __HET_EMU_SCI_h

#define HET_v2 1
#define AID1_7

#include "std_nhet.h"

#define HET_SCITX_0	(e_HETPROGRAM0_UN.Program0_ST.SCITX_0)
#define pHET_SCITX_0  	0

#define HET_Lm10_0	(e_HETPROGRAM0_UN.Program0_ST.Lm10_0)
#define pHET_Lm10_0  	1

#define HET_Lm11_0	(e_HETPROGRAM0_UN.Program0_ST.Lm11_0)
#define pHET_Lm11_0  	2

#define HET_SendOverINT_0	(e_HETPROGRAM0_UN.Program0_ST.SendOverINT_0)
#define pHET_SendOverINT_0  	3

#define HET_Lm12_0	(e_HETPROGRAM0_UN.Program0_ST.Lm12_0)
#define pHET_Lm12_0  	4

#define HET_SCIRX_0	(e_HETPROGRAM0_UN.Program0_ST.SCIRX_0)
#define pHET_SCIRX_0  	5

#define HET_Stat0BR_0	(e_HETPROGRAM0_UN.Program0_ST.Stat0BR_0)
#define pHET_Stat0BR_0  	6

#define HET_State0_0	(e_HETPROGRAM0_UN.Program0_ST.State0_0)
#define pHET_State0_0  	7

#define HET_ClrStCNT_0	(e_HETPROGRAM0_UN.Program0_ST.ClrStCNT_0)
#define pHET_ClrStCNT_0  	8

#define HET_ZeroCNT_0	(e_HETPROGRAM0_UN.Program0_ST.ZeroCNT_0)
#define pHET_ZeroCNT_0  	9

#define HET_Wait_Stat0_0	(e_HETPROGRAM0_UN.Program0_ST.Wait_Stat0_0)
#define pHET_Wait_Stat0_0  	10

#define HET_Check_Stat1_0	(e_HETPROGRAM0_UN.Program0_ST.Check_Stat1_0)
#define pHET_Check_Stat1_0  	11

#define HET_Stat1BR_0	(e_HETPROGRAM0_UN.Program0_ST.Stat1BR_0)
#define pHET_Stat1BR_0  	12

#define HET_State1_0	(e_HETPROGRAM0_UN.Program0_ST.State1_0)
#define pHET_State1_0  	13

#define HET_Wait_Stat1_0	(e_HETPROGRAM0_UN.Program0_ST.Wait_Stat1_0)
#define pHET_Wait_Stat1_0  	14

#define HET_Check_Stat2_0	(e_HETPROGRAM0_UN.Program0_ST.Check_Stat2_0)
#define pHET_Check_Stat2_0  	15

#define HET_Stat2BR_0	(e_HETPROGRAM0_UN.Program0_ST.Stat2BR_0)
#define pHET_Stat2BR_0  	16

#define HET_State2_0	(e_HETPROGRAM0_UN.Program0_ST.State2_0)
#define pHET_State2_0  	17

#define HET_Bit13Q_0	(e_HETPROGRAM0_UN.Program0_ST.Bit13Q_0)
#define pHET_Bit13Q_0  	18

#define HET_Bit13A_0	(e_HETPROGRAM0_UN.Program0_ST.Bit13A_0)
#define pHET_Bit13A_0  	19

#define HET_Bit1RecQ_0	(e_HETPROGRAM0_UN.Program0_ST.Bit1RecQ_0)
#define pHET_Bit1RecQ_0  	20

#define HET_ClearNumBit_0	(e_HETPROGRAM0_UN.Program0_ST.ClearNumBit_0)
#define pHET_ClearNumBit_0  	21

#define HET_NumOfBits_0	(e_HETPROGRAM0_UN.Program0_ST.NumOfBits_0)
#define pHET_NumOfBits_0  	22

#define HET_DoneRec_0	(e_HETPROGRAM0_UN.Program0_ST.DoneRec_0)
#define pHET_DoneRec_0  	23

#define HET_CopyRem0_0	(e_HETPROGRAM0_UN.Program0_ST.CopyRem0_0)
#define pHET_CopyRem0_0  	24

#define HET_CopyRem1_0	(e_HETPROGRAM0_UN.Program0_ST.CopyRem1_0)
#define pHET_CopyRem1_0  	25

#define HET_MovStat0_0	(e_HETPROGRAM0_UN.Program0_ST.MovStat0_0)
#define pHET_MovStat0_0  	26

#define HET_Bit5Q_0	(e_HETPROGRAM0_UN.Program0_ST.Bit5Q_0)
#define pHET_Bit5Q_0  	27

#define HET_Bit5A_0	(e_HETPROGRAM0_UN.Program0_ST.Bit5A_0)
#define pHET_Bit5A_0  	28

#define HET_Bit7Q_0	(e_HETPROGRAM0_UN.Program0_ST.Bit7Q_0)
#define pHET_Bit7Q_0  	29

#define HET_Bit7A_0	(e_HETPROGRAM0_UN.Program0_ST.Bit7A_0)
#define pHET_Bit7A_0  	30

#define HET_Bit5to7_0	(e_HETPROGRAM0_UN.Program0_ST.Bit5to7_0)
#define pHET_Bit5to7_0  	31

#define HET_NumBit1_0	(e_HETPROGRAM0_UN.Program0_ST.NumBit1_0)
#define pHET_NumBit1_0  	32

#define HET_CurrSTAT_0	(e_HETPROGRAM0_UN.Program0_ST.CurrSTAT_0)
#define pHET_CurrSTAT_0  	33



typedef union 
{ 
 	HET_MEMORY	Memory0_PST[34];
	struct
	{
		CNT_INSTRUCTION SCITX_0;
		BR_INSTRUCTION Lm10_0;
		DJZ_INSTRUCTION Lm11_0;
		CNT_INSTRUCTION SendOverINT_0;
		SHFT_INSTRUCTION Lm12_0;
		SUB_INSTRUCTION SCIRX_0;
		BR_INSTRUCTION Stat0BR_0;
		BR_INSTRUCTION State0_0;
		MOV32_INSTRUCTION ClrStCNT_0;
		CNT_INSTRUCTION ZeroCNT_0;
		BR_INSTRUCTION Wait_Stat0_0;
		SUB_INSTRUCTION Check_Stat1_0;
		BR_INSTRUCTION Stat1BR_0;
		CNT_INSTRUCTION State1_0;
		BR_INSTRUCTION Wait_Stat1_0;
		SUB_INSTRUCTION Check_Stat2_0;
		BR_INSTRUCTION Stat2BR_0;
		CNT_INSTRUCTION State2_0;
		BR_INSTRUCTION Bit13Q_0;
		AND_INSTRUCTION Bit13A_0;
		SHFT_INSTRUCTION Bit1RecQ_0;
		MOV32_INSTRUCTION ClearNumBit_0;
		CNT_INSTRUCTION NumOfBits_0;
		BR_INSTRUCTION DoneRec_0;
		XOR_INSTRUCTION CopyRem0_0;
		AND_INSTRUCTION CopyRem1_0;
		MOV32_INSTRUCTION MovStat0_0;
		SUB_INSTRUCTION Bit5Q_0;
		BR_INSTRUCTION Bit5A_0;
		SUB_INSTRUCTION Bit7Q_0;
		BR_INSTRUCTION Bit7A_0;
		BR_INSTRUCTION Bit5to7_0;
		CNT_INSTRUCTION NumBit1_0;
		CNT_INSTRUCTION CurrSTAT_0;
	} Program0_ST; 

} HETPROGRAM0_UN;

extern volatile HETPROGRAM0_UN e_HETPROGRAM0_UN;

extern const HET_MEMORY HET_INIT0_PST[34];

#endif

