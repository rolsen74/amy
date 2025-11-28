
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2014-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

static U32 App_Dispatcher(
	struct ReactiveIFace *Self,
	struct RA_Class *cl,
	struct RA_Object *obj,
	struct RA_Method *msg,
	struct AppClassData *acls,
	InstanceData *data )
{
U32 retval;

//	IExec->DebugPrintF( "App Dispatcher\n" );

	#define RUNFUNC(x)	retval = x( Self, cl, obj, (PTR) msg, acls, data ); break

	switch( msg->RA_Method_ID )
	{
		case RAM_New:				RUNFUNC( App_RAM_New );
		case RAM_Delete:			RUNFUNC( App_RAM_Delete );
//		case RAM_Set:				RUNFUNC( App_RAM_Set );
		case RAM_Get:				RUNFUNC( App_RAM_Get );


		default:
		{
			retval = RASuper( cl, obj, msg );
			break;
		}
	}

	#undef RUNFUNC

	return(	retval );
}
