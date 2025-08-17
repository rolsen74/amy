
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/exec.h>

#include <string.h>

// Well gcc likes to merge txt1 and txt2
// and gcc's build strncmp do not like NULL Pointers
// so use -fno-builtin or remove NULL_PTR_TEST

STR	txt1 = "rene olsen";
STR	txt2 = "rene olsen";
STR	txt3 = "rene Olsen";
STR	txt4 = "rene olsen dk";

int main( int argc, char **argv )
{
int stat;
int error;

	error = 10;

	// Null Pointer test

	#ifdef NULL_PTR_TEST

	stat = strncmp( NULL, txt1, 10 );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "strncmp test 1 - failed\n" );
		goto bailout;
	}

	stat = strncmp( txt1, NULL, 10 );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "strncmp test 2 - failed\n" );
		goto bailout;
	}

	stat = strncmp( NULL, NULL, 10 );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "strncmp test 3 - failed\n" );
		goto bailout;
	}

	#endif

	// Same input

	stat = strncmp( txt1, txt1, 10 );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "strncmp test 4 - failed\n" );
		goto bailout;
	}

	// --

	stat = strncmp( txt1, txt2, 10 );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "strncmp test 5 - failed\n" );
		goto bailout;
	}

	stat = strncmp( txt1, txt3, 10 );

	if ( stat < 0 )
	{
		IExec->DebugPrintF( "strncmp test 6 - failed\n" );
		goto bailout;
	}

	stat = strncmp( txt3, txt2, 10 );

	if ( stat > 0 )
	{
		IExec->DebugPrintF( "strncmp test 7 - failed\n" );
		goto bailout;
	}

	stat = strncmp( txt2, txt4, 10 );

	if ( stat > 0 )
	{
		IExec->DebugPrintF( "strncmp test 8 - failed\n" );
		goto bailout;
	}

	error = 0;

bailout:

	return( error );
}

