
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2018-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "Main.h"

// --

PTR		RAAppObject		= NULL;
STR		DefaultScript	= NULL;
STR		CompileScript	= NULL;

U32		Stat_Entries	= 0;
U32		Stat_Skipped	= 0;
U32		Stat_Passed		= 0;
U32		Stat_Failed		= 0;

static struct RAArguments arglist[] =
{
	RAArgEnd()
};

// --

int main( int argc, char **argv )
{
struct ExamineData *dat;
PTR oldproc;
int retval;
STR path;
S32 file;
U32 err;
S32 dir;

	retval = RETURN_FAIL;

	oldproc = (PTR) IDOS->SetProcWindow( (PTR) -1 );

	err = RAV_General_Success;

	RAAppObject = RACreate( NULL, RAC_Application,
		RAA_APP_Argument_Values, argv,
		RAA_APP_Argument_Count, argc,
		RAA_APP_Argument_List, arglist,
		RAA_APP_Base, "rTestCase",
		RAA_ErrorCode, &err,
		TAG_END
	);

	if ( ! RAAppObject )
	{
		printf( "Error Creating Object (ErrCode: %d)\n", err );
		goto bailout;
	}

	// --

	CompileScript = malloc( 10 * 1024 );

	if ( ! CompileScript )
	{
		printf( "Error allocating memory\n" );
		goto bailout;
	}

	// --

	/**/ if ( argc == 1 )
	{
		path = "currdir:";
	}
	else
	{
		path = argv[1];
	}

	dat = IDOS->ExamineObjectTags(
		EX_StringNameInput, path,
		TAG_END
	);

	if ( ! dat )
	{
		printf( "Could not lock '%s' dir\n", path );
		goto bailout;
	}

	dir  = ( EXD_IS_DIRECTORY( dat )) ? TRUE : FALSE ;
	file = ( EXD_IS_FILE( dat )) ? TRUE : FALSE ;

	IDOS->FreeDosObject( DOS_EXAMINEDATA, dat );

	// --

	printf( "\n" );

	/**/ if ( file )
	{
		Stat_Entries = 1;

		ScanFile( path );
	}
	else if ( dir )
	{
		ScanDir( path );
	}

	printf( "\nPassed : %d, Failed : %d, Skipped : %d\n\n", Stat_Passed, Stat_Failed, Stat_Skipped );

	// --

	retval = RETURN_OK;

bailout:

	IDOS->SetProcWindow( oldproc );

	if ( RAAppObject )
	{
		RADelete( RAAppObject );
	}

	return( retval );
}

// --
