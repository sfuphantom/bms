/** @file sys_vim.c 
*   @brief VIM Driver Inmplmentation File
*   @date 25.July.2013 
*   @version 03.06.00
*
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */


#include "sys_vim.h"
#include "system.h"
#include "esm.h"

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Vim Ram Definition */
/** @struct vimRam
*   @brief Vim Ram Definition
*
*   This type is used to access the Vim Ram.
*/
/** @typedef vimRAM_t
*   @brief Vim Ram Type Definition
*
*   This type is used to access the Vim Ram.
*/
typedef volatile struct vimRam
{
    t_isrFuncPTR ISR[VIM_CHANNELS + 1U];
} vimRAM_t;

#define vimRAM ((vimRAM_t *)0xFFF82000U)

static const t_isrFuncPTR s_vim_init[129U] =
{
    &phantomInterrupt,
    &esmHighInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &rtiCompare1Interrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &linHighLevelInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
    &phantomInterrupt,
};
void vimParityErrorHandler(void);

/** @fn void vimInit(void)
*   @brief Initializes VIM module
*
*   This function initializes VIM RAM and registers
*/

void vimInit(void)
{
/* Initialize VIM table */
    {
        uint32 i;

        for (i = 0U; i < (VIM_CHANNELS + 1U); i++)
        {
            vimRAM->ISR[i] = s_vim_init[i];
        }
    }
    
    /* Set Fall-Back Address Parity Error Register */
	/*SAFETYMCUSW 439 S MR:11.3 <APPROVED> " Need to store the address of a function in a 32 bit register" */
    VIM_FBPARERR = (uint32)&vimParityErrorHandler;

    /* set IRQ/FIQ priorities */
    vimREG->FIRQPR0 =  SYS_FIQ
                    | (SYS_FIQ <<  1U)
                    | (SYS_IRQ <<  2U)
                    | (SYS_IRQ <<  3U)
                    | (SYS_IRQ <<  4U)
                    | (SYS_IRQ <<  5U)
                    | (SYS_IRQ <<  6U)
                    | (SYS_IRQ <<  7U)
                    | (SYS_IRQ <<  8U)
                    | (SYS_IRQ <<  9U)
                    | (SYS_IRQ << 10U)
                    | (SYS_IRQ << 11U)
                    | (SYS_IRQ << 12U)
                    | (SYS_IRQ << 13U)
                    | (SYS_IRQ << 14U)
                    | (SYS_IRQ << 15U)
                    | (SYS_IRQ << 16U)
                    | (SYS_IRQ << 17U)
                    | (SYS_IRQ << 18U)
                    | (SYS_IRQ << 19U)
                    | (SYS_IRQ << 20U)
                    | (SYS_IRQ << 21U)
                    | (SYS_IRQ << 22U)
                    | (SYS_IRQ << 23U)
                    | (SYS_IRQ << 24U)
                    | (SYS_IRQ << 25U)
                    | (SYS_IRQ << 26U)
                    | (SYS_IRQ << 27U)
                    | (SYS_IRQ << 28U)
                    | (SYS_IRQ << 29U)
                    | (SYS_IRQ << 30U)
                    | (SYS_IRQ << 31U);

    vimREG->FIRQPR1 =  SYS_IRQ
                    | (SYS_IRQ <<  1U)
                    | (SYS_IRQ <<  2U)
                    | (SYS_IRQ <<  3U)
                    | (SYS_IRQ <<  4U)
                    | (SYS_IRQ <<  5U)
                    | (SYS_IRQ <<  6U)
                    | (SYS_IRQ <<  7U)
                    | (SYS_IRQ <<  8U)
                    | (SYS_IRQ <<  9U)
                    | (SYS_IRQ << 10U)
                    | (SYS_IRQ << 11U)
                    | (SYS_IRQ << 12U)
                    | (SYS_IRQ << 13U)
                    | (SYS_IRQ << 14U)
                    | (SYS_IRQ << 15U)
                    | (SYS_IRQ << 16U)
                    | (SYS_IRQ << 17U)
                    | (SYS_IRQ << 18U)
                    | (SYS_IRQ << 19U)
                    | (SYS_IRQ << 20U)
                    | (SYS_IRQ << 21U)
                    | (SYS_IRQ << 22U)
                    | (SYS_IRQ << 23U)
                    | (SYS_IRQ << 24U)
                    | (SYS_IRQ << 25U)
                    | (SYS_IRQ << 26U)
                    | (SYS_IRQ << 27U)
                    | (SYS_IRQ << 28U)
                    | (SYS_IRQ << 29U)
                    | (SYS_IRQ << 30U)
                    | (SYS_IRQ << 31U);


    vimREG->FIRQPR2 =  SYS_IRQ
                    | (SYS_IRQ << 1U)
                    | (SYS_IRQ << 2U)
                    | (SYS_IRQ << 3U)
                    | (SYS_IRQ << 4U)
                    | (SYS_IRQ << 5U)
                    | (SYS_IRQ << 6U)
                    | (SYS_IRQ << 7U)
                    | (SYS_IRQ << 8U)
                    | (SYS_IRQ << 9U)
                    | (SYS_IRQ << 10U)
                    | (SYS_IRQ << 11U)
                    | (SYS_IRQ << 12U)
                    | (SYS_IRQ << 13U)
                    | (SYS_IRQ << 14U)
                    | (SYS_IRQ << 15U)
                    | (SYS_IRQ << 16U)
                    | (SYS_IRQ << 17U)
                    | (SYS_IRQ << 18U)
                    | (SYS_IRQ << 19U)
                    | (SYS_IRQ << 20U)
                    | (SYS_IRQ << 21U)
                    | (SYS_IRQ << 22U)
                    | (SYS_IRQ << 23U)
                    | (SYS_IRQ << 24U)
                    | (SYS_IRQ << 25U)
                    | (SYS_IRQ << 26U)
                    | (SYS_IRQ << 27U)
                    | (SYS_IRQ << 28U)
                    | (SYS_IRQ << 29U)
                    | (SYS_IRQ << 30U)
                    | (SYS_IRQ << 31U);

    vimREG->FIRQPR3 =  SYS_IRQ
                    | (SYS_IRQ << 1U)
                    | (SYS_IRQ << 2U)
                    | (SYS_IRQ << 3U)
                    | (SYS_IRQ << 4U)
                    | (SYS_IRQ << 5U)
                    | (SYS_IRQ << 6U)
                    | (SYS_IRQ << 7U)
                    | (SYS_IRQ << 8U)
                    | (SYS_IRQ << 9U)
                    | (SYS_IRQ << 10U)
                    | (SYS_IRQ << 11U)
                    | (SYS_IRQ << 12U)
                    | (SYS_IRQ << 13U)
                    | (SYS_IRQ << 14U)
                    | (SYS_IRQ << 15U)
                    | (SYS_IRQ << 16U)
                    | (SYS_IRQ << 17U)
                    | (SYS_IRQ << 18U)
                    | (SYS_IRQ << 19U)
                    | (SYS_IRQ << 20U)
                    | (SYS_IRQ << 21U)
                    | (SYS_IRQ << 22U)
                    | (SYS_IRQ << 23U)
                    | (SYS_IRQ << 24U)
                    | (SYS_IRQ << 25U)
                    | (SYS_IRQ << 26U)
                    | (SYS_IRQ << 27U)
                    | (SYS_IRQ << 28U)
                    | (SYS_IRQ << 29U)
                    | (SYS_IRQ << 30U)
                    | (SYS_IRQ << 31U);

                    
    /* enable interrupts */
    vimREG->REQMASKSET0 = 1U
                        | (1U << 1U)
                        | (0U << 2U)
                        | (1U << 3U)
                        | (0U << 4U)
                        | (0U << 5U)
                        | (0U << 6U)
                        | (0U << 7U)
                        | (0U << 8U)
                        | (0U << 9U)
                        | (0U << 10U)
                        | (0U << 11U)
                        | (0U << 12U)
                        | (1U << 13U)
                        | (0U << 14U)
                        | (0U << 15U)
                        | (0U << 16U)
                        | (0U << 17U)
                        | (0U << 18U)
                        | (0U << 19U)
                        | (0U << 20U)
                        | (0U << 21U)
                        | (0U << 22U)
                        | (0U << 23U)
                        | (0U << 24U)
                        | (0U << 25U)
                        | (0U << 26U)
                        | (0U << 27U)
                        | (0U << 28U)
                        | (0U << 29U)
                        | (0U << 30U)
                        | (0U << 31U);

    vimREG->REQMASKSET1 = 0U
                        | (0U << 1U)
                        | (0U << 2U)
                        | (0U << 3U)
                        | (0U << 4U)
                        | (0U << 5U)
                        | (0U << 6U)
                        | (0U << 7U)
                        | (0U << 8U)
                        | (0U << 9U)
                        | (0U << 10U)
                        | (0U << 11U)
                        | (0U << 12U)
                        | (0U << 13U)
                        | (0U << 14U)
                        | (0U << 15U)
                        | (0U << 16U)
                        | (0U << 17U)
                        | (0U << 18U)
                        | (0U << 19U)
                        | (0U << 20U)
                        | (0U << 21U)
                        | (0U << 22U)
                        | (0U << 23U)
                        | (0U << 24U)
                        | (0U << 25U)
                        | (0U << 26U)
                        | (0U << 27U)
                        | (0U << 28U)
                        | (0U << 29U)
                        | (0U << 30U)
                        | (0U << 31U);

    vimREG->REQMASKSET2 = 0U
                        | (0U << 1U)
                        | (0U << 2U)
                        | (0U << 3U)
                        | (0U << 4U)
                        | (0U << 5U)
                        | (0U << 6U)
                        | (0U << 7U)
                        | (0U << 8U)
                        | (0U << 9U)
                        | (0U << 10U)
                        | (0U << 11U)
                        | (0U << 12U)
                        | (0U << 13U)
                        | (0U << 14U)
                        | (0U << 15U)
                        | (0U << 16U)
                        | (0U << 17U)
                        | (0U << 18U)
                        | (0U << 19U)
                        | (0U << 20U)
                        | (0U << 21U)
                        | (0U << 22U)
                        | (0U << 23U)
                        | (0U << 24U)
                        | (0U << 25U)
                        | (0U << 26U)
                        | (0U << 27U)
                        | (0U << 28U)
                        | (0U << 29U)
                        | (0U << 30U)
                        | (0U << 31U);
                        
    vimREG->REQMASKSET3 =  0U
                        | (0U << 1U)
                        | (0U << 2U)
                        | (0U << 3U)
                        | (0U << 4U)
                        | (0U << 5U)
                        | (0U << 6U)
                        | (0U << 7U)
                        | (0U << 8U)
                        | (0U << 9U)
                        | (0U << 10U)
                        | (0U << 11U)
                        | (0U << 12U)
                        | (0U << 13U)
                        | (0U << 14U)
                        | (0U << 15U)
                        | (0U << 16U)
                        | (0U << 17U)
                        | (0U << 18U)
                        | (0U << 19U)
                        | (0U << 20U)
                        | (0U << 21U)
                        | (0U << 22U)
                        | (0U << 23U)
                        | (0U << 24U)
                        | (0U << 25U)
                        | (0U << 26U)
                        | (0U << 27U)
                        | (0U << 28U)
                        | (0U << 29U)
                        | (0U << 30U)
                        | (0U << 31U);    
}

