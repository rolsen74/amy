
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

PTR AMYFUNC _generic__Priv_Mem_Realloc( struct AmyCLibIFace *Self, PTR oldmem, U32 Size )
{
struct MemStruct *realmem;
//struct libData *data;
U32 realsize;
U32 len;
PTR newmem;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Mem_Realloc\n" ); );

//	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	if (( ! oldmem ) && ( ! Size ))
	{
		newmem	= NULL;
	}
	else if ( ! oldmem )
	{
		newmem = Self->Priv_Mem_Alloc( Size );
	}
	else if ( ! Size )
	{
		Self->Priv_Mem_Free( oldmem );

		newmem	= NULL;
	}
	else
	{
		// -- Find real mem start

		// Do not align as the Back MemWall	need to be moved
		realsize = Size + 8;

		realmem = (PTR) (((U32)oldmem) - 8 );

		if ( realmem->ID != ID_MEM )
		{
			IExec->DebugPrintF( "RA Panic : Invlid Memory ID\n" );
			newmem = NULL;
			goto bailout;
		}

		if ( realmem->Size == realsize )
		{
			// No need to reallocate memory
			newmem = oldmem;
		}
		else
		{
			newmem = Self->Priv_Mem_Alloc( Size );

			if ( newmem )
			{
				len = AMY_MIN( Size, realmem->Size );

				Self->string_memcpy( newmem, oldmem, len );

				Self->Priv_Mem_Free( oldmem );
			}
		}
	}

bailout:

	return(	newmem );
}

// --
