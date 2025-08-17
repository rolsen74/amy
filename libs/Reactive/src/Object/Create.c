
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

extern const struct ClassType ClassTypes[];

// --

struct RA_PrivObject * AMYFUNC _main_Object_CreateTags(
	struct ReactivePrivIFace *Self,
	struct RA_PrivClass *Class,
	STR ClassName,
	... )
{
struct RA_PrivObject *obj;
va_list ap;

	IExec->DebugPrintF( "RA_Object_CreateTags\n" );

	va_start( ap, ClassName );

	obj	= Self->Object_CreateList( Class, ClassName, va_getlinearva( ap, struct TagItem * ));

	va_end( ap );

	return(	obj );
}

// --

struct RA_PrivObject * AMYFUNC _main_Object_CreateList(
	struct ReactivePrivIFace *Self,
	struct RA_PrivClass *Class,
	STR ClassName,
	struct TagItem *taglist )
{
struct RootClass_Data *rcd;
struct RA_PrivObject *obj;
struct RA_PrivClass *cl;
//struct libInstance *data;
//struct libBase *libBase;
U32 retval;
U32 btype;
U32 pos;
U32 *err;
S32 findlock;
//S32 dologs;

	IExec->DebugPrintF( "RA_Object_CreateList\n" );

	#if 0
	if ( Class )
	{
		IExec->DebugPrintF( "ClassPtr: %p\n", Class );
	}
	else
	{
		IExec->DebugPrintF( "ClassName: %s\n", ClassName );
	}

	if ( taglist )
	{
		IExec->DebugPrintF( "TagList: %08lx:%08lx\n", taglist->ti_Tag, taglist->ti_Data );
	}
	else
	{
		IExec->DebugPrintF( "TagList: NULL\n" );
	}
	#endif

	// --

	findlock = FALSE;

//	  libBase = (PTR) Self->Data.LibBase;

//	  data	  = (struct libInstance *)((U32) Self - Self->Data.NegativeSize );

//	  dologs  = Self->Misc_GetTagValue( taglist, RAA_LogMessages, TRUE );
	btype	= Self->Misc_GetTagValue( taglist, RAA_Object_BaseType, 0 );

	retval	= RAV_OK;

	obj		= NULL;

	if ( Class )
	{
		cl = Class;

		if ( Self->Class_Lock( cl ) != RAV_General_Success )
		{
//			IExec->DebugPrintF( "Object_Create: Invalid Class Pointer" );

//--			if ( dologs == TRUE )
//--			{
//--				Self->Error_LogTags( "Object_Create: Invalid Class Pointer" );
//--			}

			retval = RAV_General_Failure;
			goto bailout;
		}

		findlock = TRUE;
	}
	else
	{
		pos = 0;

		while( ClassTypes[pos].Type )
		{
			if ( btype == ClassTypes[pos].Type )
			{
				break;
			}
			else
			{
				pos++;
			}
		}

		cl = Self->Class_FindTags( ClassName,
//			  RAA_LogMessages, ( ClassTypes[pos].String ) ? FALSE : dologs,
			TAG_END
		);

		if (( ! cl ) && ( ClassTypes[pos].String ))
		{
//			STR cname = Self->Memory_PrintF( ClassTypes[pos].String, ClassName );
			STR cname = NULL;

			asprintf( & cname, ClassTypes[pos].String, ClassName );

			cl = Self->Class_FindTags( cname,
//				  RAA_LogMessages, dologs,
				TAG_END
			);

			free( cname );
		}

		if ( ! cl )
		{
//			IExec->DebugPrintF( "Object_Create: Class not found" );

//--			if ( dologs )
//--			{
//--				Self->Error_LogTags( "Object_Create: Class not found" );
//--				SHOWMSG( 1,			"Object_Create: Class not found" );
//--			}

			retval = RAV_General_Failure;
			goto bailout;
		}

		findlock = TRUE;
	}

