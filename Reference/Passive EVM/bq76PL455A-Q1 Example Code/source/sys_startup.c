/** @file sys_startup.c 
*   @brief Startup Source File
*   @date 25.July.2013
*   @version 03.06.00
*
*   This file contains:
*   - Include Files
*   - Type Definitions
*   - External Functions
*   - VIM RAM Setup
*   - Startup Routine
*   .
*   which are relevant for the Startup.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */


/* Include Files */

#include "sys_common.h"
#include "system.h"
#include "sys_vim.h"
#include "sys_core.h"
#include "sys_selftest.h"
#include "esm.h"
#include "mibspi.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */


/* Type Definitions */

typedef void (*handler_fptr)(const uint8 * in, uint8 * out);

/* USER CODE BEGIN (2) */
/* USER CODE END */


/* External Functions */



/*SAFETYMCUSW 218 S MR:20.2 <APPROVED> "Functions from library" */
extern void __TI_auto_init(void);
/*SAFETYMCUSW 354 S MR:1.4 <APPROVED> " Startup code(main should bedeclared by the user)" */
extern void main(void);
/*SAFETYMCUSW 122 S MR:20.11 <APPROVED> "Startup code(exit and abort need to be present)" */
/*SAFETYMCUSW 354 S MR:1.4 <APPROVED> " Startup code(Extern declaration present in the library)" */
extern void exit(void);

extern void muxInit(void);



/* USER CODE BEGIN (3) */
/* USER CODE END */

/* Startup Routine */
void _c_int00(void);
/* USER CODE BEGIN (4) */
/* USER CODE END */

#pragma CODE_STATE(_c_int00, 32)
#pragma INTERRUPT(_c_int00, RESET)
#pragma WEAK(_c_int00)

