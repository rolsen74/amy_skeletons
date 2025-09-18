
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _docky_Release( struct DockyIFace *Self )
{
	MYDEBUG( "Docky : _docky_Release" );

	Self->Data.RefCount--;

	if ( ! Self->Data.RefCount )
	{
		Self->Expunge();
	}

	return( Self->Data.RefCount );
}

// --
