
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

#define myDocky_Width				320
#define myDocky_Height				96

// --

struct DockyBase
{
	struct Library					lib_Base;
	PTR								lib_SegList;
};

// --

struct DockyData
{
	U32								dd_Width;
	U32								dd_Height;
	struct RastPort *				dd_RenderRPort;
	struct Screen *					dd_Screen;
	struct DockySize				dd_DockySize;
};

// --

#endif
