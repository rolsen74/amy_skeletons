
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

PTR _manager_Close( struct DeviceManagerInterface *Self, struct IORequest *ioreq )
{
struct PrinterBase *devBase;
struct PrinterUnit *unit;
PTR seglist;

	MYDEBUG( "Printer : _manager_Close : IOReq %p", ioreq );

	seglist = NULL;

	devBase = (PTR) Self->Data.LibBase;

	ObtainSemaphore( & devBase->dev_PRT_Semaphore );

	// Check we have an Unit
	unit = (PTR) ioreq->io_Unit;

	if ( ! unit )
	{
		MYERROR( "Printer : Unit NULL Pointer" );
		goto bailout;
	}

	// Check Unit open count
	if ( unit->unit_Unit.unit_OpenCnt )
	{
		unit->unit_Unit.unit_OpenCnt--;
	}

	if ( unit->unit_Unit.unit_OpenCnt )
	{
		// Hmm since we only have one Opener pr unit.. this is an error
		MYERROR( "Printer : Unit open count not Zero : OpenCnt %ld", unit->unit_Unit.unit_OpenCnt );
		goto bailout;
	}

	// Clear Open Array Ptr
	devBase->dev_PRT_Units[ unit->unit_UnitNr ] = NULL;

	// Free Unit
	Unit_Free( unit );
	unit = NULL;

	// Make sure unit can't be closed again
	ioreq->io_Device = NULL;
	ioreq->io_Unit = NULL;

	// Update Device open count
	if ( devBase->dev_Base.dd_Library.lib_OpenCnt )
	{
		devBase->dev_Base.dd_Library.lib_OpenCnt--;
	}

	// Check if we can expunge our self
	if ( ! devBase->dev_Base.dd_Library.lib_OpenCnt )
	{
		if ( devBase->dev_Base.dd_Library.lib_Flags & LIBF_DELEXP )
		{
			seglist = _manager_Expunge( Self );
		}
	}

bailout:

	ReleaseSemaphore( & devBase->dev_PRT_Semaphore );

	// Return NULL or SegList
	return( seglist );
}

// --
