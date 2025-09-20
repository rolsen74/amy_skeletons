
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

BOOL _blanker_Set( struct BlankerModuleIFace *Self, U32 msgType, U32 msgData )
{
//struct BlankerBase *libBase;
struct BlankerData *data;
BOOL retval;

//	libBase = (PTR) Self->Data.LibBase;
	data = (PTR) ( (U32) Self - Self->Data.NegativeSize );

	retval = TRUE;

	switch( msgType )
	{
		case BMSET_BlankerRender:
		{
			MYINFO( "Blanker : BMSET_BlankerRender" );

			data->bd_BlankerRender = (PTR) msgData;
			break;
		}

		case BMSET_BlankingMode:
		{
			switch( msgData )
			{
				case SBBM_NoBlanking:
				case SBBM_Preview:
				case SBBM_Blanking:
				case SBBM_DPMS_Standby:
				case SBBM_DPMS_Suspend:
				case SBBM_DPMS_PowerOff:
				{
					MYINFO( "Blanker : BMSET_BlankingMode : Mode %ld", msgData );
					data->bd_BlankingMode = msgData;
					retval = TRUE;
					break;
				}

				default:
				{
					MYERROR( "BMSET_BlankingMode : Unsupported Mode %ld", msgData );
					retval = FALSE;
					break;
				}
			}
			break;
		}

		case BMSET_OpenPrefsWindow:
		{
			MYINFO( "Blanker : BMSET_OpenPrefsWindow" );

			retval = GUI_Create( data, (PTR) msgData );

			if ( retval )
			{
				GUI_Refresh( data );
			}
			break;
		}

		case BMSET_ClosePrefsWindow:
		{
			MYINFO( "Blanker : BMSET_ClosePrefsWindow" );

			memset( & data->bd_WinInfo, 0, sizeof( data->bd_WinInfo ));
			data->Gad_ScreenType	= NULL;
			data->Gad_ScreenMode	= NULL;
			data->Gad_Slider		= NULL;
			break;
		}

		case BMSET_PrefsWindowInfo:
		{
			MYINFO( "Blanker : BMSET_PrefsWindowInfo" );

			data->bd_WinInfo = *((struct BlankerPrefsWindowInfo *)msgData);
			break;
		}

		case BMSET_Preferences:
		{
			MYINFO( "Blanker : BMSET_Preferences" );

			Settings_Load( data, (PTR) msgData );
			GUI_Refresh( data );

			data->bd_RefetchSettings = TRUE;
			break;
		}

		case BMSET_UseDefaultSettings:
		{
			MYINFO( "Blanker : BMSET_UseDefaultSettings" );

			Settings_Default( data );
			GUI_Refresh( data );

			data->bd_RefetchSettings = TRUE;
			break;
		}

		default:
		{
			MYINFO( "Blanker : Unsupported DOCKYSET (%ld)", msgType );

			retval = FALSE;
			break;
		}
	}

	return( retval );
}

// --
