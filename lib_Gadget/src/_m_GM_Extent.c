
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _m_GM_Extent( Class *cl, Object *obj, struct gpExtent *msg )
{
struct Rectangle rect;
struct GadData *data;

	MYINFO( "Gadget : _m_GM_Extent" );

	data = INST_DATA( cl, obj );

	if ( msg->gpe_Region )
	{
		rect.MinX = data->GadXPos;
		rect.MinY = data->GadYPos;
		rect.MaxX = data->GadXPos + data->GadWidth  - 1;
		rect.MaxY = data->GadYPos + data->GadHeight - 1;

		switch( msg->gpe_Action )
		{
			case GEXTENT_ADD:
			{
				OrRectRegion( msg->gpe_Region, & rect );
				break;
			}

			case GEXTENT_SECT:
			{
				AndRectRegion( msg->gpe_Region, & rect );
				break;
			}

			case GEXTENT_REMOVE:
			{
				ClearRectRegion( msg->gpe_Region, & rect );
				break;
			}

			case GEXTENT_INVERT:
			{
				XorRectRegion( msg->gpe_Region, & rect );
				break;
			}

			default:
			{
				break;
			}
		}

		return( GMR_CLIPDONE );
	}
	else
	{
		return( GMR_INVALID );
	}
}
