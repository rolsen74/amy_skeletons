
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _m_GM_Render( Class *cl, Object *obj, struct gpRender *msg )
{
struct RastPort *rp;
struct GadData *data;
struct Region *oldRegion;
U32 retval;

	MYINFO( "Gadget : _m_GM_Render" );

	data = INST_DATA( cl, obj );

	retval = FALSE;

	oldRegion = NULL;

	// --

	rp = msg->gpr_RPort;

	if ( ! rp )
	{
		goto bailout;
	}

	data->RastPort	= rp;

	// --

	if (( data->Region_Installed ) && ( rp->Layer ))
	{
		oldRegion = InstallClipRegion( rp->Layer, data->Region );
	}

//	myDrawAll( libBase, data );

	if (( data->Region_Installed ) && ( rp->Layer ))
	{
		InstallClipRegion( rp->Layer, oldRegion );
	}

	// --

	data->RastPort = NULL;

	retval = TRUE;

bailout:

	return(	retval );
}
