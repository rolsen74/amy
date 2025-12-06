
/*
** Based on The Open Group Base Specifications Issue 7
**
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
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

#ifndef AMYSYS_ASSERT_H
#define AMYSYS_ASSERT_H

AMY_EXTERN_C_BEGIN

/****************************************************************************/

#ifndef assert
#ifndef NDEBUG

#define assert(exp)		((void)(( exp ) ? (void)0 : ( __assert( __FILE__, __LINE__, __func__, #exp ))))

#else // NDEBUG

#define assert(ignore)	((void)0)

#endif
#endif

/****************************************************************************/

void __assert( const char *, int, const char *, const char * );

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_ASSERT_H */
