
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2014-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

static U32 Class_Exit( struct ExecIFace *IExec, struct RA_Plugin *rap )
{
struct DirClassData *data;
U32 retval;

	retval = RAV_General_Failure;

	data = rap->RA_Plugin_Data;

	if ( ! data )
	{
		goto bailout;
	}

//--	/* -- Close Utility -- */
//--
//--	if ( IUtility )
//--    {
//--		IExec->DropInterface( (PTR) IUtility );
//--		IUtility = NULL;
//--    }
//--
//--	if ( UtilityBase )
//--    {
//--		IExec->CloseLibrary( UtilityBase );
//--		UtilityBase = NULL;
//--    }

	/* -- Close DOS -- */

	if ( IDOS )
	{
		IExec->DropInterface( (PTR) IDOS );
		IDOS = NULL;
	}

	if ( DOSBase )
	{
		IExec->CloseLibrary( DOSBase );
		DOSBase = NULL;
	}

	/* -- Close ReactiveC -- */

	if ( IAmyCLib )
	{
		IExec->DropInterface( (PTR) IAmyCLib );
		IAmyCLib = NULL;
	}

	if ( AmyCLibBase )
	{
		IExec->CloseLibrary( AmyCLibBase );
		AmyCLibBase = NULL;
	}

	/* -- Done -- */

	retval = RAV_General_Success;

bailout:

	return(	retval );
}

// --
