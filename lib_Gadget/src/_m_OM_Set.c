
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _m_OM_Set( Class *cl, Object *obj, struct opSet *msg )
{
// struct libBase *libBase;
struct GadData *data;
struct TagItem *tags;
struct TagItem *tag;
U32 handled;
S32 refresh;
U32 retval;

	MYINFO( "Gadget : _m_OM_Set" );

	//	If you need too passe data, can get it this way
//	Set in Resources_Init/MakeClass
//	libBase = (PTR) cl->cl_UserData;

	data		= INST_DATA( cl, obj );
	tags		= msg->ops_AttrList;
	refresh		= FALSE;
	handled		= 0;

	while(( tag = NextTagItem( & tags )))
	{
		handled++;

		switch( tag->ti_Tag )
		{
			case GA_HintInfo:
			{
				data->HintInfoStr = (STR) tag->ti_Data;
				break;
			}

			case TEST_GADGET_Optional:
			{
				U32 val = ( tag->ti_Data ) ? TRUE : FALSE ;

				// Check for change, and only refresh gadget on change
				if ( data->Optional != val )
				{
					data->Optional = val;
					refresh = TRUE;
				}
				break;
			}

			default:
			{
				handled--;
				break;
			}
		}
	}

	// Let Super handle tags too
	retval = IDoSuperMethodA( cl, obj, (Msg) msg );

	if (( refresh ) || ( retval ))
	{
		DoRender( obj, msg->ops_GInfo, GREDRAW_REDRAW );
	}

	// Return number of handled Tags
	return(	handled );
}
