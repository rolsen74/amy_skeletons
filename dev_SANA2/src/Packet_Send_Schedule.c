
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void Packet_Send_Schedule( struct SANA2Unit *unit )
{
struct IOSana2Req *ioreq;

	// Check, can we send another?
	if ( unit->unit_Tx_Active_IOReq )
	{
		goto bailout;
	}

	// Check, are there another to send?
	ioreq = (PTR) RemHead( unit->unit_Tx_List );

	if ( ! ioreq )
	{
		goto bailout;
	}

	// Here you should setup
	// registers/device to start a Transfer.
	//
	// But make sure not too it a blocking function 
	// as that will stop Read's and main loop functions

	unit->unit_Tx_Active_IOReq = ioreq;

bailout:

	return;
}

// --
