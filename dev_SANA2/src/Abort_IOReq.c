
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

S32 Abort_IOReq( struct SANA2Unit *unit UNUSED, struct List *list, struct IOSana2Req *ioreq, U32 ErrType )
{
struct IOSana2Req *cur;
S32 aborted;

	MYDEBUG( "SANA2 : Abort_IOReq" );

	aborted = 0;

	cur = (PTR) GetHead( list );

	while( cur )
	{
		if ( cur == ioreq )
		{
			ioreq->ios2_Req.io_Error	= IOERR_ABORTED;
			ioreq->ios2_WireError		= ErrType;
			Remove( (PTR) ioreq );
			ReplyMsg( (PTR) ioreq );
			aborted++;
			break;
		}
		else
		{
			cur = (PTR) GetSucc( (PTR) cur );
		}
	}

	return( aborted );
}

// --
