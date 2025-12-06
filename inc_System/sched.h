
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

#ifndef AMYSYS_SCHED_H
#define AMYSYS_SCHED_H

#include <sys/types.h>
#include <time.h>

AMY_EXTERN_C_BEGIN

/****************************************************************************/

#define SCHED_OTHER		0
#define SCHED_FIFO		1
#define SCHED_RR		2

#define SCHED_NORMAL	SCHED_OTHER

/****************************************************************************/

struct sched_param
{
	int sched_priority;
};

/****************************************************************************/

int		sched_get_priority_max( int );
int		sched_get_priority_min( int );
int		sched_getparam( pid_t, struct sched_param * );
int		sched_getscheduler( pid_t );
int		sched_rr_get_interval( pid_t, struct timespec * );
int		sched_setparam( pid_t, const struct sched_param * );
int		sched_setscheduler( pid_t, int, const struct sched_param * );
int		sched_yield( void );

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_SCHED_H */
