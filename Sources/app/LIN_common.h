/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        LINcommon.h
* version:         1.0 
* created_by:      Carlos Calvillo
* date_created:    19/09/2013
*=============================================================================*/
/* DESCRIPTION : Header for common LIN functionality                          */
/*============================================================================*/
/* FUNCTION COMMENT :  Header for common LIN functionality                    */
/*                                                                            */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 19/09/2013  |                               | Carlos Calvillo  */
/*  First implementation.                                                     */
/*============================================================================*/

#ifndef LINCOMMON_H_
#define LINCOMMON_H_

#include "stdtypedef.h"

/* These macros RX and TX are used for the direction of the LIN messages,
 * this direction depends on the Node (master or slave) and the message itself.
 */
#define RX	0
#define TX	1

typedef enum{
	E_LIN_OK,
	E_LIN_NOK
}E_LINGET_STAT;

/* typedef for a LIN callback (function). Callbacks normally do not have return
 * value neither arguments. */
typedef void (*T_CALLBACK)(void);

/* Type used to hold the static data of the LIN message. */
typedef struct{
	T_UBYTE msgID;
	T_UBYTE msgDir;
	T_UBYTE msgDataLen;
	T_CALLBACK MsgCallback;
	T_UBYTE * MsgBuffDataStartPtr;
}S_LIN_MSG_STATIC_DATA;

typedef struct{
	T_UBYTE msgTxRxFlag : 1;
}S_MSG_DYNAMIC_DATA;

typedef struct{
	T_UBYTE bi_enhancedChksum : 1;
}S_LIN_CTRL_DATA;


#define LIN_NULL_PTR		(T_CALLBACK)0
#define LIN_SYNCH_SYMBOL			(0x55u)


extern T_UBYTE lincomm_calculateChksum(T_UBYTE lub_msgIdValue, T_UBYTE * lpub_data, T_UBYTE lub_dataLen);
extern T_UBYTE lincomm_checkIDparityBits(T_UBYTE lub_msgIdValue);

#define COMPILE_LIN_MASTER_NODE 		1
#define COMPILE_LIN_SLAVE_NODE 			1

#endif /* LINCOMMON_H_ */
