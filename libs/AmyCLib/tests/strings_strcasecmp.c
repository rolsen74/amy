
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
uint32 error;
int retval;

	error = 10;

	// NULL Pointer Check

#ifdef NULL_PTR_TEST

	retval = strcasecmp( NULL, "123" );

	if ( retval != 0 )
	{
		IExec->DebugPrintF( "strcasecmp test 1 - failed\n" );
		goto bailout;
	}

	retval = strcasecmp( "123", NULL );

	if ( retval != 0 )
	{
		IExec->DebugPrintF( "strcasecmp test 2 - failed\n" );
		goto bailout;
	}

	retval = strcasecmp( NULL, NULL );

	if ( retval != 0 )
	{
		IExec->DebugPrintF( "strcasecmp test 3 - failed\n" );
		goto bailout;
	}

#endif

	// Same string test

	retval = strcasecmp( "", "" );

	if ( retval != 0 )
	{
		IExec->DebugPrintF( "strcasecmp test 4 - failed\n" );
		goto bailout;
	}

	retval = strcasecmp( "123", "123" );

	if ( retval != 0 )
	{
		IExec->DebugPrintF( "strcasecmp test 5 - failed\n" );
		goto bailout;
	}

	// Case testing

	retval = strcasecmp( "abcdef", "abcdef" );

	if ( retval != 0 )
	{
		IExec->DebugPrintF( "strcasecmp test 6 - failed\n" );
		goto bailout;
	}

	retval = strcasecmp( "abcdef", "ABCDEF" );

	if ( retval != 0 )
	{
		IExec->DebugPrintF( "strcasecmp test 7 - failed\n" );
		goto bailout;
	}

	retval = strcasecmp( "ABCDEF", "abcdef" );

	if ( retval != 0 )
	{
		IExec->DebugPrintF( "strcasecmp test 8 - failed\n" );
		goto bailout;
	}

	retval = strcasecmp( "ABCDEF", "ABCDEF" );

	if ( retval != 0 )
	{
		IExec->DebugPrintF( "strcasecmp test 9 - failed\n" );
		goto bailout;
	}

	// Length testing

	retval = strcasecmp( "ABC", "ABCDEF" );

	if ( retval > 0 )
	{
		IExec->DebugPrintF( "strcasecmp test 10 - failed\n" );
		goto bailout;
	}

	retval = strcasecmp( "ABCDEF", "ABC" );

	if ( retval < 0 )
	{
		IExec->DebugPrintF( "strcasecmp test 11 - failed\n" );
		goto bailout;
	}

	error = 0;

bailout:

	return( error );
}

