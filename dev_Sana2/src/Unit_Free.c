
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void Unit_Free( struct SANA2Unit *unit )
{
	MYDEBUG( "SANA2 : Unit_Free :" );

	if ( ! unit )
	{
		goto bailout;
	}

	unit->unit_StartupComplete = FALSE;

	// --

	if ( unit->unit_TaskAdr )
	{
		while( unit->unit_TaskState == TASK_State_Starting )
		{
			Delay( 1 );	
		}

//		unit->unit_ExitMask = 0;	// unused at the moment
		unit->unit_ExitParent = FindTask( NULL );
		Signal( unit->unit_TaskAdr, SIGBREAKF_CTRL_C );

		while( unit->unit_TaskState != TASK_State_Stopped )
		{
			Delay( 1 );	
		}
	}

	// --
	
	if ( unit->unit_TaskName )
	{
		FreeVec( unit->unit_TaskName );
	}

	// --

	FreeVec( unit );

bailout:

	return;
}

// --
