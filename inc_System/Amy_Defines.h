
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
**
******************************************************************************
** This file is part of Amy C Lib
*/

/* -- */

#ifndef AMYSYS_DEFINES_H
#define AMYSYS_DEFINES_H

// --

#ifdef __cplusplus
#define AMY_EXTERN_C_BEGIN	extern "C" {
#define AMY_EXTERN_C_END	}
#else
#define AMY_EXTERN_C_BEGIN
#define AMY_EXTERN_C_END
#endif

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
typedef void *PTR;
#endif

#ifndef STR
typedef char *STR;
#endif

#ifndef BE_SWAP16
#define BE_SWAP16(x)	(x)
#endif

#ifndef LE_SWAP16
#define LE_SWAP16(x)	( (( (x) & 0x00ff ) << 8 ) | (( (x) & 0xff00 ) >> 8 ) )
#endif

#ifndef AMY_MIN
#define AMY_MIN(a,b)	((a) < (b) ? (a) : (b))
#endif

#ifndef AMY_MAX
#define AMY_MAX(a,b)	((a) > (b) ? (a) : (b))
#endif

#ifndef AMY_ABS
#define AMY_ABS(a)		((a) < 0 ? -(a) : (a))
#endif

// --
// GCC Compiler

#if defined(__GNUC__)

#ifndef AMY_USED
#define AMY_USED	__attribute__((used))
#endif

#ifndef AMY_UNUSED
#define AMY_UNUSED	__attribute__((unused))
#endif

#ifndef AMY_FUNC	// Library Call and we want Stack only args
#define AMY_FUNC	__attribute__((libcall, linearvarargs))
#endif

#ifndef VARARGS68K
#define VARARGS68K	__attribute__((linearvarargs))
#endif

// --
// Unknown Compiler

#else

#ifndef AMY_USED
#define AMY_USED
#endif

#ifndef AMY_UNUSED
#define AMY_UNUSED
#endif

#ifndef AMY_FUNC
#define AMY_FUNC
#endif

#ifndef VARARGS68K
#define VARARGS68K
#endif

#endif

// --

#endif /* AMYSYS_DEFINES_H */
