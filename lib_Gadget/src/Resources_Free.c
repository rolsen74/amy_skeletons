
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
	MYDEBUG( "Gadget : Resources_Free" );

	// --

	if ( ! FreeClass( libBase->lib_Base.cl_Class ))
	{
		MYERROR( "Gadget : Unable to free Class" );
		goto bailout;
	}

	libBase->lib_Base.cl_Class = NULL;

	// --
	// Free Resources last
	myCloseResources();

bailout:

	return;
}

// --
