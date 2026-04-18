
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025-2026 Rene W. Olsen
** Target OS: AmigaOS
**
******************************************************************************
** This file is part of Amy C Lib
*/

/* -- */

#ifndef AMYSYS_DEFINES_H
#define AMYSYS_DEFINES_H

// --

// --

#ifdef __cplusplus

# define AMY_EXTERN_C_BEGIN extern "C" {
# define AMY_EXTERN_C_END   }
# define AMY_STATIC_ASSERT(x) static_assert((x), #x)

#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)

# define AMY_EXTERN_C_BEGIN
# define AMY_EXTERN_C_END
# define AMY_STATIC_ASSERT(x) _Static_assert((x), #x)

#else

# define AMY_EXTERN_C_BEGIN
# define AMY_EXTERN_C_END
# define AMY_STATIC_ASSERT(x) typedef char amy_static_assert_##__LINE__[(x) ? 1 : -1]

#endif

// --

#include <stdint.h>

// --

typedef uint8_t		AMY_U8;
typedef uint16_t	AMY_U16;
typedef uint32_t	AMY_U32;
typedef uint64_t	AMY_U64;

typedef int8_t		AMY_S8;
typedef int16_t		AMY_S16;
typedef int32_t		AMY_S32;
typedef int64_t		AMY_S64;

typedef void *		AMY_PTR;
typedef char *		AMY_STR;
typedef const char *AMY_CSTR;

#ifdef AMY_SHORT_NAMES

#ifndef U8
#define U8			AMY_U8
#endif

#ifndef U16
#define U16			AMY_U16
#endif

#ifndef U32
#define U32			AMY_U32
#endif

#ifndef U64
#define U64			AMY_U64
#endif

#ifndef S8
#define S8			AMY_S8
#endif

#ifndef S16
#define S16			AMY_S16
#endif

#ifndef S32
#define S32			AMY_S32
#endif

#ifndef S64
#define S64			AMY_S64
#endif

#ifndef PTR
#define PTR			AMY_PTR
#endif

#ifndef STR
#define STR			AMY_STR
#endif

#ifndef CSTR
#define CSTR		AMY_CSTR
#endif

#endif

// --
// Hardcoded for Big-Endian (for now)

#define BE_SWAP16(x)	(x)
#define BE_SWAP32(x)	(x)
#define BE_SWAP64(x)	(x)

// --
// GCC Compiler

#if defined(__GNUC__) || defined(__clang__)

#ifndef AMY_USED
#define AMY_USED		__attribute__((used))
#endif

#ifndef AMY_UNUSED
#define AMY_UNUSED		__attribute__((unused))
#endif

#ifndef AMY_FUNC		// Library Call and we want Stack only args
#define AMY_FUNC		__attribute__((libcall, linearvarargs))
#endif

#ifndef VARARGS68K
#define VARARGS68K		__attribute__((linearvarargs))
#endif

#define AMY_MIN(a,b)	({ __typeof__(a) _a = (a); __typeof__(b) _b = (b); _a < _b ? _a : _b; })
#define AMY_MAX(a,b)	({ __typeof__(a) _a = (a); __typeof__(b) _b = (b); _a > _b ? _a : _b; })
#define AMY_ABS(a)		({ __typeof__(a) _a = (a); _a < 0 ? -_a : _a; })

#define LE_SWAP16(x)	({ U16 _x = (U16)(x); ((_x << 8) | (_x >> 8)); })

#define LE_SWAP32(x)	({ U32 _x = (U32)(x); \
	((_x << 24) | \
	 ((_x << 8) & 0x00FF0000UL) | \
	 ((_x >> 8) & 0x0000FF00UL) | \
	 (_x >> 24)); \
})

#define LE_SWAP64(x)	({ U64 _x = (U64)(x); \
	((_x << 56) | \
	 ((_x << 40) & 0x00FF000000000000ULL) | \
	 ((_x << 24) & 0x0000FF0000000000ULL) | \
	 ((_x << 8)  & 0x000000FF00000000ULL) | \
	 ((_x >> 8)  & 0x00000000FF000000ULL) | \
	 ((_x >> 24) & 0x0000000000FF0000ULL) | \
	 ((_x >> 40) & 0x000000000000FF00ULL) | \
	 (_x >> 56)); \
})

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

#define AMY_MIN(a,b)	((a) < (b) ? (a) : (b))
#define AMY_MAX(a,b)	((a) > (b) ? (a) : (b))
#define AMY_ABS(a)		((a) < 0 ? -(a) : (a))

#define LE_SWAP16(x)	( (( (x) & 0x00ffU ) << 8 ) \
						| (( (x) & 0xff00U ) >> 8 ) )

#define LE_SWAP32(x)	( (( (x) & 0x000000ffUL ) << 24 ) \
						| (( (x) & 0x0000ff00UL ) <<  8 ) \
						| (( (x) & 0x00ff0000UL ) >>  8 ) \
						| (( (x) & 0xff000000UL ) >> 24 ) )

#define LE_SWAP64(x)	( (( (x) & 0x00000000000000ffULL ) << 56 ) \
						| (( (x) & 0x000000000000ff00ULL ) << 40 ) \
						| (( (x) & 0x0000000000ff0000ULL ) << 24 ) \
						| (( (x) & 0x00000000ff000000ULL ) <<  8 ) \
						| (( (x) & 0x000000ff00000000ULL ) >>  8 ) \
						| (( (x) & 0x0000ff0000000000ULL ) >> 24 ) \
						| (( (x) & 0x00ff000000000000ULL ) >> 40 ) \
						| (( (x) & 0xff00000000000000ULL ) >> 56 ) )

#endif

// --

#endif /* AMYSYS_DEFINES_H */
