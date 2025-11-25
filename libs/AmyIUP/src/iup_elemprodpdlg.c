
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
 * \brief amy_IupLayoutDialog pre-defined dialog
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdarg.h>
#include <limits.h>
#include <ctype.h>

#include "iup.h"
#include "iupcbs.h"

#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_focus.h"
#include "iup_dlglist.h"
#include "iup_assert.h"
#include "iup_drvdraw.h"
#include "iup_draw.h"
#include "iup_image.h"
#include "iup_childtree.h"
#include "iup_dialog.h"
#include "iup_drv.h"
#include "iup_func.h"
#include "iup_register.h"
#include "iup_layout.h"

#endif

static int iLayoutPropertiesClose_CB( struct libData *data, Ihandle *ih)
{
  amy_IupHide( data, amy_IupGetDialog( data, ih ));
  return IUP_DEFAULT;
}

IUP_SDK_API void iupLayoutPropertiesUpdate( struct libData *data, Ihandle *properties, Ihandle *ih)
{
  int i, j, attr_count, cb_count, total_count = amy_IupGetClassAttributes( data, ih->iclass->name, NULL, 0 );
  char **attr_names = (char **)malloc(total_count * sizeof(char *));
  Ihandle *list1 = (Ihandle*) iupAttribGet( data, properties, "_IUP_PROPLIST1" );
  Ihandle *list2 = (Ihandle*) iupAttribGet( data, properties, "_IUP_PROPLIST2" );
  Ihandle *list3 = (Ihandle*) iupAttribGet( data, properties, "_IUP_PROPLIST3" );

  /* Clear everything */
  amy_IupSetAttribute( data, list1, "REMOVEITEM", NULL );
  amy_IupSetAttribute( data, list2, "REMOVEITEM", NULL );
  amy_IupSetAttribute( data, list3, "REMOVEITEM", NULL );
  amy_IupSetAttribute( data, amy_IupGetDialogChild( data, properties, "VALUE1A" ), "VALUE", "" );
  amy_IupSetAttribute( data, amy_IupGetDialogChild( data, properties, "VALUE1B" ), "TITLE", "" );
  amy_IupSetAttribute( data, amy_IupGetDialogChild( data, properties, "VALUE1C" ), "TITLE", "" );
  amy_IupSetAttribute( data, amy_IupGetDialogChild( data, properties, "VALUE2" ), "VALUE", "" );
  amy_IupSetAttribute( data, amy_IupGetDialogChild( data, properties, "VALUE3" ), "VALUE", "" );
  amy_IupSetAttribute( data, amy_IupGetDialogChild( data, properties, "SETBUT" ), "ACTIVE", "No" );
  amy_IupSetAttribute( data, amy_IupGetDialogChild( data, properties, "SETCOLORBUT" ), "VISIBLE", "No" );
  amy_IupSetAttribute( data, amy_IupGetDialogChild( data, properties, "SETFONTBUT" ), "VISIBLE", "No" );
  amy_IupSetAttribute( data, amy_IupGetDialogChild( data, properties, "SHOWHANDLEBUT" ), "VISIBLE", "No" );
  amy_IupSetAttribute( data, amy_IupGetDialogChild( data, properties, "IMAGELBL" ), "VISIBLE", "No" );
  amy_IupSetAttribute( data, amy_IupGetDialogChild( data, properties, "IDTEXT" ), "ACTIVE", "No" );
  amy_IupSetAttribute( data, amy_IupGetDialogChild( data, properties, "IDLABEL" ), "ACTIVE", "No" );

  attr_count = amy_IupGetClassAttributes( data, ih->iclass->name, attr_names, total_count );
  for (i = 0; i < attr_count; i++)
    amy_IupSetAttributeId( data, list1, "", i + 1, attr_names[i] );

  cb_count = total_count - attr_count;
  amy_IupGetClassCallbacks( data, ih->iclass->name, attr_names, cb_count );
  for (i = 0; i<cb_count; i++)
    amy_IupSetAttributeId( data, list3, "", i + 1, attr_names[i] );

  attr_count = amy_IupGetAllAttributes( data, ih, NULL, 0 );
  if (attr_count > total_count)
    attr_names = (char **)realloc(attr_names, attr_count * sizeof(char *));

  attr_count = amy_IupGetAllAttributes( data, ih, attr_names, attr_count );
  for (i = 0, j = 1; i < attr_count; i++)
  {
    if ( ! iupClassAttribIsRegistered( data, ih->iclass, attr_names[i] ))
    {
      amy_IupSetAttributeId( data, list2, "", j, attr_names[i] );
      j++;
    }
  }

  iupAttribSet( data, properties, "_IUP_PROPELEMENT", (char*)ih );

  amy_IupStoreAttribute( data, amy_IupGetDialogChild( data, properties, "ELEMTITLE" ), "VALUE", iupLayoutGetElementTitle( data, ih ));

  if (ih->iclass->nativetype == IUP_TYPEIMAGE)
  {
    amy_IupSetAttributeHandle( data, amy_IupGetDialogChild( data, properties, "ELEMIMAGE" ), "IMAGE", ih );
    amy_IupSetAttribute( data, amy_IupGetDialogChild( data, properties, "ELEMIMAGE" ), "VISIBLE", "Yes" );
  }
  else
    amy_IupSetAttribute( data, amy_IupGetDialogChild( data, properties, "ELEMIMAGE" ), "VISIBLE", "No" );

  free(attr_names );
}

