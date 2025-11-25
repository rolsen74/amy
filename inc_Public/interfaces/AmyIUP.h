
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
	U32							AMYFUNC (*Obtain)( struct AmyIUPIFace *Self );
	U32							AMYFUNC (*Release)( struct AmyIUPIFace *Self );
	void						AMYFUNC (*Expunge)( struct AmyIUPIFace *Self );
	struct Interface *			AMYFUNC (*Clone)( struct AmyIUPIFace *Self );
	/* IUP */
	int							AMYFUNC (*IupOpen)( struct AmyIUPIFace *Self, int *argc, char ***argv );
	void						AMYFUNC (*IupClose)( struct AmyIUPIFace *Self );
	int							AMYFUNC (*IupMainLoop)( struct AmyIUPIFace *Self );
	void						AMYFUNC (*IupSetGlobal)( struct AmyIUPIFace *Self, const char *name, const char *value );

};

// --

#endif
