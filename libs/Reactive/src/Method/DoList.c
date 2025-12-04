
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMY_FUNC _main_Method_DoList( struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, struct RA_Method *method )
{
U32 retval;

//	IExec->DebugPrintF( "RA_Method_DoList\n" );

	if (( ! obj ) || ( obj->RA_Object_ID != ID_RAObject ))
	{
//		IExec->DebugPrintF( "Method_DoArgList: Invalid Reactive object (0x%08lx)", obj );
//		  Self->Error_LogTags( txt, obj );

		retval = RAV_General_InvalidObject;
		goto bailout;
	}

	if ( method->RA_Method_ID == 0 )
	{
//		IExec->DebugPrintF( "Method_DoTagList: Invalid MethodID" );
//		  Self->Error_LogTags( txt );

		retval = RAV_General_InvalidMethod;
		goto bailout;
	}

	retval = Self->Method_RunFunc( obj->RA_Object_Class, obj, method );

bailout:

	return(	retval );
}
