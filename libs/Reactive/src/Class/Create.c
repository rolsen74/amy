
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

struct RA_PrivClass * AMY_FUNC _main_Class_CreateTags(
	struct ReactivePrivIFace *Self,
	struct RA_PrivClass *SuperClass,
	STR SuperName,
	U32 ObjectDataSize,
	PTR Dispatcher,
	... )
{
struct RA_PrivClass *cl;
va_list ap;

	va_start( ap, Dispatcher );

	cl = Self->Class_CreateList(
		SuperClass,
		SuperName,
		ObjectDataSize,
		Dispatcher,
		va_getlinearva( ap, struct TagItem * )
	);

	va_end( ap );

	return(	cl );
}

// --

struct RA_PrivClass * AMY_FUNC _main_Class_CreateList(
	struct ReactivePrivIFace *Self,
	struct RA_PrivClass *SuperClass,
	STR SuperName,
	U32 ObjectDataSize,
	PTR Dispatcher,
	struct TagItem *taglist UNUSED )
{
struct RA_PrivClass *cl, *super;
struct libBase *libBase;
S32 findlock;
S32 error;

//	IExec->DebugPrintF( "RA_Class_CreateList: '%s'\n", SuperName );

	libBase = (PTR) Self->Data.LibBase;

	findlock = FALSE;

	super	= NULL;
	error	= TRUE;
	cl		= NULL;

	IExec->ObtainSemaphore( & libBase->lib_ClassSemaphore );

	if (( SuperClass == NULL ) && (( SuperName == NULL ) || ( SuperName[0] == 0 )))
	{
//		IExec->DebugPrintF( "Class_Create: Missing Super Class Pointer\n" );
		goto bailout;
	}

	if ( ! Dispatcher )
	{
//		IExec->DebugPrintF( "Class_Create: Missing Dispatcher Pointer\n" );
		goto bailout;
	}

	if ( SuperClass )
	{
		super = SuperClass;

		if ( super->RA_Class_ID != ID_RAClass )
		{
//			IExec->DebugPrintF( "Class_Create: Invalid SuperClass Pointer\n" );
			goto bailout;
		}
	}
	else
	{
		super = Self->Class_FindTags( SuperName, TAG_END );

		if ( ! super )
		{
//			IExec->DebugPrintF( "Class_Create: SuperClass '%s' not found\n", SuperName );
			goto bailout;
		}

		findlock = TRUE;
	}

	// --

	// Class should be Globaly tracked
	cl = IExec->AllocVecTags( sizeof( struct RA_PrivClass ),
		AVT_Clear, 0,
		TAG_END
	);

	if ( ! cl )
	{
//		IExec->DebugPrintF( "Class_Create: Error allocating class memory\n" );
		goto bailout;
	}

	IExec->AddTail( & libBase->lib_PrivateClassHeader, (PTR) cl );

	super->RA_Class_Count_SubClasses++;
	super->RA_Class_Flags &= ~RA_CLASSF_DelayedExpunge;

	// Make it nicely 8 byte alligned
	ObjectDataSize +=  7;
	ObjectDataSize &= ~7;

//	cl->RA_Class_Next           	 = NULL;
//	cl->RA_Class_Prev           	 = NULL;
	cl->RA_Class_Type				 = super->RA_Class_Type;
	cl->RA_Class_ID             	 = ID_RAClass;
	cl->RA_Class_Super          	 = super;
//	cl->RA_Class_Plugin			 = NULL;
//	cl->RA_Class_Count_Objects		 = 0;
//	cl->RA_Class_Count_SubClasses	 = 0;
	cl->RA_Class_Dispatcher     	 = Dispatcher;
	cl->RA_Class_InstSize       	 = ObjectDataSize;
	cl->RA_Class_InstTotalSize		 = super->RA_Class_InstTotalSize + ObjectDataSize;
	cl->RA_Class_InstOffset     	 = super->RA_Class_InstTotalSize;
//	cl->RA_Class_Name				 = NULL;
//	cl->RA_Class_Data				 = NULL;

//	IExec->DebugPrintF( "New Class %p\n", cl );

	error = FALSE;

bailout:

	if (( super ) && ( findlock ))
	{
		Self->Class_Unlock( super );
	}

	if (( error ) && ( cl ))
	{
		Self->Class_Delete( cl );
		cl = NULL;
	}

	IExec->ReleaseSemaphore( & libBase->lib_ClassSemaphore );

	return(	cl );
}

// --
