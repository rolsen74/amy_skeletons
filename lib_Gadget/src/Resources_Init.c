
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
Class *c;
S32 retval;

	MYDEBUG( "Gadget : Resources_Init" );

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

	c = MakeClass(
		CLSNAME,
		"gadgetclass",		// This is the Parent/Root Class name
		NULL,
		sizeof( struct GadData ),
		0
	);

	if ( ! c )
	{
		MYERROR( "Gadget : Error creating gadget class" );
		goto bailout;
	}

	c->cl_Dispatcher.h_Entry = (PTR) _m_Dispatcher;
	c->cl_UserData = (U32) libBase;

	AddClass( c );
	libBase->lib_Base.cl_Class = c;

	// --

	retval = TRUE;

bailout:

	return( retval );
}

// --
