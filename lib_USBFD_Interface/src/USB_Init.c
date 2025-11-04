
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

S32 USB_Init( struct USBStruct *us )
{
S32 retval;

	MYDEBUG( "USBFD : USB_Init - Enter" );

	retval = FALSE;

	/* Setup and Claim Interface */

	us->Interface_MsgPort = AllocSysObjectTags( ASOT_PORT, TAG_END );

	if ( ! us->Interface_MsgPort ) 
	{
		MYERROR( "USBFD : Error Creating Interface MsgPort" );
		goto bailout;
	}

	us->Interface_Bit	= 1UL << us->Interface_MsgPort->mp_SigBit;
	us->Interface		= USBClaimInterface( us->StartMsg->Object, (PTR) -1, us->Interface_MsgPort );

	if ( ! us->Interface ) 
	{
		MYERROR( "USBFD : Error Claiming Interface" );
		goto bailout;
	}

	retval = TRUE;

bailout:

	MYDEBUG( "USBFD : USB_Init - Leave - Retval %ld", retval );

	return( retval );
}

// --
