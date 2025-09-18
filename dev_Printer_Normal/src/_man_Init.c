
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
struct PrinterBase *devBase;

	devBase	= NULL;
	SysBase = (PTR) mySysBase;
	IExec = (PTR) mySysBase->MainInterface;

	MYDEBUG( "Printer : _manager_Init" );

	// Make sure we havent started
	if ( FindName( & mySysBase->DeviceList, DEVNAME ))
	{
		MYERROR( "_manager_Init : Device allready loaded" );
		goto bailout;
	}

	// Create library, but still not public
	extern const PTR devInterfaces[];
	devBase = (PTR) CreateLibraryTags(
		CLT_DataSize, sizeof( struct PrinterBase ),
		CLT_Interfaces,	devInterfaces,
		CLT_NoLegacyIFace, TRUE,
		TAG_END
	);

	if ( ! devBase )
	{
		MYERROR( "_manager_Init : Failed to create device" );
		goto bailout;
	}

	devBase->dev_Base.dd_Library.lib_Node.ln_Type	= NT_DEVICE;
	devBase->dev_Base.dd_Library.lib_Node.ln_Pri	= 0;
	devBase->dev_Base.dd_Library.lib_Node.ln_Name	= DEVNAME;
	devBase->dev_Base.dd_Library.lib_Flags			= LIBF_SUMUSED|LIBF_CHANGED;
	devBase->dev_Base.dd_Library.lib_Version		= VERSION;
	devBase->dev_Base.dd_Library.lib_Revision		= REVISION;
	devBase->dev_Base.dd_Library.lib_IdString		= VSTRING;
	devBase->dev_SegList = SegList;

	/*
	** Because we add the device manually, we have full control here.
	** If needed, you could obtain your own main interface and call your
	** own methods before publication.
	*/

	if ( Resources_Init( devBase ))
	{
		MYDEBUG( "Printer : Opening Resources...  Success" );

		/* Make it public */
		AddDevice( (PTR) devBase );

		/* Optional: small startup message */
		DebugPrintF( "Printer : Rock'n Roll\n" );
	}
	else
	{
		MYERROR( "Printer : Opening Resources...  Failed" );

		Resources_Free( devBase );

		DeleteLibrary( (PTR) devBase );
		devBase = NULL;
	}

bailout:

	return( NULL );
}

// --
