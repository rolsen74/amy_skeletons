
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

PTR _docky_Clone( struct DockyIFace *Self )
{
//struct DockyBase *libBase;
struct Interface *IFace;
struct DockyData *data;
S32 error;

	MYDEBUG( "Docky : _docky_Clone" );

//	libBase = (PTR) Self->Data.LibBase;
	error = TRUE;

	extern const struct TagItem _docky_Tags[];
	IFace = MakeInterface( Self->Data.LibBase, _docky_Tags );

	if ( ! IFace )
	{
		MYERROR( "Docky : Error allocating memory" );
		goto bailout;
	}

	IFace->Data.Flags |= IFLF_CLONED;

	data = (PTR) ( (U32) IFace - IFace->Data.NegativeSize );

	memset( data, 0, sizeof( struct DockyData ));

	// Init/Alloc or Open extra resources here

	error = FALSE;

bailout:

	if (( IFace ) && ( error ))
	{
		_docky_Expunge( (PTR) IFace );
		IFace = NULL;
	}

	return( IFace );
}

// --
