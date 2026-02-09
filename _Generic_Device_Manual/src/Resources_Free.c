
/*
** SPDX-License-Identifier: Unlicense
** Written 2026 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

extern struct Interface *INewlib;
extern struct Library *NewlibBase;

void Resources_Free( struct DEVBase *devBase UNUSED )
{
	MYDEBUG( "DEV : Resources_Free" );

	// --
	// Free Resources last
	myCloseResources();

	// --
}

// --
