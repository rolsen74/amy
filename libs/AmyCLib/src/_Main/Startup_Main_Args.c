
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

static S32 is_space_uc( S32 c ) 
{
	return(	( c == '\t' )
	||		( c == '\r' ) 
	||		( c == '\n' )
	||		( c == '\v' )
	||		( c == '\f' )
	||		( c == 0x20 )
	|| 		( c == 0xA0 ));
}

// --

static STR myClone_ArgString( void )
{
U32 start;
U32 end;
STR arg;
STR str;
S32 len;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "myClone_ArgString\n" ); );

	str = NULL;
	arg = IDOS->GetArgStr();

	if (( ! arg ) || ( ! arg[0] ))
	{
		IExec->DebugPrintF( "No Arg String?? %p\n", arg );
		goto bailout;
	}

	// Find String Start 
	// skipping white spaces

	start = 0;

	while( TRUE )
	{
		if ( is_space_uc( (U8) arg[start] ))
		{
			start++;
		}
		else
		{
			break;
		}
	}

	// Find String End

	end = start;

	while( TRUE )
	{
		if ( arg[end] )
		{
			end++;
		}
		else
		{
			break;
		}
	}

	// --
	// Remove White Spaces + NL at end

	while( start < end )
	{
		if ( is_space_uc( (U8) arg[end-1] ))
		{
			end--;
		}
		else
		{
			break;
		}
	}

	// --

	len = end - start;

	if ( len < 0 )
	{
		IExec->DebugPrintF( "Start >= End ( %ld >= %ld )\n", start, end );
		goto bailout;
	}

	// Use Global Alloc here
	str = IExec->AllocVecTags( len + 1,
		TAG_END
	);

	if ( ! str )
	{
		IExec->DebugPrintF( "Error allocating memory (%ld bytes)\n", len + 1 );
		goto bailout;
	}

	if ( len > 0 )
	{
		IExec->CopyMem( & arg[start], str, len );
	}

	str[len] = 0;

bailout:

	return( str );
}

// --

static U32 myCount_StringArgs( STR str, U8 escape )
{
U32 args;
U32 cnt;
U8 mark;
U8 c;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "myCount_StringArgs\n" ); );

	cnt = 0;
	args = 0;

	while( TRUE )
	{
		// Skip White space

		while( is_space_uc( (U8) *str ))
		{
			str++;
		}

		// End of String?

		if ( ! *str )
		{
			break;
		}

		// Got one more arg
		cnt++;

		c = *str;
		if (( c == 0x22 )	// "
		||	( c == 0x27 )	// '
		||	( c == 0x60 ))	// `
		{
			// Skip mark
			mark = *str++;

			while( TRUE )
			{
				c = *str;
				
				if ( ! c )
				{
					break;
				}

				if ( c == mark )
				{
					break;
				}

				if (( c == escape ) && ( str[1] ))
				{
					str++;
				}

				str++;
			}

			if ( c != mark )
			{
				// hmm should this be an error??
				IExec->DebugPrintF( "Missing end marker 1\n" );
//				goto bailout;
			}
			else
			{
				str++;
			}
		}
		else
		{
			// Normal no space arg

			while(( *str ) && ( ! is_space_uc( (U8) *str )))
			{
				str++;
			}
		}
	}

	args = cnt + 1;

// bailout:

	return( args );
}

// --

