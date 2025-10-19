
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
// Normaly LIBNAME and CLSNAME are the same

#define CLSNAME		"test_gadget.gadget"
#define LIBNAME		"test_gadget.gadget"
#define VERSION		1
#define REVISION	1
#define DATE		"29.10.2025"
#define VERS		LIBNAME " 1.1"
#define VSTRING		LIBNAME " 1.1 (" DATE ")\r\n"
#define VERSTAG		"\0$VER: " LIBNAME " 1.1 (" DATE ")"

// --

#endif