	if (( btype ) && ( cl->RA_Class_Type != btype ))
	{
		IExec->DebugPrintF( "Object_Create : Class not the correct Base Type" );

//--		if ( dologs )
//--		{
//--			Self->Error_LogTags( "Object_Create: Class not the correct Base Type" );
//--			SHOWMSG( 1,			"Object_Create: Class not the correct Base Type" );
//--		}

		retval = RAV_General_Failure;
		goto bailout;
	}

	// ---

	// Track memory
	obj = malloc( cl->RA_Class_InstTotalSize );

	if ( ! obj )
	{
		IExec->DebugPrintF( "Object_Create: Error allocating memory for new object" );

//--		if ( dologs == TRUE )
//--		{
//--			Self->Error_LogTags( "Object_Create: Error allocating memory for new object" );
//--			SHOWMSG( 1,			"Object_Create: Error allocating memory for new object" );
//--		}

		retval = RAV_General_OutOfMemory;
		goto bailout;
	}

	// Adjust Super
	cl->RA_Class_Count_Objects++;
	cl->RA_Class_Flags &= ~RA_CLASSF_DelayedExpunge;

	// Init Object
	obj->RA_Object_ID    = ID_RAObject;
	obj->RA_Object_Type  = cl->RA_Class_Type;
	obj->RA_Object_Class = cl;

	rcd = (PTR) obj;

	IExec->NewList(			& rcd->rcd_NotifyList );
	IExec->InitSemaphore(	& rcd->rcd_Semaphore );
	rcd->rcd_SemaphoreAdr =	& rcd->rcd_Semaphore;

	// ---

	retval = Self->Method_DoTags( obj, RAM_New, taglist );

	if ( retval != RAV_General_Success )
	{
//--		if ( dologs == TRUE )
//--		{
//--			Self->Error_LogTags( "Object_Create: Error initalizing new object" );
//--			SHOWMSG( 1,			"Object_Create: Error initalizing new object" );
//--		}

		Self->Object_Delete( obj );
		obj = NULL;
		goto bailout;
	}

	// ---

	#if 0
	if ( obj->RA_Object_Type == RA_Type_Application )
	{
		if ( data->data_AppObject == NULL )
		{
			data->data_AppObject = obj;

			STRPTR str = Self->Misc_GetTagData( taglist, RAA_APP_Base, NULL );

			data->data_AppBase = strdup( str );

			// -- Prefs Notify

			#if 0
			if ( libBase->lib_PrefsMsgPort )
			{
				struct PrefsMessage *msg;

				msg	= IExec->AllocVecTags( sizeof( struct PrefsMessage ),
					AVT_Clear, 0,
					TAG_END
				);

				if ( msg )
				{
					msg->RA_Message_Command = 504;
					msg->RA_Message_ID = data->data_PrgID;
					msg->RA_Message_Pointer = data->data_AppBase;

					IExec->Disable();
					if ( libBase->lib_PrefsMsgPort )
					{
						IExec->PutMsg( libBase->lib_PrefsMsgPort, (PTR) msg );
						IExec->Enable();
					}
					else
					{
						IExec->Enable();
						IExec->FreeVec( msg );
					}
				}
			}
			#endif

			// --
		}
	
		// Only AppClass knows the RootDict so we pass NULL and let AppClass handle it
		Self->Method_DoTags( obj, RAM_LoadPrefs, NULL );
	}
	#endif

	// ---

bailout:

	if ( retval != RAV_General_Success )
	{
		err = Self->Misc_GetTagData( taglist, RAA_ErrorCode, NULL );

		if (( err ) && ( *err == RAV_General_Success ))
		{
			*err = retval;
		}
	}

	if (( cl ) && ( findlock ))
	{
		Self->Class_Unlock( cl );
	}

	IExec->DebugPrintF( "Object_Create : New Object %p\n", obj );

	return(	obj );
}

// --
