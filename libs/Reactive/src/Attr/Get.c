
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMYFUNC _main_Attr_Get( struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, U32 AttrID, PTR Storage )
{
struct RAP_Get msg;
U32 retval;

	if (( ! obj ) || ( obj->RA_Object_ID != ID_RAObject ))
	{
		IExec->DebugPrintF( "Attr_Get: Invalid Object Pointer (%p)", obj );
//		  Self->Error_LogTags( txt, obj );

		retval = RAV_General_InvalidObject;
		goto bailout;
	}

	if ( ! Storage )
	{
		IExec->DebugPrintF( "Attr_Get: Missing Storage Pointer (%p)", obj );
//		  Self->Error_LogTags( txt, obj );

		retval = RAV_General_NoStorage;
		goto bailout;
	}

	msg.MethodID= RAM_Get;
	msg.AttrID	= AttrID;
	msg.Storage	= Storage;

	retval = Self->Method_DoList( obj, (PTR) & msg );

bailout:

	return(	retval );
}
