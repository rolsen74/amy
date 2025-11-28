
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
#include <Amy_Public.h>

/* -- */

#ifndef AMYSYS_TIME_H
#define AMYSYS_TIME_H

/****************************************************************************/

#include <locale.h>
#include <sys/types.h>

/****************************************************************************/

#define CLOCKS_PER_SEC				50

#define CLOCK_MONOTONIC				0
#define CLOCK_REALTIME				1
#define CLOCK_PROCESS_CPUTIME_ID	2
#define CLOCK_THREAD_CPUTIME_ID		3

#define TIMER_ABSTIME				0

/****************************************************************************/

struct tm
{
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

struct timespec
{
	time_t	tv_sec;
	long	tv_nsec;
};

struct itimerspec
{
	struct timespec	it_interval;
	struct timespec	it_value;
};

/****************************************************************************/
/* Legacy BSD/GNU timezone structure (used by gettimeofday) */

struct timezone
{
	int tz_minuteswest;
	int tz_dsttime;
};

/****************************************************************************/

// hmm can't define timezone this way
//#define daylight		AmyCLibPublic->ra_daylight
//#define timezone		AmyCLibPublic->ra_timezone
//#define tzname			AmyCLibPublic->ra_tzname

/****************************************************************************/

struct sigevent;

AMY_EXTERN_C_BEGIN

char *		asctime( const struct tm * );
char *		asctime_r( const struct tm *, char * );
clock_t		clock( void );
int			clock_getcpuclockid( pid_t, clockid_t );
int			clock_getres( clockid_t, struct timespec * );
int			clock_gettime( clockid_t, struct timespec * );
int			clock_nanosleep( clockid_t, int, const struct timespec *, struct timespec * );
int			clock_settime( clockid_t, const struct timespec * );
char *		ctime( const time_t * );
char *		ctime_r( const time_t *, char * );
double		difftime( time_t, time_t );
struct tm *	getdate( const char * );
struct tm *	gmtime( const time_t * );
struct tm *	gmtime_r( const time_t *, struct tm * );
struct tm *	localtime( const time_t * );
struct tm *	localtime_r( const time_t *, struct tm * );
time_t		mktime( struct tm * );
int			nanosleep( const struct timespec *, struct timespec * );
size_t		strftime( char *, size_t, const char *, const struct tm * );
size_t		strftime_l( char *, size_t, const char *, const struct tm *, locale_t );
char *		strptime( const char *, const char *, struct tm * );
time_t		time( time_t * );
time_t		timegm( struct tm * );
int			timer_create( clockid_t, struct sigevent *, timer_t * );
int			timer_delete( timer_t );
int			timer_gettime( timer_t, struct itimerspec * );
int			timer_getoverrun( timer_t );
int			timer_settime( timer_t, int, const struct itimerspec *, struct itimerspec * );
void		tzset( void );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

