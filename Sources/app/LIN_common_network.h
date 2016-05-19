/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        LIN_common_network.h
* version:         1.0 
* created_by:      Carlos Calvillo
* date_created:    Nov 1, 2013
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

#ifndef LIN_COMMON_NETWORK_H_
#define LIN_COMMON_NETWORK_H_

#include "stdtypedef.h"

#define LIN_MSG_DLEN_MASTER_CMD_ALL			1
#define LIN_MSG_DLEN_MASTER_CMD_SLV1		1
#define LIN_MSG_DLEN_MASTER_CMD_SLV2		1
#define LIN_MSG_DLEN_MASTER_CMD_SLV3		1
#define LIN_MSG_DLEN_MASTER_CMD_SLV4		1
#define LIN_MSG_DLEN_SLAVE1_RSP				2
#define LIN_MSG_DLEN_SLAVE2_RSP				2
#define LIN_MSG_DLEN_SLAVE3_RSP				2
#define LIN_MSG_DLEN_SLAVE4_RSP				2
#define LIN_MSG_DLEN_SLAVE1_ID				7
#define LIN_MSG_DLEN_SLAVE2_ID				7
#define LIN_MSG_DLEN_SLAVE3_ID				7
#define LIN_MSG_DLEN_SLAVE4_ID				7
		
#define LIN_MSG_ID_MASTER_CMD_ALL		(0xCF)
#define LIN_MSG_ID_MASTER_CMD_SLV1		(0x50)
#define LIN_MSG_ID_MASTER_CMD_SLV2		(0x11)
#define LIN_MSG_ID_MASTER_CMD_SLV3		(0x92)
#define LIN_MSG_ID_MASTER_CMD_SLV4		(0xD3)
#define LIN_MSG_ID_SLAVE1_RSP			(0x20)
#define LIN_MSG_ID_SLAVE2_RSP			(0x61)
#define LIN_MSG_ID_SLAVE3_RSP			(0xE2)
#define LIN_MSG_ID_SLAVE4_RSP			(0xA3)
#define LIN_MSG_ID_SLAVE1_ID			(0xF0)
#define LIN_MSG_ID_SLAVE2_ID			(0xB1)
#define LIN_MSG_ID_SLAVE3_ID			(0x32)
#define LIN_MSG_ID_SLAVE4_ID			(0x73)

#endif /* LIN_COMMON_NETWORK_H_ */
