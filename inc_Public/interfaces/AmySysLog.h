
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_INTERFACES_AMYSYSLOG_H
#define AMYLIB_INTERFACES_AMYSYSLOG_H

// --

#include "Amy_Defines.h"

// --

struct AmySysLogIFace
{
	struct InterfaceData Data;
	U32							AMYFUNC (*Obtain)(struct AmySysLogIFace *Self);
	U32							AMYFUNC (*Release)(struct AmySysLogIFace *Self);
	void						AMYFUNC (*Expunge)(struct AmySysLogIFace *Self);
	struct Interface *			AMYFUNC (*Clone)(struct AmySysLogIFace *Self);
};

// --

#endif
