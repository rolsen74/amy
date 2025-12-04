
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMY_FUNC _main_Method_DoSuperList( struct ReactivePrivIFace *Self, struct RA_PrivClass *cl, struct RA_PrivObject *obj, struct RA_Method *method )
{
U32 retval;

//	IExec->DebugPrintF( "RA_Method_DoSuperList\n" );

	if (( ! cl ) || ( cl->RA_Class_ID != ID_RAClass ))
	{
//		IExec->DebugPrintF( "Method_DoSuperArgList: Invalid Reactive Class (0x%08lx)", cl );
//		  Self->Error_LogTags( txt, cl );

		retval = RAV_General_InvalidClass;
		goto bailout;
	}

	if (( ! obj ) || ( obj->RA_Object_ID != ID_RAObject ))
	{
//		IExec->DebugPrintF( "Method_DoSuperArgList: Invalid Reactive Object (0x%08lx)", obj );
//		  Self->Error_LogTags( txt, obj );

		retval = RAV_General_InvalidObject;
		goto bailout;
	}

	if ( method->RA_Method_ID == 0 )
	{
//		IExec->DebugPrintF( "Method_DoSuperArgList: Invalid MethodID (0x%08lx)", method->RA_Method_ID );
//		  Self->Error_LogTags( txt, method->RA_Method_ID );

		retval = RAV_General_InvalidMethod;
		goto bailout;
	}

	retval = Self->Method_RunFunc( cl->RA_Class_Super, obj, method );

bailout:

	return(	retval );
}
