
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

#ifndef AMYSYS_STDDEF_H
#define AMYSYS_STDDEF_H

/****************************************************************************/

#include <Amy_Defines.h>

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

