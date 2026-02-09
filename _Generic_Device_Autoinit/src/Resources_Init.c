
/*
** SPDX-License-Identifier: Unlicense
** Written 2026 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

S32 Resources_Init( struct DEVBase *devBase UNUSED )
{
S32 retval;

	MYDEBUG( "Device : Resources_Init" );

	retval = FALSE;

	// --
	// Open Resources first
	//
	if ( ! myOpenResources( INT_MAX ))
	{
		MYERROR( "Library : myOpenResources() failed" );
		goto bailout;
	}

	// --

	InitSemaphore( & devBase->dev_DEV_Semaphore );

	// --

	retval = TRUE;

bailout:

	return( retval );
}

// --
