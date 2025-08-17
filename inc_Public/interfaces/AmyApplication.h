
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
	U32							AMYFUNC (*Obtain)(struct AmyApplicationIFace *Self);
	U32							AMYFUNC (*Release)(struct AmyApplicationIFace *Self);
	void						AMYFUNC (*Expunge)(struct AmyApplicationIFace *Self);
	struct Interface *			AMYFUNC (*Clone)(struct AmyApplicationIFace *Self);
};

// --

#endif
