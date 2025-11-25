
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
 * \brief Menu Resources.
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include "iup.h"

#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_dialog.h"
#include "iup_str.h"
#include "iup_assert.h"
#include "iup_key.h"
#include "iup_stdcontrols.h"
#include "iup_drvinfo.h"
#include "iup_menu.h"
#include "iup_varg.h"

#endif

struct _IcontrolData 
{
  int child_id;       /* serial number used by child controls */
};

static Ihandle *iMenuGetTopMenu( struct libData *data, Ihandle *ih )
{
  for (; ih->parent; ih = ih->parent)
    ; /* empty*/
  return ih;
}

int iupMenuGetChildId( struct libData *data, Ihandle *ih )
{
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  if (dlg)
    return iupDialogGetChildId( data, ih );
  else
  {
    int id;
    ih = iMenuGetTopMenu( data, ih );
    if ( ! ih) return -1;
    id = ih->data->child_id;
    if (id == 0) id = 100; /* initial number */
    ih->data->child_id = id+1;
    return id;
  }
}

char *iupMenuGetChildIdStr( struct libData *data, Ihandle *ih )
{
  /* Used only in Motif */
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  if (dlg)
    return iupDialogGetChildIdStr( data, ih );
  else
  {
    Ihandle *dialog = iMenuGetTopMenu( data, ih );
    return iupStrReturnStrf( "iup-%s-%d", ih->iclass->name, dialog->data->child_id );
  }
}

int iupMenuIsMenuBar( struct libData *data, Ihandle *ih )
{
  if (ih->parent && ih->parent->iclass->nativetype == IUP_TYPEDIALOG)
    return 1;
  else
    return 0;
}

static void iMenuAdjustPos( struct libData *data, int *x, int *y )
{
  int cursor_x = 0, cursor_y = 0;
  int screen_width = 0, screen_height = 0;

  if (*x == IUP_CENTER || *y == IUP_CENTER ||
      *x == IUP_RIGHT  || *y == IUP_RIGHT)
    iupdrvGetScreenSize( data, &screen_width, &screen_height );

  if (*x == IUP_MOUSEPOS || *y == IUP_MOUSEPOS)
    iupdrvGetCursorPos( data, &cursor_x, &cursor_y );

  switch (*x)
  {
  case IUP_CENTER:
    *x = screen_width/2;
    break;
  case IUP_LEFT:
    *x = 0;
    break;
  case IUP_RIGHT:
    *x = screen_width;
    break;
  case IUP_MOUSEPOS:
    *x = cursor_x;
    break;
  }

  switch (*y)
  {
  case IUP_CENTER:
    *y = screen_height/2;
    break;
  case IUP_LEFT:
    *y = 0;
    break;
  case IUP_RIGHT:
    *y = screen_height;
    break;
  case IUP_MOUSEPOS:
    *y = cursor_y;
    break;
  }

  iupdrvAddScreenOffset( data, x, y, 1 );
}

char *iupMenuProcessTitle( struct libData *data, Ihandle *ih, const char *title)
{
  char *str;

  char *key = iupAttribGet( data, ih, "KEY" );  /* NOT the same definition as the global KEY attribute */
  if ( ! key) return (char*)title;

  str = strchr(title, (int)(*key));
  if (str)
  {
    int len = (int)strlen(title );
    char *new_title = malloc(len+1+1 );
    int pos = (int)(str - title );
    memcpy(new_title, title, pos );
    new_title[pos] = '&';
    memcpy(new_title+pos+1, title+pos, len-pos+1 );
    return new_title;
  }

  return (char*)title;
}

int iupMenuPopup( struct libData *data, Ihandle *ih, int x, int y )
{
  iMenuAdjustPos( data, &x, &y );
  return iupdrvMenuPopup( data, ih, x, y );
}


/******************************************************************/


static int iItemCreateMethod( struct libData *data, Ihandle *ih, void** params)
{
  if (params)
  {
    if (params[0] ) iupAttribSetStr( data, ih, "TITLE", (char*)(params[0] ));
    if (params[1] ) iupAttribSetStr( data, ih, "ACTION", (char*)(params[1] ));
  }
  return IUP_NOERROR;
}

static int iSubmenuCreateMethod( struct libData *data, Ihandle *ih, void** params)
{
  if (params)
  {
    if (params[0] ) iupAttribSetStr( data, ih, "TITLE", (char*)(params[0] ));
    if (params[1] ) 
    {
      Ihandle *child = (Ihandle*)(params[1] );
      if (child->iclass->nativetype == IUP_TYPEMENU)
        amy_IupAppend( data, ih, child );
    }
  }
  return IUP_NOERROR;
}

static int iMenuCreateMethod( struct libData *data, Ihandle *ih, void** params)
{
  ih->data = iupALLOCCTRLDATA();

  if (params)
  {
    Ihandle** iparams = (Ihandle**)params;
    while (*iparams) 
    {
      Ihandle *child = (Ihandle*)(*iparams );
      if (child->iclass->nativetype == IUP_TYPEMENU)
        amy_IupAppend( data, ih, child );
      iparams++;
    }
  }

  return IUP_NOERROR;
}


/******************************************************************************************/


