
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMYFUNC _main_Attr_GetTags( struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, ... )
{
U32 retval;
va_list ap;

	va_start( ap, obj );

	retval = Self->Attr_GetList( obj, va_getlinearva( ap, struct TagItem * ));

	va_end( ap );

	return(	retval );
}

// --

U32 AMYFUNC _main_Attr_GetList( struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, struct TagItem *taglist )
{
struct TagItem *tag;
struct RAP_Get msg;
U32 retval;
U32 result;

	retval = 0;

	if (( ! obj ) || ( obj->RA_Object_ID != ID_RAObject ))
	{
		IExec->DebugPrintF( "Attr_GetList: Invalid Object Pointer (%p)", obj );
	//		  Self->Error_LogTags( txt, obj );
		goto bailout;
	}

	for( tag = taglist ; tag && tag->ti_Tag ; tag = Self->Misc_NextTag( tag ))
	{
		if ( tag->ti_Data )
		{
			msg.MethodID= RAM_Get;
			msg.AttrID	= tag->ti_Tag;
			msg.Storage	= (PTR)tag->ti_Data;

			result = Self->Method_DoList( obj, (PTR) & msg );

			if ( result == RAV_General_Success )
			{
				retval++;
			}
		}
	}

bailout:

	return(	retval );
}
