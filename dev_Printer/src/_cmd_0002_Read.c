
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _cmd_0002_Read( struct PrinterUnit *unit, struct IOStdReq *ioreq )
{
	MYDEBUG( "Printer : _cmd_0002_Read" );

	// No need for Semaphore protection here
	// as all List handling in done in same Unit process
	AddTail( unit->unit_Read_List, (PTR) ioreq );
}

// --
