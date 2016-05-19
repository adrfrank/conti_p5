/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        LIN_mstr_network.c
* version:         1.0 
* created_by:      Carlos Calvillo
* date_created:    17/09/2013
*=============================================================================*/
/* DESCRIPTION : LIN Master Node Network Information                          */
/*============================================================================*/
/* FUNCTION COMMENT : Contains the information and definitions of the LIN     */
/* Messages, Nodes, etc. of the LIN network                                   */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 20/10/2013  |                               | Carlos Calvillo  */
/*  First Implementation.                                                     */
/*============================================================================*/

#include "LIN_mstr_network.h"
#include "LIN_mstr_il.h"
#include <cstring>  /* For inclusion of the memcpy function */

#if COMPILE_LIN_MASTER_NODE


/* Buffer to contain all data for the messages being handled by the Master node */
T_UBYTE raub_LINmsgsDataBuffer[LINMSTR_MSG_TOTAL_DLEN];

/* Static Information of messages for the LIN master */
const S_LIN_MSG_STATIC_DATA rs_LINMSTRmsgsStaticData[E_LIN_N_OF_MSGS] = {
		/* msgID,						msgDir,	msgDataLen,						MsgCallback, 						MsgBuffDataStartPtr	*/
		{ LIN_MSG_ID_MASTER_CMD_ALL,	TX,		LIN_MSG_DLEN_MASTER_CMD_ALL, 	linmstr_callback_MASTER_CMD_ALL, 	&raub_LINmsgsDataBuffer[0]},	// Info for msg: MASTER_CMD_ALL
		{ LIN_MSG_ID_MASTER_CMD_SLV1,	TX,		LIN_MSG_DLEN_MASTER_CMD_SLV1, 	linmstr_callback_MASTER_CMD_SLV1,	&raub_LINmsgsDataBuffer[1]},	// Info for msg: MASTER_CMD_SLV1
		{ LIN_MSG_ID_MASTER_CMD_SLV2,	TX,		LIN_MSG_DLEN_MASTER_CMD_SLV2, 	linmstr_callback_MASTER_CMD_SLV2,	&raub_LINmsgsDataBuffer[2]},	// Info for msg: MASTER_CMD_SLV2
		{ LIN_MSG_ID_MASTER_CMD_SLV3,	TX,		LIN_MSG_DLEN_MASTER_CMD_SLV3, 	linmstr_callback_MASTER_CMD_SLV3,	&raub_LINmsgsDataBuffer[3]},	// Info for msg: MASTER_CMD_SLV3
		{ LIN_MSG_ID_MASTER_CMD_SLV4,	TX,		LIN_MSG_DLEN_MASTER_CMD_SLV4, 	linmstr_callback_MASTER_CMD_SLV4,	&raub_LINmsgsDataBuffer[4]},	// Info for msg: MASTER_CMD_SLV4
		{ LIN_MSG_ID_SLAVE1_RSP,		RX,		LIN_MSG_DLEN_SLAVE1_RSP,		linmstr_callback_SLAVE1_RSP,		&raub_LINmsgsDataBuffer[5]},	// Info for msg: SLAVE1_RSP
		{ LIN_MSG_ID_SLAVE2_RSP,		RX,		LIN_MSG_DLEN_SLAVE2_RSP,		linmstr_callback_SLAVE2_RSP,		&raub_LINmsgsDataBuffer[7]},	// Info for msg: SLAVE2_RSP
		{ LIN_MSG_ID_SLAVE3_RSP,		RX,		LIN_MSG_DLEN_SLAVE3_RSP,		linmstr_callback_SLAVE3_RSP,		&raub_LINmsgsDataBuffer[9]},	// Info for msg: SLAVE3_RSP
		{ LIN_MSG_ID_SLAVE4_RSP,		RX,		LIN_MSG_DLEN_SLAVE4_RSP,		linmstr_callback_SLAVE4_RSP,		&raub_LINmsgsDataBuffer[11]},	// Info for msg: SLAVE4_RSP
		{ LIN_MSG_ID_SLAVE1_ID,			RX,		LIN_MSG_DLEN_SLAVE1_ID,			linmstr_callback_SLAVE1_ID, 		&raub_LINmsgsDataBuffer[13]},	// Info for msg: SLAVE1_ID
		{ LIN_MSG_ID_SLAVE2_ID,			RX,		LIN_MSG_DLEN_SLAVE2_ID,			linmstr_callback_SLAVE2_ID, 		&raub_LINmsgsDataBuffer[20]},	// Info for msg: SLAVE2_ID
		{ LIN_MSG_ID_SLAVE3_ID,			RX,		LIN_MSG_DLEN_SLAVE3_ID,			linmstr_callback_SLAVE3_ID, 		&raub_LINmsgsDataBuffer[27]},	// Info for msg: SLAVE3_ID
		{ LIN_MSG_ID_SLAVE4_ID,			RX,		LIN_MSG_DLEN_SLAVE4_ID,			linmstr_callback_SLAVE4_ID, 		&raub_LINmsgsDataBuffer[34]}	// Info for msg: SLAVE4_ID
};


/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void linmstr_RxGetMsgData(E_LINMSTR_MSGS le_msg, T_UBYTE * lpub_data)
{
	/* TODO: Enter critical section */
	memcpy(lpub_data,rs_LINMSTRmsgsStaticData[le_msg].MsgBuffDataStartPtr,rs_LINMSTRmsgsStaticData[le_msg].msgDataLen);
	/* TODO: Exit critical section */
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void linmstr_TxUpdateMsgData(E_LINMSTR_MSGS le_msg, T_UBYTE * lpub_data)
{
	/* TODO: Enter critical section */
	memcpy(rs_LINMSTRmsgsStaticData[le_msg].MsgBuffDataStartPtr,lpub_data,rs_LINMSTRmsgsStaticData[le_msg].msgDataLen);
	/* TODO: Exit critical section */
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void linmstr_clearDataBuffer()
{
	T_UWORD i;
	for(i=0; i<LINMSTR_MSG_TOTAL_DLEN; i++)
	{
		raub_LINmsgsDataBuffer[i] = 0;
	}
}

#endif

