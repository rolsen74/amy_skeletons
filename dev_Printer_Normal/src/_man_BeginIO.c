
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --
// Note:
//
//  When we get a new command/ioreq, we need too send it too some
//  one that can handle that.. and 9/10 times it mean we have to start
//  a process to handle commands. 
//
//  So most of the times the chooice is, do we need only one process too
//  handle all units or one process pr unit. Here we implement one process
//  pr. unit.
//
//  By sending all ioreq's too our process, we offen have the benifit that
//  we can avoid calling ObtainSemaphore/ReleaseSemaphore before accessing
//  data now that all commands run in the unit process.
//
//  But there is ofcoarse execptions.. 
//  If you have a device that controlled a usb device like a printer.
//  The printer may not be connected or not, but a user program might want
//  too know what type of device it is, no matter of if the printer there or
//  not.. 
//
//  So it makes sense too handle NSCMD_DEVICEQUERY out side of the process.
//  Or maybe you want maximum speed and can handle it right here and now,
//  you could also handle it here, thinkgs are easyer too run all/most commands
//  in the unit process.
//

void _manager_BeginIO( struct DeviceManagerInterface *Self UNUSED, struct IORequest *ioreq )
{
struct PrinterUnit *unit;

	MYDEBUG( "Printer : _manager_BeginIO : IOReq %p", ioreq );

	// Disable QUICK IO - we do not support that
	ioreq->io_Message.mn_Node.ln_Type = NT_MESSAGE;
	ioreq->io_Flags &= ~IOF_QUICK;
	ioreq->io_Error = 0;

	switch( ioreq->io_Command )
	{
		// Handle Device Query outside unit process
		case /* 4000 */ NSCMD_DEVICEQUERY:
		{
			_cmd_4000_NSCmd_DeviceQuery( (PTR) ioreq );
			break;
		}

		// Catch all known Device commands here
		case /* 0002 */	CMD_READ:
		case /* 0003 */	CMD_WRITE:
		{
			unit = (PTR) ioreq->io_Unit;

			// check if unit process is running, if not try and start it
			if (( ! unit->unit_Shutdown ) && ( ! unit->unit_StartupComplete ))
			{
				Unit_Startup( unit );
			}

			// is the process running or should we send it back
			if (( ! unit->unit_Shutdown ) && ( unit->unit_StartupComplete ))
			{
				PutMsg( unit->unit_Begin_MsgPort, (PTR) ioreq );
			}
			else
			{
				ioreq->io_Error = IOERR_UNITBUSY;
				ReplyMsg( (PTR) ioreq );
			}
			break;
		}

		// Return unknown commands here
		default:
		{
			MYDEBUG( "Printer : _manager_BeginIO : Unknown Cmd ($%04lx)", (U32) ioreq->io_Command );

			// Unknown Command
			ioreq->io_Error = IOERR_NOCMD;

			ReplyMsg( (PTR) ioreq );
			break;
		}
	}
}

// --
