/** @file eqep.h
*   @brief EQEP Driver Header File
*   @date 25.July.2013
*   @version 03.06.00
*   
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __QEP_H__
#define __QEP_H__

#include "reg_eqep.h"


#ifdef __cplusplus
extern "C" {
#endif


#define QEP_BASE_ADDR                        (0x00006B00U)      /*<base address of QEP */

/*QDECCTL Register */
#define QEP_QDECCTL_QSRC					 (3U  << 14U)		/*<position counter source selection   */
#define QEP_QDECCTL_SOEN					 (1U  << 13U)		/*<sync output enable                  */
#define QEP_QDECCTL_SPSEL					 (1U  << 12U)		/*<sync output pin selection           */
#define QEP_QDECCTL_XCR						 (1U  << 11U)		/*<external clock rate                 */
#define QEP_QDECCTL_SWAP					 (1U  << 10U)		/*<swap quadrature clock inputs        */
#define QEP_QDECCTL_IGATE					 (1U  <<  9U)		/*<index pulse gating option           */
#define QEP_QDECCTL_QAP						 (1U  <<  8U)		/*<QEPA input polarity                 */
#define QEP_QDECCTL_QBP						 (1U  <<  7U)		/*<QEPB input polarity                 */
#define QEP_QDECCTL_QIP						 (1U  <<  6U)		/*<QEPI input polarity                 */
#define QEP_QDECCTL_QSP						 (1U  <<  5U)		/*<QEPS input polarity                 */

/*QEPCTL Register */
#define QEP_QEPCTL_FREESOFT					 ( 3U << 14U)		/*<emulation control bit                                          */
#define QEP_QEPCTL_PCRM						 ( 3U << 12U)		/*<emulation control bit                                          */
#define QEP_QEPCTL_SEI						 ( 3U << 10U)		/*<strobe event initialization of position counter                */
#define QEP_QEPCTL_IEI						 ( 3U <<  8U)		/*<index event initialization of position counter                 */
#define QEP_QEPCTL_SWI						 ( 1U <<  7U)		/*<software initialization of position counter                    */
#define QEP_QEPCTL_SEL						 ( 1U <<  6U)		/*<strobe event latch of position counter                         */
#define QEP_QEPCTL_IEL						 ( 3U <<  4U)		/*<index event latch of position counter (software index marker)  */
#define QEP_QEPCTL_QPEN						 ( 1U <<  3U)		/*<quad position counter enable/software reset                    */
#define QEP_QEPCTL_QCLM						 ( 1U <<  2U)		/*<QEP capture latch mode                                         */
#define QEP_QEPCTL_UTE						 ( 1U <<  1U)		/*<QEP unit timer enable                                          */
#define QEP_QEPCTL_WDE						 ( 1U <<  0U)		/*<watchdog timer enable                                          */
                                                                                                                                  
/*QPOSCTL Register */                                                                                                                
#define QEP_QPOSCTL_PCSHDW					 (   1U << 15U)	/*<position compare shadow enable                                     */
#define QEP_QPOSCTL_PCLOAD					 (   1U << 14U)	/*<position compare shadow load mode                                  */
#define QEP_QPOSCTL_PCPOL					 (   1U << 13U)	/*<load when QPOSCNT = QPOSCMP                                        */
#define QEP_QPOSCTL_PCE						 (   1U << 12U)	/*<position compare enable/disable                                    */
#define QEP_QPOSCTL_PCSPW					 (4095U <<  0U)	/*<selection position compare sync output pulse width                 */

/*QCAPCTL Register */
#define QEP_QCAPCTL_CEN						 (   1U << 15U)	/*<enable QEP capture                */
#define QEP_QCAPCTL_CCPS					 (   7U <<  4U)	/*<qep capture timer clock prescaler */ 
#define QEP_QCAPCTL_UPPS					 (  15U <<  0U)	/*<unit position event prescaler     */ 

/*QEINT Register */
#define QEP_QEINT_UTO						 (   1U << 11U)	/*<unit timeout interrupt enable                    */
#define QEP_QEINT_IEL						 (   1U << 10U)	/*<index event latch interrupt enable               */
#define QEP_QEINT_SEL						 (   1U <<  9U)	/*<strobe event latch	interrupt enable            */
#define QEP_QEINT_PCM						 (   1U <<  8U)	/*<position compare match interrupt enable	        */
#define QEP_QEINT_PCR						 (   1U <<  7U)	/*<position compare ready interrupt enable          */
#define QEP_QEINT_PCO						 (   1U <<  6U)	/*<position counter overflow interrupt enable       */
#define QEP_QEINT_PCU						 (   1U <<  5U)	/*<position counter underflow interrupt enable      */
#define QEP_QEINT_WTO						 (   1U <<  4U)	/*<watchdog time out interrupt enable               */
#define QEP_QEINT_QDC						 (   1U <<  3U)	/*<quadrature direction change interrupt enable     */
#define QEP_QEINT_QPE						 (   1U <<  2U)	/*<quadrature phase error interrupt enable          */
#define QEP_QEINT_PCE						 (   1U <<  1U)	/*<position counter error interrupt enable          */
																
