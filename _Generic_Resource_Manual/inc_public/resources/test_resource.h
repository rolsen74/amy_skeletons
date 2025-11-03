
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef RESOURCES_TEST_RESOURCE_H
#define RESOURCES_TEST_RESOURCE_H

// --

#include <proto/exec.h>

// --

struct Test_ResourceBase
{
	// -- 
	// Public data
	struct Library		res_Base;

	// -- 
	// Private data
	// see inc_Private/Resource.h
};

// --

#endif
