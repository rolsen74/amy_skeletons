
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INC_PRIVATE_ALL_H
#error Include "inc_private/All.h" first
#endif

#ifndef INC_PRIVATE_DEVICE_H
#define INC_PRIVATE_DEVICE_H

// --

#define IS_MULTICAST(addr)	(((U8 *)(addr))[0] & 0x01)

#define IS_BROADCAST(addr)	(((U8 *)(addr))[0] == 0xFF && \
							 ((U8 *)(addr))[1] == 0xFF && \
							 ((U8 *)(addr))[2] == 0xFF && \
							 ((U8 *)(addr))[3] == 0xFF && \
							 ((U8 *)(addr))[4] == 0xFF && \
							 ((U8 *)(addr))[5] == 0xFF )

// --
// You well proberly need too adjust the MTU sizes
// see hardware info

#define ETHERNET_MTU		1500	// Normal Packet size send
#define ETHERNET_RAW_MTU	1516	// The hardware may add CRC info to packet
#define MAX_SANA2_UNITS		32		// 

// --

struct BufferManagement
{
	struct Hook *	bm_CopyHook;
	struct Hook *	bm_PacketHook;
	PTR				bm_CopyToBuff;
	Tag				bm_CopyToBuffTag;
	PTR				bm_CopyFromBuff;
	Tag				bm_CopyFromBuffTag;
	Tag				bm_DMACopyToBuffTag;
	Tag				bm_DMACopyFromBuffTag;
};

// --

struct MulticastAddress
{
	struct Node		mca_Node;
	S32				mca_UseCount;
	U8				mca_Address[6];
};

// --

struct SANA2Base
{
	struct Device					dev_Base;
	PTR								dev_SegList;
	struct SignalSemaphore 			dev_SANA2_Semaphore;
	PTR								dev_SANA2_Units[MAX_SANA2_UNITS];
};

// --

struct SANA2Unit
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

	struct List	*					unit_Rx_List;
	S32								unit_Rx_List_Count;
	S32								unit_Rx_Signal;
	U32								unit_Rx_SignalBit;

	struct List	*					unit_Tx_List;
	S32								unit_Tx_List_Count;
	S32								unit_Tx_Signal;
	U32								unit_Tx_SignalBit;
	struct IOSana2Req *				unit_Tx_Active_IOReq;

	struct List	*					unit_Event_List;
	S32								unit_Event_List_Count;

	struct List	*					unit_Sample_List;
	S32								unit_Sample_List_Count;

	struct List	*					unit_Multicast_List;
	S32								unit_Multicast_List_Count;

	// -- Stats
	U64								unit_Reconfigurations;
	U64								unit_Overruns;
	U64								unit_Underruns;
	U64								unit_BadData;
	U64								unit_UnknownTypesReceived;
	U64								unit_PacketsReceived;
	U64								unit_PacketsSent;
	U64								unit_MulticastRejects;
	struct TimeVal					unit_LastStart;

	// -- Settings
	U8								unit_MAC_Adr_Hard[6];		// MAC hardware address
	U8								unit_MAC_Adr_Soft[6];		// MAC software address
	U8								unit_StartupComplete;
	U8								unit_Shutdown;				// Yes time to stop, clear buffers and exit
	U8								unit_Running;				// 
	U8								unit_MAC_Adr_Okay;			// MAC Addess have been found/set
	U8								unit_SW_Can_Configure;		// Make sure we are only Configured SW once
	U8								unit_Online_Stat;			// True/False if we are online
	U8								unit_100MBits;				// True/False if we are in 10/100 MBits
};

// --

struct AbortIOMessage
{
	struct Message					am_Message;
	PTR								am_IOReq;
};

// --

#endif
