
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

BOOL _blanker_Get( struct BlankerModuleIFace *Self UNUSED, U32 msgType, U32 *msgData )
{
struct BlankerData *data;
BOOL retval;

	data = (PTR) ( (U32) Self - Self->Data.NegativeSize );

	retval = TRUE;

	switch( msgType )
	{
		case /* 0001 */ BMGET_Version:
		{
			MYINFO( "Blanker : BMGET_Version" );

			*msgData = BLANKERMODULEVERSION;
			break;
		}

		case /* 0002 */ BMGET_ModuleAuthorInfo:
		{
			MYINFO( "Blanker : BMGET_ModuleAuthorInfo" );

			*msgData = (U32) "awesome coder";
			break;
		}

		case /* 0003 */ BMGET_ModuleVersionInfo:
		{
			MYINFO( "Blanker : BMGET_ModuleVersionInfo" );

			*msgData = (U32) & VERSTAG[7];
			break;
		}

		case /* 0004 */ BMGET_RenderMode:
		{
			MYINFO( "Blanker : BMGET_RenderMode" );

			*msgData = BMRM_CustomScreen;
			break;
		}

		case /* 0005 */ BMGET_NeedsDoubleBuffer:
		{
			MYINFO( "Blanker : BMGET_NeedsDoubleBuffer" );

			retval = FALSE;
			break;
		}

		case /* 0006 */ BMGET_ColorTableType:
		{
			MYINFO( "Blanker : BMGET_ColorTableType" );

			retval = FALSE;
			break;
		}

		case /* 0007 */ BMGET_PreferencesType:
		{
			MYINFO( "Blanker : BMGET_PreferencesType" );

			*msgData = BMPT_Custom;
			break;
		}

		case /* 0008 */ BMGET_Preferences:
		{
			MYINFO( "Blanker : BMGET_Preferences" );

			Settings_Load( data, (PTR) msgData );
			break;
		}

		default:
		{
			MYINFO( "Blanker : Unsupported BMGET (%ld)", msgType );

			retval = FALSE;
			break;
		}
	}

	return( retval );
}

// --
