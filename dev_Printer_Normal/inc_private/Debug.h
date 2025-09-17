
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INC_PRIVATE_ALL_H
#error Include "inc_privatee/All.h" first
#endif

#ifndef INC_PRIVATE_DEBUG_H
#define INC_PRIVATE_DEBUG_H

// ---
// Note:
//
//  Small feature, you always need minimum 1 arg
//  even if you don't need it.. too lazy to fix
//
//  MYERROR( "Print Error Msg", 0 );
//  MYINFO(  "Print Into Msg %ld", -11 );
//  MYDEBUG( "Print Debug Msg %lu", +11 );
//
//  Change Makefile to Enable/Disable Error Types (and recompile)
// 

#if defined( DO_ERROR ) || defined( DO_INFO ) || defined( DO_DEBUG )

void VARARGS68K _MYDEBUG( U32 lvl, STR fmt, ... );

#ifdef DO_ERROR
#define MYERROR( fmt, ... )	_MYDEBUG( 2, fmt, __VA_ARGS__ )
#else
#define MYERROR( fmt, ... )	((void)0)
#endif

#ifdef DO_INFO
#define MYINFO( fmt, ... )		_MYDEBUG( 1, fmt, __VA_ARGS__ )
#else
#define MYINFO( fmt, ... )		((void)0)
#endif

#ifdef DO_DEBUG
#define MYDEBUG( fmt, ... )	_MYDEBUG( 0, fmt, __VA_ARGS__ )
#else
#define MYDEBUG( fmt, ... )	((void)0)
#endif

#else

 #define MYERROR( fmt, ... )	((void)0)
 #define MYINFO(  fmt, ... )	((void)0)
 #define MYDEBUG( fmt, ... )	((void)0)

#endif

// --

#endif
