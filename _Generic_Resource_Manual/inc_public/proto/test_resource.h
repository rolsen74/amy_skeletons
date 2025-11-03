
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef PROTO_TEST_RESOURCE_H
#define PROTO_TEST_RESOURCE_H

// --

#include <proto/exec.h>
#include <stdint.h>

// --
// AmigaOS4

#ifdef __amigaos4__

 #include <resources/test_resource.h>
 #include <interfaces/test_resource.h>

 #ifdef __USE_INLINE__
 #include <inline4/test_resource.h>
 #endif

 #ifndef __NOLIBBASE__
 extern struct Library *Test_ResourceBase;
 #endif

 #ifndef __NOGLOBALIFACE__
 extern struct Test_ResourceIFace *ITest_Resource;
 #endif

#else // Other platforms

  #error Only support for AmigaOS4 .. at the moment

#endif

// --

#endif
