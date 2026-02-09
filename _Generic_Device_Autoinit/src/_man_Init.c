
/*
** SPDX-License-Identifier: Unlicense
** Written 2026 by Rene W. Olsen
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

PTR _manager_Init( struct DEVBase *devBase, PTR SegList, struct ExecIFace *myIExec )
{
struct DEVBase *retval;

	IExec = myIExec;

	MYDEBUG( "Device : _manager_Init" );

	devBase->dev_Base.dd_Library.lib_Node.ln_Type	= NT_DEVICE;
	devBase->dev_Base.dd_Library.lib_Node.ln_Pri	= DEVPRI;
	devBase->dev_Base.dd_Library.lib_Node.ln_Name	= DEVNAME;
	devBase->dev_Base.dd_Library.lib_Flags			= LIBF_SUMUSED|LIBF_CHANGED;
	devBase->dev_Base.dd_Library.lib_Version		= VERSION;
	devBase->dev_Base.dd_Library.lib_Revision		= REVISION;
	devBase->dev_Base.dd_Library.lib_IdString		= VSTRING;
	devBase->dev_SegList = SegList;

	if ( Resources_Init( devBase ))
	{
		MYDEBUG( "Device : Opening Resources...  Success" );

		/* Set retun value */
		retval = devBase;

		/* Optional: small startup message */
		DebugPrintF( "Device : Rock'n Roll\n" );
	}
	else
	{
		MYERROR( "Device : Opening Resources...  Failed" );

		Resources_Free( devBase );

		retval	= NULL;
	}

	return( retval );
}

// --
