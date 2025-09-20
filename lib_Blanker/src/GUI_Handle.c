
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 GUI_Event_Func( struct Hook *hook UNUSED, struct BlankerModuleIFace *Self, struct BlankerPrefsWinGUIEvent *event )
{
struct BlankerData *data;
U32 GadgetID;
S32 retval;
char buf[32];

	if (( ! Self ) || ( ! event ))
	{
		MYERROR( "GUI_Event_Func : NULL Pointer" );
		goto bailout;
	}

	data = (PTR) ( (U32) Self - Self->Data.NegativeSize );

//
//	attr = 0;
//
//	refetch = data->refetchSettings;

	GadgetID = event->result & WMHI_GADGETMASK;

	switch( GadgetID )
	{
//		case GA_Style:
//		{
//			IIntuition->GetAttr(CHOOSER_Selected, style_chooser, &attr);
//			data->style = attr;
//			refetch |= TRUE;
//			break;
//		}

		case GID_ScreenType:
		{
			GetAttrs( data->Gad_ScreenType, 
				CHOOSER_Selected, & data->bd_ScreenType,
				TAG_END
			);

			RefreshSetGadgetAttrs( (PTR) data->Gad_ScreenMode, data->bd_WinInfo.window, NULL,
				GA_Disabled, ( data->bd_ScreenType == SCRT_Custom ) ? FALSE : TRUE,
				TAG_END
			);

			data->bd_RefetchSettings = TRUE;
			break;
		}

		case GID_ScreenMode:
		{
			SetAttrs( data->bd_WinInfo.object,
				WA_BusyPointer, TRUE,
				TAG_END
			);

			retval = AslRequestTags( data->bd_ScreenModeRequester,
				ASLSM_InitialDisplayID, data->bd_ScreenMode,
				ASLSM_MinDepth, 15,
				ASLSM_MaxDepth, 32,
				TAG_END
			);

			if ( retval )
			{
				data->bd_ScreenMode = data->bd_ScreenModeRequester->sm_DisplayID;

 				snprintf( buf, 32, "%ldx%ldx%ld",
					data->bd_ScreenModeRequester->sm_DisplayWidth,
					data->bd_ScreenModeRequester->sm_DisplayHeight,
					p96GetModeIDAttr( data->bd_ScreenMode, P96IDA_DEPTH )
				);

				SetAttrs( data->Gad_ScreenMode,
					GA_Text, buf,
					TAG_END
				);

				RefreshGList( (PTR) data->Gad_ScreenMode, data->bd_WinInfo.window, NULL, 0 );
			}

			SetAttrs( data->bd_WinInfo.object,
				WA_BusyPointer, FALSE,
				TAG_END
			);
			break;
		}

		default:
		{
			if ( GadgetID )
			{
				MYINFO( "Blanker : GUI_Event_Func : Unknown GadgetID $%04lx", GadgetID );
			}
			break;
		}
	}

bailout:

	return( 0 );
}

// --

U32 GUI_IDCMP_Func( struct Hook *hook UNUSED, struct BlankerModuleIFace *Self, struct BlankerPrefsWinIDCMPEvent *event )
{
struct BlankerData *data;
struct TagItem *tags;
struct TagItem *tag;
U32 Found;
U32 GID;

	if (( ! Self ) || ( ! event ))
	{
		MYERROR( "GUI_IDCMP_Func : NULL Pointer" );
		goto bailout;
	}

	if ( event->msg->Class == IDCMP_IDCMPUPDATE )
	{
		goto bailout;
	}

	data	= (PTR) ( (U32) Self - Self->Data.NegativeSize );
	tags	= (PTR) event->msg->IAddress;
	Found	= FALSE;
	GID		= 0;

	while(( ! GID ) && ( ! Found ))
	{
		tag = NextTagItem( & tags );

		if ( ! tag )
		{
			break;
		}

		switch( tag->ti_Tag )
		{
			case SLIDER_Level:
			{
				Found = TRUE;
				break;
			}

			case GA_ID:
			{
				GID = tag->ti_Data;
				break;
			}

			default:
			{
				break;
			}
		}
	}

	if (( Found ) && ( GID ))
	{
		switch( GID )
		{
			case GID_Slider:
			{
				GetAttrs( data->Gad_Slider,
					SLIDER_Level, & data->bd_SliderValue,
					TAG_END
				 );

				data->bd_RefetchSettings = TRUE;
				break;
			}

			default:
			{
				MYINFO( "Blanker : GUI_IDCMP_Func : Unknown GadgetID #%lu", GID );
				break;
			}
		}
	}

bailout:

	return( 0 );
}

// --