/** @fn void vimChannelMap(uint32 request, uint32 channel, t_isrFuncPTR handler)
*   @brief Map selected interrupt request to the selected channel
*
*    @param[in] request: Interrupt request number 2..95
*    @param[in] channel: VIM Channel number 2..95
*    @param[in] handler: Address of the interrupt handler
*
*   This function will map selected interrupt request to the selected channel.
*
*/
void vimChannelMap(uint32 request, uint32 channel, t_isrFuncPTR handler)
{
    uint32 i,j;
    i = channel >> 2U;              /* Find the register to configure */
    j = channel -(i<<2U);           /* Find the offset of the type    */
    j = 3U-j;                       /* reverse the byte order         */
    j = j<<3U;                      /* find the bit location          */

    /*Mapping the required interrupt request to the required channel*/
    vimREG->CHANCTRL[i] &= ~(0xFFU << j);
    vimREG->CHANCTRL[i] |= (request << j);

    /*Updating VIMRAM*/
    vimRAM->ISR[channel+1] = handler;
}

/** @fn void vimEnableInterrupt(uint32 channel, boolean inttype)
*   @brief Enable interrupt for the the selected channel
*
*    @param[in] channel: VIM Channel number 2..95
*    @param[in] handler: Interrupt type
*                        - SYS_IRQ: Selected channel will be enabled as IRQ
*                        - SYS_FIQ: Selected channel will be enabled as FIQ
*
*   This function will enable interrupt for the selected channel.
*
*/
void vimEnableInterrupt(uint32 channel, boolean inttype)
{
    if (channel >= 64U)
    {
        if(inttype == SYS_IRQ)
        {
            vimREG->FIRQPR2 &= ~(1U << (channel-64U));
        }
        else
        {
            vimREG->FIRQPR2 |= 1U << (channel-64U);
        }
        vimREG->REQMASKSET2 = 1U << (channel-64U);
    }
    else if (channel >= 32U)
    {
        if(inttype == SYS_IRQ)
        {
            vimREG->FIRQPR1 &= ~(1U << (channel-32U));
        }
        else
        {
            vimREG->FIRQPR1 |= 1U << (channel-32U);
        }
        vimREG->REQMASKSET1 = 1U << (channel-32U);
    }
    else if (channel >= 2U)
    {
        if(inttype == SYS_IRQ)
        {
            vimREG->FIRQPR0 &= ~(1U << channel);
        }
        else
        {
            vimREG->FIRQPR0 |= 1U << channel;
        }
        vimREG->REQMASKSET0 = 1U << channel;
    }
    else
    {
		/* Empty */
    }
}

