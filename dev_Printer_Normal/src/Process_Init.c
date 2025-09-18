
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

S32 Process_Init( struct PrinterUnit *unit )
{
S32 retval;

	retval = FALSE;

	MYDEBUG( "Printer : Process_Init" );

	// --

	unit->unit_Read_List		= AllocSysObjectTags( ASOT_LIST, TAG_END );
	unit->unit_Write_List		= AllocSysObjectTags( ASOT_LIST, TAG_END );
	unit->unit_Begin_MsgPort	= AllocSysObjectTags( ASOT_PORT, TAG_END );
	unit->unit_Abort_MsgPort	= AllocSysObjectTags( ASOT_PORT, TAG_END );

	if (( ! unit->unit_Read_List )
	||	( ! unit->unit_Write_List )
	||	( ! unit->unit_Begin_MsgPort )
	||	( ! unit->unit_Abort_MsgPort ))
	{
		MYERROR( "Printer : Process_Init : Error creating objects" );
		goto bailout;
	}

	unit->unit_Begin_MsgPortBit = 1UL << unit->unit_Begin_MsgPort->mp_SigBit;
	unit->unit_Abort_MsgPortBit = 1UL << unit->unit_Abort_MsgPort->mp_SigBit;

	// --

	retval = TRUE;

bailout:

	return( retval );
}

// --
