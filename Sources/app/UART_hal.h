/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        UART_hal.h
* version:         1.0 
* created_by:      Carlos Calvillo
* date_created:    20/10/2013
*=============================================================================*/
/* DESCRIPTION : UART Hardware Abstraction Layer (HAL) Header File            */
/*============================================================================*/
/* FUNCTION COMMENT : Implements the hardware interfaces for the UARTx        */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 20/10/2013  |                               | Carlos Calvillo  */
/*  First Implementation.                                                     */
/*============================================================================*/

#ifndef UART_HAL_H_
#define UART_HAL_H_

#include "stdtypedef.h"

typedef enum{
	UART0,
	UART1,
	UART2
}E_UART_DEV;

/* ------------------------------------------- */
/* UARTx hardware abstraction layer (HAL) APIs */
/* ------------------------------------------- */

/* Common for all UARTx */
/* -------------------- */
T_UBYTE uart_setBaudRate(E_UART_DEV le_uart, T_ULONG sysclk, T_ULONG lul_inBaud);

/* UART0 */
/* ----- */
extern T_UBYTE uart0_initHal(T_ULONG lul_baudRate);
extern T_UBYTE uart0_setBaudRate(T_ULONG sysclk, T_ULONG lul_inBaud);
extern T_UBYTE uart0_sendBreak();
extern T_UBYTE uart0_sendByte(T_UBYTE lub_data);
extern T_UBYTE uart0_getByte();

#define UART0_DISABLE_TX_RX()				(UART0_C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK))
#define UART0_ENABLE_TX_RX()				(UART0_C2 |= (UART0_C2_TE_MASK | UART0_C2_RE_MASK))

#define UART0_DISABLE_TX()				(UART0_C2 &= ~(UART0_C2_TE_MASK))
#define UART0_ENABLE_TX()				(UART0_C2 |= (UART0_C2_TE_MASK))
#define UART0_DISABLE_RX()				(UART0_C2 &= ~(UART0_C2_RE_MASK))
#define UART0_ENABLE_RX()				(UART0_C2 |= (UART0_C2_RE_MASK))

#define UART0_DISABLE_TX_RX_INT()			(UART0_C2 &= ~(UART0_C2_TCIE_MASK | UART0_C2_RIE_MASK))
#define UART0_ENABLE_TX_RX_INT()			(UART0_C2 |= (UART0_C2_TCIE_MASK | UART0_C2_RIE_MASK))

#define UART0_DISABLE_TX_INT()			(UART0_C2 &= ~(UART0_C2_TCIE_MASK))
#define UART0_ENABLE_TX_INT()			(UART0_C2 |= (UART0_C2_TCIE_MASK))
#define UART0_DISABLE_RX_INT()			(UART0_C2 &= ~(UART0_C2_RIE_MASK))
#define UART0_ENABLE_RX_INT()			(UART0_C2 |= (UART0_C2_RIE_MASK))

/* UART1 */
/* ----- */
extern T_UBYTE uart1_initHal(T_ULONG lul_baudRate);
extern T_UBYTE uart1_setBaudRate();
extern T_UBYTE uart1_sendBreak();
extern T_UBYTE uart1_sendByte(T_UBYTE lub_data);
extern T_UBYTE uart1_getByte();

#define UART1_DISABLE_TX_RX()				(UART1_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK))
#define UART1_ENABLE_TX_RX()				(UART1_C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK))

#define UART1_DISABLE_TX()				(UART1_C2 &= ~(UART_C2_TE_MASK))
#define UART1_ENABLE_TX()				(UART1_C2 |= (UART_C2_TE_MASK))
#define UART1_DISABLE_RX()				(UART1_C2 &= ~(UART_C2_RE_MASK))
#define UART1_ENABLE_RX()				(UART1_C2 |= (UART_C2_RE_MASK))

#define UART1_DISABLE_TX_RX_INT()			(UART1_C2 &= ~(UART_C2_TCIE_MASK | UART_C2_RIE_MASK))
#define UART1_ENABLE_TX_RX_INT()			(UART1_C2 |= (UART_C2_TCIE_MASK | UART_C2_RIE_MASK))

#define UART1_DISABLE_TX_INT()			(UART1_C2 &= ~(UART_C2_TCIE_MASK))
#define UART1_ENABLE_TX_INT()			(UART1_C2 |= (UART_C2_TCIE_MASK))
#define UART1_DISABLE_RX_INT()			UART1_C2 &= ~(UART_C2_RIE_MASK)
#define UART1_ENABLE_RX_INT()			UART1_C2 |= (UART_C2_RIE_MASK)

#define UART1_ENABLE_13BIT_BREAK_RX()			UART1_BDH |= (UART_BDH_SBNS_MASK | UART_BDH_LBKDIE_MASK); 	\
												UART1_C1 |= UART_C1_M_MASK; 		\
												UART1_S2 |= UART_S2_LBKDE_MASK

#define UART1_DISABLE_13BIT_BREAK_RX()			UART1_BDH &= ~(UART_BDH_SBNS_MASK | UART_BDH_LBKDIE_MASK);	\
												UART1_C1 &= ~(UART_C1_M_MASK); 		\
												UART1_S2 &= ~(UART_S2_LBKDE_MASK)

/* UART2 */
/* ----- */
#define UART2_DISABLE_TX_RX()				(UART2_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK))
#define UART2_ENABLE_TX_RX()				(UART2_C2 |= (UART_C2_TE_MASK /*| UART_C2_RE_MASK*/))

#define UART2_DISABLE_TX_RX_INT()			(UART2_C2 &= ~(UART_C2_TCIE_MASK | UART_C2_RIE_MASK))
#define UART2_ENABLE_TX_RX_INT()			(UART2_C2 |= (UART_C2_TCIE_MASK | UART_C2_RIE_MASK))

#define UART2_DISABLE_TX_INT()			(UART2_C2 &= ~(UART_C2_TCIE_MASK))
#define UART2_ENABLE_TX_INT()			(UART2_C2 |= (UART_C2_TCIE_MASK))
#define UART2_DISABLE_RX_INT()			UART2_C2 &= ~(UART_C2_RIE_MASK)
#define UART2_ENABLE_RX_INT()			UART2_C2 |= (UART_C2_RIE_MASK)

#define UART2_ENABLE_13BIT_BREAK_RX()			UART2_BDH |= (UART_BDH_SBNS_MASK | UART_BDH_LBKDIE_MASK); 	\
												UART2_C1 |= UART_C1_M_MASK; 		\
												UART2_S2 |= UART_S2_LBKDE_MASK

#define UART2_DISABLE_13BIT_BREAK_RX()			UART2_BDH &= ~(UART_BDH_SBNS_MASK | UART_BDH_LBKDIE_MASK);	\
												UART2_C1 &= ~(UART_C1_M_MASK); 		\
												UART2_S2 &= ~(UART_S2_LBKDE_MASK)


#endif /* UART_HAL_H_ */
