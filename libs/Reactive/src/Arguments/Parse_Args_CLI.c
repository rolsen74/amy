
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

static PTR Handle_CLIArgs( struct ReactivePrivIFace *Self, struct RAArguments *args, STR clistr, U32 *error )
{
S32 arraycnt;
PTR retval;
S32 start;
S32 cnt;
STR *array;
U32 len;
U32 pos;
STR str;
STR s1;
STR s2;
STR s3;
STR s;
U8 chr;

//	IExec->DebugPrintF( "RA_Arguments_ParseList : Handle_CLIArgs\n" );

	array	= NULL;
	retval	= NULL;
	arraycnt = 0;

	if ( ! clistr )
	{
		goto bailout;
	}

	// -- Max Arguments

	pos = 0;
	str = clistr;

	// Count Arguments
	while(( str[pos] ) && ( str[pos] != 10 ))
	{
		if (( str[pos] == '"' ) || ( str[pos] == '\'' ) || ( str[pos] == '`' ))
		{
			chr = str[pos++];

			while(( str[pos] ) && ( str[pos] != chr ))
			{
				pos++;
			}

			if ( str[pos] == chr )
			{
				pos++;
			}
		}
		else
		{
			while(( str[pos] ) && ( str[pos] != 9 ) && ( str[pos] != 10 ) && ( str[pos] != 32 ))
			{
				pos++;
			}
		}

		while(( str[pos] == 9 ) || ( str[pos] == 10 ) || ( str[pos] == 32 ))
		{
			pos++;
		}

		arraycnt++;
	}

	// --

	len = sizeof( PTR ) * ( arraycnt + 2 );

	array = malloc( len );

	if ( ! array )
	{
		*error = RAV_General_OutOfMemory;
		goto bailout;
	}

	// --

	cnt = 0;
	pos = 0;

	// Count Arguments

	while( str[pos] )
	{
		if (( str[pos] == '"' ) || ( str[pos] == '\'' ) || ( str[pos] == '`' ))
		{
			chr = str[pos++];

			start = pos;

			while(( str[pos] ) && ( str[pos] != chr ))
			{
				pos++;
			}

			len = pos - start;

			array[cnt] = malloc( len + 1 );

			if ( ! array[cnt] )
			{
				*error = RAV_General_OutOfMemory;
				goto bailout;
			}

			s = array[cnt];

			memcpy( s, &str[start], len );

			s[len] = 0;

			if ( str[pos] == chr )
			{
				pos++;
			}
		}
		else
		{
			start = pos;

			while(( str[pos] ) && ( str[pos] != 9 ) && ( str[pos] != 10 ) && ( str[pos] != 32 ))
			{
				pos++;
			}

			len = pos - start;

			array[cnt] = malloc( len + 1 );

			if ( ! array[cnt] )
			{
				*error = RAV_General_OutOfMemory;
				goto bailout;
			}

			s = array[cnt];

			memcpy( s, &str[start], len );

			s[ len ] = 0;
		}

		while(( str[pos] == 9 ) || ( str[pos] == 10 ) || ( str[pos] == 32 ))
		{
			pos++;
		}

		cnt++;
	}

	// Join Strings

	pos = 0;

	for( cnt=0 ; cnt<arraycnt ; cnt++ )
	{
		s1 = array[ cnt + 0 ];
		s2 = array[ cnt + 1 ];
		s3 = array[ cnt + 2 ];

		// --

		len = strlen( s1 );

		if (( s1[ len - 1 ] == '=' )
		|| (( s2 ) && ( s2[0] == '=' ) && ( s2[1] != 0 )))
		{
			str = NULL;

			asprintf( & str, "%s%s", s1, s2 );

			if ( ! str )
			{
				*error = RAV_General_OutOfMemory;
				goto bailout;
			}

			free( s1 );
			free( s2 );

			array[cnt+0] = NULL;
			array[cnt+1] = NULL;
			array[pos] = str;
			cnt += 1;
		}
		else if (( s2 ) && ( s2[0] == '=' ) && ( s2[1] == 0 ))
		{
			str = NULL;

			asprintf( & str, "%s%s%s", s1, s2, s3 );

			if ( ! str )
			{
				*error = RAV_General_OutOfMemory;
				goto bailout;
			}

			free( s1 );
			free( s2 );
			free( s3 );

			array[cnt+0] = NULL;
			array[cnt+1] = NULL;
			array[cnt+2] = NULL;
			array[pos] = str;
			cnt += 2;
		}

		pos++;
	}

	// --

	retval = Handle_Options( Self, args, pos, array, error, FALSE );

	// --

bailout:

	// --

	if ( array )
	{
		for( cnt=0 ; cnt<arraycnt ; cnt++ )
		{
			if ( array[cnt] )
			{
				free( array[cnt] );
			}
		}

		free( array );
	}

	// --

	return(	retval );
}

// --
