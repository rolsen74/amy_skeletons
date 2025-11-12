
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INC_PRIVATE_ALL_H
#define INC_PRIVATE_ALL_H

// --
// Lets provide our own S2QUAD type
#define __S2QUAD_DEFINED
typedef unsigned long long S2QUAD;

// --

#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/intuition.h>
#include <proto/timer.h>
#include <proto/utility.h>

#include <devices/newstyle.h>
#include <devices/sana2.h>
#include <devices/sana2specialstats.h>
#include <exec/emulation.h>

#include <stdarg.h>
#include <stdint.h>
#include <string.h>

// --
#include "inc_private/Types.h"
#include "inc_private/Version.h"
// --
#include "inc_private/Debug.h"
#include "inc_private/Task.h"
#include "inc_private/Device.h"
// --
#include "inc_private/Protos.h"
// --

#endif
