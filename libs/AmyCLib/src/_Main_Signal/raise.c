
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

int AMYFUNC _generic_signal_raise( struct AmyCLibPrivIFace *Self, int sig )
{
signal_handler_t handler;
struct libData *data;
int retval;

	IExec->DebugPrintF( "_generic_signal_raise\n" );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	#if 0

	// Acording to OpenGroup raise is just calling kill
	// But as we don't have kill yet

	retval = Self->pthread_kill( data->ThreadID, sig );

	#else

	retval = 0;

	if (((( data->Signals_Blocked )		 & ( 1UL << sig )) == 0 )
	&&	((( data->Signals_LocalBlocked ) & ( 1UL << sig )) == 0 ))
	{
		handler = data->buf_SignalHandlers[ sig ];

		if ( handler != SIG_IGN )
		{
			data->Signals_LocalBlocked |= ( 1UL << sig );

			if ( handler == SIG_DFL )
			{
				if ( sig == SIGINT )
				{
					data->Check_Abort_Enabled = FALSE;
				}

				Self->stdlib_abort();
			}
			else
			{
				( *handler )( sig );
			}

			data->Signals_LocalBlocked &= ~( 1UL << sig );
		}
	}

	#endif

	return(	retval );
}

/****************************************************************************/

