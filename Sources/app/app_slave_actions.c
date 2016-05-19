/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        app_slave_actions.c
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

#include "app_slave_actions.h"
#include "LIN_slave_network.h"
#include "LIN_signals.h"

t_LEDstat re_LEDaction;
t_slv_stat re_SLVstatus;

/**************************************************************
 *  Name                 :	app_slvAct_writeSlvID 
 *  Description          : 	Function to simplify the assignation of the 
 *  						slave ID (supplier and Serial)
 *  Parameters           :  [Input] supplier
 *  						[Input] serialString. String for the serial, can be provided
 *  						in the form "AABBCC" where the string shall be 6 characters long.
 *  Return               :	none
 *  Critical/explanation :  No
 **************************************************************/
void app_slvAct_writeSlvID(T_UBYTE supplier, char * serialString)
{
	S_SLAVE1_ID ls_slave1_ID;
	T_UBYTE i;
	
	ls_slave1_ID.s.slave1_supplier = supplier;
	for(i=0; i<6; i++)
	{
		ls_slave1_ID.s.slave1_serial[i] = serialString[i];
	}
	
	linslv_TxUpdateMsgData(SLAVE1_ID, ls_slave1_ID.all);
}

/**************************************************************
 *  Name                 : 	app_slaveActions_init
 *  Description          :	Initializations for this application module
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void app_slaveActions_init()
{
	re_LEDaction = TOGGLING;
	re_SLVstatus = ENABLED;
	app_slvAct_writeSlvID(0xA5,"CFCC84");
}

/**************************************************************
 *  Name                 : 	app_slaveActions_task
 *  Description          :	Task that waits for LIN command messages for this
 *  						slave node and trigger the corresponding actions
 *  Parameters           :  none
 *  Return               :	none
 *  Critical/explanation :  Must be called periodically. Suggested period-> 20 ms
 **************************************************************/
void app_slaveActions_task()
{
	S_MASTER_CMD_ALL ls_mstrCmdForAll;
	S_MASTER_CMD_SLV1 ls_mstrCmdForSlv1;
	S_SLAVE1_RSP ls_slv1Rsp;
	t_cmdType le_command;
	
	le_command = cmd_NONE;
	
	if(GET_LINSLV_MSG_FLAG(MASTER_CMD_ALL))
	{
		/* Consume RX flag */
		SET_LINSLV_MSG_FLAG(MASTER_CMD_ALL,0);
		/* Get data */
		linslv_RxGetMsgData(MASTER_CMD_ALL, ls_mstrCmdForAll.all);
		/* Get command data */
		le_command = ls_mstrCmdForAll.s.master_cmdForAll;
	} 
	else if(GET_LINSLV_MSG_FLAG(MASTER_CMD_SLV1))
	{
		/* Consume RX flag */
		SET_LINSLV_MSG_FLAG(MASTER_CMD_SLV1,0);
		/* Get data */
		linslv_RxGetMsgData(MASTER_CMD_SLV1, ls_mstrCmdForSlv1.all);
		/* Get command data */
		le_command = ls_mstrCmdForSlv1.s.master_cmdForSlave1;
	}
	
	/* Act upon command */
	/* ---------------- */
	/* Enable command has priority over other commands */
	if(le_command == cmd_enable_slv)
	{
		/* Enable action command via LIN msgs */
		re_SLVstatus = ENABLED;
	}
	else if(le_command == cmd_disable_slv)
	{
		/* Disable action command via LIN msgs */
		re_SLVstatus = DISABLED;
	}
	else
	{
		if((re_SLVstatus == ENABLED) && (le_command != cmd_NONE))
		{
			switch(le_command)
			{
			case cmd_LED_on:
				re_LEDaction = ON;
				break;
			case cmd_LED_off:
				re_LEDaction = OFF;
				break;
			case cmd_LED_toggling:
				re_LEDaction = TOGGLING;
				break;
			default:
				break;
			}
			
		}
	}
	
	/* Update LIN signals/msg with status of slave1 */
	ls_slv1Rsp.s.slave1_enabled = re_SLVstatus;
	ls_slv1Rsp.s.slave1_LEDstat = re_LEDaction;
	linslv_TxUpdateMsgData(SLAVE1_RSP, ls_slv1Rsp.all);
}
