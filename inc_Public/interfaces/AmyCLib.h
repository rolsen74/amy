
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Portions based on clib2 by Olaf Barthel (2002–2016)
** Target OS: AmigaOS
*/

#ifndef AMYLIB_INTERFACES_AMYCLIB_H
#define AMYLIB_INTERFACES_AMYCLIB_H

// --

#include <proto/exec.h>

#include "Amy_Defines.h"

#include <stddef.h>
#include <string.h>
#include <setjmp.h>

// --
struct RACLibStruct;

struct AmyCLibIFace
{
	struct InterfaceData Data;
	U32								AMYFUNC (*Obtain)(struct AmyCLibIFace *Self);
	U32								AMYFUNC (*Release)(struct AmyCLibIFace *Self);
	void							AMYFUNC (*Expunge)(struct AmyCLibIFace *Self);
	struct Interface *				AMYFUNC (*Clone)(struct AmyCLibIFace *Self);
	S32								AMYFUNC (*Priv_Startup_Init)(struct AmyCLibIFace *);
	S32								AMYFUNC (*Priv_Startup_Main)(struct AmyCLibIFace *, int main( int, char ** ) , STR arg_string, S32 arg_length, PTR wbmsg, struct RACLibStruct **pd );
	void							AMYFUNC	(*Priv_Startup_Free)(struct AmyCLibIFace *);
	void							AMYFUNC (*setjmp_longjmp)(struct AmyCLibIFace *, jmp_buf buf, int val);
	int								AMYFUNC (*setjmp_setjmp)(struct AmyCLibIFace *, jmp_buf buf);
	void *							AMYFUNC (*string_memset)(struct AmyCLibIFace *Self, void *s, int c, size_t n);
	void							AMYFUNC (*strings_bzero)(struct AmyCLibIFace *Self, void *mem, size_t len);
//	size_t							AMYFUNC (*string_strlen)(struct AmyCLibIFace *Self,const char *);
};

// --

#endif