static void iLayoutPropertiesAttribValueChanged( struct libData *data, Ihandle *ih, const char *name)
{
  char *def_value;
  int flags;
  Ihandle *elem = (Ihandle*) iupAttribGetInherit( data, ih, "_IUP_PROPELEMENT" );
  char *value = iupAttribGetLocal( data, elem, name );  /* do NOT check for inherited values */
  Ihandle *txt1 = amy_IupGetDialogChild( data, ih, "VALUE1A" );
  Ihandle *colorbut = amy_IupGetDialogChild( data, ih, "SETCOLORBUT" );
  Ihandle *handlebut = amy_IupGetDialogChild( data, ih, "SHOWHANDLEBUT" );
  Ihandle *imagelbl = amy_IupGetDialogChild( data, ih, "IMAGELBL" );

  iupClassGetAttribNameInfo( data, elem->iclass, name, &def_value, &flags );

  if (iupLayoutAttributeHasChanged( data, elem, name, value, def_value, flags))
    amy_IupSetAttribute( data, txt1, "FGCOLOR", "255 0 0" );
  else
    amy_IupSetAttribute( data, txt1, "FGCOLOR", "0 0 0" );

  if ( ! (flags&IUPAF_READONLY) &&
      !(flags&IUPAF_NO_STRING))
  {
    if (strstr(name, "COLOR" ) != NULL) /* if COLOR in attribute name, show the color selection button */
      amy_IupStoreAttribute( data, colorbut, "BGCOLOR", value );  /* set it even if it is NULL */
  }

  if ((flags&IUPAF_IHANDLENAME || (flags & IUPAF_IHANDLE)))
  {
    Ihandle *handle;
    if (flags & IUPAF_IHANDLE)
    {
      iupAttribSet( data, handlebut, "_IUP_HANDLE", value );
      handle = (Ihandle*)value;
    }
    else
    {
      iupAttribSet( data, handlebut, "_IUP_HANDLE", NULL );
      handle = amy_IupGetHandle( data, value );
    }

    if (iupObjectCheck( data, handle) && handle->iclass->nativetype == IUP_TYPEIMAGE)
    {
      amy_IupSetAttribute( data, imagelbl, "VISIBLE", "Yes" );
      amy_IupSetAttributeHandle( data, imagelbl, "IMAGE", handle );
    }
    else
      amy_IupSetAttribute( data, imagelbl, "VISIBLE", "No" );
  }
}

static int iLayoutPropertiesIdTextChanged_CB( struct libData *data, Ihandle *id_text)
{
  char *id = amy_IupGetAttribute( data, id_text, "VALUE" );
  if (id && id[0] != 0)
  {
    char *def_value;
    int flags;
    char *value, name[100];
    Ihandle *elem = (Ihandle*) iupAttribGetInherit( data, id_text, "_IUP_PROPELEMENT" );
    Ihandle *txt1 = amy_IupGetDialogChild( data, id_text, "VALUE1A" );
    Ihandle *list1 = (Ihandle*) iupAttribGetInherit( data, id_text, "_IUP_PROPLIST1" );
    char *itemlist1 = amy_IupGetAttribute( data, list1, "VALUE" );
    if ( ! itemlist1)
      return IUP_DEFAULT;

    strcpy(name, amy_IupGetAttribute( data, list1, itemlist1));

    iupClassGetAttribNameInfo( data, elem->iclass, name, &def_value, &flags );

    strcat(name, id );

    value = amy_IupGetAttribute( data, elem, name );
    if (value)
    {
      if (flags&IUPAF_NO_STRING)
        amy_IupSetfAttribute( data, txt1, "VALUE", "%p", value );
      else
        amy_IupStoreAttribute( data, txt1, "VALUE", value );
    }
    else
      amy_IupSetAttribute( data, txt1, "VALUE", "NULL" );

    iLayoutPropertiesAttribValueChanged( data, id_text, name );
  }
  return IUP_DEFAULT;
}

static void iLayoutPropertiesCallAttribChanged( struct libData *data, Ihandle *dlg, char *name)
{
  IFns cb = (IFns) amy_IupGetCallback( data, dlg, "ATTRIBCHANGED_CB" );
  if (cb)
    cb( data,dlg, name );
}

