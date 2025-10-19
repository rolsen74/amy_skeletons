
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

Class *_main_GetClass( struct Test_GadgetIFace *Self )
{
struct LibBase *libBase;

	libBase = (PTR) Self->Data.LibBase;

	return( libBase->lib_Base.cl_Class );
}

// --
