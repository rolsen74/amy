
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

#include "Startup_Main_Args.c"

// --

S32 AMYFUNC _generic__Priv_Startup_Main(
	struct AmyCLibIFace *Self,
	int main( int, char ** ),
	char *args UNUSED,
	int arglen UNUSED,
	PTR msg,
	struct _AmyCLibPublic **pd )
{
struct WBStartup *wbmsg;
struct ExitNode *enode;
struct libData *data;
struct Process *me;
STR *argv;
S32 prg_rc;		// (User) Program Return Code
S32 argc;

	IExec->DebugPrintF( "_generic__Priv_Startup_Main : pd %p, args '%s'\n", pd, (args)?args:"<NULL>" );

	prg_rc = 20;	// DOS return error code

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	*pd = data->buf_PublicData;

	// --

	me = (PTR) IExec->FindTask( NULL );

	if ( ! me->pr_CLI )
	{
	 	wbmsg = msg;

		data->ProgramName = wbmsg->sm_ArgList[0].wa_Name;
	}
	else
	{
		wbmsg = NULL;

		data->ProgramNameBuffer = Self->Priv_Mem_Alloc( 256 );

		if ( ! data->ProgramNameBuffer )
		{
			goto bailout;
		}

		IDOS->GetCliProgramName( data->ProgramNameBuffer, 255 );

		data->ProgramName = data->ProgramNameBuffer;
	}

	// --

	data->ExitSet = TRUE;

	if ( Self->setjmp_setjmp( data->ExitJumpBuffer ))
	{
		prg_rc = data->ExitReturnCode;
		goto bailout;
	}

	// --

	argc = 0;
	argv = NULL;

	if ( InitArgs( Self, data, wbmsg, & argv, & argc ))
	{
		IExec->DebugPrintF( "Calling Main( argc %ld, argv %p )\n", argc, argv );
		prg_rc = main( argc, argv );

		// --

		// Should only run on normal exit. ie. with exit().
		// not when abort() is called.
		// Run in reverse order.
		while(( enode = (PTR) IExec->RemTail( & data->ExitHeader ) ))
		{
			(*enode->Function)();
		}
	}

bailout:

 	return(	prg_rc );
}
