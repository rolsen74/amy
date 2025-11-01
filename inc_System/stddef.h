
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

/* -- */

#ifndef AMYSYS_STDDEF_H
#define AMYSYS_STDDEF_H

/****************************************************************************/

AMY_EXTERN_C_BEGIN

/****************************************************************************/

#ifndef NULL
#define NULL ((void*)0)
#endif

/****************************************************************************/

typedef int ptrdiff_t;
typedef unsigned int size_t;
typedef unsigned int wchar_t;

/****************************************************************************/

#define offsetof(type, member) ((size_t)&((type *)0)->member)

/****************************************************************************/

AMY_EXTERN_C_END

#endif

