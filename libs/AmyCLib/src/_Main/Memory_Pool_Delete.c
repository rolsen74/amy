
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMYFUNC _generic__Priv_Mem_DeletePool( struct AmyCLibIFace *Self, struct MemPoolHeader *handle )
{
struct libData *data;
struct PoolNode *pn;
U32 retval;

	IExec->DebugPrintF( "_generic__Priv_Mem_DeletePool\n" );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

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

	while(( pn = (PTR) IExec->RemHead( & handle->ph_Pools )))
	{
		if ( pn->pn_Memory )
		{
			Self->string_memset( pn->pn_Memory, 0xAD, pn->pn_Size );

			IExec->FreeVec( pn->pn_Memory );
		}

		Self->string_memset( pn, 0xAD, sizeof( struct PoolNode ));

		IExec->FreeVec( pn );
	}


	IExec->ObtainSemaphore(	& data->MemSemaphore );
	IExec->Remove(			& handle->ph_Node );
	IExec->ReleaseSemaphore(& data->MemSemaphore );

	IExec->FreeVec( handle );

	// --

	retval = TRUE;

bailout:

	return(	retval );
}

// --
