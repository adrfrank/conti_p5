/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        LIN_mstr_core.c
* version:         1.0 
* created_by:      Carlos Calvillo
* date_created:    19/09/2013
*=============================================================================*/
/* DESCRIPTION : LIN Master Core functionality                                */
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
#include "LIN_common.h"
#include "LIN_mstr_core.h"
#include "LIN_mstr_hal.h"
#include "LIN_mstr_network.h"
#include "interrupts.h"
#include "UART_hal.h"
#include <cstring>  /* For inclusion of the memcpy function */

#if COMPILE_LIN_MASTER_NODE

/* LIN Master State Machine related variables */
/* ------------------------------------------ */
volatile E_LINMSTR_STATE re_linCommState; /* Variable to hold the current state of the LIN master */
E_LINMSTR_MSGS re_currentMsg;	/* Variable to hold the current LIN message being handled by the LIN master */

/**************************************************************
 *  Name                 : linmstr_coreInit
 *  Description          : Contains the initializations for the LIN master core
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : No
 **************************************************************/
void linmstr_coreInit()
{
	/* Initialize LIN master state */
	re_linCommState = LINMSTR_IDLE;
	
	/* Initialize msg data */
	linmstr_clearDataBuffer();
	
	/* Initialize UART hardware */
	linMstrHal_initSerialHW();
}

/**************************************************************
 *  Name                 : linmstr_getMstrState
 *  Description          : Returns the current state of the LIN master state machine. 
 *  Parameters           : none
 *  Return               : current state of the LIN master node (return type E_LINMSTR_STATE)
 *  Critical/explanation : none
 **************************************************************/
E_LINMSTR_STATE linmstr_getMstrState(void)
{
	return(re_linCommState);
}

/**************************************************************
 *  Name                 : 	linmstr_masterStateMachine
 *  Description          : 	Implements the functionality of the LIN master node. It is a state machine. 
 *  Parameters           : 	[input] le_event-> Indicate the event that has happened. This event may or may not a 
 *  					   	transition to another state.
 *  Return               : 	none
 *  Critical/explanation : 	Initialization by linmstr_coreInit must be done before calling this state machine.
 *  						When re_linCommState == LINMSTR_IDLE, a new LIN frame transmission is triggered by
 *  						calling this function with the event le_event == LIN_EV_TX_START, prior to this
 *  						call global variable "re_currentMsg" must be properly set with the msg to be transmitted.
 *  						In addition, this is the only case where this function is called out of an interrupt
 *  						context (out of an ISR and hence with interrupts enabled), in all other states, this 
 *  						function is called INSIDE and ISR (with interrupts disabled by default).
 **************************************************************/
