
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

void * AMYFUNC _generic_stdlib_calloc( struct AmyCLibPrivIFace *Self, size_t num, size_t size )
{
struct libData *data;
void *retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdlib_calloc : Num %lu, Size %lu\n", num, size ); );

	DOFUNCTIONLOG( LOG_FUNC_calloc );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	retval = Self->Priv_Mem_Alloc( num * size );

	// Memory is always cleared to Zero

	if ( ! retval )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdlib_calloc : Error Allocating Memory : Size %lu\n", num * size ); );
		data->buf_PublicData->ra_ErrNo = ENOMEM;
	}

	return( retval );
}

// --
