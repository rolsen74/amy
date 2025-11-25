
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
 * \brief Space Control.
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdio.h>
#include <stdlib.h>

#include "iup.h"
#include "iupcbs.h"

#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_drv.h"
#include "iup_drvfont.h"
#include "iup_stdcontrols.h"
#include "iup_layout.h"

#endif

IUP_API Ihandle *amy_IupSpace( struct libData *data )
{
  return amy_IupCreate( data, "space" );
}

Iclass *iupSpaceNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, NULL );

  ic->name = "space";
  ic->format = NULL;  /* no parameters */
  ic->nativetype = IUP_TYPEVOID;
  ic->childtype = IUP_CHILDNONE;
  ic->is_interactive = 0;

  /* Class functions */
  ic->New = iupSpaceNewClass;
  ic->Map = iupBaseTypeVoidMapMethod;

  /* Base Callbacks */
  iupBaseRegisterBaseCallbacks( data, ic );

  /* Common */
  iupBaseRegisterCommonAttrib( data, ic );

  return ic;
}
