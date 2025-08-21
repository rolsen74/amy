
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

enum myWriteStat
{
	MWS_Okay,	// Write okay
	MWS_Error,	// Write failed, buffer full
};

struct Intern
{
	struct tm *	tm;
	U32			max;
	STR			fmt;
	STR			buffer;
	U32			bufferPos;
//	struct AmyCLibPrivIFace *Self;
};

// English (non-locale) abbreviations
static const STR MonAbbr[12] =
{
	"Jan","Feb","Mar","Apr","May","Jun",
	"Jul","Aug","Sep","Oct","Nov","Dec"
};

// English (non-locale) abbreviations
static const char *WeekdayAbbr[7] = 
{
	"Sun","Mon","Tue","Wed","Thu","Fri","Sat"
};

// --

static enum myWriteStat myWrite_Char( struct Intern *in, S32 c )
{
enum myWriteStat stat;
U32 pos;

	pos = in->bufferPos;

	if ( pos < in->max )
	{
		in->buffer[pos++] = c;
		in->bufferPos = pos;
		stat = MWS_Okay;
	}
	else
	{
		#ifdef DEBUG
		IExec->DebugPrintF( "strftime : myWrite_Char : Buffer full : Pos %ld : Max %ld\n", pos, in->max );
		#endif

		stat = MWS_Error;
	}

	return( stat );
}

// --

static enum myWriteStat myWrite_2d( struct Intern *in, int v )
{
enum myWriteStat stat;
char b;
int val;

	// clamp to 0..99 for safety

	/**/ if ( v < 0 )
	{
		v = 0; 
	} 
	else if ( v > 99 )
	{
		v = 99;
	}

	// --

	val = ( v / 10 );
	b = ( val ) ? '0' + val : ' ' ;

	stat = myWrite_Char( in, b );

	if ( stat != MWS_Error )
	{
		b = (char)( '0' + ( v % 10 ));

		stat = myWrite_Char( in, b );
	}

	return( stat );
}

// --

static enum myWriteStat myWrite_02d( struct Intern *in, int v )
{
enum myWriteStat stat;
char b;

	// clamp to 0..99 for safety

	/**/ if ( v < 0 )
	{
		v = 0; 
	} 
	else if ( v > 99 )
	{
		v = 99;
	}

	// --

	b = (char)( '0' + ( v / 10 ));

	stat = myWrite_Char( in, b );

	if ( stat != MWS_Error )
	{
		b = (char)( '0' + ( v % 10 ));

		stat = myWrite_Char( in, b );
	}

	return( stat );
}

// --

static enum myWriteStat myWrite_Str( struct Intern *in, STR str )
{
enum myWriteStat stat;
S32 c;

	stat = MWS_Okay;

	while( TRUE )
	{
		c = *str++;

		if ( ! c )
		{
			break;
		}

		stat = myWrite_Char( in, c );

		if ( stat == MWS_Error )
		{
			break;
		}
	}

	return( stat );
}

// --
// simple signed decimal (for %Y)

static enum myWriteStat myWrite_Int( struct Intern *in, S32 v )
{
enum myWriteStat stat;
char buf[16];
S32 i;
U32 u;

	i = sizeof( buf ) - 1;

	u = ( v < 0 ) ? (unsigned)(-v) : (unsigned)v;

	buf[i] = '\0';

	do 
	{ 
		buf[--i] = (char)('0' + (u % 10)); 
		u /= 10; 
	} 
	while( u );

	if ( v < 0 ) 
	{
		buf[--i] = '-';
	}

	stat = myWrite_Str( in, & buf[i] );

	return( stat );
}

// --

