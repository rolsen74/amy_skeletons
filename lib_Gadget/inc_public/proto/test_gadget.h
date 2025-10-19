
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef PROTO_TEST_GADGET_H
#define PROTO_TEST_GADGET_H

// --

#include <proto/exec.h>

#include <stdint.h>

// --
// AmigaOS4

#ifdef __amigaos4__

 #include <gadgets/test_gadget.h>
 #include <interfaces/test_gadget.h>

 #ifdef __USE_INLINE__
 #include <inline4/test_gadget.h>
 #endif

 #ifndef __NOLIBBASE__
 extern struct ClassLibrary *Test_GadgetBase;
 #endif

 #ifndef __NOGLOBALIFACE__
 extern struct Test_GadgetIFace *ITest_Gadget;
 #endif

#else // Other platforms

  #error Only support for AmigaOS4 .. at the moment

#endif

// --

#endif
