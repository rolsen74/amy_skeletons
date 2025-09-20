
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void Settings_Default( struct BlankerData *data )
{
U32 modeid;

	MYINFO( "Blanker : Settings_Default" );

	modeid = p96BestModeIDTags(
		P96BIDTAG_FormatsForbidden,	RGBFB_CLUT,
		P96BIDTAG_NominalWidth,		320,
		P96BIDTAG_NominalHeight,	240,
		P96BIDTAG_Depth,			16,
		TAG_END
	);

	data->bd_RefetchSettings = TRUE;
	data->bd_ScreenType	= SCRT_Custom;
	data->bd_ScreenMode	= modeid;
}

// --
