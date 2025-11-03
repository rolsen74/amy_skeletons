
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INTERFACES_TEST_RESOURCE_H
#define INTERFACES_TEST_RESOURCE_H

// --

#include <proto/exec.h>
#include <proto/intuition.h>

#include <stdint.h>

// --

struct Test_ResourceIFace
{
	struct InterfaceData Data;
	uint32_t					APICALL (*Obtain)(struct Test_ResourceIFace *Self);
	uint32_t					APICALL (*Release)(struct Test_ResourceIFace *Self);
	void						APICALL (*Expunge)(struct Test_ResourceIFace *Self);
	struct Interface *			APICALL (*Clone)(struct Test_ResourceIFace *Self);
	uint32_t					APICALL (*TESTRes_GetVal)( struct Test_ResourceIFace *Self );
};

// --

#endif
