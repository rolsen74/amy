
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
 * \brief User Element.
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdio.h>
#include <stdlib.h>

#include "iup.h"

#include "iup_object.h"
#include "iup_stdcontrols.h"

#endif

static int iUserSetClearAttributesAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  (void)value;
  iupTableClear( data, ih->attrib );
  return 0;
}

IUP_API Ihandle *amy_IupUser( struct libData *data )
{
  return amy_IupCreate( data, "user" );
}

Iclass *iupUserNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, NULL );

  ic->name = "user";
  ic->format = NULL;  /* no parameters */
  ic->nativetype = IUP_TYPEOTHER;
  ic->childtype = IUP_CHILDMANY; /* can have children */
  ic->is_interactive = 0;

  ic->New = iupUserNewClass;

  iupBaseRegisterBaseCallbacks( data, ic );

  iupClassRegisterAttribute( data, ic, "CLEARATTRIBUTES", NULL, iUserSetClearAttributesAttrib, NULL, NULL, IUPAF_WRITEONLY | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT);

  return ic;
}
