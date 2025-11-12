
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _cmd_0017_S2_OnEvent( struct SANA2Unit *unit, struct IOSana2Req *ioreq )
{
S32 reply;
U32 mask;

	MYDEBUG( "SANA2 : _cmd_0017_S2_OnEvent" );

	reply = TRUE;

	mask = ioreq->ios2_WireError;

//	#define SUPPORTED	( S2EVENT_ONLINE | S2EVENT_OFFLINE )

	if ( ! mask )
	{
		MYINFO( "No events given" );
		ioreq->ios2_Req.io_Error	= S2ERR_BAD_ARGUMENT;
		ioreq->ios2_WireError		= S2WERR_BAD_EVENT;
	}
//	I'm unsure if its best to Queue unsupport events, or just reject them
//	else if ( mask & ~SUPPORTED )
//	{
//		MYINFO( "There are unspported event(s)" );
//		ioreq->ios2_Req.io_Error	= S2ERR_NOT_SUPPORTED;
//		ioreq->ios2_WireError		= S2WERR_BAD_EVENT;
//	}
	else if (( mask & S2EVENT_ONLINE ) && ( unit->unit_Online_Stat ))
	{
		// Online / Offline is a little special and need too return immediately (if true)
		ioreq->ios2_Req.io_Error = 0;
		ioreq->ios2_WireError = S2EVENT_ONLINE;
	}
	else if (( mask & S2EVENT_OFFLINE ) && ( ! unit->unit_Online_Stat ))
	{
		// Online / Offline is a little special and need too return immediately (if true)
		ioreq->ios2_Req.io_Error = 0;
		ioreq->ios2_WireError = S2EVENT_OFFLINE;
	}
	else
	{
		// Queue this event
		AddTail( unit->unit_Event_List, (PTR) ioreq );
		unit->unit_Event_List_Count++;

		reply = FALSE;
	}

	if ( reply )
	{
		ReplyMsg( (PTR) ioreq );
	}
}

// --
