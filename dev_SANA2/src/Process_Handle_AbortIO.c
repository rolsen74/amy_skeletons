
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void Process_Handle_AbortIO( struct SANA2Unit *unit )
{
struct AbortIOMessage *msg;
struct IOSana2Req *ioreq;

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

		switch( ioreq->ios2_Req.io_Command )
		{
			case CMD_READ:
			{
				MYINFO( "AbortIO: io_Command = CMD_READ" );

				if ( Abort_IOReq( unit, unit->unit_Rx_List, ioreq, 0 ))
				{
					unit->unit_Rx_List_Count--;
				}
				break;
			}

			case S2_READORPHAN:
			{
				MYINFO( "AbortIO: io_Command = S2_READORPHAN" );
				
				if ( Abort_IOReq( unit, unit->unit_Rx_List, ioreq, 0 ))
				{
					unit->unit_Rx_List_Count--;
				}
				break;
			}

			case CMD_WRITE:
			{
				MYINFO( "AbortIO: io_Command = CMD_WRITE" );
				
				if ( Abort_IOReq( unit, unit->unit_Tx_List, ioreq, 0 ))
				{
					unit->unit_Tx_List_Count--;
				}
				break;
			}

			case S2_BROADCAST:
			{
				MYINFO( "AbortIO: io_Command = S2_BROADCAST" );
				
				if ( Abort_IOReq( unit, unit->unit_Tx_List, ioreq, 0 ))
				{
					unit->unit_Tx_List_Count--;
				}
				break;
			}

			case S2_MULTICAST:
			{
				MYINFO( "AbortIO: io_Command = S2_MULTICAST" );
				
				if ( Abort_IOReq( unit, unit->unit_Tx_List, ioreq, 0 ))
				{
					unit->unit_Tx_List_Count--;
				}
				break;
			}

			case S2_ONEVENT:
			{
				MYINFO( "AbortIO: io_Command = S2_ONEVENT" );
				
				if ( Abort_IOReq( unit, unit->unit_Event_List, ioreq, 0 ))
				{
					unit->unit_Event_List_Count--;
				}
				break;
			}

			case S2_SAMPLE_THROUGHPUT:
			{
				MYINFO( "AbortIO: io_Command = S2_SAMPLE_THROUGHPUT" );
				
				if ( Abort_IOReq( unit, unit->unit_Sample_List, ioreq, 0 ))
				{
					unit->unit_Sample_List_Count--;
				}
				break;
			}

			default:
			{
				MYINFO( "Unknown Command (%ld) -- This should really not chould happen", ioreq->ios2_Req.io_Command );
				// Don't reply the IOReq here, just ignore it
				break;
			}
		}
	}
}

// --
