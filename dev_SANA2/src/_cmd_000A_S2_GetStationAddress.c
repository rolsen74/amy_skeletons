
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _cmd_000A_S2_GetStationAddress( struct SANA2Unit *unit, struct IOSana2Req *ioreq )
{
	MYDEBUG( "SANA2 : _cmd_000A_S2_GetStationAddress" );

	if ( ! unit->unit_MAC_Adr_Okay )
	{
		MYINFO( "MAC Address not known" );
		ioreq->ios2_Req.io_Error	= S2ERR_BAD_STATE;
		ioreq->ios2_WireError		= S2WERR_NOT_CONFIGURED;
	}
	else
	{
		memcpy( & ioreq->ios2_SrcAddr[0], & unit->unit_MAC_Adr_Soft[0], 6 );
		memcpy( & ioreq->ios2_DstAddr[0], & unit->unit_MAC_Adr_Hard[0], 6 );
	}

	ReplyMsg( (PTR) ioreq );
}

// --
