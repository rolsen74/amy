
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

	retval = strncasecmp( NULL, "123", 3 );

	if ( retval != 0 )
	{
		IExec->DebugPrintF( "strncasecmp test 1 - failed\n" );
		goto bailout;
	}

	retval = strncasecmp( "123", NULL, 3 );

	if ( retval != 0 )
	{
		IExec->DebugPrintF( "strncasecmp test 2 - failed\n" );
		goto bailout;
	}

	retval = strncasecmp( NULL, NULL, 3 );

	if ( retval != 0 )
	{
		IExec->DebugPrintF( "strncasecmp test 3 - failed\n" );
		goto bailout;
	}

	retval = strncasecmp( NULL, "123", 0 );

	if ( retval != 0 )
	{
		IExec->DebugPrintF( "strncasecmp test 4 - failed\n" );
		goto bailout;
	}

	retval = strncasecmp( "123", NULL, 0 );

	if ( retval != 0 )
	{
		IExec->DebugPrintF( "strncasecmp test 5 - failed\n" );
		goto bailout;
	}

	retval = strncasecmp( NULL, NULL, 0 );

	if ( retval != 0 )
	{
		IExec->DebugPrintF( "strncasecmp test 6 - failed\n" );
		goto bailout;
	}

#endif

	// Same string test

	retval = strncasecmp( "", "", 100 );

	if ( retval != 0 )
	{
		IExec->DebugPrintF( "strncasecmp test 7 - failed\n" );
		goto bailout;
	}

	retval = strncasecmp( "123", "123", 100 );

	if ( retval != 0 )
	{
		IExec->DebugPrintF( "strncasecmp test 8 - failed\n" );
		goto bailout;
	}

	// Minus length test

	retval = strncasecmp( "123", "123", -100 );

	if ( retval != 0 )
	{
		IExec->DebugPrintF( "strncasecmp test 9 - failed\n" );
		goto bailout;
	}

	error = 0;

bailout:

	return( error );
}

