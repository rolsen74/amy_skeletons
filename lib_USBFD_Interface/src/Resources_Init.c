
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

S32 Resources_Init( struct LibBase *libBase )
{
S32 retval;
S32 err;

	MYDEBUG( "USBFD : Resources_Init" );

	retval = FALSE;

	// --
	// Open Resources first
	//
	if ( ! myOpenResources( INT_MAX ))
	{
		MYERROR( "USBFD : myOpenResources() failed" );
		goto bailout;
	}

	// --

	err = 0;

	libBase->lib_fdkey = USBResRegisterFD(
		USBA_FD_InterfaceDriver, TRUE,
		USBA_FD_Title,	VSTRING,
		USBA_FD_Name,	LIBNAME,
		USBA_ErrorCode,	& err,
		USBA_Subclass,	0x01, // Boot protocol
		USBA_Class,		USBCLASS_HID,
		TAG_END
	);

	if (( ! libBase->lib_fdkey ) && ( err != USBERR_ISPRESENT ))
	{
		MYERROR( "USBFD : Failed to register USB Driver : fdkey %p : Err %ld", libBase->lib_fdkey, err );
		goto bailout;
	}

	// --

	retval = TRUE;

bailout:

	return( retval );
}

// --
