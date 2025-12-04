
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMY_FUNC _main_Attr_GetSuperTags( struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, ... )
{
U32 retval;
va_list ap;

	va_start( ap, obj );

	retval = Self->Attr_GetSuperList( obj, va_getlinearva( ap, struct TagItem * ));

	va_end( ap );

	return(	retval );
}

// --

U32 AMY_FUNC _main_Attr_GetSuperList( struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, struct TagItem *taglist )
{
struct TagItem *tag;
struct RAP_Get msg;
U32 retval;
U32 result;

	retval = 0;

	if (( ! obj ) || ( obj->RA_Object_ID != ID_RAObject ))
	{
//		IExec->DebugPrintF( "Attr_GetSuperList: Invalid Object Pointer (%p)", obj );
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

			result = Self->Method_DoSuperList( obj->RA_Object_Class, obj, (PTR) & msg );

			if ( result == RAV_General_Success )
			{
				retval++;
			}
		}
	}

bailout:

	return(	retval );
}
