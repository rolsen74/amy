
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMY_FUNC _generic__Priv_Mem_Free( struct AmyCLibIFace *Self, PTR mem )
{
struct MemPoolHeader *pool;
struct libData *data;
U32 retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Mem_Free : mem %p\n", mem ); );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	IExec->ObtainSemaphore( & data->MemSemaphore );

	retval = FALSE;

	if ( ! mem )
	{
		goto bailout;
	}

	pool = (PTR) IExec->GetHead( & data->MemPools );

	while(( pool ) && ( ! pool->ph_Global ))
	{
		pool = (PTR) IExec->GetSucc( (PTR) pool );
	}

	if ( ! pool )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Mem_Free : No Memory Pool\n" ); );
		goto bailout;
	}

	Self->Priv_Mem_FreePooled( pool, mem );

	retval = TRUE;

bailout:

	IExec->ReleaseSemaphore( & data->MemSemaphore );

	return(	retval );
}

// --
