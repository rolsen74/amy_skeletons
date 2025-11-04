
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

S32 _main_RunInterface( struct Test_USBFDIFace *Self UNUSED, struct USBFDStartupMsg *msg UNUSED )
{
// struct LibBase *libBase;
// struct LibData *data;
S32 retval;

//	libBase = (PTR) Self->Data.LibBase;
//	data = (PTR) ( (U32) Self - Self->Data.NegativeSize );

	MYDEBUG( "USBFD : _main_RunInterface" );

	retval = USBERR_UNSUPPORTED;

	struct USBBusIntDsc *dsc = (PTR) msg->Descriptor;

	if ( dsc->id_Class == USBCLASS_HID )
	{
		if ( dsc->id_Subclass == 1 )		// Boot protocol
		{
			if ( dsc->id_Protocol == 1 )	// Keyboard
			{
				retval = USB_Driver( Self, msg );
			}
		}
	}

	MYDEBUG( "USBFD : _main_RunInterface : Retval %ld", retval );

	return( retval );
}

// --
