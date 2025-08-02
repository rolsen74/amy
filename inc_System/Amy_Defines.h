
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
**
******************************************************************************
** This file is part of Amy C Lib
*/

#ifndef AMYSYS_DEFINES_H
#define AMYSYS_DEFINES_H

// --

#include <stdint.h>

// --

#ifndef U8
typedef uint8_t U8;
#endif

#ifndef U16
typedef uint16_t U16;
#endif

#ifndef U32
typedef uint32_t U32;
#endif

#ifndef U64
typedef uint64_t U64;
#endif

#ifndef S8
typedef int8_t S8;
#endif

#ifndef S16
typedef int16_t S16;
#endif

#ifndef S32
typedef int32_t S32;
#endif

#ifndef S64
typedef int64_t S64;
#endif

#ifndef PTR
typedef void* PTR;
#endif

#ifndef STR
typedef char* STR;
#endif

#ifndef BE_SWAP16
#define BE_SWAP16(x)	(x)
#endif

#ifndef LE_SWAP16
#define LE_SWAP16(x)	( (( (x) & 0x00ff ) << 8 ) | (( (x) & 0xff00 ) >> 8 ) )
#endif

// --
// GCC Compiler

#if defined(__GNUC__)

#ifndef MIN
#define MIN(a,b) ({ __typeof__(a) _a = (a); __typeof__(b) _b = (b); _a < _b ? _a : _b; })
#endif

#ifndef MAX
#define MAX(a,b) ({ __typeof__(a) _a = (a); __typeof__(b) _b = (b); _a > _b ? _a : _b; })
#endif

#ifndef ABS
#define ABS(x) ({ __typeof__(x) _x = (x); _x < 0 ? -_x : _x; })
#endif

#ifndef USED
#define USED __attribute__((used))
#endif

#ifndef UNUSED
#define UNUSED __attribute__((unused))
#endif

#ifndef AMYFUNC	// Library Call and we want Stack only args
#define AMYFUNC __attribute__((libcall, linearvarargs))
#endif

#ifndef VARARGS68K
#define VARARGS68K __attribute__((linearvarargs))
#endif

// --
// Unknown Compiler

#else

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif

#ifndef ABS
#define ABS(x)   ((x) < 0 ? -(x) : (x))
#endif
#ifndef USED
#define USED
#endif

#ifndef UNUSED
#define UNUSED
#endif

#ifndef AMYFUNC
#define AMYFUNC
#endif

#ifndef VARARGS68K
#define VARARGS68K
#endif

#endif

// --

#endif
