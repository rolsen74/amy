
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

#include "Startup_Free_Signal.c"
#include "Startup_Free_Locale.c"
#include "Startup_Free_Memory.c"
#include "Startup_Free_PublicData.c"

// --

void AMYFUNC _generic__Priv_Startup_Free( struct AmyCLibPrivIFace *Self )
{
struct AmyTaskInfo *ati;
struct libData *data;
struct Task *opener_task;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Startup_Free\n" ); );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	if ( data->cli_ArgString )
	{
		IExec->FreeVec( data->cli_ArgString );
		data->cli_ArgString = NULL;
	}

	// --

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Startup_Free : Signal\n" ); );

	myFree_Signal( Self, data );

	// --

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Startup_Free : Locale\n" ); );

	myFree_Locale( Self, data );

	// --

	Self->Priv_Print_Log();

	// --

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Startup_Free : PublicData\n" ); );

	myFree_PublicData( Self, data );

	// --

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_Startup_Free : Memory\n" ); );

	myFree_Memory( Self, data );

	// --

	if ( data->UserDataSet )
	{
		opener_task = IExec->FindTask( NULL );
		opener_task->tc_UserData = NULL;
		data->UserDataSet = FALSE;
	}

	// --

	return;
}
