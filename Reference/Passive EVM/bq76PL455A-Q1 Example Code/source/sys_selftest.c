/** @file sys_selftest.c 
*   @brief Selftest Source File
*   @date 25.July.2013
*   @version 03.06.00
*
*   This file contains:
*   - Selftest API's
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */

#include "sys_selftest.h"
#include "sys_core.h"


/** @fn void selftestFailNotification(uint32 flag)
*   @brief Self test fail service routine
*
*    This function is called if there is a self test fail with appropriate flag
*/
void selftestFailNotification(uint32 flag)
{

/* USER CODE BEGIN (1) */
/* USER CODE END */

}

/* USER CODE BEGIN (2) */
/* USER CODE END */


/** @fn void ccmSelfCheck(void)
*   @brief CCM module self check Driver
*
*   This function self checks the CCM module.
*/
void ccmSelfCheck(void)
{
/* USER CODE BEGIN (3) */
/* USER CODE END */

    /* Run a diagnostic check on the CCM-R4F module */
    /* This step ensures that the CCM-R4F can actually indicate an error */

    /* Configure CCM in self-test mode */
    CCMKEYR = 0x6U;                                
    /* Wait for CCM self-test to complete */
	/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while ((CCMSR & 0x100U) != 0x100U)
    { 
    }/* Wait */         

/* USER CODE BEGIN (4) */
/* USER CODE END */
    
    /* Check if there was an error during the self-test */
    if ((CCMSR & 0x1U) == 0x1U)
    {
        /* STE is set */
        selftestFailNotification(CCMSELFCHECK_FAIL1);                                
    }
    else
    {
        /* Check CCM-R4 self-test error flag by itself (without compare error) */
        if ((esmREG->SR1[0U] & 0x80000000U) == 0x80000000U)
        {
            /* ESM flag is not set */
            selftestFailNotification(CCMSELFCHECK_FAIL2);
        }
        else
        {            
            /* Configure CCM in error-forcing mode */
            CCMKEYR = 0x9U;
            
            /* Wait till error-forcing is completed. */
			/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
            while (CCMKEYR != 0U)
            {
            }/* Wait */ 
            
            /* check if compare error flag is set */
            if ((esmREG->SR1[1U] & 0x4U) != 0x4U)
            {
                /* ESM flag is not set */
                selftestFailNotification(CCMSELFCHECK_FAIL3);
            }
            else
            {
                /* Check FIQIVEC to ESM High Interrupt flag is set */ 
                if((vimREG->FIQINDEX & 0x000000FFU) != 1U)
                {
                   /* ESM High Interrupt flag is not set in VIM*/
                   selftestFailNotification(CCMSELFCHECK_FAIL4);
                }
                
                /* clear ESM group2 channel 2 flag */ 
                esmREG->SR1[1U] = 0x4U;
                
                /* clear ESM group2 shadow status flag */
                esmREG->ESTATUS5EMU = 0x4U;                
                
                /* ESM self-test error needs to also be cleared */
                esmREG->SR1[0U] = 0x80000000U;        
                
                /* The nERROR pin will become inactive once the LTC counter expires */
                esmREG->EKR = 0x5U;    

                /* Configure CCM in selftest error-forcing mode */
                CCMKEYR = 0xFU;

                /* Wait till selftest error-forcing is completed. */
				/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
                while (CCMKEYR != 0U)
                {
                }/* Wait */ 

                if((esmREG->SR1[0U] & 0x80000000U) != 0x80000000U)
                {
                    /* ESM flag not set */
                    selftestFailNotification(CCMSELFCHECK_FAIL2);
                }
                else
                {
                    /* clear ESM flag */
                    esmREG->SR1[0U] = 0x80000000U;
                }
            }
        }
    }
}

/* USER CODE BEGIN (5) */
/* USER CODE END */


/** @fn void memoryInit(uint32 ram)
*   @brief Memory Initialization Driver
*
*   This function is called to perform Memory initialization of selected RAM's.
*/
void memoryInit(uint32 ram)
{
/* USER CODE BEGIN (6) */
/* USER CODE END */

    /* Enable Memory Hardware Initialization */
    systemREG1->MINITGCR = 0xAU;    
    
    /* Enable Memory Hardware Initialization for selected RAM's */
    systemREG1->MSINENA  = ram;
    
    /* Wait until Memory Hardware Initialization complete */
	/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while((systemREG1->MSTCGSTAT & 0x00000100U) != 0x00000100U)
    { 
    }/* Wait */         
    
    /* Disable Memory Hardware Initialization */
    systemREG1->MINITGCR = 0x5U;    
    
/* USER CODE BEGIN (7) */
/* USER CODE END */
}

/** @fn void stcSelfCheck(void)
*   @brief STC module self check Driver
*
*   This function is called to perform STC module self check.
*/
void stcSelfCheck(void)
{
/* USER CODE BEGIN (8) */
/* USER CODE END */
    uint32 i = 0U;

    /* Run a diagnostic check on the CPU self-test controller */
    /* First set up the STC clock divider as STC is only supported up to 90MHz */
    
    /* STC clock is now normal mode CPU clock frequency/2 = 180MHz/2 */
    systemREG2->STCCLKDIV = 0x01000000U;    
    
    /* Select one test interval, restart self-test next time, 0x00010001 */
    stcREG->STCGCR0 = 0x00010001U;                        
    
    /* Enable comparator self-check and stuck-at-0 fault insertion in CPU, 0x1A */
    stcREG->STCSCSCR = 0x1AU;                            
    
    /* Maximum time-out period */
    stcREG->STCTPR = 0xFFFFFFFFU;                        

    /* wait for 16 VBUS clock cycles at least, based on HCLK to VCLK ratio */
    for (i=0U; i<(16U + (16U * 0U)); i++){ /* Wait */ }                                

    /* Enable self-test */
    stcREG->STCGCR1 = 0xAU;                                    

/* USER CODE BEGIN (9) */
/* USER CODE END */
    
    /* Idle the CPU so that the self-test can start */
    _gotoCPUIdle_();

/* USER CODE BEGIN (10) */
/* USER CODE END */
}

/** @fn void cpuSelfTest(uint32 no_of_intervals, uint32 max_timeout, boolean restart_test)
*   @brief CPU self test Driver
*   @param[in] no_of_intervals - Number of Test Intervals to be 
*   @param[in] max_timeout     - Maximum Timeout to complete selected test Intervals
*   @param[in] restart_test    - Restart the test from Interval 0 or Continue from where it stopped.
*
*   This function is called to perform CPU self test using STC module.
*/
void cpuSelfTest(uint32 no_of_intervals, uint32 max_timeout, boolean restart_test)
{
    uint32 i = 0U;

/* USER CODE BEGIN (11) */
/* USER CODE END */
    
    /* Run specified no of test intervals starting from interval 0 */
    /* Start test from interval 0 or continue the test. */ 
    stcREG->STCGCR0 = (no_of_intervals << 16U)
                    | (uint32) restart_test;                        
    
    /* Configure Maximum time-out period */
    stcREG->STCTPR = max_timeout;                        
    
    /* wait for 16 VBUS clock cycles at least, based on HCLK to VCLK ratio */
    for (i=0U; i<(16U + (16U * 0U)); i++){ /* Wait */ }                                

    /* Enable self-test */
    stcREG->STCGCR1 = 0xAU;                                

/* USER CODE BEGIN (12) */
/* USER CODE END */
    /* Idle the CPU so that the self-test can start */
    
    _gotoCPUIdle_();
    
}

