
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

static void _UpdateSample( struct SANA2Unit *unit, U32 length )
{
struct Sana2ThroughputStats *stats;
struct IOSana2Req *ioreq;

	if ( unit->unit_Sample_List_Count > 0 )
	{
		ioreq = (PTR) GetHead( unit->unit_Sample_List );

		while( ioreq )
		{
			stats = ioreq->ios2_StatData;

			if ( stats )
			{
				if ( stats->s2ts_Actual >= offsetof( struct Sana2ThroughputStats, s2ts_BytesReceived ) + sizeof( U64 ))
				{
					stats->s2ts_BytesReceived += length;
				}

				if ( stats->s2ts_Actual >= offsetof( struct Sana2ThroughputStats, s2ts_Updates ) + sizeof( U64 ))
				{
					stats->s2ts_Updates++;
				}

				// --
				// Do signal last, after we have updated Stats

				if ( stats->s2ts_Actual >= offsetof( struct Sana2ThroughputStats, s2ts_NotifyMask ) + sizeof( U32 ))
				{
					if (( stats->s2ts_NotifyMask ) && ( stats->s2ts_NotifyTask ))
					{
						Signal( stats->s2ts_NotifyTask, stats->s2ts_NotifyMask );
					}
				}
			}

			ioreq = (PTR) GetSucc( (PTR) ioreq );
		}
	}
}

// --

static U32 _GetFlags( struct SANA2Unit *unit, U8 *buffer )
{
struct MulticastAddress *mc;
U32 flags;

	/**/ if ( IS_BROADCAST( buffer ))
	{
		flags = SANA2IOF_BCAST;
	}
	else if ( IS_MULTICAST( buffer ))
	{
		mc = (PTR) GetHead( unit->unit_Multicast_List );

		while( mc )
		{
			if ( ! memcmp( mc->mca_Address, buffer, 6  ))
			{
				break;
			}
			else
			{
				mc = (PTR) GetSucc( (PTR) mc );
			}
		}

		if ( mc )
		{
			flags = SANA2IOF_MCAST;
		}
		else
		{
			unit->unit_MulticastRejects++;
			flags = 0;
		}
	}
	else
	{
		flags = 0;
	}

	return(	flags );
}

// --

static void _HandleIOReq( struct SANA2Unit *unit, struct IOSana2Req *ioreq, U8 *buffer, U32 length )
{
struct BufferManagement *bm;
struct SANA2CopyHookMsg msg;
U32 local_length;
U8 *local_buffer;
S32 copied;
U32 flags;

	// --

	if ( ioreq->ios2_Req.io_Flags & SANA2IOF_RAW )
	{
		local_buffer = buffer;
		local_length = length;
	}
	else
	{
		// Strip ethernet header if this isn't a raw
		local_buffer = buffer + 14;
		local_length = length - 14;
	}

	// --
	// Copy Buffer

	bm = (PTR) ioreq->ios2_BufferManagement;

	if ( bm )
	{
		if ( bm->bm_CopyToBuffTag == S2_CopyToBuff )
		{
			msg.schm_Method		= bm->bm_CopyToBuffTag;
			msg.schm_MsgSize	= sizeof( msg );
			msg.schm_To			= ioreq->ios2_Data;
			msg.schm_From		= local_buffer;
			msg.schm_Size		= local_length;

			copied = !! CallHookPkt( bm->bm_CopyHook, ioreq, & msg );
		}
		else
		{
			copied = !! EmulateTags( bm->bm_CopyToBuff,
				ET_RegisterA0,	ioreq->ios2_Data,
				ET_RegisterA1,	local_buffer,
				ET_RegisterD0,	local_length,
				TAG_END
			);
		}
	}
	else
	{
		copied = FALSE;
	}

	if ( copied )
	{
		// set flags based on received packet
		flags  = _GetFlags( unit, buffer );
		flags |= ( ioreq->ios2_Req.io_Flags & ~( SANA2IOF_MCAST | SANA2IOF_BCAST ));

		ioreq->ios2_Req.io_Flags = flags;
		ioreq->ios2_DataLength = local_length;

		memcpy( & ioreq->ios2_DstAddr[0], & buffer[0], 6 );
		memcpy( & ioreq->ios2_SrcAddr[0], & buffer[6], 6 );
	}
	else
	{
		Event_Check( unit, S2EVENT_ERROR | S2EVENT_RX | S2EVENT_BUFF );

		ioreq->ios2_Req.io_Error	= S2ERR_NO_RESOURCES;
		ioreq->ios2_WireError		= S2WERR_BUFF_ERROR;
	}

	// --

	Remove( (PTR) ioreq );
	unit->unit_Rx_List_Count--;

	ReplyMsg( (PTR) ioreq );
}

// --
// This Function is called when we have receive the entire ethernet packet

void Packet_Read_Done( struct SANA2Unit *unit, U8 *data, U32 length )
{
struct IOSana2Req *ioreq;
U32 packet_type;

	MYDEBUG( "SANA2 : Packet_GotRead( Data %p, Length %lu )", data, length );

	// A valid frame received
	unit->unit_PacketsReceived++;

	// Update Sample Stats
	_UpdateSample( unit, length );

	// Lets peek into data
	packet_type = (( data[12] << 8 ) | ( data[13] << 0 ));

	// Lets find an IOReq with correct type
	ioreq = (PTR) GetHead( unit->unit_Rx_List );

	while( ioreq )
	{
		if ( ioreq->ios2_PacketType == packet_type )
		{
			break;
		}
		else
		{
			ioreq = (PTR) GetSucc( (PTR) ioreq );
		}
	}

	if ( ioreq )
	{
		_HandleIOReq( unit, ioreq, data, length );
	}
	else
	{
		MYINFO( "SANA2 : About to drop packet for - %02lx:%02lx:%02lx:%02lx:%02lx:%02lx",
			(U32) data[0x06],
			(U32) data[0x07],
			(U32) data[0x08],
			(U32) data[0x09],
			(U32) data[0x0a],
			(U32) data[0x0b]
		);

		// If we didn't find a place for that packet, mark it as dropped
		unit->unit_UnknownTypesReceived++;
	}
}