void linmstr_masterStateMachine(E_LIN_COMM_EVENTS le_event)
{
	static T_UBYTE lub_dataCounter; /* Counts data bytes. For TX it counts the already transmitted bytes. For RX it counts the received bytes */
	static T_UBYTE lub_tempChksum; /* Holds the calculated checksum, either for transmission or for comparison against the received checksum */
	static T_UBYTE lub_rxChksum; /* Received checksum to be used to validate the integrity of the received LIN message */
	static T_UBYTE laub_linUnifiedRxTxBuffer[8]; /* Unified data buffer. For TX this array holds the data bytes to be transmitted. For RX, this array holds the received data */

	/* TODO: remove this "if" statement code, it is only a patch while a proper timeout logic is implemented */
	if((le_event == LINMSTR_EV_TX_START) && (re_linCommState != LINMSTR_IDLE)){
		LINMSTR_HAL_DISABLE_TX_INT();
		LINMSTR_HAL_DISABLE_RX_INT();
		re_linCommState = LINMSTR_IDLE;
	}

	/* React upon timeout event */
	if( le_event == LINMSTR_EV_TIMEOUT)
	{
		LINMSTR_HAL_DISABLE_TX_INT();
		LINMSTR_HAL_DISABLE_RX_INT();
		re_linCommState = LINMSTR_IDLE;
		/* TODO: Flag the timeout error */
		linmstr_timeout_error_callback();
	}
	
	/* Execute state machine */
	switch(re_linCommState)
	{
	case LINMSTR_IDLE:
		if( le_event == LINMSTR_EV_TX_START)
		{
			/* IMPORTANT: Variable re_currentMSg shall be properly set before calling this 'LIN_EV_TX_START' event!! */
			/* Check message ID parity bits. If there is an error then the transmission of this message is not executed */
			if(lincomm_checkIDparityBits(rs_LINMSTRmsgsStaticData[re_currentMsg].msgID)){
				/* Msg ID is correct */
				/* If master is the publisher of this message (msgDir == TX) then copy data to unified buffer for transmission. */ 
				if((rs_LINMSTRmsgsStaticData[re_currentMsg].msgDir == TX) && (rs_LINMSTRmsgsStaticData[re_currentMsg].msgDataLen > 0))
				{
					memcpy(laub_linUnifiedRxTxBuffer,rs_LINMSTRmsgsStaticData[re_currentMsg].MsgBuffDataStartPtr,rs_LINMSTRmsgsStaticData[re_currentMsg].msgDataLen);
				}
				/* Transmit break symbol */
				linMstrHal_sendBrake();
				/* Enable TX interrupt */
				LINMSTR_HAL_ENABLE_TX_INT();
				/* Set new state to: transmission of SYNCH symbol */
				re_linCommState = LINMSTR_TX_SYNCH;
				}
			else
			{
				/* Msg ID is incorrect. Flag the error */
				linmstr_ID_parity_error_callback();
			}
		}
		break;
	case LINMSTR_TX_SYNCH:
		if(le_event == LINMSTR_EV_TX_OK)
		{
			/* If successful transmission of BREAK symbol then transmit SYNCH symbol */
			/* Trigger SYNCH symbol transmission */
			linMstrHal_sendByte(LIN_SYNCH_SYMBOL);
			/* Set new state to: transmission of msg ID*/
			re_linCommState = LINMSTR_TX_ID;
		}
		break;
	case LINMSTR_TX_ID:
		if(le_event == LINMSTR_EV_TX_OK)
		{
			/* If successful transmission of SYNCH symbol then transmit msg ID */
			/* Trigger msg ID transmission */
			linMstrHal_sendByte(rs_LINMSTRmsgsStaticData[re_currentMsg].msgID);
			/* Go to End of Header state */
			re_linCommState = LINMSTR_END_OF_HEADER;
		}
		break;
	case LINMSTR_END_OF_HEADER:
		if(le_event == LINMSTR_EV_TX_OK)
		{
			/* Successful transmission of ID symbol finalizes the LIN frame header transmission */
			/* If LIN master is the publisher of this msg (msgDir == TX) then transmit the first data,
			 * otherwise prepare state machine for reception of data from the publishing LIN slave*/
			if(rs_LINMSTRmsgsStaticData[re_currentMsg].msgDir == TX)
			{
				/* Data transmitted successfully (first time will be msgID, subsequent times are data bytes).
				 * Check if more data transmission is required */
				if(rs_LINMSTRmsgsStaticData[re_currentMsg].msgDataLen > 0)
				{
					/* Data bytes need to be transmitted */
					/* Send first data byte */
					linMstrHal_sendByte(laub_linUnifiedRxTxBuffer[0]);
					/* Set data counter to 1*/
					lub_dataCounter = 1;
					/* Data transmission is required */
					re_linCommState = LINMSTR_TX_DATA;
				} else {
					/* No data bytes, now trigger checksum transmission */
					/* Calculate checksum */
					lub_tempChksum = lincomm_calculateChksum(rs_LINMSTRmsgsStaticData[re_currentMsg].msgID, laub_linUnifiedRxTxBuffer,rs_LINMSTRmsgsStaticData[re_currentMsg].msgDataLen);
					/* Transmit checksum */
					linMstrHal_sendByte(lub_tempChksum);
					/* Go to next state */
					re_linCommState = LINMSTR_TX_CHKSUM;
				}
			} else {
				/* A slave node is the publisher of this message */
				if(rs_LINMSTRmsgsStaticData[re_currentMsg].msgDataLen > 0)
				{
					/* Data bytes need to be received */
					/* Set data counter to 1 */
					lub_dataCounter = 1;
					/* Data transmission is required */
					re_linCommState = LINMSTR_RX_DATA;
				} else {
					/* No data bytes, now go to receive checksum */
					re_linCommState = LINMSTR_RX_CHKSUM;
				}
				/* In any case, disable TX interrupt and enable RX Interrupt */
				LINMSTR_HAL_DISABLE_TX_INT();
				//UART0_ENABLE_RX();
				LINMSTR_HAL_ENABLE_RX_INT();
			}
		}
		break;
	case LINMSTR_TX_DATA:
		if(le_event == LINMSTR_EV_TX_OK)
		{
			/* Data transmitted successfully. Check if more data transmission is required */
			if(rs_LINMSTRmsgsStaticData[re_currentMsg].msgDataLen > lub_dataCounter)
			{
				/* More data bytes need to be transmitted */
				/* Send next data byte */
				linMstrHal_sendByte(laub_linUnifiedRxTxBuffer[lub_dataCounter]);
				/* Increment data counter */
				lub_dataCounter++;
			} else {
				/* All data bytes transmitted, now trigger checksum transmission */
				/* Calculate checksum */
				lub_tempChksum = lincomm_calculateChksum(rs_LINMSTRmsgsStaticData[re_currentMsg].msgID, laub_linUnifiedRxTxBuffer,rs_LINMSTRmsgsStaticData[re_currentMsg].msgDataLen);
				/* Transmit checksum */
				linMstrHal_sendByte(lub_tempChksum);
				/* Prepare data reception timeout */
				/* TODO: set-up timeout timer */
				/* Go to next state */
				re_linCommState = LINMSTR_TX_CHKSUM;
			}
		}
		break;
	case LINMSTR_TX_CHKSUM:
		if(le_event == LINMSTR_EV_TX_OK)
		{
			/* Checksum transmitted successfully, this flags the end of the LIN message transmission.
			 * Reset state machine to IDLE state to be able to process a new message */
			re_linCommState = LINMSTR_IDLE;
			/* Set LIN transmission flag for the appropriate message */
			SET_LINMSTR_MSG_FLAG(re_currentMsg, TRUE);
			/* Call LIN msg transmission callback */
			if(rs_LINMSTRmsgsStaticData[re_currentMsg].MsgCallback != LIN_NULL_PTR)
			{
				rs_LINMSTRmsgsStaticData[re_currentMsg].MsgCallback();
			}
			/* Disable TX interrupt */
			LINMSTR_HAL_DISABLE_TX_INT();
		}
		break;
	case LINMSTR_RX_DATA:
		if(le_event == LINMSTR_EV_RX_OK)
		{
			/* In any case the LIN_EV_RX_OK event means that we have received a new data byte so
			 * we need to get that data from HW and store it into the temporal buffer */
			laub_linUnifiedRxTxBuffer[lub_dataCounter-1] = linMstrHal_receivedByte();
			/* Now determine if more data is expected or if the checksum is expected. */
			if(rs_LINMSTRmsgsStaticData[re_currentMsg].msgDataLen > lub_dataCounter)
			{
				/* More data expected, no state change needed. */
				/* Increment data counter */
				lub_dataCounter++;
			}
			else
			{
				/* All data bytes received, now go to state: reception of checksum */
				re_linCommState = LINMSTR_RX_CHKSUM;
			}	
		}
		break;
	case LINMSTR_RX_CHKSUM:
		if(le_event == LINMSTR_EV_RX_OK)
		{
			/* Checksum received */
			lub_rxChksum = linMstrHal_receivedByte();
			/* Calculate expected checksum */
			lub_tempChksum = lincomm_calculateChksum(rs_LINMSTRmsgsStaticData[re_currentMsg].msgID, laub_linUnifiedRxTxBuffer,rs_LINMSTRmsgsStaticData[re_currentMsg].msgDataLen);
			/* Compare expected checksum against received checksum */
			if(lub_rxChksum == lub_tempChksum)
			{
				/* Checksum match. LIN msg reception completed successfully */
				/* Copy data from temporal reception buffer to the appropriate msg data buffer */
				memcpy(rs_LINMSTRmsgsStaticData[re_currentMsg].MsgBuffDataStartPtr,laub_linUnifiedRxTxBuffer,rs_LINMSTRmsgsStaticData[re_currentMsg].msgDataLen);
				/* Set LIN reception flag for the appropriate message */
				SET_LINMSTR_MSG_FLAG(re_currentMsg, TRUE);
				/* Call LIN msg reception callback */
				if(rs_LINMSTRmsgsStaticData[re_currentMsg].MsgCallback != LIN_NULL_PTR)
				{
					rs_LINMSTRmsgsStaticData[re_currentMsg].MsgCallback();
				}
			}
			else 
			{
				/* Data corruption. Received data is ignored */
				/* TODO: Flag the RX error */
				linmstr_checksum_error_callback();
			}
			/* In any case this ends the reception of msg, go to IDLE state to be able to process a new message */
			re_linCommState = LINMSTR_IDLE;
			LINMSTR_HAL_DISABLE_RX_INT();
			UART0_DISABLE_RX();
		}
		break;
	default:
		break;
	}
}

#endif

