
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _m_OM_Dispose( Class *cl, Object *obj, struct opSet *msg )
{
// struct libBase *libBase;
struct GadData *data;
U32 retval;

	MYINFO( "Gadget : _m_OM_Dispose" );

// 	libBase	= (struct libBase *) cl->cl_UserData;
	data	= INST_DATA( cl, obj );

	if ( data->SomeData )
	{
		FreeVec( data->SomeData );
		data->SomeData = NULL;
	}

	if ( data->Region )
	{
		DisposeRegion( data->Region );
		data->Region = NULL;
	}

	// Let Parent free its own data
	retval = IDoSuperMethodA( cl, obj, (PTR) msg );

	return(	retval );
}
