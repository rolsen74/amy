
/*
** SPDX-License-Identifier: Zlib
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
**
** Licensed under the zlib license. See the LICENSE file for details.
*/

#ifndef __INTERFACES_AMYZLIB_H__
#define __INTERFACES_AMYZLIB_H__

// --

#ifndef __AMY_STANDARD_H__
#include "Amy_Standard.h"
#endif

// --

struct AmyZLibIFace
{
	struct InterfaceData Data;
	U32								APICALL (*Obtain)(struct AmyZLibIFace *Self);
	U32								APICALL (*Release)(struct AmyZLibIFace *Self);
	void							APICALL (*Expunge)(struct AmyZLibIFace *Self);
	struct Interface *				APICALL (*Clone)(struct AmyZLibIFace *Self);
};

// --

#endif
