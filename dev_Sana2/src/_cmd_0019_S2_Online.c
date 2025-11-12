
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _cmd_0019_S2_Online( struct SANA2Unit *unit, struct IOSana2Req *ioreq )
{
	MYDEBUG( "SANA2 : _cmd_0019_S2_Online" );

	/**/ if ( ! unit->unit_MAC_Adr_Okay )
	{
		MYINFO( "Config error (MAC_Adr_Okay)" );
		ioreq->ios2_Req.io_Error	= S2ERR_BAD_STATE;
		ioreq->ios2_WireError		= S2WERR_NOT_CONFIGURED;
	}
	else if ( unit->unit_SW_Can_Configure )
	{
		// if we can Configure, then it have not been done
		MYINFO( "Configure error (SW_Can_Configure)" );
		ioreq->ios2_Req.io_Error	= IOERR_SELFTEST;
		ioreq->ios2_WireError		= 0;
	}
	else if ( unit->unit_Online_Stat )
	{
		MYINFO( "We are already online" );
		ioreq->ios2_Req.io_Error	= S2ERR_BAD_STATE;
		ioreq->ios2_WireError		= S2WERR_UNIT_ONLINE;
	}
	else
	{
		// Remember Start time for Stats
		GetSysTime( & unit->unit_LastStart );

		// User may have install an Online Event handler
		Event_Check( unit, S2EVENT_ONLINE );

		// You may need to Enable hardware here
		// HW_StartTransmission()

		// Mark us as Online
		unit->unit_Online_Stat = TRUE;
	}

	ReplyMsg( (PTR) ioreq );
}

// --
