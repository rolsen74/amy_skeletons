
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INC_PRIVATE_ALL_H
#error Include "inc_private/All.h" first
#endif

#ifndef INC_PRIVATE_PROTOS_H
#define INC_PRIVATE_PROTOS_H

// --
// Manager Interface
U32 _manager_Obtain( struct DeviceManagerInterface *Self );
U32 _manager_Release( struct DeviceManagerInterface *Self );
S32 _manager_Open( struct DeviceManagerInterface *Self, struct IORequest *ioreq, U32 unitnum, U32 flags );
PTR _manager_Close( struct DeviceManagerInterface *Self, struct IORequest *ioreq );
PTR _manager_Expunge( struct DeviceManagerInterface *Self );
void _manager_AbortIO( struct DeviceManagerInterface *Self, struct IORequest *ioreq );
void _manager_BeginIO( struct DeviceManagerInterface *Self, struct IORequest *ioreq );
PTR _manager_Init( PTR Dummy, PTR SegList, struct ExecBase *mySysBase );

// --
// Device Commands
void _cmd_0002_Read( struct SANA2Unit *unit, struct IOSana2Req *ioreq );
void _cmd_0003_Write( struct SANA2Unit *unit, struct IOSana2Req *ioreq );
void _cmd_0008_Flush( struct SANA2Unit *unit, struct IOSana2Req *ioreq );
void _cmd_0009_S2_DeviceQuery( struct SANA2Unit *unit, struct IOSana2Req *ioreq );
void _cmd_000A_S2_GetStationAddress( struct SANA2Unit *unit, struct IOSana2Req *ioreq );
void _cmd_000B_S2_ConfigInterface( struct SANA2Unit *unit, struct IOSana2Req *ioreq );
void _cmd_000E_S2_AddMulticastAddress( struct SANA2Unit *unit, struct IOSana2Req *ioreq );
void _cmd_000F_S2_DelMulticastAddress( struct SANA2Unit *unit, struct IOSana2Req *ioreq );
void _cmd_0010_S2_Multicast( struct SANA2Unit *unit, struct IOSana2Req *ioreq );
void _cmd_0011_S2_Broadcast( struct SANA2Unit *unit, struct IOSana2Req *ioreq );
void _cmd_0015_S2_GetSpecialStats( struct SANA2Unit *unit, struct IOSana2Req *ioreq );
void _cmd_0016_S2_GetGlobalStats( struct SANA2Unit *unit, struct IOSana2Req *ioreq );
void _cmd_0017_S2_OnEvent( struct SANA2Unit *unit, struct IOSana2Req *ioreq );
void _cmd_0018_S2_ReadOrphan( struct SANA2Unit *unit, struct IOSana2Req *ioreq );
void _cmd_0019_S2_Online( struct SANA2Unit *unit, struct IOSana2Req *ioreq );
void _cmd_001A_S2_Offline( struct SANA2Unit *unit, struct IOSana2Req *ioreq );
void _cmd_4000_NSCmd_DeviceQuery( struct IOStdReq *ioreq );
void _cmd_C004_S2_GetExtendedGlobalStats( struct SANA2Unit *unit, struct IOSana2Req *ioreq );
void _cmd_C007_S2_Sample_ThroughPut( struct SANA2Unit *unit, struct IOSana2Req *ioreq );
void _cmd_C008_S2_Sana2Hook( struct SANA2Unit *unit, struct IOSana2Req *ioreq );

// --
// Device Resources Functions
S32 Resources_Init( struct SANA2Base *devBase );
void Resources_Free( struct SANA2Base *devBase );
S32 myOpenResources( int max_libs );
void myCloseResources( void );

// --
// Unit Functions
struct SANA2Unit *Unit_Alloc( U32 unitnr );
void Unit_Free( struct SANA2Unit *unit );
S32 Unit_Startup( struct SANA2Unit *unit );

// --
// Unit Process Functions
void Process_Entry( void );
S32 Process_Init( struct SANA2Unit *unit );
void Process_Main( struct SANA2Unit *unit );
void Process_Free( struct SANA2Unit *unit );
void Process_Handle_AbortIO( struct SANA2Unit *unit );
void Process_Handle_BeginIO( struct SANA2Unit *unit );

// --
// SANA2 Functions
S32 Abort_All( struct SANA2Unit *unit, U32 ErrType );
S32 Abort_IOReq( struct SANA2Unit *unit, struct List *list, struct IOSana2Req *ioreq, U32 ErrType );
void Event_Check( struct SANA2Unit *unit, U32 events );
void Packet_Read_Handle( struct SANA2Unit *unit );
void Packet_Read_Done( struct SANA2Unit *unit, U8 *data, U32 length );
void Packet_Send_Schedule( struct SANA2Unit *unit );
void Packet_Send_Done( struct SANA2Unit *unit );

#endif
