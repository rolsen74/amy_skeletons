
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --
// We recieved a Signal that a Read packet
// have arrived

void Packet_Read_Handle( struct SANA2Unit *unit )
{
PTR data;
U32 len;

	// This function is device specific
	// so you should have setup buffer(s)
	// that you can pass along here.

	len = 0;
	data = NULL;

	Packet_Read_Done( unit, data, len );	
}

// --
