
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

// --

struct AmyCLibIFace
{
	struct InterfaceData Data;
	U32								AMYFUNC (*Obtain)(struct AmyCLibIFace *Self);
	U32								AMYFUNC (*Release)(struct AmyCLibIFace *Self);
	void							AMYFUNC (*Expunge)(struct AmyCLibIFace *Self);
	struct Interface *				AMYFUNC (*Clone)(struct AmyCLibIFace *Self);
	size_t							AMYFUNC (*string_strlen)(struct AmyCLibIFace *Self,const char *);
};

// --

#endif
