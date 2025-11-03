
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

PTR _manager_Init( PTR Dummy UNUSED, PTR SegList UNUSED, struct ExecBase *mySysBase )
{
struct Real_ResourceBase *resBase;

	SysBase = (PTR) mySysBase;
	IExec = (PTR) mySysBase->MainInterface;

	MYDEBUG( "Resource : _manager_Init" );

	// Make sure we havent been started before
	resBase = (PTR) FindName( & mySysBase->ResourceList, RESNAME );
	
	if ( resBase )
	{
		MYERROR( "_manager_Init : Library allready loaded" );
		goto bailout;
	}

	// Create library, but still not public
	extern const PTR resInterfaces[];
	resBase = (PTR) CreateLibraryTags(
		CLT_DataSize, sizeof( struct Real_ResourceBase ),
		CLT_Interfaces,	resInterfaces,
		CLT_NoLegacyIFace, TRUE,
		TAG_END
	);

	if ( ! resBase )
	{
		MYERROR( "_manager_Init : Failed to create device" );
		goto bailout;
	}

	resBase->res_Public.res_Base.lib_Node.ln_Type	= NT_RESOURCE;
	resBase->res_Public.res_Base.lib_Node.ln_Pri	= 0;
	resBase->res_Public.res_Base.lib_Node.ln_Name	= RESNAME;
	resBase->res_Public.res_Base.lib_Flags			= LIBF_SUMUSED|LIBF_CHANGED;
	resBase->res_Public.res_Base.lib_Version		= VERSION;
	resBase->res_Public.res_Base.lib_Revision		= REVISION;
	resBase->res_Public.res_Base.lib_IdString		= VSTRING;

	/*
	** Because we add the library manually, we have full control here.
	** If needed, you could obtain your own main/docky interface and call your
	** own methods before publication.
	*/

	if ( Resources_Init( resBase ))
	{
		MYDEBUG( "Resource : Opening Resources...  Success" );

		/* Make it public */
		AddResource( (PTR) resBase );

		/* Optional: small startup message */
		DebugPrintF( "Resource : Rock'n Roll\n" );
	}
	else
	{
		MYERROR( "Resource : Opening Resources...  Failed" );

		Resources_Free( resBase );

		DeleteLibrary( (PTR) resBase );
		resBase = NULL;
	}

bailout:

	return( resBase );
}

// --
