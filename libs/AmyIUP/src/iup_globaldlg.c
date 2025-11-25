
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
* \brief amy_IupGloabsDialog pre-defined dialog
*
* See Copyright Notice in "iup.h"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iup.h"

#include "iup_object.h"
#include "iup_globalattrib.h"
#include "iup_func.h"
#include "iup_str.h"
#include "iup_attrib.h"
#include "iup_names.h"

#endif

typedef struct _iRegisteredGlobal {
  char *name;
  int windows;
  int motif;
  int gtk;
  int readonly;
} iRegisteredGlobal;

/* sorted alphabetically */
static iRegisteredGlobal global_attribs[] = { 
  { "APPSHELL", 0, 0, 1, 1 }, 
  { "ARGV0", 0, 0, 1, 0 },
  { "AUTOREPEAT", 0, 1, 0, 0 }, 
  { "COMCTL32VER6", 1, 0, 0, 1 }, 
  { "COMPUTERNAME", 1, 1, 1, 1 }, 
  { "CONTROLKEY", 1, 1, 1, 1 }, 
  { "COPYRIGHT", 1, 1, 1, 1 }, 
  { "CURSORPOS", 1, 1, 1, 0 }, 
  { "DEFAULTBUTTONPADDING", 1, 1, 1, 0 },
  { "DEFAULTDECIMALSYMBOL", 1, 1, 1, 0 }, 
  { "DEFAULTFONT", 1, 1, 1, 0 }, 
  { "DEFAULTFONTFACE", 1, 1, 1, 0 }, 
  { "DEFAULTFONTSIZE", 1, 1, 1, 0 }, 
  { "DEFAULTFONTSTYLE", 1, 1, 1, 0 }, 
  { "DEFAULTPRECISION", 1, 1, 1, 0 },
  { "DEFAULTTHEME", 1, 1, 1, 0 }, 
  { "DLGBGCOLOR", 1, 1, 1, 0 }, 
  { "DLGFGCOLOR", 1, 1, 1, 0 },
  { "DLL_HINSTANCE", 1, 0, 0, 1 }, 
  { "DRAWUSEDIRECT2D", 1, 0, 0, 0 },
  { "DRIVER", 1, 1, 1, 1 }, 
  { "DWM_COMPOSITION", 1, 0, 0, 1 }, 
  { "EXEFILENAME", 1, 1, 1, 1 },
  { "EXITLOOP", 1, 1, 1, 0 }, 
  { "FREETYPEFONTS_DIR", 1, 1, 1, 0 },
  { "FULLSIZE", 1, 1, 1, 1 }, 
  { "GLOBALLAYOUTDLGKEY", 1, 1, 1, 0 }, 
  { "GLOBALLAYOUTRESIZEKEY", 1, 1, 1, 0 }, 
  { "GLOBALMENU", 0, 0, 1, 0 },
  { "GL_RENDERER", 1, 1, 1, 1 }, 
  { "GL_VENDOR", 1, 1, 1, 1 }, 
  { "GL_VERSION", 1, 1, 1, 1 }, 
  { "GTKDEVVERSION", 0, 0, 1, 1 },
  { "GTKVERSION", 0, 0, 1, 1 }, 
  { "HELPAPP", 0, 1, 1, 0 },
  { "HINSTANCE", 1, 0, 0, 1 },
  { "ICON", 1, 1, 1, 0 },
  { "IMAGEAUTOSCALE", 1, 1, 1, 0 }, 
  { "IMAGEEXPORT_STATIC", 1, 1, 1, 0 },
  { "IMAGESDPI", 1, 1, 1, 0 }, 
  { "IMAGESTOCKAUTOSCALE", 1, 1, 1, 0 },
  { "IMAGESTOCKSIZE", 1, 1, 1, 0 }, 
  { "INPUTCALLBACKS", 1, 1, 1, 0 }, 
  { "IUPIM_LASTERROR", 1, 1, 1, 1 },
  { "IUPLUA_THREADED", 1, 1, 1, 0 }, 
  { "KEY", 1, 1, 1, 1 }, 
  { "KEYPRESS", 1, 1, 1, 1 }, 
  { "KEYRELEASE", 1, 1, 1, 1 }, 
  { "LANGUAGE", 1, 1, 1, 0 },
  { "LASTERROR", 1, 0, 0, 0 }, 
  { "LEXERLUA", 1, 1, 1, 0 },
  { "LINKFGCOLOR", 1, 1, 1, 0 },
  { "LOCKLOOP", 1, 1, 1, 0 },
  { "LUA_ERROR_LABEL", 1, 1, 1, 0 },
  { "MENUBGCOLOR", 1, 0, 0, 0 }, 
  { "MENUFGCOLOR", 1, 0, 0, 1 }, 
  { "MGLFONTS", 1, 1, 1, 0 },
  { "MODKEYSTATE", 1, 1, 1, 1 }, 
  { "MONITORSCOUNT", 1, 0, 1, 1 }, 
  { "MONITORSINFO", 1, 0, 1, 1 }, 
  { "MOTIFNUMBER", 0, 1, 0, 1 }, 
  { "MOTIFVERSION", 0, 1, 0, 1 }, 
  { "MOUSEBUTTON", 1, 1, 1, 1 },
  { "OVERLAYSCROLLBAR", 0, 0, 1, 0 }, 
  { "PARENTDIALOG", 1, 1, 1, 0 },
  { "SB_BGCOLOR", 0, 1, 1, 0 }, 
  { "SCINTILLA_VERSION", 1, 1, 1, 1 },
  { "SCREENDEPTH", 1, 1, 1, 1 }, 
  { "SCREENDPI", 1, 1, 1, 1 }, 
  { "SCREENSIZE", 1, 1, 1, 1 }, 
  { "SCROLLBARSIZE", 1, 1, 1, 1 }, 
  { "SHIFTKEY", 1, 1, 1, 1 }, 
  { "SHOWMENUIMAGES", 0, 0, 1, 0 }, 
  { "SINGLEINSTANCE", 1, 0, 0, 0 }, 
  { "SYSTEM", 1, 1, 1, 1 }, 
  { "SYSTEMLANGUAGE", 1, 1, 1, 1 },
  { "SYSTEMLOCALE", 1, 1, 1, 1 }, 
  { "SYSTEMVERSION", 1, 1, 1, 1 }, 
  { "TREEIMAGE24", 1, 1, 1, 0 },
  { "TRUECOLORCANVAS", 1, 1, 1, 1 },
  { "TXTBGCOLOR", 1, 1, 1, 0 }, 
  { "TXTFGCOLOR", 1, 1, 1, 0 }, 
  { "TXTHLCOLOR", 1, 1, 1, 0 }, 
  { "USERNAME", 1, 1, 1, 1 }, 
  { "UTF8MODE", 1, 0, 1, 0 }, 
  { "UTF8MODE_FILE", 1, 0, 0, 0 }, 
  { "VERSION", 1, 1, 1, 1 }, 
  { "VIRTUALSCREEN", 1, 0, 1, 1 }, 
  { "XDISPLAY", 0, 1, 1, 1 }, 
  { "XSCREEN", 0, 1, 1, 1 }, 
  { "XSERVERVENDOR", 0, 1, 1, 1 }, 
  { "XVENDORRELEASE", 0, 1, 1, 1 },
  { NULL, 0, 0, 0, 0 }
};

