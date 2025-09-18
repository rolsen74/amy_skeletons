
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

PTR _manager_Expunge( struct DeviceManagerInterface *Self )
{
struct PrinterBase *devBase;
PTR seglist;

	MYDEBUG( "Printer : _manager_Expunge" );

	devBase = (PTR) Self->Data.LibBase;

	if ( ! devBase->dev_Base.dd_Library.lib_OpenCnt )
	{
		seglist = devBase->dev_SegList;

		Resources_Free( devBase );

		Remove( (PTR) devBase );

		DeleteLibrary( (PTR) devBase );
		devBase = NULL;
	}
	else
	{
		devBase->dev_Base.dd_Library.lib_Flags |= LIBF_DELEXP;
		seglist = NULL;
	}

	// Return NULL or SegList
	return( seglist );
}

// --
