
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
 * \brief Link Button Control
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iup.h"
#include "iupcbs.h"
#include "iupkey.h"

#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_drv.h"
#include "iup_stdcontrols.h"
#include "iup_register.h"

#endif

static int iLinkButton_CB( struct libData *data, Ihandle *ih, int button, int pressed, int x, int y, char *status)
{
  if (button==IUP_BUTTON1 && pressed)
  {
    IFns cb = (IFns) amy_IupGetCallback( data, ih, "ACTION" );
    char *url = iupAttribGetStr( data, ih, "URL" );
    if (cb)
    {
      int ret = cb( data, ih, url);
      if (ret == IUP_CLOSE) 
        amy_IupExitLoop( data );
      else if (ret == IUP_DEFAULT && url)
        amy_IupHelp( data, url );
    }
    else
      amy_IupHelp( data, url );
  }

  (void)x;
  (void)y;
  (void)status;
  return IUP_DEFAULT;
}

static int iLinkEnterWindow_CB( struct libData *data, Ihandle *ih )
{
  amy_IupSetAttribute( data, ih, "CURSOR", "HAND" );
  return IUP_DEFAULT;
}

static int iLinkLeaveWindow_CB( struct libData *data, Ihandle *ih )
{
  amy_IupSetAttribute( data, ih, "CURSOR", "ARROW" );
  return IUP_DEFAULT;
}

static int iLinkMapMethod( struct libData *data, Ihandle *ih )
{
  amy_IupSetAttribute( data, ih, "FONTSTYLE", "Underline" );
  return IUP_NOERROR;
}

static int iLinkCreateMethod( struct libData *data, Ihandle *ih, void **params)
{
  if (params)
  {
    if (params[0]) iupAttribSetStr( data, ih, "URL", (char*)(params[0]));
    if (params[1]) iupAttribSetStr( data, ih, "TITLE", (char*)(params[1]));
  }

  amy_IupSetCallback( data, ih, "BUTTON_CB", (Icallback)iLinkButton_CB);
  amy_IupSetCallback( data, ih, "ENTERWINDOW_CB", iLinkEnterWindow_CB);
  amy_IupSetCallback( data, ih, "LEAVEWINDOW_CB", iLinkLeaveWindow_CB);

  return IUP_NOERROR; 
}

Iclass *iupLinkNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, iupRegisterFindClass( data, "label" ));

  ic->name = "link";
  ic->format = "ss"; /* two strings */
  ic->format_attr = "URL";  /* must handle TITLE manually */
  ic->nativetype = IUP_TYPECONTROL;
  ic->childtype = IUP_CHILDNONE;
  ic->is_interactive = 1;

  /* Class functions */
  ic->New = iupLinkNewClass;
  ic->Create = iLinkCreateMethod;
  ic->Map = iLinkMapMethod;

  /* Callbacks */
  iupClassRegisterCallback( data, ic, "ACTION", "s" );

  /* attributes */
  iupClassRegisterAttribute( data, ic, "URL", NULL, NULL, NULL, NULL, IUPAF_NO_DEFAULTVALUE|IUPAF_NO_INHERIT);
  iupClassRegisterAttribute( data, ic, "CURSOR", NULL, iupdrvBaseSetCursorAttrib, IUPAF_SAMEASSYSTEM, "ARROW", IUPAF_IHANDLENAME|IUPAF_NO_INHERIT);

  iupClassRegisterReplaceAttribDef( data, ic, "FGCOLOR", "LINKFGCOLOR", NULL);

  return ic;
}

IUP_API Ihandle *amy_IupLink( struct libData *data, const char *url, const char * title)
{
  void *params[3];
  params[0] = (void*)url;
  params[1] = (void*)title;
  params[2] = NULL;
  return amy_IupCreatev( data, "link", params);
}
