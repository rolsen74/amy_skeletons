
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

S32 Abort_All( struct SANA2Unit *unit, U32 ErrType )
{
struct IOSana2Req *ioreq;
S32 aborted;

	MYDEBUG( "SANA2 : Abort_All" );

	aborted = 0;

	while( TRUE )
	{
		ioreq = (PTR) RemHead( unit->unit_Rx_List );

		if ( ! ioreq )
		{
			break;
		}

		ioreq->ios2_Req.io_Error	= IOERR_ABORTED;
		ioreq->ios2_WireError		= ErrType;
		ReplyMsg( (PTR) ioreq );
		aborted++;
	}

	while( TRUE )
	{
		ioreq = (PTR) RemHead( unit->unit_Tx_List );

		if ( ! ioreq )
		{
			break;
		}

		ioreq->ios2_Req.io_Error	= IOERR_ABORTED;
		ioreq->ios2_WireError		= ErrType;
		ReplyMsg( (PTR) ioreq );
		aborted++;
	}

	unit->unit_Rx_List_Count = 0;
	unit->unit_Tx_List_Count = 0;

	return( aborted );
}

// --
