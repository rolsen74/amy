
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
// File Descriptor

struct PrivFile * AMYFUNC _generic__Priv_FD_Init( struct AmyCLibPrivIFace *Self, struct FDInitStruct *is )
{
//struct FDInitStruct *is;
struct ExamineData *dat;
struct PrivFile *file;
struct libData *data;
S32 is_file_system;
S32 error;
U32 mode;

//	is = is_ptr;

	dat = NULL;

	file = NULL;

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	error = TRUE;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FD_Init : IS %p\n", is ); );

	// --

	if ( ! is->is_Filename )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FD_Init : Missing Filename\n" ); );
		data->buf_PublicData->ra_ErrNo = EFAULT;
		goto bailout;
	}

	// --

	file = Self->Priv_FD_Alloc( ID_FILE );

//	IExec->DebugPrintF( "Priv_FD_Alloc : File %p\n", file );

	if ( ! file )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FD_Init : Priv_FDAlloc failed\n" ); );
		data->buf_PublicData->ra_ErrNo = ENOMEM;
		goto bailout;
	}

	file->pf_Append = ( is->is_Append ) ? TRUE : FALSE ;
	file->pf_Write	= ( is->is_Write  ) ? TRUE : FALSE ;
	file->pf_Read	= ( is->is_Read   ) ? TRUE : FALSE ;

	// --

	dat = IDOS->ExamineObjectTags(
		EX_StringNameInput, is->is_Filename,
		TAG_END
	);

	if ( dat )
	{
		// File Exists

		if ( EXD_IS_DIRECTORY( dat ))
		{
			// We can't open Directoryes
			DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FD_Init : We don't support directories\n" ); );
			data->buf_PublicData->ra_ErrNo = EISDIR;
			goto bailout;
		}

		if ( is->is_MustNotExists )
		{
			DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FD_Init : File exists\n" ); );
			data->buf_PublicData->ra_ErrNo = EEXIST;
			goto bailout;
		}

		if ( is->is_Write )
		{
			// Make sure its Writeable
			if (( dat->Protection & EXDF_NO_WRITE  )
			||	( dat->Protection & EXDF_NO_DELETE ))
			{
				DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FD_Init : File is not Writeable\n" ); );
				data->buf_PublicData->ra_ErrNo = EACCES;
				goto bailout;
			}
		}

		if ( is->is_Read )
		{
			// Make sure its readable
			if ( dat->Protection & EXDF_NO_READ )
			{
				DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FD_Init : File is not Readable %08lx\n", dat->Protection ); );
				data->buf_PublicData->ra_ErrNo = EACCES;
				goto bailout;
			}
		}

		/**/ if ( is->is_Trunc )
		{
			mode = MODE_NEWFILE;
		}
		else
		{
			mode = MODE_OLDFILE;
		}

		is_file_system = TRUE;
	}
	else
	{
		// File do not Exists

		is_file_system = IDOS->IsFileSystem( is->is_Filename );

		if ( is_file_system )
		{
			if ( is->is_CanCreate )
			{
				mode = MODE_NEWFILE;
			}
			else
			{
				DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FD_Init : Unsupported mode for '%s'\n", is->is_Filename ); );
				data->buf_PublicData->ra_ErrNo = ENOENT;
				goto bailout;
			}
		}
		else
		{
			mode = MODE_NEWFILE;
		}
	}

	// --

	file->pf_Handle.pf_File = IDOS->Open( is->is_Filename, mode );

	if ( file->pf_Handle.pf_File == 0 )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FD_Init : Error opening File\n" ); );
		data->buf_PublicData->ra_ErrNo = Self->Priv_Convert_IOErr_to_ErrNo( IDOS->IoErr());
		goto bailout;
	}

	// --

	// Figure out if this stream is attached to a console.
	file->pf_IsInteractive = ( IDOS->IsInteractive( file->pf_Handle.pf_File )) ? TRUE : FALSE;

	if (( file->pf_IsInteractive ) && ( is->is_NonBlocking ))
	{
		// single character mode
		// Instead of LineBuffered for Console:
		if ( IDOS->SetMode( file->pf_Handle.pf_File, DOSTRUE ))
		{
			file->pf_NonBlocking = TRUE;
		}
	}
	else
	{
		if ( is_file_system )
		{
			/* We opened the file in exclusive access mode. Switch it back
			   into shared access mode so that its contents can be read
			   while it's still open. */
			if ( mode == MODE_NEWFILE )
			{
				IDOS->ChangeMode( CHANGE_FH, file->pf_Handle.pf_File, SHARED_LOCK );
			}

			/* We should be able to seek in this file. */
			file->pf_CachePosition = TRUE;
		}
	}

	// --

	// Change File Pos to the End if we are in Append Mode
	if ( is->is_Append )
	{
		IDOS->ChangeFilePosition( file->pf_Handle.pf_File, 0LL, OFFSET_END );
	}

	// --

	if ( Self->stdio_setvbuf( (PTR) file, NULL, BUFFER_MODE_FULL, BUFSIZ ) < 0 )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FD_Init : stdio_setvbuf failed\n" ); );
		goto bailout;
	}

	// --

	error = FALSE;

bailout:

	if ( dat )
	{
		IDOS->FreeDosObject( DOS_EXAMINEDATA, dat );
		dat = NULL;
	}

	if (( error ) && ( file ))
	{
		Self->Priv_FD_Free( file );
		file = NULL;
	}

	return( file );
}

// --
