
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

#define BUFFER_SIZE		( 128 > sizeof( struct tm ) ? 128 : sizeof( struct tm ))

struct tm * AMYFUNC _generic_time_localtime( struct AmyCLibIFace *Self, const time_t *time )
{
struct libData *data;
struct tm *retval;
time_t *t;
int rc;

	// Do NOT need to call tzset()

	retval = NULL;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_time_localtime : Time %p\n", time ); );

	DOFUNCTIONLOG( LOG_FUNC_localtime );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	if ( ! time )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_time_localtime : Null Pointer\n" ); );
		data->buf_PublicData->ra_ErrNo = EFAULT;
		goto bailout;
	}

	if ( ! data->buf_LocalTime )
	{
		data->buf_LocalTime = IExec->AllocVecTags( BUFFER_SIZE,
			AVT_Clear, 0,
			TAG_END
		);

		if ( ! data->buf_LocalTime )
		{
			DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_time_localtime : Failed to allocate memory\n" ); );
			data->buf_PublicData->ra_ErrNo = ENOMEM;
			goto bailout;
		}

		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_time_localtime : Allocated new buffer %p\n", data->buf_LocalTime ); );
	}

	t = (PTR) time;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_time_localtime : Calling Convert : LocalTime Buffer %p\n", data->buf_LocalTime ); );

	rc = Self->Priv_Convert_Time_to_TM( t, data->buf_LocalTime );

	if ( ! rc )
	{
		data->buf_PublicData->ra_ErrNo = EOVERFLOW;
		goto bailout;
	}

	retval = data->buf_LocalTime;

bailout:

	return(	retval );
}

// --
