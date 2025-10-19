
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INTERFACES_TEST_GADGET_H
#define INTERFACES_TEST_GADGET_H

// --

#include <proto/exec.h>
#include <proto/intuition.h>

#include <stdint.h>

// --

struct Test_GadgetIFace
{
	struct InterfaceData Data;
	uint32_t					APICALL (*Obtain)(struct Test_GadgetIFace *Self);
	uint32_t					APICALL (*Release)(struct Test_GadgetIFace *Self);
	void						APICALL (*Expunge)(struct Test_GadgetIFace *Self);
	struct Interface *			APICALL (*Clone)(struct Test_GadgetIFace *Self);
	Class *						APICALL (*TGAD_GetClass)(struct Test_GadgetIFace *Self);
	uint32_t					APICALL (*TGAD_GetError)(struct Test_GadgetIFace *Self, int arg);
};

// --

#endif
