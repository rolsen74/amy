
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"

// --

PTR AMYFUNC _Main_Clone( struct AmyIUPIFace *Self )
{
struct AmyIUPIFace *IFace;
struct libData *data;
S32 error;

	IExec->DebugPrintF( ":: AmyIUP :: _Main_Clone ::\n" );

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

	memset( data, 0, sizeof( struct libData ));

	// --

	data->IFace = Self;


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
