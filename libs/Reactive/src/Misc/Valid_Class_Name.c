
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

S32 AMYFUNC _main_Misc_Valid_Class_Name( struct ReactivePrivIFace *Self, STR name )
{
struct RA_PrivClass *cl;
struct libBase *libBase;
S32 retval;
U32 len;

//	IExec->DebugPrintF( "RA_Misc_Valid_Class_Name : Name '%s'\n", (name)?name:"<NULL>" );

	libBase = (PTR) Self->Data.LibBase;
	IExec->ObtainSemaphore( & libBase->lib_ClassSemaphore );

	retval = FALSE;

	if ( ! name )
	{
//		IExec->DebugPrintF( "NULL Pointer\n" );
		goto bailout;
	}

	len = strlen( name );

	cl = (PTR) IExec->GetHead( & libBase->lib_PublicClassHeader );

	while( cl )
	{
		if (( len == cl->RA_Class_NameLength ) && ( ! strcmp( cl->RA_Class_Name, name )))
		{
			break;
		}
		else
		{
			cl = (PTR) IExec->GetSucc( (PTR) cl );
		}
	}

	if ( cl )
	{
//		IExec->DebugPrintF( "Name allready Used\n" );
		goto bailout;
	}

	retval = TRUE;

bailout:

	IExec->ReleaseSemaphore( & libBase->lib_ClassSemaphore );

	return(	retval );
}
