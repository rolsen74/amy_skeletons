
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

BOOL _docky_Process( struct DockyIFace *Self UNUSED, U32 turnCount UNUSED, U32 *msgType UNUSED, U32 *msgData UNUSED, BOOL *anotherTurn UNUSED )
{
//struct DockyData *data;
BOOL redraw;

	// This function is offen
//	MYDEBUG( "Docky : _docky_Process" );

	redraw = FALSE;

//	data = (PTR) ( (U32) Self - Self->Data.NegativeSize );


	return( redraw );
}
