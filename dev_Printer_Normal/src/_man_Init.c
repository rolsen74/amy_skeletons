
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --
// Note:
//
//  Do not allocate MsgPort / Signals here.
//
//  We are running in Ramdisk / Ramlib / exec startup process here,
//  if you need too alloc do that in manager_open as that is in the 
//  callers process.
// 

PTR _manager_Init( PTR Dummy UNUSED, PTR SegList, struct ExecBase *mySysBase )
{
struct PrinterBase *devBase;

	devBase	= NULL;
	SysBase = (PTR) mySysBase;
	IExec = (PTR) mySysBase->MainInterface;

	MYDEBUG( "Printer : _manager_Init", 0 );

	// Make sure we havent started
	if ( FindName( & mySysBase->DeviceList, DEVNAME ))
	{
		MYERROR( "_manager_Init : Device allready loaded", 0 );
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
		MYERROR( "_manager_Init : Failed to create device", 0 );
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
	** As we are adding the Device manualy we now have
	** a little extra control here..
	**
	** Here we have the Base address even if its not public yet.
	** 
	** if we wanted we could Obtain the Main interface here
	**  and call one of our own Interface functions.
	*/

	if ( Resources_Init( devBase ))
	{
		MYDEBUG( "Printer : Opening Resources...  Success", 0 );

		// Make it public
		AddDevice( (PTR) devBase );

		// Optional : I like too always print a small message, so i'm sure we started
		DebugPrintF( "Printer : Rock'n Roll\n" );
	}
	else
	{
		MYERROR( "Printer : Opening Resources...  Failed", 0 );

		Resources_Free( devBase );

		DeleteLibrary( (PTR) devBase );
		devBase = NULL;
	}

bailout:

	return( NULL );
}

// --
