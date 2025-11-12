
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _cmd_000E_S2_AddMulticastAddress( struct SANA2Unit *unit, struct IOSana2Req *ioreq )
{
struct MulticastAddress *mc;

	MYDEBUG( "SANA2 : _cmd_000E_S2_AddMulticastAddress" );

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
		MYINFO( "SANA2 : Add Multicast MAC Address - %02lx:%02lx:%02lx:%02lx:%02lx:%02lx",
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
			// Not found, create a new node
			mc = AllocVecTags( sizeof( struct MulticastAddress ),
				AVT_ClearWithValue, 0,
				TAG_END 
			);

			if ( ! mc )
			{
				MYERROR( "SANA2 : Error allocating memory" );
				ioreq->ios2_Req.io_Error	= S2ERR_NO_RESOURCES;
				ioreq->ios2_WireError		= 0;
				goto bailout;
			}

			memcpy( & mc->mca_Address, & ioreq->ios2_SrcAddr[0], 6 );

			// Queue Multicast
			AddTail( unit->unit_Multicast_List, (PTR) mc );
			unit->unit_Multicast_List_Count++;

			// You may need to init Hardware, for new Multicast here
			// HW_SetMulticastFilter()
		}

		// Adjust use count, more than one may use this.
		mc->mca_UseCount++;
	}

bailout:

	ReplyMsg( (PTR) ioreq );
}

// --
