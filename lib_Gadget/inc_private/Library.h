
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
// ClassLibrary type needed for OpenClass()
// Library Base Data

struct LibBase
{
	struct ClassLibrary				lib_Base;
	PTR								lib_SegList;
};

// --
// Library Interface Data

struct LibData
{
	U32								bd_BlankingMode;
};

// --
// Gadget/Object Data

struct GadData
{
	PTR								needed_data;
	U32								Optional;
	PTR								SomeData;
	// --
	S32								GadXPos;
	S32								GadYPos;
	S32								GadWidth;
	S32								GadHeight;
	S32								Layout_Done;
	// --
	struct Region *					Region;
	S32								Region_Installed;
	struct RastPort *				RastPort;
};

// --

#endif
