
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

struct DirClassData
{
	int	dummy;
};

typedef struct DirObjectData
{
	struct List	Header;
	U32		ID;
	U32		IOErr;
	U32		DataFields;
	STR		String;
	STR		Path;
	STR		Pattern;
	STR		UserPattern;
	S32		Scanned;
	PTR 	Context;
	U32		Entries;

} InstanceData;

// --

#endif
