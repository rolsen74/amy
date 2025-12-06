
/*
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

#ifndef AMYSYS_SYS_RESOURCE_H
#define AMYSYS_SYS_RESOURCE_H

#include <sys/time.h>

AMY_EXTERN_C_BEGIN

/****************************************************************************/
/* Resource limit constants (for compile-time compatibility only) */

#define RLIMIT_CPU		0
#define RLIMIT_FSIZE	1
#define RLIMIT_DATA		2
#define RLIMIT_STACK	3
#define RLIMIT_CORE		4
#define RLIMIT_NOFILE	5
#define RLIMIT_AS		6
#define RLIM_NLIMITS	7

#define RLIM_INFINITY	(~0UL)

/****************************************************************************/
/* Resource usage types */

#define RUSAGE_SELF		0
#define RUSAGE_CHILDREN	-1

/****************************************************************************/
/* Structures */

struct rlimit 
{
	unsigned long rlim_cur;
	unsigned long rlim_max;
};

struct rusage 
{
	struct timeval ru_utime;	/* user time used */
	struct timeval ru_stime;	/* system time used */
	long ru_maxrss;				/* maximum resident set size */
	long ru_ixrss;				/* integral shared memory size */
	long ru_idrss;				/* integral unshared data size */
	long ru_isrss;				/* integral unshared stack size */
	long ru_minflt;				/* page reclaims */
	long ru_majflt;				/* page faults */
	long ru_nswap;				/* swaps */
	long ru_inblock;			/* block input operations */
	long ru_oublock;			/* block output operations */
	long ru_msgsnd;				/* messages sent */
	long ru_msgrcv;				/* messages received */
	long ru_nsignals;			/* signals received */
	long ru_nvcsw;				/* voluntary context switches */
	long ru_nivcsw;				/* involuntary context switches */
};

/****************************************************************************/

int		getrlimit(	int resource, struct rlimit *rlp );
int		setrlimit(	int resource, const struct rlimit *rlp );
int		getrusage(	int who, struct rusage *usage );

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_SYS_RESOURCE_H */
