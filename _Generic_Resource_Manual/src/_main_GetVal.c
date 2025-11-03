
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _main_GetVal( struct Test_ResourceIFace *Self UNUSED )
{
//struct Real_ResourceBase *resBase;

	MYDEBUG( "Resource : _main_GetVal" );

//	resBase = (PTR) Self->Data.LibBase;

	return( 0xacdc );
}

// --
