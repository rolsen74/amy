
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMYFUNC _main_Attr_SetParentTags( struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, ... )
{
U32 retval;
va_list ap;

	va_start( ap, obj );

	retval = Self->Attr_SetParentList( obj, va_getlinearva( ap, struct TagItem * ));

	va_end( ap );

	return(	retval );
}

// --

U32 AMYFUNC _main_Attr_SetParentList( struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, struct TagItem *taglist )
{
struct TagItem *tag;
struct RAP_Set msg;
U32 retval;
U32 result;

	retval = 0;

	if (( ! obj ) || ( obj->RA_Object_ID != ID_RAObject ))
	{
		IExec->DebugPrintF( "Attr_GetParentList: Invalid Object Pointer (%p)", obj );
//		  Self->Error_LogTags( txt, obj );
		goto bailout;
	}

//--	if ( obj->RA_Object_Type == RA_Type_Gadget )
//--	{
//--		msg.MethodID	= RAM_Set;
//--		msg.AttrID		= RAA_Gadget_Quiet;
//--		msg.AttrValue	= TRUE;
//--
//--		Self->Method_DoParentList( obj, (PTR) & msg );
//--	}

	for( tag = taglist ; tag && tag->ti_Tag ; tag = Self->Misc_NextTag( tag ))
	{
		msg.MethodID	= RAM_Set;
		msg.AttrID		= tag->ti_Tag;
		msg.AttrValue	= tag->ti_Data;

		result = Self->Method_DoParentList( obj, (PTR) & msg );

		if ( result == RAV_General_Success )
		{
			retval++;
		}
	}

//--	if ( obj->RA_Object_Type == RA_Type_Gadget )
//--	{
//--		msg.MethodID	= RAM_Set;
//--		msg.AttrID		= RAA_Gadget_Quiet;
//--		msg.AttrValue	= FALSE;
//--
//--		Self->Method_DoParentList( obj, (PTR) & msg );
//--	}

bailout:

	return(	retval );
}