Iclass *iupSeparatorNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, NULL );

  ic->name = "separator";
  ic->format = NULL;  /* no parameters */
  ic->nativetype = IUP_TYPEMENU;
  ic->childtype = IUP_CHILDNONE;
  ic->is_interactive = 0;

  ic->New = iupSeparatorNewClass;

  /* Common */
  iupClassRegisterAttribute( data, ic, "WID", iupBaseGetWidAttrib, NULL, NULL, NULL, IUPAF_READONLY|IUPAF_NO_INHERIT|IUPAF_NO_STRING );
  iupClassRegisterAttribute( data, ic, "NAME", NULL, iupBaseSetNameAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );

  iupdrvSeparatorInitClass( data, ic );

  return ic;
}

Iclass *iupItemNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, NULL );

  ic->name = "item";
  ic->format = "sa";  /* one string and one ACTION callback name */
  ic->format_attr = "TITLE";
  ic->nativetype = IUP_TYPEMENU;
  ic->childtype = IUP_CHILDNONE;
  ic->is_interactive = 1;

  /* Class functions */
  ic->New = iupItemNewClass;
  ic->Create = iItemCreateMethod;

  /* Callbacks */
  iupClassRegisterCallback( data, ic, "HIGHLIGHT_CB", "" );
  iupClassRegisterCallback( data, ic, "ACTION", "" );

  /* Base Callbacks */
  iupBaseRegisterBaseCallbacks( data, ic );

  /* Common Callbacks */
  iupClassRegisterCallback( data, ic, "HELP_CB", "" );

  /* Common */
  iupClassRegisterAttribute( data, ic, "WID", iupBaseGetWidAttrib, NULL, NULL, NULL, IUPAF_READONLY|IUPAF_NO_INHERIT|IUPAF_NO_STRING );
  iupClassRegisterAttribute( data, ic, "NAME", NULL, iupBaseSetNameAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "HANDLENAME", NULL, NULL, NULL, NULL, IUPAF_NO_SAVE | IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "AUTOTOGGLE", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "KEY", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );

  iupdrvItemInitClass( data, ic );

  return ic;
}

Iclass *iupSubmenuNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, NULL );

  ic->name = "submenu";
  ic->format = "sh"; /* one string and one Ihandle */
  ic->format_attr = "TITLE";
  ic->nativetype = IUP_TYPEMENU;
  ic->childtype = IUP_CHILDMANY+1;  /* 1 child */
  ic->is_interactive = 1;

  /* Class functions */
  ic->New = iupSubmenuNewClass;
  ic->Create = iSubmenuCreateMethod;

  /* Base Callbacks */
  iupBaseRegisterBaseCallbacks( data, ic );

  /* Callbacks */
  iupClassRegisterCallback( data, ic, "HIGHLIGHT_CB", "" );

  /* Common */
  iupClassRegisterAttribute( data, ic, "WID", iupBaseGetWidAttrib, NULL, NULL, NULL, IUPAF_READONLY|IUPAF_NO_INHERIT|IUPAF_NO_STRING );
  iupClassRegisterAttribute( data, ic, "NAME", NULL, iupBaseSetNameAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "HANDLENAME", NULL, NULL, NULL, NULL, IUPAF_NO_SAVE | IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "KEY", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );

  iupdrvSubmenuInitClass( data, ic );

  return ic;
}

Iclass *iupMenuNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, NULL );

  ic->name = "menu";
  ic->format = "g"; /* (Ihandle**) */
  ic->nativetype = IUP_TYPEMENU;
  ic->childtype = IUP_CHILDMANY;  /* can have children */
  ic->is_interactive = 1;

  /* Class functions */
  ic->New = iupMenuNewClass;
  ic->Create = iMenuCreateMethod;

  /* Base Callbacks */
  iupBaseRegisterBaseCallbacks( data, ic );

  /* Callbacks */
  iupClassRegisterCallback( data, ic, "OPEN_CB", "" );
  iupClassRegisterCallback( data, ic, "MENUCLOSE_CB", "" );

  /* Common */
  iupClassRegisterAttribute( data, ic, "WID", iupBaseGetWidAttrib, NULL, NULL, NULL, IUPAF_READONLY|IUPAF_NO_INHERIT|IUPAF_NO_STRING );
  iupClassRegisterAttribute( data, ic, "NAME", NULL, iupBaseSetNameAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "RADIO", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );

  iupdrvMenuInitClass( data, ic );

  return ic;
}

/************************************************************************/

IUP_API Ihandle *amy_IupItem( struct libData *data, const char *title, const char *action )
{
  void *params[2];
  params[0] = (void*)title;
  params[1] = (void*)action;
  return amy_IupCreatev( data, "item", params );
}

IUP_API Ihandle *amy_IupSubmenu( struct libData *data, const char *title, Ihandle *child )
{
  void *params[2];
  params[0] = (void*)title;
  params[1] = (void*)child;
  return amy_IupCreatev( data, "submenu", params );
}

IUP_API Ihandle *amy_IupMenuv( struct libData *data, Ihandle **children )
{
  return amy_IupCreatev( data, "menu", (void**)children );
}

IUP_API Ihandle *amy_IupMenuV( struct libData *data, Ihandle *child, va_list arglist )
{
  return amy_IupCreateV( data, "menu", child, arglist );
}

IUP_API Ihandle *amy_IupMenu( struct libData *data, Ihandle *child, ... )
{
  Ihandle *ih;

  va_list arglist;
  va_start(arglist, child );
  ih = amy_IupCreateV( data, "menu", child, arglist );
  va_end(arglist );

  return ih;
}

IUP_API Ihandle *amy_IupSeparator( struct libData *data )
{
  return amy_IupCreate( data, "separator" );
}
