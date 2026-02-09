
/*
** SPDX-License-Identifier: Unlicense
** Written 2026 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void Process_Free( struct DEVUnit *unit )
{
struct AbortIOMessage *msg;
struct IORequest *ioreq;

	MYERROR( "Device : Process_Free" );

	// --

	if ( unit->unit_Abort_MsgPort )
	{
		MYINFO( "Device : Clearing Abort MsgPort" );

		while( TRUE )
		{
			msg = (PTR) GetMsg( unit->unit_Abort_MsgPort );

			if ( ! msg )
			{
				break;
			}

			FreeVec( msg );
		}

		FreeSysObject( ASOT_PORT, unit->unit_Abort_MsgPort );
		unit->unit_Abort_MsgPortBit = 0;
		unit->unit_Abort_MsgPort = NULL;
	}

	// --

	if ( unit->unit_Begin_MsgPort )
	{
		MYINFO( "Device : Clearing Begin MsgPort" );

		while( TRUE )
		{
			ioreq = (PTR) GetMsg( unit->unit_Begin_MsgPort );

			if ( ! ioreq )
			{
				break;
			}

			MYINFO( "Device : Aborting IOReq %p", ioreq );
			ioreq->io_Error = IOERR_ABORTED;
			ReplyMsg( (PTR) ioreq );
		}

		FreeSysObject( ASOT_PORT, unit->unit_Begin_MsgPort );
		unit->unit_Begin_MsgPortBit = 0;
		unit->unit_Begin_MsgPort = NULL;
	}

	// --
}

// --
