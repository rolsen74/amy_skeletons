
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void GUI_Refresh( struct BlankerData *data )
{
struct Window *win;
char buf[32];

	MYINFO( "Blanker : GUI_Refresh" );

	win = data->bd_WinInfo.window;

//	RefreshSetGadgetAttrs( (PTR) data->Gad_Speed, data->bd_WinInfo.window, NULL,
//		SLIDER_Level, data->bd_Speed,
//		TAG_END
//	);

	RefreshSetGadgetAttrs( (PTR) data->Gad_ScreenType, data->bd_WinInfo.window, NULL,
		CHOOSER_Selected, data->bd_ScreenType,
		TAG_END
	);

	snprintf( buf, 32, "%lux%lux%lu",
		p96GetModeIDAttr( data->bd_ScreenMode, P96IDA_WIDTH ),
		p96GetModeIDAttr( data->bd_ScreenMode, P96IDA_HEIGHT ),
		p96GetModeIDAttr( data->bd_ScreenMode, P96IDA_DEPTH )
	);

	RefreshSetGadgetAttrs( (PTR) data->Gad_ScreenMode, win, NULL,
		GA_Disabled, ( data->bd_ScreenType == SCRT_Custom ) ? FALSE : TRUE,
		GA_Text, buf,
		TAG_END
	);

}

// --
