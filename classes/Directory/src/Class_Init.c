
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2014-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

static U32 Class_Init( struct ExecIFace *myIExec, struct RA_Plugin *rap )
{
struct DirClassData *data;
U32 retval;

	retval = RAV_General_Failure;

	data = rap->RA_Plugin_Data;

	if ( ! data )
	{
		goto bailout;
	}

	IExec = myIExec;

	/* -- Get ReactiveC -- */

	AmyCLibBase = IExec->OpenLibrary( "AmyCLib.library", 1 );
	IAmyCLib = (PTR) IExec->GetInterface( AmyCLibBase, "main", 1, NULL );

	if ( ! IAmyCLib )
	{
		goto bailout;
	}

	if ( ! IAmyCLib->Priv_Startup_Init( NULL, EM_STRING|EM_MEMORY ))
	{
		goto bailout;
	}

	/* -- Get DOS -- */

	DOSBase = IExec->OpenLibrary( "dos.library", 53 );
	IDOS = (PTR) IExec->GetInterface( DOSBase, "main", 1, NULL );

	if ( ! IDOS )
	{
		goto bailout;
	}

//--	/* -- Get Utility -- */
//--
//--	UtilityBase = IExec->OpenLibrary( "utility.library", 53 );
//--	IUtility = (PTR) IExec->GetInterface( UtilityBase, "main", 1, NULL );
//--
//--	if ( IUtility == NULL )
//--    {
//--		goto bailout;
//--    }

	/* -- Done -- */

	retval = RAV_General_Success;

bailout:

	return(	retval );
}

// --
