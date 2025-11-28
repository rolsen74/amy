
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

PTR AMYFUNC _main_Misc_LoadFile_32( struct ReactivePrivIFace *Self UNUSED, STR FileName, U32 *FileSize )
{
U64 size;
U8 *mem;
BPTR handle;
S32 err;

//	IExec->DebugPrintF( "_main_Misc_LoadFile_32\n" );

	size	= 0ULL;
	mem		= NULL;
	err		= TRUE;

	handle	= IDOS->Open( FileName, MODE_OLDFILE );

	if ( ! handle )
	{
		// File not found?
		goto bailout;
	}

	size = IDOS->GetFileSize( handle );

	if ( ! size )
	{
//		IExec->DebugPrintF( "LoadFile32 : Error getting filesize\n" );
		goto bailout;
	}

	if ( size > 512*1024*1024 )	// Max 512mb
	{
//		IExec->DebugPrintF( "LoadFile32 : Error file too big %lld bytes\n", size );
		goto bailout;
	}

	mem	= malloc( (U32) size + 1 );

	if ( ! mem )
	{
//		IExec->DebugPrintF( "LoadFile32 : Error allocating memory\n" );
		goto bailout;
	}

	if ( IDOS->Read( handle, mem, size ) != (S32) size )
	{
//		IExec->DebugPrintF( "LoadFile32 : Error reading file\n" );
		goto bailout;
	}

	mem[size] = 0;

	err = FALSE;

bailout:

	if ( FileSize )
	{
		if ( ! err )
		{
			*FileSize = size;
		}
		else
		{
			*FileSize = 0;
		}
	}

	if (( mem ) && ( err ))
	{
		free( mem );
		mem = NULL;
	}

	if ( handle )
	{
		IDOS->Close( handle );
	}

	return(	mem );
}