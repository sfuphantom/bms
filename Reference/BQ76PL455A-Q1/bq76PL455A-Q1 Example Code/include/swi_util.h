/*------------------------------------------------------------
* swi_util.h                             
*                                        
* SWI Utility Routines:
*   swi_enable_fiq()  - Sets 'F' bit
*   swi_disable_fiq() - Clears 'F' bit 
*   swi_
*-------------------------------------------------------------*/

#pragma SWI_ALIAS(swi_enable_fiq, 0x00)
void swi_enable_fiq(void);

#pragma SWI_ALIAS(swi_disable_fiq, 0x01)
void swi_disable_fiq(void);

#pragma SWI_ALIAS(swi_enable_irq, 0x02)
void swi_enable_irq(void);

#pragma SWI_ALIAS(swi_disable_irq, 0x03)
void swi_disable_irq(void);

#pragma SWI_ALIAS(swi_enable_fiq_irq, 0x04)
void swi_enable_fiq_irq(void);

#pragma SWI_ALIAS(swi_disable_fiq_irq, 0x05)
void swi_disable_fiq_irq(void);
