
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INLINE4_TEST_GADGET_H
#define INLINE4_TEST_GADGET_H

// --

#include <proto/exec.h>

#include <stdint.h>

// --

#define TGAD_GetClass()			TestGadgetIFace->TGAD_GetClass()
#define TGAD_GetError(x)		TestGadgetIFace->TGAD_GetError(x)

// --

#endif
