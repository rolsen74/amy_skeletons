
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _cmd_0018_S2_ReadOrphan( struct SANA2Unit *unit, struct IOSana2Req *ioreq )
{
	MYDEBUG( "SANA2 : _cmd_0018_S2_ReadOrphan" );

	// Its just a Read, so forward it
	_cmd_0002_Read( unit, ioreq );
}

// --
