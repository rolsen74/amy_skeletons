
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

/*
** Important:
**
**  Printer device: allows only one opener per unit.
*/

S32 _manager_Open(
	struct DeviceManagerInterface *Self,
	struct IORequest *ioreq,
	U32 unitnum,
	U32 flags UNUSED )
{
struct PrinterBase *devBase;
struct PrinterUnit *unit;
S32 error;

	MYDEBUG( "Printer : _manager_Open" );

	error = 0;

	devBase = (PTR) Self->Data.LibBase;

	ObtainSemaphore( & devBase->dev_PRT_Semaphore );

	/* Add Expunge protection */
	devBase->dev_Base.dd_Library.lib_OpenCnt++;

	/* Check request size */
	if ( ioreq->io_Message.mn_Length < sizeof( struct IORequest ))
	{
		MYERROR( "Printer : Invalid request size : Size %lu", (U32) ioreq->io_Message.mn_Length );
		error = IOERR_OPENFAIL;
		goto bailout;
	}

	/* Check for valid Unit number */
	if ( unitnum >= MAX_PRT_UNITS )
	{
		MYERROR( "Printer : Invalid unit number : Unit nr #%lu", unitnum );
		error = IOERR_OPENFAIL;
		goto bailout;
	}

	/* Only one opener pr. unit, check if its in use */
	if ( devBase->dev_PRT_Units[ unitnum ] )
	{
		MYERROR( "Printer : Unit alreay in use : Unit nr #%lu", unitnum );
		error = IOERR_OPENFAIL;
		goto bailout;
	}

	/* Create new unit */
	unit = Unit_Alloc( unitnum );

	if ( ! unit )
	{
		MYERROR( "Printer : Error creating Unit" );
		error = IOERR_OPENFAIL;
		goto bailout;
	}

	ioreq->io_Unit = (PTR) unit;
	unit->unit_Unit.unit_OpenCnt++;
 
	/* Prevent delayed expunges */
	devBase->dev_Base.dd_Library.lib_Flags &= ~LIBF_DELEXP;
 
	/* Success */
	error = 0;

bailout:

	if ( ! error )
	{
		devBase->dev_Base.dd_Library.lib_OpenCnt++;
	}
	else
	{
		ioreq->io_Device = NULL;
	}

	ioreq->io_Error = error;

	/* Remove Expunge protection */
	devBase->dev_Base.dd_Library.lib_OpenCnt--;

	ReleaseSemaphore( & devBase->dev_PRT_Semaphore );

	return( error );
}

// --
