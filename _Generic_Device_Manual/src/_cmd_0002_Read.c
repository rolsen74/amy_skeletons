
/*
** SPDX-License-Identifier: Unlicense
** Written 2026 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _cmd_0002_Read( struct DEVUnit *unit UNUSED, struct IORequest *ioreq )
{
	MYDEBUG( "DEV : _cmd_0002_Read" );

	ioreq->io_Error = 0;
	ReplyMsg( (PTR) ioreq );
}

// --
