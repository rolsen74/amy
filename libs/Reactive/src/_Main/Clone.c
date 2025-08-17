
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

extern const struct TagItem Main_Tags[];

// --

struct Interface * AMYFUNC _Main_Clone( struct ReactivePrivIFace *Self )
{
struct AmyCLibIFace *IFace;
struct libData *data;
S32 error;

	IExec->DebugPrintF( "Reactive : _Main_Clone\n" );

	error = TRUE;

	// --

	IFace = (PTR) IExec->MakeInterface( Self->Data.LibBase, Main_Tags );

	if ( ! IFace )
	{
		goto bailout;
	}

	IFace->Data.Flags |= IFLF_CLONED;

	// --

	data = (PTR)( (U32) IFace - IFace->Data.NegativeSize );

	IExec->DebugPrintF( "Reactive : _Main_Clone : IFace %p, Data %p\n", IFace, data );

	memset( data, 0, sizeof( struct libData ));

	// --

	error = FALSE;

bailout:

	if (( IFace ) && ( error ))
	{
		IFace->Expunge();
		IFace = NULL;
	}

	return(	(PTR) IFace );
}

// --
