
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"

// --

PTR AMY_FUNC _Main_Clone( struct AmyIUPIFace *Self )
{
struct AmyIUPIFace *IFace;
struct AmyTaskInfo *ati;
struct libData *data;
struct Task *opener_task;
S32 error;

	IExec->DebugPrintF( ":: AmyIUP :: _Main_Clone ::\n" );

	error = TRUE;
	IFace = NULL;

	// --
	// Amy C Library check

	opener_task = IExec->FindTask( NULL );

	if ( ! opener_task->tc_UserData )
	{
		IExec->DebugPrintF( ":: AmyIUP :: tc_UserData is NULL\n" );
		goto bailout;
	}

	ati = (PTR) opener_task->tc_UserData;

	if ( ati->ati_ID != Amy_ATI_ID )
	{
		IExec->DebugPrintF( ":: AmyIUP :: Invalid ATI ID\n" );
		goto bailout;
	}

	IExec->DebugPrintF( ":: AmyIUP :: ATI Check passed\n" );

	// --

	IFace = (PTR) IExec->MakeInterface( Self->Data.LibBase, Main_Tags );

	if ( ! IFace )
	{
		goto bailout;
	}

	IFace->Data.Flags |= IFLF_CLONED;

	// --

	data = (PTR)( (U32) IFace - IFace->Data.NegativeSize );

	IExec->DebugPrintF( ":: AmyIUP :: memset : IFace %p : Data : %p : Size %ld\n", IFace, data, (S32) IFace->Data.NegativeSize );
	memset( data, 0, sizeof( struct libData ));

	// --

	data->IFace = IFace;




	// --

	error = FALSE;

bailout:

	if (( IFace ) && ( error ))
	{
		IFace->Expunge();
		IFace = NULL;
	}

	IExec->DebugPrintF( ":: AmyIUP :: New IFace %p\n", IFace );

	return(	(PTR) IFace );
}

// --
