
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_ALL_H
#define AMYLIB_ALL_H

// --

#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/AmySysLog.h>

// --

#define LIBNAME		"AmySysLog.library"
#define VERSION		1
#define REVISION	1
#define DATE		"1.1.2025"
#define VERS		"AmySysLog.library 1.1"
#define VSTRING		"AmySysLog.library 1.1 (1.8.2025)\r\n"
#define VERSTAG		"\0$VER: AmySysLog.library 1.1 (1.8.2025)"

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

U32 _Main_Obtain( struct AmySysLogIFace *Self );
U32 _Main_Release( struct AmySysLogIFace *Self );

// --

#endif
