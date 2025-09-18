
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --
// Global Pointers

struct Library *		DOSBase			= NULL;
struct DOSIFace *		IDOS			= NULL;

struct Library *		SysBase			= NULL;
struct ExecIFace *		IExec			= NULL;

struct Library *		NewlibBase		= NULL;
struct Interface *		INewlib			= NULL;

struct Library *		UtilityBase		= NULL;
struct UtilityIFace *	IUtility		= NULL;

// --

static const PTR _manager_Vectors[] =
{
	(PTR) _manager_Obtain,
	(PTR) _manager_Release,
	(PTR) NULL,
	(PTR) NULL,
	(PTR) _manager_Open,
	(PTR) _manager_Close,
	(PTR) _manager_Expunge,
	(PTR) NULL,
	(PTR) -1
};

static const struct TagItem _manager_Tags[] =
{
	{ MIT_Name,			(Tag) "__library"		},
	{ MIT_VectorTable,	(Tag) _manager_Vectors	},
	{ MIT_Version,		(Tag) 1					},
	{ TAG_END,			(Tag) 0					}
};

// --

static const PTR _docky_Vectors[] =
{
	(PTR) _docky_Obtain,
	(PTR) _docky_Release,
	(PTR) _docky_Expunge,
	(PTR) _docky_Clone,
	(PTR) _docky_Get,
	(PTR) _docky_Set,
	(PTR) _docky_Process,
	(PTR) -1
};

const struct TagItem _docky_Tags[] =
{
	{ MIT_Name,			(Tag) "docky"			},
	{ MIT_VectorTable,	(Tag) _docky_Vectors	},
	{ MIT_DataSize,		(Tag) sizeof( struct DockyData )},
	{ MIT_Flags,		(Tag) IFLF_PRIVATE		},
	{ MIT_Version,		(Tag) 1					},
	{ TAG_END,			(Tag) 0					}
};

// --

const PTR libInterfaces[] =
{
	(PTR) _manager_Tags,
	(PTR) _docky_Tags,
	(PTR) NULL
};

// --
// if you want you can add a litte extra info for version
// string if you want.. but that is optional
// maybe a copyright line?

static USED char	verstag[] = VERSTAG;
//static USED char	verstag[] = VERSTAG "Coded by awesome me";

// --

static USED const struct Resident lib_res =
{
/* rt_MatchWord	*/			RTC_MATCHWORD,
/* rt_MatchTag	*/ (PTR)	( & lib_res + 0 ),
/* rt_EndSkip	*/ (PTR)	( & lib_res + 1 ),
/* rt_Flags		*/			RTF_NATIVE|RTF_COLDSTART,
/* rt_Version	*/			VERSION,
/* rt_Type		*/			NT_LIBRARY,
/* rt_Pri		*/			0,
/* rt_Name		*/ (STR)	LIBNAME,
/* rt_IdString	*/ (STR)	VSTRING,
/* rt_Init		*/ (PTR)	_manager_Init
};

// --
// This is the entry point, if someone tries to run us from shell/wb

S32 _start( STR argstring UNUSED, S32 arglen UNUSED, struct ExecBase *sysbase UNUSED )
{
	return( 0 );
}

// --
