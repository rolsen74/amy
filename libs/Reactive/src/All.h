
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_ALL_H
#define AMYLIB_ALL_H

// --

#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/icon.h>
#include <proto/AmyCLib.h>
#include <proto/Reactive.h>
#include <proto/ReactivePriv.h>

#include <workbench/startup.h>

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

// --

#define LIBNAME				"Reactive.library"
#define VERSION				1
#define REVISION			1
#define DATE				"1.1.2025"
#define VERS				"Reactive.library 1.1"
#define VSTRING				"Reactive.library 1.1 (1.8.2025)\r\n"
#define VERSTAG				"\0$VER: Reactive.library 1.1 (1.8.2025)"

// --

enum
{
	ArgType_NotSet,
	ArgType_Number,
	ArgType_Switch,
	ArgType_Key,
	ArgType_Multi,
};

struct ArgStruct
{
	U32		as_ID;
	STR *	as_Strings;
	U32		as_StringCount;
	STR *	as_Keys;
	U32		as_KeyCount;
};

#define ARG_ID		0x9283865f

// --

struct ClassType
{
	U32		Type;
	STR		Name;
	STR		Pattern;
	STR		String;
};

/***[ Root Class ]**********************************************************/

struct RootClass_Data
{
	struct RA_PrivObject		rcd_Object;
	struct RA_PrivObject *		rcd_AppObject;
	struct RA_PrivObject *		rcd_WinObject;
	struct SignalSemaphore		rcd_Semaphore;
	struct SignalSemaphore *	rcd_SemaphoreAdr;
	U32							rcd_UserData;
	STR							rcd_ID;
	U32							rcd_IDNr;
//--	CONST_STRPTR				rcd_StyleName;
	struct List 				rcd_NotifyList;
	U32							rcd_Flags;
};

#define ROOTCLASSF_NoSemaphore	0x00000001

/***[ Class/Object Types ]**************************************************/

// Not all Objects or Classes are ment to have a type,
// only some selected onces has it, think of them as base classes.

enum
{
	// If you ask for a type on something that is not a Class or Object.
	RA_Type_Error = -1,

	// Class/Object do not have a type set.
	RA_Type_Unknown = 0,
//	RA_Type_All = 0,

	// v1.5

	RA_Type_Application,
	// RA_Type_Gadget,
	// RA_Type_Hash,
	// RA_Type_Stream,
	// RA_Type_Style,
	// RA_Type_Window,

	// // v1.x

	// RA_Type_Timer,

	// // v1.8

	// RA_Type_Compress,
	// RA_Type_Crypto,
	// RA_Type_xxxxxx,	 // Not used anymore, was Socket type

	// // v1.13
	
	// RA_Type_Date,
};

// --

struct libBase
{
	struct Library				lib_Base;
	U16							lib_Pad;
	PTR							lib_SegList;

	// Class

	struct RA_PrivClass *		lib_RootClass;
	struct List					lib_PublicClassHeader;
	struct List					lib_PrivateClassHeader;
	struct SignalSemaphore		lib_ClassSemaphore;

};

// --

struct libData
{
	int	dummy;
};

// --

U32 RootDispatcher(
	struct ReactivePrivIFace * Self,
	struct RA_PrivClass		* cl,
	struct RA_PrivObject	* obj,
	struct RA_Method		* msg,
	struct libBase			* libBase,
	struct RootClass_Data	* rcd );

void ROMFree( struct libBase *libBase );

U32 AMYFUNC _manager_Obtain( struct LibraryManagerInterface *Self );
U32 AMYFUNC _manager_Release( struct LibraryManagerInterface *Self );
PTR AMYFUNC _manager_Open( struct LibraryManagerInterface *Self, U32 version );
PTR AMYFUNC _manager_Close( struct LibraryManagerInterface *Self );
PTR AMYFUNC _manager_Expunge( struct LibraryManagerInterface *Self );

U32 AMYFUNC _Main_Expunge( struct ReactivePrivIFace *Self );

// --

#endif
