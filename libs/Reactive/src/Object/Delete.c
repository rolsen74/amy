
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 _main_Object_Delete(
	struct ReactivePrivIFace *Self,
	struct RA_PrivObject *obj )
{
struct RA_PrivClass *cl;
struct libBase *libBase;
U32 retval;

	IExec->DebugPrintF( "RA_Object_Delete\n" );

	libBase = (PTR) Self->Data.LibBase;

	retval	= FALSE;

	if (( ! obj ) || ( obj->RA_Object_ID != ID_RAObject ))
	{
//		  Self->Error_LogTags( "Object_Delete: Invalid Reactive object (%p)", obj );
//		  SHOWMSG( 1,		  "Object_Delete: Invalid Reactive object (%p)", obj );
		goto bailout;
	}

//	if ( obj->RA_Object_Type == RA_Type_Application )
//	{
//		// Only AppClass knows the RootDict so we pass NULL and let AppClass handle it
//		Self->Method_DoTags( obj, RAM_SavePrefs, NULL );
//	}

	cl = obj->RA_Object_Class;

	Self->Method_DoTags( obj, RAM_Delete );

	// Free Tracked memory
	free( obj );

	// --

	IExec->ObtainSemaphore( & libBase->lib_ClassSemaphore );
	
	// Ajust Class counter
	if ( cl->RA_Class_Count_Objects )
	{
		cl->RA_Class_Count_Objects--;
	}

	// If Class is marked for expunge, lets try to do so
	if (( cl->RA_Class_Count_Objects	== 0 )
	&&	( cl->RA_Class_Count_SubClasses == 0 )
	&&	( cl->RA_Class_Count_FindLocks	== 0 )
	&&	( cl->RA_Class_Flags & RA_CLASSF_DelayedExpunge ))
	{
		Self->Class_Delete( cl );
	}

	IExec->ReleaseSemaphore( & libBase->lib_ClassSemaphore );

	// --

	retval = TRUE;

bailout:

	return(	retval );
}

// --
