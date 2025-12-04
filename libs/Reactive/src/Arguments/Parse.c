
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

#include "Parse_Option.c"
#include "Parse_Options.c"

#include "Parse_Args_WBFile.c"
#include "Parse_Args_File.c"
#include "Parse_Args_CLI.c"
#include "Parse_Args_WB.c"

// --

PTR AMY_FUNC _main_Arguments_ParseList( struct ReactivePrivIFace *Self, struct RAArguments *Args, struct TagItem *taglist )
{
char **argv;
U32 *errptr;
U32 error;
PTR retval;
PTR file;
S32 argc;
PTR wb;

	retval	= NULL;

//	IExec->DebugPrintF( "RA_Arguments_ParseList\n" );

	errptr	= Self->Misc_GetTagData( taglist, RAA_ErrorCode, NULL );
	file	= Self->Misc_GetTagData( taglist, RAA_Argument_File, NULL );
	argc	= Self->Misc_GetTagValue(taglist, RAA_Argument_Argc, 0 );
	argv	= Self->Misc_GetTagData( taglist, RAA_Argument_Argv, NULL );
	wb		= Self->Misc_GetTagData( taglist, RAA_Argument_WBStartup, NULL );

	if ( ! Args )
	{
		error = RAV_General_Failure;
		goto bailout;
	}

	/**/ if (( argc != 0 ) && ( argv ))
	{
		error = RAV_General_Success;

		retval = Handle_CLIArgs( Self, Args, IDOS-> GetArgStr(), &error );
	}
	else if (( argc == 0 ) && ( argv ))
	{
		error = RAV_General_Success;

		retval = Handle_WBArgs( Self, Args, (PTR) argv, &error );
	}
	else if ( wb )
	{
		error = RAV_General_Success;

		retval = Handle_WBArgs( Self, Args, wb, &error );
	}
	else if ( file )
	{
		error = RAV_General_Success;

		retval = Handle_FileArgs( Self, Args, file, &error );
	}
	else
	{
		error = RAV_General_Failure;
	}

bailout:

	if (( errptr ) && ( *errptr == RAV_General_Success ))
	{
		*errptr = error;
	}

	return(	retval );
}

// --

PTR AMY_FUNC _main_Arguments_ParseTags( struct ReactivePrivIFace *Self, struct RAArguments *Args, ... )
{
struct TagItem *taglist;
va_list ap;
PTR retval;

	va_start( ap, Args );

	taglist = va_getlinearva( ap, struct TagItem * );

	retval = Self->Arguments_ParseList( Args, taglist );

	va_end( ap );

	return(	retval );
}

// --
