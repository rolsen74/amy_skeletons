
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _cmd_C004_S2_GetExtendedGlobalStats( struct SANA2Unit *unit, struct IOSana2Req *ioreq )
{
struct Sana2ExtDeviceStats *stats;
struct Sana2ExtDeviceStats data;

	MYDEBUG( "SANA2 : _cmd_C004_S2_GetExtendedGlobalStats" );

	stats = ioreq->ios2_StatData;

	/**/ if ( ! stats )
	{
		MYERROR( "NULL Pointer" );
		ioreq->ios2_Req.io_Error	= S2ERR_BAD_ARGUMENT;
		ioreq->ios2_WireError		= S2WERR_NULL_POINTER;
	}
	// Struct starts with 2x U32 and then the Stats Data
	else if ( stats->s2xds_Length < 8 )	
	{
		MYERROR( "SANA2 : Bad Length : %ld", stats->s2xds_Length );
		ioreq->ios2_Req.io_Error	= IOERR_BADLENGTH;
		ioreq->ios2_WireError		= 0;
	}
	else
	{
		memset( & data, 0, sizeof( data ));

		// Init Structure, I added the U64 too show this is the 64bit stat version
		data.s2xds_Length				= stats->s2xds_Length;
		data.s2xds_Actual				= MIN( stats->s2xds_Length, sizeof( data ));
		data.s2xds_PacketsReceived		= (U64) unit->unit_PacketsReceived;
		data.s2xds_PacketsSent			= (U64) unit->unit_PacketsSent;
		data.s2xds_BadData				= (U64) unit->unit_BadData;
		data.s2xds_Overruns				= (U64) unit->unit_Overruns;
		data.s2xds_UnknownTypesReceived	= (U64) unit->unit_UnknownTypesReceived;
		data.s2xds_Reconfigurations		= (U64) unit->unit_Reconfigurations;
		data.s2xds_LastStart			= unit->unit_LastStart;
		// data.s2xds_LastConnected;
		// data.s2xds_LastDisconnected;
		// data.s2xds_TimeConnected;

		// Only copy the amount asked for
		memcpy( stats, & data, data.s2xds_Actual );
	}

	ReplyMsg( (PTR) ioreq );
}

// --
