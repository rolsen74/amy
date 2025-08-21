
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

void * AMYFUNC _generic_stdlib_malloc( struct AmyCLibPrivIFace *Self, size_t size )
{
struct libData *data;
void *retval;

	IExec->DebugPrintF( "_generic_stdlib_malloc : Size %lu\n", size );

	DOFUNCTIONLOG( LOG_FUNC_malloc );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	retval = Self->Priv_Mem_Alloc( size );

	// Memory is always cleared to Zero

	if ( ! retval )
	{
		IExec->DebugPrintF( "_generic_stdlib_malloc : Error Allocating Memory : Size %lu\n", size );
		data->buf_PublicData->ra_ErrNo = ENOMEM;
	}

	return( retval );
}

// --
