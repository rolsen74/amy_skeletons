
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INC_PRIVATE_ALL_H
#define INC_PRIVATE_ALL_H

// --

#include <proto/application.h>
#include <proto/asl.h>
#include <proto/button.h>
#include <proto/chooser.h>
#include <proto/cybergraphics.h>
#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/graphics.h>
#include <proto/intuition.h>
#include <proto/label.h>
#include <proto/layout.h>
#include <proto/Picasso96API.h>
#include <proto/slider.h>
#include <proto/space.h>
#include <proto/utility.h>

#undef __USE_INLINE__
// work around as inline4/blankermodule.h is missing from my sdk
#include <proto/blankermodule.h>
#define __USE_INLINE__

#include <proto/screenblanker.h>

#include <classes/window.h>
#include <cybergraphx/cybergraphics.h>
#include <gadgets/button.h>
#include <gadgets/chooser.h>
#include <gadgets/layout.h>
#include <gadgets/slider.h>
#include <gadgets/space.h>
#include <images/label.h>
#include <intuition/icclass.h>
#include <libraries/blankermodule.h>
#include <libraries/screenblanker.h>

#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#if 0
#include <classes/window.h>
#include <cybergraphx/cybergraphics.h>
#include <gadgets/button.h>
#include <gadgets/chooser.h>
#include <gadgets/layout.h>
#include <gadgets/slider.h>
#include <gadgets/space.h>
#include <graphics/rpattr.h>
#include <images/label.h>
#include <intuition/icclass.h>
#include <intuition/pointerclass.h>
#include <libraries/application.h>
#include <libraries/blankermodule.h>
#include <libraries/screenblanker.h>
#include <proto/blankermodule.h>
#include <proto/button.h>
#include <proto/chooser.h>
#include <proto/cybergraphics.h>
#include <proto/graphics.h>
#include <proto/intuition.h>
#include <proto/layout.h>
#include <proto/label.h>
#include <proto/slider.h>
#include <proto/space.h>
#include <proto/screenblanker.h>
#include <proto/picasso96api.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#endif

// --
#include "inc_private/Types.h"
#include "inc_private/Version.h"
// --
#include "inc_private/Debug.h"
#include "inc_private/Library.h"
// --
#include "inc_private/Protos.h"
// --

#endif
