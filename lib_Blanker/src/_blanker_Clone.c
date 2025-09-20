
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

static const struct BitMap PointerBitmap =
{
	0,
	0,
	0,
	0,
	0,
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
};

// --

PTR _blanker_Clone( struct BlankerModuleIFace *Self )
{
//struct BlankerBase *libBase;
struct Interface *IFace;
struct BlankerData *data;
S32 error;

	MYDEBUG( "Blanker : _blanker_Clone" );

//	libBase = (PTR) Self->Data.LibBase;
	error = TRUE;

	extern const struct TagItem _blanker_Tags[];
	IFace = MakeInterface( Self->Data.LibBase, _blanker_Tags );

	if ( ! IFace )
	{
		MYERROR( "Blanker : Error allocating memory" );
		goto bailout;
	}

	IFace->Data.Flags |= IFLF_CLONED;

	data = (PTR) ( (U32) IFace - IFace->Data.NegativeSize );

	memset( data, 0, sizeof( struct BlankerData ));

	// Init/Alloc or Open extra resources here

	// Default
	Settings_Default( data );

	data->bd_BlankingMode = SBBM_NoBlanking;


	// --
	// Create (Empty) Mouse Pointer

	data->bd_MouseObject = NewObject( NULL, "pointerclass",
		POINTERA_BitMap,    & PointerBitmap,
		POINTERA_XOffset,   0,
		POINTERA_YOffset,   0,
		TAG_END
	);

	if ( ! data->bd_MouseObject )
	{
		MYERROR( "Blanker : Error creating ASL Handle" );
		goto bailout;
	}

	// --
	// Alloc ASL
	data->bd_ScreenModeRequester = AllocAslRequestTags( ASL_ScreenModeRequest,
		TAG_END
	);

	if ( ! data->bd_ScreenModeRequester )
	{
		MYERROR( "Blanker : Error creating ScreenMode Requester" );
		goto bailout;
	}

	error = FALSE;

bailout:

	if (( IFace ) && ( error ))
	{
		_blanker_Expunge( (PTR) IFace );
		IFace = NULL;
	}

	return( IFace );
}

// --
