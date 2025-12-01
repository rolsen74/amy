
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

#ifndef AMYSYS_SYS_TIMES_H
#define AMYSYS_SYS_TIMES_H

/****************************************************************************/

#include <sys/types.h>

/****************************************************************************/

struct tms
{
	clock_t		tms_utime;
	clock_t		tms_stime;
	clock_t		tms_cutime;
	clock_t		tms_cstime;
};

/****************************************************************************/

AMY_EXTERN_C_BEGIN

clock_t	times( struct tms * );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

