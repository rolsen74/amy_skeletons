
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

PTR _manager_Expunge( struct LibraryManagerInterface *Self )
{
struct BlankerBase *libBase;
PTR seglist;

	MYDEBUG( "Blanker : _manager_Expunge" );

	libBase = (PTR) Self->Data.LibBase;

	#if 0

	/*
	** Looks like the Expunge() is broken in screenblanker.lib
	** My version is very old v53.6 (12-Dec-2012)
	**
	** If its fixed we can add a version check later
	*/

	if ( ! libBase->lib_Base.lib_OpenCnt )
	{
		seglist = libBase->lib_SegList;

		Resources_Free( libBase );

		Remove( (PTR) libBase );

		DeleteLibrary( (PTR) libBase );
		libBase = NULL;
	}
	else
	#endif
	{
		libBase->lib_Base.lib_Flags |= LIBF_DELEXP;
		seglist = NULL;
	}

	// Return NULL or SegList
	return( seglist );
}

// --
