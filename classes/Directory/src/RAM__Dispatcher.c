
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2014-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

static U32 Dir_Dispatcher(
	struct ReactiveIFace *Self,
	struct RA_Class *cl,
	struct RA_Object *obj,
	struct RA_Method *msg,
	struct DirClassData *dcls,
	InstanceData *data )
{
U32 retval;

//	IExec->DebugPrintF( "Dir Dispatcher\n" );

	#define RUNFUNC(x)	retval = x( Self, cl, obj, (PTR) msg, dcls, data ); break

	switch( msg->RA_Method_ID )
	{
		case RAM_New:				RUNFUNC( Dir_RAM_New );
		case RAM_Delete:			RUNFUNC( Dir_RAM_Delete );
		case RAM_Set:				RUNFUNC( Dir_RAM_Set );
		case RAM_Get:				RUNFUNC( Dir_RAM_Get );

		case RAM_DIR_Scan:			RUNFUNC( Dir_Scan );
		case RAM_DIR_Sort:			RUNFUNC( Dir_Sort );
		case RAM_DIR_GetEntry:		RUNFUNC( Dir_GetEntry );
		case RAM_DIR_Clear:			RUNFUNC( Dir_Clear );

		case RAM_DIR_IsFile:		RUNFUNC( Dir_IsFile );
		case RAM_DIR_IsDir:			RUNFUNC( Dir_IsDir );

		default:
		{
			retval = RASuper( cl, obj, msg );
			break;
		}
	}

	#undef RUNFUNC

	return(	retval );
}
