
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void USB_Free( struct USBStruct *us )
{
	MYDEBUG( "USBFD : USB_Free - Enter -" );

	if ( us->Interface )
	{
		USBDeclaimInterface( us->Interface );
		us->Interface = NULL;
	}

	if ( us->Interface_MsgPort )
	{
		FreeSysObject( ASOT_PORT, us->Interface_MsgPort );
		us->Interface_MsgPort = NULL;
	}

	MYDEBUG( "USBFD : USB_Free - Leave -" );
}

// --