static int iGlobalGetRegisteredAttributesCount(void)
{
  int count = 0;
  while (global_attribs[count].name != NULL)
    count++;
  return count;
}

static int iGlobalIsRegistered(char *name)
{
  int i;

  for (i = 0; global_attribs[i].name != NULL; i++)
  {
    if (iupStrEqual(global_attribs[i].name, name))
      return 1;
  }

  return 0;
}

static int iGlobalsCompareNames(const void* i1, const void* i2)
{
  char *name1 = *((char**)i1 );
  char *name2 = *((char**)i2 );
  return strcmp(name1, name2 );
}

static int iGlobalGetAppAttributes( struct libData *data, char **names )
{
  int total_count = iupGetGlobalAttributes( data, NULL, 0 );
  char ** gnames = NULL;
  int gcount, count, i;

  gnames = (char **)malloc(sizeof(char*)* total_count );

  gcount = iupGetGlobalAttributes( data, gnames, total_count );

  count = 0;
  for (i = 0; i < gcount; i++)
  {
    if (iGlobalIsRegistered(gnames[i] ))
      continue;
    if (names != NULL)
      names[count] = gnames[i];
    count++;
  }

  free( gnames );

  return count;
}

static void iGlobalsUpdate( struct libData *data, Ihandle *dlg )
{
  int i, j, attr_count, total_count;
  Ihandle *list1 = (Ihandle*) iupAttribGet( data, dlg, "_IUP_PROPLIST1" );
  Ihandle *txt1 = (Ihandle*) iupAttribGetInherit( data, list1, "_IUP_ATTVALUE" );
  Ihandle *setbut1 = (Ihandle*) iupAttribGetInherit( data, list1, "_IUP_SETBUTTON" );
  Ihandle *colorbut1 = (Ihandle*) iupAttribGetInherit( data, list1, "_IUP_COLORBUTTON" );
  Ihandle *fontbut1 = (Ihandle*) iupAttribGetInherit( data, list1, "_IUP_FONTBUTTON" );
  Ihandle *list2 = (Ihandle*) iupAttribGetInherit( data, dlg, "_IUP_PROPLIST2" );
  Ihandle *txt2 = (Ihandle*) iupAttribGetInherit( data, list2, "_IUP_ATTVALUE" );
  Ihandle *setbut2 = (Ihandle*) iupAttribGetInherit( data, list2, "_IUP_SETBUTTON" );
  Ihandle *colorbut2 = (Ihandle*) iupAttribGetInherit( data, list2, "_IUP_COLORBUTTON" );
  Ihandle *fontbut2 = (Ihandle*) iupAttribGetInherit( data, list2, "_IUP_FONTBUTTON" );
  Ihandle *list3 = (Ihandle*) iupAttribGet( data, dlg, "_IUP_FUNCLIST" );
  Ihandle *txt3 = (Ihandle*) iupAttribGetInherit( data, list3, "_IUP_FUNCVALUE" );
  Ihandle *list4 = (Ihandle*) iupAttribGet( data, dlg, "_IUP_NAMESLIST" );
  Ihandle *txt4 = (Ihandle*) iupAttribGetInherit( data, list4, "_IUP_NAMESVALUE" );
  Ihandle *show_auto_tg = amy_IupGetDialogChild( data, dlg, "SHOWAUTO" );
  int show_auto = amy_IupGetInt( data, show_auto_tg, "VALUE" );
  char **attr_names;

  /* Clear everything */
  amy_IupSetAttribute( data, list1, "REMOVEITEM", NULL );
  amy_IupSetAttribute( data, txt1, "VALUE", "" );
  amy_IupSetAttribute( data, setbut1, "VALUE", "" );
  amy_IupSetAttribute( data, colorbut1, "ACTIVE", "No" );
  amy_IupSetAttribute( data, fontbut1, "VISIBLE", "No" );
  amy_IupSetAttribute( data, list2, "REMOVEITEM", NULL );
  amy_IupSetAttribute( data, txt2, "VALUE", "" );
  amy_IupSetAttribute( data, setbut2, "VALUE", "" );
  amy_IupSetAttribute( data, colorbut2, "ACTIVE", "No" );
  amy_IupSetAttribute( data, fontbut2, "VISIBLE", "No" );
  amy_IupSetAttribute( data, list3, "REMOVEITEM", NULL );
  amy_IupSetAttribute( data, txt3, "VALUE", "" );
  amy_IupSetAttribute( data, list4, "REMOVEITEM", NULL );
  amy_IupSetAttribute( data, txt4, "VALUE", "" );

  total_count = iGlobalGetAppAttributes( data, NULL );
  if (total_count > 0)
  {
    attr_names = (char **)malloc(total_count * sizeof(char *));
    attr_count = iGlobalGetAppAttributes( data, attr_names );
    qsort(attr_names, total_count, sizeof(char*), iGlobalsCompareNames );
    for (i = 0; i < attr_count; i++)
    {
      amy_IupSetAttributeId( data, list2, "", i + 1, attr_names[i] );
      amy_IupSetIntId( data, list2, "_IUP_READONLY", i + 1, 0 );
    }

    free(attr_names );
  }

  total_count = iGlobalGetRegisteredAttributesCount();
  
  j = 0;
  for (i = 0; i < total_count; i++)
  {
    if ( ! (iupStrEqualNoCase(amy_IupGetGlobal( data, "DRIVER" ), "GTK" ) && global_attribs[i].gtk) &&
        !(iupStrEqualNoCase(amy_IupGetGlobal( data, "DRIVER" ), "Motif" ) && global_attribs[i].motif) &&
        !(iupStrEqualNoCase(amy_IupGetGlobal( data, "DRIVER" ), "Win32" ) && global_attribs[i].windows))
        continue;

    amy_IupSetAttributeId( data, list1, "", j + 1, global_attribs[i].name );
    amy_IupSetIntId( data, list1, "_IUP_READONLY", j + 1, global_attribs[i].readonly );
    j++;
  }

  total_count = iupGetFunctions( data, NULL, 0 );
  attr_names = (char **)malloc(total_count * sizeof(char *));
  attr_count = iupGetFunctions( data, attr_names, total_count );
  for (i = 0; i < attr_count; i++)
    amy_IupSetAttributeId( data, list3, "", i + 1, attr_names[i] );
  free(attr_names );

  total_count = amy_IupGetAllNames( data, NULL, 0 );
  attr_names = (char **)malloc(total_count * sizeof(char *));
  attr_count = amy_IupGetAllNames( data, attr_names, total_count );
  j = 1;
  for (i = 0; i < attr_count; i++)
  {
    if (show_auto || !iupStrEqualPartial(attr_names[i], "_IUP_NAME" ))
    {
      amy_IupSetAttributeId( data, list4, "", j, attr_names[i] );
      j++;
    }
  }

  free(attr_names );
}

