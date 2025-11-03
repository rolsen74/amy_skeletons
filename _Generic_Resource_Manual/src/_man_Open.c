
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

PTR _manager_Open( struct LibraryManagerInterface *Self, U32 version UNUSED )
{
struct Real_ResourceBase *resBase;

	MYDEBUG( "Resource : _manager_Open" );

	resBase = (PTR) Self->Data.LibBase;

	return( (PTR) resBase );
}

// --
