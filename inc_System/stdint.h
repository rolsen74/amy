
/*
** Based on The Open Group Base Specifications Issue 7
**
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025-2026 Rene W. Olsen
** Target OS: AmigaOS
**
******************************************************************************
** This file is part of Amy C Lib
*/

/* --------------------------------------------------------------------------
** Always include Amy_Features.h FIRST — this defines feature macros like
** _FILE_OFFSET_BITS and _TIME_BITS before any typedefs depend on them.
** -------------------------------------------------------------------------- 
*/

#include <Amy_Features.h>
#include <Amy_Defines.h>

#ifndef AMYSYS_STDINT_H
#define AMYSYS_STDINT_H

AMY_EXTERN_C_BEGIN

/****************************************************************************/

// Warning not finished

// Note to self.. avoid including other files
// as we we are included from Amy_Standard.h

typedef signed char			int8_t;
typedef signed short		int16_t;
typedef signed int			int32_t;
typedef signed long long	int64_t;
typedef	signed long long	intmax_t;
typedef	signed long			intptr_t;

typedef signed char			int_least8_t;
typedef signed short		int_least16_t;
typedef signed int			int_least32_t;
typedef signed long long	int_least64_t;

typedef signed int			int_fast8_t;
typedef signed int			int_fast16_t;
typedef signed int			int_fast32_t;
typedef signed long long	int_fast64_t;

typedef unsigned char		uint8_t;
typedef unsigned short		uint16_t;
typedef unsigned int		uint32_t;
typedef unsigned long long	uint64_t;
typedef	unsigned long long	uintmax_t;
typedef	unsigned long		uintptr_t;

typedef unsigned char		uint_least8_t;
typedef unsigned short		uint_least16_t;
typedef unsigned int		uint_least32_t;
typedef unsigned long long	uint_least64_t;

typedef unsigned int		uint_fast8_t;
typedef unsigned int		uint_fast16_t;
typedef unsigned int		uint_fast32_t;
typedef unsigned long long	uint_fast64_t;

#define INT8_MAX			0x7f
#define INT8_MIN			(-INT8_MAX - 1)
#define UINT8_MAX			0xffU

#define INT16_MAX			0x7fff
#define INT16_MIN			(-INT16_MAX - 1)
#define UINT16_MAX			0xffffU

#define INT32_MAX			0x7fffffff
#define INT32_MIN			(-0x7fffffff - 1)
#define UINT32_MAX			0xffffffffU

#define INT64_MAX			0x7fffffffffffffffLL
#define INT64_MIN			(-INT64_MAX - 1LL)
#define UINT64_MAX			0xffffffffffffffffULL

// This is the size of size_t
#define SIZE_MAX			UINT32_MAX

#define PTRDIFF_MIN			INT32_MIN
#define PTRDIFF_MAX			INT32_MAX

#define INTMAX_MAX			INT64_MAX
#define INTMAX_MIN 			INT64_MIN
#define UINTMAX_MAX			UINT64_MAX

#define INT_LEAST8_MIN		INT8_MIN
#define INT_LEAST8_MAX		INT8_MAX
#define UINT_LEAST8_MAX		UINT8_MAX

#define INT_LEAST16_MIN		INT16_MIN
#define INT_LEAST16_MAX		INT16_MAX
#define UINT_LEAST16_MAX	UINT16_MAX

#define INT_LEAST32_MIN		INT32_MIN
#define INT_LEAST32_MAX		INT32_MAX
#define UINT_LEAST32_MAX	UINT32_MAX

#define INT_LEAST64_MIN		INT64_MIN
#define INT_LEAST64_MAX		INT64_MAX
#define UINT_LEAST64_MAX	UINT64_MAX

#define INT_FAST8_MIN		INT32_MIN
#define INT_FAST8_MAX		INT32_MAX
#define UINT_FAST8_MAX		UINT32_MAX

#define INT_FAST16_MIN		INT32_MIN
#define INT_FAST16_MAX		INT32_MAX
#define UINT_FAST16_MAX		UINT32_MAX

#define INT_FAST32_MIN		INT32_MIN
#define INT_FAST32_MAX		INT32_MAX
#define UINT_FAST32_MAX		UINT32_MAX

#define INT_FAST64_MIN		INT64_MIN
#define INT_FAST64_MAX		INT64_MAX
#define UINT_FAST64_MAX		UINT64_MAX

#define INTPTR_MAX			INT32_MAX
#define INTPTR_MIN			INT32_MIN
#define UINTPTR_MAX			UINT32_MAX

#define INT8_C(x)			x
#define UINT8_C(x)			x##U

#define INT16_C(x)			x
#define UINT16_C(x)			x##U

#define INT32_C(x)			x
#define UINT32_C(x)			x##U

#define INT64_C(x)			x##LL
#define UINT64_C(x)			x##ULL

#define INTMAX_C(x) 		INT64_C(x)
#define UINTMAX_C(x)		UINT64_C(x)

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_STDINT_H */
