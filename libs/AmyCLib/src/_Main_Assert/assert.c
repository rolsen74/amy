
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

// --

#include "src/All.h"

// --

void AMYFUNC _generic_assert_assert(
	struct AmyCLibPrivIFace *Self,
	const char *filename,
	int linenumber,
	const char *function,
	const char *expression )
{
struct EasyStruct es;
struct libData *data;
struct Process *me;
PTR wbmsg;
STR fmt;

	IExec->DebugPrintF( "_generic_assert_assert\n" );

	DOFUNCTIONLOG( LOG_FUNC_assert );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	if ( ! IntuitionBase )
	{
		IntuitionBase = IExec->OpenLibrary( "intuition.library", 50 );
	}

	if (( IntuitionBase ) && ( ! IIntuition ))
	{
		IIntuition = (PTR) IExec->GetInterface( IntuitionBase, "main", 1, NULL );
	}

	fmt = "Assertion of condition\n\"%s\"\nfailed in file \"%s\", line %ld\n";

	IExec->DebugPrintF( fmt, expression, filename, linenumber );

	if ( IIntuition )
	{
		Self->string_memset( & es, 0, sizeof( es ));

		es.es_StructSize	= sizeof( es );
		es.es_Title			= (STR) function;
		es.es_TextFormat	= (STR) fmt;
		es.es_GadgetFormat	= (STR) "Sorry";

		IIntuition->EasyRequest( NULL, & es, NULL, expression, filename, linenumber );
	}

	if ( ! data->ExitSet )
	{
		IExec->DebugPrintF( "_generic_assert_assert : 2 :\n" );

		// Reply WB Message

		me = (PTR) IExec->FindTask( NULL );

		if ( ! me->pr_CLI )
		{
			struct MsgPort * mp = & me->pr_MsgPort;

			IExec->DebugPrintF( "_generic_assert_assert : 3 : reply wb msg\n" );

			IExec->WaitPort( mp );

			wbmsg = IExec->GetMsg( mp );

			IExec->ReplyMsg( wbmsg );
		}
	}

	IExec->DebugPrintF( "_generic_assert_assert : 99 : Exit %p\n", Self->stdlib_exit );

	Self->stdlib_exit( EXIT_FAILURE );
}

// --
