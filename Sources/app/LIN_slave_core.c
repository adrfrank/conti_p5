/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
 * C Source:        LIN_slave_core.c
 * version:         1.0 
 * created_by:      Carlos Calvillo
 * date_created:    Nov 1, 2013
 *=============================================================================*/
/* DESCRIPTION : LIN slave node Core functionality                            */
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

#include "LIN_common.h"
#include "LIN_slave_core.h"
#include "LIN_slave_hal.h"
#include "LIN_slave_network.h"
#include "interrupts.h"
#include "LIN_signals.h"
#include <cstring>  /* For inclusion of the memcpy function */

/* LIN Master State Machine related variables */
/* ------------------------------------------ */
volatile E_LINSLV_STATE re_linslvCommState; /* Variable to hold the current state of the LIN slave */
E_LINSLV_MSGS re_currentSlvMsg;	/* Variable to hold the current LIN message being handled by the LIN slave */


/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void linslv_init()
{
	/* FOLLOWING IS ONLY A SUGGESTED SET OF INITIALIZATIONS */
	/* Initialize LIN slave state machine */
	re_linslvCommState = LINSLV_IDLE;

	/* Initialize UART hardware */
	linSlvHal_initSerialHW();


	/* Initialize msg data */
	linslv_clearDataBuffer();
}

/**************************************************************
 *  Name                 : linslv_getSlvState
 *  Description          : 
 *  Parameters           : 
 *  Return               : 
 *  Critical/explanation :
 **************************************************************/
E_LINSLV_STATE linslv_getSlvState(void)
{
	return(re_linslvCommState);
}

/**************************************************************
 *  Name                 : linslv_slaveStateMachine
 *  Description          : 
 *  Parameters           : 
 *  Return               : 
 *  Critical/explanation :
 **************************************************************/
