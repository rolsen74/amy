
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

PTR AMYFUNC _generic__Priv_Mem_Alloc( struct AmyCLibPrivIFace *Self, U32 Size )
{
struct MemPoolHeader *pool;
struct libData *data;
PTR mem;

//	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Mem_Alloc - Size: %lu\n", Size ); );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	IExec->ObtainSemaphore( & data->MemSemaphore );

	mem = NULL;

	if ( ! Size )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Mem_Alloc : Zero size\n" ); );
		goto bailout;
	}

	pool = (PTR) IExec->GetHead( & data->MemPools );

	while(( pool ) && ( ! pool->ph_Global ))
	{
		pool = (PTR) IExec->GetSucc( (PTR) pool );
	}

	if ( ! pool )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Mem_Alloc : No Memory Pool\n" ); );
		goto bailout;
	}

	mem = Self->Priv_Mem_AllocPooled( pool, Size );

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Mem_Alloc : mem %p, size %lu\n", mem, Size ); );

bailout:

	IExec->ReleaseSemaphore( & data->MemSemaphore );

	return(	mem );
}

// --
