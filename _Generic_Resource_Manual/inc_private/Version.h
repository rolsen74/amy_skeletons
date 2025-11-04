
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INC_PRIVATE_ALL_H
#error Include "inc_private/All.h" first
#endif

#ifndef INC_PRIVATE_VERSION_H
#define INC_PRIVATE_VERSION_H

// --

#define RESPRI		0
#define RESNAME		"test_resource.resource"
#define VERSION		1
#define REVISION	1
#define DATE		"29.10.2025"		// dd.mm.yyyy
#define VERS		RESNAME " 1.1"
#define VSTRING		RESNAME " 1.1 (" DATE ")\r\n"
#define VERSTAG		"\0$VER: " RESNAME " 1.1 (" DATE ")"

// --

#endif
