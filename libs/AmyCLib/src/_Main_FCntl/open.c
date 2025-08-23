
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

int AMYFUNC _generic_fcntl_open( struct AmyCLibPrivIFace *Self, const char *path, int oflag, ... )
{
struct FDInitStruct is;
struct PrivFile *file;
struct libData *data;
int retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_fcntl_open\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_open );

	// -- Check About

	Self->Priv_Check_Abort();

	// --

	retval = -1L;

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	Self->string_memset( & is, 0, sizeof( is ));

	is.is_Filename		= (PTR) path;
	is.is_NonBlocking	= ( oflag & O_NONBLOCK ) ? TRUE : FALSE ;
	is.is_Append		= ( oflag & O_APPEND ) ? TRUE : FALSE ;
	is.is_CanCreate		= ( oflag & O_CREAT ) ? TRUE : FALSE ;
	is.is_Trunc			= ( oflag & O_TRUNC ) ? TRUE : FALSE ;
	is.is_MustNotExists = ( oflag & O_EXCL ) ? TRUE : FALSE ;

	// --

	switch( oflag & O_ACCMODE )
	{
		case O_RDONLY:
		{
			is.is_Read = TRUE;
			break;
		}

		case O_RDWR:
		{
			is.is_Read = TRUE;
			is.is_Write = TRUE;
			break;
		}

		case O_WRONLY:
		{
			is.is_Write = TRUE;
			break;
		}

		default:
		{
			DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_fcntl_open : Unknown mode\n" ); );
			data->buf_PublicData->ra_ErrNo = EFAULT;
			goto bailout;
		}
	}

	// --

	file = Self->Priv_FD_Init( & is );

	if ( ! file )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_fcntl_open : Priv_FD_Init failed\n" ); );
		goto bailout;
	}

	// --

	retval = file->pf_ArrayPos;

bailout:

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_fcntl_open : Retval %ld\n", retval ); );

	return( retval );
}
