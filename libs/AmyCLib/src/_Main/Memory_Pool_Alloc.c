
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

PTR AMYFUNC _generic__Priv_Mem_AllocPooled( struct AmyCLibIFace *Self, struct MemPoolHeader *handle, U32 Size )
{
//struct libData *data;
struct PoolBlock *new;
struct PoolBlock *old;
struct PoolBlock *pb;
struct PoolNode *pn;
//struct libBase *libBase;
U32 chunksize;
U32 datasize;
//S32 Notify;
U32 *m;
S32 move;
PTR mem;

	// --

//	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	mem = NULL;

	pb = NULL;

	// --

	if ( ! Size )
	{
		IExec->DebugPrintF( "_generic__Priv_Mem_AllocPooled : Size is zero\n" );
		goto bailout;
	}

	datasize = Size;

	// --

	chunksize = ( 8 + datasize );

	// 8 Byte align
	chunksize = (( chunksize + 7 ) & 0xfffffff8 );

//IExec->DebugPrintF( "ReaciveMemory.c | chunksize: %ld\n", chunksize );

	// --

	if ( ! handle )
	{
		IExec->DebugPrintF( "_generic__Priv_Mem_AllocPooled : Handle is NULL\n" );
		goto bailout;
	}

	if ( handle->ph_ID != ID_POOL )
	{
		IExec->DebugPrintF( "_generic__Priv_Mem_AllocPooled : Invalid Pool ID\n" );
		goto bailout;
	}

	// --

	IExec->ObtainSemaphore( & handle->ph_Semaphore );

	if ( chunksize < handle->ph_PoolSize )
	{
		// -- Get chunk inside pool
		// -- Search PoolNodes

		pn = (PTR) IExec->GetHead( & handle->ph_Pools );

		pb = NULL;

		old = NULL;

		move = FALSE;

		while( pn )
		{
			pb = pn->pn_Blocks;

			while( pb )
			{
				if ( pb->pb_Free >= chunksize )
				{
					break;
				}
				else
				{
					old = pb;

					pb = pb->pb_Next;
				}
			}

			if ( pb )
			{
				break;
			}

			pn = (PTR) IExec->GetSucc( (PTR) pn );

			old = NULL;

			move = TRUE;
		}

		// -- Found? or alloc new

		if ( ! pn )
		{
			// No Pool had Free memory large enough for our data
			// Alloc new PoolNode

			old = NULL;

			pn = IExec->AllocVecTags( sizeof( struct PoolNode ),
				AVT_Clear, 0,
				TAG_END
			);

			if ( pn )
			{
				pn->pn_Size = handle->ph_PoolSize;
				pn->pn_Memory = IExec->AllocVecTags( pn->pn_Size,
					AVT_Clear, 0,
					TAG_END
				);

				if ( pn->pn_Memory )
				{
					handle->ph_Headers++;
					handle->ph_TotalBytes += pn->pn_Size;

					IExec->AddHead( & handle->ph_Pools, (PTR) pn );

					move = FALSE;

					// --

					pb = (PTR) ((U32) pn->pn_Memory );

					pb->pb_Next = NULL;
					pb->pb_Free = pn->pn_Size;

					pn->pn_Blocks = pb;
				}
				else
				{
					IExec->FreeVec( pn );

					pn = NULL;
					pb = NULL;
				}
			}
		}

		// -- Insert Chunk

		if ( pn )
		{
			if ( move )
			{
				// Move Node to Top of list
				IExec->Remove( (PTR) pn );
				IExec->AddHead( & handle->ph_Pools, (PTR) pn );
			}

			// --

			if ( pb->pb_Free == chunksize )
			{
				if ( ! old )
				{
					pn->pn_Blocks = pb->pb_Next;
				}
				else
				{
					old->pb_Next = pb->pb_Next;
				}
			}
			else
			{
				U32 cs = (( chunksize + 7 ) & 0xfffffff8 );

				new = (PTR) ((U32) pb + cs );

				new->pb_Next = pb->pb_Next;
				new->pb_Free = pb->pb_Free - cs;

				if ( ! old )
				{
					pn->pn_Blocks = new;
				}
				else
				{
					old->pb_Next = new;
				}
			}
		}

		// --
	}
	else
	{
		// Can not Fit in Block

		pn = IExec->AllocVecTags( sizeof( struct PoolNode ),
			AVT_Clear, 0,
			TAG_END
		);

		if ( pn )
		{
			pn->pn_Size = chunksize;
			pn->pn_Memory = IExec->AllocVecTags( chunksize,
				AVT_Clear, 0,
				TAG_END
			);

			if ( pn->pn_Memory )
			{
				handle->ph_Headers++;
				handle->ph_TotalBytes += pn->pn_Size;

				IExec->AddTail( & handle->ph_Pools, (PTR) pn );

				pb = pn->pn_Memory;
			}
			else
			{
				IExec->FreeVec( pn );
			}
		}
	}

	// --

	if ( pb )
	{
		handle->ph_UsedBytes += chunksize;

//IExec->DebugPrintF( "memory: %p\n", pb );

		// --

		m		= (PTR) pb;
		m[0]	= ID_MEM;
		m[1]	= datasize;
		mem		= (PTR) & m[2];

//IExec->DebugPrintF( "mem 6\n" );

		Self->string_memset( mem, 0, datasize );
	}

//IExec->DebugPrintF( "mem 7\n" );

	IExec->ReleaseSemaphore( & handle->ph_Semaphore );

	// --

	IExec->DebugPrintF( "_generic__Priv_Mem_AllocPooled : mem %p, Size %lu\n", mem, Size );

bailout:

	return(	mem );
}

// --
