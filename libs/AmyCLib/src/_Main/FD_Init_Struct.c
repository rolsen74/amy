
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

extern struct PrivInterface		Priv_FD_Interface_File;
extern struct PrivInterface		Priv_FD_Interface_Socket;
extern struct PrivInterface		Priv_FD_Interface_String;

// --
// File Descriptor

S32 AMY_FUNC _generic__Priv_FD_Init_Struct( struct AmyCLibIFace *Self, struct FileStruct *file, U32 id )
{
struct PrivInterface *pi;
//FILE *file;
S32 retval;
S32 initid;

	retval = FALSE;

//	file = file_ptr;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FD_Init_Struct : File %p, ID $%08lx\n", file, id ); );

	if ( ! file )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FD_Init_Struct : NULL Pointer, ID $%08lx\n", id ); );
		goto bailout;
	}

	if (( id != ID_FILE )
	&&	( id != ID_SOCKET )
	&&	( id != ID_STRING ))
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FD_Init_Struct() : File %p, Error Illegal ID (%08lx)\n", file, id ); );
		goto bailout;
	}

	Self->string_memset( file, 0, sizeof( struct FileStruct ));

	IExec->InitSemaphore( & file->pf_Semaphore );

	// --

	/**/ if ( id == ID_FILE )
	{
		pi = & Priv_FD_Interface_File;
		initid = 0;
	}
//	else if ( ID == ID_SOCKET )
//	{
//		pi = & Priv_FD_Interface_Socket;
//		initid = -1;
//	}
//	else if ( id == ID_STRING )
//	{
//		pi = & Priv_FD_Interface_String;
//		initid = 0;
//	}
	else
	{
		IExec->DebugPrintF( "Invalid File ID $%08lx\n", id );
		goto bailout;
	}

	// --

	Self->string_memcpy( & file->pf_Interface, pi, sizeof( struct PrivInterface ));

	file->pf_FileType = id;
	file->pf_StructID = ID_PRIVFILE;
	file->pf_Buffer = & file->pf_BufferDefault;
	file->pf_BufferSize = 1;
	file->pf_Handle.pf_File = initid;
	file->pf_ArrayPos = -1;
	
	// --

	#if 0
	IExec->DebugPrintF( "pi_Close   : %p\n", file->pf_Interface.pi_Close );
	IExec->DebugPrintF( "pi_Read    : %p\n", file->pf_Interface.pi_Read );
	IExec->DebugPrintF( "pi_Write   : %p\n", file->pf_Interface.pi_Write );
	IExec->DebugPrintF( "pi_Seek    : %p\n", file->pf_Interface.pi_Seek );
	IExec->DebugPrintF( "pi_GetPos  : %p\n", file->pf_Interface.pi_GetPos );
	IExec->DebugPrintF( "pi_Examine : %p\n", file->pf_Interface.pi_Examine );

	IExec->DebugPrintF( "pi_Close   : %p\n", pi->pi_Close );
	IExec->DebugPrintF( "pi_Read    : %p\n", pi->pi_Read );
	IExec->DebugPrintF( "pi_Write   : %p\n", pi->pi_Write );
	IExec->DebugPrintF( "pi_Seek    : %p\n", pi->pi_Seek );
	IExec->DebugPrintF( "pi_GetPos  : %p\n", pi->pi_GetPos );
	IExec->DebugPrintF( "pi_Examine : %p\n", pi->pi_Examine );
	#endif

	retval = TRUE;

bailout:

	return( retval );
}
