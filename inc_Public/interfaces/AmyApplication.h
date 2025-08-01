
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef __INTERFACES_AMYAPPLICATION_H__
#define __INTERFACES_AMYAPPLICATION_H__

// --

#ifndef __AMY_STANDARD_H__
#include "Amy_Standard.h"
#endif

// --

struct AmyApplicationIFace
{
	struct InterfaceData Data;
	U32								APICALL (*Obtain)(struct AmyApplicationIFace *Self);
	U32								APICALL (*Release)(struct AmyApplicationIFace *Self);
	void							APICALL (*Expunge)(struct AmyApplicationIFace *Self);
	struct Interface *				APICALL (*Clone)(struct AmyApplicationIFace *Self);
};

// --

#endif
