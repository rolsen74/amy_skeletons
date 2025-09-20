
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

enum
{
	GID_ScreenType = 0x1000,		// WBClone / Custom
	GID_ScreenMode,
	GID_Slider,						// Slider is just a test example
};

// --

struct BlankerBase
{
	struct Library					lib_Base;
	PTR								lib_SegList;
};

// --

enum ScreenType
{
	SCRT_Custom,
	SCRT_WBClone,
	SCRT_Last
};

struct BlankerData
{
	struct BlankerRender *			bd_BlankerRender;
	U32								bd_BlankingMode;
	U32								bd_ScreenMode;
	enum ScreenType					bd_ScreenType;
	U32								bd_SliderValue;
	U32								bd_RefetchSettings;
	U32								bd_DoScreenSync;
	struct BlankerPrefsWindowInfo	bd_WinInfo;
	struct ScreenModeRequester *	bd_ScreenModeRequester;
	Object *						bd_MouseObject;
	// ---
	Object *						Gad_ScreenType;
	Object *						Gad_ScreenMode;
	Object *						Gad_Slider;
};

// --

#endif