static int iGlobalsList_CB( struct libData *data, Ihandle *list1, char *name, int item, int state)
{
  (void)item;
  if (state)
  {
    char *value = amy_IupGetGlobal( data, name );
    Ihandle *txt1 = (Ihandle *) iupAttribGetInherit( data, list1, "_IUP_ATTVALUE" );
    Ihandle *setbut = (Ihandle *) iupAttribGetInherit( data, list1, "_IUP_SETBUTTON" );
    Ihandle *colorbut = (Ihandle *) iupAttribGetInherit( data, list1, "_IUP_COLORBUTTON" );
    Ihandle *fontbut = (Ihandle *) iupAttribGetInherit( data, list1, "_IUP_FONTBUTTON" );

    if (value)
    {
      if (iupGlobalIsPointer( data, name ))
        amy_IupSetStrf( data, txt1, "VALUE", "%p", value );
      else
        amy_IupStoreAttribute( data, txt1, "VALUE", value );
    }
    else
      amy_IupSetAttribute( data, txt1, "VALUE", "NULL" );

    amy_IupSetInt( data, setbut, "ACTIVE", !amy_IupGetIntId( data, list1, "_IUP_READONLY", item));
    amy_IupSetInt( data, txt1, "READONLY", amy_IupGetIntId( data, list1, "_IUP_READONLY", item));

    if ( ! amy_IupGetIntId( data, list1, "_IUP_READONLY", item) && strstr(name, "COLOR" ) != NULL) /* if COLOR in attribute name, show the color selection button */
    {
      amy_IupStoreAttribute( data, colorbut, "BGCOLOR", value );  /* set it even if it is NULL */
      amy_IupSetAttribute( data, colorbut, "VISIBLE", "Yes" );
    }
    else
      amy_IupSetAttribute( data, colorbut, "VISIBLE", "No" );

    if ( ! amy_IupGetIntId( data, list1, "_IUP_READONLY", item) && strstr(name, "FONT" ) != NULL) /* if FONT in attribute name, show the color selection button */
      amy_IupSetAttribute( data, fontbut, "VISIBLE", "Yes" );
    else
      amy_IupSetAttribute( data, fontbut, "VISIBLE", "No" );
  }

  return IUP_DEFAULT;
}

