/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        LIN_mstr_core.h
* version:         1.0 
* created_by:      Carlos Calvillo
* date_created:    19/09/2013
*=============================================================================*/
/* DESCRIPTION : LIN Master Core functionality Header File                    */
/*============================================================================*/
/* FUNCTION COMMENT : This file is intended to contain the core functionality */
/* of the LIN master node.                                                    */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 20/10/2013  |                               | Carlos Calvillo  */
/*  First Implementation.                                                     */
/*============================================================================*/
#ifndef LIN_MSTR_CORE_H_
#define LIN_MSTR_CORE_H_

#include "LIN_common.h"
#include "LIN_mstr_network.h"

#if COMPILE_LIN_MASTER_NODE

/* Definition of LIN master states */
typedef enum{
	LINMSTR_IDLE,
	LINMSTR_TX_SYNCH,
	LINMSTR_TX_ID,
	LINMSTR_END_OF_HEADER,
	LINMSTR_TX_DATA,
	LINMSTR_TX_CHKSUM,
	LINMSTR_RX_DATA,
	LINMSTR_RX_CHKSUM
}E_LINMSTR_STATE;

/* Definition of LIN communication events */
typedef enum{
	LINMSTR_EV_TX_START,
	LINMSTR_EV_TX_OK,
	LINMSTR_EV_RX_OK,
	LINMSTR_EV_TIMEOUT,
	LINMSTR_EV_ERROR
}E_LIN_COMM_EVENTS;

extern E_LINMSTR_MSGS re_currentMsg;

extern void linmstr_coreInit();
extern void linmstr_masterStateMachine(E_LIN_COMM_EVENTS le_event);
extern E_LINMSTR_STATE linmstr_getMstrState(void);

/* callbacks */
extern void linmstr_timeout_error_callback();
extern void linmstr_checksum_error_callback();
extern void linmstr_ID_parity_error_callback();

#endif

#endif /* LIN_MSTR_CORE_H_ */
