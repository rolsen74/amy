
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

int AMY_FUNC _generic_stdio_vsscanf( struct AmyCLibIFace *Self, const char *buf, const char *fmt, va_list ap )
{
struct ScanStruct ss;
struct libData *data;
int retval;

	// --

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_vsscanf\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_vsscanf );

	retval = EOF;

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	if ( ! buf )
	{
//		IExec->DebugPrintF( "NULL Pointer" );
		data->buf_PublicData->ra_ErrNo = EFAULT;
		goto bailout;
	}

	if ( ! fmt )
	{
//		IExec->DebugPrintF( "NULL Pointer" );
		data->buf_PublicData->ra_ErrNo = EFAULT;
		goto bailout;
	}

	// --

	Self->strings_bzero( & ss, sizeof( ss ));

	ss.ss_Format	= fmt;
	ss.ss_Stream	= NULL;
	ss.ss_Buffer	= buf;

	va_copy( ss.ss_Args, ap );

	Self->Priv_Scan( & ss );

	retval = ss.ss_Handled;

bailout:

	return( retval );
}

/****************************************************************************/

