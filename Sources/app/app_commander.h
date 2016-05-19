/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        app_commander.h
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

#ifndef APP_COMMANDER_H_
#define APP_COMMANDER_H_

#include "stdtypedef.h"

typedef enum{
	BTTN_NOT_DEBOUNCED,
	BTTN_DEBOUNCED1,
	BTTN_DEBOUNCED2
}E_BTTN_STATE;

typedef struct{
	T_UWORD debounce1Ticks;
	T_UWORD debounce2Ticks;
	T_UWORD currentTicks;
	T_UBYTE releasedAt1;
	T_UBYTE releasedAt2;
	E_BTTN_STATE state;
}S_BUTTON;

/* Define High-Level commands */
typedef enum{
	HLC_NONE,
	HLC_LED_ON,
	HLC_LED_OFF,
	HLC_LED_TOGGLING,
	HLC_DISABLE_SLV,
	HLC_ENABLE_SLV,
	HLC_GET_IDS
}E_HL_COMMANDS;


/* Define High-Level target */
#define	TARGET_SINGLE_SLAVE		0
#define	TARGET_ALL_SLAVES		1

/* Following PINS are all related to PORTE */
#define PIN_IN_CMD_0		30		
#define PIN_IN_CMD_1		29
#define PIN_IN_CMD_2		23

#define PIN_IN_BUTTON		20

#define PIN_IN_TARGET_0		22
#define PIN_IN_TARGET_1		21

#define PIN_OUT_LED_SLV1	2
#define PIN_OUT_LED_SLV2	3
#define PIN_OUT_LED_SLV3	4
#define PIN_OUT_LED_SLV4	5

#define HLC_READ_INPUT(pin)			(!((GPIOE_PDIR >> pin) & 1))
#define HLC_SET_OUTPUT(pin)			(GPIOE_PSOR |= (1 << pin))
#define HLC_CLEAR_OUTPUT(pin)		(GPIOE_PCOR |= (1 << pin))
#define HLC_TOGGLE_OUTPUT(pin)		(GPIOE_PTOR |= (1 << pin))

extern void app_commander_init();
extern void app_processButton(S_BUTTON * button, T_UBYTE currentValue);
extern void app_commander_action_task();
extern void app_commander_status_task();
extern void app_commander_led_task();

#endif /* APP_COMMANDER_H_ */
