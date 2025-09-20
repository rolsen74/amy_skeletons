
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

S32 Resources_Init( struct BlankerBase *libBase UNUSED )
{
S32 retval;

	MYDEBUG( "Blanker : Resources_Init" );

	retval = FALSE;

	// --
	// Open Resources first

	if ( ! myOpenResources() )
	{
		MYERROR( "myOpenResources() failed" );
		goto bailout;
	}

	// --



	// --

	retval = TRUE;

bailout:

	return( retval );
}

// --
