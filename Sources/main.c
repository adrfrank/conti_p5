/****************************************************************************
 * Project developed as a simple Blink the LED's to 
 * demonstrate basic CodeWarrior functionality and capability.
 * Borrowed from Freedom Example Projects: Blinky
 * 
 * Date: 11 Sept 2012
 * Author: M. Ruthenbeck
 * Revision Level 1.0
 */

#include "derivative.h" /* include peripheral declarations */
#include "CrystalClock.h"
#include "ARM_SysTick.h"
#include "gsc_sch_core_intf.h"

volatile unsigned int sys_tick_counter = 0;

void WatchDog_cfg(void);
/********************************************************************/
int main (void)
{
	//int i=0;
	
	/* Disable Watch Dog */
	WatchDog_cfg();
	
	/* initialize clock system for 48 MHz */
	InitClock(); 
	/* Configure the timer and the interrupt to be used to generate the tick of the scheduler */
	InitSysTick();
	/* Scheduler Initialization and tasks initialization  */
	gsc_sch_core_Init();
	/* Execute Scheduler */
	gsc_sch_core_exec();

	return 0;
}

 
 /*
  * Init watch dog
  */
 void WatchDog_cfg(void)
 {
	 /* Disable watch dog */
	 SIM_COPC |= SIM_COPC_COPT(0);
 }
 
 void SysTick_Handler(void)
 {
 	sys_tick_counter++;
 	gsc_sch_core_tick_isr();
 }

