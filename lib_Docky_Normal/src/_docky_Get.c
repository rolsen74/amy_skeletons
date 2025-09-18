
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

BOOL _docky_Get( struct DockyIFace *Self, U32 msgType, U32 *msgData )
{
struct DockyData *data;
BOOL retval;

	data = (PTR) ( (U32) Self - Self->Data.NegativeSize );

	retval = TRUE;

	switch( msgType )
	{
		case DOCKYGET_Version:
		{
			MYINFO( "DOCKYGET_Version" );

			*msgData = DOCKYVERSION;
			break;
		}

		case DOCKYGET_GetSize:
		{
			MYINFO( "DOCKYGET_GetSize" );

			data->dd_DockySize.width = myDocky_Width;
			data->dd_DockySize.height = myDocky_Height;
			*((struct DockySize *)msgData) = data->dd_DockySize;
			break;
		}

		case DOCKYGET_FrameDelay:
		{
			MYINFO( "DOCKYGET_FrameDelay" );

			*msgData = 0;
			break;
		}

		case DOCKYGET_Name:
		{
			MYINFO( "DOCKYGET_Name" );

			*msgData = (U32) "TestDocky";
			break;
		}

		case DOCKYGET_RenderMode:
		{
			MYINFO( "DOCKYGET_RenderMode" );

			*msgData = DOCKYRENDERMODE_RPPA;
			break;
		}

		case DOCKYGET_Notifications:
		{
			MYINFO( "DOCKYGET_Notifications" );

			*msgData = DOCKYNOTIFY_MOUSEBUTTONS;
			break;
		}

		case DOCKYGET_DockyPrefs:
		{
			MYINFO( "DOCKYGET_DockyPrefs" );

			retval = FALSE;
			break;
		}

		default:
		{
			MYINFO( "Unsupported DOCKYGET (%ld)", msgType );

			retval = FALSE;
			break;
		}
	}

	return( retval );
}

// --
