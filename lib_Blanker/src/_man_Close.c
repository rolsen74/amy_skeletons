
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

PTR _manager_Close( struct LibraryManagerInterface *Self )
{
struct BlankerBase *libBase;
PTR seglist;

	MYDEBUG( "Blanker : _manager_Close" );

	seglist = NULL;

	libBase = (PTR) Self->Data.LibBase;

	// Update Library open count
	if ( libBase->lib_Base.lib_OpenCnt )
	{
		libBase->lib_Base.lib_OpenCnt--;
	}

	// Check if we can expunge our self
	if ( ! libBase->lib_Base.lib_OpenCnt )
	{
		if ( libBase->lib_Base.lib_Flags & LIBF_DELEXP )
		{
			seglist = _manager_Expunge( Self );
		}
	}

	// Return NULL or SegList
	return( seglist );
}

// --
