
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef __INTERFACES_AMYSYSLOG_H__
#define __INTERFACES_AMYSYSLOG_H__

// --

#ifndef __AMY_STANDARD_H__
#include "Amy_Standard.h"
#endif

// --

struct AmySysLogIFace
{
	struct InterfaceData Data;
	U32								APICALL (*Obtain)(struct AmySysLogIFace *Self);
	U32								APICALL (*Release)(struct AmySysLogIFace *Self);
	void							APICALL (*Expunge)(struct AmySysLogIFace *Self);
	struct Interface *				APICALL (*Clone)(struct AmySysLogIFace *Self);
};

// --

#endif
