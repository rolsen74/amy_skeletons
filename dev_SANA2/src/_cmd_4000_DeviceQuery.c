
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

/* Supported commands */
static const U16 _DevNSDCmds[] =
{
// Common device commands
/* 0000 */	//	CMD_INVALID,			// Not a real command
/* 0001 */	//	CMD_RESET,
/* 0002 */	CMD_READ,
/* 0003 */	CMD_WRITE,
/* 0004 */	//	CMD_UPDATE,
/* 0005 */	//	CMD_CLEAR,
/* 0006 */	//	CMD_STOP,
/* 0007 */	//	CMD_START,
/* 0008 */	CMD_FLUSH,
/* 0009	*/	//	CMD_NONSTD,				// Normal first Device Specific Command

// SANA2 commands
/* 0009 */	S2_DEVICEQUERY,
/* 000A */	S2_GETSTATIONADDRESS,
/* 000B */	S2_CONFIGINTERFACE,
/* 000E */	S2_ADDMULTICASTADDRESS,
/* 000F */	S2_DELMULTICASTADDRESS,
/* 0010 */	S2_MULTICAST,
/* 0011 */	S2_BROADCAST,
/* 0012 */	//	S2_TRACKTYPE,
/* 0013 */	//	S2_UNTRACKTYPE,
/* 0014 */	//	S2_GETTYPESTATS,
/* 0015 */	S2_GETSPECIALSTATS,
/* 0016 */	S2_GETGLOBALSTATS,
/* 0017 */	S2_ONEVENT,
/* 0018 */	S2_READORPHAN,
/* 0019 */	S2_ONLINE,
/* 001A */	S2_OFFLINE,

// New Style commands
/* 4000 */	NSCMD_DEVICEQUERY,

// SANA2 commands
/* C002 */	//	S2_GETPEERADDRESS,
/* C003 */	//	S2_GETDNSADDRESS,
/* C004 */	S2_GETEXTENDEDGLOBALSTATS,
/* C005 */	//	S2_CONNECT,
/* C006 */	//	S2_DISCONNECT,
/* C007 */	S2_SAMPLE_THROUGHPUT,
/* C008 */	S2_SANA2HOOK,
/* C010 */	//	S2_GETSIGNALQUALITY,
/* C011 */	//	S2_GETNETWORKS,
/* C012 */	//	S2_SETOPTIONS,
/* C013 */	//	S2_SETKEY,
/* C014 */	//	S2_GETNETWORKINFO,
/* C015 */	//	S2_READMGMT,
/* C016 */	//	S2_WRITEMGMT,
/* C017 */	//	S2_GETRADIOBANDS,

	0
};

void _cmd_4000_NSCmd_DeviceQuery( struct IOStdReq *ioreq )
{
struct NSDeviceQueryResult *nsd;

	MYDEBUG( "SANA2 : NSCmd_DeviceQuery" );

	nsd = ioreq->io_Data;

	if (( nsd ) && ( ioreq->io_Length >= sizeof( struct NSDeviceQueryResult )))
	{
		nsd->DevQueryFormat		= 0;
		nsd->SizeAvailable		= sizeof( struct NSDeviceQueryResult );
		nsd->DeviceType			= NSDEVTYPE_SANA2;
		nsd->DeviceSubType		= 0;
		nsd->SupportedCommands	= (PTR) _DevNSDCmds;

		ioreq->io_Actual		= sizeof( struct NSDeviceQueryResult );
		ioreq->io_Error			= 0;
	}
	else
	{
		MYDEBUG( "SANA2 : Supplied Query buffer is to small" );
		ioreq->io_Error			= IOERR_BADLENGTH;
	}

	ReplyMsg( (PTR) ioreq );
}

// --
