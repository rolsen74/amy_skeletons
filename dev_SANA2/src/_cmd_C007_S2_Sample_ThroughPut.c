
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _cmd_C007_S2_Sample_ThroughPut( struct SANA2Unit *unit, struct IOSana2Req *ioreq )
{
struct Sana2ThroughputStats *stats;
S32 reply;

	MYDEBUG( "SANA2 : _cmd_C007_S2_Sample_ThroughPut" );

	reply = TRUE;

	stats = ioreq->ios2_StatData;

	/**/ if ( ! stats )
	{
		MYERROR( "NULL Pointer" );
		ioreq->ios2_Req.io_Error	= S2ERR_BAD_ARGUMENT;
		ioreq->ios2_WireError		= S2WERR_NULL_POINTER;
	}
	else if ( stats->s2ts_Length < 8 )
	{
		MYERROR( "SANA2 : Bad Length : %ld", stats->s2ts_Length );
		ioreq->ios2_Req.io_Error	= IOERR_BADLENGTH;
		ioreq->ios2_WireError		= 0;
	}
	else
	{
		stats->s2ts_Actual = MIN( stats->s2ts_Length, sizeof( struct Sana2ThroughputStats ));

		if ( stats->s2ts_Actual > 8 )
		{
			// Clear stat, execpt first two entries that is Length and Actual
			memset( & stats->s2ts_NotifyTask, 0, stats->s2ts_Actual - 8 );
		}

		// No need for Semaphore protection here
		// as all List handling in done in same Unit process
		AddTail( unit->unit_Sample_List, (PTR) ioreq );
		unit->unit_Sample_List_Count++;

		reply = FALSE;
	}

	if ( reply )
	{
		ReplyMsg( (PTR) ioreq );
	}
}

// --
