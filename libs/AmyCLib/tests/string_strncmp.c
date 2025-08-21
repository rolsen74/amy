
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

STR	USED txt1 = "rene olsen";
STR	USED txt2 = "rene olsen B";
STR	txt3 = "rene Olsen  &&";
STR	txt4 = "rene olsen  dk";
STR txt5A = "1234A";
STR txt5B = "1234B";
STR txt5C = "1234";

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
		IExec->DebugPrintF( "%s:%04d: strncmp test 1 : Failed : Stat %ld :\n", __FILE__, __LINE__, stat );
		goto bailout;
	}

	stat = strncmp( txt1, NULL, 10 );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "%s:%04d: strncmp test 2 : Failed : Stat %ld :\n", __FILE__, __LINE__, stat );
		goto bailout;
	}

	stat = strncmp( NULL, NULL, 10 );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "%s:%04d: strncmp test 3 : Failed : Stat %ld :\n", __FILE__, __LINE__, stat );
		goto bailout;
	}

	#endif



	// --
	// Same input pointers

	stat = strncmp( txt1, txt1, 15 );

	if ( stat != 0 )
	{
		IExec->DebugPrintF( "%s:%04d: strncmp test 4 : Failed : Stat %ld :\n", __FILE__, __LINE__, stat );
		goto bailout;
	}

	// --
	// Same strings .. first 10 chars only

	stat = strncmp( txt1, txt2, 15 );

	if ( stat >= 0 )
	{
		IExec->DebugPrintF( "%s:%04d: strncmp test 5 : Failed : Stat %ld :\n", __FILE__, __LINE__, stat );
		goto bailout;
	}

	// --
	// Diffrent Strings

	stat = strncmp( txt1, txt3, 10 );

	if ( stat <= 0 )
	{
		IExec->DebugPrintF( "%s:%04d: strncmp test 6 : Failed : Stat %ld :\n", __FILE__, __LINE__, stat );
		goto bailout;
	}

	stat = strncmp( txt3, txt2, 10 );

	if ( stat >= 0 )
	{
		IExec->DebugPrintF( "%s:%04d: strncmp test 7 : Failed : Stat %ld :\n", __FILE__, __LINE__, stat );
		goto bailout;
	}

	// --
	// First 4 chars are the same
	// Make sure we don't test too much

	stat = strncmp( txt5A, txt5B, 4 );

	if ( stat )
	{
		IExec->DebugPrintF( "%s:%04d: strncmp test 8 : Failed : Stat %ld :\n", __FILE__, __LINE__, stat );
		goto bailout;
	}

	// --
	// First 4 chars are the same, but 5th is diff
	// Make sure we don't test too little
	// 

	stat = strncmp( txt5A, txt5B, 5 );

	if ( stat >= 0 )
	{
		IExec->DebugPrintF( "%s:%04d: strncmp test 9 : Failed : Stat %ld :\n", __FILE__, __LINE__, stat );
		goto bailout;
	}

	// --
	// First 4 chars are the same, but 5th is diff, swapped pointers
	// Make sure we don't test too little
	// 

	stat = strncmp( txt5B, txt5A, 5 );

	if ( stat <= 0 )
	{
		IExec->DebugPrintF( "%s:%04d: strncmp test 10 : Failed : Stat %ld :\n", __FILE__, __LINE__, stat );
		goto bailout;
	}

	// --

	error = 0;

bailout:

	return( error );
}

