
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/exec.h>

#include <string.h>

// Well gcc likes to merge txt1 and txt2
// and gcc's build memcmp do not like NULL Pointers
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

IExec->DebugPrintF( "memcmp 1\n" );

	stat = memcmp( NULL, txt1, 10 );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "memcmp test 1 - failed\n" );
		goto bailout;
	}

IExec->DebugPrintF( "memcmp 2\n" );

	stat = memcmp( txt1, NULL, 10 );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "memcmp test 2 - failed\n" );
		goto bailout;
	}

IExec->DebugPrintF( "memcmp 3\n" );

	stat = memcmp( NULL, NULL, 10 );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "memcmp test 3 - failed\n" );
		goto bailout;
	}

	#endif

	// Same input

IExec->DebugPrintF( "memcmp 4\n" );

	stat = memcmp( txt1, txt1, 10 );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "memcmp test 4 - failed\n" );
		goto bailout;
	}

	// --

IExec->DebugPrintF( "memcmp 5\n" );

	stat = memcmp( txt1, txt2, 10 );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "memcmp test 5 - failed\n" );
		goto bailout;
	}

IExec->DebugPrintF( "memcmp 6\n" );

	stat = memcmp( txt1, txt3, 10 );

	if ( stat < 0 )
	{
		IExec->DebugPrintF( "memcmp test 6 - failed\n" );
		goto bailout;
	}

IExec->DebugPrintF( "memcmp 7\n" );

	stat = memcmp( txt3, txt2, 10 );

	if ( stat > 0 )
	{
		IExec->DebugPrintF( "memcmp test 7 - failed\n" );
		goto bailout;
	}

IExec->DebugPrintF( "memcmp 8\n" );

	stat = memcmp( txt2, txt4, 10 );

	if ( stat > 0 )
	{
		IExec->DebugPrintF( "memcmp test 8 - failed\n" );
		goto bailout;
	}

	error = 0;

bailout:

	return( error );
}

