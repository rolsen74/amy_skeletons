
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void Process_Main( struct SANA2Unit *unit )
{
U32 wait;
U32 mask;

	MYERROR( "SANA2 : Process_Main : Enter" );

	wait = SIGBREAKF_CTRL_C;
	wait |= unit->unit_Rx_SignalBit;
	wait |= unit->unit_Tx_SignalBit;
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
			Packet_Send_Schedule( unit );
		}

		if ( mask & unit->unit_Rx_SignalBit )
		{
			// We received a Packet
			Packet_Read_Handle( unit );
		}

		if ( mask & unit->unit_Tx_SignalBit )
		{
			// Packet Send
			Packet_Send_Done( unit );
			Packet_Send_Schedule( unit );
		}

		if ( mask & SIGBREAKF_CTRL_C )
		{
			// I check if its myself that sended the break
			// but you may not need it, so its optional
			if ( unit->unit_ExitParent )
			{
				unit->unit_Running = FALSE;
				unit->unit_Shutdown = TRUE;
			}
		}
	}

	unit->unit_StartupComplete = FALSE;

	MYERROR( "SANA2 : __myProcess_Main : Leave" );
}

// --
