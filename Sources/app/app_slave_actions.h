/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        app_slave_actions.h
* version:         1.0 
* created_by:      Carlos Calvillo
* date_created:    Nov 17, 2013
*=============================================================================*/
/* DESCRIPTION :                                                              */
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

#ifndef APP_SLAVE_ACTIONS_H_
#define APP_SLAVE_ACTIONS_H_

#include "stdtypedef.h"
#include "LIN_signals.h"

extern t_LEDstat re_LEDaction;
extern t_slv_stat re_SLVstatus;


extern void app_slvAct_writeSlvID(T_UBYTE supplier, char * serialString);
extern void app_slaveActions_init();
extern void app_slaveActions_task();

#endif /* APP_SLAVE_ACTIONS_H_ */
