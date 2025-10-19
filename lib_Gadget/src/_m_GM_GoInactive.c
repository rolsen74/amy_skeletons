
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _m_GM_GoInactive( Class *cl, Object *obj, struct gpGoInactive *msg )
{
U32 retval;

	// --

	MYINFO( "Gadget : _m_GM_GoInactive" );

	retval = IDoSuperMethodA( cl, obj, (PTR) msg );

	// --

	return(	retval );
}
