
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
#include "Print.h"

// --

static enum myWriteStat AMYFUNC my_writechar( struct PrintStruct *ps, struct Intern *in, char c )
{
enum myWriteStat retval;

	// Error
	retval = MWS_Error;

	/**/ if ( ps->ps_Buffer )
	{
		// Buffer

		ps->ps_Buffer[ ps->ps_Written ] = c;
	}
	else if ( ps->ps_Stream )
	{
		// Stream

		if ( in->Self->stdio_fputc_unlocked( c, ps->ps_Stream ) == -1 )
		{
			goto bailout;
		}

	}

//	IExec->DebugPrintF( "WriteChar : $%02x : ' %c ' :\n", c, ( c >= 0x20 && c <= 0x7f ) ? c : ' ' );

	ps->ps_Written++;

	if (( ps->ps_Size ) && ( ps->ps_Size <= ps->ps_Written ))
	{
//		IExec->DebugPrintF( "my_writechar : Buffer full : Size %ld : Written %ld\n", ps->ps_Size, ps->ps_Written );
	
		// Okay but is Buffer now Full
		retval = MWS_Full;
	}
	else
	{
		// Okay
		retval = MWS_Okay;
	}

bailout:

	return( retval );
}