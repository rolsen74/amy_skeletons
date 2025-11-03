
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INC_PRIVATE_ALL_H
#error Include "inc_private/All.h" first
#endif

#ifndef INC_PRIVATE_RESOURCE_H
#define INC_PRIVATE_RESOURCE_H

// --

struct Real_ResourceBase
{
	// Public data
	struct Test_ResourceBase	res_Public;

	// Private data
	PTR							res_Dummy;
};

// --
// Library Interface Data

struct ResData
{
	U32					Dummy;
};

// --

#endif
