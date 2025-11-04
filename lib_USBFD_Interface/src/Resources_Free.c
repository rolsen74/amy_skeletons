
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void Resources_Free( struct LibBase *libBase )
{
	MYDEBUG( "USBFD : Resources_Free" );

	// --

	if ( libBase->lib_fdkey )
	{
		USBResUnregisterFD( libBase->lib_fdkey );
		libBase->lib_fdkey = NULL;
	}

	// --
	// Free Resources last
	myCloseResources();

// bailout:

	return;
}

// --
