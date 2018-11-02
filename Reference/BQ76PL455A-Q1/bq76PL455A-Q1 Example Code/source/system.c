/** @file system.c 
*   @brief System Driver Source File
*   @date 25.July.2013
*   @version 03.06.00
*
*   This file contains:
*   - API Functions
*   .
*   which are relevant for the System driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */


/* Include Files */

#include "system.h"
#include "sys_selftest.h"
#include "sys_pcr.h"
#include "pinmux.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @fn void systemInit(void)
*   @brief Initializes System Driver
*
*   This function initializes the System driver.
*
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void setupPLL(void)
{

/* USER CODE BEGIN (3) */
/* USER CODE END */

	/* Disable PLL1 */
	systemREG1->CSDISSET = (1U << 1U); 
	/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
	while((systemREG1->CSDIS & 0x2U) != 0x2U)
	{
	/* Wait */
	}
	
	/* Clear Global Status Register */
	systemREG1->GBLSTAT = 0x301U;
	
    /** - Configure PLL control registers */
    /** @b Initialize @b Pll1: */

    /**   - Setup pll control register 1:
    *     - Setup reset on oscillator slip 
    *     - Setup bypass on pll slip
    *     - setup Pll output clock divider to max before Lock
    *     - Setup reset on oscillator fail
    *     - Setup reference clock divider 
    *     - Setup Pll multiplier          
    */
    systemREG1->PLLCTL1 =  (uint32)0x00000000U 
                        |  (uint32)0x20000000U 
                        | (((uint32)0x1FU)<< 24U) 
                        |  (uint32)0x00000000U 
                        | (((uint32)6U - 1U)<< 16U) 
                        | (((uint32)120U - 1U)<< 8U);

    /**   - Setup pll control register 2
    *     - Enable/Disable frequency modulation
    *     - Setup spreading rate
    *     - Setup bandwidth adjustment
    *     - Setup internal Pll output divider
    *     - Setup spreading amount
    */
    systemREG1->PLLCTL2 =  0x00000000U
                        | (255U << 22U)
                        | (7U << 12U)
                        | ((2U - 1U)<< 9U)
                        |  61U;

	/** - Enable PLL(s) to start up or Lock */
    systemREG1->CSDIS = 0x00000000U	
                      | 0x00000000U 
                      | 0x00000008U 
                      | 0x00000080U 
                      | 0x00000000U 
                      | 0x00000040U 
                      | 0x00000000U;
}

void trimLPO(void)
{

/* USER CODE BEGIN (4) */
/* USER CODE END */

    /** @b Initialize Lpo: */
    /** Load TRIM values from OTP if present else load user defined values */
	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    if(LPO_TRIM_VALUE != 0xFFFFU)
    {
    
        systemREG1->LPOMONCTL  = (1U << 24U)
                                | LPO_TRIM_VALUE;
    }
    else
    {

    	systemREG1->LPOMONCTL 	= (1U << 24U)
                                 | (16U << 8U)
                                 | 8U;
    }

/* USER CODE BEGIN (5) */
/* USER CODE END */

}

void setupFlash(void)
{

/* USER CODE BEGIN (6) */
/* USER CODE END */

    /** - Setup flash read mode, address wait states and data wait states */
    flashWREG->FRDCNTL =  0x00000000U 
                       | (1U << 8U) 
                       | (0U << 4U) 
                       |  1U;

    /** - Setup flash access wait states for bank 7 */
    FSM_WR_ENA_HL    = 0x5U;
    EEPROM_CONFIG_HL = 0x00000002U
	                 | (4U << 16U) ;

/* USER CODE BEGIN (7) */
/* USER CODE END */

    /** - Disable write access to flash state machine registers */
    FSM_WR_ENA_HL = 0xAU;

    /** - Setup flash bank power modes */
    flashWREG->FBFALLBACK = 0x00000000U
                          | (SYS_ACTIVE << 14U) 
                          | (SYS_SLEEP << 12U) 
                          | (SYS_SLEEP << 10U) 
                          | (SYS_SLEEP << 8U) 
                          | (SYS_SLEEP << 6U) 
                          | (SYS_SLEEP << 4U) 
                          | (SYS_SLEEP << 2U) 
                          |  SYS_ACTIVE;

/* USER CODE BEGIN (8) */
/* USER CODE END */

}

