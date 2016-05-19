/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        LIN_mstr_sched.h
* version:         1.0 
* created_by:      Carlos Calvillo
* date_created:    Nov 19, 2013
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

#ifndef LIN_MSTR_SCHED_H_
#define LIN_MSTR_SCHED_H_

#include "stdtypedef.h"
#include "LIN_common.h"
#include "LIN_mstr_network.h"

#if COMPILE_LIN_MASTER_NODE

/* ---------------------------------------------------- */
/* Common definitions for scheduling tables             */
/* ---------------------------------------------------- */
typedef struct{
	E_LINMSTR_MSGS slotMsg;
	T_UBYTE slotTicks;
}S_LIN_SCHD_SLOT;

typedef struct{
	const S_LIN_SCHD_SLOT* schdTablePtr;
	T_UBYTE schdTableSize;	
	T_UBYTE allowsInterrupt;
}S_SCHD_TABLE_STAT_INFO;


/* ---------------------------------------------------- */
/* Network-specific information about scheduling tables */
/* ---------------------------------------------------- */

/* List of scheduling tables */
typedef enum{
	sched_SlvIDs,
	sched_SlvCmdAndStats,
	sched_AllCmd,
	sched_testing,
	N_OF_SCHD_TABLES
}E_LIN_SCHD_TABLES;

/* Size (number of slots) of scheduling tables */
#define LIN_SCHD_SIZE_sched_SlvIDs				4
#define LIN_SCHD_SIZE_sched_SlvCmdAndStats		8
#define LIN_SCHD_SIZE_sched_AllCmd				5
#define LIN_SCHD_SIZE_sched_testing				17

extern const S_SCHD_TABLE_STAT_INFO ras_schdTableStaticData[N_OF_SCHD_TABLES];


/* ---------------------------------------------------- */
/* Exported functions                                   */
/* ---------------------------------------------------- */
extern void linmstr_schedInit();
extern void linmstr_schdTableTask();
extern void linmstr_changeSchdTable(E_LIN_SCHD_TABLES le_newSchdTable);
extern void linmstr_callback_schdChanged();
extern void linmstr_callback_schdEnd();


#endif

#endif /* LIN_MSTR_SCHED_H_ */
