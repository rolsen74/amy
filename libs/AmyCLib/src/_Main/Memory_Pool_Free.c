
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMYFUNC _generic__Priv_Mem_FreePooled( struct AmyCLibPrivIFace *Self, struct MemPoolHeader *handle, PTR mem )
{
//struct libData *idata;
struct PoolBlock *old;
struct PoolBlock *cur;
struct PoolBlock *pb;
struct PoolNode *pn;
//struct libBase *libBase;
U32 *m;
U32 retval;
U32 size;
//U8 *d;
//S32 Notify;
//U32 cnt;

	IExec->DebugPrintF( "_generic__Priv_Mem_FreePooled\n" );

//IExec->DebugPrintF( "ReaciveMemory.c | AMYFUNC _generic__Priv_Mem_FreePooled - mem: %p\n", mem );

//	idata = (PTR)( (U32) Self - Self->Data.NegativeSize );

	retval = FALSE;

//	  libBase = (PTR) Self->Data.LibBase;

	if ( ! mem )
	{
		goto bailout;
	}

	if ( ! handle )
	{
		goto bailout;
	}

	if ( handle->ph_ID != ID_POOL )
	{
		goto bailout;
	}


	IExec->ObtainSemaphore( & handle->ph_Semaphore );

	// -- Find Memblock Start

	m = mem;

	m -= 2;

	mem = (PTR) m;

	size = m[1];

	size = (( size + 7 ) & 0xfffffff8 );

//IExec->DebugPrintF( "Clearsize: %ld\n", size );

	Self->string_memset( mem, 0xAC, size );

	// Search for memory Block

	pn = (PTR) IExec->GetHead( & handle->ph_Pools );

	while( pn )
	{
		if (( (U32) pn->pn_Memory				<=	(U32) mem )
		&&	( (U32) pn->pn_Memory + pn->pn_Size	>	(U32) mem ))
		{
			break;
		}
		else
		{
			pn = (PTR) IExec->GetSucc( (PTR) pn );
		}
	}

	if ( ! pn )
	{
		IExec->DebugPrintF( "RA Panic : Unknown Memory Address [%p]\n", mem );
		goto done;
	}

	// --

	if ( handle->ph_PoolSize != pn->pn_Size )
	{
		// Large Block size

		handle->ph_Headers--;
		handle->ph_TotalBytes -= pn->pn_Size;
		handle->ph_UsedBytes  -= pn->pn_Size;

		IExec->Remove( (PTR) pn );

		// --

		IExec->FreeVec( mem );

		// --

		Self->string_memset( pn, 0xAC, sizeof( struct PoolNode ));

		IExec->FreeVec( pn );
		goto done;
	}

	// --

	// Normal Block size

	pb = (PTR) m;

	pb->pb_Free = size;

	// --

	if ( ! pn->pn_Blocks )
	{
		pb->pb_Next = NULL;

		pn->pn_Blocks = pb;
	}
	else
	{
		old = NULL;
		cur = pn->pn_Blocks;

		while( cur )
		{
			if ( (U32) m < (U32) cur )
			{
				break;
			}
			else
			{
				old = cur;
				cur = cur->pb_Next;
			}
		}

		if ( cur )
		{
			pb->pb_Next = cur;
		}
		else
		{
			pb->pb_Next = NULL;
		}

		if ( ! old )
		{
			pn->pn_Blocks = pb;
		}
		else
		{
			old->pb_Next = pb;
		}

		if (( cur ) && ( (U32) cur == (U32) pb + pb->pb_Free ))
		{
			pb->pb_Next  = cur->pb_Next;
			pb->pb_Free += cur->pb_Free;
		}

		if (( old ) && ( (U32) pb == (U32) old + old->pb_Free ))
		{
			old->pb_Next  = pb->pb_Next;
			old->pb_Free += pb->pb_Free;
		}
	}

	// See if we can free the hole block
	if ( pn->pn_Blocks )
	{
		pb = pn->pn_Blocks;

		if ( pn->pn_Size == pb->pb_Free )
		{
			if ( IExec->GetHead( & handle->ph_Pools ) != IExec->GetTail( & handle->ph_Pools ))
			{
				handle->ph_Headers--;
				handle->ph_TotalBytes -= pn->pn_Size;

				IExec->Remove( (PTR) pn );

				if ( pn->pn_Memory )
				{
					Self->string_memset( pn->pn_Memory, 0xAC, pn->pn_Size );

					IExec->FreeVec( pn->pn_Memory );
				}

				Self->string_memset( pn, 0xAC, sizeof( struct PoolNode ));

				IExec->FreeVec( pn );

//				  Notify = TRUE;
			}
		}
	}

	retval = TRUE;

done:

	IExec->ReleaseSemaphore( & handle->ph_Semaphore );

bailout:

	return(	retval );
}
