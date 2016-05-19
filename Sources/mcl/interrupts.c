/*============================================================================*/
/*                     AZOR - EMBEDDED SYSTEMS SOFTWARE                       */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        interrupts.c
* version:         1.0 
* created_by:      David Robles  
* date_created:    Aug 12 2013 
*=============================================================================*/
/* DESCRIPTION : C source for inerrupts management                             */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source template according to  */
/* the new software platform                                                  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 12/08/2013  |                               | David Robles     */
/* First version of this source                                               */
/*============================================================================*/

/* Includes */
/* -------- */
#include "interrupts.h"


void HandlerC(long *hardfault_args);

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */

/* WORD constants */

/* LONG and STRUCTURE constants */

/* Custom type constants */


/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */

/* WORD RAM variables */

/* LONG and STRUCTURE RAM variables */

/* Custom type RAM variables */

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */

/* Private functions prototypes */
/* ---------------------------- */


/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : inline_func	2
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	export_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/

void interrupts_enableIRQ(E_IRQ le_irq)
{
	if((T_UBYTE)le_irq < 32u)
	{
		NVIC_ICPR |= (1ul << (T_UBYTE)le_irq);
		NVIC_ISER |= (1ul << (T_UBYTE)le_irq);
	}
}

void interrupts_disableIRQ(E_IRQ le_irq)
{
	NVIC_ICER |= (1ul << (T_UBYTE)le_irq);
}



void NMI_Handler(){
	
}
//void HardFault_Handler(){
	
//}

/**
 * This is called from the HardFaultHandler with a pointer the Fault stack
 * as the parameter. We can then read the values from the stack and place them
 * into local variables for ease of reading.
 * We then read the various Fault Status and Address Registers to help decode
 * cause of the fault.
 * The function ends with a BKPT instruction to force control back into the debugger
 */
void HandlerC(long *hardfault_args)
{
  volatile unsigned long stacked_r0;
  volatile unsigned long stacked_r1;
  volatile unsigned long stacked_r2;
  volatile unsigned long stacked_r3;
  volatile unsigned long stacked_r12;
  volatile unsigned long stacked_lr;
  volatile unsigned long stacked_pc;
  volatile unsigned long stacked_psr;
  volatile unsigned long _CFSR;
  volatile unsigned long _HFSR;
  volatile unsigned long _DFSR;
  volatile unsigned long _AFSR;
  volatile unsigned long _BFAR;
  volatile unsigned long _MMAR;
 
  stacked_r0 = ((unsigned long)hardfault_args[0]);
  stacked_r1 = ((unsigned long)hardfault_args[1]);
  stacked_r2 = ((unsigned long)hardfault_args[2]);
  stacked_r3 = ((unsigned long)hardfault_args[3]);
  stacked_r12 = ((unsigned long)hardfault_args[4]);
  stacked_lr = ((unsigned long)hardfault_args[5]);
  stacked_pc = ((unsigned long)hardfault_args[6]);
  stacked_psr = ((unsigned long)hardfault_args[7]);
 
  /* Configurable Fault Status Register */
  /* Consists of MMSR, BFSR and UFSR */
  _CFSR = (*((volatile unsigned long *)(0xE000ED28)));
 
  /* Hard Fault Status Register */
  _HFSR = (*((volatile unsigned long *)(0xE000ED2C)));
 
  /* Debug Fault Status Register */
  _DFSR = (*((volatile unsigned long *)(0xE000ED30)));
 
  /* Auxiliary Fault Status Register */
  _AFSR = (*((volatile unsigned long *)(0xE000ED3C)));
 
  /* Read the Fault Address Registers. These may not contain valid values.
   * Check BFARVALID/MMARVALID to see if they are valid values
   * MemManage Fault Address Register
   */
  _MMAR = (*((volatile unsigned long *)(0xE000ED34)));
  /* Bus Fault Address Register */
  _BFAR = (*((volatile unsigned long *)(0xE000ED38)));
 
  __asm("BKPT #0\n") ; /* cause the debugger to stop */
  
  /* suppress warnings about unused variables */
	(void)stacked_r0;
	(void)stacked_r1;
	(void)stacked_r2;
	(void)stacked_r3;
	(void)stacked_r12;
	(void)stacked_lr;
	(void)stacked_pc;
	(void)stacked_psr;
	(void)_CFSR;
	(void)_HFSR;
	(void)_DFSR;
	(void)_AFSR;
	(void)_BFAR;
	(void)_MMAR;
}

__attribute__((naked)) void HardFault_Handler(void)
{
  __asm volatile (
    " movs r0,#4      \n"  /* load bit mask into R0 */
    " movs r1, lr     \n"  /* load link register into R1 */
    " tst r0, r1      \n"  /* compare with bitmask */
    " beq _MSP        \n"  /* if bitmask is set: stack pointer is in PSP. Otherwise in MSP */
    " mrs r0, psp     \n"  /* otherwise: stack pointer is in PSP */
    " b _GetPC        \n"  /* go to part which loads the PC */
    "_MSP:            \n"  /* stack pointer is in MSP register */
    " mrs r0, msp     \n"  /* load stack pointer into R0 */
    "_GetPC:          \n"  /* find out where the hard fault happened */
    " ldr r1,[r0,#20] \n"  /* load program counter into R1. R1 contains address of the next instruction where the hard fault happened */
    " b HandlerC      \n"  /* decode more information. R0 contains pointer to stack frame */
  );
  HandlerC(0); /* dummy call to suppress compiler warning */
}



void SVC_Handler(){
	
}
void PendSV_Handler() {
	
}
//void SysTick_Handler(){
//	
//}

void DMA0_IRQHandler(){
	
}
void DMA1_IRQHandler(){
	
}
void DMA2_IRQHandler() {
	
}
void DMA3_IRQHandler(){
	
}
void MCM_IRQHandler() {
	
}
void FTFL_IRQHandler(){
	
};
void PMC_IRQHandler(){
	
}
void LLW_IRQHandler() {
	
}
void I2C0_IRQHandler() {
	
}
void I2C1_IRQHandler() {
	
}
void SPI0_IRQHandler() {
	
}
void SPI1_IRQHandler() {
	
}
//void UART0_IRQHandler(){
//	
//}
//void UART1_IRQHandler() {
//	
//}
void UART2_IRQHandler() {
	
}
void ADC0_IRQHandler() {
	
}
void CMP0_IRQHandler() {
	
}
void FTM0_IRQHandler() {
	
}
void FTM1_IRQHandler() {
	
}
void FTM2_IRQHandler() {
	
}
void RTC_Alarm_IRQHandler() {
	
}
void RTC_Seconds_IRQHandler() {
	
}
void PIT_IRQHandler(){
	
}
void USBOTG_IRQHandler() {
	
}
void DAC0_IRQHandler(){
	
}
void TSI0_IRQHandler(){
	
}
void MCG_IRQHandler(){
	
}
void LPTimer_IRQHandler() {
	
}
void PORTA_IRQHandler() {
	
}
void PORTD_IRQHandler() {
	
}

