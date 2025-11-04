
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
// Docker needs a min. vserion of 50.x

#define LIBPRI		0
#define LIBNAME		"test_docky.docky"
#define VERSION		50
#define REVISION	1
#define DATE		"18.9.2025"		// dd.mm.yyyy
#define VERS		LIBNAME " 50.1"
#define VSTRING		LIBNAME " 50.1 (" DATE ")\r\n"
#define VERSTAG		"\0$VER: " LIBNAME " 50.1 (" DATE ")"

// --

#endif
