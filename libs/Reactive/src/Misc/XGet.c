
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMY_FUNC _main_Misc_XGet( struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, U32 AttrID )
{
U32 retval;

//	IExec->DebugPrintF( "_main_Misc_XGet : Object %p, AttrID $%08lx\n", obj, AttrID );

	retval = 0;

	if (( ! obj ) || ( obj->RA_Object_ID != ID_RAObject ))
	{
//		IExec->DebugPrintF( "_main_Misc_XGet : Invalid Object Pointer : Obj %p", obj );
//		  Self->Error_LogTags( txt );

//		retval = RAV_General_InvalidObject;
	}
	else
	{
		Self->Method_DoTags(
			obj,
			RAM_Get,
			AttrID,
			& retval
		);
	}

	return(	retval );
}
