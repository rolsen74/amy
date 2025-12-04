
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMY_FUNC _main_Class_Delete( struct ReactivePrivIFace *Self, struct RA_PrivClass *cl )
{
struct RA_PrivClass *super;
struct libBase *libBase;
U32 retval;

//	IExec->DebugPrintF( "RA_Class_Delete\n" );

	libBase = (PTR) Self->Data.LibBase;

	retval = RAV_Fail;

	if ( ! cl )
	{
//		IExec->DebugPrintF( "Class_Delete: Class Pointer is missing\n" );
		goto bailout;
	}

	if ( cl->RA_Class_ID != ID_RAClass )
	{
//		IExec->DebugPrintF( "Class_Delete: Not a Class Object\n" );
		goto bailout;
	}

	if ( ! cl->RA_Class_Super )
	{
//		IExec->DebugPrintF( "Class_Delete: Can't Delete Root Class\n" );
		goto bailout;
	}

	// --

	IExec->ObtainSemaphore( & libBase->lib_ClassSemaphore );

	if (( cl->RA_Class_Count_Objects )
	||	( cl->RA_Class_Count_SubClasses )
	||	( cl->RA_Class_Count_FindLocks ))
	{
		// Mark us for expunge
		cl->RA_Class_Flags |= RA_CLASSF_DelayedExpunge;
	}
	else
	{
		// Release IDOS->resources
		if ( cl->RA_Class_Plugin )
		{
			if ( ! Self->Misc_Plugin_Free( cl->RA_Class_Plugin ))
			{
//				IExec->DebugPrintF( "Plugin will not exit\n" );
				goto bailout;
			}

			cl->RA_Class_Plugin = NULL;
		}

		// Remove from Private/Public List
		IExec->Remove( (PTR) cl );

		if ( cl->RA_Class_Name )
		{
			IExec->FreeVec( (PTR) cl->RA_Class_Name );
			cl->RA_Class_Name = NULL;
		}

		// Adjust Class counter
		if (( super = cl->RA_Class_Super ))
		{
			if ( super->RA_Class_Count_SubClasses > 0 )
			{
				super->RA_Class_Count_SubClasses--;
			}

			// If super is marked for expunge, lets try to do so
			if ( super->RA_Class_Flags & RA_CLASSF_DelayedExpunge )
			{
				Self->Class_Delete( super );
			}
		}

		// Classes belong to Global
		// Now see Class structure
		IExec->FreeVec( cl );

		retval = RAV_OK;
	}

	IExec->ReleaseSemaphore( & libBase->lib_ClassSemaphore );

bailout:

	return(	retval );
}
