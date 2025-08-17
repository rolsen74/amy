
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2014-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

static U32 App_RAM_New(
	struct ReactiveIFace *Self,
	struct RA_Class *cl,
	struct RA_Object *obj,
	struct RAP_New *msg,
	struct AppClassData *cls,
	InstanceData *data )
{
struct RAArguments *arglist;
struct TagItem *tag;
char **argv;
STR basename;
U32 retval;
int argc;

	IExec->DebugPrintF( "App_RAM_New\n" );

	arglist	= NULL;
	argv	= NULL;
	argc	= 0;

	retval = RASuper( cl, obj, msg );

	if ( retval != RAV_General_Success )
	{
		IExec->DebugPrintF( "App_RAM_New 2\n" );
		goto bailout;
	}

	if ( retval == RAV_General_Success )
	{
		basename = Self->RA_Misc_GetTagData( msg->AttrList, RAA_APP_Base, NULL );

		if ( Self->RA_Misc_Valid_Base_Name( basename ))
		{
			data->AppBase = strdup( basename );

			if ( ! data->AppBase )
			{
				IExec->DebugPrintF( "App_RAM_New : Error allocating memory\n" );

				retval = RAV_General_OutOfMemory;
			}
		}
		else
		{
			IExec->DebugPrintF( "App_RAM_New : Application Base Name is missing\n" );

			retval = RAV_General_MissingTag;
		}
	}

	for( tag = msg->AttrList ; tag && tag->ti_Tag ; tag = RANextTag( tag ))
	{
//		IExec->DebugPrintF( "App_RAM_New : Tag $%08lx:%08lx\n", tag->ti_Tag, tag->ti_Data );

		switch( tag->ti_Tag )
		{
			case RAA_APP_Argument_Count:
			{
				argc = tag->ti_Data;

				IExec->DebugPrintF( "App_RAM_New : RAA_APP_Argument_Count : Argc %ld\n", argc );
				break;
			}

			case RAA_APP_Argument_Values:
			{
				argv = (PTR) tag->ti_Data;

				IExec->DebugPrintF( "App_RAM_New : RAA_APP_Argument_Values : Argv %p\n", argv );
				break;
			}

			case RAA_APP_Argument_List:
			{
				arglist = (PTR) tag->ti_Data;

				IExec->DebugPrintF( "App_RAM_New : RAA_APP_Argument_List : ArgList %p\n", arglist );
				break;
			}

			default:
			{
				IExec->DebugPrintF( "App_RAM_New : Unknown $%08lx:%08lx\n", tag->ti_Tag, tag->ti_Data );
				break;
			}
		}
	}

	if ( arglist )
	{
		if ( retval == RAV_OK )
		{
			data->Args = Self->RA_Arguments_ParseTags( arglist,
				RAA_Argument_Argc, argc,
				RAA_Argument_Argv, argv,
				RAA_ErrorCode, & retval,
				TAG_END
			);
		}

		if (( ! data->Args  ) || ( retval != RAV_General_Success ))
		{
			IExec->DebugPrintF( "App_RAM_New : Error parsing Arguments\n" );
			goto bailout;
		}
	}

bailout:

	return(	retval );
}