/** @fn void pbistSelfCheck(void)
*   @brief PBIST self test Driver
*
*   This function is called to perform PBIST self test.
*/
void pbistSelfCheck(void)
{
    uint32 i = 0U;
    uint32 PBIST_FSRF0, PBIST_FSRF1;
/* USER CODE BEGIN (13) */
/* USER CODE END */
    /* Run a diagnostic check on the memory self-test controller */
    /* First set up the PBIST ROM clock as this clock frequency is limited to 90MHz */
    
    /* PBIST ROM clock frequency = HCLK frequency /2 */
    /* Disable memory self controller */
    systemREG1->MSTGCR = 0x00000105U;                
    
    /* Disable Memory Initialization controller */
    systemREG1->MINITGCR = 0x5U;                            

    /* Enable PBIST controller */
    systemREG1->MSINENA = 0x1U;                            
    
    /* Enable memory self controller */
    systemREG1->MSTGCR = 0x0000010AU;                               
    
    /* wait for 32 VBUS clock cycles at least, based on HCLK to VCLK ratio */
    for (i=0U; i<(32U + (32U * 0U)); i++){ /* Wait */ }                                

/* USER CODE BEGIN (14) */
/* USER CODE END */
    
    /* Enable PBIST clocks and ROM clock */
    pbistREG->PACT = 0x3U;                                
    
    /* Select algo#3, march13n to be run */
    pbistREG->ALGO = 0x00000004U;                        
    
    /* Select RAM Group 1, which is actually the PBIST ROM */
    pbistREG->RINFOL = 0x1U;                                
    
    /* ROM contents will not override ALGO and RINFOx settings */
    pbistREG->OVER = 0x0U;                                
    
    /* Algorithm code is loaded from ROM */
    pbistREG->ROM = 0x3U;                                
    
    /* Start PBIST */
    pbistREG->DLR = 0x14U;                                
    
    /* wait until memory self-test done is indicated */
	/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while ((systemREG1->MSTCGSTAT & 0x1U) != 0x1U)
    { 
    }/* Wait */                 
    
    /* Check for the failure */
    PBIST_FSRF0 = pbistREG->FSRF0;
    PBIST_FSRF1 = pbistREG->FSRF1;
    if (((PBIST_FSRF0 & 0x1U) != 0x1U) && ((PBIST_FSRF1 & 0x1U) != 0x1U))
    {
        /* no failure was indicated even if the march13n algorithm was run on a ROM */
        selftestFailNotification(PBISTSELFCHECK_FAIL1);
        
/* USER CODE BEGIN (15) */
/* USER CODE END */
    }
    else                                                
    {
        /* PBIST self-check has passed */
        
        /* Disable PBIST clocks and ROM clock */
        pbistREG->PACT = 0x0U;                            
        
        /* Disable PBIST */
        systemREG1->MSTGCR &= ~(0xFU);                    
        systemREG1->MSTGCR |= 0x5U;
        
/* USER CODE BEGIN (16) */
/* USER CODE END */
    }
}

/** @fn void pbistRun(uint32 raminfoL, uint32 algomask)
*   @brief CPU self test Driver
*   @param[in] raminfoL   - Select the list of RAM to be tested.
*   @param[in] algomask   - Select the list of Algorithm to be run.
*
*   This function performs Memory Built-in Self test using PBIST module.
*/
void pbistRun(uint32 raminfoL, uint32 algomask)
{
    uint32 i = 0U;

/* USER CODE BEGIN (17) */
/* USER CODE END */

    /* PBIST ROM clock frequency = HCLK frequency /2 */
    /* Disable memory self controller */
    systemREG1->MSTGCR = 0x00000105U;                
    
    /* Disable Memory Initialization controller */
    systemREG1->MINITGCR = 0x5U;                            

    /* Enable PBIST controller */
    systemREG1->MSINENA = 0x1U;                            
    
    /* Enable memory self controller */
    systemREG1->MSTGCR = 0x0000010AU;
    
    /* wait for 32 VBUS clock cycles at least, based on HCLK to VCLK ratio */
    for (i=0U; i<(32U + (32U * 0U)); i++){ /* Wait */ }                             

/* USER CODE BEGIN (18) */
/* USER CODE END */
    
    /* Enable PBIST clocks and ROM clock */
    pbistREG->PACT = 0x3U;                                 
    
    /* Select all algorithms to be tested */
    pbistREG->ALGO = algomask;                             
    
    /* Select RAM groups */
    pbistREG->RINFOL = raminfoL;                         
    
    /* Select all RAM groups */
    pbistREG->RINFOU = 0x00000000U;                        
    
    /* ROM contents will not override RINFOx settings */
    pbistREG->OVER = 0x0U;                                 
    
    /* Algorithm code is loaded from ROM */
    pbistREG->ROM = 0x3U;                                 
    
    /* Start PBIST */
    pbistREG->DLR = 0x14U;                                 

/* USER CODE BEGIN (19) */
/* USER CODE END */
}

/** @fn void pbistStop(void)
*   @brief Routine to stop PBIST test enabled.
*
*   This function is called to stop PBIST after test is performed.
*/
void pbistStop(void)
{
/* USER CODE BEGIN (20) */
/* USER CODE END */
    /* disable pbist clocks and ROM clock */
    pbistREG->PACT = 0x0U;                            
    systemREG1->MSTGCR &= ~(0xFU);
    systemREG1->MSTGCR |= 0x5U;
/* USER CODE BEGIN (21) */
/* USER CODE END */
}

/** @fn boolean pbistIsTestCompleted(void)
*   @brief Checks to see if the PBIST test is completed.
*   @return 1 if PBIST test completed, otherwise 0.
*
*   Checks to see if the PBIST test is completed.
*/
boolean pbistIsTestCompleted(void)
{
/* USER CODE BEGIN (22) */
/* USER CODE END */

    return ((systemREG1->MSTCGSTAT & 0x1U) != 0U);
/* USER CODE BEGIN (23) */
/* USER CODE END */
}

/** @fn boolean pbistIsTestPassed(void)
*   @brief Checks to see if the PBIST test is completed successfully.
*   @return 1 if PBIST test passed, otherwise 0.
*
*   Checks to see if the PBIST test is completed successfully.
*/
boolean pbistIsTestPassed(void)
{
/* USER CODE BEGIN (24) */
/* USER CODE END */

    return (((pbistREG->FSRF0 ==0U) && (pbistREG->FSRF1 ==0U)) == TRUE);
/* USER CODE BEGIN (25) */
/* USER CODE END */
}

/** @fn boolean pbistPortTestStatus(uint32 port)
*   @brief Checks to see if the PBIST Port test is completed successfully.
*   @param[in] port   - Select the port to get the status.
*   @return 1 if PBIST Port test completed successfully, otherwise 0.
*
*   Checks to see if the selected PBIST Port test is completed successfully.
*/
boolean pbistPortTestStatus(uint32 port)
{
    boolean status;
/* USER CODE BEGIN (26) */
/* USER CODE END */

    if(port == PBIST_PORT0)
    {
      status =  ((boolean)pbistREG->FSRF0 == 0U);
    }
    else
    {
      status =  ((boolean)pbistREG->FSRF1 == 0U);    
    }
    
    return  status;
}

/** @fn void efcCheck(void)
*   @brief EFUSE module self check Driver
*
*   This function self checks the EFUSE module.
*/
void efcCheck(void)
{
    uint32 efcStatus = 0U;

/* USER CODE BEGIN (27) */
/* USER CODE END */
    
    /* read the EFC Error Status Register */
    efcStatus = efcREG->ERROR;                        

/* USER CODE BEGIN (28) */
/* USER CODE END */
    
    if (efcStatus == 0x0U)
    {
        /* run stuck-at-zero test and check if it passed */
        if (efcStuckZeroTest()== TRUE)                        
        {
            /* start EFC ECC logic self-test */
            efcSelfTest();                            
        }
        else
        {
            /* EFC output is stuck-at-zero, device operation unreliable */
            selftestFailNotification(EFCCHECK_FAIL1);
        }
    }
    /* EFC Error Register is not zero */
    else                                            
    {
        /* one-bit error detected during autoload */
        if (efcStatus == 0x15U)                        
        {
            /* start EFC ECC logic self-test */
            efcSelfTest();                            
        }
        else
        {
            /* Some other EFC error was detected */
            selftestFailNotification(EFCCHECK_FAIL1);                
        }
    }
}

/** @fn boolean efcStuckZeroTest(void)
*   @brief Checks to see if the EFUSE Stuck at zero test is completed successfully.
*   @return 1 if EFUSE Stuck at zero test completed, otherwise 0.
*
*   Checks to see if the EFUSE Stuck at zero test is completed successfully.
*/
boolean efcStuckZeroTest(void)
{
/* USER CODE BEGIN (29) */
/* USER CODE END */

    uint32 ESM_ESTATUS4, ESM_ESTATUS1;
    
    boolean result = FALSE;
      uint32 error_checks = EFC_INSTRUCTION_INFO_EN  | 
                                  EFC_INSTRUCTION_ERROR_EN | 
                                  EFC_AUTOLOAD_ERROR_EN      | 
                                  EFC_SELF_TEST_ERROR_EN   ;
    
    /* configure the output enable for auto load error , instruction info,
         instruction error, and self test error using boundary register 
         and drive values one across all the errors */
      efcREG->BOUNDARY = (OUTPUT_ENABLE | error_checks);
      
    /* Read from the pin register. This register holds the current values 
         of above errors. This value should be 0x5c00.If not at least one of
         the above errors is stuck at 0. */
    if ((efcREG->PINS & 0x5C00U) == 0x5C00U)
    {
        ESM_ESTATUS4 = esmREG->SR4[0U];
        ESM_ESTATUS1 = esmREG->SR1[2U];
        /* check if the ESM group1 channels 40 is set and group3 channel 2 is set */
        if (((ESM_ESTATUS4 & 0x200U) == 0x200U) & ((ESM_ESTATUS1 & 0x2U) == 0x2U))
        {
           /* stuck-at-zero test passed */
           result = TRUE;                                    
        }
    }
    
    /* put the pins back low */
    efcREG->BOUNDARY = OUTPUT_ENABLE;
    
    /* clear group1 flags */
    esmREG->SR4[0U] = 0x300U;
    
    /* clear group3 flag */
    esmREG->SR1[2U] = 0x2U;                    
    
    /* The nERROR pin will become inactive once the LTC counter expires */
    esmREG->EKR = 0x5U;                            

    return result;
}

