
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

struct PrinterUnit *Unit_Alloc( U32 unitnr )
{
struct PrinterUnit *unit;
S32 error;

	MYDEBUG( "Printer : Unit_Alloc", 0 );

	error = TRUE;

	unit = AllocVecTags( sizeof( struct PrinterUnit ),
		AVT_Clear, 0,
		TAG_END
	);

	if ( ! unit )
	{
		MYERROR( "Printer : Error allocating memory", 0 );
		goto bailout;
	}

	unit->unit_UnitNr = unitnr;
	unit->unit_TaskState = TASK_State_Stopped;

	unit->unit_TaskName = ASPrintf( "Printer unit #%ld", unitnr );

	if ( ! unit->unit_TaskName )
	{
		MYERROR( "Printer : Error allocating memory", 0 );
		goto bailout;
	}

	// --

	// hmm lets not start a Process here.
	// If someone just want to Query the Device type,
	// we don't need too startup every thing for that.

	// --

	error = FALSE;

bailout:

	if (( unit ) && ( error ))
	{
		Unit_Free( unit );
		unit = NULL;
	}

	return( unit );
}

// --
