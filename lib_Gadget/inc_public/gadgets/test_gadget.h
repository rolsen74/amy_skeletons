
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef GADGETS_TEST_GADGET_H
#define GADGETS_TEST_GADGET_H

// --

#include <proto/exec.h>

#include <stdint.h>

// --
// Our Test Gadget tags

#define TEST_GADGET_Dummy		( TAG_USER )

// This tag is needed at Creation.. OM_New only
#define TEST_GADGET_Needed		( TEST_GADGET_Dummy + 1 )

// Optional, OM_Net, OM_Get, OM_Set, OM_Update
#define TEST_GADGET_Optional	( TEST_GADGET_Dummy + 2 )

// --

#endif
