
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

static void _AbortList( struct List *l )
{
struct IORequest *ioreq;

	while( TRUE )
	{
		ioreq = (PTR) RemHead( l );

		if ( ! ioreq )
		{
			break;
		}

		MYINFO( "SANA2 : Aborting IOReq %p", ioreq );
		ioreq->io_Error = IOERR_ABORTED;
		ReplyMsg( (PTR) ioreq );
	}
}

// --

static void _FreeList( struct List *l )
{
PTR node;

	while( TRUE )
	{
		node = (PTR) RemHead( l );

		if ( ! node )
		{
			break;
		}

		MYINFO( "SANA2 : Freeing Node %p", node );
		FreeVec( node );
	}
}

// --

void Process_Free( struct SANA2Unit *unit )
{
struct AbortIOMessage *msg;
struct IORequest *ioreq;

	MYERROR( "SANA2 : Process_Free" );

	// --

	if ( unit->unit_Tx_List )
	{
		MYINFO( "SANA2 : Freeing Write list" );

		_AbortList( unit->unit_Tx_List );

		FreeSysObject( ASOT_LIST, unit->unit_Rx_List );
		unit->unit_Rx_List = NULL;
	}

	// --

	if ( unit->unit_Rx_List )
	{
		MYINFO( "SANA2 : Freeing Read list" );

		_AbortList( unit->unit_Rx_List );

		FreeSysObject( ASOT_LIST, unit->unit_Rx_List );
		unit->unit_Rx_List = NULL;
	}

	// --

	if ( unit->unit_Event_List )
	{
		MYINFO( "SANA2 : Freeing Event list" );

		_AbortList( unit->unit_Event_List );

		FreeSysObject( ASOT_LIST, unit->unit_Event_List );
		unit->unit_Event_List = NULL;
	}

	// --

	if ( unit->unit_Sample_List )
	{
		MYINFO( "SANA2 : Freeing Sample list" );

		_AbortList( unit->unit_Sample_List );

		FreeSysObject( ASOT_LIST, unit->unit_Sample_List );
		unit->unit_Sample_List = NULL;
	}

	// --

	if ( unit->unit_Multicast_List )
	{
		MYINFO( "SANA2 : Freeing Multicast list" );

		_FreeList( unit->unit_Multicast_List );

		FreeSysObject( ASOT_LIST, unit->unit_Multicast_List );
		unit->unit_Multicast_List = NULL;
	}

	// --

	if ( unit->unit_Abort_MsgPort )
	{
		MYINFO( "SANA2 : Clearing Abort MsgPort" );

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
		MYINFO( "SANA2 : Clearing Begin MsgPort" );

		while( TRUE )
		{
			ioreq = (PTR) GetMsg( unit->unit_Begin_MsgPort );

			if ( ! ioreq )
			{
				break;
			}

			MYINFO( "SANA2 : Aborting IOReq %p", ioreq );
			ioreq->io_Error = IOERR_ABORTED;
			ReplyMsg( (PTR) ioreq );
		}

		FreeSysObject( ASOT_PORT, unit->unit_Begin_MsgPort );
		unit->unit_Begin_MsgPortBit = 0;
		unit->unit_Begin_MsgPort = NULL;
	}

	// --

	if ( unit->unit_Tx_Signal >= 0 )
	{
		FreeSignal( unit->unit_Tx_Signal );
		unit->unit_Tx_Signal = -1;
	}

	if ( unit->unit_Rx_Signal >= 0 )
	{
		FreeSignal( unit->unit_Rx_Signal );
		unit->unit_Rx_Signal = -1;
	}

	// --
}

// --
