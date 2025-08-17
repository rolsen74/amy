
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2014-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

static U32 Dir_Sort(
UNUSED	struct ReactiveIFace *Self,
UNUSED	struct RA_Class *cl,
UNUSED	struct RA_Object *obj,
UNUSED	struct RAP_DIR_Sort *msg,
UNUSED	struct DirClassData *cls,
		InstanceData *data )
{
struct ExamineData *dat1;
struct ExamineData *dat2;
struct List l;
U32 retval;

	IExec->DebugPrintF( "Dir_Sort\n" );

	// --

	IExec->NewList( &l );

	// -- Sort - Type then Name --

	dat1 = (PTR) IExec->GetHead( &data->Header );

	while( dat1 )
	{
		dat2 = (PTR) IExec->GetSucc( (PTR) dat1 );

		while( dat2 )
		{
			if ( EXD_IS_FILE( dat1 ))
			{
				if ( EXD_IS_FILE( dat2 ))
				{
					if ( stricmp( dat1->Name, dat2->Name ) > 0 )
					{
						dat1 = dat2;
					}
				}
				else
				{
					dat1 = dat2;
				}
			}
			else
			{
				if ( EXD_IS_FILE( dat2 ) == 0 )
				{
					if ( stricmp( dat1->Name, dat2->Name ) > 0 )
					{
						dat1 = dat2;
					}
				}
			}

			dat2 = (PTR) IExec->GetSucc( (PTR) dat2 );
		}

		IExec->Remove(		(PTR) dat1 );
		IExec->AddTail( &l, (PTR) dat1 );

		dat1 = (PTR) IExec->GetHead( &data->Header );
	}

	// --

	while(( dat1 = (PTR) IExec->RemHead( &l )))
	{
		IExec->AddTail( &data->Header, (PTR) dat1 );
	}

	// --

	retval = RAV_General_NotImplemented;

	return(	retval );
}
