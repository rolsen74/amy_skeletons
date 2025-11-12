
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _cmd_0016_S2_GetGlobalStats( struct SANA2Unit *unit, struct IOSana2Req *ioreq )
{
struct Sana2DeviceStats *stats;

	MYDEBUG( "SANA2 : _cmd_0016_S2_GetGlobalStats" );

	stats = ioreq->ios2_StatData;

	if ( ! stats )
	{
		MYERROR( "NULL Pointer" );
		ioreq->ios2_Req.io_Error	= S2ERR_BAD_ARGUMENT;
		ioreq->ios2_WireError		= S2WERR_NULL_POINTER;
	}
	else
	{
		stats->PacketsReceived		= (U32) unit->unit_PacketsReceived;
		stats->PacketsSent			= (U32) unit->unit_PacketsSent;
		stats->BadData				= (U32) unit->unit_BadData;
		stats->Overruns				= (U32) unit->unit_Overruns;
		stats->UnknownTypesReceived	= (U32) unit->unit_UnknownTypesReceived;
		stats->Reconfigurations		= (U32) unit->unit_Reconfigurations;
		stats->LastStart			= unit->unit_LastStart;
	}

	ReplyMsg( (PTR) ioreq );
}

// --
