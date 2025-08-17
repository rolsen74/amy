
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/exec.h>

#include <string.h>

int main( int argc, char **argv )
{
char buf[64];
U32 error;
U32 len;
U32 cnt;

	error = 10;

	// NULL Pointer test

	#ifdef NULL_PTR_TEST

	memset( NULL, 0, 32 );

	memset( buf, 0, 0 );

	#endif

	// --

	for( cnt=0 ; cnt<64 ; cnt++ )
	{
		buf[cnt] = 0xac;
	}

	memset( buf, 12, 32 );

	len = 0;

	while( len < 64 )
	{
		if ( buf[len] == 12 )
		{
			len++;
		}
		else
		{
			break;
		}
	}

	if ( len != 32 )
	{
		IExec->DebugPrintF( "memset failed\n" );
		goto bailout;
	}

	error = 0;

bailout:

	return( error );
}
