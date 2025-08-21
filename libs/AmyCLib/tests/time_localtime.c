
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/dos.h>
#include <proto/exec.h>

#include <time.h>
#include <stdio.h>


struct _time
{
	time_t		time;
	int			tm_sec;		// Sec 0-60
	int			tm_min;		// Min 0-59
	int			tm_hour;	// Hour 0-23
	int			tm_mday;   	// Month Day 1-31
	int			tm_mon;		// Month 0-11
	int			tm_year;	// Years since 1900
	int			tm_wday;	// Day of week 0-6
	int			tm_yday;	// Day of Year 0-365
	int			tm_isdst;
};

enum
{
	Sun = 0,
	Mon,
	Tue,
	Wed,
	Thu,
	Fri,
	Sat
};

enum
{
	Jan = 0,
	Feb,
	Mar,
	Apr,
	May,
	Jun,
	Jul,
	Aug,
	Sep,
	Oct,
	Nov,
	Dec,
};

struct _time tsttime[] =
{
//		Time			Sec	Min Hr  MD  Mon		Year  	WD  	YD  	IsDst

	// End Amiga year date
	// Sunday  31. Dec 1978, 23:59:59  GMT-0
	{	283996799,		59,	59,	23,	31,	Dec,	1978,	  Sun,	  364,	  0 },

	// Start Linux date
	// Thusday  1. Jan 1970, 01:00:00  GMT-0
	{	0,				0,	0,	0, 	1,	Jan,	1970,	  Thu,	  0,	  0 },

	// Start Amiga date
	// Sunday   1. Jan 1978, 01:00:00  GMT-0
	{	252460800,		0,	0,	0,	1,	Jan,	1978,	  Sun,	  0,	  0 },


	// year 2000 leap year check
	// Monday  28. Feb 2000, 17:39:12  GMT-0                YearDay not checked
	{	951777030,		30,	30,	22,	28,	Feb,    2000,	  Mon,	  58,	 0 },

	// year 2000 leap year check
	// Thueday  29. Feb 2000, 03:42:22  GMT-0                YearDay not checked
	{	951795742,	    22, 42, 3, 29, Feb,    2000,     Tue,    59,    0 },


	// Maximum int32
	// Thuesday  19. Jan 2038, 03:14:07  GMT-0                YearDay not checked
	{	2147483647,		 7,	14,	 3,	19,	Jan,   2038,	 Tue,	 18,	0 },

	// Maximum int32+1
	// Thuesday 19. Jen 2038, 03:14:08  GMT-0                YearDay not checked
	{	2147483648,		 8,	14,	 3,	19,	Jan,   2038,	 Tue,	 18,	0 },

	// Maximum uint32
	// Sunday   7. Feb 2106, 06:28:15  GMT-0                YearDay not checked
	{	4294967295,		15,	28,	 6,	 7,	Feb,   2106,	 Sun,	 37,	0 },

	// Maximum uint32+1
	// Sunday   7. Feb 2106, 06:28:15  GMT-0                YearDay not checked
	{	4294967296,		16,	28,	 6,	 7,	Feb,   2106,	 Sun,	 37,	0 },

	// Way above 32bit
	// Tuesday  1. Jan 2222, 01:01:01  GMT-0                YearDay not checked
	{	7952346061,		 1,	 1,	 1,	 1,	Jan,   2222,	 Tue,	 0,	   0 },

};

int main( int argc, char **argv )
{
struct tm *tm;
time_t time;
S32 error;
S32 pos;

	error = 10;

	// --

	#ifdef NULL_PTR_TEST

	if ( localtime( NULL ) )
	{
		IExec->DebugPrintF( "%s:%04d: localtime test 1 - Failed\n", __FILE__, __LINE__ );
		goto bailout;
	}

	#endif

	// --

	pos = 0;

	for( pos=0 ; pos < sizeof( tsttime ) / sizeof( struct _time ) ; pos++ )
	{
		time = tsttime[pos].time;

		tm = localtime( & time );

		if ( ! tm )
		{
			IExec->DebugPrintF( "%s:%04d: localtime 2 - failed\n", __FILE__, __LINE__ );
			goto bailout;
		}

		if (( tm->tm_sec	!= tsttime[pos].tm_sec	 )
		||	( tm->tm_min	!= tsttime[pos].tm_min	 )
		||	( tm->tm_hour	!= tsttime[pos].tm_hour	 )
		||	( tm->tm_mday	!= tsttime[pos].tm_mday	 )
		||	( tm->tm_mon	!= tsttime[pos].tm_mon	 )
		||	( tm->tm_year	!= tsttime[pos].tm_year	- 1900 )
		||	( tm->tm_wday	!= tsttime[pos].tm_wday	 )
		||	( tm->tm_yday	!= tsttime[pos].tm_yday	 ))
//		||	( tm->tm_isdst	!= tsttime[pos].tm_isdst ))
		{
			IExec->DebugPrintF( "%s:%04d: localtime 3 - failed\n", __FILE__, __LINE__ );
			IExec->DebugPrintF( "%s:%04d: sec ... : %ld\n", __FILE__, __LINE__, tm->tm_sec );
			IExec->DebugPrintF( "%s:%04d: min ... : %ld\n", __FILE__, __LINE__, tm->tm_min );
			IExec->DebugPrintF( "%s:%04d: hour .. : %ld\n", __FILE__, __LINE__, tm->tm_hour );
			IExec->DebugPrintF( "%s:%04d: mday .. : %ld\n", __FILE__, __LINE__, tm->tm_mday );
			IExec->DebugPrintF( "%s:%04d: mon ... : %ld\n", __FILE__, __LINE__, tm->tm_mon );
			IExec->DebugPrintF( "%s:%04d: year .. : %ld\n", __FILE__, __LINE__, tm->tm_year );
			IExec->DebugPrintF( "%s:%04d: wday .. : %ld\n", __FILE__, __LINE__, tm->tm_wday );
//			  printf( "isdst . : %ld\n", tm->tm_isdst );
			goto bailout;
		}
	}

	// --

	error = 0;

bailout:

	return( error );
}

