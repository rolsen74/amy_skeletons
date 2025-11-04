
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INC_PRIVATE_ALL_H
#error Include "inc_private/All.h" first
#endif

#ifndef INC_PRIVATE_USB_H
#define INC_PRIVATE_USB_H

// --

struct USBStruct
{
	struct USBFDStartupMsg *	StartMsg;
	struct UsbInterface *		Interface;
	U32							Interface_Bit;
	struct MsgPort *			Interface_MsgPort;
	S32							Running;
};

// --

#endif /* INC_PRIVATE_USB_H */

