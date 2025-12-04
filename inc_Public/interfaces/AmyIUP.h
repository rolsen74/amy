
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

#ifndef AMYLIB_INTERFACES_AMYIUP_H
#define AMYLIB_INTERFACES_AMYIUP_H

// --

#include "Amy_Defines.h"

// --

struct AmyIUPIFace
{
	struct InterfaceData Data;
	U32							AMY_FUNC (*Obtain)( struct AmyIUPIFace *Self );
	U32							AMY_FUNC (*Release)( struct AmyIUPIFace *Self );
	void						AMY_FUNC (*Expunge)( struct AmyIUPIFace *Self );
	struct Interface *			AMY_FUNC (*Clone)( struct AmyIUPIFace *Self );
	/* IUP */
	int							AMY_FUNC (*IupOpen)( struct AmyIUPIFace *Self, int *argc, char ***argv );
	void						AMY_FUNC (*IupClose)( struct AmyIUPIFace *Self );
	int							AMY_FUNC (*IupMainLoop)( struct AmyIUPIFace *Self );
	void						AMY_FUNC (*IupSetGlobal)( struct AmyIUPIFace *Self, const char *name, const char *value );

};

// --

#endif
