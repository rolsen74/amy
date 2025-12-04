
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_INTERFACES_AMYAPPLICATION_H
#define AMYLIB_INTERFACES_AMYAPPLICATION_H

// --

#include "Amy_Defines.h"

// --

struct AmyApplicationIFace
{
	struct InterfaceData Data;
	U32							AMY_FUNC (*Obtain)(struct AmyApplicationIFace *Self);
	U32							AMY_FUNC (*Release)(struct AmyApplicationIFace *Self);
	void						AMY_FUNC (*Expunge)(struct AmyApplicationIFace *Self);
	struct Interface *			AMY_FUNC (*Clone)(struct AmyApplicationIFace *Self);
};

// --

#endif
