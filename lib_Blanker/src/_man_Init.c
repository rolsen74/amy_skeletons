
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

/*
** Note:
**  Do not allocate MsgPorts / signals here.
**  We’re running in the Ramdisk/Ramlib/Exec startup context. If you need to
**  allocate any signals, do it in manager_open (the caller’s process context).
*/

PTR _manager_Init( PTR Dummy UNUSED, PTR SegList, struct ExecBase *mySysBase )
{
struct BlankerBase *libBase;

	libBase	= NULL;
	SysBase = (PTR) mySysBase;
	IExec = (PTR) mySysBase->MainInterface;

	MYDEBUG( "Blanker : _manager_Init" );

	// Make sure we havent started
	if ( FindName( & mySysBase->DeviceList, LIBNAME ))
	{
		MYERROR( "_manager_Init : Library allready loaded" );
		goto bailout;
	}

	// Create library, but still not public
	extern const PTR libInterfaces[];
	libBase = (PTR) CreateLibraryTags(
		CLT_DataSize, sizeof( struct BlankerBase ),
		CLT_Interfaces,	libInterfaces,
		CLT_NoLegacyIFace, TRUE,
		TAG_END
	);

	if ( ! libBase )
	{
		MYERROR( "_manager_Init : Failed to create device" );
		goto bailout;
	}

	libBase->lib_Base.lib_Node.ln_Type	= NT_LIBRARY;
	libBase->lib_Base.lib_Node.ln_Pri	= 0;
	libBase->lib_Base.lib_Node.ln_Name	= LIBNAME;
	libBase->lib_Base.lib_Flags			= LIBF_SUMUSED|LIBF_CHANGED;
	libBase->lib_Base.lib_Version		= VERSION;
	libBase->lib_Base.lib_Revision		= REVISION;
	libBase->lib_Base.lib_IdString		= VSTRING;
	libBase->lib_SegList = SegList;

	/*
	** Because we add the library manually, we have full control here.
	** If needed, you could obtain your own main/docky interface and call your
	** own methods before publication.
	*/

	if ( Resources_Init( libBase ))
	{
		MYDEBUG( "Blanker : Opening Resources...  Success" );

		/* Make it public */
		AddLibrary( (PTR) libBase );

		/* Optional: small startup message */
		DebugPrintF( "Blanker : Rock'n Roll\n" );
	}
	else
	{
		MYERROR( "Blanker : Opening Resources...  Failed" );

		Resources_Free( libBase );

		DeleteLibrary( (PTR) libBase );
		libBase = NULL;
	}

bailout:

	return( NULL );
}

// --
