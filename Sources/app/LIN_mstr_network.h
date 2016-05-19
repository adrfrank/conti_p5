/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        LIN_mstr_network.h
* version:         1.0 
* created_by:      Carlos Calvillo
* date_created:    19/09/2013
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

#ifndef LINMSGS_H_
#define LINMSGS_H_

#include "LIN_common.h"
#include "LIN_common_network.h"

#if COMPILE_LIN_MASTER_NODE

#define LINMSTR_MSG_TOTAL_DLEN (LIN_MSG_DLEN_MASTER_CMD_ALL + \
							LIN_MSG_DLEN_MASTER_CMD_SLV1 + \
							LIN_MSG_DLEN_MASTER_CMD_SLV2 + \
							LIN_MSG_DLEN_MASTER_CMD_SLV3 + \
							LIN_MSG_DLEN_MASTER_CMD_SLV4 + \
							LIN_MSG_DLEN_SLAVE1_RSP + \
							LIN_MSG_DLEN_SLAVE2_RSP + \
							LIN_MSG_DLEN_SLAVE3_RSP + \
							LIN_MSG_DLEN_SLAVE4_RSP + \
							LIN_MSG_DLEN_SLAVE1_ID + \
							LIN_MSG_DLEN_SLAVE2_ID + \
							LIN_MSG_DLEN_SLAVE3_ID + \
							LIN_MSG_DLEN_SLAVE4_ID)


#if LINMSTR_MSG_TOTAL_DLEN < 0xFF
	typedef T_UBYTE T_BUFF_SIZE;
#elif LINMSTR_MSG_TOTAL_DLEN < 0xFFFF
	typedef T_UWORD T_BUFF_SIZE;
#else
	typedef T_ULONG T_BUFF_SIZE;
#endif


typedef enum{
	MASTER_CMD_ALL,
	MASTER_CMD_SLV1,
	MASTER_CMD_SLV2,
	MASTER_CMD_SLV3,
	MASTER_CMD_SLV4,
	SLAVE1_RSP,
	SLAVE2_RSP,
	SLAVE3_RSP,
	SLAVE4_RSP,
	SLAVE1_ID,
	SLAVE2_ID,
	SLAVE3_ID,
	SLAVE4_ID,
    E_LIN_N_OF_MSGS
}E_LINMSTR_MSGS;

/*
#if E_LIN_N_OF_MSGS < 0xFF
	typedef T_UBYTE T_LINNMSG;
#elif E_LIN_N_OF_MSGS < 0xFFFF
	typedef T_UWORD T_LINNMSG;
#else
	typedef T_ULONG T_LINNMSG;
#endif
*/

typedef union {
	struct{
		T_UBYTE bi_MASTER_CMD_ALL: 1;
		T_UBYTE bi_MASTER_CMD_SLV1: 1;
		T_UBYTE bi_MASTER_CMD_SLV2: 1;
		T_UBYTE bi_MASTER_CMD_SLV3: 1;
		T_UBYTE bi_MASTER_CMD_SLV4: 1;
		T_UBYTE bi_SLAVE1_RSP: 1;
		T_UBYTE bi_SLAVE2_RSP: 1;
		T_UBYTE bi_SLAVE3_RSP: 1;
		T_UBYTE bi_SLAVE4_RSP: 1;
		T_UBYTE bi_SLAVE1_ID: 1;
		T_UBYTE bi_SLAVE2_ID: 1;
		T_UBYTE bi_SLAVE3_ID: 1;
		T_UBYTE bi_SLAVE4_ID: 1;
		T_UBYTE reserved: 3;
	}b;
	T_UBYTE all[2];
}U_LINMSTR_MSG_FLAGS;

U_LINMSTR_MSG_FLAGS ru_LINmsgsStatusFLag;

#define GET_LINMSTR_MSG_FLAG(msg)			( (ru_LINmsgsStatusFLag.all[((E_LINMSTR_MSGS)msg >> 3u)] >> ((E_LINMSTR_MSGS)msg % 8u)) & 1u )
#define SET_LINMSTR_MSG_FLAG(msg,val)		(val) ? (ru_LINmsgsStatusFLag.all[((E_LINMSTR_MSGS)msg >> 3u)] |= (T_UBYTE)(1u << ((E_LINMSTR_MSGS)msg % 8u))) \
												:(ru_LINmsgsStatusFLag.all[((E_LINMSTR_MSGS)msg >> 3u)] &= ~( (T_UBYTE)(1u << ((E_LINMSTR_MSGS)msg % 8u))) )

extern const S_LIN_MSG_STATIC_DATA rs_LINMSTRmsgsStaticData[E_LIN_N_OF_MSGS];

extern void linmstr_RxGetMsgData(E_LINMSTR_MSGS le_msg, T_UBYTE * lpub_data);
extern void linmstr_TxUpdateMsgData(E_LINMSTR_MSGS le_msg, T_UBYTE * lpub_data);
extern void linmstr_clearDataBuffer();

#endif
#endif /* LINMSGS_H_ */