/** @fn void efcSelfTest(void)
*   @brief EFUSE module self check Driver
*
*   This function self checks the EFSUE module.
*/
void efcSelfTest(void)
{
/* USER CODE BEGIN (30) */
/* USER CODE END */
    /* configure self-test cycles */
    efcREG->SELF_TEST_CYCLES = 0x258U;
    
    /* configure self-test signature */
    efcREG->SELF_TEST_SIGN = 0x5362F97FU;
    
    /* configure boundary register to start ECC self-test */
    efcREG->BOUNDARY = 0x0000200FU;
}

/** @fn boolean checkefcSelfTest(void)
*   @brief EFUSE module self check Driver
*
*   This function self checks the EFSUE module.
*/
boolean checkefcSelfTest(void)
{
/* USER CODE BEGIN (31) */
/* USER CODE END */
    boolean result = FALSE;
    
    uint32 EFC_PINS, EFC_ERROR;
    
    /* wait until EFC self-test is done */
	/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while((!(efcREG->PINS & EFC_SELF_TEST_DONE)) != 0U)
    { 
    }/* Wait */         
    
    /* check if EFC self-test error occurred */
    EFC_PINS = efcREG->PINS;
    EFC_ERROR = efcREG->ERROR;
    if (((!(EFC_PINS & EFC_SELF_TEST_ERROR)) & (!(EFC_ERROR & SELF_TEST_ERROR))) !=0U)
    {
        /* check if EFC self-test error is set */
        if ((esmREG->SR4[0U] & 0x100U) != 0x100U)        
        {
            result = TRUE;
        }
    }
    return result;
}

/** @fn void fmcBus2Check(void)
*   @brief Self Check Flash Bus2 Interface
*
*   This function self checks Flash Bus2 Interface
*/
void fmcBus2Check(void)
{
/* USER CODE BEGIN (32) */
/* USER CODE END */
    /* enable ECC logic inside FMC */
    flashWREG->FEDACCTRL1 = 0x000A060AU;        

    if ((esmREG->SR1[0U] & 0x40U) == 0x40U)
    {
        /* a 1-bit error was detected during flash OTP read by flash module
           run a self-check on ECC logic inside FMC */
        
        /* clear ESM group1 channel 6 flag */
        esmREG->SR1[0U] = 0x40U;    
        
        fmcECCcheck();
    }
    
    /* no 2-bit or 1-bit error detected during power-up */
    else                                        
    {
        fmcECCcheck();
    }
/* USER CODE BEGIN (33) */
/* USER CODE END */
}

/** @fn void fmcECCcheck(void)
*   @brief Check Flash ECC Single Bit and multi Bit errors detection logic.
*
*   This function Checks Flash ECC Single Bit and multi Bit errors detection logic.
*/
void fmcECCcheck(void)
{
    volatile uint32 otpread;
    volatile uint32 temp;

/* USER CODE BEGIN (34) */
/* USER CODE END */

    /* read location with deliberate 1-bit error */
    otpread = flash1bitError;                
    if ((esmREG->SR1[0U] & 0x40U) == 0x40U)
    {
        /* 1-bit failure was indicated and corrected */
        flashWREG->FEDACSTATUS = 0x00010006U;
        
        /* clear ESM group1 channel 6 flag */
        esmREG->SR1[0U] = 0x40U;            
        
        /* read location with deliberate 2-bit error */
        otpread = flash2bitError;            
        if ((esmREG->SR1[2U] & 0x80U) == 0x80U)
        {
            /* 2-bit failure was detected correctly */
            temp = flashWREG->FUNCERRADD;
            flashWREG->FEDACSTATUS = 0x00020100U;
            
            /* clear ESM group3 channel 7 */
            esmREG->SR1[2U] = 0x80U;        
            
            /* The nERROR pin will become inactive once the LTC counter expires */
            esmREG->EKR = 0x5U;                

        }
        else
        {
            /* ECC logic inside FMC cannot detect 2-bit error */
            selftestFailNotification(FMCECCCHECK_FAIL1);
        }
    }
    else
    {
        /* ECC logic inside FMC cannot detect 1-bit error */
        selftestFailNotification(FMCECCCHECK_FAIL1);
    }
/* USER CODE BEGIN (35) */
/* USER CODE END */
}

/** @fn void checkB0RAMECC(void)
*   @brief Check TCRAM1 ECC error detection logic.
*
*   This function checks TCRAM1 ECC error detection logic.
*/
void checkB0RAMECC(void)
{
    volatile uint32 ramread = 0U;
	uint64 tcramA1_bk = tcramA1bit;
	uint64 tcramA2_bk = tcramA2bit;
    uint32 i;
/* USER CODE BEGIN (36) */
/* USER CODE END */

    /* enable writes to ECC RAM, enable ECC error response */
    tcram1REG->RAMCTRL = 0x0005010AU;            
    tcram2REG->RAMCTRL = 0x0005010AU;

    /* the first 1-bit error will cause an error response */
    tcram1REG->RAMTHRESHOLD = 0x1U;                
    tcram2REG->RAMTHRESHOLD = 0x1U;

    /* allow SERR to be reported to ESM */
    tcram1REG->RAMINTCTRL = 0x1U;                
    tcram2REG->RAMINTCTRL = 0x1U;
    
    /* cause a 1-bit ECC error */
    tcramA1bitError ^= 0x1U;        
    
    /* disable writes to ECC RAM */
    tcram1REG->RAMCTRL = 0x0005000AU;            
    tcram2REG->RAMCTRL = 0x0005000AU;

    /* read from location with 1-bit ECC error */
    ramread = tcramA1bit;        
    
    /* SERR not set in TCRAM1 or TCRAM2 modules */
	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    if (!(((tcram1REG->RAMERRSTATUS & 1U) == 1U) || ((tcram2REG->RAMERRSTATUS & 1U) == 1U)))    
    {
        /* TCRAM module does not reflect 1-bit error reported by CPU */
        selftestFailNotification(CHECKB0RAMECC_FAIL1);
    }
    else
    {
        /* clear SERR flag */
        tcram1REG->RAMERRSTATUS = 0x1U;            
        tcram2REG->RAMERRSTATUS = 0x1U;
        
        /* clear status flags for ESM group1 channels 26 and 28 */
        esmREG->SR1[0U] = 0x14000000U;        
    }

    /* enable writes to ECC RAM, enable ECC error response */
    tcram1REG->RAMCTRL = 0x0005010AU;            
    tcram2REG->RAMCTRL = 0x0005010AU;

    /* cause a 2-bit ECC error */
    tcramA2bitError ^= 0x3U;

    /* read from location with 2-bit ECC error this will cause a data abort to be generated */
    ramread = tcramA2bit;

    /* delay before restoring the ram value */
    for(i=0U;i<10U;i++)
    { 
    }/* Wait */            
    
    ramread = tcram1REG->RAMUERRADDR;
    ramread = tcram2REG->RAMUERRADDR;

    /* disable writes to ECC RAM */
    tcram1REG->RAMCTRL = 0x0005000AU;
    tcram2REG->RAMCTRL = 0x0005000AU;

    /* Compute correct ECC */
    tcramA1bit = tcramA1_bk;
    tcramA2bit = tcramA2_bk;                    
    
/* USER CODE BEGIN (37) */
/* USER CODE END */
}

