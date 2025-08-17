
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYCLS_ALL_H
#define AMYCLS_ALL_H

// --

#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/AmyCLib.h>
#include <proto/Reactive.h>
//#include <proto/ReactivePriv.h>

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

struct AppClassData
{
	int	dummy;
};

typedef struct AppObjectData
{
//	struct List	Header;
	STR		AppBase;
	PTR		Args;
	U32		ID;
//	U32		IOErr;
//	U32		DataFields;
//	STR		String;
//	STR		Path;
//	STR		Pattern;
//	STR		UserPattern;
//	S32		Scanned;
//	PTR 	Context;
//	U32		Entries;



	// struct RA3Header			WindowList;
	// struct RA3_Process *		AppWindowProcess;

	// STRPTR					AppBase;
	// struct MsgPort *		    AppCmdPort;

	//  MsgPort *				WBCmdPort;

	// struct RA3_Object *		TrackingList;

	// struct SignalSemaphore	Semaphore;

	// APTR						Args;

	// APTR						CatalogArray;
	// uint32					CatalogArraySize;
	// CONST_STRPTR				CatalogLangName;
	// uint32					CatalogLangCode;

	// struct MsgPort *			UserCmdPort;
	// BOOL						UserCmdPortDel;

	// // -- Processs

	// struct Task *			Process;                // App Task Adr
	// struct MsgPort *			ProcessMsgPort;         // AppProcess Cmd MsgPort

	// struct MsgPort *			WBMsgPort;              // Shared AppWindow MsgPort

	// struct MsgPort *			WindowMsgPort;			// Shared IntuiMessage Port for Windows

	// BOOL						Dying;


} InstanceData;

// --

#endif