/*QFLG Register */
#define QEP_QFLG_UTO						 (   1U << 11U)	/*<unit timeout interrupt flag                       */
#define QEP_QFLG_IEL						 (   1U << 10U)	/*<index event latch interrupt flag                  */
#define QEP_QFLG_SEL						 (   1U <<  9U)	/*<strobe event latch	interrupt flag               */
#define QEP_QFLG_PCM						 (   1U <<  8U)	/*<position compare match interrupt flag             */
#define QEP_QFLG_PCR						 (   1U <<  7U)	/*<position compare ready interrupt flag             */
#define QEP_QFLG_PCO						 (   1U <<  6U)	/*<position counter overflow interrupt flag          */
#define QEP_QFLG_PCU						 (   1U <<  5U)	/*<position counter underflow interrupt flag         */
#define QEP_QFLG_WTO						 (   1U <<  4U)	/*<watchdog time out interrupt flag                  */
#define QEP_QFLG_QDC						 (   1U <<  3U)	/*<quadrature direction change interrupt flag        */
#define QEP_QFLG_QPE						 (   1U <<  2U)	/*<quadrature phase error interrupt flag             */
#define QEP_QFLG_PCE						 (   1U <<  1U)	/*<position counter error interrupt flag             */

/*QCLR Register */
#define QEP_QCLR_UTO						 (   1U << 11U)	/*<clear unit timeout interrupt flag                  */
#define QEP_QCLR_IEL						 (   1U << 10U)	/*<clear index event latch interrupt flag             */
#define QEP_QCLR_SEL						 (   1U <<  9U)	/*<clear strobe event latch interrupt flag            */
#define QEP_QCLR_PCM						 (   1U <<  8U)	/*<clear position compare match interrupt flag        */
#define QEP_QCLR_PCR						 (   1U <<  7U)	/*<clear position compare ready interrupt flag        */
#define QEP_QCLR_PCO						 (   1U <<  6U)	/*<clear position counter overflow interrupt flag     */
#define QEP_QCLR_PCU						 (   1U <<  5U)	/*<clear position counter underflow interrupt flag    */
#define QEP_QCLR_WTO						 (   1U <<  4U)	/*<clear watchdog time out interrupt flag             */
#define QEP_QCLR_QDC						 (   1U <<  3U)	/*<clear quadrature direction change interrupt flag   */
#define QEP_QCLR_QPE						 (   1U <<  2U)	/*<clear quadrature phase error interrupt flag        */
#define QEP_QCLR_PCE						 (   1U <<  1U)	/*<clear position counter error interrupt flag        */

/*QFRC Register */
#define QEP_QFRC_UTO						 (   1U << 11U)	/*<force unit timeout interrupt                       */
#define QEP_QFRC_IEL						 (   1U << 10U)	/*<force index event latch interrupt                  */
#define QEP_QFRC_SEL						 (   1U <<  9U)	/*<force strobe event latch interrupt                 */
#define QEP_QFRC_PCM						 (   1U <<  8U)	/*<force position compare match interrupt             */
#define QEP_QFRC_PCR						 (   1U <<  7U)	/*<force position compare ready interrupt             */
#define QEP_QFRC_PCO						 (   1U <<  6U)	/*<force position counter overflow interrupt          */
#define QEP_QFRC_PCU						 (   1U <<  5U)	/*<force position counter underflow interrupt         */
#define QEP_QFRC_WTO						 (   1U <<  4U)	/*<force watchdog time out interrupt                  */
#define QEP_QFRC_QDC						 (   1U <<  3U)	/*<force quadrature direction change interrupt        */
#define QEP_QFRC_QPE						 (   1U <<  2U)	/*<force quadrature phase error interrupt             */
#define QEP_QFRC_PCE						 (   1U <<  1U)	/*<force position counter error interrupt             */

