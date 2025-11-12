
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INC_PRIVATE_ALL_H
#error Include "inc_private/All.h" first
#endif

#ifndef INC_PRIVATE_TASK_H
#define INC_PRIVATE_TASK_H

// --

enum TaskState
{
	TASK_State_Stopped,
	TASK_State_Starting,
	TASK_State_Running,
	TASK_State_Stopping,
};

// --
struct SANA2Unit;

struct TaskStartMsg
{
	U32						Result;
	PTR						Parent;
	U32						Mask;
	struct SANA2Unit *		Unit;
};

// --

#endif
