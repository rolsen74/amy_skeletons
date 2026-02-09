
/*
** SPDX-License-Identifier: Unlicense
** Written 2026 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _manager_Release( struct DeviceManagerInterface *Self )
{
	Self->Data.RefCount--;

	return( Self->Data.RefCount );
}

// --
