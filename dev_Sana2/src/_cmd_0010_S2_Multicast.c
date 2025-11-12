
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _cmd_0010_S2_Multicast( struct SANA2Unit *unit, struct IOSana2Req *ioreq )
{
	MYDEBUG( "SANA2 : _cmd_0010_S2_Multicast" );

	if (( ! IS_MULTICAST( & ioreq->ios2_DstAddr[0] ))
	||	(	IS_BROADCAST( & ioreq->ios2_DstAddr[0] )))
	{
		MYERROR( "This is not a multicast address" );
		MYERROR( "Multicast Dst Address - %02lx:%02lx:%02lx:%02lx:%02lx:%02lx",
			(U32) ioreq->ios2_SrcAddr[0],
			(U32) ioreq->ios2_SrcAddr[1],
			(U32) ioreq->ios2_SrcAddr[2],
			(U32) ioreq->ios2_SrcAddr[3],
			(U32) ioreq->ios2_SrcAddr[4],
			(U32) ioreq->ios2_SrcAddr[5]
		);

		ioreq->ios2_Req.io_Error	= S2ERR_BAD_ADDRESS;
		ioreq->ios2_WireError		= S2WERR_BAD_MULTICAST;

		ReplyMsg( (PTR) ioreq );
	}
	else
	{
		// Its just a Write, so forward it
		_cmd_0003_Write( unit, ioreq );
	}
}

// --
