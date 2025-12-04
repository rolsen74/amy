
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMY_FUNC _main_Arguments_Free( struct ReactivePrivIFace *Self UNUSED, PTR Args )
{
struct ArgStruct *as = Args;
U32 retval;
U32 cnt;

	retval = FALSE;

//	IExec->DebugPrintF( "RA_Arguments_Free\n" );

	if (( ! as ) ||( as->as_ID != ARG_ID ))
	{
//		IExec->DebugPrintF( "RA_Arguments_Free : Illegal Argument Pointer" );
		goto bailout;
	}

	as->as_ID = 0;

	if ( as->as_Strings )
	{
		for( cnt=0 ; cnt<as->as_StringCount ; cnt ++ )
		{
			free( as->as_Strings[cnt] );
			as->as_Strings[cnt] = NULL;
		}

		free( as->as_Strings );
		as->as_Strings = NULL;
	}

	if ( as->as_Keys )
	{
		for( cnt=0 ; cnt<as->as_KeyCount ; cnt ++ )
		{
			free( as->as_Keys[cnt] );
			as->as_Keys[cnt] = NULL;
		}

		free( as->as_Keys );
		as->as_Keys = NULL;
	}

	free( as );
	as = NULL;

	retval = TRUE;

bailout:

	return(	retval );
}
