/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        LIN_slave_network.c
* version:         1.0 
* created_by:      Carlos Calvillo
* date_created:    Nov 1, 2013
*=============================================================================*/
/* DESCRIPTION : LIN slave node Network Information                           */
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

#include "LIN_slave_network.h"
#include "LIN_slave_il.h"
#include <cstring>  /* For inclusion of the memcpy function */

T_UBYTE raub_LINSLV_msgsDataBuffer[LINSLV_MSG_TOTAL_DLEN];

const S_LIN_MSG_STATIC_DATA rs_LINSLV_msgsStaticData[E_LINSLV_N_OF_MSGS] = {
	/*  { msgID,						msgDir,		msgDataLen,							MsgCallback, 						MsgBuffDataStartPtr }	*/
		{ LIN_MSG_ID_MASTER_CMD_ALL,	RX,			LIN_MSG_DLEN_MASTER_CMD_ALL, 		linslv_callback_MASTER_CMD_ALL,    	&raub_LINSLV_msgsDataBuffer[0]},
		{ LIN_MSG_ID_MASTER_CMD_SLV1,	RX,			LIN_MSG_DLEN_MASTER_CMD_SLV1, 		linslv_callback_MASTER_CMD_SLV1,   	&raub_LINSLV_msgsDataBuffer[1]},
		{ LIN_MSG_ID_SLAVE1_RSP,		TX,			LIN_MSG_DLEN_SLAVE1_RSP,			linslv_callback_SLAVE1_RSP,			&raub_LINSLV_msgsDataBuffer[2]},
		{ LIN_MSG_ID_SLAVE1_ID,			TX,			LIN_MSG_DLEN_SLAVE1_ID,				linslv_callback_SLAVE1_ID, 			&raub_LINSLV_msgsDataBuffer[4]}
};


/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void linslv_RxGetMsgData(E_LINSLV_MSGS le_msg, T_UBYTE * lpub_data)
{
	/* TODO: Enter critical section */
	memcpy(lpub_data,rs_LINSLV_msgsStaticData[le_msg].MsgBuffDataStartPtr,rs_LINSLV_msgsStaticData[le_msg].msgDataLen);
	/* TODO: Exit critical section */
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void linslv_TxUpdateMsgData(E_LINSLV_MSGS le_msg, T_UBYTE * lpub_data)
{
	/* TODO: Enter critical section */
	memcpy(rs_LINSLV_msgsStaticData[le_msg].MsgBuffDataStartPtr,lpub_data,rs_LINSLV_msgsStaticData[le_msg].msgDataLen);
	/* TODO: Exit critical section */
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void linslv_clearDataBuffer()
{
	T_UWORD i;
	for(i=0; i<LINSLV_MSG_TOTAL_DLEN; i++)
	{
		raub_LINSLV_msgsDataBuffer[i] = 0;
	}
}
