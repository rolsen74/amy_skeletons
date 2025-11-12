
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _cmd_0015_S2_GetSpecialStats( struct SANA2Unit *unit, struct IOSana2Req *ioreq )
{
struct Sana2SpecialStatHeader *h;
struct Sana2SpecialStatRecord *r;
U32 records;
U32 loop;
U32 cnt;

	MYDEBUG( "SANA2 : _cmd_0015_S2_GetSpecialStats" );

	h = ioreq->ios2_StatData;

	if ( ! h )
	{
		MYERROR( "NULL Pointer" );
		ioreq->ios2_Req.io_Error	= S2ERR_BAD_ARGUMENT;
		ioreq->ios2_WireError		= S2WERR_NULL_POINTER;
	}
	else
	{
		records = 0;

		// This driver only have 2 Special Records
		// Plus We check how many User ask for
		loop = MIN( h->RecordCountMax, 2 );

		// Record's are right after Header
		r = (struct Sana2SpecialStatRecord *) & h[1];

		for( cnt=0 ; cnt < loop ; cnt++ )
		{
			switch( cnt )
			{
				case 0:
				{
					r[records].Type		= S2SS_ETHERNET_BADMULTICAST;
					r[records].Count	= (U32) unit->unit_MulticastRejects;
					r[records].String	= (STR) "Bad multicast filtering";
					break;
				}

				case 1:
				{
					r[records].Type		= S2SS_ETHERNET_FIFO_UNDERRUNS;
					r[records].Count	= (U32) unit->unit_Underruns;
					r[records].String	= (STR) "FIFO underruns";
					break;
				}

				default:
				{
					// This should really not happen
					continue;
				}
			}

			records++;
		}

		h->RecordCountSupplied = records;
	}

	ReplyMsg( (PTR) ioreq );
}

// --
