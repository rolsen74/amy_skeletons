
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
U32 _main_Obtain( struct Test_USBFDIFace *Self );
U32 _main_Release( struct Test_USBFDIFace *Self );
PTR _main_Clone( struct Test_USBFDIFace *Self );
U32 _main_Expunge( struct Test_USBFDIFace *Self );
U32 _main_GetAttrsA( struct Test_USBFDIFace *Self, struct TagItem *taglist );
U32 VARARGS68K _main_GetAttrs( struct Test_USBFDIFace *Self, ... );
S32 _main_RunFunction( struct Test_USBFDIFace *Self, struct USBFDStartupMsg *msg );
S32 _main_RunInterface( struct Test_USBFDIFace *Self, struct USBFDStartupMsg *msg );

// --
// Library Resources Functions
S32		Resources_Init( struct LibBase *devBase );
void	Resources_Free( struct LibBase *devBase );
S32		myOpenResources( int max_libs );
void	myCloseResources( void );

// --
// USB
S32		USB_Driver( struct Test_USBFDIFace *Self, struct USBFDStartupMsg *msg );
S32		USB_Init( struct USBStruct *us );
void	USB_Free( struct USBStruct *us );
void	USB_Handle_Interface( struct USBStruct *us );

#endif
