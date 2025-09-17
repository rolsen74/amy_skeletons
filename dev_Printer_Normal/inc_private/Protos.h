
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INC_PRIVATE_ALL_H
#error Include "inc_privatee/All.h" first
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
void _cmd_0002_Read( struct PrinterUnit *unit, struct IOStdReq *ioreq );
void _cmd_0003_Write( struct PrinterUnit *unit, struct IOStdReq *ioreq );
void _cmd_4000_NSCmd_DeviceQuery( struct IOStdReq *ioreq );

// --
// Device Resources Functions
S32 Resources_Init( struct PrinterBase *devBase );
void Resources_Free( struct PrinterBase *devBase );

// --
// Unit Functions
struct PrinterUnit *Unit_Alloc( U32 unitnr );
void Unit_Free( struct PrinterUnit *unit );
S32 Unit_Startup( struct PrinterUnit *unit );

// --
// Unit Process Functions
void Process_Entry( void );
S32 Process_Init( struct PrinterUnit *unit );
void Process_Main( struct PrinterUnit *unit );
void Process_Free( struct PrinterUnit *unit );
void Process_Handle_AbortIO( struct PrinterUnit *unit );
void Process_Handle_BeginIO( struct PrinterUnit *unit );

#endif
