/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        LIN_signals.h
* version:         1.0 
* created_by:      Carlos Calvillo
* date_created:    17/09/2013
*=============================================================================*/
/* DESCRIPTION : LIN Signals definitions                                      */
/*============================================================================*/
/* FUNCTION COMMENT :  Contains data structures to ease the handling of the   */
/* LIN signals.                                                               */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 20/10/2013  |                               | Carlos Calvillo  */
/*  First Implementation.                                                     */
/*============================================================================*/
#ifndef LINSIGNALS_H_
#define LINSIGNALS_H_

#include "LIN_common_network.h"

/* -------------------------------------------------------------------------- */
// 		Signal TYPES
/* -------------------------------------------------------------------------- */

typedef enum{
	ENABLED,
	DISABLED
}t_slv_stat;

typedef enum{
	cmd_NONE,
	cmd_LED_on,
	cmd_LED_off,
	cmd_LED_toggling,
	cmd_disable_slv,
	cmd_enable_slv
}t_cmdType;

typedef enum{
	ON,
	OFF,
	TOGGLING
}t_LEDstat;

typedef enum{
	ACTIVE,
	INACTIVE
}t_target_active;


/* -------------------------------------------------------------------------- */
// 		Message structures (layout of signals)
/* -------------------------------------------------------------------------- */

typedef union{
	struct{
		T_UBYTE master_cmdForAll : 4;
		T_UBYTE reserved0: 4;
	} s;
	T_UBYTE all[LIN_MSG_DLEN_MASTER_CMD_ALL];
}S_MASTER_CMD_ALL;

typedef union{
	struct{
		T_UBYTE master_cmdForSlave1 : 4;
		T_UBYTE reserved0: 4;
	} s;
	T_UBYTE all[LIN_MSG_DLEN_MASTER_CMD_SLV1];
}S_MASTER_CMD_SLV1;

typedef union{
	struct{
		T_UBYTE master_cmdForSlave2 : 4;
		T_UBYTE reserved0: 4;
	} s;
	T_UBYTE all[LIN_MSG_DLEN_MASTER_CMD_SLV2];
}S_MASTER_CMD_SLV2;

typedef union{
	struct{
		T_UBYTE master_cmdForSlave3 : 4;
		T_UBYTE reserved0: 4;
	} s;
	T_UBYTE all[LIN_MSG_DLEN_MASTER_CMD_SLV3];
}S_MASTER_CMD_SLV3;

typedef union{
	struct{
		T_UBYTE master_cmdForSlave4 : 4;
		T_UBYTE reserved0: 4;
	} s;
	T_UBYTE all[LIN_MSG_DLEN_MASTER_CMD_SLV4];
}S_MASTER_CMD_SLV4;


typedef union{
	struct{
		T_UBYTE slave1_LEDstat : 2;
		T_UBYTE reserved0 : 6;
		T_UBYTE slave1_enabled : 1;
		T_UBYTE reserved1 : 7;
	} s;
	T_UBYTE all[LIN_MSG_DLEN_SLAVE1_RSP];
}S_SLAVE1_RSP;

typedef union{
	struct{
		T_UBYTE slave2_LEDstat : 2;
		T_UBYTE reserved0 : 6;
		T_UBYTE slave2_enabled : 1;
		T_UBYTE reserved1 : 7;
	} s;
	T_UBYTE all[LIN_MSG_DLEN_SLAVE2_RSP];
}S_SLAVE2_RSP;

typedef union{
	struct{
		T_UBYTE slave3_LEDstat : 2;
		T_UBYTE reserved0 : 6;
		T_UBYTE slave3_enabled : 1;
		T_UBYTE reserved1 : 7;
	} s;
	T_UBYTE all[LIN_MSG_DLEN_SLAVE3_RSP];
}S_SLAVE3_RSP;

typedef union{
	struct{
		T_UBYTE slave4_LEDstat : 2;
		T_UBYTE reserved0 : 6;
		T_UBYTE slave4_enabled : 1;
		T_UBYTE reserved1 : 7;
	} s;
	T_UBYTE all[LIN_MSG_DLEN_SLAVE4_RSP];
}S_SLAVE4_RSP;

typedef union{
	struct{
		T_UBYTE slave1_supplier : 8;
		T_UBYTE slave1_serial[6];
	} s;
	T_UBYTE all[LIN_MSG_DLEN_SLAVE1_ID];
}S_SLAVE1_ID;

typedef union{
	struct{
		T_UBYTE slave2_supplier : 8;
		T_UBYTE slave2_serial[6];
	} s;
	T_UBYTE all[LIN_MSG_DLEN_SLAVE2_ID];
}S_SLAVE2_ID;

typedef union{
	struct{
		T_UBYTE slave3_supplier : 8;
		T_UBYTE slave3_serial[6];
	} s;
	T_UBYTE all[LIN_MSG_DLEN_SLAVE3_ID];
}S_SLAVE3_ID;

typedef union{
	struct{
		T_UBYTE slave4_supplier : 8;
		T_UBYTE slave4_serial[6];
	} s;
	T_UBYTE all[LIN_MSG_DLEN_SLAVE4_ID];
}S_SLAVE4_ID;


#endif /* LINSIGNALS_H_ */
