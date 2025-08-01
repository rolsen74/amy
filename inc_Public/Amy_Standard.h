
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef __AMY_STANDARD_H__
#define __AMY_STANDARD_H__

// --

#include <proto/exec.h>

#include <inttypes.h>

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

#ifndef LE_SWAP16
#define LE_SWAP16(x)	( (( (x) & 0x00ff ) << 8 ) | (( (x) & 0xff00 ) >> 8 ) )
#endif

#ifndef BE_SWAP16
#define BE_SWAP16(x)	(x)
#endif

// --
// GCC Compiler

#if defined(__GNUC__)

#ifndef USED
#define USED __attribute__((used))
#endif

#ifndef UNUSED
#define UNUSED __attribute__((unused))
#endif

// --
// Unknown Compiler

#else

#ifndef USED
#define USED
#endif

#ifndef UNUSED
#define UNUSED
#endif

#endif

// --

#endif
