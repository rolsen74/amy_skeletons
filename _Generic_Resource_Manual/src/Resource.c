
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

// -- Main Interface

static const PTR _main_Vectors[] =
{
	(PTR) _main_Obtain,
	(PTR) _main_Release,
	(PTR) NULL,
	(PTR) NULL,
	(PTR) _main_GetVal,
	(PTR) -1
};

static const struct TagItem _main_Tags[] =
{
	{ MIT_Name,			(Tag) "main"		},
	{ MIT_VectorTable,	(Tag) _main_Vectors	},
	{ MIT_DataSize,		(Tag) sizeof( struct ResData ) },
	{ MIT_Version,		(Tag) 1				},
	{ TAG_END,			(Tag) 0				}
};

// --

const PTR resInterfaces[] =
{
	(PTR) _manager_Tags,
	(PTR) _main_Tags,
	(PTR) NULL
};

// --
// if you want you can add a litte extra info for version
// string if you want.. but that is optional
// maybe a copyright line?

static USED char	verstag[] = VERSTAG;
//static USED char	verstag[] = VERSTAG "Coded by awesome me";

// --

static USED const struct Resident res_res =
{
/* rt_MatchWord	*/			RTC_MATCHWORD,
/* rt_MatchTag	*/ (PTR)	( & res_res + 0 ),
/* rt_EndSkip	*/ (PTR)	( & res_res + 1 ),
/* rt_Flags		*/			RTF_NATIVE|RTF_COLDSTART,
/* rt_Version	*/			VERSION,
/* rt_Type		*/			NT_RESOURCE,
/* rt_Pri		*/			RESPRI,
/* rt_Name		*/ (STR)	RESNAME,
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