static S32 myFill_StringArgs( struct libData *data, STR str, STR *_argv, U32 _argc, U8 escape )
{
S32 retval;
U32 idx;
STR out;
U8 mark;
U8 c;
U8 d;

	retval = FALSE;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "myFill_StringArgs\n" ); );

	if (( ! str ) || ( ! _argv ) ||( ! _argc ))
	{
		IExec->DebugPrintF( "NULL Pointer\n" );
		goto bailout;
	}

	idx = 0;
	_argv[idx++] = data->ProgramName;

	while( TRUE )
	{
		// Skip White space

		while( is_space_uc( (U8) *str ))
		{
			str++;
		}

		// End of String?

		if ( ! *str )
		{
			break;
		}

		if ( idx >= _argc )
		{
			break;
		}

		c = *str;
		if (( c == 0x22 )	// "
		||	( c == 0x27 )	// '
		||	( c == 0x60 ))	// `
		{
			// Skip mark
			mark = *str++;

			_argv[idx++] = str;

			out = str;

			while( TRUE )
			{
				c = *str;
				
				if ( ! c )
				{
					break;
				}

				if ( c == mark )
				{
					*out++ = 0;
					break;
				}

				if (( c == escape ) && ( str[1] ))
				{
					d = str[1];

					/**/ if (( d == 'e' ) || ( d == 'E' ))
					{
						*out++ = 0x1b;	// ESC
					}
					else if (( d == 'n' ) || ( d == 'N' ))
					{
						*out++ = '\n';	// NewLine
					}
					else
					{
						*out++ = d;
					}

					str += 2;
				}
				else
				{
					*out++ = *str++;
				}
			}

			if ( c != mark )
			{
				// hmm should this be an error??
				IExec->DebugPrintF( "Missing end marker 2\n" );
//				goto bailout;
			}
			else
			{
				str++;
			}
		}
		else
		{
			// Normal no space arg

			_argv[idx++] = str;

			while(( *str ) && ( ! is_space_uc( (U8) *str )))
			{
				str++;
			}

			if ( *str )
			{
				*str++ = 0;
			}
		}
	}

	// NULL terminate, so we can avoid mem clear
	_argv[idx++] = NULL;

	retval = TRUE;

bailout:

	return( retval );
}

// --

static S32 myInit_CLI( struct libData *data, STR **argv_ptr, S32 *argc_ptr )
{
STR command_line;
S32 retval;
STR *_argv;
S32 _argc;
U32 cnt;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "myInit_CLI\n" ); );

	retval = FALSE;

	_argc = 0;
	_argv = NULL;

	// -- 
	// Copy String

	command_line = myClone_ArgString();

	if ( ! command_line )
	{
		IExec->DebugPrintF( "myClone_ArgString failed\n" );
		goto bailout;
	}

	// -- Count args
	// Min 1 for Program name + args, 0 = Error

	cnt = myCount_StringArgs( command_line, '*' );

	if ( cnt < 1 )
	{
		IExec->DebugPrintF( "myCount_StringArgs failed : arg cnt %lu\n", cnt );
		goto bailout;
	}

	// --

	// Use Global Alloc here
	_argv = IExec->AllocVecTags( sizeof( PTR ) * ( cnt + 1 ),
//		AVT_Clear, 0,
		TAG_END
	);

	if ( ! _argv )
	{
		IExec->DebugPrintF( "Error allocating memory\n" );
		goto bailout;
	}

	// --

	if ( ! myFill_StringArgs( data, command_line, _argv, cnt, '*' ))
	{
		IExec->DebugPrintF( "myFill_StringArgs failed\n" );
		goto bailout;
	}

	// --

	data->cli_ArgString = command_line;

	_argc = cnt;

	retval = TRUE;

	#ifdef DEBUG
{
	for( U32 oo=0 ; oo<cnt ; oo++ )
	{
		IExec->DebugPrintF( "Idx %2ld : %s\n", oo, (_argv[oo])?_argv[oo]:"<NULL>" );
	}
}
	#endif

bailout:

	if ( ! retval ) 
	{
		if ( _argv )
		{
			IExec->FreeVec( _argv );
			_argv = NULL;
		}

		if ( command_line )
		{
			IExec->FreeVec( command_line );
			command_line = NULL;
		}
	}

	if ( argv_ptr )
	{
		*argv_ptr = _argv;
	}

	if ( argc_ptr )
	{
		*argc_ptr = _argc;
	}

	return( retval );
}

// --

static S32 InitArgs(
	struct AmyCLibIFace *Self UNUSED,
	struct libData *data,
	struct WBStartup *wbmsg,
	STR **argv,
	S32 *argc )
{
S32 retval;

	if ( wbmsg )
	{
		// -- WB Start

		DOFUNCTIONPRINTF( IExec->DebugPrintF( "InitArgs : WB Start\n" ); );

		*argv = (PTR) wbmsg;
		*argc = 0;

		retval = TRUE;
	}
	else
	{
		// -- Cli Start

		DOFUNCTIONPRINTF( IExec->DebugPrintF( "InitArgs : CLI Start\n" ); );

		retval = myInit_CLI( data, argv, argc );
	}

//	IExec->DebugPrintF( "InitArgs : retval %ld\n", retval );

	return( retval );
}

// --
