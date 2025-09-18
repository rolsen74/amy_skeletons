
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

	// struct Library *	    	dd_SocketBase;
	// struct SocketIFace *		dd_ISocket;

	struct DockySize				dd_DockySize;

	// int32						dd_RedrawDelay;

	// struct TextAttr				dd_SkillFont;
	// struct TextFont *			dd_SkillFontAdr;

	// uint64						dd_ReadBytes;
	// uint64						dd_SendBytes;

	// uint32						dd_Total[ myDocky_MeterWidth ];
	// uint64						dd_TotalMax;
	// uint64						dd_OldTotal;
	// uint32						dd_Diff;

	// int32						dd_Bank;
	// int32						dd_Index;
	// int32						dd_Delay;
	// CONST_STRPTR				dd_InterfaceName;

	// uint32						dd_SmallGfx;
	// uint32						dd_ShowCurrent;

	// uint32 *					dd_WorkBuffer;

	// uint64						dd_TimeBaseSpeed;
	// uint64						dd_prev_total_time;
	// uint64						dd_prev_idle_time;
	// struct ETask *				dd_idle_etask;
};

// --

#endif
