
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void Process_Handle_AbortIO( struct PrinterUnit *unit )
{
struct AbortIOMessage *msg;
struct IORequest *ioreq2;
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
			case /* 0002 */ CMD_READ:
			{
				ioreq2 = (PTR) GetHead( unit->unit_Read_List );

				while( ioreq2 )
				{
					if ( ioreq == ioreq2 )
					{
						break;
					}
					else
					{
						ioreq2 = (PTR) GetSucc( (PTR) ioreq2 );
					}
				}

				if ( ioreq2 )
				{
					Remove( (PTR) ioreq );
					MYINFO( "Printer : Aborting IOReq %p", ioreq );
					ioreq->io_Error = IOERR_ABORTED;
					ReplyMsg( (PTR) ioreq );
				}
				break;
			}

			case /* 0003 */ CMD_WRITE:
			{
				ioreq2 = (PTR) GetHead( unit->unit_Write_List );

				while( ioreq2 )
				{
					if ( ioreq == ioreq2 )
					{
						break;
					}
					else
					{
						ioreq2 = (PTR) GetSucc( (PTR) ioreq2 );
					}
				}

				if ( ioreq2 )
				{
					Remove( (PTR) ioreq );
					MYINFO( "Printer : Aborting IOReq %p", ioreq );
					ioreq->io_Error = IOERR_ABORTED;
					ReplyMsg( (PTR) ioreq );
				}
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
