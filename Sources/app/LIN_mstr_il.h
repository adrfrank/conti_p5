/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         LIN_mstr_il.h
* version:         1.0 
* created_by:      Carlos Calvillo
* date_created:    Oct 21, 2013
*=============================================================================*/
/* DESCRIPTION : LIN Master Node Interaction Layer (IL) Header File           */
/*============================================================================*/
/* FUNCTION COMMENT :  TBD                                                    */
/*                                                                            */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 20/10/2013  |                               | Carlos Calvillo  */
/*  First Implementation.                                                     */
/*============================================================================*/

#ifndef LIN_IL_H_
#define LIN_IL_H_

#include "LIN_common.h"
#include "LIN_mstr_network.h"
#include "LIN_signals.h"

#if COMPILE_LIN_MASTER_NODE


extern void linmstr_callback_MASTER_CMD_ALL();
extern void linmstr_callback_MASTER_CMD_SLV1();
extern void linmstr_callback_MASTER_CMD_SLV2();
extern void linmstr_callback_MASTER_CMD_SLV3();
extern void linmstr_callback_MASTER_CMD_SLV4();
extern void linmstr_callback_SLAVE1_RSP();
extern void linmstr_callback_SLAVE2_RSP();
extern void linmstr_callback_SLAVE3_RSP();
extern void linmstr_callback_SLAVE4_RSP();
extern void linmstr_callback_SLAVE1_ID();
extern void linmstr_callback_SLAVE2_ID();
extern void linmstr_callback_SLAVE3_ID();
extern void linmstr_callback_SLAVE4_ID();

#endif

#endif /* LIN_IL_H_ */
