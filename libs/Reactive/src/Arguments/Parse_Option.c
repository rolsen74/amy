
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

static U32 Handle_Option( struct ReactivePrivIFace *Self UNUSED, struct RAArguments *Args, struct ArgStruct *as, STR option, U32 Type )
{
U32 error;

	IExec->DebugPrintF( "RA_Arguments_ParseList : Handle_Option\n" );

	error = RAV_General_Success;

	switch( Type )
	{
		case ArgType_Number:
		{
			if ( option[0] != '=' )
			{
				error = RAV_General_IllegalArguments;
				break;
			}

			if (( option[1] < '0' ) || ( option[1] > '9' ))
			{
				error = RAV_General_IllegalArguments;
				break;
			}

			if ( Args->Storage )
			{
				U32 *ptr = (PTR) Args->Storage;

				sscanf( & option[1], "%d", ptr );
			}
			break;
		}

		case ArgType_Switch:
		{
			U32 len;
			S32 val = TRUE;

			if ( option[0] == '=' )
			{
				len = 1;

				while(
					( option[len] !=  0 ) &&
					( option[len] !=  9 ) &&
					( option[len] != 10 ) &&
					( option[len] != 32 ))
				{
					len++;
				}

				/**/ if ( len == 3 )
				{
					/**/ if ( strnicmp(	"no", &option[1], 2 ) == 0 )
					{
						val = FALSE;
					}
					else if ( strnicmp( "on", &option[1], 2 ) == 0 )
					{
						val = TRUE;
					}
					else
					{
						error = RAV_General_IllegalArguments;
						break;
					}
				}
				else if ( len == 4 )
				{
					/**/ if ( strnicmp(	"yes", &option[1], 3 ) == 0 )
					{
						val = TRUE;
					}
					else if ( strnicmp( "off", &option[1], 3 ) == 0 )
					{
						val = FALSE;
					}
					else
					{
						error = RAV_General_IllegalArguments;
						break;
					}
				}
				else
				{
					error = RAV_General_IllegalArguments;
					break;
				}
			}

			if ( Args->Storage )
			{
				S32 *ptr = (PTR) Args->Storage;

				*ptr = val;
			}
			break;
		}

		case ArgType_Key:
		{
			if ( option[0] != '=' )
			{
				error = RAV_General_IllegalArguments;
				break;
			}

			if ( Args->Storage )
			{
				as->as_Keys[ as->as_KeyCount ] = NULL;

				asprintf( & as->as_Keys[ as->as_KeyCount ], "%s", & option[1] );

				if ( ! as->as_Keys[ as->as_KeyCount ] )
				{
					error = RAV_General_OutOfMemory;
					break;
				}

				*Args->Storage = as->as_Keys[ as->as_KeyCount++ ];
			}
			break;
		}

		default:
		{
			IExec->DebugPrintF( "_main_Arguments_ParseList : Unknown Type\n" );
			error = RAV_General_Failure;
			break;
		}
	}

	return(	error );
}

// --
