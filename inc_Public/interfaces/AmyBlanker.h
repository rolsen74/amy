
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef __INTERFACES_AMYBLANKER_H__
#define __INTERFACES_AMYBLANKER_H__

// --

#ifndef __AMY_STANDARD_H__
#include "Amy_Standard.h"
#endif

// --

struct AmyBlankerIFace
{
	struct InterfaceData Data;
	U32								APICALL (*Obtain)(struct AmyBlankerIFace *Self);
	U32								APICALL (*Release)(struct AmyBlankerIFace *Self);
	void							APICALL (*Expunge)(struct AmyBlankerIFace *Self);
	struct Interface *				APICALL (*Clone)(struct AmyBlankerIFace *Self);
};

// --

#endif
