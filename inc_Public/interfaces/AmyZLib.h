
/*
** SPDX-License-Identifier: Zlib
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
**
** Licensed under the zlib license. See the LICENSE file for details.
*/

#ifndef AMYLIB_INTERFACES_AMYZLIB_H
#define AMYLIB_INTERFACES_AMYZLIB_H

// --

#include "Amy_Defines.h"

// --

struct AmyZLibIFace
{
	struct InterfaceData Data;
	U32							AMY_FUNC (*Obtain)(struct AmyZLibIFace *Self);
	U32							AMY_FUNC (*Release)(struct AmyZLibIFace *Self);
	void						AMY_FUNC (*Expunge)(struct AmyZLibIFace *Self);
	struct Interface *			AMY_FUNC (*Clone)(struct AmyZLibIFace *Self);
};

// --

#endif