/** @fn void checkB1RAMECC(void)
*   @brief Check TCRAM2 ECC error detection logic.
*
*   This function checks TCRAM2 ECC error detection logic.
*/
void checkB1RAMECC(void)
{
    volatile uint32 ramread = 0U;
	uint64 tcramB1_bk = tcramB1bit;
	uint64 tcramB2_bk = tcramB2bit;
    uint32 i;
/* USER CODE BEGIN (38) */
/* USER CODE END */

    /* enable writes to ECC RAM, enable ECC error response */
    tcram1REG->RAMCTRL = 0x0005010AU;            
    tcram2REG->RAMCTRL = 0x0005010AU;
    
    /* the first 1-bit error will cause an error response */
    tcram1REG->RAMTHRESHOLD = 0x1U;                
    tcram2REG->RAMTHRESHOLD = 0x1U;

    /* allow SERR to be reported to ESM */
    tcram1REG->RAMINTCTRL = 0x1U;                 
    tcram2REG->RAMINTCTRL = 0x1U;

    /* cause a 1-bit ECC error */
    tcramB1bitError ^= 0x1U;                         
    
    /* disable writes to ECC RAM */
    tcram1REG->RAMCTRL = 0x0005000AU;             
    tcram2REG->RAMCTRL = 0x0005000AU;

    /* read from location with 1-bit ECC error */
    ramread = tcramB1bit;                         
    
    /* SERR not set in TCRAM1 or TCRAM2 modules */
	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    if (!(((tcram1REG->RAMERRSTATUS & 1U) == 1U) || ((tcram2REG->RAMERRSTATUS & 1U) == 1U)))    
    {
        /* TCRAM module does not reflect 1-bit error reported by CPU */
        selftestFailNotification(CHECKB1RAMECC_FAIL1);
    }
    else
    {
        /* clear SERR flag */
        tcram1REG->RAMERRSTATUS = 0x1U;             
        tcram2REG->RAMERRSTATUS = 0x1U;
        
        /* clear status flags for ESM group1 channels 26 and 28 */
        esmREG->SR1[0U] = 0x14000000U;         
    }

    /* enable writes to ECC RAM, enable ECC error response */
    tcram1REG->RAMCTRL = 0x0005010AU;             
    tcram2REG->RAMCTRL = 0x0005010AU;
    
    /* cause a 2-bit ECC error */
    tcramB2bitError ^= 0x3U;                         

    /* read from location with 2-bit ECC error this will cause a data abort to be generated */
    ramread = tcramB2bit;

    
    /* delay before restoring the ram value */
    for(i=0U;i<10U;i++)
    { 
    }/* Wait */            

    ramread = tcram1REG->RAMUERRADDR;
    ramread = tcram2REG->RAMUERRADDR;

    /* disable writes to ECC RAM */
    tcram1REG->RAMCTRL = 0x0005000AU;
    tcram2REG->RAMCTRL = 0x0005000AU;

    /* Compute correct ECC */
    tcramB1bit = tcramB1_bk;
    tcramB2bit = tcramB2_bk;    

/* USER CODE BEGIN (39) */
/* USER CODE END */
}

/** @fn void checkFlashECC(void)
*   @brief Check Flash ECC error detection logic.
*
*   This function checks Flash ECC error detection logic.
*/
void checkFlashECC(void)
{
    /* Routine to check operation of ECC logic inside CPU for accesses to program flash */
    volatile uint32 flashread = 0U;

/* USER CODE BEGIN (40) */
/* USER CODE END */
    
    /* Flash Module ECC Response enabled */
    flashWREG->FEDACCTRL1 = 0x000A060AU;            
    
    /* Enable diagnostic mode and select diag mode 7 */
    flashWREG->FDIAGCTRL = 0x00050007U;            
    
    /* Select ECC diagnostic mode, single-bit to be corrupted */
    flashWREG->FPAROVR = 0x00005A01U;            
    
    /* Set the trigger for the diagnostic mode */
    flashWREG->FDIAGCTRL |= 0x01000000U;            
    
    /* read a flash location from the mirrored memory map */
    flashread = flashBadECC;    
    
    /* disable diagnostic mode */
    flashWREG->FDIAGCTRL = 0x000A0007U;            

    /* this will have caused a single-bit error to be generated and corrected by CPU */
    /* single-bit error not captured in flash module */
	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    if ((flashWREG->FEDACSTATUS & 0x2U) == 0U)        
    {
        selftestFailNotification(CHECKFLASHECC_FAIL1);
    }
    else
    {
        /* clear single-bit error flag */
        flashWREG->FEDACSTATUS = 0x2U;                

        /* clear ESM flag */
        esmREG->SR1[0U] = 0x40U;                    

        /* Enable diagnostic mode and select diag mode 7 */
        flashWREG->FDIAGCTRL = 0x00050007U;            
        
        /* Select ECC diagnostic mode, two bits of ECC to be corrupted */
        flashWREG->FPAROVR = 0x00005A03U;            
        
        /* Set the trigger for the diagnostic mode */
        flashWREG->FDIAGCTRL |= 0x01000000U;            

        /* read from flash location from mirrored memory map this will cause a data abort */
        flashread = flashBadECC;

        /* Read FUNCERRADD register */
        flashread = flashWREG->FUNCERRADD;

        /* disable diagnostic mode */
        flashWREG->FDIAGCTRL = 0x000A0007U;            
    }

/* USER CODE BEGIN (41) */
/* USER CODE END */
}

/** @fn void custom_dabort(void)
*   @brief Custom Data abort routine for the application.
*
*   Custom Data abort routine for the application.
*/
void custom_dabort(void)
{
    /* Need custom data abort handler here.
     * This data abort is not caused due to diagnostic checks of flash and TCRAM ECC logic.
     */
/* USER CODE BEGIN (42) */
/* USER CODE END */
}

/** @fn void stcSelfCheckFail(void)
*   @brief STC Self test check fail service routine
*
*   This function is called if STC Self test check fail.
*/
void stcSelfCheckFail(void)
{
/* USER CODE BEGIN (43) */
/* USER CODE END */
    /* CPU self-test controller's own self-test failed.
     * It is not possible to verify that STC is capable of indicating a CPU self-test error.
     * It is not recommended to continue operation.
     */
     
    /* User can add small piece of code to take system to Safe state using user code section.
     * Note: Just removing the for(;;) will take the system to unknown state under ST failure,
     * since it is not handled by HALCoGen driver */
/* USER CODE BEGIN (44) */
/* USER CODE END */
    /*SAFETYMCUSW 5 C MR:NA <APPROVED> "for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below" */
    /*SAFETYMCUSW 26 S MR:NA <APPROVED> "for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below" */
	/*SAFETYMCUSW 28 D MR:NA <APPROVED> "for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below" */
    for(;;)
    { 
    }/* Wait */         
/* USER CODE BEGIN (45) */
/* USER CODE END */
}

/** @fn void cpuSelfTestFail(void)
*   @brief CPU Self test check fail service routine
*
*   This function is called if CPU Self test check fail.
*/
void cpuSelfTestFail(void)
{
/* USER CODE BEGIN (46) */
/* USER CODE END */
    /* CPU self-test has failed.
     * CPU operation is not reliable.
     */
/* USER CODE BEGIN (47) */
/* USER CODE END */
    /*SAFETYMCUSW 5 C MR:NA <APPROVED> "for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below" */
    /*SAFETYMCUSW 26 S MR:NA <APPROVED> "for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below" */
	/*SAFETYMCUSW 28 D MR:NA <APPROVED> "for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below" */
    for(;;)
    { 
    }/* Wait */         
/* USER CODE BEGIN (48) */
/* USER CODE END */
}


/** @fn void vimParityCheck(void)
*   @brief Routine to check VIM RAM parity error detection and signaling mechanism
*
*   Routine to check VIM RAM parity error detection and signaling mechanism
*/
void vimParityCheck(void)
{
    volatile uint32 vimramread = 0U;

/* USER CODE BEGIN (49) */
/* USER CODE END */
    
    /* Enable parity checking and parity test mode */
    VIM_PARCTL = 0x0000010AU;
    
    /* flip a bit in the VIM RAM parity location */
    VIMRAMPARLOC ^= 0x1U;                    
    
    /* disable parity test mode */
    VIM_PARCTL = 0x0000000AU;                

    /* cause parity error */
    vimramread = VIMRAMLOC;                    
   
    /* check if ESM group1 channel 15 is flagged */
    if ((!(esmREG->SR1[0U] & 0x8000U))    !=0U)
    {
        /* VIM RAM parity error was not flagged to ESM. */
        selftestFailNotification(VIMPARITYCHECK_FAIL1);
    }
    else
    {
        /* clear VIM RAM parity error flag in VIM */
        VIM_PARFLG = 0x1U;                    
        
        /* clear ESM group1 channel 15 flag */
        esmREG->SR1[0U] = 0x8000U;        
        
        /* Enable parity checking and parity test mode */
        VIM_PARCTL = 0x0000010AU;
    
        /* Revert back to correct data, flip bit 0 of the parity location */
        VIMRAMPARLOC ^= 0x1U;                    
    
        /* disable parity test mode */
        VIM_PARCTL = 0x0000000AU;        
    }
/* USER CODE BEGIN (50) */
/* USER CODE END */
}

