
/*
** SPDX-License-Identifier: BSD-3-Clause
** Modifications (c) 2025 Rene W. Olsen
** Part of Amy C Lib
**
** Based on:
**
** Portable ISO 'C' (1994) runtime library for the Amiga computer
** Copyright (c) 2002-2015 by Olaf Barthel <obarthel (at) gmx.net>
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
**   - Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**
**   - Neither the name of Olaf Barthel nor the names of contributors
**     may be used to endorse or promote products derived from this
**     software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
** LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
** CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
** SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
** INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
** POSSIBILITY OF SUCH DAMAGE.
**
*/

/****************************************************************************/

#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/AmyCLib.h>
#include <workbench/startup.h>

#include "src/All.h"

extern int main( int argc, char **argv );

/****************************************************************************/

struct Library *		DOSBase		USED = NULL;	// A
struct Library *		SysBase		USED = NULL;	// B
//struct Library *		UtilityBase	USED = NULL;	// C
struct Library *		AmyCBase	USED = NULL;	// D

struct DOSIFace *		IDOS		USED = NULL;	// E
struct ExecIFace *		IExec		USED = NULL;	// F
//struct UtilityIFace *	IUtility	USED = NULL;	// G
struct AmyCLibPrivIFace *	IAmyCLib	USED = NULL;	// H

struct _AmyCLibPublic *	__AmyCPublicData = NULL;

/****************************************************************************/

/*
** Dummy constructor and destructor array. The linker script will put these at the
** very beginning of section ".ctors" and ".dtors". crtend.o contains a similar entry
** with a NULL pointer entry and is put at the end of the sections. This way, the init
** code can find the global constructor/destructor pointers.
*/

static void (*__CTOR_LIST__[1]) (void) __attribute__(( used, section(".ctors"), aligned(sizeof(void (*)(void))) ));
static void (*__DTOR_LIST__[1]) (void) __attribute__(( used, section(".dtors"), aligned(sizeof(void (*)(void))) ));
//static void (*__CTOR_LIST__[1]) (void) __attribute__(( used, section(".init_array"), aligned(sizeof(void (*)(void))) ));
//static void (*__DTOR_LIST__[1]) (void) __attribute__(( used, section(".fini_array"), aligned(sizeof(void (*)(void))) ));

/****************************************************************************/

