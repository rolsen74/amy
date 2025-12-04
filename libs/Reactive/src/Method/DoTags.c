
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMY_FUNC _main_Method_DoTags(
	struct ReactivePrivIFace *Self,
	struct RA_PrivObject *obj,
	... )
{
struct RA_PrivClass *cl;
struct RA_Method *m;
U32 retval;
va_list ap;

//	IExec->DebugPrintF( "RA_Method_DoTags\n" );

	if (( ! obj ) || ( obj->RA_Object_ID != ID_RAObject ))
	{
//		IExec->DebugPrintF( "Method_DoArgs: Invalid Reactive object (0x%08lx)", obj );
//		  Self->Error_LogTags( txt, obj );

		retval = RAV_General_InvalidObject;
		goto bailout;
	}

	va_start( ap, obj );

	cl = obj->RA_Object_Class;
	m  = va_getlinearva( ap, struct RA_Method * );

	#if 0

	if ( cl->RA_Class_ID != ID_RAClass )
	{
//		IExec->DebugPrintF( "Method_DoTags: Invalid Class ID\n" );
	}

	if (( m->RA_Method_ID & 0xff000000 ) != 0xac000000 )
	{
//		IExec->DebugPrintF( "Method_DoTags: Not a system MethodID\n" );
	}

	#endif

//IExec->DebugPrintF( "DoTags: %p, %p %p %p\n", Self, cl, obj, m );

	retval = Self->Method_RunFunc( cl, obj, m );

	va_end( ap );

bailout:

	return(		retval );
}