/** @fn void het1ParityCheck(void)
*   @brief Routine to check HET1 RAM parity error detection and signaling mechanism
*
*   Routine to check HET1 RAM parity error detection and signaling mechanism
*/
void het1ParityCheck(void)
{
    volatile uint32 nhetread = 0U;

/* USER CODE BEGIN (53) */
/* USER CODE END */
    
    /* Set TEST mode and enable parity checking */
    hetREG1->PCR = 0x0000010AU;            
    
    /* flip parity bit */
    NHET1RAMPARLOC ^= 0x1U;                    
    
    /* Disable TEST mode */
    hetREG1->PCR = 0x0000000AU;            

    /* read to cause parity error */
    nhetread = NHET1RAMLOC;                    

    /* check if ESM group1 channel 7 is flagged */
    if ((!(esmREG->SR1[0U] & 0x80U)) !=0U)
    {
        /* NHET1 RAM parity error was not flagged to ESM. */
        selftestFailNotification(HET1PARITYCHECK_FAIL1);
    }
    else
    {
        /* clear ESM group1 channel 7 flag */
        esmREG->SR1[0U] = 0x80U;    

        /* Set TEST mode and enable parity checking */
        hetREG1->PCR = 0x0000010AU;            
    
        /* Revert back to correct data, flip bit 0 of the parity location */
        NHET1RAMPARLOC ^= 0x1U;                    
    
        /* Disable TEST mode */
        hetREG1->PCR = 0x0000000AU;            
    }
/* USER CODE BEGIN (54) */
/* USER CODE END */
}

/** @fn void htu1ParityCheck(void)
*   @brief Routine to check HTU1 RAM parity error detection and signaling mechanism
*
*   Routine to check HTU1 RAM parity error detection and signaling mechanism
*/
void htu1ParityCheck(void)
{
    volatile uint32 hturead = 0U;

/* USER CODE BEGIN (55) */
/* USER CODE END */

    /* Enable parity and TEST mode */
    htuREG1->PCR = 0x0000010AU;    
    
    /* flip parity bit */    
    HTU1PARLOC ^= 0x1U;            
    
    /* Disable parity RAM test mode */
    htuREG1->PCR = 0x0000000AU;    
    
    /* read to cause parity error */
    hturead = HTU1RAMLOC;        
   
    /* check if ESM group1 channel 8 is flagged */
    if ((!(esmREG->SR1[0U] & 0x100U)) != 0U)         
    {
        /* HTU1 RAM parity error was not flagged to ESM. */
        selftestFailNotification(HTU1PARITYCHECK_FAIL1);
    }
    else
    {
        /* Clear HTU parity error flag */
        htuREG1->PAR = 0x00010000U;            
        esmREG->SR1[0U] = 0x100U;

        /* Enable parity and TEST mode */
        htuREG1->PCR = 0x0000010AU;    
    
        /* Revert back to correct data, flip bit 0 of the parity location */
        HTU1PARLOC ^= 0x1U;            
    
        /* Disable parity RAM test mode */
        htuREG1->PCR = 0x0000000AU;    
        
    }

/* USER CODE BEGIN (56) */
/* USER CODE END */

}

/** @fn void adc1ParityCheck(void)
*   @brief Routine to check ADC1 RAM parity error detection and signaling mechanism
*
*   Routine to check ADC1 RAM parity error detection and signaling mechanism
*/
void adc1ParityCheck(void)
{
    volatile uint32 adcramread = 0U;

/* USER CODE BEGIN (61) */
/* USER CODE END */
    
    /* Set the TEST bit in the PARCR and enable parity checking */
    adcREG1->PARCR = 0x10AU;                
    
    /* Invert the parity bits inside the ADC1 RAM's first location */
    adcPARRAM1 = ~(adcPARRAM1);                

    /* clear the TEST bit */
    adcREG1->PARCR = 0x00AU;                

    /* This read is expected to trigger a parity error */
    adcramread = adcRAM1;                    

    /* Check for ESM group1 channel 19 to be flagged */
    if ((!(esmREG->SR1[0U] & 0x80000U)) !=0U)    
    {
        /* no ADC1 RAM parity error was flagged to ESM */
        selftestFailNotification(ADC1PARITYCHECK_FAIL1);
    }
    else
    {
        /* clear ADC1 RAM parity error flag */
        esmREG->SR1[0U] = 0x80000U;    

        /* Set the TEST bit in the PARCR and enable parity checking */
        adcREG1->PARCR = 0x10AU;                
    
        /* Revert back the parity bits to correct data */
        adcPARRAM1 = ~(adcPARRAM1);                

        /* clear the TEST bit */
        adcREG1->PARCR = 0x00AU;            
    }
    
/* USER CODE BEGIN (62) */
/* USER CODE END */
}

/** @fn void can1ParityCheck(void)
*   @brief Routine to check CAN1 RAM parity error detection and signaling mechanism
*
*   Routine to check CAN1 RAM parity error detection and signaling mechanism
*/
void can1ParityCheck(void)
{
    volatile uint32 canread = 0U;

/* USER CODE BEGIN (65) */
/* USER CODE END */
    
    /* Disable parity, init mode, TEST mode */
    canREG1->CTL = 0x00001481U;                
    
    /* Enable RAM Direct Access mode */
    canREG1->TEST = 0x00000200U;            

    /* flip the parity bit */
    canPARRAM1 ^= 0x00001000U;                

    /* Enable parity, disable init, still TEST mode */
    canREG1->CTL = 0x00002880U;                

    /* Read location with parity error */
    canread = canRAM1;                    

    /* check if ESM group1 channel 21 is flagged */
    if ((!(esmREG->SR1[0U] & 0x00200000U))    != 0U)
    {
        /* No DCAN1 RAM parity error was flagged to ESM */
        selftestFailNotification(CAN1PARITYCHECK_FAIL1);
    }
    else
    {
        /* clear ESM group1 channel 21 flag */
        esmREG->SR1[0U] = 0x00200000U;    
        
        /* Disable parity, init mode, TEST mode */
        canREG1->CTL = 0x00001481U;

        /* Revert back to correct data, flip bit 0 of the parity location */
        canPARRAM1 ^= 0x00001000U;

        /* Disable RAM Direct Access mode */
        canREG1->TEST = 0x00000000U;
        
        /* disable TEST mode */
        canREG1->CTL = 0x00002800U;        

        /* Read Error and Status register to clear Parity Error bit */
        canread = canREG1->ES;        
    }
    
/* USER CODE BEGIN (66) */
/* USER CODE END */
}

/** @fn void can2ParityCheck(void)
*   @brief Routine to check CAN2 RAM parity error detection and signaling mechanism
*
*   Routine to check CAN2 RAM parity error detection and signaling mechanism
*/
void can2ParityCheck(void)
{
    volatile uint32 canread = 0U;

/* USER CODE BEGIN (67) */
/* USER CODE END */
    
    /* Disable parity, init mode, TEST mode */
    canREG2->CTL = 0x00001481U;            

    /* Enable RAM Direct Access mode */    
    canREG2->TEST = 0x00000200U;            

    /* flip the parity bit */
    canPARRAM2 ^= 0x00001000U;                

    /* Enable parity, disable init, still TEST mode */
    canREG2->CTL = 0x00002880U;                

    /* Read location with parity error */
    canread = canRAM2;                    
    
    /* check if ESM group1 channel 23 is flagged */
    if ((!(esmREG->SR1[0U] & 0x00800000U)) != 0U)    
    {
        /* No DCAN2 RAM parity error was flagged to ESM */
        selftestFailNotification(CAN2PARITYCHECK_FAIL1);
    }
    else
    {
        /* clear ESM group1 channel 23 flag */
        esmREG->SR1[0U] = 0x00800000U;    

        /* Disable parity, init mode, TEST mode */
        canREG2->CTL = 0x00001481U;            

        /* Revert back to correct data, flip bit 0 of the parity location */
        canPARRAM2 ^= 0x00001000U;                

        /* Disable RAM Direct Access mode */    
        canREG2->TEST = 0x00000000U;            
        
        /* disable TEST mode */
        canREG2->CTL = 0x00002800U;    

        /* Read Error and Status register to clear Parity Error bit */
        canread = canREG2->ES;    
    }
    
/* USER CODE BEGIN (68) */
/* USER CODE END */
}