/*QEPSTS Register */
#define QEP_QEPSTS_UPEVNT					(   1U << 7U)		/*<unit position event flag                       */
#define QEP_QEPSTS_FDF						(   1U << 6U)		/*<direction on the first index marker            */
#define QEP_QEPSTS_QDF						(   1U << 5U)		/*<quadrature direction flag                      */
#define QEP_QEPSTS_QDLF						(   1U << 4U)		/*<direction latch flag                           */
#define QEP_QEPSTS_COEF						(   1U << 3U)		/*<capture overflow error flag                    */
#define QEP_QEPSTS_CDEF						(   1U << 2U)		/*<capture direction error flag                   */
#define QEP_QEPSTS_FIMF						(   1U << 1U)		/*<first index marker flag                        */
#define QEP_QEPSTS_PCEF						(   1U << 0U)		/*<position counter error flag                    */
                                                                                                                  
/*PC mode  */                                                                                                        
#define QEP_QUADRATURE_COUNT                 0x00U                                                                
#define QEP_DIRECTION_COUNT                  0x01U
#define QEP_UP_COUNT                         0x02U
#define QEP_DOWN_COUNT                       0x03U

/*External Clock Rate */ 
#define QEP_RESOLUTION_2x                    0x00U
#define QEP_RESOLUTION_1x                    0x01U

/*Direction */
#define QEP_CLOCKWISE                        0x01U
#define QEP_COUNTERCLOCKWISE                 0x01U

/*Edge */
#define QEP_RISING_EDGE                      0x00U
#define QEP_FALLING_EDGE                     0x01U
#define QEP_DIRECTON_DEPENDENT               0x01U

/*Index event latch of position counter */ 
#define QEP_LATCH_RISING_EDGE                0x01U
#define QEP_LATCH_FALLING_EDGE               0x02U
#define QEP_LATCH_SW_INDEX_MARKER            0x03U

/*Position counter reset mode */
#define QEP_INDEX_EVENT                      0x00U
#define QEP_MAX_POSITION                     0x01U
#define QEP_FIRST_INDEX_EVENT                0x02U
#define QEP_UNITTIME_EVENT                   0x03U

/*eQEP capture timer clock prescaler and Unit position event prescaler */
#define QEP_PS_1                             0x00U
#define QEP_PS_2                             0x01U
#define QEP_PS_4                             0x02U
#define QEP_PS_8                             0x03U
#define QEP_PS_16                            0x04U
#define QEP_PS_32                            0x05U
#define QEP_PS_64                            0x06U
#define QEP_PS_128                           0x07U
#define QEP_PS_256                           0x08U
#define QEP_PS_512                           0x09U
#define QEP_PS_1024                          0x0AU
#define QEP_PS_2048                          0x0BU

/*eQEP capture latch mode */
#define QEP_ON_POSITION_COUNTER_READ         0x00U
#define QEP_ON_UNIT_TIMOUT_EVENT             0x01U

/*Sync output pin selection */
#define QEP_INDEX_PIN                        0x00U
#define QEP_STROBE_PIN                       0x01U

/*Position-compare shadow load mode */
#define QEP_QPOSCNT_EQ_0                     0x00U
#define QEP_QPOSCNT_EQ_QPSCMP                0x01U

/*Polarity of sync output */
#define QEP_ACTIVE_HIGH                      0x00U
#define QEP_ACTIVE_LOW                       0x01U

/***************************************************************************
* the typedefs
*/
/** @brief QEP counting mode
*/
typedef enum
{
	QEP_Qsrc_Quad_Count_Mode=(0U << 14U),					/*<quadrature count mode                                          */
	QEP_Qsrc_Dir_Count_Mode=(1U << 14U),					/*<direction count mode                                           */
	QEP_Qsrc_Up_Count_Mode=(2U << 14U),						/*<up count mode for frequency measurement (QCLK=XCLK, QDIR=1U)   */
	QEP_Qsrc_Down_Count_Mode=(3U << 14U)					/*<down count mode for frequency measurement (QCLK=XCLK, QDIR=0U) */
} QEP_Qsrc_t;

/** @brief Sync output pin selection
*/
typedef enum
{	
	QEP_Spsel_Index_Pin_Sync_Output=(0U << 12U),			/*<index pin for sync output  */
	QEP_Spsel_Strobe_Pin_Sync_Output=(1U << 12U)			/*<strobe pin for sync output */ 
} QEP_Spsel_t;

/** @brief External clock rate
*/
typedef enum
{
	QEP_Xcr_2x_Res=(0U << 11U),								/*<2x resolution: count the rising/falling edge  */
	QEP_Xcr_1x_Res=(1U << 11U)								/*<1x resolution: count the rising edge only     */
} QEP_Xcr_t;

/** @brief Swap A/B channels
*/
typedef enum
{
	QEP_Swap_Not_Swapped=(0U << 10U),						/*<quad inputs not swapped  */
	QEP_Swap_Swapped=(1U << 10U)							/*<quad inputs swapped      */
} QEP_Swap_t;

