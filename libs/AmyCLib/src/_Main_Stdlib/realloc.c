
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

void * AMYFUNC _generic_stdlib_realloc( struct AmyCLibPrivIFace *Self, void *mem, size_t size )
{
struct libData *data;
void *retval;

	IExec->DebugPrintF( "_generic_stdlib_realloc : Mem %p, Size %lu\n", mem, size );

	DOFUNCTIONLOG( LOG_FUNC_realloc );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	retval = Self->Priv_Mem_Realloc( mem, size );

	if (( ! retval ) && ( size ))
	{
		IExec->DebugPrintF( "_generic_stdlib_realloc : Error Allocating Memory : Size %lu\n", size );
		data->buf_PublicData->ra_ErrNo = ENOMEM;
	}

	return( retval );
}

// --
