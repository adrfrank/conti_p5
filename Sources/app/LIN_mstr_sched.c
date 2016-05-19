/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        LIN_mstr_sched.c
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
#include "LIN_mstr_sched.h"
#include "LIN_mstr_core.h"

#if COMPILE_LIN_MASTER_NODE

/* Scheduling Tables global variables */
/* ---------------------------------- */
T_UBYTE rub_schTableChangeRequested; /* Flag to indicate if a change of sched table has been requested */
E_LIN_SCHD_TABLES re_requestedSchdTable; /* The requested sched table */
E_LIN_SCHD_TABLES re_currentSchdTable; /* The currently active sched table */
T_SBYTE rsb_schdTableTickCntr; /* Tick counter to keep track of time for the sched table slots */
T_UBYTE rub_schdTableCurrentSlot; /* Current sched table slot being processed */

/* ------------------------------------------------------------------------------------ */
/*                      Definition of scheduling tables                                 */
/* ------------------------------------------------------------------------------------ */

/* List of messages and slot size (in ticks) for the table: sched_SlvIDs */
const S_LIN_SCHD_SLOT cs_schdTable_sched_SlvIDs[LIN_SCHD_SIZE_sched_SlvIDs] = {
		{SLAVE1_ID,			12},
		{SLAVE2_ID,			12},
		{SLAVE3_ID,			12},
		{SLAVE4_ID,			12}
};

/* List of messages and slot size (in ticks) for the table: sched_SlvIDs */
const S_LIN_SCHD_SLOT cs_schdTable_sched_SlvCmdAndStats[LIN_SCHD_SIZE_sched_SlvCmdAndStats] = {
		{MASTER_CMD_SLV1,		10},
		{SLAVE1_RSP,			10},
		{MASTER_CMD_SLV2,		10},
		{SLAVE2_RSP,			10},
		{MASTER_CMD_SLV3,		10},
		{SLAVE3_RSP,			10},
		{MASTER_CMD_SLV4,		10},
		{SLAVE4_RSP,			10}
};

/* List of messages and slot size (in ticks) for the table: sched_SlvIDs */
const S_LIN_SCHD_SLOT cs_schdTable_sched_AllCmd[LIN_SCHD_SIZE_sched_AllCmd] = {
		{MASTER_CMD_ALL,	10},
		{SLAVE1_RSP,		5},
		{SLAVE2_RSP,		5},
		{SLAVE3_RSP,		5},
		{SLAVE4_RSP,		5}
};

/* List of messages and slot size (in ticks) for the table: sched_testing */
const S_LIN_SCHD_SLOT cs_schdTable_sched_testing[LIN_SCHD_SIZE_sched_testing] = {
		{SLAVE1_ID,			12},
		{SLAVE2_ID,			12},
		{SLAVE3_ID,			12},
		{SLAVE4_ID,			12},
		{MASTER_CMD_SLV1,		10},
		{SLAVE1_RSP,			10},
		{MASTER_CMD_SLV2,		10},
		{SLAVE2_RSP,			10},
		{MASTER_CMD_SLV3,		10},
		{SLAVE3_RSP,			10},
		{MASTER_CMD_SLV4,		10},
		{SLAVE4_RSP,			10},
		{MASTER_CMD_ALL,	10},
		{SLAVE1_RSP,		5},
		{SLAVE2_RSP,		5},
		{SLAVE3_RSP,		5},
		{SLAVE4_RSP,		5}
};


/* Static information of scheduling tables: pointer to the table, size and whether or not it allows interruption (changing
 * to another scheduling table before it completes) */
const S_SCHD_TABLE_STAT_INFO ras_schdTableStaticData[N_OF_SCHD_TABLES] = {
     /* { schdTablePtr,								schdTableSize,							allowsInterrupt} */
		{cs_schdTable_sched_SlvIDs, 				LIN_SCHD_SIZE_sched_SlvIDs,				0},
		{cs_schdTable_sched_SlvCmdAndStats, 		LIN_SCHD_SIZE_sched_SlvCmdAndStats,		1},
		{cs_schdTable_sched_AllCmd,					LIN_SCHD_SIZE_sched_AllCmd,				0},
		{cs_schdTable_sched_testing,				LIN_SCHD_SIZE_sched_testing,			0}
};



