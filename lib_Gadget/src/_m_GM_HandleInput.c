
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _m_GM_HandleInput( Class *cl UNUSED, Object *obj UNUSED, struct gpInput *msg )
{
U32 retval;

	MYINFO( "Gadget : _m_GM_HandleInput : Class %d", msg->gpi_IEvent->ie_Class );

	// Just a small example.. 
	// the RawMouse button will not stay active
	// so you need to remember if you are active
	// and know when to return GMR_MEACTIVE / GMR_NOREUSE

	switch( msg->gpi_IEvent->ie_Class )
	{
		case IECLASS_RAWMOUSE:
		{
			if ( msg->gpi_IEvent->ie_Code == IECODE_LBUTTON )
			{
				retval = GMR_MEACTIVE;
			}
			else
			{
				retval = GMR_NOREUSE;
			}
			break;
		}

		// case IECLASS_RAWKEY:
		// {
		// 	retval = GMR_MEACTIVE;
		// 	break;
		// }

		// case IECLASS_MOUSEWHEEL:
		// {
		// 	retval = GMR_MEACTIVE;
		// 	break;
		// }

		// case IECLASS_TIMER:
		// {
		// 	retval = GMR_MEACTIVE;
		// 	break;
		// }

		default:
		{
			retval = GMR_NOREUSE;
			break;
		}
	}

	// read more in GadgetClass.h
	// GMR_MEACTIVE - we want too stay active
	// GMR_NOREUSE  - we are done

	// --

	return(	retval );
}

