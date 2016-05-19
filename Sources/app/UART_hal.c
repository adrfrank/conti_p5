/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        UART_hal.c
* version:         1.0 
* created_by:      Carlos Calvillo
* date_created:    23/10/2013
*=============================================================================*/
/* DESCRIPTION : UART Hardware Abstraction Layer (HAL)                        */
/*============================================================================*/
/* FUNCTION COMMENT : Implements the hardware interfaces for the UARTx        */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 20/10/2013  |                               | Carlos Calvillo  */
/*  First Implementation.                                                     */
/*============================================================================*/

#include "UART_hal.h"
#include "LIN_mstr_hal.h"
#include "LIN_slave_hal.h"
#include "CrystalClock.h"
#include "interrupts.h"

/* ==================================================================================================== */
/* ==================================================================================================== */
/*                                             UART0 APIs                                               */
/* ==================================================================================================== */
/* ==================================================================================================== */
/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
T_UBYTE uart0_setBaudRate(T_ULONG sysclk, T_ULONG lul_inBaud)
{
	T_UBYTE lub_success = 0;
	T_UBYTE lub_i;
	T_ULONG lul_calculatedBaud = 0;
	T_ULONG lul_baudDiff = 0;
	T_ULONG lul_osrVal = 0;
	T_ULONG lul_sbrVal;
	T_ULONG lul_uartClk;
	T_ULONG lul_baudRate;
	T_ULONG lul_tempRegister = 0;
	T_ULONG lul_temp = 0;
    
	// Verify that a valid clock value has been passed to the function 
	if ((sysclk > 50000) || (sysclk < 32))
	{
		/* Invalid input clock. Do not do anything and flag the error */
		lub_success = 0;	
	} 
	else 
	{
		/* Valid input clock. Proceed. */
		
		// Initialize baud rate
		lul_baudRate = lul_inBaud;
		
		// Change units to Hz
		lul_uartClk = sysclk * 1000;
		
		// Calculate the first baud rate using the lowest OSR value possible.  
		lub_i = 4;
		lul_sbrVal = (T_ULONG)(lul_uartClk/(lul_baudRate * lub_i));
		lul_calculatedBaud = (lul_uartClk / (lub_i * lul_sbrVal));
		/* Estimate difference between required baud rate (input) and current one */	
		if (lul_calculatedBaud > lul_baudRate)
		{
			lul_baudDiff = lul_calculatedBaud - lul_baudRate;
		}
		else
		{
			lul_baudDiff = lul_baudRate - lul_calculatedBaud;
		}
		
		lul_osrVal = lub_i;
		
		/* Iterate over various values of OSR in order to select a better approximation for the
		 * desired baud rate */
		for (lub_i = 5; lub_i <= 32; lub_i++)
		{
			lul_sbrVal = (T_ULONG)(lul_uartClk/(lul_baudRate * lub_i));
			lul_calculatedBaud = (lul_uartClk / (lub_i * lul_sbrVal));
			/* Calculate difference */
			if (lul_calculatedBaud > lul_baudRate)
			{
				lul_temp = lul_calculatedBaud - lul_baudRate;
			}
			else
			{
				lul_temp = lul_baudRate - lul_calculatedBaud;
			}
			/* Check if new difference is smaller than initial one, i.e., baud rate approximation gets better */
			if (lul_temp <= lul_baudDiff)
			{
				/* New better value of OSR found. Use this one. */
				lul_baudDiff = lul_temp;
				lul_osrVal = lub_i; 
			}
		}
		
		/* Iteration is over. Now check if the final baud rate approximation is valid */
		if (lul_baudDiff < ((lul_baudRate / 100) * 3))
		{
			/* Disable UARTx before changing registers */
			/* --------------------------------------- */
			UART0_DISABLE_TX_RX();
			
			// If the OSR is between 4x and 8x then both edge sampling MUST be turned on.  
			if ((lul_osrVal >3) && (lul_osrVal < 9))
			{
				UART0_C5|= UART0_C5_BOTHEDGE_MASK;
			}
			
			/* Setup OSR value inside UARTx_C4 register */
			/* ---------------------------------------- */
			lul_tempRegister = UART0_C4;
			lul_tempRegister &= ~UART0_C4_OSR_MASK;
			lul_tempRegister |= UART0_C4_OSR(lul_osrVal-1);
			UART0_C4 = lul_tempRegister;
			
			/* Calculate value of SBR */
			lul_tempRegister = (lul_tempRegister & UART0_C4_OSR_MASK) + 1;
			lul_sbrVal = (T_ULONG)((lul_uartClk)/(lul_baudRate * (lul_tempRegister)));
			
			/* Setup SBR value inside both UARTx_DBH and UARTx_DBL registers */
			/* ------------------------------------------------------------- */
			 /* Save off the current value of the uartx_BDH except for the SBR field */
			lul_tempRegister = UART0_BDH & ~(UART0_BDH_SBR(0x1F));
			/* Write most-significant part of SBR insider UARTx_BDH register */
			UART0_BDH = lul_tempRegister |  UART0_BDH_SBR(((lul_sbrVal & 0x1F00) >> 8));
			/* Write least-significant part of SBR insider UARTx_BDH register */
			UART0_BDL = (T_UBYTE)(lul_sbrVal & UART0_BDL_SBR_MASK);
			
			/* Flag that everything is Ok */
			lub_success = 1;
		}
		else
		{
			/* Unacceptable baud rate difference. More than 3% difference!!
			 * Do not change any register and only exit the function flagging a failure */
			lub_success = 0;
		}
    } 
	
    return(lub_success); 
}