/** @fn void mibspi1ParityCheck(void)
*   @brief Routine to check MIBSPI1 RAM parity error detection and signaling mechanism
*
*   Routine to check MIBSPI1 RAM parity error detection and signaling mechanism
*/
void mibspi1ParityCheck(void)
{
    volatile uint32 spiread = 0U;

/* USER CODE BEGIN (71) */
/* USER CODE END */

    /* enable multi-buffered mode */
    mibspiREG1->MIBSPIE = 0x1U;                

    /* enable parity error detection */
    mibspiREG1->UERRCTRL = (mibspiREG1->UERRCTRL & 0xFFFFFFF0U) | (0xAU);
    
    /* enable parity test mode */
    mibspiREG1->UERRCTRL |= 1U << 8U;                
    
    /* flip bit 0 of the parity location */
    mibspiPARRAM1 ^= 0x1U;                    

    /* disable parity test mode */
    mibspiREG1->UERRCTRL &= ~(1U << 8U);                

    /* read from MibSPI1 RAM to cause parity error */
	/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "32-bit read from the RAM location" */
	spiread = *(uint32 *)mibspiRAM1;	

    /* check if ESM group1 channel 17 is flagged */
    if ((!(esmREG->SR1[0U] & 0x20000U))    != 0U)
    {
        /* No MibSPI1 RAM parity error was flagged to ESM. */
        selftestFailNotification(MIBSPI1PARITYCHECK_FAIL1);
    }
    else
    {
        /* clear parity error flags */
        mibspiREG1->UERRSTAT = 0x3U;            
        
        /* clear ESM group1 channel 17 flag */
        esmREG->SR1[0U] = 0x20000U;        
        
        /* enable parity test mode */
        mibspiREG1->UERRCTRL |= 1U << 8U;            
        
        /* Revert back to correct data, flip bit 0 of the parity location */
        mibspiPARRAM1 ^= 0x1U;                
        
        /* disable parity test mode */
        mibspiREG1->UERRCTRL &= ~(1U << 8U);    

        /* revert multi-buffered mode */
        mibspiREG1->MIBSPIE = 0x0U;            
    }

/* USER CODE BEGIN (72) */
/* USER CODE END */
}

/** @fn void checkRAMECC(void)
*   @brief Check TCRAM ECC error detection logic.
*
*   This function checks TCRAM ECC error detection logic.
*/
void checkRAMECC(void)
{
    volatile uint64 ramread = 0U;
	uint64 tcramA1_bk = tcramA1bit;
	uint64 tcramB1_bk = tcramB1bit;
	uint64 tcramA2_bk = tcramA2bit;
	uint64 tcramB2_bk = tcramB2bit;

    /* Clear RAMOCUUR before setting RAMTHRESHOLD register */
    tcram1REG->RAMOCCUR = 0U;
    tcram2REG->RAMOCCUR = 0U;

    /* Set Single-bit Error Threshold Count as 1 */
    tcram1REG->RAMTHRESHOLD = 1U;
    tcram2REG->RAMTHRESHOLD = 1U;

    /* Enable single bit error generation */
    tcram1REG->RAMINTCTRL = 1U;
    tcram2REG->RAMINTCTRL = 1U;

    /* Enable writes to ECC RAM, enable ECC error response */
    tcram1REG->RAMCTRL = 0x0005010AU;
    tcram2REG->RAMCTRL = 0x0005010AU;

    /* Force a single bit error in both the banks */
    tcramA1bitError ^= 1U;
    tcramB1bitError ^= 1U;

    /* Read the corrupted data to generate single bit error */
    ramread = tcramA1bit;
    ramread = tcramB1bit;

	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    if(!(((tcram1REG->RAMERRSTATUS & 0x1U) == 0x1U) && ((tcram1REG->RAMERRSTATUS & 0x1U) == 0x1U)))
    {
        /* TCRAM module does not reflect 1-bit error reported by CPU */
        selftestFailNotification(CHECKRAMECC_FAIL1);
    }
    else
    {
        if((esmREG->SR1[0U] & 0x14000000U) != 0x14000000U)
        {
            /* TCRAM 1-bit error not flagged in ESM */
            selftestFailNotification(CHECKRAMECC_FAIL2);
        }
        else
        {
            /* Clear single bit error flag in TCRAM module */
            tcram1REG->RAMERRSTATUS = 0x1U;
            tcram2REG->RAMERRSTATUS = 0x1U;

            /* Clear ESM status */
            esmREG->SR1[0U] = 0x14000000U;
        }
    }

    /* Force a double bit error in both the banks */
    tcramA2bitError ^= 3U;
    tcramB2bitError ^= 3U;

    /* Read the corrupted data to generate single bit error */
    ramread = tcramA2bit;
    ramread = tcramB2bit;

    ramread = tcram1REG->RAMUERRADDR;
    ramread = tcram2REG->RAMUERRADDR;

    /* disable writes to ECC RAM */
    tcram1REG->RAMCTRL = 0x0005000AU;
    tcram2REG->RAMCTRL = 0x0005000AU;

    /* Compute correct ECC */
    tcramA1bit = tcramA1_bk;
    tcramB1bit = tcramB1_bk;
    tcramA2bit = tcramA2_bk;
    tcramB2bit = tcramB2_bk;
}

/** @fn void checkClockMonitor(void)
*   @brief Check clock monitor failure detection logic.
*
*   This function checks clock monitor failure detection logic.
*/
void checkClockMonitor(void)
{
    systemREG1->CLKTEST |= 0x03000000U;

    /* Switch all clock domains from the oscillator to the HF LPO */
    systemREG1->GHVSRC = 0x05050005U;

    /* Disable oscillator to cause a oscillator fail */
    systemREG1->CSDISSET = 0x1U;

    /* Wait till oscillator fail flag is set */
	/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while((systemREG1->GBLSTAT & 0x1U) == 0U)
    {
    } /* Wait */

    if(esmREG->SR1[0U] != 0x800U)
    {
        selftestFailNotification(CHECKCLOCKMONITOR_FAIL1);
    }
    else
    {
        /* Clear ESM flag */
        esmREG->SR1[0U] = 0x800U;

        systemREG1->CLKTEST &= ~(0x03000000U);

        /* Enable oscillator */
        systemREG1->CSDISCLR = 0x1U;

        /* Wait until oscillator is enabled */
		/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
        while((systemREG1->CSVSTAT & 0x3U) == 0U)
        {
        } /* Wait */

        /* Clear oscillator fail flag and PLL slip flag if any*/
        systemREG1->GBLSTAT = 0x301U;

        /* Switch all clock domains from the oscillator to PLL */
        systemREG1->GHVSRC = 0x01010001U;
    }
}

/** @fn void checkFlashEEPROMECC(void)
*   @brief Check Flash EEPROM ECC error detection logic.
*
*   This function checks Flash EEPROM ECC error detection logic.
*/
void checkFlashEEPROMECC(void)
{
    uint8 ecc;

    /* Set Single Error Correction Threshold as 1 */
    flashWREG->EECTRL2 |= 1U;

    /* Enable EEPROM Emulation Error Profiling */
    flashWREG->EECTRL1 |= 1U << 8U;

    /* Load FEMU_XX regs in order to generate ECC */
    flashWREG->FEMUADDR = 0xF0200000U;
    flashWREG->FEMUDMSW = 0U;
    flashWREG->FEMUDLSW = 0U;

    /* ECC for the correct data*/
    ecc = flashWREG->FEMUECC;

    /* Load data with 1 bit error */
    flashWREG->FEMUDMSW = 0U;
    flashWREG->FEMUDLSW = 1U;

    /* Enable Diagnostic ECC data correction mode and select FEE SECDED for diagnostic testing */
    flashWREG->FDIAGCTRL = 0x00055001U;

    flashWREG->FEMUECC = ecc;

    /* Diagnostic trigger */
    flashWREG->FDIAGCTRL |= 1U << 24U;

	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    if((flashWREG->EESTATUS & 0x1U) != 0x1U)
    {
        /* No single bit error was detected */
        selftestFailNotification(CHECKFLASHEEPROMECC_FAIL1);
    }
    else
    {
        if((esmREG->SR4[0U] & 0x8U) != 0x8U)
        {
            /* EEPROM single bit error not captured in ESM */
            selftestFailNotification(CHECKFLASHEEPROMECC_FAIL2);
        }
        else
        {
            /* Clear single bit error flag in flash wrapper */
            flashWREG->EESTATUS = 0xFU;

            /* Clear ESM flag */
            esmREG->SR4[0U] = 0x8U;
        }
    }

    /* Load data with 2 bit error */
    flashWREG->FEMUDMSW = 0U;
    flashWREG->FEMUDLSW = 3U;

    /* Enable Diagnostic ECC data correction mode and select FEE SECDED for diagnostic testing */
    flashWREG->FDIAGCTRL = 0x00055001U;

    flashWREG->FEMUECC = ecc;

    /* Diagnostic trigger */
    flashWREG->FDIAGCTRL |= 1U << 24U;

	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    if((flashWREG->EESTATUS & 0x100U) != 0x100U)
    {
        /* No double bit error was detected */
        selftestFailNotification(CHECKFLASHEEPROMECC_FAIL3);
    }
    else
    {
        if((esmREG->SR4[0U] & 0x10U) != 0x10U)
        {
            /* EEPROM double bit error not captured in ESM */
            selftestFailNotification(CHECKFLASHEEPROMECC_FAIL4);
        }
        else
        {
            /* Clear uncorrectable error flag in flash wrapper */
            flashWREG->EESTATUS = 0x1100U;

            /* Read EEUNCERRADD register */
            /*SAFETYMCUSW 57 S MR:14.2 <APPROVED> "EEUNCERRADD is read clear register" */
            flashWREG->EEUNCERRADD;

            /* Clear ESM flag */
            esmREG->SR4[0U] = 0x10U;


        }
    }
}


