
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void Process_Free( struct PrinterUnit *unit )
{
struct AbortIOMessage *msg;
struct IORequest *ioreq;

	MYERROR( "Printer : Process_Free", 0 );

	// --

	if ( unit->unit_Write_List )
	{
		MYINFO( "Printer : Freeing Write list", 0 );

		while( TRUE )
		{
			ioreq = (PTR) RemHead( unit->unit_Write_List );

			if ( ! ioreq )
			{
				break;
			}

			MYINFO( "Printer : Aborting IOReq %p", ioreq );
			ioreq->io_Error = IOERR_ABORTED;
			ReplyMsg( (PTR) ioreq );
		}

		FreeSysObject( ASOT_LIST, unit->unit_Read_List );
		unit->unit_Read_List = NULL;
	}

	// --

	if ( unit->unit_Read_List )
	{
		MYINFO( "Printer : Freeing Read list", 0 );

		while( TRUE )
		{
			ioreq = (PTR) RemHead( unit->unit_Read_List );

			if ( ! ioreq )
			{
				break;
			}

			MYINFO( "Printer : Aborting IOReq %p", ioreq );
			ioreq->io_Error = IOERR_ABORTED;
			ReplyMsg( (PTR) ioreq );
		}

		FreeSysObject( ASOT_LIST, unit->unit_Read_List );
		unit->unit_Read_List = NULL;
	}

	// --

	if ( unit->unit_Abort_MsgPort )
	{
		MYINFO( "Printer : Clearing Abort MsgPort", 0 );

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
		MYINFO( "Printer : Clearing Begin MsgPort", 0 );

		while( TRUE )
		{
			ioreq = (PTR) GetMsg( unit->unit_Begin_MsgPort );

			if ( ! ioreq )
			{
				break;
			}

			MYINFO( "Printer : Aborting IOReq %p", ioreq );
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
