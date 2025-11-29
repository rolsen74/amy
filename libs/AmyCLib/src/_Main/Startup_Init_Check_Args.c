
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

static int doFuncStat( struct AmyCLibIFace *Self UNUSED, struct libData *data )
{
	#ifdef DEBUG
	IExec->DebugPrintF( "Enabling Function Stat tracking\n" );
	#endif

 	data->TrackFuncUsage = TRUE;

	return( TRUE );
}

// --

struct Option
{
	U32		Len;
	STR		Name;
	int		( *Func )( struct AmyCLibIFace *Self, struct libData *data );
};

struct Option myOptions[] =
{
//		 12345678901234567890
{	20,	"AMYCLIB_FUNCTIONSTAT", doFuncStat },
{	0,	NULL, NULL }
};

// --

static S32 myInit_Check_Args( struct AmyCLibIFace *Self, struct libData *data UNUSED, STR args )
{

STR str_out;
STR str_in;
S32 error;
U32 opt;
U32 len;
S32 c;

	error = TRUE;

	if (( ! args ) || ( ! args[0] ))
	{
		error = FALSE;
		goto bailout;
	}

//	IExec->DebugPrintF( "Check : Args : '%s'\n", args );

	str_in = args;
	str_out = args;

	while( TRUE )
	{
		// Skip space

		while( TRUE )
		{
			c = *str_in;

			if (( c == 9 )
			||	( c == 10 )
			||	( c == 13 )
			||	( c == 32 ))
			{
				*str_out++ = *str_in++;
			}
			else
			{
				break;
			}
		}

		// Check end of Arg string

		if ( ! c )
		{
			break;
		}

		// --
		// Count arg length

		len = 0;
	
		while( TRUE )
		{
			c = str_in[len];

			if (( c == 0 )
			||	( c == 9 )
			||	( c == 10 )
			||	( c == 13 )
			||	( c == '=' )
			||	( c == ' ' ))
			{
				break;
			}
			else
			{
				len++;
			}
		}

		// --
		// Check for Option

		opt = 0;

		while( myOptions[opt].Func )
		{
			if (( myOptions[opt].Len == len ) && ( ! Self->string_strncmp( myOptions[opt].Name, str_in, len )))
			{
				break;
			}
			else
			{
				opt++;
			}
		}

		if ( myOptions[opt].Func )
		{
//			IExec->DebugPrintF( "Found init arg : %s\n", myOptions[opt].Name );

			myOptions[opt].Func( Self, data );

			// Remove Option

			while( TRUE )
			{
				c = *str_in;

				if (( c == 0 )
				||	( c == 9 )
				||	( c == 10 )
				||	( c == 13 )
				||	( c == 32 ))
				{
					break;
				}
				else
				{
					str_in++;
				}
			}
		}
		else
		{
			// Skip Option

			while( TRUE )
			{
				c = *str_in;

				if (( c == 0 )
				||	( c == 9 )
				||	( c == 10 )
				||	( c == 13 )
				||	( c == 32 ))
				{
					break;
				}
				else
				{
					*str_out++ = *str_in++;
				}
			}
		}
	}

	// Lets make sure output string is terminated
	*str_out = 0;

	error = FALSE;

//	IExec->DebugPrintF( "Check : Args : '%s'\n", args );

bailout:

	return( error );
}

// --
