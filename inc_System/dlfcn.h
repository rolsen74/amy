
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

#ifndef AMYSYS_DLFCN_H
#define AMYSYS_DLFCN_H

/****************************************************************************/

#include <Amy_Defines.h>	// Need AMYFUNC

/****************************************************************************/

#define RTLD_LAZY		1
#define RTLD_NOW		2
#define RTLD_GLOBAL		4
#define RTLD_LOCAL		8

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int		AMYFUNC dlclose( void * );
char *	AMYFUNC dlerror( void );
void *	AMYFUNC dlopen( const char *, int );
void *	AMYFUNC dlsym( void *, const char * );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

