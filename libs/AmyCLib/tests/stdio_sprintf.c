
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

	len = sprintf( NULL, "Test String" );

	if ( len != EOF )
	{
		IExec->DebugPrintF( "sprintf test 0 - Failed (%d)\n", len );
		goto bailout;
	}

	#endif

	// --

	len = sprintf( buf, "Test String" );

	if (( strcmp( buf, "Test String" )) || ( len != 11 ))
	{
		IExec->DebugPrintF( "sprintf test 1 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 1 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%s", "Test String" );

	if (( strcmp( buf, "Test String" )) || ( len != 11 ))
	{
		IExec->DebugPrintF( "sprintf test 2 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 2 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%15s", "Test String" );

	if (( strcmp( buf, "    Test String" )) || ( len != 15 ))
	{
		IExec->DebugPrintF( "sprintf test 3 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 3 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%d", 123 );

	if (( strcmp( buf, "123" )) || ( len != 3 ))
	{
		IExec->DebugPrintF( "sprintf test 4 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 4 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%5d", 123 );

	if (( strcmp( buf, "  123" )) || ( len != 5 ))
	{
		IExec->DebugPrintF( "sprintf test 5 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 5 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%05d", 123 );

	if (( strcmp( buf, "00123" )) || ( len != 5 ))
	{
		IExec->DebugPrintF( "sprintf test 6 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 6 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%i", 123 );

	if (( strcmp( buf, "123" )) || ( len != 3 ))
	{
		IExec->DebugPrintF( "sprintf test 7 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 7 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%5i", 123 );

	if (( strcmp( buf, "  123" )) || ( len != 5 ))
	{
		IExec->DebugPrintF( "sprintf test 8 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 8 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%05i", 123 );

	if (( strcmp( buf, "00123" )) || ( len != 5 ))
	{
		IExec->DebugPrintF( "sprintf test 9 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 9 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%u", 123 );

	if (( strcmp( buf, "123" )) || ( len != 3 ))
	{
		IExec->DebugPrintF( "sprintf test 10 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 10 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%5u", 123 );

	if (( strcmp( buf, "  123" )) || ( len != 5 ))
	{
		IExec->DebugPrintF( "sprintf test 11 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 11 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%05u", 123 );

	if (( strcmp( buf, "00123" )) || ( len != 5 ))
	{
		IExec->DebugPrintF( "sprintf test 12 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 12 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%x", 123 );

	if (( strcmp( buf, "7b" )) || ( len != 2 ))
	{
		IExec->DebugPrintF( "sprintf test 13 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 13 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%5x", 123 );

	if (( strcmp( buf, "   7b" )) || ( len != 5 ))
	{
		IExec->DebugPrintF( "sprintf test 14 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 14 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%05x", 123 );

	if (( strcmp( buf, "0007b" )) || ( len != 5 ))
	{
		IExec->DebugPrintF( "sprintf test 15 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 15 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%X", 123 );

	if (( strcmp( buf, "7B" )) || ( len != 2 ))
	{
		IExec->DebugPrintF( "sprintf test 16 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 16 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%5X", 123 );

	if (( strcmp( buf, "   7B" )) || ( len != 5 ))
	{
		IExec->DebugPrintF( "sprintf test 17 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 17 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%05X", 123 );

	if (( strcmp( buf, "0007B" )) || ( len != 5 ))
	{
		IExec->DebugPrintF( "sprintf test 18 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 18 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%#X", 123 );

	if (( strcmp( buf, "0x7B" )) || ( len != 4 ))
	{
		IExec->DebugPrintF( "sprintf test 19 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 19 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%#7X", 123 );

	if (( strcmp( buf, "   0x7B" )) || ( len != 7 ))
	{
		IExec->DebugPrintF( "sprintf test 20 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 20 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%#07X", 123 );

	if (( strcmp( buf, "0x0007B" )) || ( len != 7 ))
	{
		IExec->DebugPrintF( "sprintf test 21 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 21 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%#x", 123 );

	if (( strcmp( buf, "0x7b" )) || ( len != 4 ))
	{
		IExec->DebugPrintF( "sprintf test 22 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 22 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%#7x", 123 );

	if (( strcmp( buf, "   0x7b" )) || ( len != 7 ))
	{
		IExec->DebugPrintF( "sprintf test 23 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 23 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%#07x", 123 );

	if (( strcmp( buf, "0x0007b" )) || ( len != 7 ))
	{
		IExec->DebugPrintF( "sprintf test 24 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 24 - '%s'\n", buf );
		goto bailout;
	}

	// --

	len = sprintf( buf, "%s %d %s", "Test", 123, "String" );

	if (( strcmp( buf, "Test 123 String" )) || ( len != 15 ))
	{
		IExec->DebugPrintF( "sprintf test 25 - Failed (%d)\n", len );
		IExec->DebugPrintF( "sprintf test 25 - '%s'\n", buf );
		goto bailout;
	}

	// --

	error = 0;

bailout:

	return( error );
}
