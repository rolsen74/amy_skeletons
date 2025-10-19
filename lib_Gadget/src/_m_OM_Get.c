
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _m_OM_Get( Class *cl, Object *obj, struct opGet *msg )
{
// struct libBase *libBase;
struct GadData *data;
U32 *store;
U32 retval;

	MYINFO( "Gadget : _m_OM_Get" );

//	If you need too passe data, can get it this way
//	Set in Resources_Init/MakeClass
//	libBase = (PTR) cl->cl_UserData;

	data = INST_DATA( cl, obj );

	store = (PTR) msg->opg_Storage;

	retval = TRUE;

	switch( msg->opg_AttrID )
	{
		case TEST_GADGET_Optional:
		{
			*store = (U32) data->Optional;
			break;
		}

		default:
		{
			// Not our tag.. ask Super
			retval = IDoSuperMethodA( cl, obj, (Msg) msg );
			break;
		}
	}

	return(	retval );
}
