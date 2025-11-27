

#include <proto/exec.h>
#include <proto/AmyIUP.h>

#include <stdio.h>

struct Library *		AmyIUPBase		= NULL;
struct AmyIUPIFace *	IAmyIUP			= NULL;

int main( int argc, char **argv )
{
	IExec->DebugPrintF( ": AmyIUP : Test : Start 1 :\n" );

	AmyIUPBase = IExec->OpenLibrary( "AmyIUP.library", 1 );

	if ( ! AmyIUPBase )
	{
		IExec->DebugPrintF( "Error opening library\n" );
		goto bailout;
	}

	IExec->DebugPrintF( ": AmyIUP : Test : Start 2 :\n" );

	IAmyIUP = (PTR) IExec->GetInterface( AmyIUPBase, "main", 1, NULL );

	if ( ! IAmyIUP )
	{
		IExec->DebugPrintF( "Error obtaining interface\n" );
		goto bailout;
	}

	IExec->DebugPrintF( ": AmyIUP : Test : Start 3 :\n" );



	// ---------
	IExec->DebugPrintF( ": AmyIUP : Test : Run 1 :\n" );

	int stat = IAmyIUP->IupOpen( & argc, & argv );

	if ( stat != IUP_NOERROR )
	{
		IExec->DebugPrintF( "IupOpen failed with %ld\n", stat );
		goto bailout;
	}

	IExec->DebugPrintF( ": AmyIUP : Test : Run 2 :\n" );

	IAmyIUP->IupClose();

	IExec->DebugPrintF( ": AmyIUP : Test : Run 3 :\n" );
	// ---------


bailout:

	IExec->DebugPrintF( ": AmyIUP : Test : Quit 1 :\n" );

	if ( IAmyIUP )
	{
		IExec->DropInterface( (PTR) IAmyIUP );
	}

	IExec->DebugPrintF( ": AmyIUP : Test : Quit 2 :\n" );

	if ( AmyIUPBase )
	{
		IExec->CloseLibrary( AmyIUPBase );
	}

	IExec->DebugPrintF( ": AmyIUP : Test : Quit 99 :\n" );
}