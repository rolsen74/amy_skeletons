
/*
** SPDX-License-Identifier: Unlicense
** Written 2026 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

/*
** Note:
**
**  When we get a new command/IORequest, we need to send it to something
**  that can handle it, and 9/10 times that means starting a process to
**  handle commands.
**
**  The usual choice is: do we run a single process for all units, or one
**  process per unit? Here we implement one process per unit.
**
**  By sending all IORequests to our unit process, we often benefit by
**  avoiding ObtainSemaphore/ReleaseSemaphore around shared data, since all
**  commands run in the unit process.
**
**  Of course there are exceptions:
**  If your device controls external hardware (e.g., a USB sana2), the
**  sana2 may or may not be connected, but a program might still want to
**  know what type of device it is, regardless of presence.
**
**  So it makes sense to handle NSCMD_DEVICEQUERY outside of the unit process.
**  If you need maximum speed and can handle a command immediately, you can
**  also do it here. Still, it’s usually simpler to run most commands inside
**  the unit process.
*/

void _manager_BeginIO( struct DeviceManagerInterface *Self UNUSED, struct IORequest *ioreq )
{
struct DEVUnit *unit;

//	MYDEBUG( "DEV : _manager_BeginIO : IOReq %p", ioreq );

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
			if (( ! unit->unit_Shutdown ) && ( unit->unit_TaskState == TASK_State_Stopped ))
			{
				Unit_Startup( unit );
			}

			// is the process running or should we send it back
			if (( ! unit->unit_Shutdown ) && ( unit->unit_TaskState == TASK_State_Running ))
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
			MYDEBUG( "DEV : _manager_BeginIO : Unknown Cmd ($%04lx)", (U32) ioreq->io_Command );

			// Unknown Command
			ioreq->io_Error = IOERR_NOCMD;

			ReplyMsg( (PTR) ioreq );
			break;
		}
	}
}

// --
