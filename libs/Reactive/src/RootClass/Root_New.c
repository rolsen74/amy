
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

static U32 Root_New(
UNUSED	struct ReactivePrivIFace *Self,
UNUSED	struct RA_PrivClass *cl,
UNUSED	struct RA_PrivObject *obj,
UNUSED	struct RAP_New *msg,
UNUSED	struct libBase *libBase,
UNUSED	struct RootClass_Data *rcd )
{
//struct RA_PrivStyle *s;
struct TagItem *tag;
U32 retval;

	IExec->DebugPrintF( "Root_New\n" );

	IExec->NewList( & rcd->rcd_NotifyList );

	// Object Data is first inited in CreateObject()

	for( tag = msg->AttrList ; tag && tag->ti_Tag ; tag = Self->Misc_NextTag( tag ))
	{
		if ( ! tag )
		{
			break;
		}

		switch( tag->ti_Tag )
		{
			// case RAA_ID:
			// {
			// 	rcd->rcd_ID = (CONST_STRPTR)tag->ti_Data;
			// 	break;
			// }

			// case RAA_IDNr:
			// {
			// 	rcd->rcd_IDNr = tag->ti_Data;
			// 	break;
			// }

			// case RAA_UserData:
			// {
			// 	rcd->rcd_UserData = tag->ti_Data;
			// 	break;
			// }

//--			case RAA_Style:
//--			{
//--				s = (PTR) tag->ti_Data;
//--
//--				if ( s == NULL )
//--				{
//--					retval = RAV_General_InvalidObject;
//--					goto bailout;
//--				}
//--
//--				if ( IReactive->Misc_GetSubType( s ) != RA_Type_Style )
//--				{
//--					retval = RAV_General_WrongType;
//--					goto bailout;
//--				}
//--
//--				if ( rcd->rcd_Object.RA_Object_Style )
//--				{
//--					if ( rcd->rcd_StyleName )
//--					{
//--						IReactive->Style_Unlock( rcd->rcd_Object.RA_Object_Style );
//--						rcd->rcd_StyleName = NULL;
//--					}
//--					else
//--					{
//--						rcd->rcd_Object.RA_Object_Style->RA_Style_Count_Open--;
//--					}
//--					rcd->rcd_Object.RA_Object_Style = NULL;
//--				}
//--
//--				rcd->rcd_Object.RA_Object_Style = s;
//--				rcd->rcd_Object.RA_Object_Style->RA_Style_Count_Open++;
//--				break;
//--			}
//--
//--			case RAA_StyleName:
//--			{
//--				if ( rcd->rcd_Object.RA_Object_Style )
//--				{
//--					if ( rcd->rcd_StyleName )
//--					{
//--						IReactive->Style_Unlock( rcd->rcd_Object.RA_Object_Style );
//--						rcd->rcd_StyleName = NULL;
//--					}
//--					else
//--					{
//--						rcd->rcd_Object.RA_Object_Style->RA_Style_Count_Open--;
//--					}
//--					rcd->rcd_Object.RA_Object_Style = NULL;
//--				}
//--
//--				rcd->rcd_Object.RA_Object_Style = IReactive->Style_FindTags( (CONST_STRPTR)tag->ti_Data, TAG_END );
//--
//--//		  IExec->DebugPrintF( "Style : %p, Name : %s, Object : %p\n",
//--//				  rcd->rcd_Object.RA_Object_Style, tag->ti_Data, obj );
//--
//--				if ( rcd->rcd_Object.RA_Object_Style == NULL )
//--				{
//--					retval = RAV_General_Failure;
//--					goto bailout;
//--				}
//--
//--				rcd->rcd_StyleName = (CONST_STRPTR)tag->ti_Data;
//--				break;
//--			}

			// case RAA_Parent:
			// {
			// 	rcd->rcd_Object.RA_Object_Parent = (PTR)tag->ti_Data;
			// 	break;
			// }

			// case RAA_SemaphoreLock:
			// {
			// 	if ( tag->ti_Data )
			// 	{
			// 		rcd->rcd_Flags &= ~ROOTCLASSF_NoSemaphore;
			// 	}
			// 	else
			// 	{
			// 		rcd->rcd_Flags |= ROOTCLASSF_NoSemaphore;
			// 	}
			// 	break;
			// }

			default:
			{
				//retval = RAV_General_Failure;
				break;
			}
		}
	}

	retval = RAV_General_Success;

//bailout:

	return(	retval );
}

// --
