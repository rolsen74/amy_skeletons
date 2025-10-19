
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _m_GM_Domain( Class *cl UNUSED, Object *obj UNUSED, struct gpDomain *msg )
{
// struct libBase *libBase;
// struct GadData *data;
U32 retval;

	MYINFO( "Gadget : _m_GM_Domain" );

//	If you need too passe data, can get it this way
//	Set in Resources_Init/MakeClass
//	libBase = (PTR) cl->cl_UserData;

	retval = TRUE;

//	data = INST_DATA( cl, obj );

	switch( msg->gpd_Which )
	{
		case GDOMAIN_MINIMUM:
		case GDOMAIN_NOMINAL:
		{
			msg->gpd_Domain.Width	= 100;
			msg->gpd_Domain.Height	= 100;
			break;
		}

		case GDOMAIN_MAXIMUM:
		{
			msg->gpd_Domain.Width   = 16384;
			msg->gpd_Domain.Height  = 16384;
			break;
		}

		default:
		{
			retval = FALSE;
			break;
		}
	}

	return(	retval );
}
