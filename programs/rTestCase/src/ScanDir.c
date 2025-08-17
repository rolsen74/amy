
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2018-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "Main.h"

// --

void ScanDir( STR path )
{
struct ExamineData *dat;
PTR DirObj;
BPTR oldlock;
BPTR newlock;
U32 stat;
U32 cnt;
U32 id;

	DirObj = NULL;

	oldlock = 0;

	newlock = IDOS->Lock( path, ACCESS_READ );

	if ( ! newlock )
	{
		printf( "Failed to lock path\n" );
		goto bailout;
	}

	oldlock = IDOS->SetCurrentDir( newlock );

	// --

	DefaultScript = RALoadFile( "Compile.Script", NULL );

	// -- Scan Dir

	DirObj = RACreate( NULL, RAC_Directory,
		RAA_DIR_Pattern, "#?(.c|.cpp)",
		RAA_DIR_Path, "currdir:",
		TAG_END
	);

	if ( ! DirObj )
	{
		printf( "Error creating object\n" );
		goto bailout;
	}

	stat = RAMethod( DirObj, RAM_DIR_Scan );

	if ( stat != RAV_General_Success )
	{
		printf( "Error scanning dir\n" );
		goto bailout;
	}

	Stat_Entries = 0;

	RAGet( DirObj, RAA_DIR_Entries, & Stat_Entries );

	RAMethod( DirObj, RAM_DIR_Sort, 0 );

	// --

	id = 0;
	cnt = 0;

	while( RAMethod( DirObj, RAM_DIR_GetEntry, &id, &dat ) == RAV_General_Success )
    {
 	    cnt++;

		if ( IDOS->CheckSignal( SIGBREAKF_CTRL_C ))
		{
			printf( "** User Break\n" );
			break;
		}

		if ( EXD_IS_FILE( dat ))
		{
			TestFile( dat->Name, cnt );
		}
		else
		{
			printf( "Skipping  '%s' ... [%d/%d] Failed (Not a file)", dat->Name, cnt, Stat_Entries );
			fflush( stdout );
			Stat_Skipped++;
		}
	}

	// --

bailout:

	if ( oldlock )
	{
		IDOS->SetCurrentDir( oldlock );
	}

	if ( DirObj )
	{
		RADelete( DirObj );
	}
}

// --
