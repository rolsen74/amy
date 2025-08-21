
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/dos.h>
#include <proto/exec.h>

#include <time.h>
#include <string.h>
#include <stdio.h>

struct Tests
{
	U64		Time;
	STR		Date;
};

struct Tests tst[] =
{
{	0,				"Thu Jan  1 00:00:00 1970\n" },		// Unix Epoch Start Time
{   252460800,		"Sun Jan  1 00:00:00 1978\n" },		// Amiga Epcoh Start Time
{   283996799,		"Sun Dec 31 23:59:59 1978\n" },
{   951777030,		"Mon Feb 28 22:30:30 2000\n" },		// Before leap year
{   951795742,		"Tue Feb 29 03:42:22 2000\n" },		// leap year
{   2147483647,		"Tue Jan 19 03:14:07 2038\n" },		// int32 max
{   2147483648,		"Tue Jan 19 03:14:08 2038\n" },		// int32 max + 1
{   4294967295,		"Sun Feb  7 06:28:15 2106\n" },		// uint32 max
{   4294967296,		"Sun Feb  7 06:28:16 2106\n" },		// uint32 max +1
{   7952346061,		"Tue Jan  1 01:01:01 2222\n" },		// Way above 32bit
{	0,				NULL },
};

int main( int argc, char **argv )
{
struct tm *tm;
time_t time;
char buf[64];
S32 error;
S32 len;
S32 idx;

	error = 10;

	// --

	for( idx = 0 ; tst[idx].Date ; idx++ )
	{
		time = tst[idx].Time;

		tm = gmtime( & time );

		if ( ! tm )
		{
			IExec->DebugPrintF( "%s:%04d: strftime 1 - failed\n", __FILE__, __LINE__ );
			goto bailout;
		}

		len = strftime( buf, 64, "%a %b %e %H:%M:%S %Y\n", tm );

		if (( len != 25 ) || ( strcmp( buf, tst[idx].Date )))
		{
			IExec->DebugPrintF( "%s:%04d: strftime 2 - failed (idx : %ld)\n", __FILE__, __LINE__, idx );
			IExec->DebugPrintF( "%s:%04d: strftime 2 - failed (len : %ld)\n", __FILE__, __LINE__, len );
			IExec->DebugPrintF( "%s:%04d: strftime 2 - failed (buf : %s)\n", __FILE__, __LINE__, buf );
			IExec->DebugPrintF( "%s:%04d: strftime 2 - failed (date: %s)\n", __FILE__, __LINE__, tst[idx].Date );
			goto bailout;
		}
	}

	// --

	error = 0;

bailout:

	return( error );
}