static S32 __handle( struct Intern *in )
{
enum myWriteStat stat;
struct tm *tm;
S32 retval;
STR fmt;
U32 pos;
S32 c;

	retval = 0; // error

	// -- 
	// Validate Max buffer size

	if ( in->max <= 0 )
	{
		#ifdef DEBUG
		IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
		#endif
		goto bailout;
	}

	// make space for NUL
	in->max--;

	// --
	// Validate Time
	// check only when used

	tm = in->tm;

	#ifdef DEBUG
	if ( ! tm )
	{
		#ifdef DEBUG
		IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
		#endif
		goto bailout;
	}
	#endif

	// --
	// Validate Format string

	fmt = in->fmt;

	if ( ! fmt )
	{
		#ifdef DEBUG
		IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
		#endif
		goto bailout;
	}

	pos = 0;

	while( TRUE )
	{
		c = fmt[pos++];

		if ( ! c )
		{
			// Done
			break;
		}

		if ( c != '%' )
		{
			stat = myWrite_Char( in, c );

			if ( stat == MWS_Error )
			{
				#ifdef DEBUG
				IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
				#endif
				goto bailout;
			}

			continue;
		}

		c = fmt[pos++];

		switch( c )
		{
			case '%': // "%%"
			{
				IExec->DebugPrintF( "strftime : %%\n" );

				if ( myWrite_Char( in, '%' ) == MWS_Error )
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}
				break;
			}

			// ---

			case 'H': // 00..23
			{
				if ( ! tm )	goto bailout;

				IExec->DebugPrintF( "strftime : H : %ld\n", tm->tm_hour );

				if ( myWrite_02d( in, tm->tm_hour ) == MWS_Error )
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}
				break;
			}

			case 'M': // 00..59
			{
				if ( ! tm )	goto bailout;

				IExec->DebugPrintF( "strftime : M : %ld\n", tm->tm_min );

				if ( myWrite_02d( in, tm->tm_min ) == MWS_Error )
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}
				break;
			}

			case 'S': // 00..60 (inc leap)
			{
				if ( ! tm )	goto bailout;

				IExec->DebugPrintF( "strftime : S : %ld\n", tm->tm_sec );

				if ( myWrite_02d( in, tm->tm_sec ) == MWS_Error )
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}
				break;
			}

			case 'Y': // full year
			{
				if ( ! tm )	goto bailout;

				IExec->DebugPrintF( "strftime : Y : %ld\n", tm->tm_year );

				if ( myWrite_Int( in, tm->tm_year+1900 ) == MWS_Error )
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}
				break;
			}

			// ---

			case 'a': // Weekday
			{
				if ( ! tm )	goto bailout;

				IExec->DebugPrintF( "strftime : a : %ld\n", tm->tm_mon );

				S32 m = tm->tm_wday; // 0..6, Sun=0

				if (( m < 0 ) || ( m > 6 ))	goto bailout;

				if ( myWrite_Str( in, (STR) WeekdayAbbr[m] ) == MWS_Error )
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}
				break;
			}

			case 'b': // Jan..Dec
			{
				if ( ! tm )	goto bailout;

				IExec->DebugPrintF( "strftime : b : %ld\n", tm->tm_mon );

				S32 m = tm->tm_mon; // 0..11

				if (( m < 0 ) || ( m > 11 ))	goto bailout;

				if ( myWrite_Str( in, (STR) MonAbbr[m] ) == MWS_Error )
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}
				break;
			}

			case 'd': // 01..31
			{
				if ( ! tm )	goto bailout;

				IExec->DebugPrintF( "strftime : d : %ld\n", tm->tm_mday );

				if ( myWrite_02d( in, tm->tm_mday ) == MWS_Error )
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}
				break;
			}

			case 'e': // 01..31
			{
				if ( ! tm )	goto bailout;

				IExec->DebugPrintF( "strftime : e : %ld\n", tm->tm_mday );

				if ( myWrite_2d( in, tm->tm_mday ) == MWS_Error )
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}
				break;
			}

			case 'm': // 01..12
			{
				if ( ! tm )	goto bailout;

				IExec->DebugPrintF( "strftime : m : %ld\n", tm->tm_mon );

				if ( myWrite_02d( in, tm->tm_mon+1 ) == MWS_Error )
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}
				break;
			}

			// ---

			default:
			{
				#ifdef DEBUG
				IExec->DebugPrintF( "%s:%04d: Unsupported type %c (%ld)\n", __FILE__, __LINE__, c, c );
				#endif
				goto bailout;
			}
		}
	}

	// --
	// so we can write NUL
	in->max++;

	// --
	// Write NUL terminator
	stat = myWrite_Char( in, 0 );

	if ( stat == MWS_Error )
	{
		#ifdef DEBUG
		IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
		#endif
		goto bailout;
	}

	// Written bytes minus NUL
	retval = in->bufferPos - 1;

bailout:

	if (( ! retval ) && ( in->buffer ))
	{
		// if error and we have a buffer
		// lets just write a NUL terminator
//		in->buffer[0] = 0;
		in->buffer[ in->bufferPos ] = 0;
	}

	return( retval );
}

// generic version without Locale
size_t AMYFUNC _generic_time_strftime( struct AmyCLibPrivIFace *Self, char *s, size_t size, const char *format, const struct tm *timeptr )
{
struct Intern in;
size_t retval;

	IExec->DebugPrintF( "_generic_time_strftime : Buf %p, Size %ld, Fmt '%s', TM %p\n", s, size, format, timeptr );

	DOFUNCTIONLOG( LOG_FUNC_strftime );

	if ( size > 0 )
	{
		Self->string_memset( & in, 0, sizeof( in ));
		in.tm = (PTR) timeptr;
		in.fmt = (PTR) format;
		in.max = size;
		in.buffer = s;

		retval = __handle( & in );
	}
	else
	{
		// if Size is Zero
		retval = 0;
	}

	IExec->DebugPrintF( "_generic_time_strftime : Exit : Retval %ld, Buf %s\n", retval, s );

	return( retval );
}

// --