/** @fn void checkPLL1Slip(void)
*   @brief Check PLL1 Slip detection logic.
*
*   This function checks PLL1 Slip detection logic.
*/
void checkPLL1Slip(void)
{
    uint32 ghvsrc_bk, pllctl1_bk;

    /* Back up the the registers GHVSRC and PLLCTRL1 */
    ghvsrc_bk = systemREG1->GHVSRC;
    pllctl1_bk = systemREG1->PLLCTL1;

    /* Disable Reset on PLL Slip and enable Bypass on PLL slip */
    systemREG1->PLLCTL1 &= 0x1FFFFFFFU;

    /* Force a PLL Slip */
    systemREG1->PLLCTL1 ^= 0x8000U;

    /* Wait till PLL slip flag is set */
	/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while((systemREG1->GBLSTAT & 0x300U) == 0U)
    {
    } /* Wait */

    if((esmREG->SR1[0U] & 0x400U) != 0x400U)
    {
        /* ESM flag not set */
        selftestFailNotification(CHECKPLL1SLIP_FAIL1);
    }
    else
    {
        /* Switch all clock domains to oscillator */
        systemREG1->GHVSRC = 0x00000000U;

        /* Disable PLL1 */
        systemREG1->CSDISSET = 0x2U;

        /* Wait till PLL1 is disabled */
		/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
        while((systemREG1->CSDIS & 0x2U) == 0U)
        {
        } /* Wait */

        /* Restore the PLL multiplier value */
        systemREG1->PLLCTL1 = pllctl1_bk;

        /* Enable PLL1 */
        systemREG1->CSDISCLR = 0x2U;

        /* Wait till PLL1 is disabled */
		/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
        while((systemREG1->CSDIS & 0x2U) != 0U)
        {
        } /* Wait */

        /* Switch back to the initial clock source */
        systemREG1->GHVSRC = ghvsrc_bk;

        /* Clear PLL slip flag */
        systemREG1->GBLSTAT = 0x300U;

        /* Clear ESM flag */
        esmREG->SR1[0U] = 0x400U;
    }
}

/** @fn void checkPLL2Slip(void)
*   @brief Check PLL2 Slip detection logic.
*
*   This function checks PLL2 Slip detection logic.
*/
void checkPLL2Slip(void)
{
    uint32 ghvsrc_bk;

    /* Back up the the register GHVSRC */
    ghvsrc_bk = systemREG1->GHVSRC;

    /* Force a PLL2 Slip */
    systemREG2->PLLCTL3 ^= 0x8000U;

	/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while((esmREG->SR4[0U] & 0x400U) != 0x400U)
    {
        /* Wait till ESM flag is set */
    }

    /* Switch all clock domains to oscillator */
    systemREG1->GHVSRC = 0x00000000U;

    /* Disable PLL2 */
    systemREG1->CSDISSET = 0x40U;

    /* Wait till PLL2 is disabled */
	/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while((systemREG1->CSDIS & 0x40U) == 0U)
    {
    } /* Wait */

    /* Restore the PLL 2 multiplier value */
    systemREG2->PLLCTL3 ^= 0x8000U;

    /* Enable PLL2 */
    systemREG1->CSDISCLR = 0x40U;

    /* Wait till PLL2 is disabled */
	/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while((systemREG1->CSDIS & 0x40U) != 0U)
    {
    } /* Wait */

    /* Switch back to the initial clock source */
    systemREG1->GHVSRC = ghvsrc_bk;

    /* Clear PLL slip flag */
    systemREG1->GBLSTAT = 0x300U;

    /* Clear ESM flag */
    esmREG->SR4[0U] = 0x400U;
}

/** @fn void checkRAMAddrParity(void)
*   @brief Check TCRAM Address parity error detection and signaling mechanism.
*
*   This function TCRAM Address parity error detection and signaling mechanism.
*/
void checkRAMAddrParity(void)
{
    /* Invert Address parity scheme */
    tcram1REG->RAMCTRL = 0x0D05000AU;
    tcram2REG->RAMCTRL = 0x0D05000AU;

    /* Read from both RAM banks */
    tcramA1bit;
    tcramB1bit;

    /* Switch back to Address parity scheme */
    tcram1REG->RAMCTRL = 0x0005000AU;
    tcram2REG->RAMCTRL = 0x0005000AU;

	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    if(((tcram1REG->RAMERRSTATUS & 0x100U) == 0U) || ((tcram2REG->RAMERRSTATUS & 0x100U) == 0U))
    {
        /* No Address parity error detected */
        selftestFailNotification(CHECKRAMADDRPARITY_FAIL1);
    }
    else
    {
        if((esmREG->SR1[1U] & 0x1400U) != 0x1400U)
        {
            /* Address parity error not reported to ESM */
            selftestFailNotification(CHECKRAMADDRPARITY_FAIL2);
        }
        else
        {
            /* Clear Address parity error flag */
            tcram1REG->RAMERRSTATUS = 0x300U;
            tcram2REG->RAMERRSTATUS = 0x300U;

            /* Clear ESM flag */
            esmREG->SR1[1U] = 0x1400U;

            /* The nERROR pin will become inactive once the LTC counter expires */
            esmREG->EKR = 0x5U;

            /*SAFETYMCUSW 57 S MR:14.2 <APPROVED> "RAMPERADDR is read clear register" */
            tcram1REG->RAMPERADDR;
            /*SAFETYMCUSW 57 S MR:14.2 <APPROVED> "RAMPERADDR is read clear register" */
            tcram2REG->RAMPERADDR;
        }
    }
}

/** @fn void checkRAMUERRTest(void)
*   @brief Run RAM test
*
*   This function runs RAM test to test the redundant address decode and compare logic.
*/
void checkRAMUERRTest(void)
{
    /* Trigger equality check */
    tcram1REG->RAMTEST = 0x018AU;
    tcram2REG->RAMTEST = 0x018AU;

    /* Wait till test is completed */
	/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while(!((tcram1REG->RAMTEST == 0x008AU) && (tcram1REG->RAMTEST == 0x008AU)))
    {
    } /* Wait */

	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    if(((tcram1REG->RAMERRSTATUS & 0x10U) == 0x10U) || ((tcram1REG->RAMERRSTATUS & 0x10U) == 0x10U))
    {
        /* test failed */
        selftestFailNotification(CHECKRAMUERRTEST_FAIL1);
    }

    /* Trigger inequality check */
    tcram1REG->RAMTEST = 0x014AU;
    tcram2REG->RAMTEST = 0x014AU;

    /* Wait till test is completed */
	/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while(!((tcram1REG->RAMTEST == 0x004AU) && (tcram1REG->RAMTEST == 0x004AU)))
	{
	}/* Wait */

	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    if(((tcram1REG->RAMERRSTATUS & 0x10U) == 0x10U) || ((tcram1REG->RAMERRSTATUS & 0x10U) == 0x10U))
    {
        /* test failed */
        selftestFailNotification(CHECKRAMUERRTEST_FAIL2);
    }
    else
    {
        tcram1REG->RAMERRSTATUS = 0x4U;
        tcram2REG->RAMERRSTATUS = 0x4U;

		/* Clear ESM flag */
        esmREG->SR1[1U] = 0x140U;
        esmREG->SSR2 = 0x140U;
        esmREG->EKR = 0x5U;
    }
    
    /* Disable RAM test mode */
    tcram2REG->RAMTEST = 0x5U;
}

void fmcBus1ParityCheck(void)
{
	uint32 regBkupFparOvr,regBckupFdiagctrl;
	volatile uint32 flashread = 0U;

	/* Backup registers */
	regBkupFparOvr = flashWREG->FPAROVR;
	regBckupFdiagctrl = flashWREG->FDIAGCTRL;

	/* Read to unfreeze the error address registers */
	flashread = flashWREG->FUNCERRADD;

	/* clear status register */
	flashWREG->FEDACSTATUS = 0x400U;

	/* Enable Parity Error */
	flashWREG->FPAROVR  = (0x5U << 9U)|(0x5U << 12U);

	/* set Diag test mode */
	flashWREG->FDIAGCTRL = 0x00050000U | 0x00000007U;

	/* Add parity */
	flashWREG->FPAROVR |= 1U << 8U;

	/* Start Test */
	flashWREG->FDIAGCTRL |= 0x1000000U;

	/* Wait until test done */
	/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
	while((flashWREG->FDIAGCTRL & 0x1000000U) == 0x1000000U)
	{
	}/* Wait */

	/* Check address Error */
	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
	if((flashWREG->FEDACSTATUS & 0x400U) != 0x400U)
	{
	    selftestFailNotification(FMCBUS1PARITYCHECK_FAIL1);
	}
	else
	{
        /* clear status register */
		flashWREG->FEDACSTATUS = 0x400U;

		/* check if ESM is flagged */
		/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
		if((esmREG->SR1[1U] & 0x0000010U) == 0U)
		{
		    selftestFailNotification(FMCBUS1PARITYCHECK_FAIL2);
		}
		else
		{
			/* clear ESM flag */
			esmREG->SR1[1U] |= 0x0000010U;
			esmREG->SSR2 |= 0x0000010U;
			esmREG->EKR = 0x5U;

			/* Stop Diag test mode */
			flashWREG->FDIAGCTRL = regBckupFdiagctrl;
			flashWREG->FPAROVR	 = regBkupFparOvr;
		}
	}

	/* Read to unfreeze the error address registers */
	flashread = flashWREG->FUNCERRADD;
}


