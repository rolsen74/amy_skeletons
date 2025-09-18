
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _docky_Expunge( struct DockyIFace *Self )
{
//struct DockyBase *libBase;
struct DockyData *data;

	MYDEBUG( "Docky : _docky_Expunge" );

//	libBase = (PTR) Self->Data.LibBase;
	data = (PTR) ( (U32) Self - Self->Data.NegativeSize );

	// Free data obtained in _docky_Clone()

	FreeVec( data );
	
	return( TRUE );
}

// --
