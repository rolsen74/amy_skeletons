
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _blanker_Blank( struct BlankerModuleIFace *Self )
{
struct BlankerData *data;

	MYDEBUG( "Blanker : _blanker_Blank" );

	data = (PTR) ( (U32) Self - Self->Data.NegativeSize );

	if ( Blanker_Init( data ))
	{
		if ( data->bd_BlankerRender->isPreview )
		{
			MYDEBUG( "Blanker : _blanker_Blank : Preview" );
	
			Blanker_Render_Preview( data );
		}
		else
		{
			MYDEBUG( "Blanker : _blanker_Blank : Screen" );

			Blanker_Render_Screen( data );
		}
	}
	else
	{
		MYDEBUG( "Blanker : _blanker_Blank : Blanker_Init() failed" );
	}

	Blanker_Free( data );
}

// --
