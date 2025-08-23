
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMYFUNC _generic__Priv_Mem_FlushPool( struct AmyCLibPrivIFace *Self, struct MemPoolHeader *handle )
{
//struct libData *data;
struct PoolBlock *pb;
struct PoolNode *def;
struct PoolNode *pn;
//struct libBase *libBase;
U32 retval;
//S32 Notify;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Mem_FlushPool\n" ); );

//	  IExec->DebugPrintF( "FlushPool( %p )\n", handle );

//	  libBase = (PTR) Self->Data.LibBase;

//	  data = (struct libData *)((U32) Self - Self->Data.NegativeSize );

	retval = FALSE;

	if ( ! handle )
	{
		goto bailout;
	}

	if ( handle->ph_ID != ID_POOL )
	{
		goto bailout;
	}

	IExec->ObtainSemaphore( & handle->ph_Semaphore );

	// -- Find a Default Size Pool Node

	def = (PTR) IExec->GetHead( & handle->ph_Pools );

	while( def )
	{
		if ( def->pn_Size == handle->ph_PoolSize )
		{
			break;
		}
		else
		{
			def = (PTR) IExec->GetSucc( (PTR) def );
		}
	}

	if ( def )
	{
		IExec->Remove( (PTR) def );
	}

	// -- Release Memory

	while(( pn = (PTR) IExec->RemHead( & handle->ph_Pools )))
	{
		handle->ph_Headers--;
		handle->ph_TotalBytes -= pn->pn_Size;
		handle->ph_UsedBytes  -= pn->pn_Size;

		if ( pn->pn_Memory )
		{
			Self->string_memset( pn->pn_Memory, 0xAC, pn->pn_Size );

			IExec->FreeVec( pn->pn_Memory );
		}

		Self->string_memset( pn, 0xAC, sizeof( struct PoolNode ));

		IExec->FreeVec( pn );
	}

	// -- Put back an Empty Node (def size)

	if ( def )
	{
		Self->string_memset( def->pn_Memory, 0xAC, def->pn_Size );

		pb = (PTR) def->pn_Memory;

		pb->pb_Next = NULL;
		pb->pb_Free = def->pn_Size;

		def->pn_Blocks = pb;

		IExec->AddTail( & handle->ph_Pools, (PTR) def );
	}

	// --

	IExec->ReleaseSemaphore( & handle->ph_Semaphore );

	// --

	retval = TRUE;

bailout:

	return(	retval );
}

// --
