
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

static void myFree_Memory( struct AmyCLibPrivIFace *Self, struct libData *data )
{
PTR handle;

	// Free Alloc Private Memory

	IExec->ObtainSemaphore( & data->MemSemaphore );

	while(( handle = (PTR) IExec->GetTail( & data->MemPools )))
	{
		Self->Priv_Mem_DeletePool( handle );
	}

	IExec->ReleaseSemaphore( & data->MemSemaphore );
}

// --