void linslv_slaveStateMachine(E_LINSLV_COMM_EVENTS le_event)
{
	/* Local variables (including the ones with static storage class) */
	static T_UBYTE lub_dataCounter; /* Counts data bytes. For TX it counts the already transmitted bytes. For RX it counts the received bytes */
	static T_UBYTE lub_tempChksum; /* Holds the calculated checksum, either for transmission or for comparison against the received checksum */
	static T_UBYTE lub_rxChksum; /* Received checksum to be used to validate the integrity of the received LIN message */
	static T_UBYTE laub_linUnifiedRxTxBuffer[8]; /* Unified data buffer. For TX this array holds the data bytes to be transmitted. For RX, this array holds the received data */
	static T_UBYTE lub_tempSync;


	/* IMPLEMENTATION OF THE LIN SLAVE STATE MACHINE GOES HERE... */
	if((le_event == LINSLV_EV_BREAK_DETECTED) && (re_linslvCommState != LINSLV_IDLE)){
		LINSLV_HAL_DISABLE_TX_INT();
		LINSLV_HAL_DISABLE_RX_INT();
		re_linslvCommState = LINSLV_IDLE;
	}

	/* React upon timeout event */
	if( le_event == LINSLV_EV_TIMEOUT)
	{
		LINSLV_HAL_DISABLE_TX_INT();
		LINSLV_HAL_DISABLE_RX_INT();
		re_linslvCommState = LINSLV_IDLE;
		/* TODO: Flag the timeout error */
		linslv_timeout_error_callback();
	}

	switch(re_linslvCommState){
	case LINSLV_IDLE:
		if(le_event == LINSLV_EV_BREAK_DETECTED){
			LINSLV_HAL_DISABLE_TX_INT();
			LINSLV_HAL_ENABLE_RX_INT();
			LINSLV_HAL_DISABLE_BREAK_RX();
			re_linslvCommState = LINSLV_RX_SYNCH;
		}
		break;
	case LINSLV_RX_SYNCH:
		if(le_event== LINSLV_EV_RX_OK){
			lub_tempSync = linSlvHal_receivedByte();
			if(lub_tempSync == LIN_SYNCH_SYMBOL){
				re_linslvCommState = LINSLV_RX_ID;
			}else{
				linslv_synch_error_callback();
				re_linslvCommState = LINSLV_IDLE;
			}
		}		
		break;
	case LINSLV_RX_ID:
		if(le_event== LINSLV_EV_RX_OK){
			//rs_LINSLV_msgsStaticData[re_currentSlvMsg].msgID = linSlvHal_receivedByte();
			if(lincomm_checkIDparityBits(rs_LINSLV_msgsStaticData[re_currentSlvMsg].msgID)){
				if(rs_LINSLV_msgsStaticData[re_currentSlvMsg].msgDir == TX){
					LINSLV_HAL_ENABLE_TX_INT();
					LINSLV_HAL_DISABLE_RX_INT();
					if(rs_LINSLV_msgsStaticData[re_currentSlvMsg].msgDataLen > 0){
						linSlvHal_sendByte(laub_linUnifiedRxTxBuffer[0]);
						lub_dataCounter = 1;
						re_linslvCommState = LINSLV_TX_DATA;
					}else {
						lub_tempChksum = lincomm_calculateChksum(rs_LINSLV_msgsStaticData[re_currentSlvMsg].msgID, laub_linUnifiedRxTxBuffer,rs_LINSLV_msgsStaticData[re_currentSlvMsg].msgDataLen);
						linSlvHal_sendByte(lub_tempChksum);
						re_linslvCommState = LINSLV_TX_CHKSUM;
					}
				}else{//RX
					LINSLV_HAL_DISABLE_TX_INT();
					LINSLV_HAL_ENABLE_RX_INT();
					if(rs_LINSLV_msgsStaticData[re_currentSlvMsg].msgDataLen > 0){
						lub_dataCounter = 1;
						re_linslvCommState = LINSLV_RX_DATA;
					}else {
						re_linslvCommState = LINSLV_RX_CHKSUM;
					}

				}
			}else{
				/* Msg ID is incorrect. Flag the error */
				linslv_ID_parity_error_callback();
				re_linslvCommState = LINSLV_IDLE;
			}
		}	
		break;
	case LINSLV_TX_DATA:
		if(le_event == LINSLV_EV_TX_OK){
			if(rs_LINSLV_msgsStaticData[re_currentSlvMsg].msgDataLen > lub_dataCounter){
				linSlvHal_sendByte(laub_linUnifiedRxTxBuffer[lub_dataCounter]);
				lub_dataCounter++;
			}else{
				lub_tempChksum = lincomm_calculateChksum(rs_LINSLV_msgsStaticData[re_currentSlvMsg].msgID, laub_linUnifiedRxTxBuffer,rs_LINSLV_msgsStaticData[re_currentSlvMsg].msgDataLen);
				linSlvHal_sendByte(lub_tempChksum);
				re_linslvCommState = LINSLV_TX_CHKSUM;
			}
		}
		break;
	case LINSLV_TX_CHKSUM:
		if(le_event == LINSLV_EV_TX_OK){
			re_linslvCommState = LINSLV_IDLE;
			SET_LINSLV_MSG_FLAG(re_currentSlvMsg, TRUE);
			if(rs_LINSLV_msgsStaticData[re_currentSlvMsg].MsgCallback != LIN_NULL_PTR){
				rs_LINSLV_msgsStaticData[re_currentSlvMsg].MsgCallback ();
			}
			LINSLV_HAL_DISABLE_TX_INT();
		}
		break;
	case LINSLV_RX_DATA:
		if(le_event == LINSLV_EV_RX_OK){
			laub_linUnifiedRxTxBuffer[lub_dataCounter-1] = linSlvHal_receivedByte();
			if(rs_LINSLV_msgsStaticData[re_currentSlvMsg].msgDataLen> lub_dataCounter){
				lub_dataCounter++;
			}else{
				re_linslvCommState = LINSLV_RX_CHKSUM;
			}
		}
		break;
	case LINSLV_RX_CHKSUM:
		if(le_event == LINSLV_EV_RX_OK){
			lub_rxChksum = linSlvHal_receivedByte();
			lub_tempChksum = lincomm_calculateChksum(rs_LINSLV_msgsStaticData[re_currentSlvMsg].msgID,laub_linUnifiedRxTxBuffer,rs_LINSLV_msgsStaticData[re_currentSlvMsg].msgDataLen);
			if(lub_rxChksum == lub_tempChksum){
				memcpy(rs_LINSLV_msgsStaticData[re_currentSlvMsg].MsgBuffDataStartPtr,laub_linUnifiedRxTxBuffer,rs_LINSLV_msgsStaticData[re_currentSlvMsg].msgDataLen);
				SET_LINSLV_MSG_FLAG(re_currentSlvMsg, TRUE);
				if(rs_LINSLV_msgsStaticData[re_currentSlvMsg].MsgCallback != LIN_NULL_PTR)
				{
					rs_LINSLV_msgsStaticData[re_currentSlvMsg].MsgCallback();
				}
			}else{
				linslv_checksum_error_callback();
			}
			re_linslvCommState = LINSLV_IDLE;
			LINSLV_HAL_DISABLE_RX_INT();

		}
		break;
	default:
		break;
	}
}
