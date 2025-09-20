
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

S32 Blanker_Init( struct BlankerData *data UNUSED )
{
S32 retval;

	retval = FALSE;

	//
	// Alloc/Init Blanker data here
	//
	// jump too bailout on error
	//
	// Blanker_Free() will always be called
	// so free your data there
	//

	retval = TRUE;

//bailout:

	return( retval );
}

// --
