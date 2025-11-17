
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

#ifndef AMYSYS_UTIME_H
#define AMYSYS_UTIME_H

/****************************************************************************/

#include <sys/types.h>

/****************************************************************************/

struct utimbuf
{
	time_t	actime;		/* Access time. */
	time_t	modtime;	/* Modification time. */
};

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int utime( const char *, const struct utimbuf * );

AMY_EXTERN_C_END

/****************************************************************************/

#endif
