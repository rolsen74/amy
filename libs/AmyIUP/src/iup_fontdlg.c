
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"

// --

#if 0

/** \file
 * \brief amy_IupFontDlg pre-defined dialog
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdarg.h>
#include <limits.h>

#include "iup.h"

#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_stdcontrols.h"
#include "iup_register.h"

#endif

IUP_API Ihandle *amy_IupFontDlg( struct libData *data )
{
	return amy_IupCreate( data, "fontdlg" );
}

Iclass *iupFontDlgNewClass( struct libData *data )
{
	Iclass *ic = iupClassNew( data, iupRegisterFindClass( data, "dialog" ));

	ic->name = "fontdlg";
	ic->cons = "FontDlg";
	ic->nativetype = IUP_TYPEDIALOG;
	ic->is_interactive = 1;

	ic->New = iupFontDlgNewClass;

	if (!iupStrEqualNoCase( amy_IupGetGlobal( data, "DRIVER" ), "Motif" ))
	{
		/* reset not used native dialog methods */
		ic->parent->LayoutUpdate = NULL;
		ic->parent->SetChildrenPosition = NULL;
		ic->parent->Map = NULL;
		ic->parent->UnMap = NULL;
	}

	/* amy_IupFontDialog only */
	iupClassRegisterAttribute( data, ic, "STATUS", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT|IUPAF_READONLY);
	iupClassRegisterAttribute( data, ic, "VALUE", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT);

	iupdrvFontDlgInitClass( data, ic );

	return ic;
}
