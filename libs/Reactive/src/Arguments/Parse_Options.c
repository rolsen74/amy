
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

static PTR Handle_Options( struct ReactivePrivIFace *Self, struct RAArguments *Args, S32 argc, STR *argv, U32 *error, S32 FromWB )
{
struct ArgStruct *retval;
STR str;
U32 start;
U32 Type;
//U32 mpos;
U32 pos;
U32 len;
U32 val;
U32 l;
U32 i;
S32 cnt;
S32 Found;
S32 Multi;
S32 err;
S32 Req;
S32 Case;
S32 Key;

	IExec->DebugPrintF( "RA_Arguments_ParseList : Handle_Options\n" );

	retval	= NULL;
	Multi	= FALSE;
	err		= TRUE;

	// First Check for All Required Keywords

	pos = 0;

	while( Args[pos].Name )
	{
		Type= ArgType_NotSet;
		Case= FALSE;
		Req = FALSE;
		Key = FALSE;
		l   = 0;

		// Skip Type

		while(( Args[pos].Name[l] ) && ( Args[pos].Name[l] != ',' ))
		{
			switch( Args[pos].Name[l] )
			{
				case 'A':	Req = TRUE;				break;	// Required
				case 'C':	Case = TRUE;			break;	// Case Sensetive
				case 'K':	Key = TRUE;				break;	// Keyword
				case 'N':	Type = ArgType_Number;	break;	// Number
				case 'S':	Type = ArgType_Switch;	break;	// Switch
				case 'M':	Type = ArgType_Multi;	break;	// Multi Strings

				default:
				{
					IExec->DebugPrintF( "Illegal Arguments" );
					*error = RAV_General_IllegalArguments;
					goto bailout;
				}
			}

			l++;
		}

		// Validate Data

		if (( Key == TRUE ) && ( Req == TRUE ))
		{
			IExec->DebugPrintF( "Illegal Arguments" );
			*error = RAV_General_IllegalArguments;
			goto bailout;
		}

		if (( Type == ArgType_NotSet ) && ( Key == FALSE ))
		{
			IExec->DebugPrintF( "Illegal Arguments, Missing Type" );
			*error = RAV_General_IllegalArguments;
			goto bailout;
		}

		if ( Type == ArgType_Multi )
		{
			Multi = TRUE;
		}

		if ( Args[pos].Name[l] != ',' )
		{
			IExec->DebugPrintF( "Illegal Arguments, Missing Comma" );
			*error = RAV_General_IllegalArguments;
			goto bailout;
		}

		// Is the Argument Required?

		if ( Req == FALSE )
		{
			pos++;
			continue;
		}

		// Skip comman, but only one comma

		l++;

		if ( FromWB == TRUE )
		{
			i = l;

			while(( Args[pos].Name[i] ) && ( Args[pos].Name[i] != '|' ))
			{
				i++;
			}

			if ( Args[pos].Name[i] == '|' )
			{
				l = i+1;
			}
		}

		start = l;

		// Calc Argument Length

		while(( Args[pos].Name[l] ) && ( Args[pos].Name[l] != '|' ))
		{
			l++;
		}

		// Now check for the Keyword

		for( cnt=0 ; cnt<argc ; cnt++ )
		{
			len = 0;
			str = argv[cnt];

			// Calc Option Length

			while(
				( str[len] !=  0 ) &&
				( str[len] !=  9 ) &&
				( str[len] != 10 ) &&
				( str[len] != 32 ) &&
				( str[len] != '=' ))
			{
				len++;
			}

			if ( len == l - start )
			{
				if ( Case == TRUE )
				{
					if ( strncmp( str, &Args[pos].Name[start], len ) == 0 )
					{
						break;
					}
				}
				else
				{
					if ( strnicmp( str, &Args[pos].Name[start], len ) == 0 )
					{
						break;
					}
				}
			}
		}

		if ( cnt == argc )
		{
			// Keyword is missing
			*error = RAV_General_MissingKeyword;
			goto bailout;
		}

		// Next Argument

		pos++;
	}

	// --

	retval = malloc( sizeof( struct ArgStruct ));

	if ( retval == NULL )
	{
		*error = RAV_General_OutOfMemory;
		goto bailout;
	}

	retval->as_ID		= ARG_ID;
	retval->as_Strings	= malloc( ( argc + 1 ) * sizeof( PTR ));
	retval->as_Keys		= malloc( ( argc + 1 ) * sizeof( PTR ));

	if (( retval->as_Strings == NULL )
	||	( retval->as_Keys	 == NULL ))
	{
		*error = RAV_General_OutOfMemory;
		goto bailout;
	}

//	  mpos = 0;

	for( cnt=0 ; cnt<argc ; cnt++ )
	{
		str = argv[cnt];
		len = 0;

		// Calc Option Length

		while(
			( str[len] !=  0 ) &&
			( str[len] !=  9 ) &&
			( str[len] != 10 ) &&
			( str[len] != 32 ) &&
			( str[len] != '=' ))
		{
			len++;
		}

		pos = 0;

		// Check for known Arguments

		while( Args[pos].Name )
		{
			Case= FALSE;
			Type= ArgType_NotSet;
			l   = 0;

			// Skip Type

			while((  Args[pos].Name[l] ) && ( Args[pos].Name[l] != ',' ))
			{
				if ( Args[pos].Name[l] == 'C' ) // Case Sencetive
				{
					Case = TRUE;
				}

				if ( Args[pos].Name[l] == 'N' ) // Number
				{
					Type = ArgType_Number;
				}

				if ( Args[pos].Name[l] == 'S' ) // Switch
				{
					Type = ArgType_Switch;
				}

				if ( Args[pos].Name[l] == 'K' ) // Key
				{
					Type = ArgType_Key;
				}

				if ( Args[pos].Name[l] == 'M' )	// Multi Strings
				{
					if ( Args[pos].Storage )
					{
						*Args[pos].Storage = retval->as_Strings;
					}
				}

				l++;
			}

			// SKip Comma

			l++;

			if ( FromWB == TRUE )
			{
				i = l;

				while(( Args[pos].Name[i] ) && ( Args[pos].Name[i] != '|' ))
				{
					i++;
				}

				if ( Args[pos].Name[i] == '|' )
				{
					l = i+1;
				}
			}

			start = l;

			// Calc Argument Length

			while(( Args[pos].Name[l] ) && ( Args[pos].Name[l] != '|' ))
			{
				l++;
			}

			if ( len == l - start )
			{
				if ( Case == TRUE )
				{
					Found = strncmp( str, &Args[pos].Name[start], len );
				}
				else
				{
					Found = strnicmp( str, &Args[pos].Name[start], len );
				}
			}
			else
			{
				Found = 1;
			}

			if ( Found == 0 )
			{
				if (( val = Handle_Option( Self, &Args[pos], retval, &str[len], Type ) != RAV_General_Success ))
				{
					*error = val;
					goto bailout;
				}
				else
				{
					break;
				}
			}
			else
			{
				pos++;
			}
		}

		if (( Multi == TRUE ) && ( ! Args[pos].Name ))
		{
			retval->as_Strings[ retval->as_StringCount ] = NULL;

			asprintf( & retval->as_Strings[ retval->as_StringCount ], "%s", str );

			if ( ! retval->as_Strings[ retval->as_StringCount ] )
			{
				*error = RAV_General_OutOfMemory;
				goto bailout;
			}

			retval->as_StringCount++;
		}
	}

	err = FALSE;

bailout:

	if (( retval ) && ( err ))
	{
		if ( retval->as_Strings )
		{
			for( cnt=0 ; cnt<argc ; cnt ++ )
			{
				free( retval->as_Strings[cnt] );
				retval->as_Strings[cnt] = NULL;
			}
			
			free( retval->as_Strings );
		}

		if ( retval->as_Keys )
		{
			for( cnt=0 ; cnt<argc ; cnt ++ )
			{
				free( retval->as_Keys[cnt] );
				retval->as_Keys[cnt] = NULL;
			}

			free( retval->as_Keys );
		}

		free( retval );
		retval = NULL;
	}

	return( retval );
}

// --
