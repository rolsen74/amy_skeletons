
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _cmd_001A_S2_Offline( struct SANA2Unit *unit, struct IOSana2Req *ioreq )
{
	MYDEBUG( "SANA2 : _cmd_001A_S2_Offline" );

	// I only check Online stat here, we will not be online
	// if Configure have been completed first.
	if ( ! unit->unit_Online_Stat )
	{
		MYINFO( "We are not online" );
		ioreq->ios2_Req.io_Error	= S2ERR_BAD_STATE;
		ioreq->ios2_WireError		= S2WERR_NOT_CONFIGURED;
	}
	else
	{
		// Mark us as Offline
		unit->unit_Online_Stat = FALSE;

		// Abort all queued Transfers
		Abort_All( unit, S2WERR_UNIT_OFFLINE );

		// You may need to Disable hardware here
		// HW_StopTransmission()

		// User may have install an Offline Event handler
		Event_Check( unit, S2EVENT_OFFLINE );
	}

	ReplyMsg( (PTR) ioreq );
}

// --
