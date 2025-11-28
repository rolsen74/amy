
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2014-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

static U32 Dir_Clear(
UNUSED	struct ReactiveIFace *Self,
UNUSED	struct RA_Class *cl,
UNUSED	struct RA_Object *obj,
UNUSED	struct RAP_DIR_Clear *msg,
UNUSED	struct DirClassData *cls,
		InstanceData *data )
{
U32 retval;

//	IExec->DebugPrintF( "Dir_Clear\n" );

	retval	= RAV_General_Success;

	// Next ID, excluding Zero
	while(( data->ID++ == 0 ));

	// Clear List
	IExec->NewList( &data->Header );
	
	// Release Resources
	IDOS->ReleaseDirContext( data->Context );
	data->Context = NULL;

	// Cleared scan Flag
	data->Scanned = FALSE;
	data->Entries = 0;

	return(	retval );
}
