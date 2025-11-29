
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

#define SECONDS_PER_DAY		86400		// 24 * 60 * 60
#define SECONDS_PER_MIN		60

S32 AMYFUNC _generic__Priv_Convert_DS_to_Time( struct AmyCLibIFace *Self UNUSED, const struct DateStamp *ds, time_t *time )
{
//struct libData *data;
time_t t;
S32 retval;

	retval = FALSE;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Convert_DS_to_Time\n" ); );

	if ( ! ds )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Convert_DS_to_Time : NULL Pointer\n" ); );
		goto bailout;
	}

	if ( ! time )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Convert_DS_to_Time : NULL Pointer\n" ); );
		goto bailout;
	}

	/* If possible, adjust for the local time zone. We do this because the
	   AmigaOS system time is returned in local time and we want to return
	   it in UTC. */

	t	 = UNIX_TIME_OFFSET;
	t	+= ( ds->ds_Days	* SECONDS_PER_DAY );
	t	+= ( ds->ds_Minute	* SECONDS_PER_MIN );
	t	+= ( ds->ds_Tick	/ TICKS_PER_SECOND );

	// --

//--    data = (PTR)( (U32) Self - Self->Data.NegativeSize );
//--
//--    IExec->ObtainSemaphore( & data->LocaleSemaphore );
//--
//--    if ( data->LocaleDefault )
//--    {
//--		t += 60 * data->LocaleDefault->loc_GMTOffset;
//--    }
//--
//--    IExec->ReleaseSemaphore( & data->LocaleSemaphore );

	// --

	*time = t;

	retval = TRUE;

bailout:

	return(	retval );
}

// --
