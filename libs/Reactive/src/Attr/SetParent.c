
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMYFUNC _main_Attr_SetParent( struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, U32 AttrID, U32 AttrValue )
{
struct RAP_Set msg;
U32 retval;

	if (( ! obj ) || ( obj->RA_Object_ID != ID_RAObject ))
	{
		IExec->DebugPrintF( "Attr_SetParent: Invalid Object Pointer (%p)", obj );
//		  Self->Error_LogTags( txt, obj );

		retval = RAV_General_InvalidObject;
		goto bailout;
	}

	msg.MethodID	= RAM_Set;
	msg.AttrID		= AttrID;
	msg.AttrValue	= AttrValue;

	retval = Self->Method_DoParentList( obj, (PTR) & msg );

bailout:

	return(	retval );
}
