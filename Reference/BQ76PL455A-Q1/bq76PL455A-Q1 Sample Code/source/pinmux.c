/** @file pinmux.c 
*   @brief PINMUX Driver Implementation File
*   @date 25.July.2013
*   @version 03.06.00
*
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

/* Include Files */

#include "pinmux.h"

#define PINMUX_SET(REG, BALLID, MUX)								\
				pinMuxReg->PINMMR##REG## = (pinMuxReg->PINMMR##REG## & PINMUX_BALL_##BALLID##_MASK) | (PINMUX_BALL_##BALLID##_##MUX)


#define PINMUX_GIOB_DISABLE_HET2_ENABLE	\
			pinMuxReg->PINMMR29 = (pinMuxReg->PINMMR29 & PINMUX_GIOB_DISABLE_HET2_MASK) | PINMUX_GIOB_DISABLE_HET2
			
#define PINMUX_ALT_ADC_TRIGGER_SELECT(num)	\
			pinMuxReg->PINMMR30 = (pinMuxReg->PINMMR30 & PINMUX_ALT_ADC_TRIGGER_MASK) | (PINMUX_ALT_ADC_TRIGGER_##num)
			

/* USER CODE BEGIN (0) */
/* USER CODE END */

void muxInit(void){

/* USER CODE BEGIN (1) */
/* USER CODE END */

	/* Enable Pin Muxing */
	kickerReg->KICKER0 = 0x83E70B13U;
	kickerReg->KICKER1 = 0x95A4F1E0U;
	
/* USER CODE BEGIN (2) */
/* USER CODE END */

        pinMuxReg->PINMMR0 = PINMUX_PIN_1_GIOA_0;
	
	pinMuxReg->PINMMR1 = PINMUX_PIN_2_GIOA_1 | PINMUX_PIN_5_GIOA_2 | PINMUX_PIN_8_GIOA_3 | PINMUX_PIN_9_GIOA_4;
	
	pinMuxReg->PINMMR2 = PINMUX_PIN_10_GIOA_5 | PINMUX_PIN_12_GIOA_6 | PINMUX_PIN_18_GIOA_7;
	
	pinMuxReg->PINMMR3 = PINMUX_PIN_27_MIBSPI1nCS_2 | PINMUX_PIN_36_SPI3CLK | PINMUX_PIN_37_SPI3nENA;
	
	pinMuxReg->PINMMR4 = PINMUX_PIN_38_SPI3nCS_0 | PINMUX_PIN_39_MIBSPI1nCS_3 | PINMUX_PIN_58_ADEVT;
	
	pinMuxReg->PINMMR5 = PINMUX_PIN_68_MIBSPI1nENA;
	
	pinMuxReg->PINMMR6 = PINMUX_PIN_93_MIBSPI1nCS_1;
	
	
/* USER CODE BEGIN (3) */
/* USER CODE END */
	
	/* Disable Pin Muxing */
	kickerReg->KICKER0 = 0x00000000U;
	kickerReg->KICKER1 = 0x00000000U;
	
/* USER CODE BEGIN (4) */
/* USER CODE END */
}

/* USER CODE BEGIN (5) */
/* USER CODE END */
