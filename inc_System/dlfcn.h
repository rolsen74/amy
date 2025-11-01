
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

#ifndef AMYSYS_DLFCN_H
#define AMYSYS_DLFCN_H

/****************************************************************************/

#define RTLD_LAZY		1
#define RTLD_NOW		2
#define RTLD_GLOBAL		4
#define RTLD_LOCAL		8

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int		dlclose( void * );
char *	dlerror( void );
void *	dlopen( const char *, int );
void *	dlsym( void *, const char * );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