/** @brief Index gating
*/
typedef enum
{
	QEP_Igate_Disable=(0U << 9U),							/*<disable gating of index pulse  */
	QEP_Igate_Enable=(1U << 9U)								/*<enable gating of index pulse   */
} QEP_Igate_t;

/** @brief Channel A polarity
*/
typedef enum
{
	QEP_Qap_No_Effect=(0U << 8U),							/*<no effect           */
	QEP_Qap_Inverted=(1U << 8U)								/*<negates QEPA input  */
} QEP_Qap_t;

/** @brief Channel B polarity
*/
typedef enum
{
	QEP_Qbp_No_Effect=(0U << 7U),							/*<no effect           */
	QEP_Qbp_Inverted=(1U << 7U)								/*<negates QEPB input  */
} QEP_Qbp_t;

/** @brief Index polarity
*/
typedef enum
{
	QEP_Qip_No_Effect=(0U << 6U),							/*<no effect          */
	QEP_Qip_Inverted=(1U << 6U)								/*<negates QEPI input */
} QEP_Qip_t;

/** @brief Channel S polarity
*/
typedef enum
{
	QEP_Qsp_No_Effect=(0U << 5U),							/*<no effect          */
	QEP_Qsp_Inverted=(1U << 5U)								/*<negates QEPS input */
} QEP_Qsp_t;

/** @brief Emulation control bits
*/
typedef enum
{
	QEPCTL_Freesoft_Immediate_Halt=(0U << 14U),				/*<position, watchdog, unit timer, capture timer stops immediately                                       */
	QEPCTL_Freesoft_Rollover_Halt=(1U << 14U),				/*<position, watchdog, unit timer continues until rollover, capture counts until next unit period event  */
	QEPCTL_Freesoft_Unaffected_Halt=(2U << 14U)				/*<position, watchdog, unit timer, capture timer unaffected by emu suspend                               */
} QEPCTL_Freesoft_t;

/** @brief Position counter reset mode
*/
typedef enum
{
	QEPCTL_Pcrm_Index_Reset=(0U << 12U),					/*<position counter reset on index event      */
	QEPCTL_Pcrm_Max_Reset=(1U << 12U),						/*<position counter reset on max position     */
	QEPCTL_Pcrm_First_Index_Reset=(2U << 12U),				/*<position counter reset on first index event*/
	QEPCTL_Pcrm_Unit_Time_Reset=(3U << 12U)					/*<position counter reset on unit time event  */
} QEPCTL_Pcrm_t;

/** @brief Strobe event initialization of position counter
*/
typedef enum
{ 
	QEPCTL_Sei_Nothing=(0U << 10U),							/*<does nothing                                       */
	QEPCTL_Sei_Rising_Edge_Init=(2U << 10U),				/*<initializes on rising edge of QEPS signal          */
	QEPCTL_Sei_Rising_Falling_Edge_Init=(3U << 10U)			/*<initializes on rising/falling edge of QEPS signal  */
} QEPCTL_Sei_t;

/** @brief Index event initialization of position counter
*/
typedef enum
{
	QEPCTL_Iei_Nothing=(0U << 8U),							/*<does nothing                               */
	QEPCTL_Iei_Rising_Edge_Init=(2U << 8U),					/*<initializes on rising edge of QEPI signal  */
	QEPCTL_Iei_Rising_Falling_Edge_Init=(3U << 8U)			/*<initializes on falling edge of QEPS signal */
} QEPCTL_Iei_t;

/** @brief Software initialization of position counter
*/
typedef enum
{
	QEPCTL_Swi_Nothing=(0U << 7U),							/*<does nothing                             */
	QEPCTL_Swi_Auto_Init_Counter=(1U << 7U)					/*<init position counter (QPOSCNT=QPOSINIT) */
} QEPCTL_Swi_t;

/** @brief Strobe event latch of position counter
*/
typedef enum
{
	QEPCTL_Sel_Rising_Edge=(0U << 6U),						/*<Position counter latched on rising edge of QEPS strobe (QPOSSLAT = POSCCNT)                    */
	QEPCTL_Sel_Rising_Falling_Edge=(1U << 6U)				/*<Clockwise: position counter latched on rising edge, counter clockwise: latched on falling edge */
} QEPCTL_Sel_t;
	
/** @brief Index event latch of position counter (software index marker)
*/
typedef enum
{
	QEPCTL_Iel_Rising_Edge=(1U << 4U),						/*<latches position counter on rising edge of index signal  */
	QEPCTL_Iel_Falling_Edge=(2U << 4U),						/*<ditto on falling edge of index signal                    */
	QEPCTL_Iel_Software_Index_Marker=(3U << 4U)				/*<software index marker.  See data sheet.                  */
} QEPCTL_Iel_t;

