
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void Blanker_Render_Screen( struct BlankerData *data )
{
struct Screen *scr;
struct Window *win;
U32 modeid;
S32 w;
S32 h;

	MYDEBUG( "Blanker : Blanker_Render_Screen" );

	// --

	win = NULL;
	scr = NULL;

	modeid = INVALID_ID;

	// --
	// Get Screen ModeID

	/**/ if ( data->bd_ScreenType == SCRT_WBClone )
	{
		// Get WB Screen ModeID
	
		scr = LockPubScreen( "Workbench" );

		if ( scr )
		{
			modeid = GetVPModeID( & scr->ViewPort );

			if ( p96GetModeIDAttr( modeid, P96IDA_DEPTH ) <= 8 )
			{
				MYERROR( "Blanker : Invalid WB Screen Depth : Using fallback" );
				modeid = data->bd_ScreenMode;
			}

			UnlockPubScreen( NULL, scr );
		}
		else
		{
			MYERROR( "Blanker : Failed to lock WB Screen : Using fallback" );
			modeid = data->bd_ScreenMode;
		}
	}
	else if ( data->bd_ScreenType == SCRT_Custom )
	{
		// Use Custom Screen
		modeid = data->bd_ScreenMode;
	}
	else
	{
		MYERROR( "Blanker : Invalid ScreenType #%lu", data->bd_ScreenType );
		goto bailout;
	}

	if ( modeid == INVALID_ID )
	{
		MYERROR( "Blanker : Invalid ScreenMode ID $%08lx", modeid );
		goto bailout;
	}

	w = p96GetModeIDAttr( modeid, P96IDA_WIDTH );
	h = p96GetModeIDAttr( modeid, P96IDA_HEIGHT );

	// --
	// Open Screen

	scr = OpenScreenTags( NULL,
		SA_LikeWorkbench,	TRUE,
		SA_Overscan,		OSCAN_STANDARD,
		SA_Type,			CUSTOMSCREEN,
		SA_ShowTitle,		FALSE,
		SA_Left,			0,
		SA_Top,				0,
		SA_Width,			w,
		SA_Height,			h,
		SA_DisplayID,		modeid,
		SA_Quiet,			TRUE,
		TAG_END
	);

	if ( ! scr )
	{
		MYERROR( "Blanker : Failed to open Screen" );
		goto bailout;
	}

	// --
	// Open Window

	win = OpenWindowTags( NULL,
		WA_Activate,		TRUE,
		WA_Backdrop,		TRUE,
		WA_Borderless,		TRUE,
		WA_CloseGadget,		FALSE,
		WA_CustomScreen,	scr,
		WA_DepthGadget,		FALSE,
		WA_DragBar,			FALSE,
		WA_SizeGadget,		FALSE,
		WA_Title,			NULL,
		WA_Pointer,			data->bd_MouseObject,
		WA_Left,			0,
		WA_Top,				0,
		WA_Width,			w,
		WA_Height,			h,
		TAG_END
	);

	if ( ! win )
	{
		MYERROR( "Blanker : Failed to open Window" );
		goto bailout;
	}

	// --
	// Start Rendering
	Blanker_Render_Main( data, scr, win->RPort, w, h );

bailout:

	if ( win )
	{
		CloseWindow( win );
		win = NULL;
	}

	if ( scr )
	{
		CloseScreen( scr );
		scr = NULL;
	}
}

// --
