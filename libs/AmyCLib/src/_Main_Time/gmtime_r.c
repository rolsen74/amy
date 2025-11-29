
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

struct tm *_generic_time_gmtime_r( struct AmyCLibIFace *Self, const time_t *time, struct tm *tm )
{
struct libData *data;
struct tm *retval;
time_t *t;

	retval = NULL;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_time_gmtime_r : Time %p\n", time ); );

	DOFUNCTIONLOG( LOG_FUNC_gmtime_r );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	if (( ! time ) || ( ! tm ))
	{
		#ifdef DEBUG
		IExec->DebugPrintF( "%s:%04d: Error : NULL Pointer\n", __FILE__, __LINE__ );
		#endif
		data->buf_PublicData->ra_ErrNo = EFAULT;
		goto bailout;
	}

	t = (PTR) time;

	if ( ! Self->Priv_Convert_Time_to_TM( t, tm ))
	{
		#ifdef DEBUG
		IExec->DebugPrintF( "%s:%04d: Error : Convert Error\n", __FILE__, __LINE__ );
		#endif
		goto bailout;
	}

	retval = tm;

bailout:

	return(	retval );
}

// --
