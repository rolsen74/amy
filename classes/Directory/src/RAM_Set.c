
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2014-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

static U32 Dir_RAM_Set(
		struct ReactiveIFace *Self,
		struct RA_Class *cl,
		struct RA_Object *obj,
		struct RAP_Set *msg,
UNUSED	struct DirClassData *cls,
		InstanceData *data )
{
U32 retval;
S32 clr;

//	IExec->DebugPrintF( "Dir_RAM_Set\n" );

	clr = FALSE;

	switch( msg->AttrID )
	{
		case RAA_DIR_DataFields:
		{
			if ( msg->AttrValue != data->DataFields )
			{
				data->DataFields = data->DataFields;
				clr = TRUE;
			}

			retval = RAV_General_Success;
			break;
		}

		case RAA_DIR_Path:
		{
			Parse_Path( Self, cls, data, (PTR) msg->AttrValue );

			retval = RAV_General_Success;
			break;
		}

		case RAA_DIR_Pattern:
		{
			data->UserPattern = (PTR) msg->AttrValue;

			retval = RAV_General_Success;
			break;
		}

		default:
		{
			retval = RASuper( cl, obj, msg );
			break;
		}
	}

	if ( clr == TRUE )
	{
		RAMethod( obj, RAM_DIR_Clear );
	}

	return(	retval );
}
