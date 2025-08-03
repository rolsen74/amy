
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

S32 _main__Priv_Startup_Main(
	struct AmyCLibIFace *Self,
	int main( int, char ** ),
	char *args,
	int arglen,
	PTR msg,
	struct RACLibStruct **pd )
{
S32 prg_rc;		// (User) Program Return Code

// struct WBStartup *wbmsg;
// struct ExitNode *enode;
// struct libData *data;
// struct Process *me;
// STRPTR *argv;
// int32 argc;

// 	ENTER( 8 );

// 	wbmsg = msg;

// 	data = (APTR)( (uint32) Self - Self->Data.NegativeSize );

// 	*pd = data->buf_PublicData;

	IExec->DebugPrintF( "_main__Priv_Startup_Main\n" );

	prg_rc = 20;	// DOS return error code

// 	// - Get WB Message

// 	me = (APTR) IExec->FindTask( NULL );

// 	SHOWMSG( 3, "Main 11" );

// 	if ( me->pr_CLI == 0 )
// 	{
// 		data->ProgramName = wbmsg->sm_ArgList[0].wa_Name;
// 	}
// 	else
// 	{
// 		wbmsg = NULL;

// 		data->ProgramNameBuffer = Self->_Priv_Mem_Alloc( 256 );

// 	    if ( data->ProgramNameBuffer == NULL )
// 	    {
// 		    goto bailout;
// 	    }

// 	    IDOS->GetCliProgramName( data->ProgramNameBuffer, 255 );

// 	    data->ProgramName = data->ProgramNameBuffer;
// 	}

// 	// --

// 	data->ExitSet = TRUE;

// 	if ( Self->setjmp_setjmp( data->ExitJumpBuffer ))
//     {
// 		prg_rc = data->ExitReturnCode;
// 	    goto bailout;
//     }

// 	// --

// 	argc = 0;
// 	argv = NULL;

// 	if ( InitArgs( Self, data, wbmsg, args, arglen, & argv, & argc ))
// 	{
// 		SHOWMSG( 3, "Running main()" );

// 		prg_rc = main( argc, argv );

// 		// --

// 		// Should only run on normal exit. ie. with exit().
// 		// not when abort() is called.
// 		// Run in reverse order.
// 		while(( enode = (APTR) IExec->RemTail( & data->ExitHeader ) ))
// 		{
// 			(*enode->Function)();
// 		}
// 	}

// bailout:

// 	RETURN( 8,	prg_rc );
 	return(	prg_rc );
}
