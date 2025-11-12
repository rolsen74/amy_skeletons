
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

S32 Resources_Init( struct SANA2Base *devBase UNUSED )
{
S32 retval;

	MYDEBUG( "SANA2 : Resources_Init" );

	retval = FALSE;

	// --
	// We do not need any Timer IO, 
	// we only need to access the Interface

	TimerBase = (PTR) FindName( & ((struct ExecBase *)SysBase)->DeviceList, "timer.device" );

	if ( ! TimerBase )
	{
		MYERROR( "Failed to get Timer Base" );
		goto bailout;
	}

	// --
	// Open Resources first
	//
	if ( ! myOpenResources( INT_MAX ))
	{
		MYERROR( "Library : myOpenResources() failed" );
		goto bailout;
	}

	// --

	InitSemaphore( & devBase->dev_SANA2_Semaphore );

	// --

	retval = TRUE;

bailout:

	return( retval );
}

// --