/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
T_UBYTE uart0_initHal(T_ULONG lul_baudRate)
{
	T_UBYTE lub_success = 0;
	T_ULONG lul_UARTclk;
	
	/* PORT pins for UART */
	/* ------------------ */
	/* UART0 pins are chosen to alternative functions of PORTA pins 1 (UART0_RX) and pin 2 (UART0_TX) */
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;	/* Enable Clock for PORTA, this must be done before configuring 
										 * anything else of PORTA, otherwise a "hardFault" error may occur */
	PORTA_PCR1 = PORT_PCR_MUX(2) | PORT_PCR_DSE_MASK; /* Select PIN alternative 2 --> UART0_RX */
	PORTA_PCR2 = PORT_PCR_MUX(2) | PORT_PCR_DSE_MASK; /* Select PIN alternative 2 --> UART0_TX */
	
	/* Clock settings for UART */
	/* ----------------------- */
	/* Configure Clock for UART0 to be PLL/2 */
	SIM_SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK; /* Clear bits for UART0SRC */
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1); /* Set UART0SRC = 1 --> MCGFLLCLK clock or MCGPLLCLK/2 clock */
	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK; /* Set PLLFLLSEL = 1 --> MCGPLLCLK/2 */
			
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK; /* Enable Clock for UART0 */
	
	lul_UARTclk = rul_currentSystemClockHz/2/1000; /* Clock to be feed to baud rate init function shall be in Khz */
	lub_success = uart0_setBaudRate(lul_UARTclk, lul_baudRate);
	
	/* Other configurations for the UART */
	/* --------------------------------- */
	UART0_S2 |= UART_S2_BRK13_MASK; /* Select Brake symbol to be 13 bits */

	/* Enable receiver and transmitter */
	/* ------------------------------- */
	UART0_ENABLE_TX_RX();
	
	/* Enable TX and RX IRQ  */
	/* --------------------- */
	UART0_DISABLE_TX_RX_INT();
	interrupts_enableIRQ(E_IRQ_UART0);

	return(lub_success);
}


