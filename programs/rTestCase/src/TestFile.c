
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2018-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "Main.h"

// --

void TestFile( STR FileName, U32 CurrentEntry )
{
STR FileScript;
STR FileScriptName;
STR str;
U32 doserr;
U32 len;
S32 stat;

	FileScriptName = NULL;
	FileScript = NULL;

	// Copy String

	str = NULL;

	asprintf( & str, "%s", FileName );

	if ( ! str )
	{
		printf( "Error allocating memory\n" );
		goto bailout;
	}

	// -- Remove end

	len = strlen( str );

	/**/ if ( ! stricmp( & str[ len - 4 ], ".cpp" ))
	{
		str[ len - 4 ] = 0;
	}
	else if ( ! stricmp( & str[ len - 2 ], ".c" ))
	{
		str[ len - 2 ] = 0;
	}

	// Build Script Name

	FileScriptName = NULL;

	asprintf( & FileScriptName, "%s.Script", str );

	if ( ! FileScriptName )
	{
		printf( "Error allocating memory\n" );
		goto bailout;
	}

	// Load File Script
	
	FileScript = RALoadFile( FileScriptName, NULL );

	stat = BuildScript( ( FileScript ) ? FileScript : DefaultScript, FileName );

	if ( ! stat )
	{
		printf( "Error building script\n" );
		goto bailout;
	}

	// Compile

	printf( "Compiling '%s' ... [%d/%d] ", FileName, CurrentEntry, Stat_Entries );

	fflush( stdout );

	doserr = IDOS->SystemTags( CompileScript,
		SYS_Asynch, FALSE,
		SYS_Output, ZERO,
		SYS_Input, ZERO,
		TAG_END
	);

	// Run binary

	if ( ! doserr )
	{
		printf( "\rTesting   '%s' ... [%d/%d] ", FileName, CurrentEntry, Stat_Entries );
		fflush( stdout );

		doserr = IDOS->SystemTags( "a.out",
			SYS_Asynch, FALSE,
			SYS_Output, ZERO,
//			SYS_Input, ZERO,	// need CTRL+D
			SYS_Error, ZERO,
			TAG_END
		);
	}

	// Update stats

	if ( ! doserr )
	{
		printf( "Passed\n" );
		Stat_Passed++;
	}
	else
	{
		printf( "Failed\n" );
//		printf( "\033[34mFailed\033[31m\n" );
		Stat_Failed++;
	}

	// Delete binary

	for( int cnt=0 ; cnt<30 ; cnt++ )
	{
		IDOS->Delete( "a.out" );

		if ( IDOS->IoErr() == ERROR_OBJECT_IN_USE )
		{
			IDOS->Delay( ( cnt / 3 ) + 1 );
		}
		else
		{
			break;
		}
	}

	// Done

bailout:

	if ( FileScript )
	{
		free( FileScript );
	}

	if ( FileScriptName )
	{
		free( FileScriptName );
	}

	if ( str )
	{
		free( str );
	}
}

// --
