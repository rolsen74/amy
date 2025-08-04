
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

struct AmyCLibIFace
{
	struct InterfaceData Data;
	U32								AMYFUNC (*Obtain)(struct AmyCLibIFace *Self);
	U32								AMYFUNC (*Release)(struct AmyCLibIFace *Self);
	void							AMYFUNC (*Expunge)(struct AmyCLibIFace *Self);
	struct Interface *				AMYFUNC (*Clone)(struct AmyCLibIFace *Self);
	S32								AMYFUNC (*Priv_Startup_Init)(struct AmyCLibIFace *);
	S32								AMYFUNC (*Priv_Startup_Main)(struct AmyCLibIFace *, int main( int, char ** ) , STR arg_string, S32 arg_length, PTR wbmsg, struct _AmyCLibPublic **pd );
	void							AMYFUNC	(*Priv_Startup_Free)(struct AmyCLibIFace *);
	PTR								AMYFUNC (*Priv_Mem_Alloc)(struct AmyCLibIFace *Self, U32 Size);
	U32								AMYFUNC (*Priv_Mem_Free)(struct AmyCLibIFace *Self, PTR mem);
	PTR								AMYFUNC (*Priv_Mem_Realloc)(struct AmyCLibIFace *Self, PTR oldmem, U32 Size);
	struct MemPoolHeader *			AMYFUNC (*Priv_Mem_CreatePool)(struct AmyCLibIFace *Self, U32 size);
	U32								AMYFUNC (*Priv_Mem_DeletePool)(struct AmyCLibIFace *Self, struct MemPoolHeader *handle);
	U32								AMYFUNC (*Priv_Mem_FlushPool)(struct AmyCLibIFace *Self, struct MemPoolHeader *handle);
	PTR								AMYFUNC (*Priv_Mem_AllocPooled)(struct AmyCLibIFace *Self, struct MemPoolHeader *handle, U32 Size);
	U32								AMYFUNC (*Priv_Mem_FreePooled)(struct AmyCLibIFace *Self, struct MemPoolHeader *handle, PTR mem);
	void							AMYFUNC (*setjmp_longjmp)(struct AmyCLibIFace *, jmp_buf buf, int val);
	int								AMYFUNC (*setjmp_setjmp)(struct AmyCLibIFace *, jmp_buf buf);
	PTR								AMYFUNC (*string_memcpy)(struct AmyCLibIFace *Self, void *dst, const void *src, size_t len);
	void *							AMYFUNC (*string_memset)(struct AmyCLibIFace *Self, void *s, int c, size_t n);
	void							AMYFUNC (*strings_bzero)(struct AmyCLibIFace *Self, void *mem, size_t len);
	void *							AMYFUNC (*stdlib_calloc)(struct AmyCLibIFace *Self, size_t num, size_t size);
	void *							AMYFUNC (*stdlib_malloc)(struct AmyCLibIFace *Self, size_t size);
	void *							AMYFUNC (*stdlib_realloc)(struct AmyCLibIFace *Self, void *mem, size_t size);
	void							AMYFUNC (*stdlib_free)(struct AmyCLibIFace *Self, void *mem);
	//	size_t							AMYFUNC (*string_strlen)(struct AmyCLibIFace *Self,const char *);
};

// --

#endif
