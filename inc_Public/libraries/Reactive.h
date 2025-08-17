
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_LIBRARIES_REACTIVE_H
#define AMYLIB_LIBRARIES_REACTIVE_H

// --

#include <proto/exec.h>
#include "Amy_Defines.h"
#include "Reactive/ra_Reactive.h"
#include "Reactive/ra_Plugin.h"

// --

/***[ Class ]***************************************************************/

struct RA_Class
{
	U32						I_Am_Private;
};

/***[ Object ]**************************************************************/

struct RA_Object
{
	U32						I_Am_Private;
};

/***[ Method ]**************************************************************/

struct RA_Method
{
	U32						RA_Method_ID;
};

/***[ Reactive Window Node ]************************************************/

struct RA_WindowNode
{
	struct RA_WindowNode *	Next;
	struct RA_WindowNode *	Prev;
	U32						Version;
	struct Window *			Window;
	struct RA_Object *		WinObject;
	U32						WinActions;
	struct MsgPort *		WinCmdPort;
};

#define RAV_Window_Version	0

// --

#if defined(__USE_INLINE__)

  #define RACALL

#elif defined(__RA_CLASS__)

  #define RACALL  Self->

#else

  #define RACALL  IReactive->

#endif

// --

#define RACreate					RACALL RA_Object_CreateTags
#define RADelete					RACALL RA_Object_Delete
#define RAMethod					RACALL RA_Method_DoTags
#define RASuper(x,y,z)				RACALL RA_Method_DoSuperList( (x), (y), (PTR)(z) )
#define RANextTag					RACALL RA_Misc_NextTag
#define RAXGet						RACALL RA_Misc_XGet
#define RALoadFile					RACALL RA_Misc_LoadFile_32
#define RALoadFile64				RACALL RA_Misc_LoadFile_64

#define RASet						RACALL RA_Attr_Set
#define RASetSuper					RACALL RA_Attr_SetSuper
#define RASetParent					RACALL RA_Attr_SetParent
#define RAGet						RACALL RA_Attr_Get
#define RAGetSuper					RACALL RA_Attr_GetSuper
#define RAGetParent					RACALL RA_Attr_GetParent

#if 0


#define RAQuery					RACALL Class_QueryTags

#define RACreateImage				RACALL Image_Create
#define RADeleteImage				RACALL Image_Delete
#define RALoadImage				RACALL Image_Load

#define RACreate					RACALL Object_CreateTags
#define RADelete					RACALL Object_Delete
#define RARender					RACALL Object_Render

#define RAParent(x,y)				RACALL Method_DoParentList( x, (PTR) y )
#define RADoSuperNew				RACALL Method_DoSuperNew

#define RAPrintF					RACALL Memory_PrintF
#define RAAddPart					RACALL Memory_AddPart

#define RAAddHead					RACALL Node_AddHead
#define RAAddTail					RACALL Node_AddTail
#define RAAddAfter				RACALL Node_AddAfter
#define RARemHead					RACALL Node_RemHead
#define RARemNode					RACALL Node_RemNode
#define RARemTail					RACALL Node_RemTail
#define RAGetNext					RACALL Node_GetNext
#define RAGetPrev					RACALL Node_GetTail
#define RAGetHead					RACALL Node_GetHead
#define RAGetTail					RACALL Node_GetTail

#define RASubType					RACALL Misc_GetSubType

#define RAGetStyle				RACALL Style_GetTag

#endif

#endif
