
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMYFUNC _main_Attr_SetTags( struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, ... )
{
U32 retval;
va_list ap;

	va_start( ap, obj );

	retval = Self->Attr_SetList( obj, va_getlinearva( ap, struct TagItem * ));

	va_end( ap );

	return(	retval );
}

// --

U32 AMYFUNC _main_Attr_SetList( struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, struct TagItem *taglist )
{
struct TagItem *tag;
struct RAP_Set msg;
U32 retval;
U32 result;

	retval = 0;

	if (( ! obj ) || ( obj->RA_Object_ID != ID_RAObject ))
	{
		IExec->DebugPrintF( "Attr_SetList: Invalid Object Pointer (%p)\n", obj );
//		  Self->Error_LogTags( txt, obj );
		goto bailout;
	}

//--	if ( obj->RA3_Object_Type == RA3_Type_Gadget )
//--	{
//--		msg.MethodID	= RAM_Set;
//--		msg.AttrID		= RAA_Gadget_Quiet;
//--		msg.AttrValue	= TRUE;
//--
//--		Self->Method_DoList( obj, (APTR)&msg );
//--	}

	for( tag = taglist ; tag && tag->ti_Tag ; tag = Self->Misc_NextTag( tag ))
	{
		msg.MethodID	= RAM_Set;
		msg.AttrID		= tag->ti_Tag;
		msg.AttrValue	= tag->ti_Data;

		result = Self->Method_DoList( obj, (PTR) & msg );

	//	  IExec->DebugPrintF( "RAM_Set : %08lx : %08lx (%ld)\n", msg.AttrID, msg.AttrValue, result );

		if ( result == RAV_General_Success )
		{
			retval++;
		}
	}

//--	if ( obj->RA3_Object_Type == RA3_Type_Gadget )
//--	{
//--		msg.MethodID	= RAM_Set;
//--		msg.AttrID		= RAA_Gadget_Quiet;
//--		msg.AttrValue	= FALSE;
//--
//--		Self->Method_DoList( obj, (APTR)&msg );
//--	}

bailout:

	return(	retval );
}
