
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

/* This is roughly equivalent to fflush(), but returns the last character
   written to the buffer, or EOF if flushing produced an error. The putc()
   macro and the internal __putc() macro need this functionality. This
   function is called only if the last character written to the buffer
   was a line feed, prompting the buffer contents to be flushed. It should
   never be used in place of fflush(). */

// Same as __flush
int AMYFUNC _generic__Priv_FB_Write_Flush_Buffer2( struct AmyCLibIFace *Self, struct PrivFile *file )
{
int last_c;
int retval;

	IExec->DebugPrintF( "_generic__Priv_FB_Write_Flush_Buffer2\n" );

	retval = -1;

	if (( ! file ) || ( file->pf_StructID != ID_PRIVFILE ))
	{
		IExec->DebugPrintF( "%s:%04ld: Invalid file id\n", __FILE__, __LINE__ );
		goto bailout;
	}

	if ( ! file->pf_Handle.pf_File )
	{
		IExec->DebugPrintF( "_generic__Priv_FB_Write_Flush_Buffer2 : NULL Pointer\n" );
		goto bailout;
	}

	Self->stdio_flockfile( (PTR) file );

	last_c = file->pf_Buffer[ file->pf_BufferWriteBytes - 1 ];

	if ( Self->Priv_FB_Write_Flush_Buffer( file ) < 0 )
	{
		/* Remove the last character stored in the buffer, which is
		   typically a '\n'. */
		file->pf_BufferWriteBytes--;
	}
	else
	{
		retval = last_c;
	}

	Self->stdio_funlockfile( (PTR) file );

bailout:
	return(	retval );
}
