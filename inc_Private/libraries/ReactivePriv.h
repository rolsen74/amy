
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_LIBRARIES_REACTIVEPRIV_H
#define AMYLIB_LIBRARIES_REACTIVEPRIV_H

// --

#include <proto/exec.h>
#include "Amy_Defines.h"
#include "Reactive/ra_Reactive.h"
#include "Reactive/ra_Plugin.h"

// --

/***[ IDs ]****************************************************************/

#define ID_RAClass			(('C'<<24)+('l'<<16)+('s'<<8)+0)
#define ID_RAObject			(('O'<<24)+('b'<<16)+('j'<<8)+0)
//#define ID_RAStyle		(('S'<<24)+('t'<<16)+('y'<<8)+0)
//#define ID_RAStyleTag		(('S'<<24)+('t'<<16)+('g'<<8)+0)
//#define ID_RAProcess		(('P'<<24)+('r'<<16)+('c'<<8)+0)
//#define ID_RAImage		(('I'<<24)+('m'<<16)+('g'<<8)+0)
//#define ID_RAMemory		(('M'<<24)+('e'<<16)+('m'<<8)+0)
//#define ID_RAMessage		(('M'<<24)+('s'<<16)+('g'<<8)+0)
//#define ID_RAEnvirement	(('E'<<24)+('n'<<16)+('v'<<8)+0)

/***[ Real Reactive Class ]*************************************************/

// Note: First 4 entries much not be moved

struct RA_PrivClass
{
	// Node Pointers
	struct RA_PrivClass *	RA_Class_Next;
	struct RA_PrivClass *	RA_Class_Prev;

	// Class Type
	U32						RA_Class_Type;

	// Class ID, ID is set to ID_RAClass
	U32						RA_Class_ID;

	// ---

	// Pointer to SuperClass or NULL if its RootClass
	struct RA_PrivClass *	RA_Class_Super;

	// Plugin Pointer if Class was loaded from disk or NULL
	struct RA_Plugin *		RA_Class_Plugin;

	// Class Flags see below
	U32						RA_Class_Flags;

	// Data is either from Plugin or user's	SetData call (can be NULL)
	PTR						RA_Class_Data;

	// Locks to prevent the class to be expunged
	S32						RA_Class_Count_Objects;
	S32						RA_Class_Count_SubClasses;
	S32						RA_Class_Count_FindLocks;

	// --

	U32					( *	RA_Class_Dispatcher ) ( struct RA_Class *, struct RA_Object *, struct RA_Method *, void *, void *, struct ReactiveIFace * );

	U32						RA_Class_InstSize;
	U32						RA_Class_InstTotalSize;
	U32						RA_Class_InstOffset;

	STR						RA_Class_Name;
	U32						RA_Class_NameLength;

};

#define RA_CLASSB_DelayedExpunge	0
#define RA_CLASSB_BaseClass			1

#define RA_CLASSF_DelayedExpunge	( 1UL << RA_CLASSB_DelayedExpunge )
#define RA_CLASSF_BaseClass			( 1UL << RA_CLASSB_BaseClass )

/***[ Real Reactive Object ]************************************************/

// Note: First 4 entries much not be moved

struct RA_PrivObject
{
	// Node pointers
	struct RA_PrivObject *	RA_Object_Next;
	struct RA_PrivObject *	RA_Object_Prev;

	// Object Type
	U32						RA_Object_Type;

	// Object ID, ID is set to ID_RAObject
	U32						RA_Object_ID;

	// ---

	// Pointer to Object's Class
	struct RA_PrivClass *	RA_Object_Class;

	// Parent Object
	struct RA_PrivObject *	RA_Object_Parent;

	// Pointer to Object's Style
	struct RA_PrivStyle *	RA_Object_Style;
};


// --
#if 0

// hmm we have RACreate and so on from Public

#define RACreate					RA_Object_CreateTags
#define RADelete					RA_Object_Delete


#define RASet						RACALL Attr_Set
#define RASetSuper				RACALL Attr_SetSuper
#define RASetParent				RACALL Attr_SetParent
#define RAGet						RACALL Attr_Get
#define RAGetSuper				RACALL Attr_GetSuper
#define RAGetParent				RACALL Attr_GetParent

#define RAQuery					RACALL Class_QueryTags

#define RACreateImage				RACALL Image_Create
#define RADeleteImage				RACALL Image_Delete
#define RALoadImage				RACALL Image_Load

#define RACreate					RACALL Object_CreateTags
#define RADelete					RACALL Object_Delete
#define RARender					RACALL Object_Render

#define RAMethod					RACALL Method_DoTags
#define RASuper(x,y,z)			RACALL Method_DoSuperList( x, y, (PTR) z )
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

#define RANextTag        			RACALL Misc_NextTag
#define RASubType					RACALL Misc_GetSubType

#define RAGetStyle				RACALL Style_GetTag

#endif

#endif
