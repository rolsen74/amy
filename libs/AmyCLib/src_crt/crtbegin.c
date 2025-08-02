
/*
 * Portable ISO 'C' (1994) runtime library for the Amiga computer
 * Copyright (c) 2002-2015 by Olaf Barthel <obarthel (at) gmx.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   - Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   - Neither the name of Olaf Barthel nor the names of contributors
 *     may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/****************************************************************************/

#include <workbench/startup.h>

#include <proto/AmyCLib.h>

//#include "Library.h"
//#include "ReactiveC_rev.h"

extern int main( int argc, char **argv );

/****************************************************************************/

struct Library *		DOSBase			= NULL;
struct Library *		SysBase			= NULL;
struct Library *		UtilityBase		= NULL;
struct Library *		RA_CBase		= NULL;

struct DOSIFace *		IDOS			= NULL;
struct ExecIFace *		IExec			= NULL;
struct UtilityIFace *	IUtility		= NULL;
struct RA_CIFace *		IRA_C			= NULL;

struct RACLibStruct *	__RAPublicData	= NULL;

/****************************************************************************/

/*
 * Dummy constructor and destructor array. The linker script will put these at the
 * very beginning of section ".ctors" and ".dtors". crtend.o contains a similar entry
 * with a NULL pointer entry and is put at the end of the sections. This way, the init
 * code can find the global constructor/destructor pointers.
 */

static void (*__CTOR_LIST__[1]) (void) __attribute__(( used, section(".ctors"), aligned(sizeof(void (*)(void))) ));
static void (*__DTOR_LIST__[1]) (void) __attribute__(( used, section(".dtors"), aligned(sizeof(void (*)(void))) ));
//static void (*__CTOR_LIST__[1]) (void) __attribute__(( used, section(".init_array"), aligned(sizeof(void (*)(void))) ));
//static void (*__DTOR_LIST__[1]) (void) __attribute__(( used, section(".fini_array"), aligned(sizeof(void (*)(void))) ));

/****************************************************************************/

int _start( char *args, int arglen, struct ExecBase *mySysBase )
{
// struct UtilityIFace *myIUtility;
// struct ExecIFace *myIExec;
// struct RA_CIFace *myIRA_C;
// struct WBStartup *wbmsg;
// struct DOSIFace *myIDOS;
// struct Library *myUtilityBase;
// struct Library *myRA_CBase;
// struct Library *myDOSBase;
// struct libData *data;
// struct Process *self;
// //char *errtxt;
int retval;
// int i;

// 	// --

	retval			= RETURN_FAIL;
// //	errtxt			= NULL;
// 	wbmsg			= NULL;
// 	SysBase 		= (APTR) mySysBase;
// 	IExec = myIExec	= (APTR) mySysBase->MainInterface;
// 	self			= (APTR) myIExec->FindTask( NULL );

// 	myDOSBase		= NULL;
// 	myUtilityBase	= NULL;
// 	myRA_CBase		= NULL;
// 	myIUtility		= NULL;
// 	myIRA_C			= NULL;
// 	myIDOS			= NULL;

// 	// --

// 	if ( self->pr_CLI == 0 )
// 	{
// 		struct MsgPort * mp = & self->pr_MsgPort;

// 		myIExec->WaitPort( mp );

// 		wbmsg = (APTR) myIExec->GetMsg( mp );
// 	}
// 	else
// 	{
// 		wbmsg = NULL;
// 	}

// 	// --

// 	DOSBase = myDOSBase = myIExec->OpenLibrary( "dos.library", 53 );
// 	IDOS = myIDOS = (APTR) myIExec->GetInterface( myDOSBase, "main", 1, NULL );

//     if ( myIDOS == NULL )
//     {
// 	    // No point in setting error txt.. as we can't print it
// 	    goto bailout;
//     }

// 	// -- Open ReactiveC

// 	AmyCBase = myRA_CBase = myIExec->OpenLibrary( RACLIBNAME, 0 );

// 	if ( AmyCBase->lib_Version < VERSION )
// 	{
// //		  errtxt = "ReactiveC version check failure. Only version 1+ is supported\n";
// 		goto bailout;
// 	}

// 	IAmyC = myIRA_C = (APTR) myIExec->GetInterface( myRA_CBase, "main", 1, NULL );

// 	if ( myIRA_C == NULL )
// 	{
// //		  errtxt = "Error Getting ReactiveC Interface\n";
// 		goto bailout;
// 	}

// 	// --

// 	if ( myIRA_C -> _Priv_Startup_Init() == FALSE )
// 	{
// //		  errtxt = "Error ,,,,\n";
// 		goto bailout;
// 	}

// 	// --

//     UtilityBase = myUtilityBase = myIExec->OpenLibrary( "utility.library", 53 );
//     IUtility = myIUtility = (APTR) myIExec->GetInterface( myUtilityBase, "main", 1, NULL );

//     if ( myIUtility == NULL )
//     {
// //		  errtxt = "Error Opening Utility Library\n";
// 	    goto bailout;
//     }

// 	// --

// 	data = (APTR)( (uint32) myIRA_C - IRA_C->Data.NegativeSize );

// 	if ( myIRA_C -> setjmp_setjmp( data->ExitJumpBuffer ) == 0 )
//     {
// 		// -- Count Constructors

// 		i = 0;

// 		while( __CTOR_LIST__[ i + 1 ] )
// 		{
// 			i++;
// 		}

// 		// -- Run Constructors

// 		while( i )
// 		{
// 			__CTOR_LIST__[ i ]();

// 			i--;
// 		}

// 		// -- Start

// 		retval = myIRA_C -> _Priv_Startup_Main(
// 			& main,
// 			args,
// 			arglen,
// 			wbmsg,
// 			& __RAPublicData
// 		);
//     }

// 	// -- Run Destructiors

// 	i = 1;

// 	while( __DTOR_LIST__[i] )
// 	{
// 		if ( myIRA_C -> setjmp_setjmp( data->ExitJumpBuffer ) == 0 )
// 		{
// 			__DTOR_LIST__[ i ]();
// 		}

// 		i++;
// 	}

// 	// -- Exit

// bailout:

// 	// --

// //	  errtxt is only set if we have DOS open
// //	  if ( errtxt )
// //	  {
// //		  myIDOS->PutStr( errtxt );
// //	  }

// 	// --

//     if ( myIUtility )
//     {
// 	    myIExec->DropInterface( (APTR) myIUtility );
//     }

//     if ( myUtilityBase )
//     {
// 	    myIExec->CloseLibrary( myUtilityBase );
//     }

// 	// --

// 	if ( myIRA_C )
// 	{
// 		myIRA_C -> _Priv_Startup_Exit();

// 		myIExec->DropInterface( (APTR) myIRA_C );
// 	}

// 	if ( myRA_CBase )
// 	{
// 		myIExec->CloseLibrary( myRA_CBase );
// 	}

// 	// --

//     if ( myIDOS )
//     {
// 	    myIExec->DropInterface( (APTR) myIDOS );
//     }

//     if ( myDOSBase )
//     {
// 	    myIExec->CloseLibrary( myDOSBase );
//     }

// 	// --

// 	if ( wbmsg )
// 	{
// 		myIExec->Forbid();

// 		myIExec->ReplyMsg( (APTR) wbmsg );
// 	}

// 	// --

	return( retval );
}

/****************************************************************************/

