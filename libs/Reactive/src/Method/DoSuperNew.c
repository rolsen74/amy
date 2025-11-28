
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMYFUNC _main_Method_DoSuperNew(
	struct ReactivePrivIFace *Self,
	struct RA_PrivClass *cl,
	struct RA_PrivObject *obj,
	... )
{
struct RAP_New method;
U32 retval;
va_list ap;

//	IExec->DebugPrintF( "RA_Method_DoSuperNew\n" );

	retval	= RAV_General_Failure;

	if (( ! cl ) || ( cl->RA_Class_ID != ID_RAClass ))
	{
//		IExec->DebugPrintF( "Method_DoSuperNew: Invalid Reactive object" );
//		  Self->Error_LogTags( txt );

		retval = RAV_General_InvalidClass;
		goto bailout;
	}

	if (( ! obj ) || ( obj->RA_Object_ID != ID_RAObject ))
	{
//		IExec->DebugPrintF( "Method_DoSuperNew: Invalid Reactive object" );
//		  Self->Error_LogTags( txt );

		retval = RAV_General_InvalidObject;
		goto bailout;
	}

	va_start( ap, obj );

	method.MethodID = RAM_New;
	method.AttrList = va_getlinearva( ap, struct TagItem * );

	retval = Self->Method_RunFunc( cl->RA_Class_Super, obj, (PTR) & method );

	va_end( ap );

bailout:

	return(	retval );
}
