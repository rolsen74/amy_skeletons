
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

void _cmd_C008_S2_Sana2Hook( struct SANA2Unit *unit UNUSED, struct IOSana2Req *ioreq )
{
struct BufferManagement *bm;
struct Sana2Hook *hook;

	MYDEBUG( "SANA2 : _cmd_C008_S2_Sana2Hook" );

	bm		= (PTR) ioreq->ios2_BufferManagement;
	hook	= (PTR) ioreq->ios2_Data;

	/**/ if (( ! bm ) || ( ! hook ))
	{
		MYERROR( "NULL Pointer" );
		ioreq->ios2_Req.io_Error	= S2ERR_BAD_ARGUMENT;
		ioreq->ios2_WireError		= S2WERR_NULL_POINTER;
	}
	// Make sure we have min 20 bytes, default Sana2Hook structure (may grow)
	else if ( ioreq->ios2_DataLength < 20 )
	{
		MYERROR( "SANA2 : Bad Length : %ld", ioreq->ios2_DataLength );
		ioreq->ios2_Req.io_Error	= IOERR_BADLENGTH;
		ioreq->ios2_WireError		= 0;
	}
	else
	{
		bm->bm_CopyToBuff			= NULL;
		bm->bm_CopyFromBuff			= NULL;
		bm->bm_CopyToBuffTag		= TagInArray( S2_CopyToBuff, hook->s2h_Methods ) ? S2_CopyToBuff : 0 ;
		bm->bm_CopyFromBuffTag		= TagInArray( S2_CopyFromBuff, hook->s2h_Methods ) ? S2_CopyFromBuff : 0 ;
		bm->bm_DMACopyToBuffTag		= TagInArray( S2_DMACopyToBuff32, hook->s2h_Methods ) ? S2_DMACopyToBuff32 : 0 ;
		bm->bm_DMACopyFromBuffTag	= TagInArray( S2_DMACopyFromBuff32, hook->s2h_Methods ) ? S2_DMACopyFromBuff32 : 0 ;

		if (( ! bm->bm_CopyToBuffTag ) || ( ! bm->bm_DMACopyToBuffTag ))
		{
			ioreq->ios2_Req.io_Error	= S2ERR_BAD_ARGUMENT;
			ioreq->ios2_WireError		= S2WERR_FUNCTIONS_MISSING;
			bm->bm_CopyHook = NULL;
		}
		else
		{
			bm->bm_CopyHook = & hook->s2h_Hook;
		}
	}

	ReplyMsg( (PTR) ioreq );
}

// --
