
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

struct SANA2Unit *Unit_Alloc( U32 unitnr )
{
struct SANA2Unit *unit;
S32 error;

	MYDEBUG( "SANA2 : Unit_Alloc" );

	error = TRUE;

	unit = AllocVecTags( sizeof( struct SANA2Unit ),
		AVT_Clear, 0,
		TAG_END
	);

	if ( ! unit )
	{
		MYERROR( "SANA2 : Error allocating memory" );
		goto bailout;
	}

	unit->unit_UnitNr = unitnr;
	unit->unit_TaskState = TASK_State_Stopped;

	unit->unit_TaskName = ASPrintf( "SANA2 unit #%ld", unitnr );

	if ( ! unit->unit_TaskName )
	{
		MYERROR( "SANA2 : Error allocating memory" );
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
