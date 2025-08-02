
/*
** SPDX-License-Identifier: LGPL-2.1-or-later
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_INTERFACES_AMYSDL_H
#define AMYLIB_INTERFACES_AMYSDL_H

// --

#include "Amy_Defines.h"

// --

struct AmySDLIFace
{
	struct InterfaceData Data;
	U32								AMYFUNC (*Obtain)(struct AmySDLIFace *Self);
	U32								AMYFUNC (*Release)(struct AmySDLIFace *Self);
	void							AMYFUNC (*Expunge)(struct AmySDLIFace *Self);
	struct Interface *				AMYFUNC (*Clone)(struct AmySDLIFace *Self);
};

// --

#endif