/** @fn void vimDisableInterrupt(uint32 channel)
*   @brief Disable interrupt for the the selected channel
*
*    @param[in] channel: VIM Channel number 2..95
*
*   This function will disable interrupt for the selected channel.
*
*/
void vimDisableInterrupt(uint32 channel)
{
    if (channel >= 64U)
    {
        vimREG->REQMASKCLR2 = 1U << (channel-64U);
    }
    else if (channel >=32U)
    {
        vimREG->REQMASKCLR1 = 1U << (channel-32U);
    }
    else if (channel >= 2U)
    {
        vimREG->REQMASKCLR0 = 1U << channel;
    }
    else
    {
		/* Empty */
    }
}

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @fn void vimGetConfigValue(vim_config_reg_t *config_reg, config_value_type_t type)
*   @brief Get the initial or current values of the configuration registers
*
*    @param[in] *config_reg: pointer to the struct to which the initial or current value of the configuration registers need to be stored
*    @param[in] type:     whether initial or current value of the configuration registers need to be stored
*                        - InitialValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*                        - CurrentValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*
*   This function will copy the initial or current value (depending on the parameter 'type') of the configuration 
*   registers to the struct pointed by config_reg
*
*/

void vimGetConfigValue(vim_config_reg_t *config_reg, config_value_type_t type)
{  
    if (type == InitialValue)
    {
        config_reg->CONFIG_FIRQPR0 = VIM_FIRQPR0_CONFIGVALUE;
        config_reg->CONFIG_FIRQPR1 = VIM_FIRQPR1_CONFIGVALUE;
        config_reg->CONFIG_FIRQPR2 = VIM_FIRQPR2_CONFIGVALUE;
        config_reg->CONFIG_FIRQPR3 = VIM_FIRQPR3_CONFIGVALUE;
        config_reg->CONFIG_REQMASKSET0 = VIM_REQMASKSET0_CONFIGVALUE;
        config_reg->CONFIG_REQMASKSET1 = VIM_REQMASKSET1_CONFIGVALUE;
        config_reg->CONFIG_REQMASKSET2 = VIM_REQMASKSET2_CONFIGVALUE;
        config_reg->CONFIG_REQMASKSET3 = VIM_REQMASKSET3_CONFIGVALUE;
        config_reg->CONFIG_WAKEMASKSET0 = VIM_WAKEMASKSET0_CONFIGVALUE;
        config_reg->CONFIG_WAKEMASKSET1 = VIM_WAKEMASKSET1_CONFIGVALUE;
        config_reg->CONFIG_WAKEMASKSET2 = VIM_WAKEMASKSET2_CONFIGVALUE;
        config_reg->CONFIG_WAKEMASKSET3 = VIM_WAKEMASKSET3_CONFIGVALUE;
        config_reg->CONFIG_CAPEVT = VIM_CAPEVT_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[0] = VIM_CHANCTRL0_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[1] = VIM_CHANCTRL1_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[2] = VIM_CHANCTRL2_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[3] = VIM_CHANCTRL3_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[4] = VIM_CHANCTRL4_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[5] = VIM_CHANCTRL5_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[6] = VIM_CHANCTRL6_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[7] = VIM_CHANCTRL7_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[8] = VIM_CHANCTRL8_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[9] = VIM_CHANCTRL9_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[10] = VIM_CHANCTRL10_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[11] = VIM_CHANCTRL11_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[12] = VIM_CHANCTRL12_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[13] = VIM_CHANCTRL13_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[14] = VIM_CHANCTRL14_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[15] = VIM_CHANCTRL15_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[16] = VIM_CHANCTRL16_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[17] = VIM_CHANCTRL17_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[18] = VIM_CHANCTRL18_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[19] = VIM_CHANCTRL19_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[20] = VIM_CHANCTRL20_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[21] = VIM_CHANCTRL21_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[22] = VIM_CHANCTRL22_CONFIGVALUE;
		config_reg->CONFIG_CHANCTRL[23] = VIM_CHANCTRL23_CONFIGVALUE;
    }
    else
    {
	/*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "Register read back support" */
        config_reg->CONFIG_FIRQPR0 = vimREG->FIRQPR0;
        config_reg->CONFIG_FIRQPR1 = vimREG->FIRQPR1;
        config_reg->CONFIG_FIRQPR2 = vimREG->FIRQPR2;
        config_reg->CONFIG_FIRQPR3 = vimREG->FIRQPR3;
        config_reg->CONFIG_REQMASKSET0 = vimREG->REQMASKSET0;
        config_reg->CONFIG_REQMASKSET1 = vimREG->REQMASKSET1;
        config_reg->CONFIG_REQMASKSET2 = vimREG->REQMASKSET2;
        config_reg->CONFIG_REQMASKSET3 = vimREG->REQMASKSET3;
        config_reg->CONFIG_WAKEMASKSET0 = vimREG->WAKEMASKSET0;
        config_reg->CONFIG_WAKEMASKSET1 = vimREG->WAKEMASKSET1;
        config_reg->CONFIG_WAKEMASKSET2 = vimREG->WAKEMASKSET2;
        config_reg->CONFIG_WAKEMASKSET3 = vimREG->WAKEMASKSET3;
        config_reg->CONFIG_CAPEVT = vimREG->CAPEVT;
		config_reg->CONFIG_CHANCTRL[0] = vimREG->CHANCTRL[0];
		config_reg->CONFIG_CHANCTRL[1] = vimREG->CHANCTRL[1];
		config_reg->CONFIG_CHANCTRL[2] = vimREG->CHANCTRL[2];
		config_reg->CONFIG_CHANCTRL[3] = vimREG->CHANCTRL[3];
		config_reg->CONFIG_CHANCTRL[4] = vimREG->CHANCTRL[4];
		config_reg->CONFIG_CHANCTRL[5] = vimREG->CHANCTRL[5];
		config_reg->CONFIG_CHANCTRL[6] = vimREG->CHANCTRL[6];
		config_reg->CONFIG_CHANCTRL[7] = vimREG->CHANCTRL[7];
		config_reg->CONFIG_CHANCTRL[8] = vimREG->CHANCTRL[8];
		config_reg->CONFIG_CHANCTRL[9] = vimREG->CHANCTRL[9];
		config_reg->CONFIG_CHANCTRL[10] = vimREG->CHANCTRL[10];
		config_reg->CONFIG_CHANCTRL[11] = vimREG->CHANCTRL[11];
		config_reg->CONFIG_CHANCTRL[12] = vimREG->CHANCTRL[12];
		config_reg->CONFIG_CHANCTRL[13] = vimREG->CHANCTRL[13];
		config_reg->CONFIG_CHANCTRL[14] = vimREG->CHANCTRL[14];
		config_reg->CONFIG_CHANCTRL[15] = vimREG->CHANCTRL[15];
		config_reg->CONFIG_CHANCTRL[16] = vimREG->CHANCTRL[16];
		config_reg->CONFIG_CHANCTRL[17] = vimREG->CHANCTRL[17];
		config_reg->CONFIG_CHANCTRL[18] = vimREG->CHANCTRL[18];
		config_reg->CONFIG_CHANCTRL[19] = vimREG->CHANCTRL[19];
		config_reg->CONFIG_CHANCTRL[20] = vimREG->CHANCTRL[20];
		config_reg->CONFIG_CHANCTRL[21] = vimREG->CHANCTRL[21];
		config_reg->CONFIG_CHANCTRL[22] = vimREG->CHANCTRL[22];
		config_reg->CONFIG_CHANCTRL[23] = vimREG->CHANCTRL[23];


        
    }
}


