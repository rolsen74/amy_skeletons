
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void Settings_Load( struct BlankerData *data, PrefsObject *dict )
{
U32 modeid;

	MYINFO( "Blanker : Settings_Load" );

	if ( ! dict )
	{
		MYERROR( "Settings_Load : NULL Pointer" );
		goto bailout;
	}

	// bd->Particle = IPrefsObjects->DictGetIntegerForKey( dict, "Particle", 8 );
	// Fix_Values( &bd->Particle, 1, 25 );

	// bd->Tale = IPrefsObjects->DictGetIntegerForKey( dict, "Tale", 8 );
	// Fix_Values( &bd->Tale, 1, 25 );

	data->bd_ScreenType = DictGetIntegerForKey( dict, "ScreenType", SCRT_WBClone );
	MYINFO( "Blanker : ScreenType #%lu", data->bd_ScreenType );

	modeid = p96BestModeIDTags(
		P96BIDTAG_FormatsForbidden, RGBFB_CLUT,
		P96BIDTAG_NominalWidth,		320,
		P96BIDTAG_NominalHeight,	240,
		P96BIDTAG_Depth,			16,
		TAG_END
	);
	MYINFO( "Blanker : modeid $%08lx", modeid );

	data->bd_ScreenMode = DictGetIntegerForKey( dict, "ScreenMode", modeid );
	MYINFO( "Blanker : bd_ScreenMode $%08lx", data->bd_ScreenMode );

bailout:

	return;
}

// --
