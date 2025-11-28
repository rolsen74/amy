
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

const struct ClassType ClassTypes[] =
{
	{ RA_Type_Application,	RAC_Application,	NULL,								NULL							},
//	{ RA_Type_Compress,		RAC_Compress,		"libs:RA3/Compress_#?_Class.ra",	"libs:RA3/Compress_%s_Class.ra"	},
//	{ RA_Type_Crypto,		RAC_Crypto,			"libs:RA3/Crypto_#?_Class.ra",		"libs:RA3/Crypto_%s_Class.ra"	},
//	{ RA_Type_Gadget,		RAC_Gadget,			"libs:RA3/Gadget_#?_Class.ra",		"libs:RA3/Gadget_%s_Class.ra"	},
//	{ RA_Type_Hash,			RAC_Hash,			"libs:RA3/Hash_#?_Class.ra",		"libs:RA3/Hash_%s_Class.ra"		},
//	{ RA_Type_Stream,		RAC_Stream,			"libs:RA3/Stream_#?_CLass.ra",		"libs:RA3/Stream_%s_Class.ra"	},
//	{ RA_Type_Timer,		RAC_Timer,			NULL,								NULL							},
//	{ RA_Type_Window,		RAC_Window,			NULL,								NULL							},
	{ RA_Type_Unknown,		NULL,				NULL,								NULL							},
};

// --

struct RA_PrivClass * AMYFUNC _main_Class_FindTags( struct ReactivePrivIFace *Self, STR name, ... )
{
struct RA_PrivClass *cl;
va_list ap;

	va_start( ap, name );

	cl = Self->Class_FindList( name, va_getlinearva( ap, struct TagItem * ));

	va_end( ap );

	return(	cl );
}

// --

struct RA_PrivClass * AMYFUNC _main_Class_FindList( struct ReactivePrivIFace *Self, STR name, struct TagItem *taglist UNUSED )
{
struct RA_PrivClass *cl;
struct libBase *libBase;
STR name2;
U32 len;
U32 pos;
//S32 dologs;

//	IExec->DebugPrintF( "RA_Class_FindList : %s\n", name );

	libBase = (PTR) Self->Data.LibBase;

	cl = NULL;

	// ---

//	  dologs = Self->Misc_GetTagValue( taglist, RAA_LogMessages, TRUE );

	if (( name == NULL ) || ( name[0] == 0 ))
	{
//		IExec->DebugPrintF( "RA_Class_Find : invalid class name\n" );

//		  if ( dologs )
//		  {
//			  Self->Error_LogTags( "Class_Find: invalid class name" );
//		  }

		goto bailout;
	}

	// ---

	IExec->ObtainSemaphore( & libBase->lib_ClassSemaphore );

	cl = (PTR) IExec->GetHead( & libBase->lib_PublicClassHeader );

	name2 = (PTR) IDOS->FilePart( name );

	len = strlen( name2 );

	while( cl )
	{
		if (( len == cl->RA_Class_NameLength ) && ( strcmp( cl->RA_Class_Name, name2 ) == 0 ))
		{
//			IExec->DebugPrintF( "RA_Class_Find : Found '%s' Class\n", name2 );
			break;
		}
		else
		{
			cl = (PTR) IExec->GetSucc( (PTR) cl );
		}
	}

	if ( ! cl )
	{
		// Class not found - try to load class from disk
		cl = Self->Misc_Plugin_Open( name );

		if ( ! cl )
		{
//			IExec->DebugPrintF( "RA_Class_Find : Error finding %s class\n", name );

//			  if ( dologs )
//			  {
//				  Self->Error_LogTags( "Class_Find: Error finding %s class", name );
//			  }
		}
		else
		{
			pos = 0;

			while( ClassTypes[pos].Name )
			{
				if ( ! strcmp( ClassTypes[pos].Name, name ))
				{
					break;
				}
				else
				{
					pos++;
				}
			}

			if ( ClassTypes[pos].Name )
			{
				cl->RA_Class_Type = ClassTypes[pos].Type;
			}
			else if ( cl->RA_Class_Super )
			{
				cl->RA_Class_Type = cl->RA_Class_Super->RA_Class_Type;
			}
		}
	}

	if ( cl )
	{
		cl->RA_Class_Count_FindLocks++;
	}

	IExec->ReleaseSemaphore( & libBase->lib_ClassSemaphore );

	// ---

	#if 0
	if (( cl == NULL ) && ( dologs ))
	{
		// To avoid a dead lock, we have to make sure not to send a msg to our self
		if ( IExec->FindTask( NULL ) != (PTR)libBase->lib_MasterProcess )
		{
			memset( & msg, 0, sizeof( msg ));

			msg.RA_Message_ID		 = ID_RAProcessMessage;
			msg.RA_Message_Task	 = IExec->FindTask( NULL );
			msg.RA_Message_Signal	 = SIGBREAKF_CTRL_D;
			msg.RA_Message_Command	 = RACmd_ShowMessage;
			msg.RA_Message_Title	 = (PTR)"Missing Class";
			msg.RA_Message_Message	 = myPrintF( "Class '%s' could not be found", name );

			IExec->PutMsg( libBase->lib_CmdMsgPort, (PTR) & msg );

			while( TRUE )
			{
				mask = IExec->Wait( msg.RA_Message_Signal );

				if ( mask & msg.RA_Message_Signal )
				{
					break;
				}
			}

			IExec->FreeVec( msg.RA_Message_Message );
		}
	}
	#endif

	// --

bailout:

	return(	cl );
}
