/*============================================================================*/
/*                  CONTINENTAL AUTOMOTIVE SYSTEMS AG                         */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        LINcommon.c
* version:         1.0 
* created_by:      Carlos Calvillo
* date_created:    19/09/2013
*=============================================================================*/
/* DESCRIPTION : LIN common defines and functions                             */
/*============================================================================*/
/* FUNCTION COMMENT :  This file is intended to provide common functionality  */
/* for both LIN master and or LIN slave                                       */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 19/09/2013  |                               | Carlos Calvillo  */
/*  First implementation.                                                     */
/*============================================================================*/

#include "LIN_common.h"
/**************************************************************
 *  Name                 : lincomm_calculateChksum
 *  Description          : This function calculates the checksum for a given set of data.
 *  Parameters           : [in] lub_msgIdValue -> Id of the message. 
 *  					   This is to be used for the checksum calculation if the related message requires enhanced checksum.
 *  					   If not enhanced checksum is required then this parameter shall be 0x00.
 *  					   [in] lpub_data -> data to be used for the checksum calculation.
 *  					   [in] lpub_data -> data length.
 *  Return               : This function returns the calculated checksum as per the inputs.
 *  Critical/explanation : No
 **************************************************************/
T_UBYTE lincomm_calculateChksum(T_UBYTE lub_msgIdValue, T_UBYTE * lpub_data, T_UBYTE lub_dataLen)
{
	T_UBYTE lub_checksum;
	T_UWORD luw_tmpChksum;
	T_UBYTE lub_it;

	/* Initialize checksum calculation variable */
	luw_tmpChksum = lub_msgIdValue;

	for (lub_it = 0; lub_it < lub_dataLen; lub_it++ )
	{
		/* Checksum calculation */
		luw_tmpChksum += lpub_data[lub_it];
		/* Greater than 0xFF, carry has occurred, save as a byte and add 1 */
		if (luw_tmpChksum > 0xFF)
		{
			luw_tmpChksum = (luw_tmpChksum & 0x00FF) + 0x0001;
		}
	}
	lub_checksum = (T_UBYTE)~luw_tmpChksum;

	return(lub_checksum);
}

/**************************************************************
 *  Name                 : lincomm_checkIDparityBits
 *  Description          : This function checks if the given ID pairty bits are OK.
 *  Parameters           : [in] lub_msgIdValue -> Id of the message. 
 *  Return               : This function returns true if the ID is correct and 
 *  					   false if there is a parity bit error.
 *  Critical/explanation : No
 **************************************************************/
T_UBYTE lincomm_checkIDparityBits(T_UBYTE lub_msgIdValue)
{
	T_UBYTE lub_parityMatch;
	T_UBYTE lub_calculatedID;
	T_UBYTE lub_P0;
	T_UBYTE lub_P1;
	
	/* Calculate pairty bits */
	lub_P0 = (lub_msgIdValue & 1) ^ ((lub_msgIdValue >> 1) & 1) ^ ((lub_msgIdValue >> 2) & 1) ^ ((lub_msgIdValue >> 4) & 1);
	lub_P1 = ~(((lub_msgIdValue >> 1) & 1) ^ ((lub_msgIdValue >> 3) & 1) ^ ((lub_msgIdValue >> 4) & 1) ^ ((lub_msgIdValue >> 5) & 1));
	/* Write parity bits */
	lub_calculatedID = (lub_msgIdValue & 0x3F) | (lub_P0 << 6) | (lub_P1 << 7);
	/* Compare calculated ID with input ID */
	lub_parityMatch = (lub_calculatedID == lub_msgIdValue) ? 1 : 0;
	
	return(lub_parityMatch);
}
