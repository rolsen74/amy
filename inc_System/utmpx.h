
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

#ifndef AMYSYS_UTMPX_H
#define AMYSYS_UTMPX_H

#include <sys/types.h>
#include <sys/time.h>

AMY_EXTERN_C_BEGIN

/****************************************************************************/
// Must match utmp.h

#define EMPTY			0
#define RUN_LVL			1
#define BOOT_TIME		2
#define NEW_TIME		3
#define OLD_TIME		4
#define INIT_PROCESS	5
#define LOGIN_PROCESS	6
#define USER_PROCESS	7
#define DEAD_PROCESS	8

/****************************************************************************/

#define __UT_IDSIZE		4
#define __UT_NAMESIZE	32
#define __UT_LINESIZE	32
#define __UT_HOSTSIZE	256

struct utmpx
{
	short			ut_type;
	pid_t			ut_pid;
	char			ut_id[__UT_IDSIZE];
	char			ut_line[__UT_LINESIZE];
	char			ut_user[__UT_NAMESIZE];
	char			ut_host[__UT_HOSTSIZE];
	struct timeval	ut_tv;
};

/****************************************************************************/

void			endutxent( void );
struct utmpx *	getutxent( void );
struct utmpx *	getutxid( const struct utmpx * );
struct utmpx *	getutxline( const struct utmpx * );
struct utmpx *	pututxline( const struct utmpx * );
void			setutxent( void );

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_UTMPX_H */
