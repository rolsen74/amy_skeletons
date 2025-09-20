
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void Settings_Save( struct BlankerData *data, PrefsObject *dict )
{
PrefsObject *o;

	MYINFO( "Blanker : Settings_Save" );

	if ( ! dict )
	{
		MYERROR( "Settings_Save : NULL Pointer" );
		goto bailout;
	}

	o = PrefsNumber( NULL, NULL, ALPONUM_AllocSetLong, data->bd_ScreenType, TAG_END );
	DictSetObjectForKey( dict, o, "ScreenType" );
	MYINFO( "Blanker : ScreenType #%lu", data->bd_ScreenType );

	o = PrefsNumber( NULL, NULL, ALPONUM_AllocSetLong, data->bd_ScreenMode, TAG_END );
	DictSetObjectForKey( dict, o, "ScreenMode" );
	MYINFO( "Blanker : bd_ScreenMode $%08lx", data->bd_ScreenMode );

bailout:

	return;
}

// --
