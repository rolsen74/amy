
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
#include "Scan.h"

// --

static S32 my_Scan_Char_Peek( struct Intern *in )
{
// struct AmyCLibPrivIFace *Self;
S32 val;
U32 pos;
STR str;

	DODEBUGPRINTF( IExec->DebugPrintF( "my_Scan_Char_Peek\n" ); );

	/**/ if ( in->buffer )
	{
		// Buffer
		str = in->buffer;
		pos = in->bufferPos;
		val = str[pos];
	}
	else if ( in->stream )
	{
		// Stream

//		Self = in->Self;
		val = EOF;

		#ifdef DEBUG
		IExec->DebugPrintF( "my_Scan_Char_Peek : Implement Stream\n" );
		#endif
	}
	else
	{
		// Unknown
		val = EOF;

		#ifdef DEBUG
		IExec->DebugPrintF( "my_Scan_Char_Peek : Unknown\n" );
		#endif
	}

	return( val );

	#if 0

			if ( __Priv_Is_Buffer_Empty( Self, file ))
			{
// IExec->DebugPrintF( "ab\n" );
				goto input_failure;
			}

//			if (*fp->_p != c)
			if ( __Priv_Peek_Buffer( file ) != c )
			{
// IExec->DebugPrintF( "ac\n" );
				goto match_failure;
			}

//			fp->_r--, fp->_p++;
			__Priv_Skip_Bytes( Self, file, 1 );

	#endif

//			while (( __Priv_Is_Buffer_Empty( Self, file ) == 0 ) && Self->ctype_isspace( __Priv_Peek_Buffer(file) ))
//			{
//		// IExec->DebugPrintF( " 4\n" );
//		//			nread++, fp->_r--, fp->_p++;
//				nread++, __Priv_Skip_Bytes( Self, file, 1 );
//			}


//    if (ensure_has_char(Self,f) < 0) return -1;
//    return __Priv_Peek_Buffer(f);
}

// --
