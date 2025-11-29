
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

struct MemPoolHeader * AMYFUNC _generic__Priv_Mem_CreatePool( struct AmyCLibIFace *Self, U32 size )
{
struct MemPoolHeader *handle;
struct libData *data;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Mem_CreatePool\n" ); );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	handle = NULL;

	if ( ! size )
	{
		goto bailout;
	}

	handle = IExec->AllocVecTags( sizeof( struct MemPoolHeader ),
		AVT_Clear, 0,
		TAG_END
	);

	if ( ! handle )
	{
		goto bailout;
	}

	IExec->NewList(			& handle->ph_Pools );
	IExec->InitSemaphore(	& handle->ph_Semaphore );

	handle->ph_ID		= ID_POOL;
	handle->ph_PoolSize	= (( size + 7 ) & 0xfffffff8 );

	// -- Done

	IExec->ObtainSemaphore( & data->MemSemaphore );
	IExec->AddTail( 		& data->MemPools, & handle->ph_Node );
	IExec->ReleaseSemaphore(& data->MemSemaphore );

bailout:

	return(	handle );
}

// --
