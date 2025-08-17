
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMYFUNC _main_Method_DoParentTags(
	struct ReactivePrivIFace *Self,
	struct RA_PrivObject *obj,
	... )
{
struct RA_PrivObject *o;
struct RA_PrivClass *cl;
U32 retval;
va_list ap;

	IExec->DebugPrintF( "RA_Method_DoParentTags\n" );

	retval = RAV_General_Failure;

	if (( ! obj ) || ( obj->RA_Object_ID != ID_RAObject ))
	{
		IExec->DebugPrintF( "_main_Method_DoParentTags: Invalid Reactive Object (0x%08lx)", obj );

		retval = RAV_General_InvalidObject;
		goto bailout;
	}

	o = obj->RA_Object_Parent;

	if ( o == NULL )
	{
		IExec->DebugPrintF( "Method_DoParentTags: Object has no Parent" );

		retval = RAV_General_NoParent;
		goto bailout;
	}
	
	if ( o->RA_Object_ID != ID_RAObject )
	{
		IExec->DebugPrintF( "_main_Method_DoParentTags: Invalid Reactive Object (0x%08lx)", o );

		retval = RAV_General_InvalidObject;
		goto bailout;
	}

	cl = o->RA_Object_Class;

	if (( ! cl ) || ( cl->RA_Class_ID != ID_RAClass ))
	{
		IExec->DebugPrintF( "Method_DoParentTags: Object has no Class" );

		retval = RAV_General_InvalidClass;
		goto bailout;
	}

	// --
	
	va_start( ap, obj );

	retval = Self->Method_RunFunc( cl, o, va_getlinearva( ap, struct RA_Method * ) );

	va_end( ap );

bailout:

	return(	retval );
}