int _start( STR arg_string, S32 arg_length, struct ExecBase *mySysBase )
{
struct ExecIFace *		myIExec;		// 0
struct Process *		self;			// 1  - Own Program Task/Process adr
struct MsgPort *		wb_mp;			// 2  - Workbench MsgPort
//struct Library *		myUtilityBase;	// 3
//struct UtilityIFace *	myIUtility;		// 4
struct Library *		myAmyCBase;		// 5
struct Library *		myDOSBase;		// 6
struct AmyCLibIFace *	myIAmyC;		// 7
struct DOSIFace *		myIDOS;			// 8
char *					errtxt;			// 9  - Error String
int						prg_rc;			// 10 - Program Return Code
struct WBStartup *		wb_msg;			// 11 - Workbench Message
U32						ver;			// 12 - Min. Version 
struct libData *		data;			// 13
U32						i;				// 14

	// -- Init Stack values in same order as above

	myIExec			= (PTR) mySysBase->MainInterface;	// 0
	self			= (PTR) myIExec->FindTask( NULL );	// 1
	wb_mp			= (PTR) & self->pr_MsgPort;			// 2 - Only valid for Processes
//	myUtilityBase	= NULL;				// 3
//	myIUtility		= NULL;				// 4
	myAmyCBase		= NULL;				// 5
	myDOSBase		= NULL;				// 6
	myIAmyC			= NULL;				// 7
	myIDOS			= NULL;				// 8
	errtxt			= NULL;				// 9  - Error String
	prg_rc			= RETURN_FAIL;		// 10 - Program Return Code

	// -- Init WBMsg last

	if ( ! self->pr_CLI )
	{
		myIExec->WaitPort( wb_mp );

		wb_msg = (PTR) myIExec->GetMsg( wb_mp );	// 11
	}
	else
	{
		wb_msg = NULL;	// 11
	}

	// -- 

	myDOSBase		= (PTR) myIExec->OpenLibrary( "dos.library", 50 );
	myIDOS			= (PTR) myIExec->GetInterface( myDOSBase, "main", 1, NULL );

	if ( ! myIDOS )
	{
		// No point in setting error txt.. as we can't print it
		goto bailout;
	}

	// -- Open ReactiveC

 	myAmyCBase		= (PTR) myIExec->OpenLibrary( "AmyCLib.library", 0 );

	if ( ! myAmyCBase )
	{
		errtxt = "Error: Opening AmyC library\n";
		goto bailout;
	}

	ver = (( myAmyCBase->lib_Version << 16 ) | ( myAmyCBase->lib_Revision ));

	if ( ver < CRT_MIN_VERSION )	// ver 0001.0000
	{
		errtxt = "Error: AmyCLib version failure\n";
		goto bailout;
	}

 	myIAmyC			= (PTR) myIExec->GetInterface( myAmyCBase, "main", 1, NULL );

 	if ( ! myIAmyC )
 	{
		errtxt = "Error: Getting AmyC Interface\n";
		goto bailout;
	}

	// -- Init Global Pointers

	DOSBase 		= (PTR) myDOSBase;			// A
	SysBase			= (PTR) mySysBase;			// B
	AmyCBase		= (PTR) myAmyCBase;			// D
	IDOS			= (PTR) myIDOS;				// E
	IExec			= (PTR) myIExec;			// F
	IAmyCLib		= (PTR) myIAmyC;			// H

	// --

	if ( ! myIAmyC->Priv_Startup_Init( arg_string, -1 ))	// Enable everything
	{
		errtxt = "Error: Initialization of the AmyCLib library failed.\n";
		goto bailout;
	}

	// --

	data = (PTR)( (U32) myIAmyC - myIAmyC->Data.NegativeSize );

	if ( ! myIAmyC->setjmp_setjmp( data->ExitJumpBuffer ))
	{
		// -- Count Constructors

		i = 0;

		while( __CTOR_LIST__[ i + 1 ] )
		{
			i++;
		}

		// -- Run Constructors

		while( i )
		{
// myIExec->DebugPrintF( "Calling CTOR( %p #%ld )\n", __CTOR_LIST__[ i ], i );

			__CTOR_LIST__[ i ]();

			i--;
		}

 		// -- Start

// myIExec->DebugPrintF( "Calling Main()\n" );

		prg_rc = myIAmyC->Priv_Startup_Main(
			& main,
			arg_string,
			arg_length,
			wb_msg,
			& __AmyCPublicData
		);

// myIExec->DebugPrintF( "Returned Main( rc #%ld )\n", prg_rc );

	}

	// -- Run Destructiors

	i = 1;

	while( __DTOR_LIST__[i] )
	{
		if ( ! myIAmyC->setjmp_setjmp( data->ExitJumpBuffer ))
		{
// myIExec->DebugPrintF( "Calling DTOR( %p #%ld )\n", __DTOR_LIST__[ i ], i );

			__DTOR_LIST__[ i ]();
		}

		i++;
	}

	// -- Exit

bailout:

	// --

	if ( errtxt )
	{
		// errtxt is only set if we have DOS open
		myIDOS->PutStr( errtxt );
	}

	// --

	if ( myIAmyC )
	{
//		Moved into Expunge Infterface
//		myIAmyC->Priv_Startup_Free();	

		myIExec->DropInterface( (PTR) myIAmyC );
	}

	if ( myAmyCBase )
	{
		myIExec->CloseLibrary( myAmyCBase );
	}

	// --

	if ( myIDOS )
	{
		myIExec->DropInterface( (PTR) myIDOS );
	}

	if ( myDOSBase )
	{
		myIExec->CloseLibrary( myDOSBase );
	}

	// --

	if ( wb_msg )
	{
		myIExec->Forbid();
		myIExec->ReplyMsg( (PTR) wb_msg );
	}

	// --

	return( prg_rc );
}

/****************************************************************************/
