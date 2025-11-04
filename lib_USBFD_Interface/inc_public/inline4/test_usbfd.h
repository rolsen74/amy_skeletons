
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INLINE4_TEST_USBFD_H
#define INLINE4_TEST_USBFD_H

// --

#include <proto/exec.h>

// --

#define TESTLIB_GetAttrsA(x)		ITest_USBFD->TESTLIB_GetAttrsA(x)
#define TESTLIB_RunFunction(x)		ITest_USBFD->TESTLIB_RunFunction(x)
#define TESTLIB_RunInterface(x)		ITest_USBFD->TESTLIB_RunInterface(x)

//	int32_t						APICALL (*TESTLIB_GetAttrsA)(struct Test_USBFDIFace *Self, struct TagItem *list );
//	int32_t						APICALL (*TESTLIB_GetAttrs)(struct Test_USBFDIFace *Self, ... );
//	int32_t						APICALL (*TESTLIB_RunFunction)(struct Test_USBFDIFace *Self, struct USBFDStartupMsg *msg );
//	int32_t						APICALL (*TESTLIB_RunInterface)(struct Test_USBFDIFace *Self, struct USBFDStartupMsg *msg );

// --

#endif
