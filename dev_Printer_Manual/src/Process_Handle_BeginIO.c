
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void Process_Handle_BeginIO( struct PrinterUnit *unit )
{
struct IORequest *ioreq;

	while( TRUE )
	{
		ioreq = (PTR) GetMsg( unit->unit_Begin_MsgPort );

		if ( ! ioreq )
		{
			break;
		}

		ioreq->io_Error = 0;

		switch( ioreq->io_Command )
		{
			case /* 0002 */ CMD_READ:
			{
				_cmd_0002_Read( unit, (PTR) ioreq );
				break;
			}

			case /* 0003 */ CMD_WRITE:
			{
				_cmd_0003_Write( unit, (PTR) ioreq );
				break;
			}

			default:
			{
				MYINFO( "Unknown Command (%ld) -- This should really not chould happen", ioreq->io_Command );
				ioreq->io_Error = IOERR_NOCMD;
				ReplyMsg( (PTR) ioreq );
				break;
			}
		}
	}
}

// --
