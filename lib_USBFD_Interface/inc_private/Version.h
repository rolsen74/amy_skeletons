
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
// Pri Note:
//  If we are going too add this to Kickstart
//  ( a mouse/keyboard is nice for Early Startup menu ),
//  We need a pri value before usb stack and after usb resource
//  is started.
//
//  On the other hand if this driver gets loaded from disk
//  the pri value is not used.
//

#define LIBPRI		-46
#define LIBNAME		"test_usbfd.usbfd"
#define VERSION		1
#define REVISION	1
#define DATE		"03.11.2025"
#define VERS		LIBNAME " 1.1"
#define VSTRING		LIBNAME " 1.1 (" DATE ")\r\n"
#define VERSTAG		"\0$VER: " LIBNAME " 1.1 (" DATE ")"

// --

#endif
