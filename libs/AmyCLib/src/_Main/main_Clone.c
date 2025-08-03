
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

struct Interface *_main_Clone( struct AmyCLibIFace *Self )
{
struct AmyCLibIFace *IFace;
struct libData *data;
S32 error;

	IExec->DebugPrintF( "_main_Clone\n" );

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

//	IExec->DebugPrintF( "_main_Clone 2 : Neg %ld, data %p, IFace %p, Self %p, bzerp %p\n", 
//		IFace->Data.NegativeSize, data, IFace, Self, IFace->strings_bzero );

	IFace->strings_bzero( data, sizeof( struct libData ));

	// --
	// This Init code is so simple and do not alloc anything
	// and its nice to have Data in a valid state even through
	// its only used after main/Startup have been run.

//	IExec->InitSemaphore( & data->PThread_Semaphore );
//	IExec->InitSemaphore( & data->netdb_Semaphore );
//	IExec->InitSemaphore( & data->FileSemaphore );
//	IExec->InitSemaphore( & data->LocaleSemaphore );
//	IExec->InitSemaphore( & data->MemSemaphore );
//	IDOS->DateStamp( & data->TimeClock_StartTime );
//	IExec->NewList( & data->ExitHeader );
//	IExec->NewList( & data->MemPools );

//	data->SignalAllocated = -1;
//	data->IAmyC = IFace;

	// --

	// Libraries only opens the Interface but do not run
	// main/Startup() .. which make String functions acceable.

	// So code setup that have to be available in libraries
	// and Programs is put here.

	// If code only have only available for Programs is put into
	// main/Startup().

	// Basicly this means .. Sockets, Files, Locale and Memory
	// is unavable for Libraries

	// String functions are avail for all that have IRA_C.
	// stubs code also call IRA_C directly for Strings

	// --

//	IExec->DebugPrintF( "_main_Clone 3\n" );

	error = FALSE;

bailout:

	if (( IFace ) && ( error ))
	{
		IFace->Expunge();
		IFace = NULL;
	}

//	IExec->DebugPrintF( "_main_Clone 99 : %p\n", IFace );

	return(	(PTR) IFace );
}

// --
