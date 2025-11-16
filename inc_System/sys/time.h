
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

#ifndef AMYSYS_SYS_TIME_H
#define AMYSYS_SYS_TIME_H

/****************************************************************************/

// Amiga Include
#include <devices/timer.h>

#include <sys/types.h>
#include <sys/select.h>

/****************************************************************************/

#ifndef __TIMEVAL_ALREADY_DEFINED
#define __TIMEVAL_ALREADY_DEFINED

struct timeval
{
	time_t		tv_sec;			// This is 64bit, were the Amiga version is 32bit
	suseconds_t	tv_micro;
};

#else

 #error 'struct timeval' have already been defined.

#endif

#ifndef tv_secs
#define tv_secs tv_sec
#endif

#ifndef tv_usec
#define tv_usec tv_micro
#endif

struct itimerval
{
	struct timeval	it_interval;
	struct timeval	it_value;
};

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int getitimer( int, struct itimerval * );
int setitimer( int, const struct itimerval *, struct itimerval * );
int gettimeofday( struct timeval *, void * );
int select( int, fd_set *, fd_set *, fd_set *, struct timeval * );
int utimes( const char *, const struct timeval [2] );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

