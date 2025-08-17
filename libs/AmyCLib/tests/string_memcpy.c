
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/exec.h>

#include <string.h>

char buf1[4096];
char buf2[4096];

int main( int argc, char **argv )
{
U32 error;
int len;

	error = 10;

	// NULL Pointer test

	#ifdef NULL_PTR_TEST

	memmove( NULL, buf2, 4096 );

	memmove( buf1, NULL, 4096 );

	memmove( buf1, buf1, 0 );

	#endif

	// --

	memset( buf1, 0, 1000 );

	memset( buf2, 1, 1000 );

	memcpy( buf2, buf1, 100 );

	for( len=0 ; len<1000 ; len++ )
	{
		if ( buf2[len] )
		{
			break;
		}
	}

	if ( len != 100 )
	{
		goto bailout;
	}

	// --

	error = 0;

bailout:

	return( error );
}

