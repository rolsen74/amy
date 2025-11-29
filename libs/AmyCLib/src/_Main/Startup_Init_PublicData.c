
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

static S32 myInit_PublicData(
	struct AmyCLibIFace *Self,
	struct libData *data )
{
struct _AmyCLibPublic *pd;	// Public Data
FILE *file;
S32 error;
S32 stat;

	error = TRUE;

	pd = data->buf_PublicData;

	// Only if Memory functions is Enabled
	if ( data->Enable_Memory )
	{
		// Only if File handling is Enabled
		if ( data->Enable_File )
		{
			// -- FD 0 - is stdin

			stat = Self->fcntl_open( "console:", O_RDONLY );

			if ( stat < 0 )
			{
				IExec->DebugPrintF( "myInit_PublicData : fcntl_open (stdin) failed : Stat %ld\n", stat );
				goto bailout;
			}

			file = data->FD_Array.Nodes[STDIN_FILENO].Node;

			if ( Self->stdio_setvbuf( (PTR) file, NULL, BUFFER_MODE_LINE, 2048 ) < 0 )
			{
				IExec->DebugPrintF( "myInit_PublicData : setvbuf (stdin) failed\n" );
				goto bailout;
			}

			pd->ra_stdin = (PTR) file;

			// -- FD 1 - is stdout

			stat = Self->fcntl_open( "console:", O_WRONLY );

			if ( stat < 0 )
			{
				IExec->DebugPrintF( "myInit_PublicData : fcntl_open (stdout) failed : Stat %ld\n", stat );
				goto bailout;
			}

			file = data->FD_Array.Nodes[STDOUT_FILENO].Node;

			if ( Self->stdio_setvbuf( (PTR) file, NULL, BUFFER_MODE_LINE, 2048 ) < 0 )
			{
				IExec->DebugPrintF( "myInit_PublicData : setvbuf (stdout) failed\n" );
				goto bailout;
			}

			pd->ra_stdout = (PTR) file;

			// -- FD 2 - is stderr

			stat = Self->fcntl_open( "console:", O_WRONLY );

			if ( stat < 0 )
			{
				IExec->DebugPrintF( "myInit_PublicData : fcntl_open (stderr) failed : Stat %ld\n", stat );
				goto bailout;
			}

			file = data->FD_Array.Nodes[STDERR_FILENO].Node;

			if ( Self->stdio_setvbuf( (PTR) file, NULL, BUFFER_MODE_LINE, 2048 ) < 0 )
			{
				IExec->DebugPrintF( "myInit_PublicData : setvbuf (stderr) failed\n" );
				goto bailout;
			}

			pd->ra_stderr = (PTR) file;
		}
	}

	error = FALSE;

//	IExec->DebugPrintF( "myInit_PublicData : OK\n" );

bailout:

//	IExec->DebugPrintF( "myInit_PublicData : error %ld\n", error );

 	return( error );
}

// --
