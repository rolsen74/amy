
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMYFUNC _main_Method_DoSuperTags(
	struct ReactivePrivIFace *Self,
	struct RA_PrivClass *cl,
	struct RA_PrivObject *obj,
	... )
{
U32 retval;
va_list ap;

//	IExec->DebugPrintF( "RA_Method_DoSuperTags\n" );

	if (( ! cl ) || ( cl->RA_Class_ID != ID_RAClass ))
	{
//		IExec->DebugPrintF( "Method_DoSuperArgs: Invalid Reactive Class (0x%08lx)", obj );
//		  Self->Error_LogTags( txt, cl );

		retval = RAV_General_InvalidClass;
		goto bailout;
	}

	if (( ! obj ) || ( obj->RA_Object_ID != ID_RAObject ))
	{
//		IExec->DebugPrintF( "Method_DoSuperArgs: Invalid Reactive Object (0x%08lx)", obj );
//		  Self->Error_LogTags( txt, obj );

		retval = RAV_General_InvalidObject;
		goto bailout;
	}

	va_start( ap, obj );

	retval = Self->Method_RunFunc( cl->RA_Class_Super, obj, va_getlinearva( ap, struct RA_Method * ));

	va_end( ap );

bailout:

	return(	retval );
}
