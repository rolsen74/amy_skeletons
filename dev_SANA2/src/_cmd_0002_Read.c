
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _cmd_0002_Read( struct SANA2Unit *unit, struct IOSana2Req *ioreq )
{
S32 reply;

	MYDEBUG( "SANA2 : _cmd_0002_Read" );

	reply = TRUE;

	/**/ if ( ! unit->unit_MAC_Adr_Okay )
	{
		MYINFO( "Config error (MAC_Adr_Okay)" );
		ioreq->ios2_Req.io_Error	= S2ERR_BAD_STATE;
		ioreq->ios2_WireError		= S2WERR_NOT_CONFIGURED;
	}
	else if ( ! unit->unit_Online_Stat )
	{
		MYINFO( "We are not online" );
		ioreq->ios2_Req.io_Error	= S2ERR_OUTOFSERVICE;
		ioreq->ios2_WireError		= S2WERR_UNIT_OFFLINE;
	}
	else
	{
		// No need for Semaphore protection here
		// as all List handling in done in same Unit process
		AddTail( unit->unit_Rx_List, (PTR) ioreq );
		unit->unit_Rx_List_Count++;

		reply = FALSE;
	}

	if ( reply )
	{
		ReplyMsg( (PTR) ioreq );
	}
}

// --
