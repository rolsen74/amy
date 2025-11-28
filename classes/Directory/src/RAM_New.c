
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2014-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

static U32 Dir_RAM_New(
	struct ReactiveIFace *Self,
	struct RA_Class *cl,
	struct RA_Object *obj,
	struct RAP_New *msg,
	struct DirClassData *cls,
	InstanceData *data )
{
struct TagItem *tag;
U32 retval;

//	IExec->DebugPrintF( "Dir_RAM_New\n" );

	IExec->NewList( &data->Header );

//	  data->Path	   = "sys:";
	data->DataFields = (EXF_NAME|EXF_SIZE|EXF_TYPE|EXF_LINK);

	retval = RASuper( cl, obj, msg );

	if ( retval != RAV_General_Success )
	{
		goto bailout;
	}

	for( tag = msg->AttrList ; tag && tag->ti_Tag ; tag = RANextTag( tag ))
	{
		switch( tag->ti_Tag )
		{
			case RAA_DIR_DataFields:
			{
//				IExec->DebugPrintF( "RAA_DIR_DataFields\n" );
				data->DataFields = tag->ti_Data;
				break;
			}

			case RAA_DIR_Path:
			{
				STR str = (STR) tag->ti_Data;
//				IExec->DebugPrintF( "RAA_DIR_Path : '%s'\n", (str)?str:"" );
				Parse_Path( Self, cls, data, str );
				break;
			}

			case RAA_DIR_Pattern:
			{
//				STR str = (STR) tag->ti_Data;
//				IExec->DebugPrintF( "RAA_DIR_Pattern : '%s'\n", (str)?str:"" );
				data->UserPattern = (PTR) tag->ti_Data;
				break;
			}

			default:
			{
				break;
			}
		}
	}

bailout:

	return(	retval );
}