static int iLayoutPropertiesSet_CB( struct libData *data, Ihandle *button)
{
  Ihandle *list1 = (Ihandle*) iupAttribGetInherit( data, button, "_IUP_PROPLIST1" );
  char *item = amy_IupGetAttribute( data, list1, "VALUE" );
  if (item)
  {
    Ihandle *dlg = amy_IupGetDialog( data, button );
    Ihandle *elem = (Ihandle*) iupAttribGetInherit( data, button, "_IUP_PROPELEMENT" );
    Ihandle *txt1 = amy_IupGetDialogChild( data, button, "VALUE1A" );
    char *value = amy_IupGetAttribute( data, txt1, "VALUE" );
    char *name = amy_IupGetAttribute( data, list1, item );
    Ihandle *id_text = amy_IupGetDialogChild( data, button, "IDTEXT" );

    if (amy_IupGetInt( data, id_text, "ACTIVE" ))
    {
      char nameid[100];
      char *id = amy_IupGetAttribute( data, id_text, "VALUE" );
      if ( ! id || id[0] == 0)
        id = "";

      sprintf(nameid, "%s%s", name, id );

      if ( ! value || iupStrEqual(value, "NULL" ))
        amy_IupSetAttribute( data, elem, nameid, NULL );
      else
        amy_IupStoreAttribute( data, elem, nameid, value );
    }
    else
    {
      if ( ! value || iupStrEqual(value, "NULL" ))
        amy_IupSetAttribute( data, elem, name, NULL );
      else
        amy_IupStoreAttribute( data, elem, name, value );
    }

    iLayoutPropertiesAttribValueChanged( data, button, name );

    iLayoutPropertiesCallAttribChanged( data, dlg, name );
  }
  return IUP_DEFAULT;
}

static int iLayoutPropertiesSetColor_CB( struct libData *data, Ihandle *colorbut )
{
  Ihandle *color_dlg = amy_IupColorDlg( data );
  amy_IupSetAttributeHandle( data, color_dlg, "PARENTDIALOG", amy_IupGetDialog( data, colorbut));
  amy_IupSetAttribute( data, color_dlg, "TITLE", "Choose Color" );
  amy_IupStoreAttribute( data, color_dlg, "VALUE", amy_IupGetAttribute( data, colorbut, "BGCOLOR" ));

  amy_IupPopup( data, color_dlg, IUP_CENTER, IUP_CENTER );

  if (amy_IupGetInt( data, color_dlg, "STATUS" ) == 1)
  {
    Ihandle *dlg = amy_IupGetDialog( data, colorbut );
    Ihandle *elem = (Ihandle*) iupAttribGetInherit( data, colorbut, "_IUP_PROPELEMENT" );
    Ihandle *list1 = (Ihandle*) iupAttribGetInherit( data, colorbut, "_IUP_PROPLIST1" );
    Ihandle *txt1 = amy_IupGetDialogChild( data, colorbut, "VALUE1A" );
    char *value = amy_IupGetAttribute( data, color_dlg, "VALUE" );
    char *name = amy_IupGetAttribute( data, list1, amy_IupGetAttribute( data, list1, "VALUE" ));
    Ihandle *id_text = amy_IupGetDialogChild( data, colorbut, "IDTEXT" );

    amy_IupStoreAttribute( data, txt1, "VALUE", value );
    amy_IupStoreAttribute( data, colorbut, "BGCOLOR", value );

    if (amy_IupGetInt( data, id_text, "ACTIVE" ))
    {
      char nameid[100];
      char *id = amy_IupGetAttribute( data, id_text, "VALUE" );
      if ( ! id || id[0] == 0)
        id = "";

      sprintf(nameid, "%s%s", name, id );
      amy_IupStoreAttribute( data, elem, nameid, value );
    }
    else
      amy_IupStoreAttribute( data, elem, name, value );

    iLayoutPropertiesAttribValueChanged( data, colorbut, name );

    iLayoutPropertiesCallAttribChanged( data, dlg, name );
  }

  amy_IupDestroy( data, color_dlg );

  return IUP_DEFAULT;
}

static int iLayoutPropertiesSetFont_CB( struct libData *data, Ihandle *fontbut )
{
  Ihandle *font_dlg = amy_IupFontDlg( data );
  Ihandle *txt1 = amy_IupGetDialogChild( data, fontbut, "VALUE1A" );
  amy_IupSetAttributeHandle( data, font_dlg, "PARENTDIALOG", amy_IupGetDialog( data, fontbut));
  amy_IupSetAttribute( data, font_dlg, "TITLE", "Choose Font" );
  amy_IupStoreAttribute( data, font_dlg, "VALUE", amy_IupGetAttribute( data, txt1, "VALUE" ));

  amy_IupPopup( data, font_dlg, IUP_CENTER, IUP_CENTER );

  if (amy_IupGetInt( data, font_dlg, "STATUS" ) == 1)
  {
    Ihandle *dlg = amy_IupGetDialog( data, fontbut );
    Ihandle *elem = (Ihandle*) iupAttribGetInherit( data, fontbut, "_IUP_PROPELEMENT" );
    Ihandle *list1 = (Ihandle*) iupAttribGetInherit( data, fontbut, "_IUP_PROPLIST1" );
    char *value = amy_IupGetAttribute( data, font_dlg, "VALUE" );
    char *name = amy_IupGetAttribute( data, list1, amy_IupGetAttribute( data, list1, "VALUE" ));
    Ihandle *id_text = amy_IupGetDialogChild( data, fontbut, "IDTEXT" );

    amy_IupStoreAttribute( data, txt1, "VALUE", value );

    if (amy_IupGetInt( data, id_text, "ACTIVE" ))
    {
      char nameid[100];
      char *id = amy_IupGetAttribute( data, id_text, "VALUE" );
      if ( ! id || id[0] == 0)
        id = "";

      sprintf(nameid, "%s%s", name, id );
      amy_IupStoreAttribute( data, elem, nameid, value );
    }
    else
      amy_IupStoreAttribute( data, elem, name, value );

    iLayoutPropertiesAttribValueChanged( data, fontbut, name );

    iLayoutPropertiesCallAttribChanged( data, dlg, name );
  }

  amy_IupDestroy( data, font_dlg );

  return IUP_DEFAULT;
}