static int iGlobalsSet_CB( struct libData *data, Ihandle *button)
{
  Ihandle *list1 = (Ihandle*) iupAttribGetInherit( data, button, "_IUP_PROPLIST" );
  char *item = amy_IupGetAttribute( data, list1, "VALUE" );
  if (item)
  {
    Ihandle *txt1 = (Ihandle *) iupAttribGetInherit( data, list1, "_IUP_ATTVALUE" );
    char *value = amy_IupGetAttribute( data, txt1, "VALUE" );
    char *name = amy_IupGetAttribute( data, list1, item );

    if ( ! value || iupStrEqual(value, "NULL" ))
      amy_IupSetGlobal( data, name, NULL );
    else
      amy_IupSetStrGlobal( data, name, value );

    if (strstr(name, "COLOR" ) != NULL)
    {
      Ihandle *colorbut = (Ihandle *) iupAttribGetInherit( data, list1, "_IUP_COLORBUTTON" );
      amy_IupStoreAttribute( data, colorbut, "BGCOLOR", value );  /* set it even if it is NULL */
      amy_IupSetStrGlobal( data, "BGCOLOR", value );
    }
  }
  return IUP_DEFAULT;
}

static int iGlobalsSetColor_CB( struct libData *data, Ihandle *colorbut)
{
  Ihandle *color_dlg = amy_IupColorDlg( data );
  amy_IupSetAttributeHandle( data, color_dlg, "PARENTDIALOG", amy_IupGetDialog( data, colorbut));
  amy_IupSetAttribute( data, color_dlg, "TITLE", "Choose Color" );
  amy_IupStoreAttribute( data, color_dlg, "VALUE", amy_IupGetAttribute( data, colorbut, "BGCOLOR" ));

  amy_IupPopup( data, color_dlg, IUP_CENTER, IUP_CENTER );

  if (amy_IupGetInt( data, color_dlg, "STATUS" ) == 1)
  {
    Ihandle *list1 = (Ihandle*) iupAttribGetInherit( data, colorbut, "_IUP_PROPLIST" );
    Ihandle *txt1 = (Ihandle *) iupAttribGetInherit( data, list1, "_IUP_ATTVALUE" );
    char *value = amy_IupGetAttribute( data, color_dlg, "VALUE" );
    char *name = amy_IupGetAttribute( data, list1, amy_IupGetAttribute( data, list1, "VALUE" ));

    amy_IupStoreAttribute( data, txt1, "VALUE", value );

    if (strstr(name, "COLOR" ) != NULL)
    {
      amy_IupStoreAttribute( data, colorbut, "BGCOLOR", value );
      amy_IupSetStrGlobal( data, name, value );
    }

    amy_IupUpdate( data, amy_IupGetDialog( data, colorbut));

    amy_IupDestroy( data, color_dlg );
  }

  return IUP_DEFAULT;
}

static int iGlobalsSetFont_CB( struct libData *data, Ihandle *fontbut)
{
  Ihandle *font_dlg = amy_IupFontDlg( data );
  Ihandle *list1 = (Ihandle*) iupAttribGetInherit( data, fontbut, "_IUP_PROPLIST" );
  Ihandle *txt1 = (Ihandle *) iupAttribGetInherit( data, list1, "_IUP_ATTVALUE" );
  amy_IupSetAttributeHandle( data, font_dlg, "PARENTDIALOG", amy_IupGetDialog( data, fontbut));
  amy_IupSetAttribute( data, font_dlg, "TITLE", "Choose Font" );
  amy_IupStoreAttribute( data, font_dlg, "VALUE", amy_IupGetAttribute( data, txt1, "VALUE" ));

  amy_IupPopup( data, font_dlg, IUP_CENTER, IUP_CENTER );

  if (amy_IupGetInt( data, font_dlg, "STATUS" ) == 1)
  {
    char *value = amy_IupGetAttribute( data, font_dlg, "VALUE" );
    char *name = amy_IupGetAttribute( data, list1, amy_IupGetAttribute( data, list1, "VALUE" ));

    amy_IupStoreAttribute( data, txt1, "VALUE", value );

    amy_IupSetStrGlobal( data, name, value );
  }

  amy_IupDestroy( data, font_dlg );

  return IUP_DEFAULT;
}

static int iGlobalsSetNewAttrib_CB( struct libData *data, Ihandle *button)
{
  char *name = amy_IupGetAttribute( data, amy_IupGetDialogChild( data, button, "NEW_ATTRIB_NAME" ), "VALUE" );
  char *value = amy_IupGetAttribute( data, amy_IupGetDialogChild( data, button, "NEW_ATTRIB_VALUE" ), "VALUE" );
  if ( ! value || iupStrEqual(value, "NULL" ))
    amy_IupSetGlobal( data, name, NULL );
  else
    amy_IupSetStrGlobal( data, name, value );

  iGlobalsUpdate( data, amy_IupGetDialog( data, button));

  return IUP_DEFAULT;
}

static int iGlobalsFunctionsList_CB( struct libData *data, Ihandle *list, char *name, int item, int state)
{
  (void)item;
  if (state)
  {
    Icallback cb = amy_IupGetFunction( data, name );
    Ihandle *txt = (Ihandle *) iupAttribGetInherit( data, list, "_IUP_FUNCVALUE" );

    if (cb)
      amy_IupSetfAttribute( data, txt, "VALUE", "%p", cb );
    else
      amy_IupSetAttribute( data, txt, "VALUE", "NULL" );
  }

  return IUP_DEFAULT;
}

