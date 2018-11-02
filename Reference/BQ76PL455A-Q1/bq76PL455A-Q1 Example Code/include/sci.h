/** @file sci.h
*   @brief SCI Driver Definition File
*   @date 25.July.2013
*   @version 03.06.00
*   
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */


#ifndef __SCI_H__
#define __SCI_H__

#include "reg_sci.h"


/** @enum sciIntFlags
*   @brief Interrupt Flag Definitions
*
*   Used with sciEnableNotification, sciDisableNotification
*/
enum sciIntFlags
{
    SCI_FE_INT    = 0x04000000U,  /* framing error */
    SCI_OE_INT    = 0x02000000U,  /* overrun error */
    SCI_PE_INT    = 0x01000000U,  /* parity error */
    SCI_RX_INT    = 0x00000200U,  /* receive buffer ready */
    SCI_TX_INT    = 0x00000100U,  /* transmit buffer ready */
    SCI_WAKE_INT  = 0x00000002U,  /* wakeup */
    SCI_BREAK_INT = 0x00000001U   /* break detect */
};

/** @def SCI_IDLE
*   @brief Alias name for the SCI IDLE Flag
*
*   This is an alias name for the SCI IDLE Flag.
*
*/
#define SCI_IDLE 0x00000004U

/** @struct sciBase
*   @brief SCI Register Definition
*
*   This structure is used to access the SCI module registers.
*/
/** @typedef sciBASE_t
*   @brief SCI Register Frame Type Definition
*
*   This type is used to access the SCI Registers.
*/

enum sciPinSelect
{
    PIN_SCI_TX = 4U,
    PIN_SCI_RX = 2U
};


/* Configuration registers */
typedef struct sci_config_reg
{
    uint32 CONFIG_GCR0;
    uint32 CONFIG_GCR1;
    uint32 CONFIG_SETINT;
    uint32 CONFIG_SETINTLVL;
    uint32 CONFIG_FORMAT;
    uint32 CONFIG_BRS;
    uint32 CONFIG_PIO0;
    uint32 CONFIG_PIO1;
    uint32 CONFIG_PIO6;
    uint32 CONFIG_PIO7;	
	uint32 CONFIG_PIO8;
} sci_config_reg_t;


/* Configuration registers initial value for SCI*/
#define SCILIN_GCR0_CONFIGVALUE       0x00000001U   
#define SCILIN_GCR1_CONFIGVALUE    ((1U << 5U) \
                                 | ((1U-1U) << 4U) \
                                 | (0U << 3U) \
                                 | (0U << 2U) \
                                 | (1U << 1U) \
                                 | (0U << 2U) \
                                 | 0x03000080U)
#define SCILIN_SETINTLVL_CONFIGVALUE  ((0U << 26U) \
                                 | (0U << 25U) \
                                 | (0U << 24U) \
                                 | (0U << 9U) \
                                 | (0U << 8U) \
                                 | (0U << 1U) \
                                 | (0U))

#define SCILIN_SETINT_CONFIGVALUE ((0U << 26U) \
                                 | (0U << 25U) \
                                 | (0U << 24U) \
                                 | (1U << 9U) \
                                 | (0U << 1U) \
                                 | (0U))

#define SCILIN_FORMAT_CONFIGVALUE     (8U - 1U)
#define SCILIN_BRS_CONFIGVALUE        (19U)
#define SCILIN_PIO0_CONFIGVALUE       (1U | 1U | 0U)
#define SCILIN_PIO1_CONFIGVALUE       (1U | 0U | 0U)
#define SCILIN_PIO6_CONFIGVALUE       (0U | 0U | 0U)
#define SCILIN_PIO7_CONFIGVALUE       (1U | 1U | 0U)
#define SCILIN_PIO8_CONFIGVALUE       (1U | 1U | 1U)
 
/** 
 *  @defgroup SCI SCI
 *  @brief Serial Communication Interface Module.
 *  
 *  The SCI module is a universal asynchronous receiver-transmitter that implements the standard nonreturn
 *  to zero format. The SCI can be used to communicate, for example, through an RS-232 port or over a K-line.
 *
 *	Related Files
 *   - reg_sci.h
 *   - sci.h
 *   - sci.c
 *  @addtogroup SCI
 *  @{
 */
 
/* SCI Interface Functions */
void sciInit(void);
void sciSetFunctional(sciBASE_t *sci, uint32 port);
void sciSetBaudrate(sciBASE_t *sci, uint32 baud);
uint32  sciIsTxReady(sciBASE_t *sci);
void sciSendByte(sciBASE_t *sci, uint8 byte);
void sciSend(sciBASE_t *sci, uint32 length, uint8 * data);
uint32  sciIsRxReady(sciBASE_t *sci);
uint32  sciIsIdleDetected(sciBASE_t *sci);
uint32  sciRxError(sciBASE_t *sci);
uint32  sciReceiveByte(sciBASE_t *sci);
void sciReceive(sciBASE_t *sci, uint32 length, uint8 * data);
void sciEnableNotification(sciBASE_t *sci, uint32 flags);
void sciDisableNotification(sciBASE_t *sci, uint32 flags);
void sciEnableLoopback(sciBASE_t *sci, loopBackType_t Loopbacktype);
void sciDisableLoopback(sciBASE_t *sci);

void scilinGetConfigValue(sci_config_reg_t *config_reg, config_value_type_t type);
/** @fn void sciNotification(sciBASE_t *sci, uint32 flags)
*   @brief Interrupt callback
*   @param[in] sci   - sci module base address
*   @param[in] flags - copy of error interrupt flags
*
* This is a callback that is provided by the application and is called upon
* an interrupt.  The parameter passed to the callback is a copy of the 
* interrupt flag register.
*/
void sciNotification(sciBASE_t *sci, uint32 flags);

/**@}*/
#endif
