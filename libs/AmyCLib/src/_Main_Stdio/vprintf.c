
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

int AMYFUNC _generic_stdio_vprintf( struct AmyCLibIFace *Self, const char *fmt, va_list ap )
{
struct PrintStruct ps;
struct libData *data;
int retval;

	// -- Enable Check

	IExec->DebugPrintF( "_generic_stdio_vprintf\n" );

	retval = -1;

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

//	if ( ! ( data->EnableMask & EM_FILE ))
//	{
//		IExec->DebugPrintF( "%s:%04lu: Function Not Enabled\n", __FILE__, __LINE__ );
//		goto bailout;
//	}

	// --

	Self->Priv_Check_Abort();

	// --

	if ( ! fmt )
	{
		IExec->DebugPrintF( "_generic_stdio_vprintf : NULL Pointer\n" );
		data->buf_PublicData->ra_ErrNo = EFAULT;
		goto bailout;
	}

	ps.ps_Format	= fmt;
	ps.ps_Stream	= (PTR) data->buf_PublicData->ra_stdout;
	ps.ps_Buffer	= NULL;
	ps.ps_Size		= INT_MAX;
	ps.ps_Result	= 0;
//	ps.ps_Args		= & ap;

//	IExec->DebugPrintF("fmt = %s\n", fmt);
//	IExec->DebugPrintF("arg1 = %ld\n", va_arg(ap, long));
//	IExec->DebugPrintF("arg2 = %lx\n", va_arg(ap, long));

	va_copy( ps.ps_Args, ap );  // ✅ CORRECT for standard stdarg

	Self->Priv_Print( & ps );

	if ( ps.ps_Result < 0 )
	{
		IExec->DebugPrintF( "_generic_stdio_vprintf : Failed with %ld\n", ps.ps_Result );
		goto bailout;
	}

	retval = ps.ps_Result;

bailout:

	return(	retval );
}

// --
