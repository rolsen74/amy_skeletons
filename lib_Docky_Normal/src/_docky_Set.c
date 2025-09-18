
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

BOOL _docky_Set( struct DockyIFace *Self, U32 msgType, U32 msgData )
{
//struct DockyBase *libBase;
struct DockyData *data;
BOOL retval;

//	libBase = (PTR) Self->Data.LibBase;
	data = (PTR) ( (U32) Self - Self->Data.NegativeSize );

	retval = TRUE;

	switch( msgType )
	{
		case DOCKYSET_RenderDestination:
		{
			MYINFO( "DOCKYSET_RenderDestination" );

			struct DockyRenderDestination *drd = (PTR) msgData;

			switch( drd->renderMode )
			{
				case DOCKYRENDERMODE_RPPA:
				{
					data->dd_Width = drd->renderSize.width;
					data->dd_Height = drd->renderSize.height;
					data->dd_RenderRPort = drd->render.RP;
					break;
				}

				default:
				{
					data->dd_Width = 0;
					data->dd_Height = 0;
					data->dd_RenderRPort = NULL;

					retval = FALSE;
					break;
				}
			}
			break;
		}

		case DOCKYSET_RedrawNow:
		{
			MYINFO( "DOCKYSET_RedrawNow" );
			break;
		}

		case DOCKYSET_DockTypeChange:
		{
			MYINFO( "DOCKYSET_DockTypeChange" );

			struct DockyDockType *ddt = (PTR) msgData;

			if ( ddt->dockType != AMIDOCK_DockType_Icons )
			{
				retval = FALSE;
			}
			break;
		}

		case DOCKYSET_Screen:
		{
			MYINFO( "DOCKYSET_Screen" );

			data->dd_Screen = (PTR) msgData;
			break;
		}

		case DOCKYSET_MouseMove:
		{
			MYINFO( "DOCKYSET_MouseMove" );
			break;
		}

		case DOCKYSET_MouseIsOverDocky:
		{
			MYINFO( "DOCKYSET_MouseIsOverDocky" );
			break;
		}

		case DOCKYSET_HotKey:
		{
			MYINFO( "DOCKYSET_HotKey" );
			break;
		}

		case DOCKYSET_SingleClick:
		{
			MYINFO( "DOCKYSET_SingleClick" );
			break;
		}

		case DOCKYSET_DoubleClick:
		{
			MYINFO( "DOCKYSET_DoubleClick" );
			break;
		}

		case DOCKYSET_DockyRawKey:
		{
			MYINFO( "DOCKYSET_DockyRawKey" );
			break;
		}

		case DOCKYSET_DockyPrefs:
		{
			MYINFO( "DOCKYSET_DockyPrefs" );
			break;
		}

		case DOCKYSET_ContextMenuResult:
		{
			MYINFO( "DOCKYSET_ContextMenuResult" );
			break;
		}

		case DOCKYSET_FileName:
		{
			MYINFO( "DOCKYSET_FileName" );
			break;
		}

		default:
		{
			MYINFO( "Unsupported DOCKYSET (%ld)", msgType );

			retval = FALSE;
			break;
		}
	}

	return( retval );
}

// --
