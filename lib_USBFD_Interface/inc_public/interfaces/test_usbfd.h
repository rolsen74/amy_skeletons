
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INTERFACES_TEST_USBFD_H
#define INTERFACES_TEST_USBFD_H

// --

#include <proto/exec.h>
#include <proto/intuition.h>

#include <stdint.h>

// --

struct Test_USBFDIFace
{
	struct InterfaceData Data;
	uint32_t					APICALL (*TESTLIB_Obtain)(struct Test_USBFDIFace *Self);
	uint32_t					APICALL (*TESTLIB_Release)(struct Test_USBFDIFace *Self);
	void						APICALL (*TESTLIB_Expunge)(struct Test_USBFDIFace *Self);
	struct Interface *			APICALL (*TESTLIB_Clone)(struct Test_USBFDIFace *Self);
	int32_t						APICALL (*TESTLIB_GetAttrsA)(struct Test_USBFDIFace *Self, struct TagItem *list );
	int32_t						APICALL (*TESTLIB_GetAttrs)(struct Test_USBFDIFace *Self, ... );
	int32_t						APICALL (*TESTLIB_RunFunction)(struct Test_USBFDIFace *Self, struct USBFDStartupMsg *msg );
	int32_t						APICALL (*TESTLIB_RunInterface)(struct Test_USBFDIFace *Self, struct USBFDStartupMsg *msg );
};

// --

#endif
