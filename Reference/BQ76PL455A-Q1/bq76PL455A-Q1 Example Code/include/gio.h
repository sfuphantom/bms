/** @file gio.h
*   @brief GIO Driver Definition File
*   @date 25.July.2013
*   @version 03.06.00
*   
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __GIO_H__
#define __GIO_H__

#include "reg_gio.h"

typedef struct gio_config_reg
{
    uint32 CONFIG_INTDET;
    uint32 CONFIG_POL;
    uint32 CONFIG_INTENASET;
    uint32 CONFIG_LVLSET;
	
	uint32 CONFIG_PORTADIR;
	uint32 CONFIG_PORTAPDR;
	uint32 CONFIG_PORTAPSL;
	uint32 CONFIG_PORTAPULDIS;
	
	uint32 CONFIG_PORTBDIR;
	uint32 CONFIG_PORTBPDR;
	uint32 CONFIG_PORTBPSL;
	uint32 CONFIG_PORTBPULDIS;
}gio_config_reg_t;

#define GIO_INTDET_CONFIGVALUE		0U
#define GIO_POL_CONFIGVALUE			(0U   \
								| (0U << 1U) \
								| (0U << 2U) \
								| (0U << 3U) \
								| (0U << 4U) \
								| (0U << 5U) \
								| (0U << 6U) \
								| (0U << 7U) \
															      \
								| (0U << 8U) \
								| (0U << 9U) \
								| (0U << 10U)\
								| (0U << 11U)\
								| (0U << 12U)\
								| (0U << 13U)\
								| (0U << 14U)\
								| (0U << 15U))


#define GIO_INTENASET_CONFIGVALUE (0U        \
								| (0U << 1U) \
								| (0U << 2U) \
								| (0U << 3U) \
								| (0U << 4U) \
								| (0U << 5U) \
								| (0U << 6U) \
								| (0U << 7U) \
			                                                      \
								| (0U << 8U) \
								| (0U << 9U) \
								| (0U << 10U)\
								| (0U << 11U)\
								| (0U << 12U)\
								| (0U << 13U)\
								| (0U << 14U)\
								| (0U << 15U))

#define GIO_LVLSET_CONFIGVALUE    (0U         \
								| (0U << 1U) \
								| (0U << 2U) \
								| (0U << 3U) \
								| (0U << 4U) \
								| (0U << 5U) \
								| (0U << 6U) \
								| (0U << 7U) \
				                                                  \
								| (0U << 8U) \
								| (0U << 9U) \
								| (0U << 10U)\
								| (0U << 11U)\
								| (0U << 12U)\
								| (0U << 13U)\
								| (0U << 14U)\
								| (0U << 15U))                     
				                                                  
#define GIO_PORTADIR_CONFIGVALUE	(1U | (0U << 1U) | (0U << 2U) | (0U << 3U) | (0U << 4U) | (0U << 5U) | (0U << 6U) | (0U << 7U))
#define GIO_PORTAPDR_CONFIGVALUE	0U | (0U << 1U) | (0U << 2U) | (0U << 3U) | (0U << 4U) | (0U << 5U) | (0U << 6U) | (0U << 7U)
#define GIO_PORTAPSL_CONFIGVALUE	0U | (0U << 1U) | (0U << 2U) |(0U << 3U) | (0U << 4U) | (0U << 5U) | (0U << 6U) | (0U << 7U)
#define GIO_PORTAPULDIS_CONFIGVALUE	 0U | (0U << 1U) | (0U << 2U) |(0U << 3U) | (0U << 4U) | (0U << 5U) | (0U << 6U) | (0U << 7U)
	
#define GIO_PORTBDIR_CONFIGVALUE	(0U | (0U << 1U) | (0U << 2U) | (0U << 3U) | (0U << 4U) | (0U << 5U) | (0U << 6U) | (0U << 7U))
#define GIO_PORTBPDR_CONFIGVALUE	0U | (0U << 1U) | (0U << 2U) | (0U << 3U) | (0U << 4U) | (0U << 5U) | (0U << 6U) | (0U << 7U)
#define GIO_PORTBPSL_CONFIGVALUE	0U | (0U << 1U) | (0U << 2U) |(0U << 3U) | (0U << 4U) | (0U << 5U) | (0U << 6U) | (0U << 7U)
#define GIO_PORTBPULDIS_CONFIGVALUE	 0U | (0U << 1U) | (0U << 2U) |(0U << 3U) | (0U << 4U) | (0U << 5U) | (0U << 6U) | (0U << 7U)
	

/** 
 *  @defgroup GIO GIO
 *  @brief General-Purpose Input/Output Module.
 *  
 *  The GIO module provides the family of devices with input/output (I/O) capability. 
 *  The I/O pins are bidirectional and bit-programmable.
 *  The GIO module also supports external interrupt capability.
 *
 *	Related Files
 *   - reg_gio.h
 *   - gio.h
 *   - gio.c
 *  @addtogroup GIO
 *  @{
 */
 
/* GIO Interface Functions */
void gioInit(void);
void gioSetDirection(gioPORT_t *port, uint32 dir);
void gioSetBit(gioPORT_t *port, uint32 bit, uint32 value);
void gioSetPort(gioPORT_t *port, uint32 value);
uint32 gioGetBit(gioPORT_t *port, uint32 bit);
uint32 gioGetPort(gioPORT_t *port);
void gioToggleBit(gioPORT_t *port, uint32 bit);
void gioEnableNotification(gioPORT_t *port, uint32 bit);
void gioDisableNotification(gioPORT_t *port, uint32 bit);
void gioNotification(gioPORT_t *port, sint32 bit);
void gioGetConfigValue(gio_config_reg_t *config_reg, config_value_type_t type);

/**@}*/
#endif
