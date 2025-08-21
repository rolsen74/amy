
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

STR	USED txt1 = "rene olsen  !!";
STR	USED txt2 = "rene olsen  ##";
STR	txt3 = "rene Olsen  &&";
STR	txt4 = "rene olsen  dk";
STR txt5A = "1234A";
STR txt5B = "1234B";

int main( int argc, char **argv )
{
int stat;
int error;

	error = 10;




	// Null Pointer test

	#ifdef NULL_PTR_TEST

	stat = memcmp( NULL, txt1, 10 );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "%s:%04d: memcmp test 1 : Failed : Stat %ld :\n", __FILE__, __LINE__, stat );
		goto bailout;
	}

	stat = memcmp( txt1, NULL, 10 );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "%s:%04d: memcmp test 2 : Failed : Stat %ld :\n", __FILE__, __LINE__, stat );
		goto bailout;
	}

	stat = memcmp( NULL, NULL, 10 );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "%s:%04d: memcmp test 3 : Failed : Stat %ld :\n", __FILE__, __LINE__, stat );
		goto bailout;
	}

	#endif



	// --
	// Same input pointers

	stat = memcmp( txt1, txt1, 10 );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "%s:%04d: memcmp test 4 : Failed : Stat %ld :\n", __FILE__, __LINE__, stat );
		goto bailout;
	}

	// --
	// Same strings

	stat = memcmp( txt1, txt2, 10 );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "%s:%04d: memcmp test 5 : Failed : Stat %ld :\n", __FILE__, __LINE__, stat );
		goto bailout;
	}

	// --
	// Diffrent Strings

	stat = memcmp( txt1, txt3, 10 );

	if ( stat <= 0 )
	{
		IExec->DebugPrintF( "%s:%04d: memcmp test 6 : Failed : Stat %ld :\n", __FILE__, __LINE__, stat );
		goto bailout;
	}

	stat = memcmp( txt3, txt2, 10 );

	if ( stat >= 0 )
	{
		IExec->DebugPrintF( "%s:%04d: memcmp test 7 : Failed : Stat %ld :\n", __FILE__, __LINE__, stat );
		goto bailout;
	}

	// --
	// First 4 chars are the same
	// Make sure we don't test too much

	stat = memcmp( txt5A, txt5B, 4 );

	if ( stat )
	{
		IExec->DebugPrintF( "%s:%04d: memcmp test 8 : Failed : Stat %ld :\n", __FILE__, __LINE__, stat );
		goto bailout;
	}

	// --
	// First 4 chars are the same, but 5th is diff
	// Make sure we don't test too little
	// 

	stat = memcmp( txt5A, txt5B, 5 );

	if ( stat >= 0 )
	{
		IExec->DebugPrintF( "%s:%04d: memcmp test 9 : Failed : Stat %ld :\n", __FILE__, __LINE__, stat );
		goto bailout;
	}

	// --
	// First 4 chars are the same, but 5th is diff, swapped pointers
	// Make sure we don't test too little
	// 

	stat = memcmp( txt5B, txt5A, 5 );

	if ( stat <= 0 )
	{
		IExec->DebugPrintF( "%s:%04d: memcmp test 10 : Failed : Stat %ld :\n", __FILE__, __LINE__, stat );
		goto bailout;
	}

	// --

	error = 0;

bailout:

	return( error );
}

