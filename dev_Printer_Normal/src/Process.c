
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void Process_Entry( void )
{
struct TaskStartMsg *msg;
struct PrinterUnit *unit;
struct Task *parent;
struct Task *self;
U32 mask;
S32 stat;

	MYERROR( "Printer : Process_Entry : Enter", 0 );

	self	= FindTask( NULL );
	msg		= (PTR) self->tc_UserData;
	parent	= msg->Parent;
	mask	= msg->Mask;
	unit	= msg->Unit;

	// --

	unit->unit_TaskState = TASK_State_Starting;

	stat = Process_Init( unit );

	if ( stat )
	{
		unit->unit_TaskAdr = self;

		msg->Result = TRUE;
		Signal( parent, mask );

		// --

		unit->unit_TaskState = TASK_State_Running;

		Process_Main( unit );

		unit->unit_TaskState = TASK_State_Stopping;

		// --

		parent	= unit->unit_ExitParent;
		mask	= unit->unit_ExitMask;

		unit->unit_TaskAdr = NULL;
	}

	Process_Free( unit );

	// --

	Disable();

	unit->unit_TaskState = TASK_State_Stopped;

	MYERROR( "Printer : Process_Entry : Leave", 0 );

	// --
	// Parent can be NULL

	if ( parent )
	{
		Signal( parent, mask );
	}
}

// --
