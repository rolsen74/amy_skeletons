
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

extern struct Interface *INewlib;
extern struct Library *NewlibBase;

void Resources_Free( struct PrinterBase *devBase UNUSED )
{
	MYDEBUG( "Printer : Resources_Free" );

	// --



	// --

	if ( IUtility )
	{	
		DropInterface( (PTR) IUtility );
	}

	if ( UtilityBase )
	{
		CloseLibrary( (PTR) UtilityBase );
	}

	// --

	if ( IDOS )
	{	
		DropInterface( (PTR) IDOS );
	}

	if ( DOSBase )
	{
		CloseLibrary( (PTR) DOSBase );
	}

	// --

	if ( INewlib )
	{	
		DropInterface( INewlib );
	}

	if ( NewlibBase )
	{
		CloseLibrary( NewlibBase );
	}

	// --
}

// --
