
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

#include "Root_New.c"
#include "Root_Delete.c"

// --

STR GetTagGroup( U32 val )
{
STR txt;

	switch( val & 0xACFFF000 )
	{
		case RAB_Global:		txt = "RAB_Global ";		break;
		case RAB_Root:			txt = "RAB_Root ";			break;
//		case RAB_User:			txt = "RAB_User ";			break;

		case RAB_Application:	txt = "RAB_Application ";	break;
		case RAB_Directory:		txt = "RAB_Directory ";		break;
//		case RAB_Array:			txt = "RAB_Array ";			break;
//		case RAB_Gadget:		txt = "RAB_Gadget ";		break;
//		case RAB_Hash:			txt = "RAB_Hash ";			break;
//		case RAB_USBStack:		txt = "RAB_USBStack ";		break;
//		case RAB_Window:	    txt = "RAB_Window ";	    break;
//
//		  case RAB_List:      	  txt = "RAB_List ";		  break;
//		  case RAB_Stream:		  txt = "RAB_Stream ";		  break;
//		  case RAB_File:		  txt = "RAB_File ";		  break;
//		  case RAB_Group:		  txt = "RAB_Group ";		  break;
//		  case RAB_Button:		  txt = "RAB_Button ";		  break;
//		  case RAB_Scroller:	  txt = "RAB_Scroller ";	  break;
//		  case RAB_Page:		  txt = "RAB_Page ";		  break;
//		  case RAB_Chooser:		  txt = "RAB_Chooser ";		  break;
//		  case RAB_Date:		  txt = "RAB_Date ";		  break;
//		  case RAB_Socket:		  txt = "RAB_Socket ";		  break;
//		  case RAB_Mutex:		  txt = "RAB_Mutex ";		  break;
//		  case RAB_ListView:	  txt = "RAB_ListView ";	  break;
//		  case RAB_IFF:			  txt = "RAB_IFF ";			  break;
//		  case RAB_GIF:			  txt = "RAB_GIF ";			  break;
//		  case RAB_LW_Camera:	  txt = "RAB_LW_Camera ";	  break;
//		  case RAB_LW_Light:	  txt = "RAB_LW_Light ";	  break;
//		  case RAB_LW_Motion:	  txt = "RAB_LW_Motion ";	  break;
//		  case RAB_LW_Object:	  txt = "RAB_LW_Object ";	  break;
//		  case RAB_LW_Scene:	  txt = "RAB_LW_Scene ";	  break;
//		  case RAB_Media:		  txt = "RAB_Media ";		  break;
//		  case RAB_Media_Coder:	  txt = "RAB_Media_Coder ";	  break;
//		  case RAB_Media_Filter:  txt = "RAB_Media_Filter ";  break;
//		  case RAB_Media_Mutex:	  txt = "RAB_Media_Mutex ";	  break;
//		  case RAB_Media_Output:  txt = "RAB_Media_Output ";  break;
		default:				txt = "";					break;
	}

	return( txt );
}

// --

U32 RootDispatcher(
	struct ReactivePrivIFace * Self,
	struct RA_PrivClass		* cl,
	struct RA_PrivObject	* obj,
	struct RA_Method		* msg,
	struct libBase			* libBase,
	struct RootClass_Data	* rcd )
{
U32 retval;

//	IExec->DebugPrintF( "Root Dispatcher\n" );

	#define RUNFUNC(x)	retval = x( Self, cl, obj, (PTR) msg, libBase, rcd ); break

	switch( msg->RA_Method_ID )
	{
		case RAM_New:				RUNFUNC( Root_New );
		case RAM_Delete:			RUNFUNC( Root_Delete );
//		case RAM_Set:				RUNFUNC( Root_Set );
//		case RAM_Get:				RUNFUNC( Root_Get );
//		case RAM_AddNotify:			RUNFUNC( Root_AddNotify );
//		case RAM_RemNotify:			RUNFUNC( Root_RemNotify );
//		case RAM_CheckNotify:		RUNFUNC( Root_CheckNotify );
//		case RAM_FindIDNr:			RUNFUNC( Root_FindIDNr );
//
//		case RAM_SetWindow:			RUNFUNC( Root_SetWindow );
//		case RAM_SetSemaphore:		RUNFUNC( Root_SetSemaphore );
//		case RAM_SetApplication:	RUNFUNC( Root_SetApplication );

		default:
		{
//			IExec->DebugPrintF( "Root Class : Unknown $%08lx %sMethod\n", msg->RA_Method_ID, GetTagGroup( msg->RA_Method_ID ));

//			#ifdef DEBUG
//			IExec->DebugPrintF( "\nUnknown %sMethod: 0x%08lx\n\n", (PTR) GetTagGroup( msg->RA_Method_ID ), msg->RA_Method_ID );
//			#endif

			retval = RAV_General_NotImplemented;
			break;
		}
	}

	#undef RUNFUNC

	return(	retval );
}

// --
