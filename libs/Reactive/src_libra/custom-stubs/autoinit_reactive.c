
/****************************************************************************/

#include <stdio.h>
#include <assert.h>

#include <proto/AmyCLib.h>
#include <proto/Reactive.h>

struct Library *		ReativeBase		= NULL;
struct ReactiveIFace *	IReactive		= NULL;

/****************************************************************************/

void __attribute__((constructor)) __init_libreactive( void )
{
	// -- Open Library

	ReativeBase = IExec->OpenLibrary( "Reactive.library", RA_LIB_VERSION );

	if ( ! ReativeBase )
	{
		IExec->DebugPrintF( "Unable to open Reactive.library v%lu\n", (U32) RA_LIB_VERSION );
	}

	assert( ReativeBase );

	// -- Version Check

//	if ( ReativeBase->lib_Version < RA_LIB_VERSION )
//	{
//		IExec->DebugPrintF( "Reactive version check failure. Only version %lu.xx is supported\n", RA_LIB_VERSION );
//	}

	assert( ReativeBase->lib_Version >= RA_LIB_VERSION );

	// -- Open Interface

	IReactive = (PTR) IExec->GetInterface( ReativeBase, "main", 1, NULL );

	if ( ! IReactive )
	{
		IExec->DebugPrintF( "Unable to obtain Reactive interface\n" );
	}

	assert( IReactive );
}

/****************************************************************************/

void __attribute__((destructor)) __exit_libreactive( void )
{
	if ( IReactive )
	{
		IExec->DropInterface( (PTR) IReactive );
		IReactive = NULL;
	}

	// --

	if ( ReativeBase )
	{
		IExec->CloseLibrary( ReativeBase );
		ReativeBase = NULL;
	}
}

/****************************************************************************/