/** @brief QEP capture latch mode
*/
typedef enum
{
	QEPCTL_Qclm_Latch_on_CPU_Read=(0U << 2U),					/*<latch on position counter read by cpu  */
	QEPCTL_Qclm_Latch_on_Unit_Timeout=(1U << 2U)				/*<latch on unit time out                 */
} QEPCTL_Qclm_t;

/** @brief Position compare shadow enable
*/
typedef enum
{
	QPOSCTL_Pcshdw_Load_Immediate=(0U << 15U),				/*<shadow disabled, load immediate */
	QPOSCTL_Pcshdw_Shadow_Enabled=(1U << 15U)				/*<shadow enabled                  */
} QPOSCTL_Pcshdw_t;

/** @brief Position compare shadow load mode
*/
typedef enum
{
	QPOSCTL_Pcload_Load_Posn_Count_Zero=(0U << 14U),			/*<load on qposcnt = 0          */
	QPOSCTL_Pcload_Load_Posn_Count_Equal_Compare=(1U << 14U)	/*<load when qposcnt = qposcmp  */
} QPOSCTL_Pcload_t;

/** @brief Polarity of sync output
*/
typedef enum
{
	QPOSCTL_Pcpol_Active_High=(0U << 13U),					/*<active high pulse output  */
	QPOSCTL_Pcpol_Active_Low=(1U << 13U)					/*<active low pulse output   */
} QPOSCTL_Pcpol_t;

/** @brief QEP capture timer clock prescaler
*/
typedef enum
{
	QCAPCTL_Ccps_Capture_Div_1=(0U << 4U),					/*<capclk = sysclkout/1   */
	QCAPCTL_Ccps_Capture_Div_2=(1U << 4U),					/*<capclk = sysclkout/2   */
	QCAPCTL_Ccps_Capture_Div_4=(2U << 4U),					/*<capclk = sysclkout/4   */
	QCAPCTL_Ccps_Capture_Div_8=(3U << 4U),					/*<capclk = sysclkout/8   */
	QCAPCTL_Ccps_Capture_Div_16=(4U << 4U),					/*<capclk = sysclkout/16  */
	QCAPCTL_Ccps_Capture_Div_32=(5U << 4U),					/*<capclk = sysclkout/32  */
	QCAPCTL_Ccps_Capture_Div_64=(6U << 4U),					/*<capclk = sysclkout/64  */
	QCAPCTL_Ccps_Capture_Div_128=(7U << 4U)					/*<capclk = sysclkout/128 */
} QCAPCTL_Ccps_t;

/** @brief Unit position event prescaler
*/
typedef enum
{
	QCAPCTL_Upps_Div_1_Prescale=(0U << 0U),					/*<upevnt = qclk/1    */
	QCAPCTL_Upps_Div_2_Prescale=(1U << 0U),					/*<upevnt = qclk/2    */
	QCAPCTL_Upps_Div_4_Prescale=(2U << 0U),					/*<upevnt = qclk/4    */
	QCAPCTL_Upps_Div_8_Prescale=(3U << 0U),					/*<upevnt = qclk/8    */
	QCAPCTL_Upps_Div_16_Prescale=(4U << 0U),				/*<upevnt = qclk/16   */
	QCAPCTL_Upps_Div_32_Prescale=(5U << 0U),				/*<upevnt = qclk/32   */
	QCAPCTL_Upps_Div_64_Prescale=(6U << 0U),				/*<upevnt = qclk/64   */
	QCAPCTL_Upps_Div_128_Prescale=(7U << 0U),				/*<upevnt = qclk/128  */
	QCAPCTL_Upps_Div_256_Prescale=(8U << 0U),				/*<upevnt = qclk/256  */
	QCAPCTL_Upps_Div_512_Prescale=(9U << 0U),				/*<upevnt = qclk/512  */
	QCAPCTL_Upps_Div_1024_Prescale=(10U << 0U),				/*<upevnt = qclk/1024 */
	QCAPCTL_Upps_Div_2048_Prescale=(11U << 0U)				/*<upevnt = qclk/2048 */
} QCAPCTL_Upps_t;

/** @brief QEP interrupt enable flags
*/
typedef enum
{
	QEINT_Uto=(1U << 11U),									    /*<unit time out interrupt enable                      */
	QEINT_Iel=(1U << 10U),								     	/*<index event latch interrupt enable                  */
	QEINT_Sel=(1U << 9U),										/*<strobe event latch interrupt enable                 */
	QEINT_Pcm=(1U << 8U),										/*<position compare match interrupt enable             */
	QEINT_Pcr=(1U << 7U),										/*<position compare ready interrupt enable             */
	QEINT_Pco=(1U << 6U),										/*<position compare overflow interrupt enable          */
	QEINT_Pcu=(1U << 5U),										/*<position compare underflow interrupt enable         */
	QEINT_Wto=(1U << 4U),										/*<position compare watchdog time out interrupt enable */
	QEINT_Qdc=(1U << 3U),										/*<quadrature direction change interrupt enable        */
	QEINT_Qpe=(1U << 2U),										/*<quadrature phase error interrupt enable             */
	QEINT_Pce=(1U << 1U)										/*<position counter interrupt enable                   */
} QEINT_t;                                                                                                             
                                                                                                                      

