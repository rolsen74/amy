
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

#ifndef AMYSYS_SYS_TYPES_H
#define AMYSYS_SYS_TYPES_H

/****************************************************************************/

#include <Amy_Defines.h>

/****************************************************************************/

// file block cnt
typedef signed int blkcnt_t;

// file block size
typedef signed int blksize_t;

typedef unsigned long long clock_t;

typedef unsigned int clockid_t;

typedef unsigned int dev_t;

typedef unsigned int fsblkcnt_t;

typedef unsigned int fsfilcnt_t;

typedef unsigned int gid_t;

typedef unsigned int id_t;

typedef unsigned int ino_t;

typedef struct key key_t;

typedef unsigned int mode_t;

typedef unsigned int nlink_t;

// clib2 and Newlib is only 32bit
typedef long long int off_t;
typedef long long int off64_t;		// Not Official

typedef signed int pid_t;

#if 0

// Posix says these pthread are definded here and in
// pthread.h, I moved them to pthread.h

typedef ... pthread_attr_t;
typedef ...	pthread_barrier_t;
typedef ... pthread_barrierattr_t;
typedef ... pthread_cond_t;
typedef ... pthread_condattr_t;
typedef ... pthread_key_t;
typedef ... pthread_mutex_t;
typedef ... pthread_mutexattr_t;
typedef ... pthread_once_t;
typedef ... pthread_rwlock_t;
typedef ... pthread_rwlockattr_t;
typedef ... pthread_spinlock_t;
typedef ... pthread_t;

#endif

// Unsigned size
typedef unsigned int size_t;

// Signed size
typedef signed int ssize_t;

typedef long suseconds_t;

// 64bit just as OpenBsd
typedef long long time_t;

typedef signed int timer_t;

typedef struct trace_attr trace_attr_t;

typedef struct trace_event_id trace_event_id_t;

typedef struct trace_event_set trace_event_set_t;

typedef struct trace_id trace_id_t;

typedef unsigned int uid_t;

typedef unsigned int useconds_t;

/****************************************************************************/
// BSD defines

typedef unsigned char		u_char;
typedef unsigned short		u_short;
typedef unsigned int		u_int;
typedef unsigned long		u_long;

typedef   signed long long	quad_t;
typedef unsigned long long	u_quad_t;

/****************************************************************************/

#endif

