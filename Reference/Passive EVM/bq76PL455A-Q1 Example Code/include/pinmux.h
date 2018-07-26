/** @file pinmux.h 
*   @brief PINMUX Driver Implementation File
*   @date 25.July.2013
*   @version 03.06.00
*
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __PINMUX_H__
#define __PINMUX_H__

#include "reg_pinmux.h"



#define PINMUX_PIN_1_SHIFT	8U
#define PINMUX_PIN_2_SHIFT	0U
#define PINMUX_PIN_5_SHIFT	8U
#define PINMUX_PIN_8_SHIFT	16U
#define PINMUX_PIN_9_SHIFT	24U
#define PINMUX_PIN_10_SHIFT	0U
#define PINMUX_PIN_12_SHIFT	8U
#define PINMUX_PIN_18_SHIFT	16U
#define PINMUX_PIN_27_SHIFT	0U
#define PINMUX_PIN_36_SHIFT	16U
#define PINMUX_PIN_37_SHIFT	24U
#define PINMUX_PIN_38_SHIFT	0U
#define PINMUX_PIN_39_SHIFT	8U
#define PINMUX_PIN_58_SHIFT	16U
#define PINMUX_PIN_68_SHIFT	8U
#define PINMUX_PIN_93_SHIFT	8U

#define PINMUX_PIN_1_MASK		(~(0xFFU << PINMUX_PIN_1_SHIFT)
#define PINMUX_PIN_2_MASK		(~(0xFFU << PINMUX_PIN_2_SHIFT)
#define PINMUX_PIN_5_MASK		(~(0xFFU << PINMUX_PIN_5_SHIFT)
#define PINMUX_PIN_8_MASK		(~(0xFFU << PINMUX_PIN_8_SHIFT)
#define PINMUX_PIN_9_MASK		(~(0xFFU << PINMUX_PIN_9_SHIFT)
#define PINMUX_PIN_10_MASK		(~(0xFFU << PINMUX_PIN_10_SHIFT)
#define PINMUX_PIN_12_MASK		(~(0xFFU << PINMUX_PIN_12_SHIFT)
#define PINMUX_PIN_18_MASK		(~(0xFFU << PINMUX_PIN_18_SHIFT)
#define PINMUX_PIN_27_MASK		(~(0xFFU << PINMUX_PIN_27_SHIFT)
#define PINMUX_PIN_36_MASK		(~(0xFFU << PINMUX_PIN_36_SHIFT)
#define PINMUX_PIN_37_MASK		(~(0xFFU << PINMUX_PIN_37_SHIFT)
#define PINMUX_PIN_38_MASK		(~(0xFFU << PINMUX_PIN_38_SHIFT)
#define PINMUX_PIN_39_MASK		(~(0xFFU << PINMUX_PIN_39_SHIFT)
#define PINMUX_PIN_58_MASK		(~(0xFFU << PINMUX_PIN_58_SHIFT)
#define PINMUX_PIN_68_MASK		(~(0xFFU << PINMUX_PIN_68_SHIFT)
#define PINMUX_PIN_93_MASK		(~(0xFFU << PINMUX_PIN_93_SHIFT)



#define PINMUX_PIN_1_GIOA_0		(0x1U <<  PINMUX_PIN_1_SHIFT)
#define PINMUX_PIN_1_SPI3nCS_3		(0x2U <<  PINMUX_PIN_1_SHIFT)

#define PINMUX_PIN_2_GIOA_1		(0x1U <<  PINMUX_PIN_2_SHIFT)
#define PINMUX_PIN_2_SPI3nCS_2		(0x2U <<  PINMUX_PIN_2_SHIFT)

#define PINMUX_PIN_5_GIOA_2		(0x1U <<  PINMUX_PIN_5_SHIFT)
#define PINMUX_PIN_5_SPI3nCS_1		(0x2U <<  PINMUX_PIN_5_SHIFT)

#define PINMUX_PIN_8_GIOA_3		(0x1U <<  PINMUX_PIN_8_SHIFT)
#define PINMUX_PIN_8_SPI2nCS_3		(0x2U <<  PINMUX_PIN_8_SHIFT)

#define PINMUX_PIN_9_GIOA_4		(0x1U <<  PINMUX_PIN_9_SHIFT)
#define PINMUX_PIN_9_SPI2nCS_2		(0x2U <<  PINMUX_PIN_9_SHIFT)

#define PINMUX_PIN_10_GIOA_5		(0x1U <<  PINMUX_PIN_10_SHIFT)
#define PINMUX_PIN_10_EXTCLKIN		(0x2U <<  PINMUX_PIN_10_SHIFT)

#define PINMUX_PIN_12_GIOA_6		(0x1U <<  PINMUX_PIN_12_SHIFT)
#define PINMUX_PIN_12_SPI2nCS_1		(0x2U <<  PINMUX_PIN_12_SHIFT)
#define PINMUX_PIN_12_HET_31		(0x4U <<  PINMUX_PIN_12_SHIFT)

#define PINMUX_PIN_18_GIOA_7		(0x1U <<  PINMUX_PIN_18_SHIFT)
#define PINMUX_PIN_18_HET_29		(0x2U <<  PINMUX_PIN_18_SHIFT)

#define PINMUX_PIN_27_MIBSPI1nCS_2	(0x1U <<  PINMUX_PIN_27_SHIFT)
#define PINMUX_PIN_27_HET_20		(0x2U <<  PINMUX_PIN_27_SHIFT)
#define PINMUX_PIN_27_HET_19		(0x4U <<  PINMUX_PIN_27_SHIFT)

#define PINMUX_PIN_36_SPI3CLK		(0x1U <<  PINMUX_PIN_36_SHIFT)
#define PINMUX_PIN_36_EQEPA		(0x2U <<  PINMUX_PIN_36_SHIFT)

#define PINMUX_PIN_37_SPI3nENA		(0x1U <<  PINMUX_PIN_37_SHIFT)
#define PINMUX_PIN_37_EQEPB		(0x2U <<  PINMUX_PIN_37_SHIFT)

#define PINMUX_PIN_38_SPI3nCS_0		(0x1U <<  PINMUX_PIN_38_SHIFT)
#define PINMUX_PIN_38_EQEPI		(0x2U <<  PINMUX_PIN_38_SHIFT)

#define PINMUX_PIN_39_MIBSPI1nCS_3	(0x1U <<  PINMUX_PIN_39_SHIFT)
#define PINMUX_PIN_39_HET_26		(0x2U <<  PINMUX_PIN_39_SHIFT)

#define PINMUX_PIN_58_ADEVT		(0x1U <<  PINMUX_PIN_58_SHIFT)
#define PINMUX_PIN_58_HET_28		(0x2U <<  PINMUX_PIN_58_SHIFT)

#define PINMUX_PIN_68_MIBSPI1nENA	(0x1U <<  PINMUX_PIN_68_SHIFT)
#define PINMUX_PIN_68_HET_23		(0x2U <<  PINMUX_PIN_68_SHIFT)
#define PINMUX_PIN_68_HET_30		(0x4U <<  PINMUX_PIN_68_SHIFT)

#define PINMUX_PIN_93_MIBSPI1nCS_1	(0x1U <<  PINMUX_PIN_93_SHIFT)
#define PINMUX_PIN_93_EQEPS		(0x2U <<  PINMUX_PIN_93_SHIFT)
#define PINMUX_PIN_93_HET_17		(0x4U <<  PINMUX_PIN_93_SHIFT)


/** 
 *  @defgroup IOMM IOMM
 *  @brief I/O Multiplexing and Control Module.
 *  
 *  The IOMM contains memory-mapped registers (MMR) that control device-specific multiplexed functions.
 *  The safety and diagnostic features of the IOMM are:
 *  - Kicker mechanism to protect the MMRs from accidental writes
 *  - Master-id checker to only allow the CPU to write to the MMRs
 *  - Error indication for access violations
 *
 *	Related Files
 *   - reg_pinmux.h
 *   - pinmux.h
 *   - pinmux.c
 *  @addtogroup IOMM
 *  @{
 */
 
/** @fn void muxInit(void)
*   @brief Initializes the PINMUX Driver
*
*   This function initializes the PINMUX module and configures the selected 
*   pinmux settings as per the user selection in the GUI
*/
void muxInit(void);

/**@}*/
#endif
