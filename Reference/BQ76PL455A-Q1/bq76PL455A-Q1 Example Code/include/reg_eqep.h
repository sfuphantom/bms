/** @file reg_eqep.h
*   @brief EQEP Register Layer Header File
*   @date 25.July.2013
*   @version 03.06.00
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the EQEP driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __REG_EQEP_H__
#define __REG_EQEP_H__

#include "sys_common.h"


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Eqep Register Frame Definition */
/** @struct eqepBASE
*   @brief EQEP Register Frame Definition
*
*   This type is used to access the EQEP Registers.
*/
/** @typedef eqepBASE_t
*   @brief EQEP Register Frame Type Definition
*
*   This type is used to access the EQEP Registers.
*/
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1)) 

typedef struct eqepBASE
{
  uint32      QPOSCNT;       /*< 0x0000 eQEP Position Counter*/
  uint32      QPOSINIT;      /*< 0x0004 eQEP Initialization Position Count*/
  uint32      QPOSMAX;       /*< 0x0008 eQEP Maximum Position Count*/
  uint32      QPOSCMP;       /*< 0x000C eQEP Position Compare*/
  uint32      QPOSILAT;      /*< 0x0010 eQEP Index Position Latch*/
  uint32      QPOSSLAT;      /*< 0x0014 eQEP Strobe Position Latch*/
  uint32      QPOSLAT;       /*< 0x0018 eQEP Position Latch*/
  uint32      QUTMR;         /*< 0x001C eQEP Unit Timer*/
  uint32      QUPRD;         /*< 0x0020 eQEP Unit Period*/
  uint16		QWDTMR;		   /*< 0x0024 eQEP Watchdog Timer*/
  uint16		QWDPRD;		   /*< 0x0026 eQEP Watchdog Period*/
  uint16		QDECCTL;	   /*< 0x0028 eQEP Decoder Control*/
  uint16		QEPCTL;		   /*< 0x002A eQEP Control*/
  uint16		QCAPCTL;	   /*< 0x002C eQEP Capture Control*/
  uint16		QPOSCTL;	   /*< 0x002E eQEP Position Compare Control*/
  uint16		QEINT;		   /*< 0x0030 eQEP Interrupt Enable Register*/
  uint16		QFLG;		   /*< 0x0032 eQEP Interrupt Flag Register*/
  uint16		QCLR;		   /*< 0x0034 eQEP Interrupt Clear Register*/
  uint16		QFRC;		   /*< 0x0036 eQEP Interrupt Force Register*/
  uint16		QEPSTS;		   /*< 0x0038 eQEP Status Register*/
  uint16		QCTMR;		   /*< 0x003A eQEP Capture Timer*/
  uint16		QCPRD;		   /*< 0x003C eQEP Capture Period*/
  uint16		QCTMRLAT;	   /*< 0x003E eQEP Capture Timer Latch*/
  uint16		QCPRDLAT;	   /*< 0x0040 eQEP Capture Period Latch*/
  uint16		rsvd_1;	       /*< 0x0042 Reserved*/
} eqepBASE_t;

#else

typedef struct eqepBASE
{
  uint32      QPOSCNT;       /*< 0x0000 eQEP Position Counter*/
  uint32      QPOSINIT;      /*< 0x0004 eQEP Initialization Position Count*/
  uint32      QPOSMAX;       /*< 0x0008 eQEP Maximum Position Count*/
  uint32      QPOSCMP;       /*< 0x000C eQEP Position Compare*/
  uint32      QPOSILAT;      /*< 0x0010 eQEP Index Position Latch*/
  uint32      QPOSSLAT;      /*< 0x0014 eQEP Strobe Position Latch*/
  uint32      QPOSLAT;       /*< 0x0018 eQEP Position Latch*/
  uint32      QUTMR;         /*< 0x001C eQEP Unit Timer*/
  uint32      QUPRD;         /*< 0x0020 eQEP Unit Period*/
  uint16		QWDPRD;		   /*< 0x0026 eQEP Watchdog Period*/
  uint16		QWDTMR;		   /*< 0x0024 eQEP Watchdog Timer*/
  uint16		QEPCTL;		   /*< 0x002A eQEP Control*/
  uint16		QDECCTL;	   /*< 0x0028 eQEP Decoder Control*/
  uint16		QPOSCTL;	   /*< 0x002E eQEP Position Compare Control*/
  uint16		QCAPCTL;	   /*< 0x002C eQEP Capture Control*/
  uint16		QFLG;		   /*< 0x0032 eQEP Interrupt Flag Register*/
  uint16		QEINT;		   /*< 0x0030 eQEP Interrupt Enable Register*/
  uint16		QFRC;		   /*< 0x0036 eQEP Interrupt Force Register*/
  uint16		QCLR;		   /*< 0x0034 eQEP Interrupt Clear Register*/
  uint16		QCTMR;		   /*< 0x003A eQEP Capture Timer*/
  uint16		QEPSTS;		   /*< 0x0038 eQEP Status Register*/
  uint16		QCTMRLAT;	   /*< 0x003E eQEP Capture Timer Latch*/
  uint16		QCPRD;		   /*< 0x003C eQEP Capture Period*/
  uint16		rsvd_1;	       /*< 0x0042 Reserved*/
  uint16		QCPRDLAT;	   /*< 0x0040 eQEP Capture Period Latch*/
} eqepBASE_t;

#endif

/** @def eqepREG1
*   @brief eQEP1 Register Frame Pointer
*
*   This pointer is used by the eQEP driver to access the eQEP1 registers.
*/
#define eqepREG1 ((eqepBASE_t *)0xFFF79900U)


/* USER CODE BEGIN (1) */
/* USER CODE END */


#endif
