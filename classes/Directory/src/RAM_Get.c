
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2014-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

static U32 Dir_RAM_Get(
		struct ReactiveIFace *Self,
		struct RA_Class *cl,
		struct RA_Object *obj,
		struct RAP_Get *msg,
UNUSED	struct DirClassData *cls,
		InstanceData *data )
{
U32 *Storage32;
U32 retval;

	IExec->DebugPrintF( "Dir_RAM_Get\n" );

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

		case RAA_DIR_IOErr:
		{
			*Storage32 = data->IOErr;

			retval = RAV_General_Success;
			break;
		}

		case RAA_DIR_IOErrString:
		{
			*Storage32 = (U32) Get_IOErrString( data->IOErr );

			retval = RAV_General_Success;
			break;
		}

		case RAA_DIR_Pattern:
		{
			*Storage32 = (U32) data->UserPattern;

			retval = RAV_General_Success;
			break;
		}

		case RAA_DIR_Entries:
		{
			*Storage32 = (U32) data->Entries;

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
