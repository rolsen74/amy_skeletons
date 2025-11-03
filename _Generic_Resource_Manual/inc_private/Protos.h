
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
// Main Interface
U32 _main_Obtain( struct Test_ResourceIFace *Self );
U32 _main_Release( struct Test_ResourceIFace *Self );
U32 _main_GetVal( struct Test_ResourceIFace *Self );

// --
// Gadget Resources Functions
S32 Resources_Init( struct Real_ResourceBase *devBase );
void Resources_Free( struct Real_ResourceBase *devBase );
S32 myOpenResources( int max_libs );
void myCloseResources( void );

#endif
