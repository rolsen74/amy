
/*
** SPDX-License-Identifier: BSD-3-Clause
** Modifications (c) 2025 Rene W. Olsen
** Part of Amy C Lib
**
** Based on:
**
** Portable ISO 'C' (1994) runtime library for the Amiga computer
** Copyright (c) 2002-2015 by Olaf Barthel <obarthel (at) gmx.net>
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
**   - Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**
**   - Neither the name of Olaf Barthel nor the names of contributors
**     may be used to endorse or promote products derived from this
**     software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
** LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
** CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
** SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
** INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
** POSSIBILITY OF SUCH DAMAGE.
**
*/

// --

#include "src/All.h"

// --

FILE * AMYFUNC _generic_stdio_fopen( struct AmyCLibIFace *Self, const char *filename, const char *mode )
{
struct FDInitStruct is;
struct FileStruct *file;
struct libData *data;
U32 Mode;

	// --

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_fopen, Filename %s, Mode: %s\n", filename, mode ); );

	DOFUNCTIONLOG( LOG_FUNC_fopen );

	file = NULL;

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	Self->Priv_Check_Abort();
	Self->string_memset( & is, 0, sizeof( is ));

	is.is_Filename = (PTR) filename;
	is.is_Fildes = -1;

	// --
	// Scan mode

	#define Mode_R		( 1UL << 0 )	// Read
	#define Mode_W		( 1UL << 1 )	// Write
	#define Mode_A		( 1UL << 2 )	// Append
	#define Mode_P		( 1UL << 3 )	// + (Plus)
	#define Mode_B		( 1UL << 4 )	// Binary
	#define Mode_I		( 1UL << 5 )	// Invalid
	#define Mode_T		( 1UL << 6 )	// Text
	#define Mode_Mask	( Mode_R | Mode_W | Mode_A | Mode_P | Mode_I )

	#define FOPEN_R		( Mode_R )
	#define FOPEN_RP	( Mode_R | Mode_P )
	#define FOPEN_W		( Mode_W )
	#define FOPEN_WP	( Mode_W | Mode_P )
	#define FOPEN_A		( Mode_A )
	#define FOPEN_AP	( Mode_A | Mode_P )

	Mode = 0;

	for( ; *mode ; mode++ )
	{
		switch( *mode )
		{
			case '+':	Mode |= Mode_P; break;

			case 'r':
			case 'R':	Mode |= Mode_R; break;

			case 'w':
			case 'W':	Mode |= Mode_W; break;

			case 'a':
			case 'A':	Mode |= Mode_A; break;

			case 'b':
			case 'B':	Mode |= Mode_B; break;	// optional, may ignore on Amiga

			case 't':
			case 'T':	Mode |= Mode_T; break;	// none standard, may ignore on Amiga

			default:	Mode |= Mode_I; break;
		}
	}

	switch( Mode & Mode_Mask )
	{
		case ( FOPEN_R ):
		{
			// Opens file for reading. The File must exist.

			is.is_Read = TRUE;
			break;
		}

		case ( FOPEN_RP ):
		{
			// Open a file for reading and writting
			// The file must exists

			is.is_Read = TRUE;
			is.is_Write = TRUE;
			break;
		}

		case ( FOPEN_W ):
		{
			// Creates an empty file for writing.
			// if a file with same name allready exists, so sould be overwitten
			// file is truncated to zero length

			is.is_CanCreate = TRUE;
			is.is_Trunc = TRUE;
			is.is_Write = TRUE;
			break;
		}

		case ( FOPEN_WP ):
		{
			// Creates an expty file
			// for reading and writting
			// file is truncated to zero length.. this diffres from fdopen()

			is.is_CanCreate = TRUE;
			is.is_Trunc = TRUE;
			is.is_Write = TRUE;
			is.is_Read = TRUE;
			break;
		}

		case ( FOPEN_A ):
		{
			// Open or create a file for writting at end
			// Appends to a file..
			// Writting to the end of an file

			is.is_CanCreate = TRUE;
			is.is_Append = TRUE;
			is.is_Write = TRUE;
			break;
		}

		case ( FOPEN_AP ):
		{
			// open or create a file
			// Opens a file for reading and appending
			// writes to end of file

			is.is_CanCreate = TRUE;
			is.is_Append = TRUE;
			is.is_Write = TRUE;
			is.is_Read = TRUE;
			break;
		}

		default:
		{
			if ( Mode & Mode_I )
			{
				DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_fopen : Invalid Mode $%08lx\n", Mode ); );
			}
			else
			{
				DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_fopen : Unsupported Mode $%08lx\n", Mode ); );
			}

			data->buf_PublicData->ra_ErrNo = EFAULT;
			goto bailout;
		}
	}

	// --

	file = Self->Priv_FD_Init( & is );

	if ( ! file )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_fopen : Priv_FD_Init failed\n" ); );
		goto bailout;
	}

	// --

bailout:

	return( (PTR) file );
}

// --
