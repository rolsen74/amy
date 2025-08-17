
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMYFUNC _main_Class_Unlock( struct ReactivePrivIFace *Self, struct RA_PrivClass *cl )
{
struct libBase *libBase;
U32 retval;

	IExec->DebugPrintF( "RA_Class_Unlock\n" );

	libBase = (PTR) Self->Data.LibBase;

	retval = RAV_General_Failure;

	IExec->ObtainSemaphore( & libBase->lib_ClassSemaphore );

	if ( ! cl )
	{
//		IExec->DebugPrintF( "Class_Unlock: Error NULL Pointer" );
		goto bailout;
	}

	if ( cl->RA_Class_ID != ID_RAClass )
	{
//		IExec->DebugPrintF( "Class_Unlock: Not an valid Class" );
		goto bailout;
	}

	if ( ! cl->RA_Class_Count_FindLocks )
	{
//		IExec->DebugPrintF( "Class_Unlock: Unexpected Unlock" );
		goto bailout;
	}

	cl->RA_Class_Count_FindLocks--;

	retval = RAV_General_Success;

bailout:

	IExec->ReleaseSemaphore( & libBase->lib_ClassSemaphore );

	return(	retval );
}
