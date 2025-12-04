
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
// File Buffer

// Same as _drop_iob_read_buffer

S32 AMY_FUNC _generic__Priv_FB_Read_Drop_Buffer( struct AmyCLibIFace *Self, struct FileStruct *file )
{
struct libData *data;
S64 bytes;
S64 pos;
S32 retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FB_Read_Drop_Buffer\n" ); );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	retval = -1;

	if (( ! file ) || ( file->pf_StructID != ID_PRIVFILE ))
	{
		IExec->DebugPrintF( "%s:%04ld: Invalid StructID\n", __FILE__, __LINE__ );
		goto bailout;
	}

	if ( ! file->pf_Handle.pf_File )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FB_Read_Drop_Buffer : NULL Pointer\n" ); );
		goto bailout;
	}

	file->pf_EOF_Reached = FALSE;

	if ( file->pf_BufferReadBytes > 0 )
	{
		bytes = file->pf_BufferReadBytes - file->pf_BufferPosition ;

		if ( bytes > 0 )
		{
			if ( ! file->pf_Interface.pi_Seek )
			{
				IExec->DebugPrintF( "pi_Seek 2 : NULL Pointer\n" );
				goto bailout;
			}

			//	  IExec->DebugPrintF( "213\n" );
			pos = file->pf_Interface.pi_Seek( Self, file, -bytes, SEEK_CUR );
//	  IExec->DebugPrintF( "346\n" );

			if ( pos < 0 )
			{
				file->pf_Error = TRUE;

				goto bailout;
			}

			data->buf_PublicData->ra_ErrNo = 0;
		}

		file->pf_BufferReadBytes	= 0;
		file->pf_BufferPosition		= 0;
	}

	retval = TRUE;

bailout:

	return(	retval );
}
