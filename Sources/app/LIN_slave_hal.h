/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        LIN_slave_hal.h
* version:         1.0 
* created_by:      Carlos Calvillo
* date_created:    Nov 1, 2013
*=============================================================================*/
/* DESCRIPTION : LIN slave node Hardware Abstraction Layer (HAL) Header File  */
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      |             |                               | Carlos Calvillo  */
/*  First Implementation.                                                     */
/*============================================================================*/

#ifndef LIN_SLAVE_HAL_H_
#define LIN_SLAVE_HAL_H_

#include "LIN_common.h"
#include "UART_hal.h"

extern void linSlvHal_initSerialHW(void);
extern T_UBYTE linSlvHal_start(void);
extern T_UBYTE linSlvHal_stop(void);
extern void linSlvHal_sendBrake(void);
extern void linSlvHal_sendByte(T_UBYTE lub_data);
extern T_UBYTE linSlvHal_receivedByte(void);
extern void linSlvHal_TxISR(void);
extern void linSlvHal_RxISR(void);
extern void linSlvHal_RxBreakDetectedISR(void);

#define LINSLV_HAL_ENABLE_TX_INT()			UART1_ENABLE_TX_INT()	
#define LINSLV_HAL_DISABLE_TX_INT()			UART1_DISABLE_TX_INT()		
#define LINSLV_HAL_ENABLE_RX_INT()			UART1_ENABLE_RX_INT()	
#define LINSLV_HAL_DISABLE_RX_INT()			UART1_DISABLE_RX_INT()		

#define LINSLV_HAL_ENABLE_BREAK_RX()		UART1_ENABLE_13BIT_BREAK_RX()
#define LINSLV_HAL_DISABLE_BREAK_RX()		UART1_DISABLE_13BIT_BREAK_RX()

#endif /* LIN_SLAVE_HAL_H_ */
