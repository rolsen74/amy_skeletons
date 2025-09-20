
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

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

static const PTR _blanker_Vectors[] =
{
	(PTR) _blanker_Obtain,
	(PTR) _blanker_Release,
	(PTR) _blanker_Expunge,
	(PTR) _blanker_Clone,
	(PTR) _blanker_Get,
	(PTR) _blanker_Set,
	(PTR) _blanker_Blank,
	(PTR) -1
};

const struct TagItem _blanker_Tags[] =
{
	{ MIT_Name,			(Tag) "blankermodule"	},
	{ MIT_VectorTable,	(Tag) _blanker_Vectors	},
	{ MIT_DataSize,		(Tag) sizeof( struct BlankerData )},
	{ MIT_Flags,		(Tag) IFLF_PRIVATE		},
	{ MIT_Version,		(Tag) 1					},
	{ TAG_END,			(Tag) 0					}
};

// --

const PTR libInterfaces[] =
{
	(PTR) _manager_Tags,
	(PTR) _blanker_Tags,
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