/***************************************************************************/
/**
 *  @defgroup EQEP EQEP
 *  @brief Enhanced Quadrature Encoder Pulse Module
 *
 *  The enhanced quadrature encoder pulse (eQEP) module is used for direct interface with a linear or rotary
 *  incremental encoder to get position, direction, and speed information from a rotating machine for use in a
 *  high-performance motion and position-control system.
 *
 *	Related Files
 *   - reg_eqep.h
 *   - eqep.h
 *   - eqep.c
 *  @addtogroup EQEP
 *  @{
 */
 
/*the function prototypes*/

/** @brief Initialize QEP module
*/
void QEPInit(void);

/** @brief Clears all QEP interrupt flags
*   @param[in] eqep		Handle to QEP object
*/
void QEP_clear_all_interrupt_flags (eqepBASE_t *eqep);

/** @brief Clears a single interrupt flag
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEINT			Interrupt flag
*/
void QEP_clear_interrupt_flag (eqepBASE_t *eqep, const QEINT_t QEINT);

/** @brief Clears the position counter
*   @param[in] eqep		Handle to QEP object
*/
void QEP_clear_posn_counter (eqepBASE_t *eqep);

/** @brief Disables all interrupts
*   @param[in] eqep		Handle to QEP object
*/
void QEP_disable_all_interrupts (eqepBASE_t *eqep);

/** @brief Disable capture
*   @param[in] eqep		Handle to QEP object
*/
void QEP_disable_capture (eqepBASE_t *eqep);

/** @brief Disable gating of index pulse
*   @param[in] eqep		Handle to QEP object
*/
void QEP_disable_gate_index (eqepBASE_t *eqep);

/** @brief Disable individual interrupt
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEINT			Individual interrupts
*/
void QEP_disable_interrupt (eqepBASE_t *eqep, const QEINT_t QEINT);

/** @brief Disable position compare
*   @param[in] eqep		Handle to QEP object
*/
void QEP_disable_posn_compare (eqepBASE_t *eqep);

/** @brief Disable position compare shadowing
*   @param[in] eqep		Handle to QEP object
*/
void QEP_disable_posn_compare_shadow (eqepBASE_t *eqep);

/** @brief Disable output sync pulse
*   @param[in] eqep		Handle to QEP object
*/
void QEP_disable_sync_out (eqepBASE_t *eqep);

/** @brief Disable unit timer
*   @param[in] eqep		Handle to QEP object
*/
void QEP_disable_unit_timer (eqepBASE_t *eqep);

/** @brief Disable watchdog timer
*   @param[in] eqep		Handle to QEP object
*/
void QEP_disable_watchdog (eqepBASE_t *eqep);

/** @brief Enable capture
*   @param[in] eqep		Handle to QEP object
*/
void QEP_enable_capture (eqepBASE_t *eqep);

/** @brief Enable counter
*   @param[in] eqep		Handle to QEP object
*/
void QEP_enable_counter (eqepBASE_t *eqep);

/** @brief Enable gating of index pulse
*   @param[in] eqep		Handle to QEP object
*/
void QEP_enable_gate_index (eqepBASE_t *eqep);

/** @brief Enable individual interrupt
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEINT			Individual interrupts
*/
void QEP_enable_interrupt (eqepBASE_t *eqep, const QEINT_t QEINT);

/** @brief Enable position compare
*   @param[in] eqep		Handle to QEP object
*/
void QEP_enable_posn_compare (eqepBASE_t *eqep);

/** @brief Enable position compare shadowing
*   @param[in] eqep		Handle to QEP object
*/
void QEP_enable_posn_compare_shadow (eqepBASE_t *eqep);

/** @brief Enable output sync pulse
*   @param[in] eqep		Handle to QEP object
*/
void QEP_enable_sync_out (eqepBASE_t *eqep);

/** @brief Enable unit timer
*   @param[in] eqep		Handle to QEP object
*/
void QEP_enable_unit_timer (eqepBASE_t *eqep);

/** @brief Enable watchdog timer
*   @param[in] eqep		Handle to QEP object
*/
void QEP_enable_watchdog (eqepBASE_t *eqep);

