/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        app_commander.c
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

#include "app_commander.h"
#include "LIN_mstr_sched.h"
#include "LIN_mstr_il.h"

#if COMPILE_LIN_MASTER_NODE

S_BUTTON rs_buttonSendCmd;
T_UWORD ruw_ledBlinkCntr;

t_LEDstat re_app_slv1_led_status;
t_LEDstat re_app_slv2_led_status;
t_LEDstat re_app_slv3_led_status;
t_LEDstat re_app_slv4_led_status;

T_UBYTE rub_bttnRlsdAt_1=0;
T_UBYTE rub_bttnRlsdAt_2=0;

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void app_commander_init(){
	
	/* Initialize button settings  */
	rs_buttonSendCmd.currentTicks = 0;
	rs_buttonSendCmd.debounce1Ticks = 5; /* 5 ticks = 50 ms */
	rs_buttonSendCmd.debounce2Ticks = 200; /* 200 ticks = 2000 ms */
	rs_buttonSendCmd.state = BTTN_NOT_DEBOUNCED;
	rs_buttonSendCmd.releasedAt1 = 0;
	rs_buttonSendCmd.releasedAt2 = 0;
	
	re_app_slv1_led_status = OFF;
	re_app_slv2_led_status = OFF;
	re_app_slv3_led_status = OFF;
	re_app_slv4_led_status = OFF;
	
	/* ---------------- */
	/* Initialize ports */
	/* ---------------- */

	/* Turn on clock to PortE module */
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;

	/* Configure input PINs */
	/* -------------------- */
	/* Set the appropriated pins multiplexer to GPIO mode */
	PORT_PCR_REG(PORTE_BASE_PTR,PIN_IN_CMD_0) = (PORT_PCR_MUX(1) | PORT_PCR_PE_MASK);
	PORT_PCR_REG(PORTE_BASE_PTR,PIN_IN_CMD_1) = (PORT_PCR_MUX(1) | PORT_PCR_PE_MASK);
	PORT_PCR_REG(PORTE_BASE_PTR,PIN_IN_CMD_2) = (PORT_PCR_MUX(1) | PORT_PCR_PE_MASK);
	PORT_PCR_REG(PORTE_BASE_PTR,PIN_IN_BUTTON) = (PORT_PCR_MUX(1) | PORT_PCR_PE_MASK);
	PORT_PCR_REG(PORTE_BASE_PTR,PIN_IN_TARGET_0) = (PORT_PCR_MUX(1) | PORT_PCR_PE_MASK);
	PORT_PCR_REG(PORTE_BASE_PTR,PIN_IN_TARGET_1) = (PORT_PCR_MUX(1) | PORT_PCR_PE_MASK);
	/* Set pins as inputs */
	GPIOE_PDDR &= ~((1 << PIN_IN_CMD_0) | (1 << PIN_IN_CMD_1) | (1 << PIN_IN_CMD_2) | (1 << PIN_IN_BUTTON) | (1 << PIN_IN_TARGET_0) | (1 << PIN_IN_TARGET_1)); 
	
	/* Configure output PINs */
	/* --------------------- */
	/* Set the appropriated pins multiplexer to GPIO mode */
	PORT_PCR_REG(PORTE_BASE_PTR,PIN_OUT_LED_SLV1) = PORT_PCR_MUX(1);
	PORT_PCR_REG(PORTE_BASE_PTR,PIN_OUT_LED_SLV2) = PORT_PCR_MUX(1);
	PORT_PCR_REG(PORTE_BASE_PTR,PIN_OUT_LED_SLV3) = PORT_PCR_MUX(1);
	PORT_PCR_REG(PORTE_BASE_PTR,PIN_OUT_LED_SLV4) = PORT_PCR_MUX(1);
	/* Set the initial output state to low */
	GPIOE_PCOR |= ((1 << PIN_OUT_LED_SLV1) | (1 << PIN_OUT_LED_SLV2) | (1 << PIN_OUT_LED_SLV3) | (1 << PIN_OUT_LED_SLV4));
	/* Set pins to outputs */
	GPIOE_PDDR |= ((1 << PIN_OUT_LED_SLV1) | (1 << PIN_OUT_LED_SLV2) | (1 << PIN_OUT_LED_SLV3) | (1 << PIN_OUT_LED_SLV4));
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void app_processButton(S_BUTTON * button, T_UBYTE currentValue)
{
	if(button->state == BTTN_NOT_DEBOUNCED)
	{
		if(currentValue){
			button->currentTicks++;
			if(button->currentTicks > button->debounce1Ticks){
				button->state = BTTN_DEBOUNCED1;
			}
		} else {
			/* Reset debounce counter */
			button->currentTicks = 0;
		}
	}
	else if(button->state == BTTN_DEBOUNCED1)
	{
		if(currentValue){
			button->currentTicks++;
			if(button->currentTicks > button->debounce2Ticks){
				button->state = BTTN_DEBOUNCED2;
			}
		} else {
			/* Reset debounce counter */
			button->currentTicks = 0;
			button->state = BTTN_NOT_DEBOUNCED;
			button->releasedAt1 = 1;
		}
	}
	else if(button->state == BTTN_DEBOUNCED2)
	{
		if(!currentValue){
			button->currentTicks = 0;
			button->state = BTTN_NOT_DEBOUNCED;
			button->releasedAt2 = 1;
		}	
	}
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation : To be called each 5 ms
 **************************************************************/
void app_commander_action_task()
{
	E_HL_COMMANDS command;
	T_UBYTE target;	
	S_MASTER_CMD_ALL ls_MstrCmdMsgForAll;
	S_MASTER_CMD_SLV1 ls_MstrCmdMsgForSlv1;
	S_MASTER_CMD_SLV2 ls_MstrCmdMsgForSlv2;
	S_MASTER_CMD_SLV3 ls_MstrCmdMsgForSlv3;
	S_MASTER_CMD_SLV4 ls_MstrCmdMsgForSlv4;
		 
	/* Debounce buttons */
	app_processButton(&rs_buttonSendCmd,HLC_READ_INPUT(PIN_IN_BUTTON));
	/* Execute commands if required */
	if(rs_buttonSendCmd.releasedAt1)
	{
		/* Button has been pressed and has been debounced and released at 1*/
		rs_buttonSendCmd.releasedAt1 = 0; // consume flag
		/* Get command from input pins */
		command = (E_HL_COMMANDS)((HLC_READ_INPUT(PIN_IN_CMD_2) << 2) | (HLC_READ_INPUT(PIN_IN_CMD_1) << 1) | HLC_READ_INPUT(PIN_IN_CMD_0));
		target = ((HLC_READ_INPUT(PIN_IN_TARGET_1) << 1) | HLC_READ_INPUT(PIN_IN_TARGET_0));
		
		/* TODO: remove following two lines. Those are just for testing purposes */
		//command = HLC_LED_TOGGLING;
		//target = 0;
		
		switch(command)
		{
		case HLC_NONE:
			break;
		case HLC_LED_ON:
			if(target == 0)
			{
				ls_MstrCmdMsgForSlv1.s.master_cmdForSlave1 = cmd_LED_on;
				linmstr_TxUpdateMsgData(MASTER_CMD_SLV1, ls_MstrCmdMsgForSlv1.all);
			} 
			else if(target == 1)
			{
				ls_MstrCmdMsgForSlv2.s.master_cmdForSlave2 = cmd_LED_on;
				linmstr_TxUpdateMsgData(MASTER_CMD_SLV2, ls_MstrCmdMsgForSlv2.all);
			}
			else if(target == 2)
			{
				ls_MstrCmdMsgForSlv3.s.master_cmdForSlave3 = cmd_LED_on;
				linmstr_TxUpdateMsgData(MASTER_CMD_SLV3, ls_MstrCmdMsgForSlv3.all);	
			}
			else if(target == 3)
			{
				ls_MstrCmdMsgForSlv4.s.master_cmdForSlave4 = cmd_LED_on;
				linmstr_TxUpdateMsgData(MASTER_CMD_SLV4, ls_MstrCmdMsgForSlv4.all);
			}
			else { }
			linmstr_changeSchdTable(sched_SlvCmdAndStats);
			break;
		case HLC_LED_OFF:
			if(target == 0)
			{
				ls_MstrCmdMsgForSlv1.s.master_cmdForSlave1 = cmd_LED_off;
				linmstr_TxUpdateMsgData(MASTER_CMD_SLV1, ls_MstrCmdMsgForSlv1.all);
			} 
			else if(target == 1)
			{
				ls_MstrCmdMsgForSlv2.s.master_cmdForSlave2 = cmd_LED_off;
				linmstr_TxUpdateMsgData(MASTER_CMD_SLV2, ls_MstrCmdMsgForSlv2.all);
			}
			else if(target == 2)
			{
				ls_MstrCmdMsgForSlv3.s.master_cmdForSlave3 = cmd_LED_off;
				linmstr_TxUpdateMsgData(MASTER_CMD_SLV3, ls_MstrCmdMsgForSlv3.all);	
			}
			else if(target == 3)
			{
				ls_MstrCmdMsgForSlv4.s.master_cmdForSlave4 = cmd_LED_off;
				linmstr_TxUpdateMsgData(MASTER_CMD_SLV4, ls_MstrCmdMsgForSlv4.all);
			}
			else { }
			linmstr_changeSchdTable(sched_SlvCmdAndStats);
			break;
		case HLC_LED_TOGGLING:
			if(target == 0)
			{
				ls_MstrCmdMsgForSlv1.s.master_cmdForSlave1 = cmd_LED_toggling;
				linmstr_TxUpdateMsgData(MASTER_CMD_SLV1, ls_MstrCmdMsgForSlv1.all);
			} 
			else if(target == 1)
			{
				ls_MstrCmdMsgForSlv2.s.master_cmdForSlave2 = cmd_LED_toggling;
				linmstr_TxUpdateMsgData(MASTER_CMD_SLV2, ls_MstrCmdMsgForSlv2.all);
			}
			else if(target == 2)
			{
				ls_MstrCmdMsgForSlv3.s.master_cmdForSlave3 = cmd_LED_toggling;
				linmstr_TxUpdateMsgData(MASTER_CMD_SLV3, ls_MstrCmdMsgForSlv3.all);	
			}
			else if(target == 3)
			{
				ls_MstrCmdMsgForSlv4.s.master_cmdForSlave4 = cmd_LED_toggling;
				linmstr_TxUpdateMsgData(MASTER_CMD_SLV4, ls_MstrCmdMsgForSlv4.all);
			}
			else { }
			linmstr_changeSchdTable(sched_SlvCmdAndStats);
			break;
		case HLC_DISABLE_SLV:
			if(target == 0)
			{
				ls_MstrCmdMsgForSlv1.s.master_cmdForSlave1 = cmd_disable_slv;
				linmstr_TxUpdateMsgData(MASTER_CMD_SLV1, ls_MstrCmdMsgForSlv1.all);
			} 
			else if(target == 1)
			{
				ls_MstrCmdMsgForSlv2.s.master_cmdForSlave2 = cmd_disable_slv;
				linmstr_TxUpdateMsgData(MASTER_CMD_SLV2, ls_MstrCmdMsgForSlv2.all);
			}
			else if(target == 2)
			{
				ls_MstrCmdMsgForSlv3.s.master_cmdForSlave3 = cmd_disable_slv;
				linmstr_TxUpdateMsgData(MASTER_CMD_SLV3, ls_MstrCmdMsgForSlv3.all);	
			}
			else if(target == 3)
			{
				ls_MstrCmdMsgForSlv4.s.master_cmdForSlave4 = cmd_disable_slv;
				linmstr_TxUpdateMsgData(MASTER_CMD_SLV4, ls_MstrCmdMsgForSlv4.all);
			}
			else { }
			linmstr_changeSchdTable(sched_SlvCmdAndStats);
			break;
		case HLC_ENABLE_SLV:
			if(target == 0)
			{
				ls_MstrCmdMsgForSlv1.s.master_cmdForSlave1 = cmd_enable_slv;
				linmstr_TxUpdateMsgData(MASTER_CMD_SLV1, ls_MstrCmdMsgForSlv1.all);
			} 
			else if(target == 1)
			{
				ls_MstrCmdMsgForSlv2.s.master_cmdForSlave2 = cmd_enable_slv;
				linmstr_TxUpdateMsgData(MASTER_CMD_SLV2, ls_MstrCmdMsgForSlv2.all);
			}
			else if(target == 2)
			{
				ls_MstrCmdMsgForSlv3.s.master_cmdForSlave3 = cmd_enable_slv;
				linmstr_TxUpdateMsgData(MASTER_CMD_SLV3, ls_MstrCmdMsgForSlv3.all);	
			}
			else if(target == 3)
			{
				ls_MstrCmdMsgForSlv4.s.master_cmdForSlave4 = cmd_enable_slv;
				linmstr_TxUpdateMsgData(MASTER_CMD_SLV4, ls_MstrCmdMsgForSlv4.all);
			}
			else { }
			linmstr_changeSchdTable(sched_SlvCmdAndStats);
			break;
		case HLC_GET_IDS:
			linmstr_changeSchdTable(sched_SlvIDs);
			break;
		}
	}
	else if(rs_buttonSendCmd.releasedAt2)
	{
		/* Button has been pressed and has been debounced and released at 2 */
		rs_buttonSendCmd.releasedAt2 = 0; // consume flag
		/* Get command from input pins */
		command = (E_HL_COMMANDS)((HLC_READ_INPUT(PIN_IN_CMD_2) << 2) | (HLC_READ_INPUT(PIN_IN_CMD_1) << 1) | HLC_READ_INPUT(PIN_IN_CMD_0));	
		switch(command)
		{
		case HLC_NONE:
			break;
		case HLC_LED_ON:
			ls_MstrCmdMsgForAll.s.master_cmdForAll = cmd_LED_on;
			linmstr_TxUpdateMsgData(MASTER_CMD_ALL, ls_MstrCmdMsgForAll.all);
			linmstr_changeSchdTable(sched_AllCmd);
			break;
		case HLC_LED_OFF:
			ls_MstrCmdMsgForAll.s.master_cmdForAll = cmd_LED_off;
			linmstr_TxUpdateMsgData(MASTER_CMD_ALL, ls_MstrCmdMsgForAll.all);
			linmstr_changeSchdTable(sched_AllCmd);
			break;
		case HLC_LED_TOGGLING:
			ls_MstrCmdMsgForAll.s.master_cmdForAll = cmd_LED_toggling;
			linmstr_TxUpdateMsgData(MASTER_CMD_ALL, ls_MstrCmdMsgForAll.all);
			linmstr_changeSchdTable(sched_AllCmd);
			break;
		case HLC_DISABLE_SLV:
			ls_MstrCmdMsgForAll.s.master_cmdForAll = cmd_disable_slv;
			linmstr_TxUpdateMsgData(MASTER_CMD_ALL, ls_MstrCmdMsgForAll.all);
			linmstr_changeSchdTable(sched_AllCmd);
			break;
		case HLC_ENABLE_SLV:
			ls_MstrCmdMsgForAll.s.master_cmdForAll = cmd_enable_slv;
			linmstr_TxUpdateMsgData(MASTER_CMD_ALL, ls_MstrCmdMsgForAll.all);
			linmstr_changeSchdTable(sched_AllCmd);
			break;
		case HLC_GET_IDS:
			linmstr_changeSchdTable(sched_SlvIDs);
			break;
		}
	}
	else
	{
		/* Waiting for button debounce-release, do nothing. */
	}
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void app_commander_status_task()
{	
	if(GET_LINMSTR_MSG_FLAG(SLAVE1_RSP))
	{
		S_SLAVE1_RSP ls_slv1_Rsp; /* define local variable */
		/* Consume RX flag */
		SET_LINMSTR_MSG_FLAG(SLAVE1_RSP,0);
		/* Get data */
		linmstr_RxGetMsgData(SLAVE1_RSP, ls_slv1_Rsp.all);
		/* Store data in the application layer */
		re_app_slv1_led_status = ls_slv1_Rsp.s.slave1_LEDstat;
	} 
	if(GET_LINMSTR_MSG_FLAG(SLAVE2_RSP))
	{
		S_SLAVE2_RSP ls_slv2_Rsp; /* define local variable */
		/* Consume RX flag */
		SET_LINMSTR_MSG_FLAG(SLAVE2_RSP,0);
		/* Get data */
		linmstr_RxGetMsgData(SLAVE2_RSP, ls_slv2_Rsp.all);
		/* Store data in the application layer */
		re_app_slv2_led_status = ls_slv2_Rsp.s.slave2_LEDstat;
	}
	if(GET_LINMSTR_MSG_FLAG(SLAVE3_RSP))
	{
		S_SLAVE3_RSP ls_slv3_Rsp; /* define local variable */
		/* Consume RX flag */
		SET_LINMSTR_MSG_FLAG(SLAVE3_RSP,0);
		/* Get data */
		linmstr_RxGetMsgData(SLAVE3_RSP, ls_slv3_Rsp.all);
		/* Store data in the application layer */
		re_app_slv3_led_status = ls_slv3_Rsp.s.slave3_LEDstat;
	}
	if(GET_LINMSTR_MSG_FLAG(SLAVE4_RSP))
	{
		S_SLAVE4_RSP ls_slv4_Rsp; /* define local variable */
		/* Consume RX flag */
		SET_LINMSTR_MSG_FLAG(SLAVE4_RSP,0);
		/* Get data */
		linmstr_RxGetMsgData(SLAVE4_RSP, ls_slv4_Rsp.all);
		/* Store data in the application layer */
		re_app_slv4_led_status = ls_slv4_Rsp.s.slave4_LEDstat;
	}
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :  Suggested periodic time is 100 ms
 **************************************************************/
void app_commander_led_task()
{
	ruw_ledBlinkCntr++;
	
	/* Process status of LIN slave 1 */
	if(re_app_slv1_led_status == OFF)
	{
		HLC_CLEAR_OUTPUT(PIN_OUT_LED_SLV1);
	}
	else if(re_app_slv1_led_status == ON)
	{
		HLC_SET_OUTPUT(PIN_OUT_LED_SLV1);
	}
	else if(re_app_slv1_led_status == TOGGLING)
	{
		if( (ruw_ledBlinkCntr >> 1) & 0x0001 )
		{
			/* Toggle pin output each period_time/4 */
			HLC_TOGGLE_OUTPUT(PIN_OUT_LED_SLV1);
		}
	}
	
	/* Process status of LIN slave 2 */
	if(re_app_slv2_led_status == OFF)
	{
		HLC_CLEAR_OUTPUT(PIN_OUT_LED_SLV2);
	}
	else if(re_app_slv2_led_status == ON)
	{
		HLC_SET_OUTPUT(PIN_OUT_LED_SLV2);
	}
	else if(re_app_slv2_led_status == TOGGLING)
	{
		if( (ruw_ledBlinkCntr >> 1) & 0x0001 )
		{
			/* Toggle pin output each period_time/4 */
			HLC_TOGGLE_OUTPUT(PIN_OUT_LED_SLV2);
		}
	}
	
	/* Process status of LIN slave 3 */
	if(re_app_slv3_led_status == OFF)
	{
		HLC_CLEAR_OUTPUT(PIN_OUT_LED_SLV3);
	}
	else if(re_app_slv3_led_status == ON)
	{
		HLC_SET_OUTPUT(PIN_OUT_LED_SLV3);
	}
	else if(re_app_slv3_led_status == TOGGLING)
	{
		if( (ruw_ledBlinkCntr >> 1) & 0x0001 )
		{
			/* Toggle pin output each period_time/4 */
			HLC_TOGGLE_OUTPUT(PIN_OUT_LED_SLV3);
		}
	}
	
	/* Process status of LIN slave 4 */
	if(re_app_slv4_led_status == OFF)
	{
		HLC_CLEAR_OUTPUT(PIN_OUT_LED_SLV4);
	}
	else if(re_app_slv4_led_status == ON)
	{
		HLC_SET_OUTPUT(PIN_OUT_LED_SLV4);
	}
	else if(re_app_slv4_led_status == TOGGLING)
	{
		if( (ruw_ledBlinkCntr >> 1) & 0x0001 )
		{
			/* Toggle pin output each period_time/4 */
			HLC_TOGGLE_OUTPUT(PIN_OUT_LED_SLV4);
		}
	}
}


#endif
