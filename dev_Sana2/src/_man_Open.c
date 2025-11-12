
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
**  SANA2 device: allows only one opener per unit.
*/

S32 _manager_Open(
	struct DeviceManagerInterface *Self,
	struct IORequest *ioreq,
	U32 unitnum,
	U32 flags UNUSED )
{
struct SANA2Base *devBase;
struct SANA2Unit *unit;
S32 error;

	MYDEBUG( "SANA2 : _manager_Open" );

	error = 0;

	devBase = (PTR) Self->Data.LibBase;

	ObtainSemaphore( & devBase->dev_SANA2_Semaphore );

	/* Add Expunge protection */
	devBase->dev_Base.dd_Library.lib_OpenCnt++;

	/* Check request size */
	if ( ioreq->io_Message.mn_Length < sizeof( struct IORequest ))
	{
		MYERROR( "SANA2 : Invalid request size : Size %lu", (U32) ioreq->io_Message.mn_Length );
		error = IOERR_OPENFAIL;
		goto bailout;
	}

	/* Check for valid Unit number */
	if ( unitnum >= MAX_SANA2_UNITS )
	{
		MYERROR( "SANA2 : Invalid unit number : Unit nr #%lu", unitnum );
		error = IOERR_OPENFAIL;
		goto bailout;
	}

	/* Only one opener pr. unit, check if its in use */
	if ( devBase->dev_SANA2_Units[ unitnum ] )
	{
		MYERROR( "SANA2 : Unit alreay in use : Unit nr #%lu", unitnum );
		error = IOERR_OPENFAIL;
		goto bailout;
	}

	/* Create new unit */
	unit = Unit_Alloc( unitnum );

	if ( ! unit )
	{
		MYERROR( "SANA2 : Error creating Unit" );
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

	ReleaseSemaphore( & devBase->dev_SANA2_Semaphore );

	return( error );
}

// --
