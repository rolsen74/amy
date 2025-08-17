
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

static S32 myInit_Signal( struct AmyCLibIFace *Self UNUSED, struct libData *data )
{
int error;
//U32 cnt;

	error = TRUE;

	// --

	// hmm we really need memory here
	if ( data->Enable_Memory )
	{
		data->Signals_BreakMask = SIGBREAKF_CTRL_C;

		data->buf_SignalHandlers = Self->Priv_Mem_Alloc( sizeof( signal_handler_t ) * 32 );

		if ( ! data->buf_SignalHandlers )
		{
			IExec->DebugPrintF( "myInit_Signal : Error allocating memory\n" );
			goto bailout;
		}

		#if 0
		// SIG_DFL is zero and this gets converted to memset
		for( cnt = 0 ; cnt < 32 ; cnt++ )
		{
			data->buf_SignalHandlers[cnt] = SIG_DFL;
		}
		#endif
	}

	// --

	error = FALSE;

bailout:

	return( error );
}

// --
