
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void Process_Handle_BeginIO( struct SANA2Unit *unit )
{
struct IOSana2Req *ioreq;

	while( TRUE )
	{
		ioreq = (PTR) GetMsg( unit->unit_Begin_MsgPort );

		if ( ! ioreq )
		{
			break;
		}

		switch( ioreq->ios2_Req.io_Command )
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

			case /* 0008 */ CMD_FLUSH:
			{
				_cmd_0008_Flush( unit, ioreq );
				break;
			}

			case /* 0009 */ S2_DEVICEQUERY:
			{
				_cmd_0009_S2_DeviceQuery( unit, ioreq );
				break;
			}

			case /* 000A */ S2_GETSTATIONADDRESS:
			{
				_cmd_000A_S2_GetStationAddress( unit, ioreq );
				break;
			}

			case /* 000B */ S2_CONFIGINTERFACE:
			{
				_cmd_000B_S2_ConfigInterface( unit, ioreq );
				break;
			}

			case /* 000E */ S2_ADDMULTICASTADDRESS:
			{
				_cmd_000E_S2_AddMulticastAddress( unit, ioreq );
				break;
			}

			case /* 000F */ S2_DELMULTICASTADDRESS:
			{
				_cmd_000F_S2_DelMulticastAddress( unit, ioreq );
				break;
			}

			case /* 0010 */ S2_MULTICAST:
			{
				_cmd_0010_S2_Multicast( unit, ioreq );
				break;
			}

			case /* 0011 */ S2_BROADCAST:
			{
				_cmd_0011_S2_Broadcast( unit, ioreq );
				break;
			}

			case /* 0015 */ S2_GETSPECIALSTATS:
			{
				_cmd_0015_S2_GetSpecialStats( unit, ioreq );
				break;
			}

			case /* 0016 */ S2_GETGLOBALSTATS:
			{
				_cmd_0016_S2_GetGlobalStats( unit, ioreq );
				break;
			}

			case /* 0017 */ S2_ONEVENT:
			{
				_cmd_0017_S2_OnEvent( unit, ioreq );
				break;
			}

			case /* 0018 */ S2_READORPHAN:
			{
				_cmd_0018_S2_ReadOrphan( unit, ioreq );
				break;
			}

			case /* 0019 */ S2_ONLINE:
			{
				_cmd_0019_S2_Online( unit, ioreq );
				break;
			}

			case /* 001A */ S2_OFFLINE:
			{
				_cmd_001A_S2_Offline( unit, ioreq );
				break;
			}

			case /* C004 */ S2_GETEXTENDEDGLOBALSTATS:
			{
				_cmd_C004_S2_GetExtendedGlobalStats( unit, ioreq );
				break;
			}

			case /* C007 */ S2_SAMPLE_THROUGHPUT:
			{
				_cmd_C007_S2_Sample_ThroughPut( unit, ioreq );
				break;
			}

			case /* C008 */ S2_SANA2HOOK:
			{
				_cmd_C008_S2_Sana2Hook( unit, ioreq );
				break;
			}

			default:
			{
				MYINFO( "Unknown Command (%ld) -- This should really not chould happen", ioreq->ios2_Req.io_Command );
				ioreq->ios2_Req.io_Error = IOERR_NOCMD;
				ReplyMsg( (PTR) ioreq );
				break;
			}
		}
	}
}

// --