static int iLayoutPropertiesShowHandle_CB( struct libData *data, Ihandle *handlebut )
{
  Ihandle *elem = (Ihandle*) iupAttribGet( data, handlebut, "_IUP_HANDLE" );
  if ( ! elem)  /* Handle Name */
  {
    Ihandle *txt1 = amy_IupGetDialogChild( data, handlebut, "VALUE1A" );
    char *name = amy_IupGetAttribute( data, txt1, "VALUE" );
    elem = amy_IupGetHandle( data, name );
  }

  if (iupObjectCheck( data, elem))
  {
    Ihandle *dlg = amy_IupElementPropertiesDialog( data, amy_IupGetDialog( data, handlebut), elem );
    amy_IupPopup( data, dlg, IUP_CENTERPARENT, IUP_CENTERPARENT );
    amy_IupDestroy( data, dlg );
  }
  else
  {
    if (elem == NULL)
      amy_IupMessageError( data, amy_IupGetDialog( data, handlebut), "Handle not set" );
    else
      amy_IupMessageError( data, amy_IupGetDialog( data, handlebut), "Invalid Handle!" );
  }
  return IUP_DEFAULT;
}

static int iLayoutPropertiesList1_CB( struct libData *data, Ihandle *list1, char *name, int item, int state )
{
  (void)item;
  if (state)
  {
    char *def_value;
    int flags;
    Ihandle *elem = (Ihandle*) iupAttribGetInherit( data, list1, "_IUP_PROPELEMENT" );
    char *value = iupAttribGetLocal( data, elem, name );  /* do NOT check for inherited values */
    Ihandle *txt1 = amy_IupGetDialogChild( data, list1, "VALUE1A" );
    Ihandle *lbl2 = amy_IupGetDialogChild( data, list1, "VALUE1B" );
    Ihandle *lbl3 = amy_IupGetDialogChild( data, list1, "VALUE1C" );
    Ihandle *setbut = amy_IupGetDialogChild( data, list1, "SETBUT" );
    Ihandle *colorbut = amy_IupGetDialogChild( data, list1, "SETCOLORBUT" );
    Ihandle *fontbut = amy_IupGetDialogChild( data, list1, "SETFONTBUT" );
    Ihandle *handlebut = amy_IupGetDialogChild( data, list1, "SHOWHANDLEBUT" );
    Ihandle *id_text = amy_IupGetDialogChild( data, list1, "IDTEXT" );
    Ihandle *id_label = amy_IupGetDialogChild( data, list1, "IDLABEL" );

    iupClassGetAttribNameInfo( data, elem->iclass, name, &def_value, &flags );

    if (value)
    {
      if (flags&IUPAF_NO_STRING)
        amy_IupSetfAttribute( data, txt1, "VALUE", "%p", value );
      else
        amy_IupStoreAttribute( data, txt1, "VALUE", value );
    }
    else
      amy_IupSetAttribute( data, txt1, "VALUE", "NULL" );

    if (def_value)
      amy_IupStoreAttribute( data, lbl2, "TITLE", def_value );
    else
      amy_IupSetAttribute( data, lbl2, "TITLE", "NULL" );

    amy_IupSetfAttribute( data, lbl3, "TITLE", "%s\n%s%s%s%s%s", flags&(IUPAF_NO_INHERIT | IUPAF_NO_STRING) ? "NON Inheritable" : "Inheritable",
                     flags&IUPAF_NO_STRING ? "NOT a String\n" : "",
                     flags&IUPAF_HAS_ID ? "Has ID\n" : "",
                     flags&IUPAF_READONLY ? "Read-Only\n" : (flags&IUPAF_WRITEONLY ? "Write-Only\n" : "" ),
                     flags&IUPAF_IHANDLENAME ? "Ihandle *name\n" : "",
                     flags&IUPAF_NOT_SUPPORTED ? "NOT SUPPORTED in this driver" : "" );

    if ( ! (flags&IUPAF_READONLY) &&
        !(flags&IUPAF_NO_STRING))
    {
      amy_IupSetAttribute( data, setbut, "ACTIVE", "Yes" );
      amy_IupSetAttribute( data, txt1, "READONLY", "No" );

      if (strstr(name, "COLOR" ) != NULL) /* if COLOR in attribute name, show the color selection button */
        amy_IupSetAttribute( data, colorbut, "VISIBLE", "Yes" );
      else
        amy_IupSetAttribute( data, colorbut, "VISIBLE", "No" );

      if (strstr(name, "FONT" ) != NULL &&      /* if FONT in attribute name, show the font selection button, */
          strstr(name, "FONTFACE" ) == NULL &&  /* but don't show partial font attributes */
          strstr(name, "FONTSTYLE" ) == NULL &&
          strstr(name, "FONTSIZE" ) == NULL)
        amy_IupSetAttribute( data, fontbut, "VISIBLE", "Yes" );
      else
        amy_IupSetAttribute( data, fontbut, "VISIBLE", "No" );
    }
    else
    {
      amy_IupSetAttribute( data, txt1, "READONLY", "Yes" );
      amy_IupSetAttribute( data, setbut, "ACTIVE", "No" );
      amy_IupSetAttribute( data, colorbut, "VISIBLE", "No" );
      amy_IupSetAttribute( data, fontbut, "VISIBLE", "No" );
    }

    if (flags&IUPAF_HAS_ID)
    {
      amy_IupSetAttribute( data, id_text, "ACTIVE", "Yes" );
      amy_IupSetAttribute( data, id_label, "ACTIVE", "Yes" );
    }
    else
    {
      amy_IupSetAttribute( data, id_text, "ACTIVE", "No" );
      amy_IupSetAttribute( data, id_label, "ACTIVE", "No" );
    }

    if (flags&IUPAF_IHANDLENAME || flags & IUPAF_IHANDLE)
      amy_IupSetAttribute( data, handlebut, "VISIBLE", "Yes" );
    else
      amy_IupSetAttribute( data, handlebut, "VISIBLE", "No" );

    iLayoutPropertiesAttribValueChanged( data, list1, name );
  }

  return IUP_DEFAULT;
}

