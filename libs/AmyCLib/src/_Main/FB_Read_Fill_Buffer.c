
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

// Same as __filL_iob_read_buffer
S32 AMYFUNC _generic__Priv_FB_Read_Fill_Buffer( struct AmyCLibPrivIFace *Self, struct PrivFile *file )
{
S64 bytes;
S32 retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FB_Read_Fill_Buffer\n" ); );

	retval = -1;

	if (( ! file ) || ( file->pf_StructID != ID_PRIVFILE ))
	{
		IExec->DebugPrintF( "%s:%04ld: Invalid StructID\n", __FILE__, __LINE__ );
		goto bailout;
	}

	if ( ! file->pf_Handle.pf_File )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FB_Read_Fill_Buffer : NULL Pointer\n" ); );
		goto bailout;
	}

//--	/* Flush all line buffered streams before we proceed to fill this buffer. */
//--	if((file->iob_Flags & IOBF_BUFFER_MODE) == IOBF_BUFFER_MODE_LINE)
//--	{
//--		if(__flush_all_files(IOBF_BUFFER_MODE_LINE) < 0)
//--			goto out;
//--	}

	if ( ! file->pf_Interface.pi_Read )
	{
		IExec->DebugPrintF( "pi_Read 1 : NULL Pointer\n" );
		goto bailout;
	}

	bytes = file->pf_Interface.pi_Read( Self, file, file->pf_Buffer, file->pf_BufferSize );

	if ( bytes < 0 )
	{
		file->pf_Error = TRUE;
		goto bailout;
	}

	file->pf_BufferReadBytes	= bytes;
	file->pf_BufferPosition		= 0;

	retval = TRUE;

bailout:

	return(	retval );
}
