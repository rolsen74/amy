
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/exec.h>

#include <math.h>

int main( int argc, char **argv )
{
double x;
double y;
int error;

	error = 10;

	// --

	x = 100;

	y = fabs( x );

	if ( 100 != y )
	{
		IExec->DebugPrintF( "fabs test 1 - Failed\n" );
		goto bailout;
	}

	// --

	x = -100;

	y = fabs( x );

	if ( 100 != y )
	{
		IExec->DebugPrintF( "fabs test 2 - Failed\n" );
		goto bailout;
	}

	// --

	x = INFINITY;

	y = fabs( x );

	if ( isinf(y) == FALSE )
	{
		IExec->DebugPrintF( "fabs test 3 - Failed\n" );
		goto bailout;
	}

	// --

	x = NAN;

	y = fabs( x );

	if ( isnan(x) == FALSE )
	{
		IExec->DebugPrintF( "fabs test 4 - Failed\n" );
		goto bailout;
	}

	// --

	error = 0;

bailout:

	return( error );
}

