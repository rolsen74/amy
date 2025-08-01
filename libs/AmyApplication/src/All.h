
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef __ALL_H__
#define __ALL_H__

// --

#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/AmyApplication.h>

// --

#define LIBNAME		"AmyApplication.library"
#define VERSION		1
#define REVISION	1
#define DATE		"1.1.2025"
#define VERS		"AmyApplication.library 1.1"
#define VSTRING		"AmyApplication.library 1.1 (1.8.2025)\r\n"
#define VERSTAG		"\0$VER: AmyApplication.library 1.1 (1.8.2025)"

// --

struct libBase
{
	struct Library		lib_Base;
	U16					lib_Pad;
	PTR					lib_SegList;
};

// --

void ROMFree( struct libBase *libBase );

U32 _manager_Obtain( struct LibraryManagerInterface *Self );
U32 _manager_Release( struct LibraryManagerInterface *Self );
PTR _manager_Open( struct LibraryManagerInterface *Self, U32 version );
PTR _manager_Close( struct LibraryManagerInterface *Self );
PTR _manager_Expunge( struct LibraryManagerInterface *Self );

U32 _main_Obtain( struct AmyApplicationIFace *Self );
U32 _main_Release( struct AmyApplicationIFace *Self );

// --

#endif
