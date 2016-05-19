/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        LIN_mstr_il.c
* version:         1.0 
* created_by:      Carlos Calvillo
* date_created:    Oct 21, 2013
*=============================================================================*/
/* DESCRIPTION : LIN Master Node Interaction Layer (IL)                       */
/*============================================================================*/
/* FUNCTION COMMENT :  All functions for the Interaction Layer should be      */
/* placed here. E.g., the callbacks for reception or transmission of the      */
/* LIN messages.                                                              */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 20/10/2013  |                               | Carlos Calvillo  */
/*  First Implementation.                                                     */
/*============================================================================*/

#include "LIN_mstr_il.h"
#include "LIN_mstr_core.h"
#include "LIN_mstr_sched.h"

#if COMPILE_LIN_MASTER_NODE

/* ------------------------------------------------------------------------- */
//     LIN Master Node Error Callbacks:
//     Called upon transmission or reception of a LIN msg (called inside an ISR so shall be short)
/* ------------------------------------------------------------------------- */
void linmstr_timeout_error_callback()
{
	
}
void linmstr_checksum_error_callback()
{
	
}
void linmstr_ID_parity_error_callback()
{
	
}

/* ------------------------------------------------------------------------- */
//     Msg Callbacks:
//     Called upon transmission or reception of a LIN msg (called inside an ISR so shall be short)
/* ------------------------------------------------------------------------- */
void linmstr_callback_MASTER_CMD_ALL()
{
	
}

void linmstr_callback_MASTER_CMD_SLV1()
{
	
}

void linmstr_callback_MASTER_CMD_SLV2()
{
	
}

void linmstr_callback_MASTER_CMD_SLV3()
{
	
}

void linmstr_callback_MASTER_CMD_SLV4()
{
	
}

void linmstr_callback_SLAVE1_RSP()
{
	
}

void linmstr_callback_SLAVE2_RSP()
{
	
}

void linmstr_callback_SLAVE3_RSP(){
	
}

void linmstr_callback_SLAVE4_RSP()
{
	
}

void linmstr_callback_SLAVE1_ID()
{
	
}

void linmstr_callback_SLAVE2_ID()
{
	
}

void linmstr_callback_SLAVE3_ID()
{
	
}

void linmstr_callback_SLAVE4_ID()
{
	
}

#endif
