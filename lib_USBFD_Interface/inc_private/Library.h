
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INC_PRIVATE_ALL_H
#error Include "inc_private/All.h" first
#endif

#ifndef INC_PRIVATE_LIBRARY_H
#define INC_PRIVATE_LIBRARY_H

// --
// Library Base .. is global data shared by all opening the library

struct LibBase
{
	struct Library		lib_Base;
	PTR					lib_SegList;
	PTR					lib_fdkey;
};

// --

struct LibData
{
	int		Dummy;
};

// --

#endif