/** @brief Manually force QEP interrupt
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEINT			Individual interrupt
*/
void QEP_force_interrupt (eqepBASE_t *eqep, const QEINT_t QEINT);


/** @brief Reads capture period latch
*   @param[in] eqep		Handle to QEP object
*   @return						Counter value
*/
uint16 QEP_read_capture_period_latch (eqepBASE_t *eqep);

/** @brief Reads timer latch
*   @param[in] eqep		Handle to QEP object
*   @return						Timer value
*/
uint16 QEP_read_capture_timer_latch (eqepBASE_t *eqep);

/** @brief Reads interrupt flag value
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEINT			Which interrupt to interrogate
*   @return						Interrupt flag value
*/
uint16 QEP_read_interrupt_flag (eqepBASE_t *eqep, const QEINT_t QEINT);

/** @brief Reads position compare register
*   @param[in] eqep		Handle to QEP object
*   @return						Counter value
*/
uint32 QEP_read_posn_compare (eqepBASE_t *eqep);

/** @brief Reads position counter
*   @param[in] eqep		Handle to QEP object
*   @return						Counter value
*/
uint32 QEP_read_posn_count (eqepBASE_t *eqep);

/** @brief Reads position counter value index pulse latch register
*   @param[in] eqep		Handle to QEP object
*   @return						Counter value
*/
uint32 QEP_read_posn_index_latch (eqepBASE_t *eqep);

/** @brief Reads position counter value
*   @param[in] eqep		Handle to QEP object
*   @return						Counter value
*/
uint32 QEP_read_posn_latch (eqepBASE_t *eqep);

/** @brief Reads position strobe latch
*   @param[in] eqep		Handle to QEP object
*   @return						Counter value
*/
uint32 QEP_read_posn_strobe_latch (eqepBASE_t *eqep);

/** @brief Reads status register
*   @param[in] eqep		Handle to QEP object
*   @return						Status register value
*/
uint16 QEP_read_status (eqepBASE_t *eqep);

/** @brief Resets counter
*   @param[in] eqep		Handle to QEP object
*/
void QEP_reset_counter (eqepBASE_t *eqep);

/** @brief Sets capture latch mode
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEPCTL_Qclm		capture latch mode
*/
void QEP_set_capture_latch_mode (eqepBASE_t *eqep, const QEPCTL_Qclm_t QEPCTL_Qclm);

/** @brief Sets capture period
*   @param[in] eqep		Handle to QEP object
*   @param[in] period			Capture period
*/
void QEP_set_capture_period (eqepBASE_t *eqep, const uint16 period);

/** @brief Sets capture pre-scaler
*   @param[in] eqep		Handle to QEP object
*   @param[in] QCAPCTL_Ccps		Capture pre-scaler 
*/
void QEP_set_capture_prescale (eqepBASE_t *eqep, const QCAPCTL_Ccps_t QCAPCTL_Ccps);

/** @brief Sets emulation control
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEPCTL_Freesoft	Emulation control bits
*/
void QEP_set_emu_control (eqepBASE_t *eqep, const QEPCTL_Freesoft_t QEPCTL_Freesoft);

/** @brief Sets external clock rate
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEP_Xcr			External clock rate
*/
void QEP_set_ext_clock_rate (eqepBASE_t *eqep, const QEP_Xcr_t QEP_Xcr);

/** @brief Sets the event which initializes the counter register
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEPCTL_Iei		Index event
*/
void QEP_set_index_event_init (eqepBASE_t *eqep, const QEPCTL_Iei_t QEPCTL_Iei);

/** @brief Sets the index event which latches the position counter 
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEPCTL_Iel		Latch event
*/
void QEP_set_index_event_latch (eqepBASE_t *eqep, const QEPCTL_Iel_t QEPCTL_Iel);

/** @brief Sets index polarity
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEP_Qip			Index polarity
*/
void QEP_set_index_polarity (eqepBASE_t *eqep, const QEP_Qip_t QEP_Qip);

/** @brief Sets max position count
*   @param[in] eqep		Handle to QEP object
*   @param[in] max_count		Maximum counter value
*/
void QEP_set_max_posn_count (eqepBASE_t *eqep, const uint32 max_count);

/** @brief Sets output pulse width when a match occur
*   @param[in] eqep		Handle to QEP object
*   @param[in] pulse_width		Pulse width value
*/
void QEP_set_posn_compare_pulse_width (eqepBASE_t *eqep, const uint16 pulse_width);

/** @brief Sets position compare shadow load mode
*   @param[in] eqep		Handle to QEP object
*   @param[in] QPOSCTL_Pcload	PC load event	
*/
void QEP_set_posn_compare_shadow_load (eqepBASE_t *eqep, const QPOSCTL_Pcload_t QPOSCTL_Pcload);

