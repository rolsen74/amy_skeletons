
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _docky_Obtain( struct DockyIFace *Self )
{
	MYDEBUG( "Docky : _docky_Obtain" );

	Self->Data.RefCount++;

	return( Self->Data.RefCount );
}

// --
