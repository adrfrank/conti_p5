/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        LIN_mstr_hal.h
* version:         1.0 
* created_by:      Carlos Calvillo
* date_created:    20/10/2013
*=============================================================================*/
/* DESCRIPTION : LIN Master Node Hardware Abstraction Layer (HAL) header file */
/*============================================================================*/
/* FUNCTION COMMENT :  This file is intended to implement all                 */
/* hardware-dependant functionality of the LIN driver                         */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 20/10/2013  |                               | Carlos Calvillo  */
/*  First Implementation.                                                     */
/*============================================================================*/

/*
 * LINhal.h
 *
 *  Created on: 20/10/2013
 *      Author: uidw7826
 */

#ifndef LINHAL_H_
#define LINHAL_H_

#include "LIN_common.h"
#include "UART_hal.h"

#if COMPILE_LIN_MASTER_NODE

extern void linMstrHal_initSerialHW(void);
extern T_UBYTE linMstrHal_start(void);
extern T_UBYTE linMstrHal_stop(void);
extern void linMstrHal_sendBrake(void);
extern void linMstrHal_sendByte(T_UBYTE lub_data);
extern T_UBYTE linMstrHal_receivedByte(void);
extern void linMstrHal_TxISR(void);
extern void linMstrHal_RxISR(void);

#define LINMSTR_HAL_ENABLE_TX_INT()			UART0_ENABLE_TX_INT()	
#define LINMSTR_HAL_DISABLE_TX_INT()		UART0_DISABLE_TX_INT()		
#define LINMSTR_HAL_ENABLE_RX_INT()			UART0_ENABLE_RX_INT()	
#define LINMSTR_HAL_DISABLE_RX_INT()		UART0_DISABLE_RX_INT()		

#endif

#endif /* LINHAL_H_ */
