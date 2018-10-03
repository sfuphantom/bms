/**
 *
 *  @file emb1428.h
 *
 *  @author Stephen Holland - Texas Instruments Inc.
 *  @date June 2015
 *  @version 1.0 Initial version
 *  @note Built with CCS for Hercules Version: 5.4.0
 */

#ifndef EMB1428_H_
#define EMB1428_H_

#include "datatypes.h"
#define TMS570SPI
// User defines
#define EMB_SCLK		0x04
#define	nCS_DAC			0x08
#define	nCS_BOTSTACK	0x04
#define	nCS_MIDSTACK	0x02
#define	nCS_TOPSTACK	0x01
#define charge			0x00
#define discharge		0x08

#define VIO_3V3		// VIO used for current setpoint DAC output. Set to VIO_3V3 or VIO_5V3.

// Function Prototypes
void initEMB1428Interface(int nDev_ID);
void EMB_Start(int nDev_ID, int channel, int direction);
void EMB_Start_Command(int nDev_ID, int EMB_CS, int EMB_COMMAND);
void EMB_Stop(int nDev_ID, int channel);
void EMB_SetCS(int nDev_ID, int CS);
void EMB_Vset(int nDev_ID, float Amps);

#endif /* EMB1428_H_ */
//EOF