#pragma CODE_STATE(vimParityErrorHandler, 32)
#pragma INTERRUPT(vimParityErrorHandler, IRQ)
#pragma WEAK(vimParityErrorHandler)

void vimParityErrorHandler(void)
{
    uint32 vec;
    
    /* Identify the corrupted address */
    uint32 error_addr = VIM_ADDERR;

    /* Identify the channel number */
    uint32 error_channel = ((error_addr & 0x1FFU) >> 2U) - 1U;

    /* Correct the corrupted location */
    vimRAM->ISR[error_channel + 1U] = s_vim_init[error_channel + 1U];

    /* Clear Parity Error Flag */
    VIM_PARFLG = 1U;

    /* Disable and enable the highest priority pending channel */
    if (vimREG->FIQINDEX != 0U)
    {
        vec = vimREG->FIQINDEX - 1U;
    }
    else 
    {
	   /*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "Read 32 bit volatile register" */
        vec = vimREG->IRQINDEX - 1U;
    }
    if(vec == 0U)
    {
        vimREG->INTREQ0 = 1U;
	    vec = esmREG->IOFFHR - 1U;
		
        if (vec < 32U)
        {
            esmREG->SR1[0U] = 1U << vec;
            esmGroup1Notification(vec);
        }
        else if (vec < 64U)
        {
            esmREG->SR1[1U] = 1U << (vec-32U);
            esmGroup2Notification(vec-32U);
        }
        else if (vec < 96U)
        {
            esmREG->SR4[0U] = 1U << (vec-64U);
            esmGroup1Notification(vec-32U);
        }
        else if (vec < 128U)
        {
            esmREG->SR4[1U] = 1U << (vec-96U);
            esmGroup2Notification(vec-64U);
        }
    }
    else if (vec < 32U)
    {
        vimREG->REQMASKCLR0 = 1U << vec;
        vimREG->REQMASKSET0 = 1U << vec;
    }
    else if (vec < 64U)
    {
        vimREG->REQMASKCLR1 = 1U << (vec-32U);
        vimREG->REQMASKSET1 = 1U << (vec-32U);
    }
    else
    {
        vimREG->REQMASKCLR2 = 1U << (vec-64U);
        vimREG->REQMASKSET2 = 1U << (vec-64U);
    }
    
}
