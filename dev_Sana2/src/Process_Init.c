
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

S32 Process_Init( struct SANA2Unit *unit )
{
S32 retval;

	retval = FALSE;

	MYDEBUG( "SANA2 : Process_Init" );

	// --

	unit->unit_Rx_Signal = AllocSignal( -1 );
	unit->unit_Tx_Signal = AllocSignal( -1 );

	if (( unit->unit_Rx_Signal < 0 ) || ( unit->unit_Tx_Signal < 0 ))
	{
		MYERROR( "SANA2 : Process_Init : Error Allocating Signals" );
		goto bailout;
	}

	unit->unit_Rx_SignalBit = 1UL << unit->unit_Rx_Signal;
	unit->unit_Tx_SignalBit = 1UL << unit->unit_Tx_Signal;

	// --

	unit->unit_Rx_List			= AllocSysObjectTags( ASOT_LIST, TAG_END );
	unit->unit_Tx_List			= AllocSysObjectTags( ASOT_LIST, TAG_END );
	unit->unit_Event_List		= AllocSysObjectTags( ASOT_LIST, TAG_END );
	unit->unit_Sample_List		= AllocSysObjectTags( ASOT_LIST, TAG_END );
	unit->unit_Multicast_List	= AllocSysObjectTags( ASOT_LIST, TAG_END );
	unit->unit_Begin_MsgPort	= AllocSysObjectTags( ASOT_PORT, TAG_END );
	unit->unit_Abort_MsgPort	= AllocSysObjectTags( ASOT_PORT, TAG_END );

	if (( ! unit->unit_Rx_List )
	||	( ! unit->unit_Tx_List )
	||	( ! unit->unit_Event_List )
	||	( ! unit->unit_Sample_List )
	||	( ! unit->unit_Multicast_List )
	||	( ! unit->unit_Begin_MsgPort )
	||	( ! unit->unit_Abort_MsgPort ))
	{
		MYERROR( "SANA2 : Process_Init : Error creating objects" );
		goto bailout;
	}

	unit->unit_Begin_MsgPortBit = 1UL << unit->unit_Begin_MsgPort->mp_SigBit;
	unit->unit_Abort_MsgPortBit = 1UL << unit->unit_Abort_MsgPort->mp_SigBit;

	// --

	// Read MAC Address somewhere
	// ie. ENV/Config/UBoot/Hardware
	// HW_ReadMAC()

	// Set if we got it
	unit->unit_MAC_Adr_Okay = TRUE;


	// Set temporay mac addr (only for this example)
	unit->unit_MAC_Adr_Hard[0] = 0x02;
	unit->unit_MAC_Adr_Hard[1] = 0xAA;
	unit->unit_MAC_Adr_Hard[2] = 0xBB;
	unit->unit_MAC_Adr_Hard[3] = 0xCC;
	unit->unit_MAC_Adr_Hard[4] = 0xDD;
	unit->unit_MAC_Adr_Hard[5] = 0x01;
	//
	unit->unit_MAC_Adr_Soft[0] = 0x02;
	unit->unit_MAC_Adr_Soft[1] = 0xAA;
	unit->unit_MAC_Adr_Soft[2] = 0xBB;
	unit->unit_MAC_Adr_Soft[3] = 0xCC;
	unit->unit_MAC_Adr_Soft[4] = 0xDD;
	unit->unit_MAC_Adr_Soft[5] = 0x01;

	// --
	// make sure we can run Configure
	unit->unit_SW_Can_Configure = TRUE;

	// --

	retval = TRUE;

bailout:

	return( retval );
}

// --
