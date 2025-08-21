
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/exec.h>

#include <stdlib.h>

int main( int argc, char **argv )
{
int error;
int aa;
int bb;

	error = 10;

	// --

	srand( 0 );

	aa = rand();

	srand( 0 );

	bb = rand();

	if ( aa != bb )
	{
		IExec->DebugPrintF( "rand test 1 - failed\n" );
		goto bailout;
	}

	bb = rand();

	if ( aa == bb )
	{
		IExec->DebugPrintF( "rand test 2 - failed\n" );
		goto bailout;
	}

	// --

	error = 0;

bailout:

	return( error );
}