static int iLayoutPropertiesList2_CB( struct libData *data, Ihandle *list2, char *name, int item, int state )
{
  (void)item;
  if (state)
  {
    Ihandle *elem = (Ihandle*) iupAttribGetInherit( data, list2, "_IUP_PROPELEMENT" );
    char *value = iupAttribGet( data, elem, name );
    Ihandle *lbl = amy_IupGetDialogChild( data, list2, "VALUE2" );
    if (value)
      amy_IupSetfAttribute( data, lbl, "VALUE", "%p", value );
    else
      amy_IupSetAttribute( data, lbl, "VALUE", "NULL" );
  }
  return IUP_DEFAULT;
}

static int iLayoutPropertiesGetAsString_CB( struct libData *data, Ihandle *button )
{
  Ihandle *elem = (Ihandle*) iupAttribGetInherit( data, button, "_IUP_PROPELEMENT" );
  Ihandle *list2 = (Ihandle*) iupAttribGetInherit( data, button, "_IUP_PROPLIST2" );
  char *item = amy_IupGetAttribute( data, list2, "VALUE" );
  if (item)
  {
    char *value = iupAttribGet( data, elem, amy_IupGetAttribute( data, list2, item));
    Ihandle *lbl = amy_IupGetDialogChild( data, button, "VALUE2" );
    if (value)
      amy_IupStoreAttribute( data, lbl, "VALUE", value );
    else
      amy_IupSetAttribute( data, lbl, "VALUE", "NULL" );
  }
  return IUP_DEFAULT;
}

static int iLayoutPropertiesSetStr_CB( struct libData *data, Ihandle *button )
{
  Ihandle *dlg = amy_IupGetDialog( data, button );
  Ihandle *elem = (Ihandle*) iupAttribGetInherit( data, button, "_IUP_PROPELEMENT" );
  char *name = amy_IupGetAttribute( data, amy_IupGetDialogChild( data, button, "NAME22" ), "VALUE" );
  char *value = amy_IupGetAttribute( data, amy_IupGetDialogChild( data, button, "VALUE22" ), "VALUE" );
  if ( ! value || iupStrEqual(value, "NULL" ))
    amy_IupSetAttribute( data, elem, name, NULL );
  else
    amy_IupStoreAttribute( data, elem, name, value );

  iupLayoutPropertiesUpdate( data, dlg, elem );

  iLayoutPropertiesCallAttribChanged( data, dlg, name );

  return IUP_DEFAULT;
}

static int iLayoutPropertiesList3_CB( struct libData *data, Ihandle *list3, char *text, int item, int state )
{
  (void)item;
  if (state)
  {
    Ihandle *elem = (Ihandle*) iupAttribGetInherit( data, list3, "_IUP_PROPELEMENT" );
    Icallback cb = amy_IupGetCallback( data, elem, text );
    Ihandle *txt = amy_IupGetDialogChild( data, list3, "VALUE3" );
    if (cb)
    {
      char *cb_name = iupGetCallbackName( data, elem, text );
      if (cb_name)
        amy_IupSetfAttribute( data, txt, "VALUE", "%p [\"%s\"]", cb, cb_name );
      else
        amy_IupSetfAttribute( data, txt, "VALUE", "%p", cb );
    }
    else
    {
      char *cb_name = iupGetCallbackName( data, elem, text );
      if (cb_name)
        amy_IupSetfAttribute( data, txt, "VALUE", "NULL [\"%s\"]", cb_name );
      else
        amy_IupSetAttribute( data, txt, "VALUE", "NULL" );
    }
  }
  return IUP_DEFAULT;
}

