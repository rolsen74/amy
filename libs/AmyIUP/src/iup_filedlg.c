
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"
#include "inc/iup_box.h"

// --

#if 0

/** \file
 * \brief amy_IupFileDlg pre-defined dialog
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

IUP_API Ihandle *amy_IupFileDlg( struct libData *data )
{
	IExec->DebugPrintF( "amy_IupFileDlg\n" );

	return amy_IupCreate( data, "filedlg" );
}

Iclass *iupFileDlgNewClass( struct libData *data )
{
	IExec->DebugPrintF( "iupFileDlgNewClass\n" );

	Iclass *ic = iupClassNew( data, iupRegisterFindClass( data, "dialog" ));

  ic->name = "filedlg";
  ic->cons = "FileDlg";
  ic->nativetype = IUP_TYPEDIALOG;
  ic->is_interactive = 1;

  iupClassRegisterCallback( data, ic, "FILE_CB", "ss" );

  ic->New = iupFileDlgNewClass;

  /* reset not used native dialog methods */
  ic->parent->LayoutUpdate = NULL;
  ic->parent->SetChildrenPosition = NULL;
  ic->parent->Map = NULL;
  ic->parent->UnMap = NULL;

  iupdrvFileDlgInitClass( data, ic );

  /* only the default value */
  iupClassRegisterAttribute( data, ic, "NOCHANGEDIR", NULL, NULL, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DIALOGTYPE", NULL, NULL, IUPAF_SAMEASSYSTEM, "OPEN", IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "PREVIEWDC", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT|IUPAF_READONLY|IUPAF_NO_STRING );
  iupClassRegisterAttribute( data, ic, "PREVIEWWIDTH", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT|IUPAF_READONLY );
  iupClassRegisterAttribute( data, ic, "PREVIEWHEIGHT", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT|IUPAF_READONLY );

  iupClassRegisterAttribute( data, ic, "ALLOWNEW", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DIRECTORY", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "FILE", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "FILTER", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "NOOVERWRITEPROMPT", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "SHOWHIDDEN", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "SHOWPREVIEW", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MULTIVALUEPATH", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "EXTDEFAULT", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MULTIPLEFILES", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "FILEEXIST", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT|IUPAF_READONLY );
  iupClassRegisterAttribute( data, ic, "STATUS", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT|IUPAF_READONLY );
  iupClassRegisterAttribute( data, ic, "VALUE", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT|IUPAF_READONLY );

  return ic;
}
