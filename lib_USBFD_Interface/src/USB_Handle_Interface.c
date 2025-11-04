
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void USB_Handle_Interface( struct USBStruct *us )
{
struct USBNotifyMsg *msg;

	MYDEBUG( "USBFD : USB_Handle_Interface - Enter -" );

	while( TRUE )
	{
		msg = (PTR) GetMsg( us->Interface_MsgPort );

		if ( ! msg )
		{
			break;
		}

		if ( msg->Type == USBNM_TYPE_INTERFACEDETACH )
		{
			// Someone Detached our Device, lets quit
			us->Running = FALSE;
		}

		ReplyMsg( (PTR) msg );
	}

	MYDEBUG( "USBFD : USB_Handle_Interface - Leave -" );
}

// --
