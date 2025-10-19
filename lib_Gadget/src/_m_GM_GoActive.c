
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _m_GM_GoActive( Class *cl, Object *obj, struct gpInput *msg )
{
// struct libBase *libBase;
struct GadData *data;
U32 retval;

	MYINFO( "Gadget : _m_GM_GoActive" );

//	If you need too passe data, can get it this way
//	Set in Resources_Init/MakeClass
//	libBase = (PTR) cl->cl_UserData;

	data = INST_DATA( cl, obj );

	// Mouse X/Y is offset Gadget Pos ( 0,0 -> W,H )
	if (( msg->gpi_Mouse.X < data->GadWidth ) && ( msg->gpi_Mouse.Y < data->GadHeight ))
	{
		retval = _m_GM_HandleInput( cl, obj, msg );
	}
	else
	{
		retval = GMR_NOREUSE;
	}

	return(	retval );
}
