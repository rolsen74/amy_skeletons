
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef PROTO_TEST_USBFD_H
#define PROTO_TEST_USBFD_H

// --

#include <proto/exec.h>

#include <stdint.h>

// --
// AmigaOS4

#ifdef __amigaos4__

 #include <libraries/test_usbfd.h>
 #include <interfaces/test_usbfd.h>

 #ifdef __USE_INLINE__
 #include <inline4/test_usbfd.h>
 #endif

 #ifndef __NOLIBBASE__
 extern struct Library *Test_LibraryBase;
 #endif

 #ifndef __NOGLOBALIFACE__
 extern struct Test_USBFDIFace *ITest_USBFD;
 #endif

#else // Other platforms

  #error Only support for AmigaOS4 .. at the moment

#endif

// --

#endif
