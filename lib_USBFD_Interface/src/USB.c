
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

S32 USB_Driver( struct Test_USBFDIFace *Self UNUSED, struct USBFDStartupMsg *msg )
{
struct USBStruct us;
S32 retval;
U32 wait;
U32 mask;

	MYDEBUG( "USBFD : USB_Driver - Enter -" );

	// Default to an error
	retval = USBERR_NOMEM;

	// --
	// Device Base and Main Interface should be that same 
	// for all as there are only one USB Stack

	if ( ! USBSysBase )
	{
		USBSysBase = msg->USBReq->io_Device;
	}

	if ( ! IUSBSys )
	{
		IUSBSys = (PTR) GetInterface( (PTR) USBSysBase, "main", 1, NULL );

		if ( ! IUSBSys )
		{
			MYERROR( "USBFD : Error obtaining USBSys Interface" );
			goto bailout;
		}
	}

	// --
	// Lets startup

	memset( & us, 0, sizeof( us ));

	us.Running = TRUE;
	us.StartMsg = msg;

	if ( USB_Init( & us ))
	{
		// --
		// Only used too break the Wait() waiting
		// you still need to set Running to FALSE
		wait = SIGBREAKF_CTRL_C;

		// Stack message for from Interface
		wait |= us.Interface_Bit;

		while( us.Running )
		{
			mask = Wait( wait );

			if ( mask & us.Interface_Bit )
			{
				USB_Handle_Interface( & us );
			}
		}

		retval = USBERR_NOERROR;
	}

	USB_Free( & us );

bailout:

	MYDEBUG( "USBFD : USB_Driver - Leave - Retval %ld", retval );

	return( retval );
}

// --