void periphInit(void)
{

/* USER CODE BEGIN (9) */
/* USER CODE END */

    /** - Disable Peripherals before peripheral powerup*/
    systemREG1->CLKCNTL &= 0xFFFFFEFFU;

	/** - Release peripherals from reset and enable clocks to all peripherals */
    /** - Power-up all peripherals */
    pcrREG->PSPWRDWNCLR0 = 0xFFFFFFFFU;
    pcrREG->PSPWRDWNCLR1 = 0xFFFFFFFFU;
    pcrREG->PSPWRDWNCLR2 = 0xFFFFFFFFU;
    pcrREG->PSPWRDWNCLR3 = 0xFFFFFFFFU;

    /** - Enable Peripherals */
    systemREG1->CLKCNTL |= 1U << 8U;
	
/* USER CODE BEGIN (10) */
/* USER CODE END */

}

void mapClocks(void)
{
	uint32 SYS_CSVSTAT, SYS_CSDIS;
	
/* USER CODE BEGIN (11) */
/* USER CODE END */

    /** @b Initialize @b Clock @b Tree: */
    /** - Disable / Enable clock domain */
    systemREG1->CDDIS= (FALSE << 4U ) /* AVCLK 1 OFF */
                      |(TRUE << 5U ) /* AVCLK 2 OFF */
	                  |(FALSE << 8U ) /* VCLK3 OFF */
	                  |(FALSE << 10U) /* AVCLK 3 OFF */
                      |(FALSE << 11U); /* AVCLK 4 OFF */


    /* Work Around for Errata SYS#46:
     * 
     * Errata Description:            
     *            Clock Source Switching Not Qualified with Clock Source Enable And Clock Source Valid
     * Workaround:
     *            Always check the CSDIS register to make sure the clock source is turned on and check 
     * the CSVSTAT register to make sure the clock source is valid. Then write to GHVSRC to switch the clock.
     */
	/** - Wait for until clocks are locked */
	SYS_CSVSTAT = systemREG1->CSVSTAT;
	SYS_CSDIS = systemREG1->CSDIS;
    while ((SYS_CSVSTAT & ((SYS_CSDIS ^ 0xFFU) & 0xFFU)) != ((SYS_CSDIS ^ 0xFFU) & 0xFFU))
    { 
		SYS_CSVSTAT = systemREG1->CSVSTAT;
		SYS_CSDIS = systemREG1->CSDIS;
	} /* Wait */

/* USER CODE BEGIN (12) */
/* USER CODE END */

	/* Now the PLLs are locked and the PLL outputs can be sped up */
	/* The R-divider was programmed to be 0xF. Now this divider is changed to programmed value */
    systemREG1->PLLCTL1 = (systemREG1->PLLCTL1 & 0xE0FFFFFFU)|((2U - 1U)<< 24U);

	/** - Map device clock domains to desired sources and configure top-level dividers */
	/** - All clock domains are working off the default clock sources until now */
	/** - The below assignments can be easily modified using the HALCoGen GUI */
    
    /** - Setup GCLK, HCLK and VCLK clock source for normal operation, power down mode and after wakeup */
    systemREG1->GHVSRC = (SYS_PLL1 << 24U) 
                       | (SYS_PLL1 << 16U) 
                       |  SYS_PLL1;
                       
    /** - Setup synchronous peripheral clock dividers for VCLK1, VCLK2, VCLK3 */
    systemREG1->CLKCNTL  = (systemREG1->CLKCNTL & 0xF0F0FFFFU) 
						 | (0U << 24U)  
						 | (0U << 16U);  

/* USER CODE BEGIN (13) */
/* USER CODE END */
	
    /** - Setup RTICLK1 and RTICLK2 clocks */
    systemREG1->RCLKSRC = (1U << 24U)
                        | (SYS_VCLK << 16U) 
                        | (1U << 8U)  
                        |  SYS_VCLK;

    /** - Setup asynchronous peripheral clock sources for AVCLK1 and AVCLK2 */
    systemREG1->VCLKASRC = (SYS_VCLK << 8U)
                          |  SYS_VCLK;

/* USER CODE BEGIN (14) */
/* USER CODE END */

}