/**************************************************************
 *  Name                 : linmstr_schedInit
 *  Description          : 
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : No
 **************************************************************/
void linmstr_schedInit()
{
	/* Initialize scheduling table stuff */
	rsb_schdTableTickCntr = 0;
	rub_schdTableCurrentSlot = 0;
	linmstr_changeSchdTable(sched_testing);
	
	/* initialize master core stuff */
	linmstr_coreInit();
}

/**************************************************************
 *  Name                 : linmstr_schdTableTask
 *  Description          : Periodic function that process the scheduling tables. 
 *  				       It executes the current sched table determined by variable re_currentSchdTable. It also performs the change
 *  				       of sched tables if requested.
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : It shall be called periodically with a cycle period equal to the one configured for the LIN network (e.g. 5ms/10ms)
 **************************************************************/
void linmstr_schdTableTask()
{
	/* Check if Slot tick counter has expired */
	if(rsb_schdTableTickCntr <= 0)
	{
		/* Ticks counter expired a new sched. table Slot is to be processed */
		/* Check for possible scheduling table change */
		if(rub_schTableChangeRequested)
		{
			if( (rub_schdTableCurrentSlot == 0) || ras_schdTableStaticData[re_currentSchdTable].allowsInterrupt )
			{
				/* Change is allowed always at beginning of sched table, i.e., when Slot is equal to 0.
				 * For other slots, change is only allowed if the current sched table permits interruptions, i.e. allowsInterrupt == TRUE */
				re_currentSchdTable = re_requestedSchdTable;
				rub_schdTableCurrentSlot = 0;
				rub_schTableChangeRequested = FALSE; /* Consume requesting flag */
				linmstr_callback_schdChanged(); /* Trigger callback that indicates a change in scheduling table */
			}
		}
		/* Trigger LIN message transmission */
		re_currentMsg = ras_schdTableStaticData[re_currentSchdTable].schdTablePtr[rub_schdTableCurrentSlot].slotMsg;
		linmstr_masterStateMachine(LINMSTR_EV_TX_START);
		/* Reload ticks counter */
		rsb_schdTableTickCntr = (ras_schdTableStaticData[re_currentSchdTable].schdTablePtr[rub_schdTableCurrentSlot].slotTicks - 1);
		/* Point to next scheduling table slot */
		rub_schdTableCurrentSlot++;
		if(rub_schdTableCurrentSlot >= ras_schdTableStaticData[re_currentSchdTable].schdTableSize)
		{
			/* If end of scheduling table reached its last Slot then set current slot to slot 0 */
			rub_schdTableCurrentSlot = 0;
			linmstr_callback_schdEnd(); /* Trigger callback that indicates the end of a scheduling table */
		}
	} 
	else
	{
		/* Decrement Slot ticks counter */
		rsb_schdTableTickCntr--;
	}
}

/**************************************************************
 *  Name                 : linmstr_changeSchdTable
 *  Description          : Function to request a change into the scheduling table. Depending on the settings of the
 *  					   currently active sched table this change may take place after the expiration of the current
 *  					   slot or it may take place once the current sched table has finished all its slots
 *  Parameters           : [in] le_newSchdTable -> New requested scheduling table. 
 *  Return               : none
 *  Critical/explanation : No
 **************************************************************/
void linmstr_changeSchdTable(E_LIN_SCHD_TABLES le_newSchdTable)
{
	/* Only request change of sched table if the requested table is different 
	 * than the current one.
	 */
	if(re_currentSchdTable != le_newSchdTable)
	{
		rub_schTableChangeRequested = TRUE;
		re_requestedSchdTable = le_newSchdTable;
	}
}

/**************************************************************
 *  Name                 : linmstr_callback_schdChanged
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void linmstr_callback_schdChanged()
{
	
}

/**************************************************************
 *  Name                 : linmstr_callback_schdEnd
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void linmstr_callback_schdEnd()
{	
	/*if(re_currentSchdTable == sched_SlvIDs || re_currentSchdTable == sched_testing)
	{
		linmstr_changeSchdTable(sched_SlvCmdAndStats);
	}*/
}

#endif
