
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/exec.h>

#include <string.h>

STRPTR	txt1 = "";
STRPTR	txt2 = "1234567890";

int main( int argc, char **argv )
{
int len;
int error;

	error = 10;

	// Null Pointer test

	#ifdef NULL_PTR_TEST
	
	len = strlen( NULL );

	if ( len != 0 )
	{
		IExec->DebugPrintF( "strnlen test 1 - failed\n" );
		goto bailout;
	}

	#endif

	// Zero size test
	len = strnlen( txt1, 25 );

	if ( len != 0 )
	{
		IExec->DebugPrintF( "strnlen test 2 - failed [ 0 != %ld ]\n", len );
		goto bailout;
	}

	// size test
	len = strnlen( txt2, 25 );

	if ( len != 10 )
	{
		IExec->DebugPrintF( "strnlen test 3 - failed [ 10 != %ld ]\n", len );
		goto bailout;
	}

	// size test
	len = strnlen( txt2, 5 );

	if ( len != 5 )
	{
		IExec->DebugPrintF( "strnlen test 4 - failed [ 5 != %ld ]\n", len );
		goto bailout;
	}

	error = 0;

bailout:

	return( error );
}

