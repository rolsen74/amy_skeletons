
/*
** SPDX-License-Identifier: Unlicense
** Written 2026 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void Process_Handle_AbortIO( struct DEVUnit *unit )
{
struct AbortIOMessage *msg;
struct IORequest *ioreq;

	while( TRUE )
	{
		msg = (PTR) GetMsg( unit->unit_Abort_MsgPort );

		if ( ! msg )
		{
			break;
		}

		ioreq = msg->am_IOReq;
		FreeVec( msg );

		if ( ! ioreq )
		{
			continue;
		}

		switch( ioreq->io_Command )
		{
			case CMD_READ:
			{
				MYINFO( "AbortIO: io_Command = CMD_READ" );
				break;
			}

			case CMD_WRITE:
			{
				MYINFO( "AbortIO: io_Command = CMD_WRITE" );
				break;
			}

			default:
			{
				MYINFO( "Unknown Command (%ld) -- This should really not chould happen", ioreq->io_Command );
				// Don't reply the IOReq here, just ignore it
				break;
			}
		}
	}
}

// --
