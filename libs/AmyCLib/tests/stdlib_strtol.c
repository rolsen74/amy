
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/exec.h>

#include <stdlib.h>

char str[] = "2030300 This is a test";

int main( int argc, char **argv )
{
char *ptr;
long val;
int error;

	error = 10;

	// --

	val = strtol( str, & ptr, 10 );

	if ( val != 2030300 )
	{
		IExec->DebugPrintF( "strtol test 1 - failed\n" );
		goto bailout;
	}

	if ( ptr != &str[7] )
	{
		IExec->DebugPrintF( "strtol test 2 - failed\n" );
		goto bailout;
	}

	// --

	error = 0;

bailout:

	return( error );
}

