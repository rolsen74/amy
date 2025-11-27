
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2014-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

static U32 App_RAM_Get(
		struct ReactiveIFace *Self,
		struct RA_Class *cl,
		struct RA_Object *obj,
		struct RAP_Get *msg,
UNUSED	struct AppClassData *cls,
UNUSED	InstanceData *data )
{
U32 *Storage32;
U32 retval;

	IExec->DebugPrintF( "App_RAM_Get\n" );

	Storage32 = msg->Storage;

	switch( msg->AttrID )
	{
		case RAA_Version:
		{
			*Storage32 = VERSION;

			retval = RAV_General_Success;
			break;
		}

		case RAA_Revision:
		{
			*Storage32 = REVISION;

			retval = RAV_General_Success;
			break;
		}

		default:
		{
			retval = RASuper( cl, obj, msg );
			break;
		}
	}

	return(	retval );
}