/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
T_UBYTE uart0_sendBreak()
{
	T_UBYTE lub_retVal = 0;
	
	if(UART0_S1 & UART_S1_TDRE_MASK){
		/* Buffer for TX is empty, can proceed with this request */
		/* To send a break symbol we need to write 1 and then 0 to SBK bit of register UARTx_C2 */
		UART0_C2 |= UART_C2_SBK_MASK;
		UART0_C2 &= ~UART_C2_SBK_MASK;
		lub_retVal = 1;
	} else {
		/* Not possible to continue with this request. Retry later */
	}
	
	return(lub_retVal);
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
T_UBYTE uart0_sendByte(T_UBYTE lub_data)
{
	T_UBYTE lub_retVal = 0;
	
	if(UART0_S1 & UART_S1_TDRE_MASK){
		/* Buffer for TX is empty, can proceed with this request */
		lub_retVal = 1;
		/* To send a data byte just write UARTx_D register with the TX data*/
		UART0_D = lub_data;
	} else {
		/* Not possible to continue with this request. Retry later */
		lub_retVal = 0;
	}

	return(lub_retVal);
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
T_UBYTE uart0_getByte()
{
	return(UART0_D);
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void uart0_TX_ISR()
{
#if COMPILE_LIN_MASTER_NODE
	linMstrHal_TxISR();
#endif
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void uart0_RX_ISR()
{
#if COMPILE_LIN_MASTER_NODE
	linMstrHal_RxISR();
#endif
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void UART0_IRQHandler(void)
{
	volatile T_UBYTE lub_temp_UART0_D;
	
	/* Unified Interrupt Service Routine for all UART0 interrupts */
	/* Discriminate the source of the interrupt and call the appropriate
	 * function */
	
	/* ISRs for flags of UARTx_S1 */
	/* -------------------------- */
//	if(lub_temp_UART0_S1 & UART_S1_TDRE_MASK)
//	{
//		
//	}
	if((UART0_C2 & UART0_C2_TCIE_MASK) && (UART0_S1 & UART0_S1_TC_MASK))
	{
		/* Transmission Complete Flag */
		uart0_TX_ISR();
	}
//	if(lub_temp_UART0_S1 & UART0_S1_RDRF_MASK)
//	{
//		/* Receive Data Register Full Flag */
//		uart0_RX_ISR();
//	}
	if((UART0_C2 & UART0_C2_RIE_MASK) && (UART0_S1 & UART0_S1_RDRF_MASK))
	{
		/* Receive Data Register Full Flag */
		uart0_RX_ISR();
	}
//	if(lub_temp_UART0_S1 & UART_S1_IDLE_MASK)
//	{
//		
//	}
	if((UART0_S1 & UART0_S1_FE_MASK) || (UART0_S1 & UART0_S1_NF_MASK)
		|| (UART0_S1 & UART0_S1_OR_MASK))
	{
		/* Clear flag by reading the UARTx_D register */
		lub_temp_UART0_D = UART0_D;
	}
//	if(lub_temp_UART0_S1 & UART_S1_PF_MASK)
//	{
//		
//	}
   
	/* ISRs for flags of UARTx_S2 */	
	/* -------------------------- */
//	if(lub_temp_UART0_S2 & UART_S2_LBKDIF_MASK)
//	{
//		UART0_S2 |= UART0_S2_LBKDIF_MASK; /* Clear flag by writing 1 to it */
//	}
//	if(lub_temp_UART0_S2 & UART_S2_RXEDGIF_MASK)
//	{
//		UART0_S2 |= UART_S2_RXEDGIF_MASK; /* Clear flag by writing 1 to it */
//	}
//	if(lub_temp_UART0_S2 & UART_S2_RAF_MASK)
//	{
//		
//	}
	
	(void)lub_temp_UART0_D; /* This line of code is only to remove the "variable set but not used" warning */
}

/* ==================================================================================================== */
/* ==================================================================================================== */
/*                                             UART1 APIs                                               */
/* ==================================================================================================== */
/* ==================================================================================================== */

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
T_UBYTE uart1_setBaudRate(T_ULONG sysclk, T_ULONG lul_inBaud)
{
	T_UBYTE lub_success = 0;
	T_ULONG lul_calculatedBaud = 0;
	T_ULONG lul_baudDiff = 0;
	T_ULONG lul_sbrVal;
	T_ULONG lul_uartClk;
	T_ULONG lul_baudRate;
	T_ULONG lul_tempRegister = 0;
    
	// Verify that a valid clock value has been passed to the function 
	if ((sysclk > 50000) || (sysclk < 32))
	{
		/* Invalid input clock. Do not do anything and flag the error */
		lub_success = 0;	
	}
	else
	{
		/* Valid input clock. Proceed. */
		
		// Initialize baud rate
		lul_baudRate = lul_inBaud;
		
		// Change units to Hz
		lul_uartClk = sysclk * 1000;
		
		/* Baud Rate calculation for UART1 and UART2 is different than for UART0, however UART1 and UART2 baud
		 * rate calculation is same between both. */
		
		/* Calculate value of SBR */
		lul_sbrVal = (T_ULONG)((lul_uartClk)/(lul_baudRate << 4u));
		lul_calculatedBaud = (lul_uartClk / (lul_sbrVal << 4));
		
		/* Calculate difference */
		if (lul_calculatedBaud > lul_baudRate)
		{
			lul_baudDiff = lul_calculatedBaud - lul_baudRate;
		}
		else
		{
			lul_baudDiff = lul_baudRate - lul_calculatedBaud;
		}
		/* Verify that real baud rate is within tolerance: +/- 3% */
		if (lul_baudDiff < ((lul_baudRate / 100) * 3))
		{
			/* Disable UARTx before changing registers */
			/* --------------------------------------- */
			UART1_DISABLE_TX_RX();
			
			/* Setup SBR value inside both UARTx_DBH and UARTx_DBL registers */
			/* ------------------------------------------------------------- */
			 /* Save off the current value of the uartx_BDH except for the SBR field */
			lul_tempRegister = UART1_BDH & ~(UART_BDH_SBR(0x1F));
			/* Write most-significant part of SBR insider UARTx_BDH register */
			UART1_BDH = lul_tempRegister |  UART_BDH_SBR(((lul_sbrVal & 0x1F00) >> 8));
			/* Write least-significant part of SBR insider UARTx_BDH register */
			UART1_BDL = (T_UBYTE)(lul_sbrVal & UART_BDL_SBR_MASK);
			
			/* Flag that everything is Ok */
			lub_success = 1;
		}
		else
		{
			/* Unacceptable baud rate difference. More than 3% difference!!
			 * Do not change any register and only exit the function flagging a failure */
			lub_success = 0;
		}	
    } 
	
    return(lub_success); 
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
T_UBYTE uart1_initHal(T_ULONG lul_baudRate)
{
	T_UBYTE lub_success = 0;
	T_ULONG lul_UARTclk;
	
	/* PORT pins for UART */
	/* ------------------ */
	/* UART1 pins are chosen to alternative functions of PORTE pins 0 (UART1_TX) and pin 2 (UART1_RX) */
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;	/* Enable Clock for PORTE, this must be done before configuring 
										 * anything else of PORTE, otherwise a "hardFault" error may occur */
	PORTE_PCR0 = PORT_PCR_MUX(3) | PORT_PCR_DSE_MASK; /* Select PIN alternative 2 --> UART1_TX */
	PORTE_PCR1 = PORT_PCR_MUX(3) | PORT_PCR_DSE_MASK; /* Select PIN alternative 2 --> UART1_RX */
	
	/* Clock settings for UART */
	/* ----------------------- */
	SIM_SCGC4 |= SIM_SCGC4_UART1_MASK; /* Enable Clock for UART1 */
	
	lul_UARTclk = rul_currentSystemClockHz/2/1000; /* Clock to be feed to baud rate init function shall be in Khz */
	lub_success = uart1_setBaudRate(lul_UARTclk, lul_baudRate);
	
	/* Other configurations for the UART */
	/* --------------------------------- */	
	UART1_ENABLE_13BIT_BREAK_RX(); /* Enable LIN 13-bit break detection */
	
	/* Enable receiver and transmitter */
	/* ------------------------------- */
	UART1_ENABLE_TX_RX();
	
	/* Enable TX and RX IRQ  */
	/* --------------------- */
	UART1_DISABLE_TX_RX_INT();
	interrupts_enableIRQ(E_IRQ_UART1);

	return(lub_success);
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
T_UBYTE uart1_sendBreak()
{
	T_UBYTE lub_retVal = 0;
	
	if(UART1_S1 & UART_S1_TDRE_MASK){
		/* Buffer for TX is empty, can proceed with this request */
		/* To send a break symbol we need to write 1 and then 0 to SBK bit of register UARTx_C2 */
		UART1_C2 |= UART_C2_SBK_MASK;
		UART1_C2 &= ~UART_C2_SBK_MASK;
		lub_retVal = 1;
	} else {
		/* Not possible to continue with this request. Retry later */
	}
	
	return(lub_retVal);
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
T_UBYTE uart1_sendByte(T_UBYTE lub_data)
{
	T_UBYTE lub_retVal = 0;
	
	if(UART1_S1 & UART_S1_TDRE_MASK){
		/* Buffer for TX is empty, can proceed with this request */
		lub_retVal = 1;
		/* To send a data byte just write UARTx_D register with the TX data*/
		UART1_D = lub_data;
	} else {
		/* Not possible to continue with this request. Retry later */
		lub_retVal = 0;
	}

	return(lub_retVal);
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
T_UBYTE uart1_getByte()
{
	return(UART1_D);
}

/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void UART1_IRQHandler(void)
{
	volatile T_UBYTE lub_temp_UART1_D;
	
	/* Unified Interrupt Service Routine for all UART1 interrupts */
	/* Discriminate the source of the interrupt and call the appropriate
	 * function */
	
	/* ISRs for flags of UARTx_S1 */
	/* -------------------------- */
//	if(lub_temp_UART1_S1 & UART_S1_TDRE_MASK)
//	{
//		
//	}
	if((UART1_C2 & UART_C2_TCIE_MASK) && (UART1_S1 & UART_S1_TC_MASK))
	{
		/* Transmission Complete Flag */
		linSlvHal_TxISR();
	}
	if((UART1_C2 & UART_C2_RIE_MASK) && (UART1_S1 & UART_S1_RDRF_MASK))
	{
		/* Receive Data Register Full Flag */
		linSlvHal_RxISR();
	}
//	if(lub_temp_UART1_S1 & UART_S1_IDLE_MASK)
//	{
//		
//	}
	if((UART1_S1 & UART_S1_FE_MASK) || (UART1_S1 & UART_S1_NF_MASK)
		|| (UART1_S1 & UART_S1_OR_MASK))
	{
		/* Clear flag by reading the UARTx_D register */
		lub_temp_UART1_D = UART1_D;
	}
//	if(lub_temp_UART1_S1 & UART_S1_PF_MASK)
//	{
//		
//	}
   
	/* ISRs for flags of UARTx_S2 */	
	/* -------------------------- */
	if((UART1_BDH & UART_BDH_LBKDIE_MASK) && (UART1_S2 & UART_S2_LBKDIF_MASK))
	{
		UART1_S2 |= UART_S2_LBKDIF_MASK; /* Clear flag by writing 1 to it */
		linSlvHal_RxBreakDetectedISR();
	}
//	if(lub_temp_UART1_S2 & UART_S2_RXEDGIF_MASK)
//	{
//		UART1_S2 |= UART_S2_RXEDGIF; /* Clear flag by writing 1 to it */
//	}
//	if(lub_temp_UART1_S2 & UART_S2_RAF_MASK)
//	{
//		
//	}
	
	(void)lub_temp_UART1_D; /* This line of code is only to remove the "variable set but not used" warning */
}
