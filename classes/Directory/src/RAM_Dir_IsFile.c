
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2014-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

static U32 Dir_IsFile(
UNUSED	struct ReactiveIFace *Self,
UNUSED	struct RA_Class *cl,
UNUSED	struct RA_Object *obj,
		struct RAP_DIR_IsFile *msg,
UNUSED	struct DirClassData *cls,
UNUSED	InstanceData *data )
{
struct ExamineData *ed;
U32 retval;

//	IExec->DebugPrintF( "Dir_IsFile\n" );

	PTR oldproc = IDOS->SetProcWindow( (PTR) -1 );

	ed = IDOS->ExamineObjectTags(
		EX_StringName, msg->FullPath,
		TAG_END
	);

	IDOS->SetProcWindow( oldproc );

	if ( ed )
	{
		if ( EXD_IS_FILE( ed ))
		{
			retval = TRUE;
		}
		else
		{
			retval = FALSE;
		}

		IDOS->FreeDosObject( DOS_EXAMINEDATA, ed );
	}
	else
	{
		retval = -1;
	}

	return(	retval );
}
