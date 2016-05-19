/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        LIN_slave_network.h
* version:         1.0 
* created_by:      Carlos Calvillo
* date_created:    Nov 1, 2013
*=============================================================================*/
/* DESCRIPTION : LIN slave node Network Information Header File               */
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
#ifndef LIN_SLAVE_NETWORK_H_
#define LIN_SLAVE_NETWORK_H_


#include "LIN_common.h"
#include "LIN_common_network.h"

#define LINSLV_MSG_TOTAL_DLEN (LIN_MSG_DLEN_MASTER_CMD_ALL + \
								LIN_MSG_DLEN_MASTER_CMD_SLV1 + \
								LIN_MSG_DLEN_SLAVE1_RSP + \
								LIN_MSG_DLEN_SLAVE1_ID)


#if LINSLV_MSG_TOTAL_DLEN < 0xFF
	typedef T_UBYTE T_LINSLV_BUFF_SIZE;
#elif LINSLV_MSG_TOTAL_DLEN < 0xFFFF
	typedef T_UWORD T_LINSLV_BUFF_SIZE;
#else
	typedef T_ULONG T_LINSLV_BUFF_SIZE;
#endif


typedef enum{
	MASTER_CMD_ALL,
	MASTER_CMD_SLV1,
	SLAVE1_RSP,
	SLAVE1_ID,
	E_LINSLV_N_OF_MSGS
}E_LINSLV_MSGS;


#if E_LINSLV_N_OF_MSGS < 0xFF
	typedef T_UBYTE T_LINSLV_NMSG;
#elif E_LINSLV_N_OF_MSGS < 0xFFFF
	typedef T_UWORD T_LINSLV_NMSG;
#else
	typedef T_ULONG T_LINSLV_NMSG;
#endif


typedef union {
	struct{
		T_UBYTE bi_MASTER_CMD_ALL: 1;
		T_UBYTE bi_MASTER_CMD_SLV1: 1;
		T_UBYTE bi_SLAVE1_RSP: 1;
		T_UBYTE bi_SLAVE1_ID: 1;
		T_UBYTE reserved: 4;
	}b;
	T_UBYTE all[1];
}U_LINSLV_MSG_FLAGS;

U_LINSLV_MSG_FLAGS ru_LINSLV_msgsStatusFLag;

#define GET_LINSLV_MSG_FLAG(msg)			( (ru_LINSLV_msgsStatusFLag.all[((T_LINSLV_NMSG)msg >> 3u)] >> ((T_LINSLV_NMSG)msg % 8u)) & 1u )
#define SET_LINSLV_MSG_FLAG(msg,val)		(val) ? (ru_LINSLV_msgsStatusFLag.all[((T_LINSLV_NMSG)msg >> 3u)] |= (T_UBYTE)(1u << ((T_LINSLV_NMSG)msg % 8u))) \
													:(ru_LINSLV_msgsStatusFLag.all[((T_LINSLV_NMSG)msg >> 3u)] &= ~( (T_UBYTE)(1u << ((T_LINSLV_NMSG)msg % 8u))) )

extern const S_LIN_MSG_STATIC_DATA rs_LINSLV_msgsStaticData[E_LINSLV_N_OF_MSGS];

extern void linslv_RxGetMsgData(E_LINSLV_MSGS le_msg, T_UBYTE * lpub_data);
extern void linslv_TxUpdateMsgData(E_LINSLV_MSGS le_msg, T_UBYTE * lpub_data);
extern void linslv_clearDataBuffer();


#endif /* LIN_SLAVE_NETWORK_H_ */
