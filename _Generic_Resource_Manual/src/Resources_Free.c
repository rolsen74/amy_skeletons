
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void Resources_Free( struct Real_ResourceBase *resBase UNUSED )
{
	MYDEBUG( "Resource : Resources_Free" );

	// --

	// Free resources here

	// --
	// Free Resources last
	myCloseResources();

//bailout:

	return;
}

// --
