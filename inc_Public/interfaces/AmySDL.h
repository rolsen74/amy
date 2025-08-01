
/*
** SPDX-License-Identifier: LGPL-2.1-or-later
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef __INTERFACES_AMYSDL_H__
#define __INTERFACES_AMYSDL_H__

// --

#ifndef __AMY_STANDARD_H__
#include "Amy_Standard.h"
#endif

// --

struct AmySDLIFace
{
	struct InterfaceData Data;
	U32								APICALL (*Obtain)(struct AmySDLIFace *Self);
	U32								APICALL (*Release)(struct AmySDLIFace *Self);
	void							APICALL (*Expunge)(struct AmySDLIFace *Self);
	struct Interface *				APICALL (*Clone)(struct AmySDLIFace *Self);
};

// --

#endif