static int iGlobalsFunctionReset_CB( struct libData *data, Ihandle *bt )
{
  Ihandle *list = (Ihandle*) iupAttribGetInherit( data, bt, "_IUP_FUNCLIST" );
  char *name = amy_IupGetAttribute( data, list, "VALUESTRING" );
  if (name)
  {
    Ihandle *txt = (Ihandle *) iupAttribGetInherit( data, bt, "_IUP_FUNCVALUE" );

    amy_IupSetFunction( data, name, NULL );
    amy_IupSetAttribute( data, txt, "VALUE", "NULL" );
    amy_IupSetInt( data, list, "REMOVEITEM", amy_IupGetInt( data, list, "VALUE" ));
  }
  return IUP_DEFAULT;
}

static int iGlobalsNamesList_CB( struct libData *data, Ihandle *list, char *name, int item, int state)
{
  (void)item;
  if (state)
  {
    Ihandle *txt = (Ihandle *) iupAttribGetInherit( data, list, "_IUP_NAMESVALUE" );
    Ihandle *elem = amy_IupGetHandle( data, name );

    if (elem)
      amy_IupSetfAttribute( data, txt, "VALUE", "%p (%s)", elem, elem->iclass->name );
    else
      amy_IupSetAttribute( data, txt, "VALUE", "NULL" );
  }

  return IUP_DEFAULT;
}

static int iGlobalsNameReset_CB( struct libData *data, Ihandle *bt )
{
  Ihandle *list = (Ihandle*) iupAttribGetInherit( data, bt, "_IUP_NAMESLIST" );
  char *name = amy_IupGetAttribute( data, list, "VALUESTRING" );
  if (name)
  {
    Ihandle *txt = (Ihandle *) iupAttribGetInherit( data, bt, "_IUP_NAMESVALUE" );

    amy_IupSetHandle( data, name, NULL );
    amy_IupSetAttribute( data, txt, "VALUE", "NULL" );
    amy_IupSetInt( data, list, "REMOVEITEM", amy_IupGetInt( data, list, "VALUE" ));
  }
  return IUP_DEFAULT;
}

static int iGlobalsNameProperties_CB( struct libData *data, Ihandle *bt )
{
  Ihandle *list = (Ihandle*) iupAttribGetInherit( data, bt, "_IUP_NAMESLIST" );
  char *name = amy_IupGetAttribute( data, list, "VALUESTRING" );
  if (name)
  {
    Ihandle *elem = amy_IupGetHandle( data, name );
    Ihandle *dlg = amy_IupElementPropertiesDialog( data, amy_IupGetDialog( data, list), elem );
    amy_IupPopup( data, dlg, IUP_CENTERPARENT, IUP_CENTERPARENT );
    amy_IupDestroy( data, dlg );
  }
  return IUP_DEFAULT;
}

static int iGlobalsNameFind_CB( struct libData *data, Ihandle *bt )
{
  Ihandle *list = (Ihandle*) iupAttribGetInherit( data, bt, "_IUP_NAMESLIST" );
  char *name = amy_IupGetAttribute( data, list, "VALUESTRING" );
  if (name)
  {
    Ihandle *elem = amy_IupGetHandle( data, name );
    int count = iupNamesFindAll( data, elem, NULL, 0 );
    if (count > 1)
    {
      int i, total_len = 0, max_len = count * 50;
      char *str = malloc(max_len );
      char** names = malloc(count * sizeof(char*));
      iupNamesFindAll( data, elem, names, count );
      str[0] = 0;
      for (i = 0; i < count; i++)
      {
        total_len += (int)strlen(names[i] );
        if (total_len > max_len)
        {
          max_len += 10 * (total_len - max_len );
          str = realloc(str, max_len );
        }
        strcat(str, names[i] );
        strcat(str, "\n" );
      }
      amy_IupGetText( data, "Other Names", str, -1 );  /* read-only */
      free(names );
      free(str );
    }
    else
      amy_IupMessage( data, "Other Names", "No other names." );
  }
  return IUP_DEFAULT;
}

static int iGlobalsNamesShowAuto_CB( struct libData *data, Ihandle *tg, int state)
{
  (void)state;
  iGlobalsUpdate( data, amy_IupGetDialog( data, tg));
  return IUP_DEFAULT;
}

static int iGlobalsNameCheckHandles_CB( struct libData *data, Ihandle *bt )
{
  Ihandle *list = (Ihandle*) iupAttribGetInherit( data, bt, "_IUP_NAMESLIST" );
  int i, count = amy_IupGetInt( data, list, "COUNT" );
  int log_size = 0, log_max_size = count * 50;
  char *log = malloc(log_max_size );

  for (i = 0; i < count; i++)
  {
    char *name = amy_IupGetAttributeId( data, list, "", i+1 );
    Ihandle *elem = amy_IupGetHandle( data, name );
    if ( ! iupObjectCheck( data, elem))
    {
      int name_len = (int)strlen(name );
      if (log_size + name_len + 1 > log_max_size)
      {
        log_max_size += 10 * name_len;
        log = realloc(log, log_max_size );
      }

      memcpy(log + log_size, name, name_len );
      memcpy(log + log_size + name_len, "\n", 1 );
      log_size += name_len + 1;
    }
  }

  if (log_size != 0)
  {
    log[log_size] = 0;
    amy_IupGetText( data, "Invalid Handles", log, -1 );  /* read-only */
  }
  else
    amy_IupMessage( data, "Invalid Handles", "All handles are valid!" );

  free(log );
  return IUP_DEFAULT;
}

