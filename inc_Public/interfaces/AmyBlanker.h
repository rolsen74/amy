
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
	U32							AMYFUNC (*Obtain)(struct AmyBlankerIFace *Self);
	U32							AMYFUNC (*Release)(struct AmyBlankerIFace *Self);
	void						AMYFUNC (*Expunge)(struct AmyBlankerIFace *Self);
	struct Interface *			AMYFUNC (*Clone)(struct AmyBlankerIFace *Self);
};

// --

#endif
