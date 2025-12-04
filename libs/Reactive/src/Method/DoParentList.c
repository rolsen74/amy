
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMY_FUNC _main_Method_DoParentList( struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, struct RA_Method *method )
{
struct RA_PrivObject *o;
struct RA_PrivClass *cl;
U32 retval;

//	IExec->DebugPrintF( "RA_Method_DoParentList\n" );

	if (( ! obj ) || ( obj->RA_Object_ID != ID_RAObject ))
	{
//		IExec->DebugPrintF( "Method_DoParentList: Invalid Reactive Object (0x%08lx)", obj );

		retval = RAV_General_InvalidObject;
		goto bailout;
	}

	if ( method->RA_Method_ID == 0 )
	{
//		IExec->DebugPrintF( "Method_DoParentList: Invalid MethodID (0x%08lx)", method->RA_Method_ID );

		retval = RAV_General_InvalidMethod;
		goto bailout;
	}

	o = obj->RA_Object_Parent;

	if ( o == NULL )
	{
//		IExec->DebugPrintF( "Method_DoParentList: Object has no Parent" );

		retval = RAV_General_NoParent;
		goto bailout;
	}

	if ( o->RA_Object_ID != ID_RAObject )
	{
//		IExec->DebugPrintF( "_main_Method_DoParentTags: Invalid Reactive Object (0x%08lx)", o );

		retval = RAV_General_InvalidObject;
		goto bailout;
	}

	cl = o->RA_Object_Class;

	if (( ! cl ) || ( cl->RA_Class_ID != ID_RAClass ))
	{
//		IExec->DebugPrintF( "Method_DoParentList: Object has no Class" );

		retval = RAV_General_InvalidClass;
		goto bailout;
	}

	retval = Self->Method_RunFunc( cl, o, method );

bailout:

	return(	retval );
}
