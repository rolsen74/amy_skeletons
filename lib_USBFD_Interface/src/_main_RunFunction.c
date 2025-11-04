
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

S32 _main_RunFunction( struct Test_USBFDIFace *Self UNUSED, struct USBFDStartupMsg *msg UNUSED )
{
// struct LibBase *libBase;
// struct LibData *data;
S32 retval;

//	libBase = (PTR) Self->Data.LibBase;
//	data = (PTR) ( (U32) Self - Self->Data.NegativeSize );

	MYDEBUG( "USBFD : _main_RunFunction" );

	retval = USBERR_UNSUPPORTED;

	MYDEBUG( "USBFD : _main_RunFunction : Return %ld", retval );

	return( retval );
}

// --
