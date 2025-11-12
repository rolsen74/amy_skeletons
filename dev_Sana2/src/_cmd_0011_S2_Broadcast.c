
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _cmd_0011_S2_Broadcast( struct SANA2Unit *unit, struct IOSana2Req *ioreq )
{
	MYDEBUG( "SANA2 : _cmd_0011_S2_Broadcast" );

	// Make sure we have a Broadcast addr
	ioreq->ios2_DstAddr[0] = 0xff;
	ioreq->ios2_DstAddr[1] = 0xff;
	ioreq->ios2_DstAddr[2] = 0xff;
	ioreq->ios2_DstAddr[3] = 0xff;
	ioreq->ios2_DstAddr[5] = 0xff;
	ioreq->ios2_DstAddr[6] = 0xff;

	// Its just a Write
	_cmd_0003_Write( unit, ioreq );
}

// --