void pbistFail(void)
{
    uint32 PBIST_RAMT, PBIST_FSRA0, PBIST_FSRDL0, PBIST_FSRA1, PBIST_FSRDL1;
	/*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "Hardware status bit read check" */
    PBIST_RAMT = pbistREG->RAMT;
    PBIST_FSRA0 = pbistREG->FSRA0;
    PBIST_FSRDL0 = pbistREG->FSRDL0;
    PBIST_FSRA1 = pbistREG->FSRA1;
    PBIST_FSRDL1 = pbistREG->FSRDL1;
    
    if(pbistPortTestStatus((uint32)PBIST_PORT0) != TRUE)
    {
        memoryPort0TestFailNotification((uint32)((PBIST_RAMT & 0xFF000000U) >> 24U), (uint32)((PBIST_RAMT & 0x00FF0000U) >> 16U),(uint32)PBIST_FSRA0, (uint32)PBIST_FSRDL0);
    }
    else if(pbistPortTestStatus((uint32)PBIST_PORT1) != TRUE)
    {
        memoryPort1TestFailNotification((uint32)((PBIST_RAMT & 0xFF000000U) >> 24U), (uint32)((PBIST_RAMT & 0x00FF0000U) >> 16U), (uint32)PBIST_FSRA1, (uint32)PBIST_FSRDL1);
    }
    else
    {
/* USER CODE BEGIN (77) */
/* USER CODE END */
/*SAFETYMCUSW 5 C MR:NA <APPROVED> "for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below" */
/*SAFETYMCUSW 26 S MR:NA <APPROVED> "for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below" */
/*SAFETYMCUSW 28 D MR:NA <APPROVED> "for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below" */
        for(;;)
        { 
        }/* Wait */                 

/* USER CODE BEGIN (78) */
/* USER CODE END */
    }
}

/** @fn void pbistGetConfigValue(pbist_config_reg_t *config_reg, config_value_type_t type)
*   @brief Get the initial or current values of the configuration registers
*
*    @param[in] *config_reg: pointer to the struct to which the initial or current value of the configuration registers need to be stored
*    @param[in] type:     whether initial or current value of the configuration registers need to be stored
*                        - InitialValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*                        - CurrentValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*
*   This function will copy the initial or current value (depending on the parameter 'type') of the configuration registers to the struct pointed by config_reg
*
*/

void pbistGetConfigValue(pbist_config_reg_t *config_reg, config_value_type_t type)
{
    if (type == InitialValue)
    {
        config_reg->CONFIG_RAMT = PBIST_RAMT_CONFIGVALUE;
        config_reg->CONFIG_DLR = PBIST_DLR_CONFIGVALUE;
        config_reg->CONFIG_PACT = PBIST_PACT_CONFIGVALUE;
        config_reg->CONFIG_PBISTID = PBIST_PBISTID_CONFIGVALUE;
        config_reg->CONFIG_OVER = PBIST_OVER_CONFIGVALUE;
        config_reg->CONFIG_FSRDL1 = PBIST_FSRDL1_CONFIGVALUE;
        config_reg->CONFIG_ROM = PBIST_ROM_CONFIGVALUE;
        config_reg->CONFIG_ALGO = PBIST_ALGO_CONFIGVALUE;
        config_reg->CONFIG_RINFOL = PBIST_RINFOL_CONFIGVALUE;
        config_reg->CONFIG_RINFOU = PBIST_RINFOU_CONFIGVALUE;
    }
    else
    {   
	/*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "Register read back support" */
	    config_reg->CONFIG_RAMT = pbistREG->RAMT;
        config_reg->CONFIG_DLR = pbistREG->DLR;
        config_reg->CONFIG_PACT = pbistREG->PACT;
        config_reg->CONFIG_PBISTID = pbistREG->PBISTID;
        config_reg->CONFIG_OVER = pbistREG->OVER;
        config_reg->CONFIG_FSRDL1 = pbistREG->FSRDL1;
        config_reg->CONFIG_ROM = pbistREG->ROM;
        config_reg->CONFIG_ALGO = pbistREG->ALGO;
        config_reg->CONFIG_RINFOL = pbistREG->RINFOL;
        config_reg->CONFIG_RINFOU = pbistREG->RINFOU;
    }
}

/** @fn void stcGetConfigValue(stc_config_reg_t *config_reg, config_value_type_t type)
*   @brief Get the initial or current values of the configuration registers
*
*    @param[in] *config_reg: pointer to the struct to which the initial or current value of the configuration registers need to be stored
*    @param[in] type:     whether initial or current value of the configuration registers need to be stored
*                        - InitialValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*                        - CurrentValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*
*   This function will copy the initial or current value (depending on the parameter 'type') of the configuration registers to the struct pointed by config_reg
*
*/

void stcGetConfigValue(stc_config_reg_t *config_reg, config_value_type_t type)
{
    if (type == InitialValue)
    {
        config_reg->CONFIG_STCGCR0 = STC_STCGCR0_CONFIGVALUE;
        config_reg->CONFIG_STCGCR1 = STC_STCGCR1_CONFIGVALUE;
        config_reg->CONFIG_STCTPR = STC_STCTPR_CONFIGVALUE;
        config_reg->CONFIG_STCSCSCR = STC_STCSCSCR_CONFIGVALUE;
    }
    else
    {   
	/*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "Register read back support" */
	    config_reg->CONFIG_STCGCR0 = stcREG->STCGCR0;
        config_reg->CONFIG_STCGCR1 = stcREG->STCGCR1;
        config_reg->CONFIG_STCTPR = stcREG->STCTPR;
        config_reg->CONFIG_STCSCSCR = stcREG->STCSCSCR;
    }
}


/** @fn void efcGetConfigValue(efc_config_reg_t *config_reg, config_value_type_t type)
*   @brief Get the initial or current values of the configuration registers
*
*    @param[in] *config_reg: pointer to the struct to which the initial or current value of the configuration registers need to be stored
*    @param[in] type:     whether initial or current value of the configuration registers need to be stored
*                        - InitialValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*                        - CurrentValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*
*   This function will copy the initial or current value (depending on the parameter 'type') of the configuration registers to the struct pointed by config_reg
*
*/

void efcGetConfigValue(efc_config_reg_t *config_reg, config_value_type_t type)
{
    if (type == InitialValue)
    {
        config_reg->CONFIG_BOUNDARY = EFC_BOUNDARY_CONFIGVALUE;
        config_reg->CONFIG_PINS = EFC_PINS_CONFIGVALUE;
        config_reg->CONFIG_SELFTESTCYCLES = EFC_SELFTESTCYCLES_CONFIGVALUE;
        config_reg->CONFIG_SELFTESTSIGN = EFC_SELFTESTSIGN_CONFIGVALUE;
    }
    else
    {   
	/*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "Register read back support" */
	    config_reg->CONFIG_BOUNDARY = efcREG->BOUNDARY;
        config_reg->CONFIG_PINS = efcREG->PINS;
        config_reg->CONFIG_SELFTESTCYCLES = efcREG->SELF_TEST_CYCLES;
        config_reg->CONFIG_SELFTESTSIGN = efcREG->SELF_TEST_SIGN;
    }
}


/** @fn void ccmr4GetConfigValue(ccmr4_config_reg_t *config_reg, config_value_type_t type)
*   @brief Get the initial or current values of the configuration registers
*
*    @param[in] *config_reg: pointer to the struct to which the initial or current value of the configuration registers need to be stored
*    @param[in] type:     whether initial or current value of the configuration registers need to be stored
*                        - InitialValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*                        - CurrentValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*
*   This function will copy the initial or current value (depending on the parameter 'type') of the configuration registers to the struct pointed by config_reg
*
*/

void ccmr4GetConfigValue(ccmr4_config_reg_t *config_reg, config_value_type_t type)
{
    if (type == InitialValue)
    {
        config_reg->CONFIG_CCMKEYR = CCMR4_CCMKEYR_CONFIGVALUE;
    }
    else
    {
	/*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "Register read back support" */
        config_reg->CONFIG_CCMKEYR = CCMKEYR;
    }
}
