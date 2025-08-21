
#include <proto/dos.h>
#include <proto/exec.h>

#include <stdio.h>
#include <string.h>

int main( int argc, char **argv )
{
int error;
int args;
int arg1;
int arg2;
int arg3;
int arg4;

	error = 10;

	// --

	#if 0
	#ifdef NULL_PTR_TEST

	len = sprintf( NULL, "Test String" );

	if ( len != EOF )
	{
		IExec->DebugPrintF( "sprintf test 0 - Failed (%d)\n", len );
		goto bailout;
	}

	#endif
	#endif

	// --

	args = sscanf( "192.168.1.211", "%d.%d.%d.%d", & arg1, & arg2, & arg3, & arg4 );

	if (( args != 4 )
	||	( arg1 != 192 )
	||	( arg2 != 168 )
	||	( arg3 != 1 )
	||	( arg4 != 211 ))
	{
		IExec->DebugPrintF( "sscanf test 1 - Failed (%d)\n", args );
		IExec->DebugPrintF( "sscanf test 1 - %ld %ld %ld %ld\n", arg1, arg2, arg3, arg4 );
		goto bailout;
	}

	// --

	error = 0;

bailout:

	return( error );
}
