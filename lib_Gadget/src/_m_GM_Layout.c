
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _m_GM_Layout( Class *cl, Object *obj, struct gpLayout *msg UNUSED )
{
// struct libBase *libBase;
struct GadData *data;
struct Gadget *gad;

	MYINFO( "Gadget : _m_GM_Layout" );

//	If you need too passe data, can get it this way
//	Set in Resources_Init/MakeClass
//	libBase = (PTR) cl->cl_UserData;

	data = INST_DATA( cl, obj );

	gad = (PTR) obj;

	// --

	data->GadXPos	= gad->LeftEdge;
	data->GadYPos	= gad->TopEdge;
	data->GadWidth	= gad->Width;
	data->GadHeight	= gad->Height;
	data->Layout_Done = TRUE;

	// --

	return( TRUE );
}
