
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void Packet_Send_Done( struct SANA2Unit *unit )
{
struct IOSana2Req *ioreq;

	// We got a signal a transfer is done
	// it may be an error or just got send okay

	ioreq = unit->unit_Tx_Active_IOReq;

	if ( ! ioreq )
	{
		goto bailout;
	}

	unit->unit_Tx_Active_IOReq = NULL;

	// Here you should init the IOReq's io_Error
	// indicating if it failed or not
	// And then reply it

	if ( TRUE )
	{
		// ok

		// Lets adjust Stats
		unit->unit_PacketsSent++;

		ioreq->ios2_Req.io_Error = S2ERR_NO_ERROR;
		ReplyMsg( (PTR) ioreq );	
	}
	else
	{
		// error

		ioreq->ios2_Req.io_Error = S2ERR_TX_FAILURE;
		ReplyMsg( (PTR) ioreq );	
	}

bailout:

	return;
}

// --
