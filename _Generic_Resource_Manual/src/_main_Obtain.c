
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _main_Obtain( struct Test_ResourceIFace *Self )
{
	MYDEBUG( "Resource : _main_Obtain" );

	Self->Data.RefCount++;

	return( Self->Data.RefCount );
}

// --
