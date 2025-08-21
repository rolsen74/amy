
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

static int mySeek( struct AmyCLibPrivIFace *Self, struct PrivFile *file, S64 pos, S32 mode )
{
struct libData *data;
S32 new_mode;
S64 new_pos;
S32 success;
S64 retval;
S32 err;

	IExec->DebugPrintF( "FD_IFC_File_Seek\n" );

	retval = -1L;

	if (( ! file ) || ( file->pf_StructID != ID_PRIVFILE ))
	{
		IExec->DebugPrintF( "%s:%04ld: Invalid file id\n", __FILE__, __LINE__ );
		goto bailout;
	}

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	/**/ if ( mode == SEEK_CUR )
	{
		new_mode = OFFSET_CURRENT;

		new_pos = pos;
	}
	else if ( mode == SEEK_SET )
	{
		new_mode = OFFSET_BEGINNING;

		new_pos = pos;
	}
	else if ( mode == SEEK_END )
	{
		new_mode = OFFSET_END;

		new_pos = pos;
	}
	else
	{

IExec->DebugPrintF( "Illegal SEEK_xxx (%ld)\n", mode );

		goto bailout;
	}

	// --

	success = IDOS->ChangeFilePosition( file->pf_Handle.pf_File, new_pos, new_mode );

	if ( success == 0 )
	{
		err = IDOS->IoErr();

		data->buf_PublicData->ra_ErrNo = Self->Priv_Convert_IOErr_to_ErrNo( err );

		goto bailout;
	}

	// --

	retval = TRUE;

bailout:

	return( retval );
}

