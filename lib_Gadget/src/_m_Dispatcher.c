
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _m_Dispatcher( Class *cl, Object *obj, Msg msg )
{
// struct libBase *libBase;
U32 retval;

//	If you need too passe data, can get it this way
//	Set in Resources_Init/MakeClass
//	libBase = (PTR) cl->cl_UserData;

	MYINFO( "Gadget : MethodID : %08lx", msg->MethodID );

	switch( msg->MethodID )
	{
		/* BOOPSI methods */
		case OM_NEW:			retval = _m_OM_New(			cl, obj, (PTR) msg );	break;
		case OM_DISPOSE:		retval = _m_OM_Dispose(		cl, obj, (PTR) msg );	break;
		case OM_GET:			retval = _m_OM_Get(			cl, obj, (PTR) msg );	break;
		case OM_SET:			retval = _m_OM_Set(			cl, obj, (PTR) msg );	break;
		case OM_UPDATE:			retval = _m_OM_Update(		cl, obj, (PTR) msg );	break;

		/* Gadgets Methods */
		case GM_DOMAIN:			retval = _m_GM_Domain(		cl, obj, (PTR) msg );	break;
		case GM_LAYOUT:			retval = _m_GM_Layout(		cl, obj, (PTR) msg );	break;
		case GM_CLIPRECT:		retval = _m_GM_ClipRect(	cl, obj, (PTR) msg );	break;
		case GM_EXTENT:			retval = _m_GM_Extent(		cl, obj, (PTR) msg );	break;
		case GM_HITTEST:		retval = _m_GM_HitTest(		cl, obj, (PTR) msg );	break;
		case GM_GOACTIVE:		retval = _m_GM_GoActive(	cl, obj, (PTR) msg );	break;
		case GM_HANDLEINPUT:	retval = _m_GM_HandleInput(	cl, obj, (PTR) msg );	break;
		case GM_GOINACTIVE:		retval = _m_GM_GoInactive(	cl, obj, (PTR) msg );	break;
		case GM_RENDER:			retval = _m_GM_Render(		cl, obj, (PTR) msg );	break;
		case GM_QUERY:			retval = _m_GM_Query( 		cl, obj, (PTR) msg );	break;

		/* Custom Methods */
		// case SIMPLELISTM_Clear:		retval = SL_SIMPLELISTM_Clear(		cl, obj, (PTR) msg );	break;

		/* Unknown method -> delegate to SuperClass */
		default:				retval = IDoSuperMethodA( cl, obj, (PTR) msg ); break;
	}

	return( retval );
}
