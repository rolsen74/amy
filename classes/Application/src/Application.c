
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2014-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

#include "Class_Init.c"
#include "Class_Exit.c"

#include "RAM_New.c"
#include "RAM_Delete.c"
//#include "RAM_Set.c"
#include "RAM_Get.c"

#include "RAM__Dispatcher.c"

// --

struct ExecIFace *		IExec		= NULL;
struct Library *		DOSBase		= NULL;
struct DOSIFace *		IDOS		= NULL;
struct Library *		AmyCLibBase	= NULL;
struct AmyCLibIFace	*	IAmyCLib	= NULL;

// --

S32 _start( STR arg UNUSED, S32 arglen UNUSED, PTR SysBase UNUSED )
{
	return( RETURN_OK );
}

// --

static struct RA_Plugin USED App_Plugin =
{
/* RA_Plugin_MatchWord		*/ ID_RAPlugin,
/* RA_Plugin_MatchTag		*/ & App_Plugin,

/* RA_Plugin_LoadSeg		*/ 0,
/* RA_Plugin_NotifyReq		*/ NULL,
/* RA_Plugin_PathName		*/ NULL,

/* RA_Plugin_Data			*/ NULL,
/* RA_Plugin_ClsDataSize	*/ sizeof( struct AppClassData ),

/* RA_Plugin_Init			*/ Class_Init,
/* RA_Plugin_Exit			*/ Class_Exit,

/* RA_Plugin_Super			*/ RAC_Root,
/* RA_Plugin_PubName		*/ RAC_Application,
/* RA_Plugin_ObjDataSize	*/ sizeof( InstanceData ),
/* RA_Plugin_Dispatcher		*/ App_Dispatcher,
};

// --
