
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _cmd_0009_S2_DeviceQuery( struct SANA2Unit *unit, struct IOSana2Req *ioreq )
{
struct Sana2DeviceQuery *stats;
struct Sana2DeviceQuery data;

	MYDEBUG( "SANA2 : _cmd_0009_S2_DeviceQuery" );

	stats = ioreq->ios2_StatData;

	/**/ if ( ! stats )
	{
		MYERROR( "NULL Pointer" );
		ioreq->ios2_Req.io_Error	= S2ERR_BAD_ARGUMENT;
		ioreq->ios2_WireError		= S2WERR_NULL_POINTER;
	}
	// Struct starts with 2x U32 and then the Stats Data
	else if ( stats->SizeAvailable < 8 )
	{
		MYERROR( "SANA2 : Bad Length : %ld", stats->SizeAvailable );
		ioreq->ios2_Req.io_Error	= IOERR_BADLENGTH;
		ioreq->ios2_WireError		= 0;
	}
	else
	{
		// Init Structure
		// Note you proberly need to adjust info here
		data.SizeAvailable		= stats->SizeAvailable;
		data.SizeSupplied		= MIN( stats->SizeAvailable, sizeof( data ));
		data.DevQueryFormat		= 0;
		data.DeviceLevel		= 0;
		data.AddrFieldSize		= 48;
		data.MTU				= ETHERNET_MTU;
//		data.BPS				= 0;
		data.HardwareType		= S2WireType_Ethernet;
		data.RawMTU				= ETHERNET_RAW_MTU;

		// In this example, we only support 10/100 MBit
		if ( unit->unit_100MBits )
		{
			// 100MBits
			data.BPS = 100000000;
		}
		else
		{
			// 10MBits
			data.BPS = 10000000;
		}

		// Only copy the amount asked for
		memcpy( stats, & data, data.SizeSupplied );
	}

	ReplyMsg( (PTR) ioreq );
}

// --
