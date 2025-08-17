
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#ifndef REACTIVE_CLS_APPLICATION_H
#define REACTIVE_CLS_APPLICATION_H

/****************************************************************************/

#define RAC_Application						"Application.ra"

#define RAA_APP_Base						( RAB_Application + 0 )		// [I.G.] CONST_STRPTR
//--#define RAA_APP_CommandPort				( RAB_Application + 1 )		// [ISG.] struct MsgPort *
//--#define RAA_APP_Screen					( RAB_Application + 2 )		// [I...] RA3_Object *
//--#define RAA_APP_Window					( RAB_Application + 3 )		// [I...] RA3_Object *
//--#define RAA_APP_WindowPort				( RAB_Application + 4 )	    // [..G.] struct MsgPort *
//--#define RAA_APP_TrackObject				( RAB_Application + 5 )		// [I...] RA3_Object *

#define RAA_APP_Argument_Count				( RAB_Application + 6 )		// [I...] int
#define RAA_APP_Argument_Values				( RAB_Application + 7 )		// [I...] char **
#define RAA_APP_Argument_List				( RAB_Application + 8 )		// [I...] struct RAArguments *

//--#define RAA_APP_GameMode				( RAB_Application + 9 )		// [ISG.] BOOL
//--#define RAA_APP_WorkbenchPort			( RAB_Application + 10 )	// [..G.] struct MsgPort *
//--
//--#define RAA_APP_Catalog_Language		( RAB_Application + 11 )	// [I...] CONST_STRPTR ( Default to "english" )
//--#define RAA_APP_Catalog_CodeSet			( RAB_Application + 12 )	// [I...] uint32 ( Default to 4 ISO-8859-1 )
//--#define RAA_APP_Catalog_Array			( RAB_Application + 13 )	// [I...] struct CatCompArrayType *
//--#define RAA_APP_Catalog_ArraySize		( RAB_Application + 14 )	// [I...] uint32

#define RAA_APP_ProcessCmdMsgPort			( RAB_Application + 15 )	// [..G.] struct MsgPort *

//--/****************************************************************************/
//--
//--#define RAM_Application_DoFunction			( RAB_Application + 1000 )
//--
//--struct  RAP_Application_DoFunction
//--{
//--	uint32				MethodID;
//--	struct RA3_Object *	Object;
//--	APTR				Function;
//--	APTR				Data;
//--};
//--
//--/****************************************************************************/
//--
//--#define RAM_Application_DoKey				( RAB_Application + 1001 )
//--
//--struct  RAP_Application_DoKey
//--{
//--	uint32				MethodID;
//--	struct RA3_Object *	Object;
//--	struct Hook *		Hook;
//--	uint32				Code;
//--	uint32				Qualifier;
//--	uint32				Seconds;
//--	uint32				Micros;
//--};
//--
//--/****************************************************************************/
//--
//--#define RAM_Application_DoSet				( RAB_Application + 1002 )
//--
//--struct  RAP_Application_DoSet
//--{
//--	uint32				MethodID;
//--	struct RA3_Object *	Object;
//--	uint32				Tag;
//--	uint32				Value;
//--};
//--
//--/****************************************************************************/
//--
//--#define RAM_Application_DoRefresh			( RAB_Application + 1003 )
//--
//--struct  RAP_Application_DoRefresh
//--{
//--	uint32				MethodID;
//--	struct RA3_Object *	Object;
//--};
//--
//--/****************************************************************************/
//--
//--#define RAM_Application_DoMethod			( RAB_Application + 1004 )
//--
//--struct  RAP_Application_DoMethod
//--{
//--	uint32				MethodID;
//--	struct RA3_Object *	Object;
//--	uint32				ID;
//--	APTR				Data;
//--};
//--
//--/****************************************************************************/
//--
//--#define RAM_Application_DoAppWindow			( RAB_Application + 1005 )
//--
//--struct  RAP_Application_DoAppWindow
//--{
//--	uint32				MethodID;
//--	struct RA3_Object *	WindowObj;
//--	APTR				Function;
//--	struct AppMessage *	AppMessage;
//--};
//--
//--/****************************************************************************/
//--
//--#define RAM_Application_DoCmdID				( RAB_Application + 1006 )
//--
//--struct  RAP_Application_DoCmdID
//--{
//--	uint32				MethodID;
//--	uint32				CmdID;
//--};
//--
//--/****************************************************************************/
//--
//--#define RAM_Application_DoDraw				( RAB_Application + 1007 )
//--
//--struct  RAP_Application_DoDraw
//--{
//--	uint32				MethodID;
//--	struct RA3_Object *	Gadget;
//--	int32				XPos;
//--	int32				YPos;
//--	int32				Width;
//--	int32				Height;
//--};

/****************************************************************************/

#endif
