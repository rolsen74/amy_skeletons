
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _blanker_Obtain( struct BlankerModuleIFace *Self )
{
	MYDEBUG( "Blanker : _blanker_Obtain" );

	Self->Data.RefCount++;

	return( Self->Data.RefCount );
}

// --
