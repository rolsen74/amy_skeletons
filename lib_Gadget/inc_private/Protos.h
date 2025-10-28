
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
U32 _main_Obtain( struct Test_GadgetIFace *Self );
U32 _main_Release( struct Test_GadgetIFace *Self );
Class *_main_GetClass( struct Test_GadgetIFace *Self );

// --
// Gadget Resources Functions
S32 Resources_Init( struct LibBase *devBase );
void Resources_Free( struct LibBase *devBase );
S32 myOpenResources( void );
void myCloseResources( void );

// --
// BOOPSI Methods
U32 _m_Dispatcher( Class *cl, Object *obj, Msg msg );
U32 _m_OM_New( Class *cl, Object *obj, struct opSet *msg );
U32 _m_OM_Dispose( Class *cl, Object *obj, struct opSet *msg );
U32 _m_OM_Get( Class *cl, Object *obj, struct opGet *msg );
U32 _m_OM_Set( Class *cl, Object *obj, struct opSet *msg );
U32 _m_OM_Update( Class *cl, Object *obj, struct opSet *msg );
U32 _m_GM_Domain( Class *cl, Object *obj, struct gpDomain *msg );
U32 _m_GM_Layout( Class *cl, Object *obj, struct gpLayout *msg );
U32 _m_GM_ClipRect( Class *cl, Object *obj, struct gpClipRect *msg );
U32 _m_GM_Extent( Class *cl, Object *obj, struct gpExtent *msg );
U32 _m_GM_HitTest( Class *cl, Object *obj, struct gpHitTest *msg );
U32 _m_GM_GoActive( Class *cl, Object *obj, struct gpInput *msg );
U32 _m_GM_GoInactive( Class *cl, Object *obj, struct gpGoInactive *msg );
U32 _m_GM_HandleInput( Class *cl, Object *obj, struct gpInput *msg );
U32 _m_GM_Render( Class *cl, Object *obj, struct gpRender *msg );
U32 _m_GM_Query( Class *cl, Object *obj, struct gpQuery *msg );

#endif
