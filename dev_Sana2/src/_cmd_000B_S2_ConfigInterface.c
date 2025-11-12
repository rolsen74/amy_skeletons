
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _cmd_000B_S2_ConfigInterface( struct SANA2Unit *unit, struct IOSana2Req *ioreq )
{
	MYDEBUG( "SANA2 : _cmd_000B_S2_ConfigInterface" );

	/**/ if ( ! unit->unit_MAC_Adr_Okay )
	{
		MYINFO( "MAC Address not known" );
		ioreq->ios2_Req.io_Error	= S2ERR_BAD_STATE;
		ioreq->ios2_WireError		= S2WERR_NOT_CONFIGURED;
	}
	else if ( IS_MULTICAST( & ioreq->ios2_SrcAddr[0] ))
	{
		MYINFO( "Invalid Address (Multicast), Must be a local MAC Address" );
		ioreq->ios2_Req.io_Error	= S2ERR_BAD_ADDRESS;
		ioreq->ios2_WireError		= 0;
	}
	else if ( IS_BROADCAST( & ioreq->ios2_SrcAddr[0] ))
	{
		MYINFO( "Invalid Address (Broadcast), Must be a local MAC Address" );
		ioreq->ios2_Req.io_Error	= S2ERR_BAD_ADDRESS;
		ioreq->ios2_WireError		= 0;
	}
	else if ( ! unit->unit_SW_Can_Configure )
	{
		MYINFO( "Configure error (SW_Can_Configure)" );
		ioreq->ios2_Req.io_Error	= IOERR_SELFTEST;
		ioreq->ios2_WireError		= 0;
	}
	else
	{
		// Set Current MAC Address
		memcpy( & unit->unit_MAC_Adr_Soft[0], & ioreq->ios2_SrcAddr[0], 6 );

		MYINFO( "SANA2 : Setting MAC Address - %02lx:%02lx:%02lx:%02lx:%02lx:%02lx",
			(U32) ioreq->ios2_SrcAddr[0],
			(U32) ioreq->ios2_SrcAddr[1],
			(U32) ioreq->ios2_SrcAddr[2],
			(U32) ioreq->ios2_SrcAddr[3],
			(U32) ioreq->ios2_SrcAddr[4],
			(U32) ioreq->ios2_SrcAddr[5]
		);

		// You may need to init Hardware, for new MAC address here
		// HW_SetMacAddress()

		// Remember Start time for Stats
		GetSysTime( & unit->unit_LastStart );

		// Make sure we are only Configured once
		unit->unit_SW_Can_Configure = FALSE;

		// We start out being Online
		// you can't reley on S2_Online getting called first
		unit->unit_Online_Stat = TRUE;
	}

	ReplyMsg( (PTR) ioreq );
}

// --
