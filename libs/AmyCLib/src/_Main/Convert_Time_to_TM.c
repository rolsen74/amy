
/*
** SPDX-License-Identifier: BSD-3-Clause
** Modifications (c) 2025 Rene W. Olsen
** Part of Amy C Lib
**
** Based on:
**
** Portable ISO 'C' (1994) runtime library for the Amiga computer
** Copyright (c) 2002-2015 by Olaf Barthel <obarthel (at) gmx.net>
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
**   - Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**
**   - Neither the name of Olaf Barthel nor the names of contributors
**     may be used to endorse or promote products derived from this
**     software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
** LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
** CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
** SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
** INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
** POSSIBILITY OF SUCH DAMAGE.
**
*/

// --

#include "src/All.h"

// --

static const int	NormalMonths[]	= { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
static const int	LeapMonths[]	= { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
#define				IS_LEAP(xx)		(((( xx % 4 ) == 0 ) && (( xx % 100 ) != 0 )) || (( xx % 400 ) == 0 ))

S32 AMYFUNC _generic__Priv_Convert_Time_to_TM( struct AmyCLibIFace *Self UNUSED, const time_t *time, struct tm *tm )
{
const int *ptr;
time_t t;
S32 retval;
S32 year;
S32 days;
S32 d;

	retval = FALSE;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Convert_Time_to_TM : Time %p, TM %p\n", time, tm ); );

	if ( ! time )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Convert_Time_to_TM : NULL Pointer\n" ); );
		goto bailout;
	}

	if ( ! tm )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Convert_Time_to_TM : NULL Pointer\n" ); );
		goto bailout;
	}

	t = *time;

	if ( t < 0 )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Convert_Time_to_TM : Invalid time\n" ); );
		goto bailout;
	}

	tm->tm_sec		= t % 60;	t /= 60;
	tm->tm_min		= t % 60;	t /= 60;
	tm->tm_hour		= t % 24;	t /= 24;
	tm->tm_wday		= ( t + 4 ) % 7;

	// Days since 1/1/1970
	days	= t;
	year	= 1970;

	while( TRUE )
	{
		d = IS_LEAP( year ) ? 366 : 365 ;

		if ( days < d )
		{
			break;
		}

		days -= d;
		year++;
	}

	tm->tm_yday		= days;
	tm->tm_mon		= 0;

	// --

	ptr = IS_LEAP( year ) ? LeapMonths : NormalMonths ;

	while( days >= ptr[ tm->tm_mon ] )
	{
		days -= ptr[ tm->tm_mon ];
		tm->tm_mon++;
	}

	// --

	tm->tm_mday		= days + 1;
	tm->tm_year		= year - 1900;
	tm->tm_isdst	= -1;


	#ifdef DEBUG

	S32 valid = tm
	&& tm->tm_mon  >= 0 && tm->tm_mon  <= 11
	&& tm->tm_mday >= 1 && tm->tm_mday <= 31
	&& tm->tm_hour >= 0 && tm->tm_hour <= 23
	&& tm->tm_min  >= 0 && tm->tm_min  <= 59
	&& tm->tm_sec  >= 0 && tm->tm_sec  <= 60;

	if ( ! valid )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Convert_Time_to_TM : Invalid output\n" );
		IExec->DebugPrintF( "tm_mon ... : %ld\n", tm->tm_mon );
		IExec->DebugPrintF( "tm_mday .. : %ld\n", tm->tm_mday );
		IExec->DebugPrintF( "tm_hour .. : %ld\n", tm->tm_hour );
		IExec->DebugPrintF( "tm_min ... : %ld\n", tm->tm_min );
		IExec->DebugPrintF( "tm_sec ... : %ld\n", tm->tm_sec );
	}

	#endif

	retval = TRUE;

bailout:

	return(	retval );
}

// --
