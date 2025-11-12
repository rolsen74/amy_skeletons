
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void Event_Check( struct SANA2Unit *unit, U32 events )
{
struct IOSana2Req *ioreq;
struct IOSana2Req *next;

	ioreq = (PTR) GetHead( unit->unit_Event_List );

	while( ioreq )
	{
		next = (PTR) GetSucc( (PTR) ioreq );

		if ( ioreq->ios2_WireError & events )
		{
			ioreq->ios2_WireError = events;
			unit->unit_Event_List_Count--;
			Remove( (PTR) ioreq );
			ReplyMsg( (PTR) ioreq );
		}

		ioreq = next;
	}
}

// --
