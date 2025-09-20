
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _blanker_Expunge( struct BlankerModuleIFace *Self )
{
//struct BlankerBase *libBase;
struct BlankerData *data;

	MYDEBUG( "Blanker : _blanker_Expunge" );

//	libBase = (PTR) Self->Data.LibBase;
	data = (PTR) ( (U32) Self - Self->Data.NegativeSize );

	// Free data obtained in _blanker_Clone()

	if ( data->bd_ScreenModeRequester )
	{
		FreeAslRequest( data->bd_ScreenModeRequester );
		data->bd_ScreenModeRequester = NULL;
	}

	FreeVec( data );
	
	return( TRUE );
}

// --
