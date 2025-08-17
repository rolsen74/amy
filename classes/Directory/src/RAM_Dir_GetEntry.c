
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2014-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

static U32 Dir_GetEntry(
UNUSED	struct ReactiveIFace *Self,
UNUSED	struct RA_Class *cl,
UNUSED	struct RA_Object *obj,
UNUSED	struct RAP_DIR_GetEntry *msg,
UNUSED	struct DirClassData *cls,
		InstanceData *data )
{
U32 retval;

	IExec->DebugPrintF( "Dir_GetEntry\n" );

	retval = RAV_General_Failure;

	if ( ! data->Scanned )
	{
		goto bailout;
	}

	if (( ! msg->ID ) || ( ! msg->Dat ))
	{
		goto bailout;
	}

	if (( *msg->ID ) && ( *msg->ID != data->ID ))
	{
		goto bailout;
	}

	if ( *msg->ID == 0 )
	{
		*msg->ID	= data->ID;
		*msg->Dat	= (PTR) IExec->GetHead( & data->Header );
	}
	else
	{
		*msg->Dat	= (PTR) IExec->GetSucc( (PTR) *msg->Dat );
	}

	if ( *msg->Dat == NULL )
	{
		retval = RAV_General_EndOfData;
	}
	else
	{
		retval = RAV_General_Success;
	}

bailout:

	return(	retval );
}
