
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

PTR _manager_Close( struct LibraryManagerInterface *Self UNUSED )
{
PTR seglist;

	MYDEBUG( "Resource : _manager_Close" );

	seglist = NULL;

	return( seglist );
}

// --
