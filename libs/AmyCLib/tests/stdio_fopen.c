
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/exec.h>

#include <stdio.h>

int main( int argc, char **argv )
{
FILE *file;
int error;

	error = 10;

	// --

	file = fopen( "ram:delete_me", "w" );

	if ( ! file )
	{
		IExec->DebugPrintF( "fopen test 1 - Failed\n" );
		goto bailout;
	}

	fclose( file );

	// --

	error = 0;

bailout:

	return( error );
}