/** @brief Sets position counter reset mode
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEPCTL_Pcrm		Position counter reset mode
*/
void QEP_set_posn_count_reset_mode (eqepBASE_t *eqep, const QEPCTL_Pcrm_t QEPCTL_Pcrm);

/** @brief Sets initial position counter value
*   @param[in] eqep		Handle to QEP object
*   @param[in] init_count		initial counter value
*/
void QEP_set_posn_init_count (eqepBASE_t *eqep, const uint32 init_count);

/** @brief Selects whether index or strobe pin is used for sync output
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEP_SPsel		Selected pin
*/
void QEP_set_select_sync_pin (eqepBASE_t *eqep, const QEP_Spsel_t QEP_SPsel);

/** @brief Determines if software initialization of position counter enabled 
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEPCTL_Swi		Enable/disable position counter initialization
*/
void QEP_set_soft_init (eqepBASE_t *eqep, const QEPCTL_Swi_t QEPCTL_Swi);

/** @brief Determines strobe initialization of position counter 
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEPCTL_Sei		Strobe initialization of position counter (disabled, rising edge of QEPI) or rising/falling depending on direction
*/
void QEP_set_strobe_event_init (eqepBASE_t *eqep, const QEPCTL_Sei_t QEPCTL_Sei);

/** @brief Sets up strobe latch of position counter 
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEPCTL_Sel		Sets strobe latch of position counter
*/
void QEP_set_strobe_event_latch (eqepBASE_t *eqep, const QEPCTL_Sel_t QEPCTL_Sel);

/** @brief Sets up strobe polarity 
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEP_Qsp			Strobe polarity
*/
void QEP_set_strobe_polarity (eqepBASE_t *eqep, const QEP_Qsp_t QEP_Qsp);

/** @brief Sets up swapping of A/B channels
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEP_Swap			Swap/don't swap A/B channels
*/
void QEP_set_swap_quad_inputs (eqepBASE_t *eqep, QEP_Swap_t QEP_Swap);

/** @brief Sets synch output compare polarity
*   @param[in] eqep		Handle to QEP object
*   @param[in] QPOSCTL_Pcpol	Polarity of sync output
*/
void QEP_set_synch_output_compare_polarity (eqepBASE_t *eqep, const QPOSCTL_Pcpol_t QPOSCTL_Pcpol);

/** @brief Sets unit timer period
*   @param[in] eqep		Handle to QEP object
*   @param[in] unit_period		Unit period
*/
void QEP_set_unit_period (eqepBASE_t *eqep, const uint16 unit_period);

/** @brief Sets unit timer prescaling
*   @param[in] eqep		Handle to QEP object
*   @param[in] QCAPCTL_Upps		Unit timer prescaling
*/
void QEP_set_unit_posn_prescale (eqepBASE_t *eqep, const QCAPCTL_Upps_t QCAPCTL_Upps);

/** @brief Sets watchdog period
*   @param[in] eqep		Handle to QEP object
*   @param[in] watchdog_period	Watchdog period
*/
void QEP_set_watchdog_period (eqepBASE_t *eqep, const uint16 watchdog_period);

/** @brief Sets stobe event latch
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEPCTL_Sel	Sets strobe latch of position counter
*/
void QEP_setup_strobe_event_latch (eqepBASE_t *eqep, const QEPCTL_Sel_t QEPCTL_Sel);

/** @brief Sets A polarity
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEP_Qap			Channel A polarity
*/
void QEP_set_A_polarity (eqepBASE_t *eqep, const QEP_Qap_t QEP_Qap);

/** @brief Sets B polarity
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEP_Qbp			Channel B polarity
*/
void QEP_set_B_polarity (eqepBASE_t *eqep, const QEP_Qbp_t QEP_Qbp);

/** @brief QEP counting mode
*   @param[in] eqep		Handle to QEP object
*   @param[in] QEP_Qsrc			Sets QEP counting mode	
*/
void QEP_set_QEP_source (eqepBASE_t *eqep, const QEP_Qsrc_t QEP_Qsrc);

/** @brief Writes a value to the position compare register
*   @param[in] eqep		Handle to QEP object
*   @param[in] posn				Position compare register value
*/
void QEP_write_posn_compare (eqepBASE_t *eqep, const uint32 posn);

/** @brief Interrupt callback
*   @param[in] eqep		Handle to QEP object
*   @param[in] flags			Copy of  interrupt flags
*/
void 	eqepNotification(eqepBASE_t *eqep,uint16 flags);

/**@}*/
#ifdef __cplusplus
}
#endif /*extern "C" */



#endif /*end of _QEP_H_ definition */
