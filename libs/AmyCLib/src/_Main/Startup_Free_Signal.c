
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

static void myFree_Signal( struct AmyCLibIFace *Self, struct libData *data )
{
	if ( data->buf_SignalHandlers )
	{
		Self->Priv_Mem_Free( data->buf_SignalHandlers );
		data->buf_SignalHandlers = NULL;
	}
}

// --
