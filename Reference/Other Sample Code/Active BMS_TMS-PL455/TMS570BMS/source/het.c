/** @file het.c
*   @brief HET Driver Implementation File
*   @date 28.Aug.2015
*   @version 04.05.01
*
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


#include "het.h"
#include "std_nhet.h"
#include "HET_EMU_SCI.h"
#include "sys_vim.h"
/* USER CODE BEGIN (0) */
#include "HET_EMU_SCI.h"
/* USER CODE END */

/*----------------------------------------------------------------------------*/
/* Global variables                                                           */



/** @fn void hetInit(void)
*   @brief Initializes the het Driver
*
*   This function initializes the het 1 module.
*/
/* SourceId : HET_SourceId_001 */
/* DesignId : HET_DesignId_001 */
/* Requirements : HL_SR363 */
void hetInit(void)
{
    /** @b initialize @b HET */

    /** - Set HET pins default output value */
    hetREG1->DOUT = (uint32)((uint32)0U << 31U)
                  | (uint32)((uint32)0U << 30U)
                  | (uint32)((uint32)0U << 29U)
                  | (uint32)((uint32)0U << 28U)
                  | (uint32)((uint32)0U << 27U)
                  | (uint32)((uint32)0U << 26U)
                  | (uint32)((uint32)0U << 25U)
                  | (uint32)((uint32)0U << 24U)
                  | (uint32)((uint32)0U << 23U)
                  | (uint32)((uint32)0U << 22U)
                  | (uint32)((uint32)0U << 21U)
                  | (uint32)((uint32)0U << 20U)
                  | (uint32)((uint32)0U << 19U)
                  | (uint32)((uint32)0U << 18U)
                  | (uint32)((uint32)0U << 17U)
                  | (uint32)((uint32)0U << 16U)
                  | (uint32)((uint32)0U << 15U)
                  | (uint32)((uint32)0U << 14U)
                  | (uint32)((uint32)0U << 13U)
                  | (uint32)((uint32)0U << 12U)
                  | (uint32)((uint32)0U << 11U)
                  | (uint32)((uint32)0U << 10U)
                  | (uint32)((uint32)0U << 9U)
                  | (uint32)((uint32)0U << 8U)
                  | (uint32)((uint32)0U << 7U)
                  | (uint32)((uint32)0U << 6U)
                  | (uint32)((uint32)0U << 5U)
                  | (uint32)((uint32)0U << 4U)
                  | (uint32)((uint32)0U << 3U)
                  | (uint32)((uint32)0U << 2U)
                  | (uint32)((uint32)0U << 1U)
                  | (uint32)((uint32)1U << 0U);

    /** - Set HET pins direction */
    hetREG1->DIR = (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000001U;

    /** - Set HET pins open drain enable */
    hetREG1->PDR = (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U;

    /** - Set HET pins pullup/down enable */
    hetREG1->PULDIS = (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U
                    | (uint32) 0x00000000U;

    /** - Set HET pins pullup/down select */
    hetREG1->PSL = (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U;

    /** - Set HET pins high resolution share */
    hetREG1->HRSH = (uint32) 0x00008000U
                  | (uint32) 0x00004000U
                  | (uint32) 0x00002000U
                  | (uint32) 0x00001000U
                  | (uint32) 0x00000000U
                  | (uint32) 0x00000000U
                  | (uint32) 0x00000000U
                  | (uint32) 0x00000000U
                  | (uint32) 0x00000000U
                  | (uint32) 0x00000000U
                  | (uint32) 0x00000000U
                  | (uint32) 0x00000000U
                  | (uint32) 0x00000008U
                  | (uint32) 0x00000004U
                  | (uint32) 0x00000000U
                  | (uint32) 0x00000000U;

    /** - Set HET pins AND share */
    hetREG1->AND = (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U;

    /** - Set HET pins XOR share */
    hetREG1->XOR = (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U
                 | (uint32) 0x00000000U;

/* USER CODE BEGIN (1) */
/* USER CODE END */

    /** - Setup prescaler values
    *     - Loop resolution prescaler
    *     - High resolution prescaler
    */
    hetREG1->PFR = (uint32)((uint32) 6U << 8U)
                | ((uint32) 0U);


   /** - Parity control register
    *     - Enable/Disable Parity check
    */
    hetREG1->PCR = (uint32) 0x00000005U;

    /** - Fill HET RAM with opcodes and Data */
    /** - "x" in "HET_INITx_PST" denote the HET module Instance
    *      Valid range of x - 0 to 9
    *      For HET1 module x = 0
    *      Refer HET assembler User guide for more Info
    */
    /*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "HET RAM Fill from the table - Allowed as per MISRA rule 11.2" */
    /*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "HET RAM Fill from the table - Allowed as per MISRA rule 11.2" */
    /*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "HET RAM Fill from the table - Allowed as per MISRA rule 11.2" */
    /*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "HET RAM Fill from the table - Allowed as per MISRA rule 11.2" */
    (void)memcpy((void*)hetRAM1, (void*)HET_INIT0_PST, sizeof(HET_INIT0_PST));

    /** - Setup interrupt priority level */
    hetREG1->PRY = 0xFFFFFFFF;

    /** - Enable interrupts */
    hetREG1->INTENAC = 0xFFFFFFFFU;
    hetREG1->INTENAS = (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00200000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U
                     | (uint32) 0x00000000U;


   /** - Setup control register
    *     - Enable output buffers
    *     - Ignore software breakpoints
    *     - Master or Slave Clock Mode
    *     - Enable HET
    */
    hetREG1->GCR = ( 0x00000001U 
                   | (uint32)((uint32)0U << 24U)
	               | (uint32)((uint32)1U << 16U)
                   | (0x00020000U));


}


/* USER CODE BEGIN (4) */
/* USER CODE END */


/** @fn void het1GetConfigValue(het_config_reg_t *config_reg, config_value_type_t type)
*   @brief Get the initial or current values of the HET1 configuration registers
*
*   @param[in] *config_reg: pointer to the struct to which the initial or current
*                           value of the configuration registers need to be stored
*   @param[in] type:    whether initial or current value of the configuration registers need to be stored
*                       - InitialValue: initial value of the configuration registers will be stored
*                                       in the struct pointed by config_reg
*                       - CurrentValue: initial value of the configuration registers will be stored
*                                       in the struct pointed by config_reg
*
*   This function will copy the initial or current value (depending on the parameter 'type')
*   of the configuration registers to the struct pointed by config_reg
*
*/
/* SourceId : HET_SourceId_016 */
/* DesignId : HET_DesignId_016 */
/* Requirements : HL_SR379 */
void het1GetConfigValue(het_config_reg_t *config_reg, config_value_type_t type)
{
    if (type == InitialValue)
    {
        config_reg->CONFIG_GCR     = HET1_GCR_CONFIGVALUE;
        config_reg->CONFIG_PFR     = HET1_PFR_CONFIGVALUE;
        config_reg->CONFIG_INTENAS = HET1_INTENAS_CONFIGVALUE;
        config_reg->CONFIG_INTENAC = HET1_INTENAC_CONFIGVALUE;
        config_reg->CONFIG_PRY     = HET1_PRY_CONFIGVALUE;
        config_reg->CONFIG_AND     = HET1_AND_CONFIGVALUE;
        config_reg->CONFIG_HRSH    = HET1_HRSH_CONFIGVALUE;
        config_reg->CONFIG_XOR     = HET1_XOR_CONFIGVALUE;
        config_reg->CONFIG_DIR     = HET1_DIR_CONFIGVALUE;
        config_reg->CONFIG_PDR     = HET1_PDR_CONFIGVALUE;
        config_reg->CONFIG_PULDIS  = HET1_PULDIS_CONFIGVALUE;
        config_reg->CONFIG_PSL     = HET1_PSL_CONFIGVALUE;
        config_reg->CONFIG_PCR     = HET1_PCR_CONFIGVALUE;
    }
    else
    {
    /*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "LDRA Tool issue" */
        config_reg->CONFIG_GCR     = hetREG1->GCR;
        config_reg->CONFIG_PFR     = hetREG1->PFR;
        config_reg->CONFIG_INTENAS = hetREG1->INTENAS;
        config_reg->CONFIG_INTENAC = hetREG1->INTENAC;
        config_reg->CONFIG_PRY     = hetREG1->PRY;
        config_reg->CONFIG_AND     = hetREG1->AND;
        config_reg->CONFIG_HRSH    = hetREG1->HRSH;
        config_reg->CONFIG_XOR     = hetREG1->XOR;
        config_reg->CONFIG_DIR     = hetREG1->DIR;
        config_reg->CONFIG_PDR     = hetREG1->PDR;
        config_reg->CONFIG_PULDIS  = hetREG1->PULDIS;
        config_reg->CONFIG_PSL     = hetREG1->PSL;
        config_reg->CONFIG_PCR     = hetREG1->PCR;
    }
}

/* USER CODE BEGIN (5) */
/* USER CODE END */

/** @fn void het1HighLevelInterrupt(void)
*   @brief Level 0 Interrupt for HET1
*/
#pragma CODE_STATE(het1HighLevelInterrupt, 32)
#pragma INTERRUPT(het1HighLevelInterrupt, IRQ)

/* SourceId : HET_SourceId_018 */
/* DesignId : HET_DesignId_017 */
/* Requirements : HL_SR371, HL_SR380, HL_SR381 */
void het1HighLevelInterrupt(void)
{
    uint32 vec = hetREG1->OFF1;

    hetNotification(hetREG1,vec);
}


