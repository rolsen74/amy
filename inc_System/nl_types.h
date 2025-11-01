
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

#ifndef AMYSYS_NL_TYPES_H
#define AMYSYS_NL_TYPES_H

/****************************************************************************/

typedef struct _nl_catd
{
	void *	__data;
	int		__size;

} *nl_catd;

#define NL_SETD			1
#define NL_CAT_LOCALE	1

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int		catclose( nl_catd );
char *	catgets( nl_catd, int, int, const char * );
nl_catd	catopen( const char *, int );

AMY_EXTERN_C_END

/****************************************************************************/

#endif
