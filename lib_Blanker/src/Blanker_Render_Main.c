
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

struct intern
{
	U32					Blanker_Running;
	U32					Blanker_CurMode;
	U32					Render_Active;
	struct Screen *		Render_Screen;
	struct RastPort *	Render_RP;
	S32					Render_W;
	S32					Render_H;
};

// --

static void __Wait( struct BlankerData *data, struct intern *in )
{
U32 wait;
U32 mask;

	// ahh my idea was too start a Timer process
	// that just keept sending Singals 1/50 frame or so

	// and then change this to a Wait() and avoid busy waiting
	// maybe full speed, where there is no waiting only Blanker signal check

	if ( TRUE )
	{
		// Full Speed - Check signal only

		wait = data->bd_BlankerRender->taskSigBreak;
		mask = CheckSignal( wait );

		if ( mask & data->bd_BlankerRender->taskSigBreak )
		{
			in->Blanker_Running = FALSE;
		}
	}
	else
	{
		// still too do
		// Wait for Signals

		wait = data->bd_BlankerRender->taskSigBreak;
//		wait |= Refresh Signal

		mask = Wait( wait );

		if ( mask & data->bd_BlankerRender->taskSigBreak )
		{
			in->Blanker_Running = FALSE;
		}

//		if ( mask & Refresh Signal )
//		{
//			// just return, do nothing here
//		}
	}
}

// --

static S32 __Init( struct BlankerData *data UNUSED, struct intern *in UNUSED )
{
S32 retval;

	MYDEBUG( "Blanker : __Init" );

	retval = FALSE;

	retval = TRUE;

//bailout:

	return( retval );
}

// --

static void __Free( struct BlankerData *data UNUSED, struct intern *in UNUSED )
{
	MYDEBUG( "Blanker : __Free" );

}

// --

static void __Render( struct BlankerData *data UNUSED, struct intern *in UNUSED )
{

}

// --

static void __SetBlankingMode( struct BlankerData *data, struct intern *in )
{
struct RastPort *rp;
struct Screen *scr;
U32 active;
U32 mode;
U32 lvl;

	MYDEBUG( "Blanker : __SetBlankingMode" );

	active = FALSE;
	mode = data->bd_BlankingMode;
	scr = in->Render_Screen;
	rp = in->Render_RP;

	switch ( mode )
	{
		case SBBM_Preview:
		case SBBM_Blanking:
		{
			if ( GetBitMapAttr( rp->BitMap, BMA_DEPTH ) > 8 )
			{
				active = TRUE;
			}

			lvl = DPMS_ON;
			break;
		}

		case SBBM_NoBlanking:
		{
			lvl = DPMS_ON;
			break;
		}

		case SBBM_DPMS_Standby:
		{
			lvl = DPMS_STANDBY;
			break;
		}

		case SBBM_DPMS_Suspend:
		{
			lvl = DPMS_SUSPEND;
			break;
		}

		case SBBM_DPMS_PowerOff:
		{
			lvl = DPMS_OFF;
			break;
		}

		default:
		{
			scr = NULL; // Don't set DPMSLevel
			MYERROR( "Unknown blanking mode #%lu", mode );
			break;
		}
	}

	if ( scr )
	{
		// ICyberGfx function
		CVideoCtrlTags( & scr->ViewPort,
			SETVC_DPMSLevel, lvl,
			TAG_END
		);
	}

	in->Blanker_CurMode = mode;
	in->Render_Active = active;
}

// --

static void __UpdateGfx( struct BlankerData *data, struct intern *in UNUSED )
{
	//
	// Update RastPort here
	//
	// Normaly we would just Blit Bitmap into Render_RP here
	// and do the rendering in __Render()
	//

	if ( data->bd_DoScreenSync )
	{
		WaitTOF();
	}

	if ( data->bd_BlankerRender->renderHook )
	{
		// Tells Preview we have updated Gfx
		CallHookPkt( data->bd_BlankerRender->renderHook, (PTR) BMRHM_FrameRendered, (PTR) 0 );
	}
}

// --

void Blanker_Render_Main( struct BlankerData *data, struct Screen *scr, struct RastPort *rp, S32 w, S32 h )
{
struct Task *Self;
struct intern in;
S32 oldpri;

	MYERROR( "Blanker_Render_Main : Enter" );

	memset( & in, 0, sizeof( in ));
	in.Blanker_CurMode = -1;		// -1 so we run at once
	in.Blanker_Running = TRUE;
	in.Render_Screen = scr;
	in.Render_RP = rp;
	in.Render_W = w;
	in.Render_H = h;

	Self	= FindTask( NULL );
	oldpri	= SetTaskPri( Self, -25 );

	// Outer loop
	while( in.Blanker_Running )
	{
		// Handle Current Settings

		__Free( data, & in );

		if ( ! __Init( data, & in ))
		{
			MYERROR( "Render : __Init() failed" );
			break;
		}

		// Clear Refetch
		data->bd_RefetchSettings = FALSE;

		// Inner loop
		while(( in.Blanker_Running ) && ( ! data->bd_RefetchSettings ))
		{
			if ( in.Blanker_CurMode != data->bd_BlankingMode )
			{
				__SetBlankingMode( data, & in );
			}

			if ( in.Render_Active )
			{
				__Render( data, & in );

				__UpdateGfx( data, & in );
			}

			__Wait( data, & in );
		}
	}

	SetTaskPri( Self, oldpri );

	__Free( data, & in );

	MYERROR( "Blanker_Render_Main : Leave" );
}

// --
