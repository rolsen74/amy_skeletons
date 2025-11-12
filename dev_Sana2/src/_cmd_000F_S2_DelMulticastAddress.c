
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _cmd_000F_S2_DelMulticastAddress( struct SANA2Unit *unit, struct IOSana2Req *ioreq )
{
struct MulticastAddress *mc;

	MYDEBUG( "SANA2 : _cmd_000F_S2_DelMulticastAddress" );

	// I only check Online stat here, we will not be online
	// if Configure have been completed first.
	if ( ! unit->unit_Online_Stat )
	{
		MYINFO( "We are not online" );
		ioreq->ios2_Req.io_Error	= S2ERR_OUTOFSERVICE;
		ioreq->ios2_WireError		= S2WERR_UNIT_OFFLINE;
	}
	else if ( ! IS_MULTICAST( & ioreq->ios2_SrcAddr[0] ))
	{
		MYINFO( "Invalid Address, Must be a Multicast MAC Address" );
		ioreq->ios2_Req.io_Error	= S2ERR_BAD_ADDRESS;
		ioreq->ios2_WireError		= 0;
	}
	else if ( IS_BROADCAST( & ioreq->ios2_SrcAddr[0] ))
	{
		MYINFO( "Invalid Address (Broadcast), Must be a Multicast MAC Address" );
		ioreq->ios2_Req.io_Error	= S2ERR_BAD_ADDRESS;
		ioreq->ios2_WireError		= 0;
	}
	else
	{
		MYINFO( "SANA2 : Del Multicast MAC Address - %02lx:%02lx:%02lx:%02lx:%02lx:%02lx",
			(U32) ioreq->ios2_SrcAddr[0],
			(U32) ioreq->ios2_SrcAddr[1],
			(U32) ioreq->ios2_SrcAddr[2],
			(U32) ioreq->ios2_SrcAddr[3],
			(U32) ioreq->ios2_SrcAddr[4],
			(U32) ioreq->ios2_SrcAddr[5]
		);

		// Search if we know it
		mc = (PTR) GetHead( unit->unit_Multicast_List );

		while( mc )
		{
			if ( ! memcmp( mc->mca_Address, & ioreq->ios2_SrcAddr[0], 6 ))
			{
				break;
			}
			else
			{
				mc = (PTR) GetSucc( (PTR) mc );
			}
		}

		if ( ! mc )
		{
			// Not found
			MYINFO( "Couldn't find multicast address" );
			ioreq->ios2_Req.io_Error	= S2ERR_BAD_ADDRESS;
			ioreq->ios2_WireError		= S2WERR_BAD_MULTICAST;
			goto bailout;
		}

		// Check for other users
		mc->mca_UseCount--;

		if ( mc->mca_UseCount <= 0 )
		{
			MYINFO( "Removing multicast" );
			Remove( (PTR) mc );
			FreeVec( mc );

			// You may need to init Hardware, for changed Multicast here
			// HW_SetMulticastFilter()
		}
	}

bailout:

	ReplyMsg( (PTR) ioreq );
}

// --
