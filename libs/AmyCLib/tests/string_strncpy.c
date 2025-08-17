
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/exec.h>

#include <string.h>

STR txt = "rene olsen";

char buf[256];

int main( int argc, char **argv )
{
int error;
STR str;

	error = 10;

	memset( buf, 0, 256 );

	// Null Pointer test

	#ifdef NULL_PTR_TEST

	strncpy( NULL, txt, 10 );
	strncpy( buf, NULL, 10 );
	strncpy( NULL, NULL, 10 );

	#endif

	// --

	str = strncpy( buf, txt, 10 );

	if ( str != buf )
	{
		IExec->DebugPrintF( "strncpy test 1 - failed\n" );
		goto bailout;
	}

	if ( strcmp( str, buf ))
	{
		IExec->DebugPrintF( "strncpy test 5 - failed\n" );
		goto bailout;
	}

	error = 0;

bailout:

	return( error );
}

