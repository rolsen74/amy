
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
int x;

	error = 10;

	// --

	x = atoi( "+9" );

	if ( x != 9 )
	{
		IExec->DebugPrintF( "atoi test 1 - Failed\n" );
		goto bailout;
	}

	x = atoi( "-123" );

	if ( x != -123 )
	{
		IExec->DebugPrintF( "atoi test 2 - Failed\n" );
		goto bailout;
	}

	// --

	error = 0;

bailout:

	return( error );
}
