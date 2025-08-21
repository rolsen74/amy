
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
double xx;
int error;

	error = 10;

	xx = nan( NULL );

	if ( isnan( xx ) == FALSE )
	{
		IExec->DebugPrintF( "isnan test 1 - Failed\n" );
		goto bailout;
	}

	error = 0;

bailout:

	return( error );
}

