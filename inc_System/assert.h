
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

#ifndef AMYSYS_ASSERT_H
#define AMYSYS_ASSERT_H

/****************************************************************************/

#include <Amy_Defines.h>	// Need AMY_EXTERN_C_BEGIN

/****************************************************************************/

#ifndef assert
#ifndef NDEBUG

#define assert(exp)		((void)(( exp ) ? (void)0 : ( __assert( __FILE__, __LINE__, __func__, #exp ))))

#else // NDEBUG

#define assert(ignore)	((void)0)

#endif
#endif

/****************************************************************************/

AMY_EXTERN_C_BEGIN

void __assert( const char *, int, const char *, const char * );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

