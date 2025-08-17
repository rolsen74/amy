
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMYFUNC _main_Class_Add( struct ReactivePrivIFace *Self, struct RA_PrivClass *cl, STR PubName )
{
struct libBase *libBase;
U32 retval;
STR name;

	IExec->DebugPrintF( "RA_Class_Add\n" );

	libBase = (PTR) Self->Data.LibBase;

	retval	= FALSE;

	if ( ! cl )
	{
		IExec->DebugPrintF( "Class_Add: Class Pointer is missing\n" );
		goto bailout;
	}

	if ( cl->RA_Class_ID != ID_RAClass )
	{
		IExec->DebugPrintF( "Class_Add: Not a Class Object\n" );
		goto bailout;
	}

	if ( cl->RA_Class_Name )
	{
		IExec->DebugPrintF( "Class_Add: Class is allready public\n" );
		goto bailout;
	}

	if (( ! PubName ) || ( PubName[0] == 0 ))
	{
		IExec->DebugPrintF( "Class_Add: Public Name is missing\n" );
		goto bailout;
	}

	if ( ! Self->Misc_Valid_Class_Name( PubName ))
	{
		IExec->DebugPrintF( "Class name used\n" );
		goto bailout;
	}

	cl->RA_Class_NameLength = strlen( PubName );

	name = IExec->AllocVecTags( cl->RA_Class_NameLength,
		AVT_Clear, 0,
		TAG_END
	);

	if ( ! name )
	{
		IExec->DebugPrintF( "Class_Add: Error copying Name\n" );
		goto bailout;
	}

	memcpy( name, PubName, cl->RA_Class_NameLength );

	cl->RA_Class_Name = name;

	IExec->DebugPrintF( "Making Public Class %p (%s)\n", cl, PubName );

	IExec->ObtainSemaphore( & libBase->lib_ClassSemaphore );

	// Remove from Private List
	IExec->Remove( (PTR) cl );

	// Add to Public List
	IExec->AddTail( & libBase->lib_PublicClassHeader, (PTR) cl );

	IExec->ReleaseSemaphore( &libBase->lib_ClassSemaphore );

	retval = TRUE;

bailout:

	return(	retval );
}