static int iLayoutPropertiesTabChangePos_CB( struct libData *data, Ihandle *ih, int new_pos, int old_pos )
{
  (void)old_pos;
  switch (new_pos)
  {
  case 0:
    amy_IupSetAttribute( data, ih, "TIP", "All attributes that are known by the element." );
    break;
  case 1:
    amy_IupSetAttribute( data, ih, "TIP", "Custom attributes set by the application." );
    break;
  case 2:
    amy_IupSetAttribute( data, ih, "TIP", "All callbacks that are known by the element." );
    break;
  }

  /* In GTK the TIP appears for all children */
  /* TODO: move this code to iupgtk_tabs.c */
  if (iupStrEqualNoCase(amy_IupGetGlobal( data, "DRIVER" ), "GTK" ))
  {
    char *tabtype = amy_IupGetAttribute( data, ih, "TABTYPE" );
    int x = 0;
    int y = 0;
    int w = ih->currentwidth;
    int h = ih->currentheight;
    int cw = 0, ch = 0;

    amy_IupGetIntInt( data, ih, "CLIENTSIZE", &cw, &ch );

    /* TABORIENTATION is ignored */
    if (iupStrEqualNoCase(tabtype, "BOTTOM" ))
    {
      y += ch;  /* position after the client area */
      h -= ch;
    }
    else if (iupStrEqualNoCase(tabtype, "RIGHT" ))
    {
      x += cw;  /* position after the client area */
      w -= cw;
    }
    else if (iupStrEqualNoCase(tabtype, "LEFT" ))
      w -= cw;
    else  /* TOP */
      h -= ch;

    amy_IupSetfAttribute( data, ih, "TIPRECT", "%d %d %d %d", x, y, x + w, y + h );
  }

  amy_IupSetAttribute( data, ih, "TIPVISIBLE", "YES" );
  return IUP_DEFAULT;
}

