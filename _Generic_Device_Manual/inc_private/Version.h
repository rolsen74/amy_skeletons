
/*
** SPDX-License-Identifier: Unlicense
** Written 2026 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INC_PRIVATE_ALL_H
#error Include "inc_private/All.h" first
#endif

#ifndef INC_PRIVATE_VERSION_H
#define INC_PRIVATE_VERSION_H

// --

#define DEVPRI		0
#define DEVNAME		"test.device"
#define VERSION		1
#define REVISION	1
#define DATE		"09.02.2026"	// dd.mm.yyyy
#define VERS		DEVNAME " 1.1"
#define VSTRING		DEVNAME " 1.1 (" DATE ")\r\n"
#define VERSTAG		"\0$VER: " DEVNAME " 1.1 (" DATE ")"

// --

#endif
