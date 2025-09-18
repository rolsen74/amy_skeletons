
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
U32 _manager_Obtain( struct LibraryManagerInterface *Self );
U32 _manager_Release( struct LibraryManagerInterface *Self );
PTR _manager_Open( struct LibraryManagerInterface *Self, U32 version );
PTR _manager_Close( struct LibraryManagerInterface *Self );
PTR _manager_Expunge( struct LibraryManagerInterface *Self );
PTR _manager_Init( PTR Dummy, PTR SegList, struct ExecBase *mySysBase );

// --
// Docky Interface
U32 _docky_Obtain( struct DockyIFace *Self );
U32 _docky_Release( struct DockyIFace *Self );
U32	_docky_Expunge( struct DockyIFace *Self );
PTR _docky_Clone( struct DockyIFace *Self );
BOOL _docky_Get( struct DockyIFace *Self, U32 msgType, U32 *msgData );
BOOL _docky_Set( struct DockyIFace *Self, U32 msgType, U32 msgData );
BOOL _docky_Process( struct DockyIFace *Self, U32 turnCount, U32 *msgType, U32 *msgData, BOOL *anotherTurn );

// --
// Device Resources Functions
S32 Resources_Init( struct DockyBase *devBase );
void Resources_Free( struct DockyBase *devBase );

#endif
