
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _cmd_0008_Flush( struct SANA2Unit *unit, struct IOSana2Req *ioreq )
{
	MYDEBUG( "SANA2 : _cmd_0008_Flush" );

	// Abort all queued Transfers
	Abort_All( unit, S2WERR_GENERIC_ERROR );

	ReplyMsg( (PTR) ioreq );
}

// --
