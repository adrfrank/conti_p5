/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        LIN_slave_core.h
* version:         1.0 
* created_by:      Carlos Calvillo
* date_created:    Nov 1, 2013
*=============================================================================*/
/* DESCRIPTION : LIN slave node Core functionality Header File                */
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
#ifndef LIN_SLAVE_CORE_H_
#define LIN_SLAVE_CORE_H_


/* Definition of LIN slave states */
typedef enum{
	LINSLV_IDLE, /* TODO: Put your LIN slave states here! */
	LINSLV_RX_SYNCH,
	LINSLV_RX_ID,
	LINSLV_END_OF_HEADER,
	LINSLV_TX_DATA,
	LINSLV_TX_CHKSUM,
	LINSLV_RX_DATA,
	LINSLV_RX_CHKSUM
}E_LINSLV_STATE;

/* Definition of LIN communication events */
typedef enum{
	LINSLV_EV_BREAK_DETECTED,
	LINSLV_EV_TX_OK,
	LINSLV_EV_RX_OK,
	LINSLV_EV_TIMEOUT,
	LINSLV_EV_ERROR
}E_LINSLV_COMM_EVENTS;

extern void linslv_init();
extern void linslv_slaveStateMachine(E_LINSLV_COMM_EVENTS le_event);
extern E_LINSLV_STATE linslv_getSlvState(void);

/* callbacks */
extern void linslv_timeout_error_callback();
extern void linslv_checksum_error_callback();
extern void linslv_ID_parity_error_callback();
extern void linslv_synch_error_callback();

#endif /* LIN_SLAVE_CORE_H_ */
