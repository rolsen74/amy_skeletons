
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INC_PRIVATE_ALL_H
#error Include "inc_privatee/All.h" first
#endif

#ifndef INC_PRIVATE_DEVICE_H
#define INC_PRIVATE_DEVICE_H

// --

#define MAX_PRT_UNITS				32

struct PrinterBase
{
	struct Device					dev_Base;
	PTR								dev_SegList;
	struct SignalSemaphore 			dev_PRT_Semaphore;
	PTR								dev_PRT_Units[MAX_PRT_UNITS];
};

// --

struct PrinterUnit
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

	struct List	*					unit_Read_List;
	struct List	*					unit_Write_List;

	// -- Settings
	U8								unit_StartupComplete;
//	U8								unit_NotRunning;			// Error shown
//	U8								unit_CfgError;				// Cfg err Shown
//	U8								unit_Detached;				// USB Device disconnected
//	U8								unit_PrinterStatus;
//	U8								unit_LastByteSend;
	U8								unit_Shutdown;				// Yes time to stop, clear buffers and exit
	U8								unit_Running;				// 
};

// --

struct AbortIOMessage
{
	struct Message		am_Message;
	PTR					am_IOReq;
};

// --

#endif
