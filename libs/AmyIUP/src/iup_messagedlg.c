
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
 * \brief amy_IupMessageDlg class
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
#include "iup_stdcontrols.h"
#include "iup_register.h"
#include "iup_str.h"
#include "iup_varg.h"

#endif

IUP_API Ihandle *amy_IupMessageDlg( struct libData *data )
{
  return amy_IupCreate( data, "messagedlg" );
}

Iclass *iupMessageDlgNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, iupRegisterFindClass( data, "dialog" ));

  ic->name = "messagedlg";
  ic->cons = "MessageDlg";
  ic->nativetype = IUP_TYPEDIALOG;
  ic->is_interactive = 1;

  ic->New = iupMessageDlgNewClass;

  /* reset not used native dialog methods */
  ic->parent->LayoutUpdate = NULL;
  ic->parent->SetChildrenPosition = NULL;
  ic->parent->Map = NULL;
  ic->parent->UnMap = NULL;

  iupdrvMessageDlgInitClass( data, ic );

  /* only the default values */
  iupClassRegisterAttribute( data, ic, "DIALOGTYPE", NULL, NULL, IUPAF_SAMEASSYSTEM, "MESSAGE", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "BUTTONS", NULL, NULL, IUPAF_SAMEASSYSTEM, "OK", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "BUTTONDEFAULT", NULL, NULL, IUPAF_SAMEASSYSTEM, "1", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "BUTTONRESPONSE", NULL, NULL, IUPAF_SAMEASSYSTEM, "1", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "VALUE", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );

  return ic;
}

IUP_API void amy_IupMessage( struct libData *data, const char *title, const char *message )
{
  Ihandle *dlg = amy_IupCreate( data, "messagedlg" );

  amy_IupSetAttribute( data, dlg, "TITLE", (char*)title );
  amy_IupSetAttribute( data, dlg, "VALUE", (char*)message );
  amy_IupSetAttribute( data, dlg, "PARENTDIALOG", amy_IupGetGlobal( data, "PARENTDIALOG" ));

  amy_IupPopup( data, dlg, IUP_CENTER, IUP_CENTER );
  amy_IupDestroy( data, dlg );
}

IUP_API void amy_IupMessageV( struct libData *data, const char *title, const char *format, va_list arglist)
{
  int size;
  char *str = iupStrGetLargeMem(&size );
  vsnprintf(str, size, format, arglist );
  amy_IupMessage( data, title, str );
}

IUP_API void amy_IupMessagef( struct libData *data, const char *title, const char *format, ... )
{
  va_list arglist;
  va_start( arglist, format );
  amy_IupMessageV( data, title, format, arglist );
  va_end( arglist );
}

IUP_API void amy_IupMessageError( struct libData *data, Ihandle *parent, const char *message )
{
  Ihandle *dlg = amy_IupMessageDlg( data );
  char *title = NULL, *str_message;

  if ( ! parent)
  {
    amy_IupSetStrAttribute( data, dlg, "PARENTDIALOG", amy_IupGetGlobal( data, "PARENTDIALOG" ));
    parent = amy_IupGetAttributeHandle( data, dlg, "PARENTDIALOG" );
  }
  else
    amy_IupSetAttributeHandle( data, dlg, "PARENTDIALOG", parent );

  if (parent)
    title = amy_IupGetAttribute( data, parent, "TITLE" );

  if ( ! title)
    title = "_@IUP_ERROR";

  amy_IupSetStrAttribute( data, dlg, "TITLE", title );
  amy_IupSetAttribute( data, dlg, "DIALOGTYPE", "ERROR" );
  amy_IupSetAttribute( data, dlg, "BUTTONS", "OK" );

  str_message = amy_IupGetLanguageString( data, message );
  if ( ! str_message)
    str_message = (char*)message;
  amy_IupStoreAttribute( data, dlg, "VALUE", str_message );

  amy_IupPopup( data, dlg, IUP_CENTERPARENT, IUP_CENTERPARENT );

  amy_IupDestroy( data, dlg );
}

IUP_API int amy_IupMessageAlarm( struct libData *data, Ihandle *parent, const char *title, const char *message, const char *buttons)
{
  Ihandle *dlg = amy_IupMessageDlg( data );
  char *str_message, *str_title;
  int ret;

  if ( ! parent)
    amy_IupSetStrAttribute( data, dlg, "PARENTDIALOG", amy_IupGetGlobal( data, "PARENTDIALOG" ));
  else
    amy_IupSetAttributeHandle( data, dlg, "PARENTDIALOG", parent );

  if ( ! title)
    title = "IUP_ATTENTION";

  str_title = amy_IupGetLanguageString( data, title );
  if ( ! str_title)
    str_title = (char*)title;
  amy_IupStoreAttribute( data, dlg, "TITLE", str_title );

  str_message = amy_IupGetLanguageString( data, message );
  if ( ! str_message)
    str_message = (char*)message;
  amy_IupStoreAttribute( data, dlg, "VALUE", str_message );

  amy_IupSetAttribute( data, dlg, "DIALOGTYPE", "QUESTION" );
  amy_IupSetStrAttribute( data, dlg, "BUTTONS", buttons );

  amy_IupPopup( data, dlg, IUP_CENTERPARENT, IUP_CENTERPARENT );

  ret = amy_IupGetInt( data, dlg, "BUTTONRESPONSE" );

  amy_IupDestroy( data, dlg );

  return ret;
}