void systemInit(void)
{
/* USER CODE BEGIN (15) */
/* USER CODE END */

	/* Configure PLL control registers and enable PLLs.
	 * The PLL takes (127 + 1024 * NR) oscillator cycles to acquire lock.
	 * This initialization sequence performs all the tasks that are not
	 * required to be done at full application speed while the PLL locks.
	 */
	setupPLL();
	
/* USER CODE BEGIN (16) */
/* USER CODE END */

	/* Run eFuse controller start-up checks and start eFuse controller ECC self-test.
	 * This includes a check for the eFuse controller error outputs to be stuck-at-zero.
	 */
	efcCheck();
	
/* USER CODE BEGIN (17) */
/* USER CODE END */
	
	/* Enable clocks to peripherals and release peripheral reset */
	periphInit();

/* USER CODE BEGIN (18) */
/* USER CODE END */

	/* Configure device-level multiplexing and I/O multiplexing */
	muxInit();
	
/* USER CODE BEGIN (19) */
/* USER CODE END */

	/* Wait for eFuse controller self-test to complete and check results */
	if (checkefcSelfTest() == FALSE)							/* eFuse controller ECC logic self-test failed */
	{
		selftestFailNotification(EFCCHECK_FAIL2);           /* device operation is not reliable */
	}
	
/* USER CODE BEGIN (20) */
/* USER CODE END */

	/** - Set up flash address and data wait states based on the target CPU clock frequency
	 * The number of address and data wait states for the target CPU clock frequency are specified
	 * in the specific part's datasheet.
	 */
	setupFlash();

/* USER CODE BEGIN (21) */
/* USER CODE END */

	/** - Configure the LPO such that HF LPO is as close to 10MHz as possible */
	trimLPO();

/* USER CODE BEGIN (23) */
/* USER CODE END */

	/** - Wait for PLLs to start up and map clock domains to desired clock sources */
	mapClocks();

/* USER CODE BEGIN (24) */
/* USER CODE END */

	/** - set ECLK pins functional mode */
    systemREG1->SYSPC1 = 0U;

    /** - set ECLK pins default output value */
    systemREG1->SYSPC4 = 0U;

    /** - set ECLK pins output direction */
    systemREG1->SYSPC2 = 1U;

    /** - set ECLK pins open drain enable */
    systemREG1->SYSPC7 = 0U;

    /** - set ECLK pins pullup/pulldown enable */
    systemREG1->SYSPC8 = 0U;   

    /** - set ECLK pins pullup/pulldown select */
    systemREG1->SYSPC9 = 1U;

    /** - Setup ECLK */
    systemREG1->ECPCNTL = (0U << 24U)
                        | (0U << 23U)
                        | ((8U - 1U) & 0xFFFFU);

/* USER CODE BEGIN (25) */
/* USER CODE END */
}

void systemPowerDown(uint32 mode)
{

/* USER CODE BEGIN (26) */
/* USER CODE END */

    /* Disable clock sources */
    systemREG1->CSDISSET = mode & 0x000000FFU;

    /* Disable clock domains */
    systemREG1->CDDIS = (mode >> 8U) & 0x00000FFFU;

    /* Idle CPU */
	/*SAFETYMCUSW 88 S MR:2.1 <APPROVED> "Assembly in C needed" */
    asm(" wfi");

/* USER CODE BEGIN (27) */
/* USER CODE END */

}

/* USER CODE BEGIN (28) */
/* USER CODE END */
