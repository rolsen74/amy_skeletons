
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
// Blanker Interface
U32 _blanker_Obtain( struct BlankerModuleIFace *Self );
U32 _blanker_Release( struct BlankerModuleIFace *Self );
U32	_blanker_Expunge( struct BlankerModuleIFace *Self );
PTR _blanker_Clone( struct BlankerModuleIFace *Self );
BOOL _blanker_Get( struct BlankerModuleIFace *Self, U32 msgType, U32 *msgData );
BOOL _blanker_Set( struct BlankerModuleIFace *Self, U32 msgType, U32 msgData );
void _blanker_Blank( struct BlankerModuleIFace *Self );

// --
// Device Resources Functions
S32 Resources_Init( struct BlankerBase *devBase );
void Resources_Free( struct BlankerBase *devBase );
S32 myOpenResources( int max_libs );
void myCloseResources( void );

// -- Blanker
S32 Blanker_Init( struct BlankerData *data );
void Blanker_Free( struct BlankerData *data );
void Blanker_Render_Main( struct BlankerData *data, struct Screen *scr, struct RastPort *rp, S32 w, S32 h );
void Blanker_Render_Preview( struct BlankerData *data );
void Blanker_Render_Screen( struct BlankerData *data );

// --
// GUI
S32 GUI_Create( struct BlankerData *data, struct BlankerPrefsWindowSetup *bpws );
U32 GUI_Event_Func( struct Hook *hook, struct BlankerModuleIFace *Self, struct BlankerPrefsWinGUIEvent *event );
U32 GUI_IDCMP_Func( struct Hook *hook, struct BlankerModuleIFace *Self, struct BlankerPrefsWinIDCMPEvent *event );
void GUI_Refresh( struct BlankerData *data );

// --
// Misc
void Settings_Default( struct BlankerData *data );
void Settings_Load( struct BlankerData *data, PrefsObject *dict );
void Settings_Save( struct BlankerData *data, PrefsObject *dict );

#endif
