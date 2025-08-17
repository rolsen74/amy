
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

static U32 Root_Delete(
UNUSED	struct ReactivePrivIFace *Self,
UNUSED	struct RA_PrivClass *cl,
		struct RA_PrivObject *obj,
UNUSED	struct RAP_Delete *method,
UNUSED	struct libBase *libBase,
UNUSED	struct RootClass_Data *rcd )
{
//struct NotifyNode *nn;
U32 retval;

	IExec->DebugPrintF( "Root_Delete\n" );

	// Clear ID, then it can't be used any more
	obj->RA_Object_ID = 0;

//--	if ( rcd->rcd_Object.RA_Object_Style )
//--	{
//--		if ( rcd->rcd_StyleName )
//--		{
//--			IReactive->Style_Unlock( rcd->rcd_Object.RA_Object_Style );
//--			rcd->rcd_StyleName = NULL;
//--		}
//--		else
//--		{
//--			rcd->rcd_Object.RA_Object_Style->RA_Style_Count_Open--;
//--		}
//--		rcd->rcd_Object.RA_Object_Style = NULL;
//--	}

//	while(( nn = (PTR)IExec->RemHead( & rcd->rcd_NotifyList )))
//	{
//		free( nn );
//	}

	retval = RAV_General_Success;

	return(	retval );
}

