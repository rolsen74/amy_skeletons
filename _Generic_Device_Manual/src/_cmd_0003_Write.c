
/*
** SPDX-License-Identifier: Unlicense
** Written 2026 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _cmd_0003_Write( struct DEVUnit *unit UNUSED, struct IORequest *ioreq )
{
	MYDEBUG( "DEV : _cmd_0003_Write" );

	ioreq->io_Error = 0;
	ReplyMsg( (PTR) ioreq );
}

// --