static Ihandle *iLayoutPropertiesCreateDialog( struct libData *data, Ihandle *parent )
{
  Ihandle *list1, *list2, *list3, *close, *dlg, *dlg_box, *button_box, *colorbut, *fontbut, *handlebut,
    *tabs, *box1, *box11, *box2, *box22, *box3, *box33, *set, *id_text, *id_label, *imagelbl;

  close = amy_IupButton( data, "Close", NULL );
  amy_IupSetStrAttribute( data, close, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
  amy_IupSetCallback( data, close, "ACTION", (Icallback)iLayoutPropertiesClose_CB );

  button_box = amy_IupHbox( data,
    amy_IupFill( data ),
    close,
    NULL );
  amy_IupSetAttribute( data, button_box, "MARGIN", "0x0" );

  list1 = amy_IupList( data, NULL );
  amy_IupSetCallback( data, list1, "ACTION", (Icallback)iLayoutPropertiesList1_CB );
  amy_IupSetAttribute( data, list1, "VISIBLELINES", "15" );
  amy_IupSetAttribute( data, list1, "VISIBLECOLUMNS", "11" );
  amy_IupSetAttribute( data, list1, "SORT", "Yes" );
  amy_IupSetAttribute( data, list1, "EXPAND", "VERTICAL" );

  list2 = amy_IupList( data, NULL );
  amy_IupSetCallback( data, list2, "ACTION", (Icallback)iLayoutPropertiesList2_CB );
  amy_IupSetAttribute( data, list2, "VISIBLELINES", "15" );
  amy_IupSetAttribute( data, list2, "VISIBLECOLUMNS", "11" );
  amy_IupSetAttribute( data, list2, "SORT", "Yes" );
  amy_IupSetAttribute( data, list2, "EXPAND", "VERTICAL" );

  list3 = amy_IupList( data, NULL );
  amy_IupSetCallback( data, list3, "ACTION", (Icallback)iLayoutPropertiesList3_CB );
  amy_IupSetAttribute( data, list3, "VISIBLELINES", "15" );
  amy_IupSetAttribute( data, list3, "VISIBLECOLUMNS", "14" );
  amy_IupSetAttribute( data, list3, "SORT", "Yes" );
  amy_IupSetAttribute( data, list3, "EXPAND", "VERTICAL" );

  set = amy_IupButton( data, "Set", NULL );
  amy_IupSetCallback( data, set, "ACTION", iLayoutPropertiesSet_CB );
  amy_IupSetStrAttribute( data, set, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
  amy_IupSetAttribute( data, set, "NAME", "SETBUT" );

  id_text = amy_IupText( data, NULL );
  amy_IupSetCallback( data, id_text, "VALUECHANGED_CB", (Icallback)iLayoutPropertiesIdTextChanged_CB );
  amy_IupSetAttribute( data, id_text, "VISIBLECOLUMNS", "5" );
  amy_IupSetAttribute( data, id_text, "NAME", "IDTEXT" );

  id_label = amy_IupLabel( data, "Id:" );
  amy_IupSetAttribute( data, id_label, "NAME", "IDLABEL" );

  colorbut = amy_IupButton( data, NULL, NULL );
  amy_IupSetAttribute( data, colorbut, "SIZE", "20x10" );
  amy_IupStoreAttribute( data, colorbut, "BGCOLOR", "0 0 0" );
  amy_IupSetCallback( data, colorbut, "ACTION", (Icallback)iLayoutPropertiesSetColor_CB );
  amy_IupSetAttribute( data, colorbut, "NAME", "SETCOLORBUT" );
  amy_IupSetAttribute( data, colorbut, "VISIBLE", "NO" );

  fontbut = amy_IupButton( data, "F", NULL );
  amy_IupSetAttribute( data, fontbut, "SIZE", "20x10" );
  amy_IupStoreAttribute( data, fontbut, "FONT", "Times, Bold Italic 12" );
  amy_IupSetCallback( data, fontbut, "ACTION", (Icallback)iLayoutPropertiesSetFont_CB );
  amy_IupSetAttribute( data, fontbut, "NAME", "SETFONTBUT" );
  amy_IupSetAttribute( data, fontbut, "VISIBLE", "NO" );

  handlebut = amy_IupButton( data, "Handle", NULL );
  amy_IupSetCallback( data, handlebut, "ACTION", (Icallback)iLayoutPropertiesShowHandle_CB );
  amy_IupSetAttribute( data, handlebut, "NAME", "SHOWHANDLEBUT" );
  amy_IupSetAttribute( data, handlebut, "VISIBLE", "NO" );

  imagelbl = amy_IupLabel( data, NULL );
  amy_IupSetAttribute( data, imagelbl, "NAME", "IMAGELBL" );
  amy_IupSetAttribute( data, imagelbl, "IMAGE", "IMGEMPTY" );
  amy_IupSetAttribute( data, imagelbl, "ALIGNMENT", "ACENTER:ACENTER" );
  amy_IupSetAttribute( data, imagelbl, "VISIBLE", "NO" );
  amy_IupSetAttribute( data, imagelbl, "RASTERSIZE", "32x32" );
  amy_IupSetAttribute( data, imagelbl, "EXPAND", "HORIZONTALFREE" );

  box11 = amy_IupVbox( data,
    amy_IupLabel( data, "Value:" ),
    amy_IupSetAttributes( data, amy_IupHbox( data, amy_IupSetAttributes( data, amy_IupText( data, NULL ), "MULTILINE=Yes, ALIGNMENT=ALEFT:ATOP, EXPAND=YES, NAME=VALUE1A" ), amy_IupSetAttributes( data, amy_IupVbox( data, set, id_label, id_text, colorbut, fontbut, handlebut, imagelbl, NULL), "GAP=3" ), NULL), "GAP=10" ),
    amy_IupSetAttributes( data, amy_IupFill( data ), "RASTERSIZE=10" ),
    amy_IupLabel( data, "Default Value:" ),
    amy_IupFrame( data, amy_IupSetAttributes( data, amy_IupLabel( data, NULL ), "ALIGNMENT=ALEFT:ATOP, EXPAND=HORIZONTAL, NAME=VALUE1B" )),
    amy_IupSetAttributes( data, amy_IupFill( data ), "RASTERSIZE=10" ),
    amy_IupLabel( data, "Other Info:" ),
    amy_IupFrame( data, amy_IupSetAttributes( data, amy_IupLabel( data, NULL ), "SIZE=90x48, ALIGNMENT=ALEFT:ATOP, NAME=VALUE1C" )),
    NULL );
  amy_IupSetAttribute( data, box11, "MARGIN", "0x0" );
  amy_IupSetAttribute( data, box11, "GAP", "0" );

  box22 = amy_IupVbox( data,
    amy_IupLabel( data, "Value:" ),
    amy_IupSetAttributes( data, amy_IupText( data, NULL ), "MULTILINE=Yes, ALIGNMENT=ALEFT:ATOP, EXPAND=YES, NAME=VALUE2, READONLY=Yes" ),
    amy_IupSetAttributes( data, amy_IupFill( data ), "RASTERSIZE=10" ),
    amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupButton( data, "Get as String", NULL), "PADDING=3x3" ), "ACTION", iLayoutPropertiesGetAsString_CB, NULL),
    amy_IupLabel( data, "IMPORTANT: if the attribute is not a string\nthis can crash the application." ),
    amy_IupSetAttributes( data, amy_IupFill( data ), "SIZE=60" ),
    NULL );
  amy_IupSetAttribute( data, box22, "MARGIN", "0x0" );
  amy_IupSetAttribute( data, box22, "GAP", "0" );

  box33 = amy_IupVbox( data,
    amy_IupLabel( data, "Value:" ),
    amy_IupSetAttributes( data, amy_IupText( data, NULL ), "EXPAND=HORIZONTAL, READONLY=Yes, NAME=VALUE3" ),
    NULL );
  amy_IupSetAttribute( data, box33, "MARGIN", "0x0" );
  amy_IupSetAttribute( data, box33, "GAP", "0" );

  box1 = amy_IupHbox( data, amy_IupSetAttributes( data, amy_IupVbox( data, amy_IupLabel( data, "Name:" ), list1, NULL), "MARGIN=0x0, GAP=0" ), box11, NULL );
  box2 = amy_IupHbox( data, amy_IupSetAttributes( data, amy_IupVbox( data, amy_IupLabel( data, "Name:" ), list2, NULL), "MARGIN=0x0, GAP=0" ), box22, NULL );
  box3 = amy_IupHbox( data, amy_IupSetAttributes( data, amy_IupVbox( data, amy_IupLabel( data, "Name:" ), list3, NULL), "MARGIN=0x0, GAP=0" ), box33, NULL );

  box2 = amy_IupSetAttributes( data, amy_IupVbox( data,
    box2,
    amy_IupSetAttributes( data, amy_IupFrame( data, amy_IupSetAttributes( data, amy_IupHbox( data,
      amy_IupSetAttributes( data, amy_IupVbox( data, amy_IupLabel( data, "Name:" ), amy_IupSetAttributes( data, amy_IupText( data, NULL ), "VISIBLECOLUMNS=9, NAME=NAME22" ), NULL), "GAP=0, MARGIN=5x5" ),
      amy_IupSetAttributes( data, amy_IupVbox( data, amy_IupLabel( data, "Value:" ), amy_IupSetAttributes( data, amy_IupText( data, NULL ), "EXPAND=HORIZONTAL, NAME=VALUE22" ), NULL), "GAP=0, MARGIN=5x5" ),
      amy_IupSetAttributes( data, amy_IupVbox( data, amy_IupLabel( data, "" ), amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupButton( data, "Set", NULL), "PADDING=3x0, TIP=\"Sets an attribute value. Actually can be any attribute, registered or custom.\"" ), "ACTION", iLayoutPropertiesSetStr_CB, NULL), NULL), "GAP=0, MARGIN=5x5" ),
      NULL), "ALIGNMENT=ACENTER" )), "TITLE=\"Set Attribute\"" ), 
    NULL), "MARGIN=0x0" );

  tabs = amy_IupTabs( data, box1, box2, box3, NULL );
  amy_IupSetAttribute( data, tabs, "TABTITLE0", "Registered Attributes" );
  amy_IupSetAttribute( data, tabs, "TABTITLE1", "Custom Attributes" );
  amy_IupSetAttribute( data, tabs, "TABTITLE2", "Callbacks" );
  amy_IupSetCallback( data, tabs, "TABCHANGEPOS_CB", (Icallback)iLayoutPropertiesTabChangePos_CB );
  iLayoutPropertiesTabChangePos_CB( data, tabs, 0, 0 );

  dlg_box = amy_IupVbox( data,
    amy_IupSetAttributes( data, amy_IupHbox( data,
      amy_IupSetAttributes( data, amy_IupText( data, NULL ), "EXPAND=HORIZONTAL, READONLY=Yes, NAME=ELEMTITLE, BORDER=NO" ),
      amy_IupSetAttributes( data, amy_IupLabel( data, NULL ), "RASTERSIZE=32x32, IMAGE=IMGEMPTY, NAME=ELEMIMAGE, VISIBLE=NO" ),
      NULL), "MARGIN=0x0, GAP=5" ),
    tabs,
    button_box,
    NULL );

  amy_IupSetAttribute( data, dlg_box, "MARGIN", "10x10" );
  amy_IupSetAttribute( data, dlg_box, "GAP", "10" );

  dlg = amy_IupDialog( data, dlg_box );
  amy_IupSetAttribute( data, dlg, "TITLE", "Element Properties" );
  amy_IupSetAttribute( data, dlg, "MINBOX", "NO" );
  amy_IupSetAttribute( data, dlg, "MAXBOX", "NO" );
  amy_IupSetAttributeHandle( data, dlg, "DEFAULTENTER", close );
  amy_IupSetAttributeHandle( data, dlg, "DEFAULTESC", close );
  if (parent) amy_IupSetAttributeHandle( data, dlg, "PARENTDIALOG", parent );
  amy_IupSetAttribute( data, dlg, "ICON", amy_IupGetGlobal( data, "ICON" ));
  iupAttribSet( data, dlg, "_IUP_PROPLIST1", (char*)list1 );
  iupAttribSet( data, dlg, "_IUP_PROPLIST2", (char*)list2 );
  iupAttribSet( data, dlg, "_IUP_PROPLIST3", (char*)list3 );

  amy_IupStoreAttribute( data, amy_IupGetDialogChild( data, dlg, "ELEMTITLE" ), "BGCOLOR", amy_IupGetAttribute( data, dlg, "BGCOLOR" ));

  return dlg;
}

IUP_API Ihandle *amy_IupElementPropertiesDialog( struct libData *data, Ihandle *parent, Ihandle *elem )
{
  Ihandle *dlg = iLayoutPropertiesCreateDialog( data, parent );
  iupLayoutPropertiesUpdate( data, dlg, elem );
  return dlg;
}