static int iGlobalsTabChangePos_CB( struct libData *data, Ihandle *ih, int new_pos, int old_pos)
{
  (void)old_pos;
  switch (new_pos)
  {
    case 0:
      amy_IupSetAttribute( data, ih, "TIP", "Application Global attributes." );
      break;
    case 1:
      amy_IupSetAttribute( data, ih, "TIP", "Registered Global attributes." );
      break;
    case 2:
      amy_IupSetAttribute( data, ih, "TIP", "Functions." );
      break;
    case 3:
      amy_IupSetAttribute( data, ih, "TIP", "Names." );
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

static int iGlobalsClose_CB( struct libData *data, Ihandle *ih)
{
  amy_IupHide( data, amy_IupGetDialog( data, ih));
  return IUP_DEFAULT;
}

static Ihandle *iGlobalsCreateDialog( struct libData *data )
{
  Ihandle *list1, *list2, *list3, *list4, *close, *dlg, *dlg_box, *button_box, *colorbut1, *fontbut1, *colorbut2, *fontbut2,
    *tabs, *box1, *box11, *box12, *box13, *box14, *box2, *box3, *box4, *set1, *set2, *value1, *value2, *value3, *value4;

  close = amy_IupButton( data, "Close", NULL );
  amy_IupSetStrAttribute( data, close, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
  amy_IupSetCallback( data, close, "ACTION", (Icallback)iGlobalsClose_CB );

  button_box = amy_IupHbox( data,
    amy_IupFill( data ),
    close,
    NULL );
  amy_IupSetAttribute( data, button_box, "MARGIN", "0x0" );

  list1 = amy_IupList( data, NULL );
  amy_IupSetCallback( data, list1, "ACTION", (Icallback)iGlobalsList_CB );
  amy_IupSetAttribute( data, list1, "VISIBLELINES", "15" );
  amy_IupSetAttribute( data, list1, "VISIBLECOLUMNS", "16" );
  amy_IupSetAttribute( data, list1, "EXPAND", "VERTICAL" );

  set1 = amy_IupButton( data, "Set", NULL );
  amy_IupSetCallback( data, set1, "ACTION", iGlobalsSet_CB );
  amy_IupSetStrAttribute( data, set1, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));

  colorbut1 = amy_IupButton( data, NULL, NULL );
  amy_IupSetAttribute( data, colorbut1, "SIZE", "20x10" );
  amy_IupStoreAttribute( data, colorbut1, "BGCOLOR", "0 0 0" );
  amy_IupSetCallback( data, colorbut1, "ACTION", (Icallback)iGlobalsSetColor_CB );
  amy_IupSetAttribute( data, colorbut1, "VISIBLE", "NO" );

  fontbut1 = amy_IupButton( data, "F", NULL );
  amy_IupSetAttribute( data, fontbut1, "SIZE", "20x10" );
  amy_IupStoreAttribute( data, fontbut1, "FONT", "Times, Bold Italic 12" );
  amy_IupSetCallback( data, fontbut1, "ACTION", (Icallback)iGlobalsSetFont_CB );
  amy_IupSetAttribute( data, fontbut1, "VISIBLE", "NO" );

  value1 = amy_IupText( data, NULL );
  amy_IupSetAttribute( data, value1, "MULTILINE", "Yes" );
  amy_IupSetAttribute( data, value1, "ALIGNMENT", "ALEFT:ATOP" );
  amy_IupSetAttribute( data, value1, "EXPAND", "YES" );

  list2 = amy_IupList( data, NULL );
  amy_IupSetCallback( data, list2, "ACTION", (Icallback)iGlobalsList_CB );
  amy_IupSetAttribute( data, list2, "VISIBLELINES", "15" );
  amy_IupSetAttribute( data, list2, "VISIBLECOLUMNS", "16" );
  amy_IupSetAttribute( data, list2, "EXPAND", "VERTICAL" );

  set2 = amy_IupButton( data, "Set", NULL );
  amy_IupSetCallback( data, set2, "ACTION", iGlobalsSet_CB );
  amy_IupSetStrAttribute( data, set2, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));

  colorbut2 = amy_IupButton( data, NULL, NULL );
  amy_IupSetAttribute( data, colorbut2, "SIZE", "20x10" );
  amy_IupStoreAttribute( data, colorbut2, "BGCOLOR", "0 0 0" );
  amy_IupSetCallback( data, colorbut2, "ACTION", (Icallback)iGlobalsSetColor_CB );
  amy_IupSetAttribute( data, colorbut2, "VISIBLE", "NO" );

  fontbut2 = amy_IupButton( data, "F", NULL );
  amy_IupSetAttribute( data, fontbut2, "SIZE", "20x10" );
  amy_IupStoreAttribute( data, fontbut2, "FONT", "Times, Bold Italic 12" );
  amy_IupSetCallback( data, fontbut2, "ACTION", (Icallback)iGlobalsSetFont_CB );
  amy_IupSetAttribute( data, fontbut2, "VISIBLE", "NO" );

  value2 = amy_IupText( data, NULL );
  amy_IupSetAttribute( data, value2, "MULTILINE", "Yes" );
  amy_IupSetAttribute( data, value2, "ALIGNMENT", "ALEFT:ATOP" );
  amy_IupSetAttribute( data, value2, "EXPAND", "YES" );

  list3 = amy_IupList( data, NULL );
  amy_IupSetCallback( data, list3, "ACTION", (Icallback)iGlobalsFunctionsList_CB );
  amy_IupSetAttribute( data, list3, "VISIBLELINES", "15" );
  amy_IupSetAttribute( data, list3, "VISIBLECOLUMNS", "16" );
  amy_IupSetAttribute( data, list3, "SORT", "Yes" );
  amy_IupSetAttribute( data, list3, "EXPAND", "VERTICAL" );

  value3 = amy_IupText( data, NULL );
  amy_IupSetAttribute( data, value3, "EXPAND", "HORIZONTAL" );
  amy_IupSetAttribute( data, value3, "READONLY", "Yes" );

  list4 = amy_IupList( data, NULL );
  amy_IupSetCallback( data, list4, "ACTION", (Icallback)iGlobalsNamesList_CB );
  amy_IupSetAttribute( data, list4, "VISIBLELINES", "15" );
  amy_IupSetAttribute( data, list4, "VISIBLECOLUMNS", "16" );
  amy_IupSetAttribute( data, list4, "SORT", "Yes" );
  amy_IupSetAttribute( data, list4, "EXPAND", "VERTICAL" );

  value4 = amy_IupText( data, NULL );
  amy_IupSetAttribute( data, value4, "EXPAND", "HORIZONTAL" );
  amy_IupSetAttribute( data, value4, "READONLY", "Yes" );

  box11 = amy_IupVbox( data,
    amy_IupLabel( data, "Value:" ),
    amy_IupSetAttributes( data, amy_IupHbox( data, value1, amy_IupSetAttributes( data, amy_IupVbox( data, set1, colorbut1, fontbut1, NULL), "GAP=3" ), NULL), "GAP=10" ),
    NULL );
  amy_IupSetAttribute( data, box11, "MARGIN", "0x0" );
  amy_IupSetAttribute( data, box11, "GAP", "0" );

  box12 = amy_IupVbox( data,
    amy_IupLabel( data, "Value:" ),
    amy_IupSetAttributes( data, amy_IupHbox( data, value2, amy_IupSetAttributes( data, amy_IupVbox( data, set2, colorbut2, fontbut2, NULL), "GAP=3" ), NULL), "GAP=10" ),
    NULL );
  amy_IupSetAttribute( data, box12, "MARGIN", "0x0" );
  amy_IupSetAttribute( data, box12, "GAP", "0" );

  box13 = amy_IupVbox( data,
    amy_IupLabel( data, "Value:" ),
    value3, 
    amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupButton( data, "Reset Value", NULL), "PADDING=DEFAULTBUTTONPADDING" ), "ACTION", iGlobalsFunctionReset_CB, NULL),
    NULL );
  amy_IupSetAttribute( data, box13, "MARGIN", "0x0" );
  amy_IupSetAttribute( data, box13, "GAP", "0" );

  box14 = amy_IupVbox( data,
    amy_IupLabel( data, "Value:" ),
    value4, 
    amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupButton( data, "Reset Value", NULL), "PADDING=DEFAULTBUTTONPADDING, NORMALIZERGROUP=amy_IupGlobalNamesNorm" ), "ACTION", iGlobalsNameReset_CB, NULL),
    amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupButton( data, "Properties...", NULL), "PADDING=DEFAULTBUTTONPADDING, NORMALIZERGROUP=amy_IupGlobalNamesNorm" ), "ACTION", iGlobalsNameProperties_CB, NULL),
    amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupButton( data, "Other Names...", NULL), "PADDING=DEFAULTBUTTONPADDING, NORMALIZERGROUP=amy_IupGlobalNamesNorm" ), "ACTION", iGlobalsNameFind_CB, NULL),
    amy_IupSetAttributes( data, amy_IupFlatSeparator( data ), "ORIENTATION=HORIZONTAL" ),
    amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupToggle( data, "Show Auto Names", NULL), "NAME=SHOWAUTO, TIP=\"Show Automatic Generated Names (_IUP_NAME*)\", NORMALIZERGROUP=amy_IupGlobalNamesNorm" ), "ACTION", (Icallback)iGlobalsNamesShowAuto_CB, NULL),
    amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupButton( data, "Check Handles...", NULL), "PADDING=DEFAULTBUTTONPADDING, NORMALIZERGROUP=amy_IupGlobalNamesNorm" ), "ACTION", iGlobalsNameCheckHandles_CB, NULL),
    NULL );
  amy_IupSetAttribute( data, box14, "MARGIN", "0x0" );
  amy_IupSetAttribute( data, box14, "GAP", "3" );

  box1 = amy_IupHbox( data, amy_IupSetAttributes( data, amy_IupVbox( data, amy_IupLabel( data, "Name:" ), list1, NULL), "MARGIN=0x0, GAP=0" ), box11, NULL );
  iupAttribSet( data, box1, "_IUP_PROPLIST", (char*)list1 );
  iupAttribSet( data, box1, "_IUP_ATTVALUE", (char*)value1 );
  iupAttribSet( data, box1, "_IUP_SETBUTTON", (char*)set1 );
  iupAttribSet( data, box1, "_IUP_COLORBUTTON", (char*)colorbut1 );
  iupAttribSet( data, box1, "_IUP_FONTBUTTON", (char*)fontbut1 );

  box2 = amy_IupHbox( data, amy_IupSetAttributes( data, amy_IupVbox( data, amy_IupLabel( data, "Name:" ), list2, NULL), "MARGIN=0x0, GAP=0" ), box12, NULL );
  iupAttribSet( data, box2, "_IUP_PROPLIST", (char*)list2 );
  iupAttribSet( data, box2, "_IUP_ATTVALUE", (char*)value2 );
  iupAttribSet( data, box2, "_IUP_SETBUTTON", (char*)set2 );
  iupAttribSet( data, box2, "_IUP_COLORBUTTON", (char*)colorbut2 );
  iupAttribSet( data, box2, "_IUP_FONTBUTTON", (char*)fontbut2 );

  box2 = amy_IupSetAttributes( data, amy_IupVbox( data,
    box2,
    amy_IupSetAttributes( data, amy_IupFrame( data, amy_IupSetAttributes( data, amy_IupHbox( data, amy_IupSetAttributes( data, amy_IupVbox( data, amy_IupLabel( data, "Name:" ), amy_IupSetAttributes( data, amy_IupText( data, NULL ), "VISIBLECOLUMNS=9, NAME=NEW_ATTRIB_NAME" ), NULL), "GAP=0, MARGIN=5x5" ),
    amy_IupSetAttributes( data, amy_IupVbox( data, amy_IupLabel( data, "Value:" ), amy_IupSetAttributes( data, amy_IupText( data, NULL ), "EXPAND=HORIZONTAL, NAME=NEW_ATTRIB_VALUE" ), NULL), "GAP=0, MARGIN=5x5" ),
    amy_IupSetAttributes( data, amy_IupVbox( data, amy_IupLabel( data, "" ), amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupButton( data, "Set", NULL), "PADDING=3x0, TIP=\"Sets an attribute value. Actually can be any attribute, registered or custom.\"" ), "ACTION", iGlobalsSetNewAttrib_CB, NULL), NULL), "GAP=0, MARGIN=5x5" ),
    NULL), "ALIGNMENT=ACENTER" )), "TITLE=\"Set Attribute\"" ),
    NULL), "MARGIN=0x0" );

  box3 = amy_IupHbox( data, amy_IupSetAttributes( data, amy_IupVbox( data, amy_IupLabel( data, "Name:" ), list3, NULL), "MARGIN=0x0, GAP=0" ), box13, NULL );
  iupAttribSet( data, box3, "_IUP_FUNCLIST", (char*)list3 );
  iupAttribSet( data, box3, "_IUP_FUNCVALUE", (char*)value3 );

  box4 = amy_IupHbox( data, amy_IupSetAttributes( data, amy_IupVbox( data, amy_IupLabel( data, "Name:" ), list4, NULL), "MARGIN=0x0, GAP=0" ), box14, NULL );
  iupAttribSet( data, box4, "_IUP_NAMESLIST", (char*)list4 );
  iupAttribSet( data, box4, "_IUP_NAMESVALUE", (char*)value4 );

  tabs = amy_IupTabs( data, box1, box2, box3, box4, NULL );
  amy_IupSetAttribute( data, tabs, "TABTITLE0", "Registered Attributes" );
  amy_IupSetAttribute( data, tabs, "TABTITLE1", "Custom Attributes" );
  amy_IupSetAttribute( data, tabs, "TABTITLE2", "Functions" );
  amy_IupSetAttribute( data, tabs, "TABTITLE3", "Names" );
  amy_IupSetCallback( data, tabs, "TABCHANGEPOS_CB", (Icallback)iGlobalsTabChangePos_CB );
  iGlobalsTabChangePos_CB( data, tabs, 0, 0 );

  dlg_box = amy_IupVbox( data,
    tabs,
    button_box,
    NULL );

  amy_IupSetAttribute( data, dlg_box, "MARGIN", "10x10" );
  amy_IupSetAttribute( data, dlg_box, "GAP", "10" );
  amy_IupAppend( data, box1, amy_IupGetHandle( data, "amy_IupGlobalNamesNorm" ));  /* to automatically normalize when the dialog is resized. Must be placed before the normalized controls. */

  dlg = amy_IupDialog( data, dlg_box );
  amy_IupSetAttribute( data, dlg, "TITLE", "Globals" );
  amy_IupSetAttributeHandle( data, dlg, "DEFAULTENTER", close );
  amy_IupSetAttributeHandle( data, dlg, "DEFAULTESC", close );
  amy_IupSetAttribute( data, dlg, "ICON", amy_IupGetGlobal( data, "ICON" ));
  iupAttribSet( data, dlg, "_IUP_PROPLIST1", (char*)list1 );
  iupAttribSet( data, dlg, "_IUP_PROPLIST2", (char*)list2 );
  iupAttribSet( data, dlg, "_IUP_FUNCLIST", (char*)list3 );
  iupAttribSet( data, dlg, "_IUP_NAMESLIST", (char*)list4 );
  amy_IupSetAttribute( data, dlg, "SIZE", "250x" );
  amy_IupSetAttribute( data, dlg, "MINBOX", "NO" );
  amy_IupSetAttribute( data, dlg, "MAXBOX", "NO" );

  return dlg;
}

IUP_API Ihandle *amy_IupGlobalsDialog( struct libData *data )
{
	Ihandle *dlg = iGlobalsCreateDialog( data );
	iGlobalsUpdate( data, dlg );
	return dlg;
}
