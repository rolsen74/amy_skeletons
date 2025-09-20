
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void Blanker_Render_Preview( struct BlankerData *data )
{
	MYDEBUG( "Blanker : Blanker_Render_Preview" );

	Blanker_Render_Main(
		data,
		NULL,
		data->bd_BlankerRender->rp,
		data->bd_BlankerRender->blankWidth,
		data->bd_BlankerRender->blankHeight
	);

}

// --
