
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

S32 Resources_Init( struct DockyBase *libBase UNUSED )
{
S32 retval;

	MYDEBUG( "Docky : Resources_Init" );

	retval = FALSE;

	// --

	NewlibBase = OpenLibrary( "newlib.library", 50 );
	INewlib = GetInterface( NewlibBase, "main", 1, NULL );

	if ( ! INewlib )
	{
		MYERROR( "Error opening Newlib library (v50)" );
		goto bailout;
	}

	// --

	DOSBase = OpenLibrary( "dos.library", 50 );
	IDOS = (PTR) GetInterface( (PTR) DOSBase, "main", 1, NULL );

	if ( ! IDOS )
	{
		MYERROR( "Error opening DOS library (v50)" );
		goto bailout;
	}

	// --

	UtilityBase = OpenLibrary( "utility.library", 50 );
	IUtility = (PTR) GetInterface( (PTR) UtilityBase, "main", 1, NULL );

	if ( ! IUtility )
	{
		MYERROR( "Error opening Utility library (v50)" );
		goto bailout;
	}

	// --




	// --

	retval = TRUE;

bailout:

	return( retval );
}

// --
