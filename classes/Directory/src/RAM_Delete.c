
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2014-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

static U32 Dir_RAM_Delete(
		struct ReactiveIFace *Self,
		struct RA_Class *cl,
		struct RA_Object *obj,
		struct RAP_Delete *msg,
UNUSED	struct DirClassData *cls,
		InstanceData *data )
{
U32 retval;

//	IExec->DebugPrintF( "Dir_Delete\n" );

	if ( data->String )
	{
		free( data->String );
		data->String = NULL;
	}

	if ( data->Pattern )
	{
		free( data->Pattern );
		data->Pattern = NULL;
	}

//	  if ( data->IFace )
//	  {
//		  RAFreeMem( data->IFace );
//		  data->IFace = NULL;
//	  }

	// Free

	RAMethod( obj, RAM_DIR_Clear );

	// Done

	retval = RASuper( cl, obj, msg );

	return(	retval );
}

