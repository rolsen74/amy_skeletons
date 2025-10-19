
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _m_GM_HitTest( Class *cl UNUSED, Object *obj UNUSED, struct gpHitTest *msg UNUSED )
{
	MYINFO( "Gadget : _m_GM_HitTest" );

	return( GMR_GADGETHIT );
}
