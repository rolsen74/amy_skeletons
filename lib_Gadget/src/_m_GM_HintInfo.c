
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _m_GM_Query( Class *cl, Object *obj, struct gpQuery *msg )
{
struct InputEvent *ie;
struct GadData *data;
U32 retval;

	data = INST_DATA( cl, obj );

	retval = GMR_REUSE;

	if ( msg->gpq_Type == GMQ_HINTINFO )
	{
		ie = msg->gpq_IEvent;

		if (( ie )
		&&	( ie->ie_X > data->GadXPos ) 
		&&	( ie->ie_X < data->GadXPos + data->GadWidth ) 
		&&	( ie->ie_Y > data->GadYPos ) 
		&&	( ie->ie_Y < data->GadYPos + data->GadHeight ))
		{
			*msg->gpq_Data = (U32) data->HintInfoStr;

			retval = GMR_NOREUSE;
		}
		else
		{
			*msg->gpq_Data = 0;
		}
	}

	return( retval );
}

// --
