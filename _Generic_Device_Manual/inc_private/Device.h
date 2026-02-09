
/*
** SPDX-License-Identifier: Unlicense
** Written 2026 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INC_PRIVATE_ALL_H
#error Include "inc_private/All.h" first
#endif

#ifndef INC_PRIVATE_DEVICE_H
#define INC_PRIVATE_DEVICE_H

// --

#define MAX_DEV_UNITS		32		// 

// --

struct DEVBase
{
	struct Device					dev_Base;
	PTR								dev_SegList;
	struct SignalSemaphore 			dev_DEV_Semaphore;
	PTR								dev_DEV_Units[MAX_DEV_UNITS];
};

// --

struct DEVUnit
{
	struct Unit						unit_Unit;
	U32								unit_UnitNr;

	STR								unit_TaskName;
	enum TaskState					unit_TaskState;
	struct Task *					unit_TaskAdr;

	struct Task *					unit_ExitParent;
	U32								unit_ExitMask;

	struct MsgPort *				unit_Begin_MsgPort;
	U32								unit_Begin_MsgPortBit;

	struct MsgPort *				unit_Abort_MsgPort;
	U32								unit_Abort_MsgPortBit;

	// -- Settings
	U8								unit_StartupComplete;
	U8								unit_Shutdown;				// Yes time to stop, clear buffers and exit
	U8								unit_Running;				// 
	U8								unit_SW_Can_Configure;		// Make sure we are only Configured SW once
	U8								unit_Online_Stat;			// True/False if we are online
};

// --

struct AbortIOMessage
{
	struct Message					am_Message;
	PTR								am_IOReq;
};

// --

#endif
