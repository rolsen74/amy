
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/exec.h>

#include <string.h>

// Well gcc likes to merge txt1 and txt2
// and gcc's build strcmp do not like NULL Pointers
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

	stat = strcmp( NULL, txt1 );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "strcmp test 1 - failed\n" );
		goto bailout;
	}

	stat = strcmp( txt1, NULL );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "strcmp test 2 - failed\n" );
		goto bailout;
	}

	stat = strcmp( NULL, NULL );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "strcmp test 3 - failed\n" );
		goto bailout;
	}

	#endif

	// Same input

	stat = strcmp( txt1, txt1 );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "strcmp test 4 - failed\n" );
		goto bailout;
	}

	// --

	stat = strcmp( txt1, txt2 );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "strcmp test 5 - failed\n" );
		goto bailout;
	}

	stat = strcmp( txt1, txt3 );

	if ( stat < 0 )
	{
		IExec->DebugPrintF( "strcmp test 6 - failed\n" );
		goto bailout;
	}

	stat = strcmp( txt3, txt2 );

	if ( stat > 0 )
	{
		IExec->DebugPrintF( "strcmp test 7 - failed\n" );
		goto bailout;
	}

	stat = strcmp( txt2, txt4 );

	if ( stat > 0 )
	{
		IExec->DebugPrintF( "strcmp test 8 - failed\n" );
		goto bailout;
	}

	error = 0;

bailout:

	return( error );
}
