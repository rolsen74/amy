
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_INTERFACES_AMYBLANKER_H
#define AMYLIB_INTERFACES_AMYBLANKER_H

// --

#include "Amy_Defines.h"

// --

struct AmyBlankerIFace
{
	struct InterfaceData Data;
	U32							AMY_FUNC (*Obtain)(struct AmyBlankerIFace *Self);
	U32							AMY_FUNC (*Release)(struct AmyBlankerIFace *Self);
	void						AMY_FUNC (*Expunge)(struct AmyBlankerIFace *Self);
	struct Interface *			AMY_FUNC (*Clone)(struct AmyBlankerIFace *Self);
};

// --

#endif
