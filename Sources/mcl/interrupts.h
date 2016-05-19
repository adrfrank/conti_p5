/*============================================================================*/
/*                     AZOR - EMBEDDED SYSTEMS SOFTWARE                       */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:       interrupts.h
* version:         1.0 
* created_by:      David Robles  
* date_created:    Aug 12 2013 
*=============================================================================*/
/* DESCRIPTION : Header file of interrupt handling                            */
/*============================================================================*/
/* FUNCTION COMMENT : contains only symbols which are exported to internal    */
/* platform modules. This will not be delivered with the library              */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 12/08/2013  |                               | David Robles     */
/* First version of this header                                               */
/*============================================================================*/

#ifndef INTERRUPTS_H                               /* To avoid double inclusion */
#define INTERRUPTS_H

/* Includes */
/* -------- */
#include "stdtypedef.h"

typedef enum{
	E_IRQ_DMA0 = 0u,
	E_IRQ_DMA1,
	E_IRQ_DMA2,
	E_IRQ_DMA3,
	E_IRQ_UNUSED0,
	E_IRQ_FTFA,
	E_IRQ_PMC,
	E_IRQ_LLWU,
	E_IRQ_I2C0,
	E_IRQ_I2C1,
	E_IRQ_SPI0,
	E_IRQ_SPI1,
	E_IRQ_UART0,
	E_IRQ_UART1,
	E_IRQ_UART2,
	E_IRQ_ADC0,
	E_IRQ_CMP0,
	E_IRQ_TPM0,
	E_IRQ_TPM1,
	E_IRQ_TPM2,
	E_IRQ_RTC0,
	E_IRQ_RTC1,
	E_IRQ_PIT,
	E_IRQ_UNUSED1,
	E_IRQ_USB,
	E_IRQ_DAC0,
	E_IRQ_TSI0,
	E_IRQ_MCG,
	E_IRQ_LPTMR0,
	E_IRQ_UNUSED2,
	E_IRQ_PortA,
	E_IRQ_PortD,
}E_IRQ;

/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */


/*======================================================*/ 
/* Declaration of exported constants                    */
/*======================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */


/* Custom type constants */


/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTES */


/* WORDS */


/* LONGS and STRUCTURES */


/* Custom type RAM variables */

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */
extern void interrupts_enableIRQ(E_IRQ le_irq);
extern void interrupts_disableIRQ(E_IRQ le_irq);

/* Functions macros */


/* Exported defines */


#endif


