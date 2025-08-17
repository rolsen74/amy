
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#ifndef REACTIVE_CLS_ROOT_H
#define REACTIVE_CLS_ROOT_H

/****************************************************************************/

#define RAC_Root					"RootClass.ra"

// #define RAA_ID						( RAB_Root + 0 )	// [I.G.] STR
// #define RAA_UserData				( RAB_Root + 1 )	// [ISG.] PTR
#define RAA_Version					( RAB_Root + 2 )	// [..G.] U32
#define RAA_Revision				( RAB_Root + 3 )	// [..G.] U32
// #define RAA_Style					( RAB_Root + 4 )	// [I.G.] struct RA_Style *
// #define RAA_StyleName				( RAB_Root + 5 )	// [I...] STR
// #define RAA_ErrorCode				  ( RAB_Root + 6 )	  // [I...] U32 *
// #define RAA_Parent					( RAB_Root + 7 )	// [I.G.] struct RA_Object *
// #define RAA_IDNr					( RAB_Root + 8 )	// [I...] U32
// #define RAA_SemaphoreAdr			( RAB_Root + 9 )    // ]..G.] struct SignalSemaphore *
// #define RAA_SemaphoreLock			( RAB_Root + 10 )   // [ISG.] S32
// #define RAA_Application				( RAB_Root + 11 )	// [..G.] struct RA_Object *

// Place those two some where nice... maybe a rename
// #define RAV_Notify_EveryTime		0x873216ae
// #define RAV_Notify_TriggerValue		0x873216ae
// #define RAA_NOTIFY_CHECK(x)			{ if ( x != msg->AttrValue ) { RACALL Method_DoSuperTags( cl, obj, RAM_CheckNotify, msg->AttrID, msg->AttrValue ); x = msg->AttrValue; }}

/***[ New Method ]**********************************************************/

#define RAM_New						( RAB_Root + 1000 )

struct  RAP_New
{
	U32					MethodID;
	struct TagItem *	AttrList;
};

/***[ Delete Method ]*******************************************************/

#define RAM_Delete					( RAB_Root + 1001 )

struct  RAP_Delete
{
	U32					MethodID;
};

/***[ Set Method ]**********************************************************/

#define RAM_Set						( RAB_Root + 1002 )

struct  RAP_Set
{
	U32					MethodID;
	U32					AttrID;
 	U32 				AttrValue;
};

/***[ Get Method ]**********************************************************/

#define RAM_Get						( RAB_Root + 1003 )

struct  RAP_Get
{
	U32					MethodID;
	U32					AttrID;
	PTR					Storage;
};

/***[ Add Member ]**********************************************************/

// #define RAM_AddMember				( RAB_Root + 1004 )

// struct  RAP_AddMember
// {
// 	U32					MethodID;
// 	PTR				Node;
// };

// /***[ Remove Member ]*******************************************************/

// #define RAM_RemMember				( RAB_Root + 1005 )

// struct  RAP_RemMember
// {
// 	U32					MethodID;
// 	PTR					Node;
// };

// /***[ Load Prefs ]**********************************************************/

// #define RAM_LoadPrefs				( RAB_Root + 1006 )

// struct  RAP_LoadPrefs
// {
// 	U32					MethodID;
// 	PTR					Dict;
// };

// /***[ Save Prefs ]**********************************************************/

// #define RAM_SavePrefs				( RAB_Root + 1007 )

// struct  RAP_SavePrefs
// {
// 	U32					MethodID;
// 	PTR					Dict;
// };

// /***[ Locate Object ]*******************************************************/

// #define RAM_LocateObject			( RAB_Root + 1008 )

// struct  RAP_LocateObject
// {
// 	U32					MethodID;
// 	STR					ID;
// };

// /****************************************************************************/

// #define RAM_AddNotify				( RAB_Root + 1009 )

// struct  RAP_AddNotify
// {
// 	U32 				MethodID;
// 	U32					AttrID;
// 	U32					AttrValue;
// 	struct RA_Object *	DestObject;
// 	U32					Arguments;
// 	U32					Data[];
// };

// /****************************************************************************/

// #define RAM_RemNotify				( RAB_Root + 1010 )

// struct  RAP_RemNotify
// {
// 	U32 				MethodID;
// };

// /****************************************************************************/

// #define RAM_CheckNotify				( RAB_Root + 1011 )

// struct  RAP_CheckNotify
// {
// 	U32 				MethodID;
// 	U32					AttrID;
// 	U32					AttrValue;
// };

// /****************************************************************************/

// #define RAM_Notify_Set				( RAB_Root + 1012 )

// struct  RAP_Notify_Set
// {
// 	U32 				MethodID;
// 	U32					AttrID;
// 	U32					AttrValue;
// };

// /****************************************************************************/

// #define RAM_FindIDNr				( RAB_Root + 1013 )

// struct  RAP_FindIDNr
// {
// 	U32 				MethodID;
// 	U32					Pass;
// 	U32					IDNr;
// 	PTR					Object;
// };

// #define RAV_FindIDNr_Application	-1
// #define RAV_FindIDNr_Window			-2

// /****************************************************************************/

// #define RAM_Notify_Signal			( RAB_Root + 1014 )

// struct  RAP_Notify_Signal
// {
// 	U32 				MethodID;
// 	struct Task *		Task;
// 	U32					Signals;
// };

// /****************************************************************************/

// #define RAM_Notify_Function			( RAB_Root + 1015 )

// struct  RAP_Notify_Function
// {
// 	U32 				MethodID;
// 	void 				(*Function)(struct RA_Object *,PTR);
// 	PTR					Data;
// };

// /****************************************************************************/

// #define RAM_Send_Command			( RAB_Root + 1016 )

// struct  RAP_Send_Command
// {
// 	U32 				MethodID;
// 	U32					Recipient;
// 	U32					Command;
// };

// enum // Recipient
// {
// 	RCMD_Application,
// 	RCMD_Window,
// };

// /****************************************************************************/

// #define RAM_SetSemaphore			( RAB_Root + 1017 )

// struct  RAP_SetSemaphore
// {
// 	U32 				MethodID;
// 	struct RA_Object *	Object;
// };

// /****************************************************************************/

// #define RAM_Notify_SetParent		( RAB_Root + 1018 )

// struct  RAP_Notify_SetParent
// {
// 	U32 				MethodID;
// 	U32					AttrID;
// 	U32					AttrValue;
// };

// /****************************************************************************/

// #define RAM_SetApplication			( RAB_Root + 1019 )

// struct  RAP_SetApplication
// {
// 	U32 				MethodID;
// 	struct RA_Object *	Object;
// };

// /****************************************************************************/

// #define RAM_Notify_UserSet			( RAB_Root + 1020 )

// struct  RAP_Notify_UserSet
// {
// 	U32 				MethodID;
// 	U32					AttrID;
// 	U32					AttrValue;
// };

// /****************************************************************************/

// #define RAM_Notify_CmdID			( RAB_Root + 1021 )

// struct  RAP_Notify_CmdID
// {
// 	U32 				MethodID;
// 	U32					CmdID;
// };

// /****************************************************************************/

// #define RAM_SetWindow				( RAB_Root + 1022 )

// struct  RAP_SetWindow
// {
// 	U32 				MethodID;
// 	struct RA_Object *	Object;
// };

/****************************************************************************/

#endif
