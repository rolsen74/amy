
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
 * \brief Timer Control.
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdio.h>
#include <stdlib.h>

#include "iup.h"
#include "iupcbs.h"

#include "iup_object.h"
#include "iup_str.h"
#include "iup_stdcontrols.h"
#include "iup_timer.h"
#include "iup_attrib.h"

#endif

long long iupTimerGetLongLong( struct libData *data, Ihandle *ih, const char *name )
{
  long long i = 0;
  char *value = iupAttribGetStr( data, ih, name );
  if (value)
  {
    if (sscanf(value, "%lld", &i) != 1)
      return 0;
  }
  return i;
}

static int iTimerSetRunAttrib( struct libData *data, Ihandle *ih, const char *value )
{
  if (iupStrBoolean(value))
    iupdrvTimerRun( data, ih );
  else
    iupdrvTimerStop( data, ih );

  return 0;
}

static char *iTimerGetRunAttrib( struct libData *data, Ihandle *ih )
{
  return iupStrReturnBoolean( ih->serial > 0 );
}

static char *iTimerGetWidAttrib( struct libData *data, Ihandle *ih )
{
  return amy_iupStrReturnInt( data, ih->serial );
}

static void iTimerDestroyMethod( struct libData *data, Ihandle *ih )
{
  iupdrvTimerStop( data, ih );
}

/******************************************************************************/

IUP_API Ihandle *amy_IupTimer( struct libData *data )
{
  return amy_IupCreate( data, "timer" );
}

Iclass *iupTimerNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, NULL );

  ic->name = "timer";
  ic->format = NULL;  /* no parameters */
  ic->nativetype = IUP_TYPEOTHER;
  ic->childtype = IUP_CHILDNONE;
  ic->is_interactive = 0;

  /* Class functions */
  ic->New = iupTimerNewClass;
  ic->Destroy = iTimerDestroyMethod;

  /* Callbacks */
  iupClassRegisterCallback( data, ic, "ACTION_CB", "" );

  /* Attribute functions */
  iupClassRegisterAttribute( data, ic, "WID", iTimerGetWidAttrib, NULL, NULL, NULL, IUPAF_READONLY|IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT|IUPAF_NO_STRING );
  iupClassRegisterAttribute( data, ic, "RUN", iTimerGetRunAttrib, iTimerSetRunAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "TIME", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );

  iupdrvTimerInitClass( data, ic );

  return ic;
}
