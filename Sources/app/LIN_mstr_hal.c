/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        LIN_mstr_hal.c
* version:         1.0 
* created_by:      Carlos Calvillo
* date_created:    20/10/2013
*=============================================================================*/
/* DESCRIPTION : LIN Master Node Hardware Abstraction Layer (HAL)             */
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

/* LIN HAL interfaces */
#include "LIN_common.h"
#include "LIN_mstr_hal.h"
#include "LIN_mstr_core.h"
#include "UART_hal.h"

#if COMPILE_LIN_MASTER_NODE

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void linMstrHal_initSerialHW(void)
{
	uart0_initHal(9600u);
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
T_UBYTE linMstrHal_start(void)
{
	UART0_ENABLE_TX_RX();
	return (1);
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
T_UBYTE linMstrHal_stop(void)
{
	UART0_DISABLE_TX_RX();
	return (1);
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void linMstrHal_sendBrake(void)
{
	uart0_sendBreak();
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void linMstrHal_sendByte(T_UBYTE lub_data)
{
	uart0_sendByte(lub_data);
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
T_UBYTE linMstrHal_receivedByte(void)
{
	T_UBYTE lub_data;
	lub_data = uart0_getByte();
	return (lub_data);
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void linMstrHal_TxISR(void)
{
	linmstr_masterStateMachine(LINMSTR_EV_TX_OK);
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void linMstrHal_RxISR(void)
{
	linmstr_masterStateMachine(LINMSTR_EV_RX_OK);
}

#endif