void _c_int00(void)
{
    
/* USER CODE BEGIN (5) */
/* USER CODE END */

    /* Initialize Core Registers to avoid CCM Error */
    _coreInitRegisters_();

/* USER CODE BEGIN (6) */
/* USER CODE END */

    /* Initialize Stack Pointers */
    _coreInitStackPointer_();

/* USER CODE BEGIN (7) */
/* USER CODE END */


    /* Enable CPU Event Export */
    /* This allows the CPU to signal any single-bit or double-bit errors detected
     * by its ECC logic for accesses to program flash or data RAM.
     */
    _coreEnableEventBusExport_();

/* USER CODE BEGIN (11) */
/* USER CODE END */

    /* Reset handler: the following instructions read from the system exception status register
     * to identify the cause of the CPU reset.
     */

    /* check for power-on reset condition */
	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    if ((SYS_EXCEPTION & POWERON_RESET) != 0U)
    {
/* USER CODE BEGIN (12) */
/* USER CODE END */
        
        /* clear all reset status flags */
        SYS_EXCEPTION = 0xFFFFU;

/* USER CODE BEGIN (13) */
/* USER CODE END */

    _errata_CORTEXR4_66_();
    
/* USER CODE BEGIN (14) */
/* USER CODE END */

        /* continue with normal start-up sequence */
    }
	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    else if ((SYS_EXCEPTION & OSC_FAILURE_RESET) != 0U)
    {
        /* Reset caused due to oscillator failure.
        Add user code here to handle oscillator failure */

/* USER CODE BEGIN (16) */
/* USER CODE END */
    }
	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    else if ((SYS_EXCEPTION & WATCHDOG_RESET) !=0U)
    {
        /* Reset caused due 
         *  1) windowed watchdog violation - Add user code here to handle watchdog violation.
         *  2) ICEPICK Reset - After loading code via CCS / System Reset through CCS
         */
        /* Check the WatchDog Status register */
        if(WATCHDOG_STATUS != 0U)
        {
            /* Add user code here to handle watchdog violation. */ 
/* USER CODE BEGIN (17) */
/* USER CODE END */

            /* Clear the Watchdog reset flag in Exception Status register */ 
            SYS_EXCEPTION = WATCHDOG_RESET;
        
/* USER CODE BEGIN (18) */
/* USER CODE END */
        }
        else
        {
            /* Clear the ICEPICK reset flag in Exception Status register */ 
            SYS_EXCEPTION = ICEPICK_RESET;
/* USER CODE BEGIN (19) */
/* USER CODE END */
        }
    }
	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    else if ((SYS_EXCEPTION & CPU_RESET) !=0U)
    {
        /* Reset caused due to CPU reset.
        CPU reset can be caused by CPU self-test completion, or
        by toggling the "CPU RESET" bit of the CPU Reset Control Register. */

/* USER CODE BEGIN (20) */
/* USER CODE END */

        /* clear all reset status flags */
        SYS_EXCEPTION = CPU_RESET;

/* USER CODE BEGIN (21) */
/* USER CODE END */

    }
	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    else if ((SYS_EXCEPTION & SW_RESET) != 0U)
    {
        /* Reset caused due to software reset.
        Add user code to handle software reset. */

/* USER CODE BEGIN (22) */
/* USER CODE END */
    }
    else
    {
        /* Reset caused by nRST being driven low externally.
        Add user code to handle external reset. */

/* USER CODE BEGIN (23) */
/* USER CODE END */
    }

    /* Check if there were ESM group3 errors during power-up.
     * These could occur during eFuse auto-load or during reads from flash OTP
     * during power-up. Device operation is not reliable and not recommended
     * in this case.
     * An ESM group3 error only drives the nERROR pin low. An external circuit
     * that monitors the nERROR pin must take the appropriate action to ensure that
     * the system is placed in a safe state, as determined by the application.
     */
    if ((esmREG->SR1[2]) != 0U)
    {
/* USER CODE BEGIN (24) */
/* USER CODE END */
    /*SAFETYMCUSW 5 C MR:NA <APPROVED> "for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below" */
    /*SAFETYMCUSW 26 S MR:NA <APPROVED> "for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below" */
	/*SAFETYMCUSW 28 D MR:NA <APPROVED> "for(;;) can be removed by adding "# if 0" and "# endif" in the user codes above and below" */
        for(;;)
        { 
        }/* Wait */                 
/* USER CODE BEGIN (25) */
/* USER CODE END */
    }

/* USER CODE BEGIN (26) */
/* USER CODE END */

    /* Initialize System - Clock, Flash settings with Efuse self check */
    systemInit();


/* USER CODE BEGIN (29) */
/* USER CODE END */


    /* Run a diagnostic check on the memory self-test controller.
     * This function chooses a RAM test algorithm and runs it on an on-chip ROM.
     * The memory self-test is expected to fail. The function ensures that the PBIST controller
     * is capable of detecting and indicating a memory self-test failure.
     */
    pbistSelfCheck();

/* USER CODE BEGIN (31) */
/* USER CODE END */


	_coreDisableRamEcc_();
	
    /* Run PBIST on CPU RAM.
     * The PBIST controller needs to be configured separately for single-port and dual-port SRAMs.
     * The CPU RAM is a single-port memory. The actual "RAM Group" for all on-chip SRAMs is defined in the
     * device datasheet.
     */
    pbistRun(0x00000020U, /* ESRAM Single Port PBIST */
             (uint32)PBIST_March13N_SP);

/* USER CODE BEGIN (32) */
/* USER CODE END */

    /* Wait for PBIST for CPU RAM to be completed */
	/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while(pbistIsTestCompleted() != TRUE)
    { 
    }/* Wait */                 
    

/* USER CODE BEGIN (33) */
/* USER CODE END */
	
    /* Check if CPU RAM passed the self-test */
    if( pbistIsTestPassed() != TRUE)
    {
        /* CPU RAM failed the self-test.
         * Need custom handler to check the memory failure
         * and to take the appropriate next step.
         */
/* USER CODE BEGIN (34) */
/* USER CODE END */
		 
		pbistFail();
		
/* USER CODE BEGIN (35) */
/* USER CODE END */
    }

/* USER CODE BEGIN (36) */
/* USER CODE END */

    /* Disable PBIST clocks and disable memory self-test mode */
    pbistStop();
    

/* USER CODE BEGIN (37) */
/* USER CODE END */


    /* Initialize CPU RAM.
     * This function uses the system module's hardware for auto-initialization of memories and their
     * associated protection schemes. The CPU RAM is initialized by setting bit 0 of the MSIENA register.
     * Hence the value 0x1 passed to the function.
     * This function will initialize the entire CPU RAM and the corresponding ECC locations.
     */
    memoryInit(0x1U);

/* USER CODE BEGIN (38) */
/* USER CODE END */
    
    /* Enable ECC checking for TCRAM accesses.
     * This function enables the CPU's ECC logic for accesses to B0TCM and B1TCM.
     */
    _coreEnableRamEcc_();

/* USER CODE BEGIN (39) */
/* USER CODE END */


    /* Start PBIST on all dual-port memories */
    /* NOTE : Please Refer DEVICE DATASHEET for the list of Supported Dual port Memories.
       PBIST test perfomed only on the user selected memories in HALCoGen's GUI SAFETY INIT tab.
     */
    
    pbistRun(  (uint32)0x00000000U   
             | (uint32)0x00000000U         
             | (uint32)0x00000000U    
             | (uint32)0x00000200U   
             | (uint32)0x00000040U
             | (uint32)0x00000000U
             | (uint32)0x00000000U
             | (uint32)0x00000004U   
             | (uint32)0x00000008U   
             | (uint32)0x00000000U   
             | (uint32)0x00000400U   
             | (uint32)0x00000000U   
             | (uint32)0x00001000U   
             | (uint32)0x00000000U   
             | (uint32)0x00002000U   
             | (uint32)0x00000000U   
             | (uint32)0x00000000U    
             | (uint32)0x00000000U    
             | (uint32)0x00000000U   
             ,(uint32) PBIST_March13N_DP);

/* USER CODE BEGIN (40) */
/* USER CODE END */


    /* Test the CPU ECC mechanism for RAM accesses.
     * The checkBxRAMECC functions cause deliberate single-bit and double-bit errors in TCRAM accesses
     * by corrupting 1 or 2 bits in the ECC. Reading from the TCRAM location with a 2-bit error
     * in the ECC causes a data abort exception. The data abort handler is written to look for
     * deliberately caused exception and to return the code execution to the instruction
     * following the one that caused the abort.
     */
	checkRAMECC();

/* USER CODE BEGIN (41) */
/* USER CODE END */


/* USER CODE BEGIN (43) */
/* USER CODE END */

    /* Wait for PBIST for CPU RAM to be completed */
	/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while(pbistIsTestCompleted() != TRUE)
    { 
    }/* Wait */                 
    

/* USER CODE BEGIN (44) */
/* USER CODE END */

    /* Check if CPU RAM passed the self-test */
    if( pbistIsTestPassed() != TRUE)
    {

/* USER CODE BEGIN (45) */
/* USER CODE END */

        /* CPU RAM failed the self-test.
         * Need custom handler to check the memory failure
         * and to take the appropriate next step.
         */
/* USER CODE BEGIN (46) */
/* USER CODE END */
		 
		pbistFail();
		
/* USER CODE BEGIN (47) */
/* USER CODE END */
    }

/* USER CODE BEGIN (48) */
/* USER CODE END */

    /* Disable PBIST clocks and disable memory self-test mode */
    pbistStop();
    


/* USER CODE BEGIN (55) */
/* USER CODE END */

    /* Release the MibSPI1 modules from local reset.
     * This will cause the MibSPI1 RAMs to get initialized along with the parity memory.
     */
     mibspiREG1->GCR0 = 0x1U;
     
/* USER CODE BEGIN (56) */
/* USER CODE END */

    /* Initialize all on-chip SRAMs except for MibSPIx RAMs
     * The MibSPIx modules have their own auto-initialization mechanism which is triggered
     * as soon as the modules are brought out of local reset.
     */
    /* The system module auto-init will hang on the MibSPI RAM if the module is still in local reset.
     */
    /* NOTE : Please Refer DEVICE DATASHEET for the list of Supported Memories and their channel numbers.
              Memory Initialization is perfomed only on the user selected memories in HALCoGen's GUI SAFETY INIT tab.
     */
    memoryInit(  (0U << 1U)   
                 | (1U << 2U)  
                 | (1U << 5U)  
                 | (1U << 6U)  
                 | (0U << 10U) 
                 | (1U << 8U)  
                 | (0U << 14U) 
                 | (1U << 3U)  
                 | (1U << 4U)  
                 | (0U << 15U) 
                 | (0U << 16U) 
                 | (0U << 13U) );

    /* Test the parity protection mechanism for peripheral RAMs
       NOTE : Please Refer DEVICE DATASHEET for the list of Supported Memories with parity.
                 Parity Self check is perfomed only on the user selected memories in HALCoGen's GUI SAFETY INIT tab.
    */

/* USER CODE BEGIN (57) */
/* USER CODE END */
     
    het1ParityCheck();
    
/* USER CODE BEGIN (58) */
/* USER CODE END */

    htu1ParityCheck();
    
/* USER CODE BEGIN (61) */
/* USER CODE END */

    adc1ParityCheck();
    
/* USER CODE BEGIN (63) */
/* USER CODE END */

    can1ParityCheck();
    
/* USER CODE BEGIN (64) */
/* USER CODE END */

    can2ParityCheck();
    
/* USER CODE BEGIN (66) */
/* USER CODE END */

    vimParityCheck();
    

/* USER CODE BEGIN (68) */
/* USER CODE END */

/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while ((mibspiREG1->FLG & 0x01000000U) == 0x01000000U)
    { 
    }/* Wait */                 
    /* wait for MibSPI1 RAM to complete initialization */

/* USER CODE BEGIN (69) */
/* USER CODE END */

    mibspi1ParityCheck();
    

/* USER CODE BEGIN (72) */
/* USER CODE END */
    
    /* Enable IRQ offset via Vic controller */
    _coreEnableIrqVicOffset_();
    

/* USER CODE BEGIN (73) */
/* USER CODE END */

    /* Initialize VIM table */
    vimInit();    

/* USER CODE BEGIN (74) */
/* USER CODE END */

    /* Configure system response to error conditions signaled to the ESM group1 */
    /* This function can be configured from the ESM tab of HALCoGen */
    esmInit();

    /* initialize copy table */
    __TI_auto_init();

/* USER CODE BEGIN (75) */
/* USER CODE END */
    
    /* call the application */
/*SAFETYMCUSW 296 S MR:8.6 <APPROVED> "Startup code(library functions at block scope)" */
/*SAFETYMCUSW 326 S MR:8.2 <APPROVED> "Startup code(Declaration for main in library)" */
/*SAFETYMCUSW 60 D MR:8.8 <APPROVED> "Startup code(Declaration for main in library;Only doing an extern for the same)" */
    main();

/* USER CODE BEGIN (76) */
/* USER CODE END */
/*SAFETYMCUSW 122 S MR:20.11 <APPROVED> "Startup code(exit and abort need to be present)" */
    exit();
/* USER CODE BEGIN (77) */
/* USER CODE END */
}

/* USER CODE BEGIN (78) */
/* USER CODE END */
