#include "ARM_SysTick.h"
#include "derivative.h"
#include "CrystalClock.h"

//Since this SysTick is part of the Cortex M0 Core,   you need to look in the 
//Cortex M0 Generic users Guide



//See Section 4.4
void InitSysTick()
{
	SYST_RVR = CORE_CLOCK/SYSTICK_FREQUENCY;
	SYST_CSR = SysTick_CSR_ENABLE_MASK | SysTick_CSR_TICKINT_MASK | SysTick_CSR_CLKSOURCE_MASK;
	//Important!  Since the Systick is part of the Cortex core and NOT a kinetis peripheral
	// its Interrupt line is not passed through NVIC.   You need to make sure that
	//the SysTickIRQ function is poopulated in the vector table.  See the kinetis_sysinit.c file
}


