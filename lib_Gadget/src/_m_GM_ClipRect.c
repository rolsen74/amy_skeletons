
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _m_GM_ClipRect( Class *cl, Object *obj, struct gpClipRect *msg )
{
// struct libBase *libBase;
struct GadData *data;

	MYINFO( "Gadget : _m_GM_ClipRect" );

//	If you need too passe data, can get it this way
//	Set in Resources_Init/MakeClass
//	libBase = (PTR) cl->cl_UserData;

	data = INST_DATA( cl, obj );

	ClearRegion( data->Region );
	data->Region_Installed = FALSE;

	if ( msg->gpc_ClipRect )
	{
		data->Region_Installed = TRUE;
		OrRectRegion( data->Region, msg->gpc_ClipRect );
	}

	return(	GMC_VISIBLE );
}
