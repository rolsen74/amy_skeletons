
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void Process_Main( struct PrinterUnit *unit )
{
U32 wait;
U32 mask;

	MYERROR( "Printer : Process_Main : Enter", 0 );

	wait = SIGBREAKF_CTRL_C;
	wait |= unit->unit_Begin_MsgPortBit;
	wait |= unit->unit_Abort_MsgPortBit;

	// I'm using a BOOL here, you may need too 
	// shutdown from other code when project grows
	unit->unit_Running = TRUE;

	while( unit->unit_Running )
	{
		mask = Wait( wait );

		if ( mask & unit->unit_Abort_MsgPortBit )
		{
			Process_Handle_AbortIO( unit );
		}

		if ( mask & unit->unit_Begin_MsgPortBit )
		{
			Process_Handle_BeginIO( unit );
		}

		if ( mask & SIGBREAKF_CTRL_C )
		{
			// I check if its myself that sended the break
			// but you may not need it, so its optional
			if ( unit->unit_ExitParent )
			{
				unit->unit_Running = FALSE;
			}
		}
	}

	unit->unit_StartupComplete = FALSE;

	MYERROR( "Printer : __myProcess_Main : Leave", 0 );
}

// --
