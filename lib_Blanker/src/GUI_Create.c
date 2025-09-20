
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

static const struct Hook GUI_Event_Hook = {{ NULL, NULL }, (HOOKFUNC) GUI_Event_Func, NULL, NULL };
static const struct Hook GUI_IDCMP_Hook = {{ NULL, NULL }, (HOOKFUNC) GUI_IDCMP_Func, NULL, NULL };

static const STR ScreenTypes[SCRT_Last+1] = 
{
	[SCRT_Custom]	= "Custom Screen",
	[SCRT_WBClone]	= "Clone WB Screen",
	[SCRT_Last]		= NULL,
};

S32 GUI_Create( struct BlankerData *data, struct BlankerPrefsWindowSetup *bpws )
{
S32 retval;

	MYINFO( "Blanker : GUI_Create" );

	retval = FALSE;

	if ( ! bpws )
	{
		MYERROR( "GUI_Create : NULL Pointer" );
		goto bailout;
	}

	bpws->winWidth		= 400;
	bpws->winHeight		= 100;
	bpws->eventHook		= (PTR) & GUI_Event_Hook;
	bpws->idcmpHook		= (PTR) & GUI_IDCMP_Hook;
	bpws->idcmpHookBits = IDCMP_IDCMPUPDATE;

	bpws->rootLayout	= (PTR) NewObject( LayoutClass, NULL,
		LAYOUT_Orientation, 		LAYOUT_ORIENT_VERT,
			
		LAYOUT_AddChild,			data->Gad_Slider = NewObject( SliderClass, NULL,
			GA_ID,					GID_Slider,
			GA_RelVerify,			TRUE,
			SLIDER_Orientation,		SLIDER_HORIZONTAL,
			SLIDER_Min,				1,
			SLIDER_Max,				100,
			SLIDER_Level,			20,
			SLIDER_LevelFormat,		"%ld     ",
			ICA_TARGET,				ICTARGET_IDCMP,
			TAG_END
		),
		CHILD_Label,				NewObject( LabelClass, NULL,
			LABEL_Text,				"Balls",
			TAG_END
		),

		LAYOUT_AddChild,			NewObject( SpaceClass, NULL,
			TAG_END
		),
		CHILD_MinHeight,			5,
		CHILD_MaxHeight,			5,

		LAYOUT_AddChild,			data->Gad_ScreenType = NewObject( ChooserClass, NULL,
			GA_ID,					GID_ScreenType,
			GA_RelVerify,			TRUE,
			CHOOSER_LabelArray,		ScreenTypes,
			CHOOSER_Selected,		0,
			CHOOSER_Justification,	CHJ_CENTER,
			TAG_END
		),
		CHILD_Label,				NewObject( LabelClass, NULL,
			LABEL_Text,				"Screen Type",
			TAG_END
		),

		LAYOUT_AddChild,			data->Gad_ScreenMode = NewObject( ButtonClass, NULL,
			GA_Disabled,			( data->bd_ScreenType == SCRT_Custom ) ? FALSE : TRUE,
			GA_ID,					GID_ScreenMode,
			GA_RelVerify,			TRUE,
			GA_Text,				"800x600x8",
			TAG_END
		),
		CHILD_Label,				NewObject( LabelClass, NULL,
			LABEL_Text,				"Screenmode",
			TAG_END
		),
		TAG_END
	);

	retval = TRUE;

bailout:

	return( retval );
}

// --
