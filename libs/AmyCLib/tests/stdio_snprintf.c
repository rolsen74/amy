
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/dos.h>
#include <proto/exec.h>

#include <stdio.h>
#include <string.h>

#define MAX_BUF		128

int main( int argc, char **argv )
{
char buf[MAX_BUF];
int error;
int len;

	error = 10;

	// --

	#ifdef NULL_PTR_TEST

	len = snprintf( NULL, MAX_BUF, "Test String" );

	if ( len != EOF )
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 0A - Failed (%d)\n", __FILE__, __LINE__, len );
		goto bailout;
	}

	#endif

	// --

	buf[0] = 0xac;	// Random byte, too see if something have been written to buffer

	// Count bytes, nothing should be written
	len = snprintf( buf, 0, "Test String" );

	if (( len != 11 ) || ( buf[0] != 0xac ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 1A - Failed (%d)\n", __FILE__, __LINE__, len );
		goto bailout;
	}

	// --

	buf[0] = 0xdc;	// Random byte, too see if something have been written to buffer

	// Count bytes, nothing should be written
	len = snprintf( NULL, 0, "Test String" );

	if (( len != 11 ) || ( buf[0] != 0xdc ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 1B - Failed (%d)\n", __FILE__, __LINE__, len );
		goto bailout;
	}

	// --

	len = snprintf( buf, 5, "Test String" );

	// Only first 5 bytes should be writtin (plus nul, but not counted)
	if (( strcmp( buf, "Test " )) || ( len != 5 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 1C - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 1C - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "Test String" );

	if (( strcmp( buf, "Test String" )) || ( len != 11 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 1D - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 1D - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%s", "Test String" );

	if (( strcmp( buf, "Test String" )) || ( len != 11 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 2A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 2A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%15s", "Test String" );

	if (( strcmp( buf, "    Test String" )) || ( len != 15 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 3A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 3A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%d", 123 );

	if (( strcmp( buf, "123" )) || ( len != 3 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 4A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 4A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%5d", 123 );

	if (( strcmp( buf, "  123" )) || ( len != 5 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 5A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 5A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%05d", 123 );

	if (( strcmp( buf, "00123" )) || ( len != 5 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 6A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 6A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%i", 123 );

	if (( strcmp( buf, "123" )) || ( len != 3 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 7A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 7A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%5i", 123 );

	if (( strcmp( buf, "  123" )) || ( len != 5 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 8A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 8A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%05i", 123 );

	if (( strcmp( buf, "00123" )) || ( len != 5 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 9A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 9A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%u", 123 );

	if (( strcmp( buf, "123" )) || ( len != 3 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 10A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 10A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%5u", 123 );

	if (( strcmp( buf, "  123" )) || ( len != 5 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 11A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 11A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%05u", 123 );

	if (( strcmp( buf, "00123" )) || ( len != 5 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 12A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 12A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%x", 123 );

	if (( strcmp( buf, "7b" )) || ( len != 2 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 13A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 13A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%5x", 123 );

	if (( strcmp( buf, "   7b" )) || ( len != 5 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 14A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 14A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%05x", 123 );

	if (( strcmp( buf, "0007b" )) || ( len != 5 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 15A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 15A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%X", 123 );

	if (( strcmp( buf, "7B" )) || ( len != 2 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 16A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 16A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%5X", 123 );

	if (( strcmp( buf, "   7B" )) || ( len != 5 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 17A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 17A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%05X", 123 );

	if (( strcmp( buf, "0007B" )) || ( len != 5 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 18A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 18A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%#X", 123 );

	if (( strcmp( buf, "0x7B" )) || ( len != 4 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 19A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 19A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%#7X", 123 );

	if (( strcmp( buf, "   0x7B" )) || ( len != 7 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 20A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 20A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%#07X", 123 );

	if (( strcmp( buf, "0x0007B" )) || ( len != 7 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 21A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 21A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%#x", 123 );

	if (( strcmp( buf, "0x7b" )) || ( len != 4 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 22A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 22A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%#7x", 123 );

	if (( strcmp( buf, "   0x7b" )) || ( len != 7 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 23A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 23A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%#07x", 123 );

	if (( strcmp( buf, "0x0007b" )) || ( len != 7 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 24A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 24A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	len = snprintf( buf, MAX_BUF, "%s %d %s", "Test", 123, "String" );

	if (( strcmp( buf, "Test 123 String" )) || ( len != 15 ))
	{
		IExec->DebugPrintF( "%s:%04ld: snprintf test 25A - Failed (%d)\n", __FILE__, __LINE__, len );
		IExec->DebugPrintF( "%s:%04ld: snprintf test 25A - '%s'\n", __FILE__, __LINE__, buf );
		goto bailout;
	}

	// --

	error = 0;

bailout:

	return( error );
}
