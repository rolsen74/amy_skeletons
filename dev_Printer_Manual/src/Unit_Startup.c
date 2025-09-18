
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

S32 Unit_Startup( struct PrinterUnit *unit )
{
struct TaskStartMsg msg;
S32 retval;
U32 mask;
S32 sig;

	retval = FALSE;

	if ( ! unit )
	{
		MYERROR( "Printer : Unit_Startup : NULL Pointer" );
		goto bailout;
	}

	MYDEBUG( "Printer : Unit_Startup : UnitNr #%lu", unit->unit_UnitNr );

	// --
	// Try and alloc signal
	sig = AllocSignal( -1 );

	msg.Result	= 0;
	msg.Parent	= FindTask( NULL );
	msg.Mask	= ( sig == -1 ) ? ( SIGBREAKF_CTRL_D ) : ( 1UL << sig );
	msg.Unit	= unit;

	// Clear signal
	SetSignal( 0, msg.Mask );

	if ( CreateNewProcTags( 
		NP_Name,		unit->unit_TaskName,
		NP_Child,		FALSE,
		NP_Priority,	5,
		NP_StackSize,	1024 * 32,
		NP_Entry,		Process_Entry,
		NP_UserData,	& msg,
		TAG_END ))
	{
		while( TRUE )
		{
			mask = Wait( msg.Mask );

			if (( mask & msg.Mask ) == msg.Mask )
			{
				break;
			}
		}
	}

	if ( sig != -1 )
	{
		FreeSignal( sig );
	}

	if ( ! msg.Result )
	{
		MYERROR( "Printer : Failed to Printer process" );
		goto bailout;
	}

	// --
	// Startup complete, we can now handle IOReq
	unit->unit_StartupComplete = TRUE;

	// All okay
	retval = TRUE;

bailout:

	MYDEBUG( "Printer : Unit_Startup : Leave" );

	return( retval );
}

// --
