
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

S32 Resources_Init( struct Real_ResourceBase *resBase UNUSED )
{
S32 retval;

	MYDEBUG( "Resource : Resources_Init" );

	retval = FALSE;

	// --
	// Open Resources first

	if ( ! myOpenResources() )
	{
		MYERROR( "Resource : myOpenResources() failed" );
		goto bailout;
	}

	// --

	// Alloc resources here

	// --

	retval = TRUE;

bailout:

	return( retval );
}

// --
