
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

extern struct Interface *INewlib;
extern struct Library *NewlibBase;

void Resources_Free( struct SANA2Base *devBase UNUSED )
{
	MYDEBUG( "SANA2 : Resources_Free" );

	// --
	// Free Resources last
	myCloseResources();

	// --
}

// --
