
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/exec.h>

#include <strings.h>

int main( int argc, char **argv )
{
char buf[64];
U32 error;
U32 len;
U32 cnt;

	error = 10;

	// NULL Pointer test

	#ifdef NULL_PTR_TEST

	bzero( NULL, 32 );

	bzero( buf, 0 );

	#endif

	// --

	for( cnt=0 ; cnt<64 ; cnt++ )
	{
		buf[cnt] = 0xac;
	}

	bzero( buf, 32 );

	len = 0;

	while( len < 64 )
	{
		if ( buf[len] == 0 )
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
		IExec->DebugPrintF( "bzero failed\n" );
		goto bailout;
	}

	error = 0;

bailout:

	return( error );
}

