
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _manager_AbortIO( struct DeviceManagerInterface *Self UNUSED, struct IORequest *ioreq )
{
struct AbortIOMessage *msg;
struct SANA2Unit *unit;

	MYDEBUG( "SANA2 : _manager_AbortIO : IOReq %p", ioreq );

	unit = (PTR) ioreq->io_Unit;

	switch( ioreq->io_Command )
	{
		// Only those can queue IOReq's
		case /* 0002 */ CMD_READ:
		case /* 0003 */ CMD_WRITE:
		case /* 0010 */ S2_MULTICAST:
		case /* 0011 */ S2_BROADCAST:
		case /* 0017 */ S2_ONEVENT:
		case /* 0018 */ S2_READORPHAN:
		case /* C007 */ S2_SAMPLE_THROUGHPUT:
		{
			msg = AllocVecTags( sizeof( struct AbortIOMessage ), AVT_Clear, 0, TAG_END );

			if ( msg )
			{
				msg->am_IOReq = ioreq;
				PutMsg( unit->unit_Abort_MsgPort, & msg->am_Message );
			}
			else
			{
				// Just ignore it if we are out of mem
				// Do not reply the IOReq
			}
			break;
		}

		default:
		{
			// Ignoring.. do nothing
			// Do not reply the IOReq
			break;
		}
	}
}

// --
