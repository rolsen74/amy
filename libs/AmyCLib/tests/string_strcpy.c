
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

	strcpy( NULL, txt );
	strcpy( buf, NULL );
	strcpy( NULL, NULL );

	#endif

	// --

	str = strcpy( buf, txt );

	if ( str != buf )
	{
		IExec->DebugPrintF( "strcpy test 1 - failed\n" );
		goto bailout;
	}

	if ( strcmp( str, buf ))
	{
		IExec->DebugPrintF( "strcpy test 5 - failed\n" );
		goto bailout;
	}

	error = 0;

bailout:

	return( error );
}

