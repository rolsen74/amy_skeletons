
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _main_GetAttrsA( struct Test_USBFDIFace *Self UNUSED, struct TagItem *taglist UNUSED )
{
// struct LibBase *libBase;
// struct LibData *data;
U32 retval;

//	libBase = (PTR) Self->Data.LibBase;
//	data = (PTR) ( (U32) Self - Self->Data.NegativeSize );

	MYDEBUG( "USBFD : _main_GetAttrsA" );

	/* We don't support any tags - so we simply return */
	retval = 0;

	return( retval );
}

// --

U32 VARARGS68K _main_GetAttrs( struct Test_USBFDIFace *Self, ... )
{
va_list ap;
U32 retval;

	MYDEBUG( "USBFD : _main_GetAttrs" );

	va_startlinear( ap, Self );

	struct Test_USBFDIFace *ITest_USBFD = Self;
	retval = TESTLIB_GetAttrsA( va_getlinearva( ap, struct TagItem * ));

	va_end( ap );

	return( retval );
}

// --
