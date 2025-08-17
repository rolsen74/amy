
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
// File Descriptor

static S32 myStat( struct AmyCLibIFace *Self, struct PrivFile *file, struct stat *stat )
{
struct ExamineData *ed;
S32 retval;

	IExec->DebugPrintF( "FD_IFC_File_Stat\n" );

	retval = -1;

	ed = NULL;

	if (( ! file ) || ( file->pf_StructID != ID_PRIVFILE ))
	{
		IExec->DebugPrintF( "%s:%04ld: Invalid file id\n", __FILE__, __LINE__ );
		goto bailout;
	}

	if (( ! file ) || ( ! stat ))
	{
		IExec->DebugPrintF( "myStat Err 1\n" );
		goto bailout;
	}

	ed = IDOS->ExamineObjectTags(
		EX_FileHandleInput, file->pf_Handle.pf_File,
		TAG_END
	);

	if ( ! ed )
	{
		IExec->DebugPrintF( "myStat Err 2\n" );
		goto bailout;
	}

	if ( Self->Priv_Convert_ED_to_Stat( ed, stat ) < 0 )
	{
		IExec->DebugPrintF( "myStat Err 3\n" );
		goto bailout;
	}

	retval = 0;

bailout:

	if ( ed )
	{
		IDOS->FreeDosObject( DOS_EXAMINEDATA, ed );
	}

	return( retval );
}

