/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        LIN_slave_il.h
* version:         1.0 
* created_by:      Carlos Calvillo
* date_created:    Nov 1, 2013
*=============================================================================*/
/* DESCRIPTION : LIN slave node Interaction Layer (IL) Header File            */
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

#ifndef LIN_SLAVE_IL_H_
#define LIN_SLAVE_IL_H_

extern void linslv_callback_MASTER_CMD_ALL();
extern void linslv_callback_MASTER_CMD_SLV1();
extern void linslv_callback_SLAVE1_RSP();
extern void linslv_callback_SLAVE1_ID();

#endif /* LIN_SLAVE_IL_H_ */
