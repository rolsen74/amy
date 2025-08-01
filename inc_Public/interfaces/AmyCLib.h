
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Portions based on clib2 by Olaf Barthel (2002–2016)
** Target OS: AmigaOS
*/

#ifndef __INTERFACES_AMYCLIB_H__
#define __INTERFACES_AMYCLIB_H__

// --

#ifndef __AMY_STANDARD_H__
#include "Amy_Standard.h"
#endif

// --

struct AmyCLibIFace
{
	struct InterfaceData Data;
	U32								APICALL (*Obtain)(struct AmyCLibIFace *Self);
	U32								APICALL (*Release)(struct AmyCLibIFace *Self);
	void							APICALL (*Expunge)(struct AmyCLibIFace *Self);
	struct Interface *				APICALL (*Clone)(struct AmyCLibIFace *Self);
};

// --

#endif
