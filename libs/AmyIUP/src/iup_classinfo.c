
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "iup.h"

#include "iup_class.h"
#include "iup_register.h"
#include "iup_str.h"

#endif

static int compare_names(const void *a, const void *b)
{
  return strcmp( * ( char** ) a, * ( char** ) b );
}

static char *getClassParameters( struct libData *data, const char *format, const char *format_attr)
{
  static char str[200], *pstr;
  pstr = &str[0];

  str[0] = 0;  /* clear for the case where there are no parameters */

  if (format && format[0]!=0)
  {
    int i, count = (int)strlen(format );
    if (count > 10) count = 10;

    for (i=0; i<count; i++)
    {
      char *fstr = NULL;

      switch(format[i] )
      {
      case 'b': fstr = "unsigned char"; break;   /* unused */
      case 'j': fstr = "int*"; break;            /* unused */
      case 'f': fstr = "float"; break;           /* unused */
      case 'i': fstr = (i == 0)? "int w": "int h"; break;     /* used in amy_IupImage* only */
      case 'c': fstr = "const unsigned char *pixels"; break;  /* used in amy_IupImage* only */
      case 's': fstr = "const char *"; break;  /* usually is for TITLE, but depends on format_attr */
      case 'a': fstr = "const char *action"; break; /* name of the ACTION callback */
      case 'h': fstr = "Ihandle *ih"; break;
      case 'g': fstr = "Ihandle** ih_array"; break;  /* when used there are no other parameters */
      }

      if (fstr)
      {
        if (i!=0)
          pstr += sprintf(pstr, "%s", ", " );

        pstr += sprintf(pstr, "%s", fstr );

        if (format[i] == 's')
        {
          if (i == 0 && format_attr)
          {
            char attr[100];
            iupStrLower(attr, format_attr );
            pstr += sprintf(pstr, "%s", attr );
          }
          else
            pstr += sprintf(pstr, "%s", "title" );
        }
      }
      else
      {
        amy_IupMessagef( data, "Internal Error:", "Invalid class format: %s", format );
        return NULL;
      }
    }
  }

  return str;
}

static char *getCallbackReturn( struct libData *data, const char *format )
{
  char *fstr = NULL;

  switch(format[0] )
  {
  case 'c': fstr = "unsigned char"; break;
  case 'i': fstr = "int"; break;
  case 'I': fstr = "int*"; break;
  case 'f': fstr = "float"; break;
  case 'd': fstr = "double"; break;
  case 's': fstr = "char*"; break;
  case 'V': fstr = "void*"; break;
  case 'C': fstr = "cdCanvas*"; break;
  case 'n': fstr = "Ihandle*"; break;
  }

  if (fstr)
    return fstr;
  else
  {
    amy_IupMessagef( data, "Internal Error:", "Invalid callback return format: %s", format );
    return NULL;
  }
}

static char *getCallbackParameters( struct libData *data, const char *format )
{
  static char str[200], *pstr;
  pstr = &str[0];

  pstr += sprintf(pstr, "%s", "Ihandle*" );  /* First parameter in all callbacks */

  if (format && format[0]!=0)
  {
    int i, count = (int)strlen(format );
    if (count > 10) count = 10;

    for (i=0; i<count; i++)
    {
      char *fstr = NULL;

      switch(format[i] )
      {
      case 'c': fstr = "unsigned char"; break;
      case 'i': fstr = "int"; break;
      case 'I': fstr = "int*"; break;
      case 'f': fstr = "float"; break;
      case 'd': fstr = "double"; break;
      case 's': fstr = "char*"; break;
      case 'V': fstr = "void*"; break;
      case 'C': fstr = "cdCanvas*"; break;
      case 'n': fstr = "Ihandle*"; break;
      case '=': return str;
      }

      if ( ! fstr)
      {
        amy_IupMessagef( data, "Internal Error:", "Invalid callback format: %s", format );
        return NULL;
      }

      pstr += sprintf(pstr, ", %s", fstr );
    }
  }

  return str;
}

/* Update callback labels */
static int callbacksList_ActionCB( struct libData *data, Ihandle *ih, char *callName, int pos, int state)
{
  if (state == 1)
  {
    Ihandle *listClasses = amy_IupGetDialogChild( data, ih, "listClasses" );
    Ihandle *txtInfo = amy_IupGetDialogChild( data, ih, "txtInfo" );
    char *className = amy_IupGetAttribute( data, listClasses, amy_IupGetAttribute( data, listClasses, "VALUE" ));
    Iclass *ic = iupRegisterFindClass( data, className );
    char *format = iupClassCallbackGetFormat( data, ic, callName );
    const char *ret = strchr(format, '=' );
    if (ret!=NULL)
      amy_IupSetfAttribute( data, txtInfo, "VALUE", "%s %s(%s );", getCallbackReturn( data, ret + 1), callName, getCallbackParameters( data, format));
    else
      amy_IupSetfAttribute( data, txtInfo, "VALUE", "int %s(%s );", callName, getCallbackParameters( data, format ));
  }

  (void)pos;
  return IUP_DEFAULT;
}

/* Update attribute labels */
static int attributesList_ActionCB(  struct libData *data, Ihandle *ih, char *attribName, int pos, int state )
{
  if (state == 1)
  {
    Ihandle *listClasses = amy_IupGetDialogChild( data, ih, "listClasses" );
    Ihandle *txtInfo = amy_IupGetDialogChild( data, ih, "txtInfo" );
    char *className = amy_IupGetAttribute( data, listClasses, amy_IupGetAttribute( data, listClasses, "VALUE" ));
    Iclass *ic = iupRegisterFindClass( data, className );

    if (iupClassAttribIsRegistered( data, ic, attribName))
    {
      char *def_value;
      int flags;
      iupClassGetAttribNameInfo( data, ic, attribName, &def_value, &flags );

      amy_IupSetfAttribute( data, txtInfo, "VALUE", "Attribute Name: %s\n"
                                         "Default Value: %s\n"
                                         "Flags:\n"
                                         "%s"
                                         "%s"
                                         "%s"
                                         "%s"
                                         "%s"
                                         "%s",
                                         attribName,
                                         def_value==NULL? "NULL": def_value,
                                         flags&(IUPAF_NO_INHERIT|IUPAF_NO_STRING)? "  Is Inheritable\n": "  NON Inheritable\n",
                                         flags&IUPAF_NO_STRING? "  NOT a String\n": "",
                                         flags&IUPAF_HAS_ID? "  Has ID\n": "",
                                         flags&IUPAF_READONLY? "  Read-Only\n": (flags&IUPAF_WRITEONLY? "  Write-Only\n": "" ),
                                         flags&IUPAF_IHANDLENAME? "  Ihandle *name\n": "",
                                         flags&IUPAF_NOT_SUPPORTED? "  NOT SUPPORTED in this driver\n": "" );
    }
    else
      amy_IupSetAttribute( data, txtInfo, "VALUE", "Custom Attribute" );
  }

  (void)pos;
  return IUP_DEFAULT;
}

static char *getNativeType( struct libData *data, InativeType nativetype )
{
  char *str[] = { "void", "control", "canvas", "dialog", "image", "menu", "other" }; 
  return str[nativetype];
}

static const char *getChildType( struct libData *data, int childtype )
{
  if (childtype > IUP_CHILDMANY)
  {
    static char buf[100];
    sprintf(buf, "%d CHILDREN", childtype-IUP_CHILDMANY );
    return buf;
  }
  else
  {
    static const char * str[] = {"NO CHILD", "MANY CHILDREN"};
    return str[childtype];
  }
}

IUP_SDK_API void iupClassInfoGetDesc( struct libData *data, Iclass *ic, Ihandle *ih, const char *attrib_name)
{
  char constructor[50];

  if (ic->cons)
    strcpy(constructor, ic->cons );
  else
  {
    strcpy(constructor, ic->name );
    constructor[0] = (char)toupper(constructor[0] );
  }

  amy_IupSetfAttribute( data, ih, attrib_name, "Ihandle *amy_Iup%s(%s );\n"
                   "Class Name: %s\n"
                   "Native Type: %s\n"
                   "Container Type: %s\n"
                   "Flags:\n"
                   "%s"
                   "%s",
                   constructor,
                   getClassParameters( data, ic->format, ic->format_attr),
                   ic->name,
                   getNativeType( data, ic->nativetype ),
                   getChildType( data, ic->childtype ),
                   ic->is_interactive ? "  Is Keyboard Interactive\n" : "  NOT Keyboard Interactive\n",
                   ic->has_attrib_id ? "  Has Id Attributes\n" : "" );
}

static int classesList_ActionCB( struct libData *data, Ihandle *ih, char *className, int pos, int state )
{
  if (state == 1)
  {
    Iclass *ic;
    int i, total_n, attr_n, cb_n;
    Ihandle *listAttributes = amy_IupGetDialogChild( data, ih, "listAttributes" );
    Ihandle *listCallbacks = amy_IupGetDialogChild( data, ih, "listCallbacks" );
    Ihandle *txtInfo = amy_IupGetDialogChild( data, ih, "txtInfo" );
    char **attr_names;
    
    total_n = amy_IupGetClassAttributes( data, className, NULL, -1 ); /* total include callbacks */
    attr_names = (char **)malloc(total_n * sizeof(char *));

    /************ attributes ************/

    attr_n = amy_IupGetClassAttributes( data, className, attr_names, total_n );
    qsort(attr_names, attr_n, sizeof(char*), compare_names );

    /* Clear lists */
    amy_IupSetAttribute( data, listAttributes, "REMOVEITEM", NULL );

    /* Populate lists */
    for (i = 0; i < attr_n; i++)
      amy_IupSetAttribute( data, listAttributes, "APPENDITEM", attr_names[i] );

    /************ callbacks ************/

    amy_IupSetAttribute( data, listCallbacks, "REMOVEITEM", NULL );

    cb_n = amy_IupGetClassCallbacks( data, className, attr_names, total_n );
    if (cb_n > 0)
    {
      qsort(attr_names, cb_n, sizeof(char*), compare_names );

      for (i = 0; i < cb_n; i++)
        amy_IupSetAttribute( data, listCallbacks, "APPENDITEM", attr_names[i] );
    }

    /***********************************/

    ic = iupRegisterFindClass( data, className );

    iupClassInfoGetDesc( data, ic, txtInfo, "VALUE" );

    free(attr_names );
  }

  (void)pos;
  return IUP_DEFAULT;
}

static void PopulateListOfClasses( struct libData *data, Ihandle *ih )
{
  Ihandle *listClasses = amy_IupGetDialogChild( data, ih, "listClasses" );
  int i, num_classes;
  char **list;

  num_classes = amy_IupGetAllClasses( data, NULL, -1 );
  list = (char **)malloc(num_classes * sizeof(char *));
  amy_IupGetAllClasses( data, list, num_classes );

  qsort(list, num_classes, sizeof(char*), compare_names );

  for (i = 0; i < num_classes; i++)
    amy_IupSetAttribute( data, listClasses, "APPENDITEM", list[i] );

  free(list );
}

IUP_SDK_API void iupClassInfoShowHelp( struct libData *data, const char *className )
{
  char url[1024];
  char *folder = "elem";
  char *sep = "";

  if (strstr(className, "dlg" ) || iupStrEqual(className, "dialog" ))
    folder = "dlg";
  else if (iupStrEqualPartial(className, "matrix" ) ||
            iupStrEqualPartial(className, "mgl" ) ||
            iupStrEqual(className, "plot" ) ||
            iupStrEqual(className, "scintilla" ) ||
            iupStrEqual(className, "cells" ) ||
            iupStrEqual(className, "glbackgroundbox" ) ||
            iupStrEqual(className, "glcanvas" ) ||
            iupStrEqual(className, "olecontrol" ) ||
            iupStrEqual(className, "tuioclient" ) ||
            iupStrEqual(className, "webbrowser" ))
            folder = "ctrl";
  else if (className[0] == 'g' && className[1] == 'l')
    folder = "gl";

  if (iupStrEqualPartial(className, "mgl" ) ||
      iupStrEqual(className, "plot" ) ||
      iupStrEqual(className, "scintilla" ))
      sep = "_";

  /* filename fixes */
  if (iupStrEqualPartial(className, "imagergb" ))
    className = "image";
  else if (iupStrEqual(className, "spinbox" ))
    className = "spin";
  else if (iupStrEqual(className, "olecontrol" ))
    className = "ole";
  else if (iupStrEqual(className, "tuioclient" ))
    className = "tuio";
  else if (iupStrEqual(className, "webbrowser" ))
    className = "web";

  /* sprintf(url, "http://www.tecgraf.puc-rio.br/iup/en/%s/iup%s%s.html", folder, sep, className ); -- direct page version */
  sprintf(url, "http://www.tecgraf.puc-rio.br/iup/index.html?url=%s/iup%s%s.html", folder, sep, className );

  amy_IupHelp( data, url );
}

static int button_help_CB( struct libData *data, Ihandle *ih )
{
  Ihandle *listClasses = amy_IupGetDialogChild( data, ih, "listClasses" );
  char *className = amy_IupGetAttribute( data, listClasses, amy_IupGetAttribute( data, listClasses, "VALUE" ));
  if ( ! className)
    amy_IupMessageError( data, amy_IupGetDialog( data, ih ), "Select a class from the list first!" );
  else
    iupClassInfoShowHelp( data, className );
  return IUP_DEFAULT;
}

static int button_ok_CB( struct libData *data, Ihandle *ih )
{
  amy_IupHide( data, amy_IupGetDialog( data, ih ));
  return IUP_DEFAULT;
}

IUP_API Ihandle *amy_IupClassInfoDialog( struct libData *data, Ihandle *parent )
{
  Ihandle *dialog, *box, *buttons, *listClasses, *listAttributes, *listCallbacks, *txtInfo, *ok_bt, *help_bt;
  
  listClasses    = amy_IupList( data, NULL );  /* list of registered classes */
  listAttributes = amy_IupList( data, NULL );  /* list of attributes of the selected class */
  listCallbacks  = amy_IupList( data, NULL );  /* list of  callbacks of the selected class */

  amy_IupSetAttributes( data, listClasses,    "NAME=listClasses, SIZE=70x85, EXPAND=VERTICAL" );
  amy_IupSetAttributes( data, listAttributes, "NAME=listAttributes, SIZE=120x85, EXPAND=VERTICAL" );
  amy_IupSetAttributes( data, listCallbacks,  "NAME=listCallbacks, SIZE=120x85, EXPAND=VERTICAL" );

  amy_IupSetCallback( data, listClasses,    "ACTION", (Icallback)    classesList_ActionCB );
  amy_IupSetCallback( data, listAttributes, "ACTION", (Icallback) attributesList_ActionCB );
  amy_IupSetCallback( data, listCallbacks,  "ACTION", (Icallback)  callbacksList_ActionCB );

  txtInfo = amy_IupText( data, NULL );
  amy_IupSetAttribute( data, txtInfo, "VISIBLELINES", "7" );
  amy_IupSetAttribute( data, txtInfo, "MULTILINE", "YES" );
  amy_IupSetAttribute( data, txtInfo, "SCROLLBAR", "NO" );
  amy_IupSetAttribute( data, txtInfo, "EXPAND", "HORIZONTAL" );
  amy_IupSetAttribute( data, txtInfo, "NAME", "txtInfo" );

  ok_bt = amy_IupButton( data, "Close", NULL );
  amy_IupSetStrAttribute( data, ok_bt, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
  amy_IupSetCallback( data, ok_bt, "ACTION", (Icallback)button_ok_CB );

  help_bt = amy_IupButton( data, "Class Help", NULL );
  amy_IupSetStrAttribute( data, help_bt, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
  amy_IupSetCallback( data, help_bt, "ACTION", (Icallback)button_help_CB );

  buttons = amy_IupHbox( data, amy_IupFill( data ), ok_bt, help_bt, NULL );
  amy_IupSetAttribute( data, buttons, "MARGIN", "0x0" );
  amy_IupSetAttribute( data, buttons, "NORMALIZESIZE", "HORIZONTAL" );

  box = amy_IupVbox( data,
            amy_IupHbox( data,
              amy_IupSetAttributes( data, amy_IupFrame( data, amy_IupVbox( data, listClasses,    NULL)), "TITLE=Classes:" ),
              amy_IupSetAttributes( data, amy_IupFrame( data, amy_IupVbox( data, listAttributes, NULL)), "TITLE=Attributes:" ),
              amy_IupSetAttributes( data, amy_IupFrame( data, amy_IupVbox( data, listCallbacks,  NULL)), "TITLE=Callbacks:" ),
              NULL),
            amy_IupHbox( data,
              amy_IupSetAttributes( data, amy_IupFrame( data, amy_IupHbox( data, txtInfo, NULL)), "TITLE=Info:" ),
              NULL),
            buttons,
            NULL );

	amy_IupSetAttributes( data, box,"MARGIN=8x8, GAP=4" );

  dialog = amy_IupDialog( data, box );
  amy_IupSetAttribute( data, dialog, "RESIZE", "NO" );
  amy_IupSetAttribute( data, dialog, "MAXBOX", "NO" );
  amy_IupSetAttribute( data, dialog, "MINBOX", "NO" );
  amy_IupSetAttributeHandle( data, dialog, "DEFAULTENTER", ok_bt );
  amy_IupSetAttributeHandle( data, dialog, "DEFAULTESC", ok_bt );

  if (parent) amy_IupSetAttributeHandle( data, dialog, "PARENTDIALOG", parent );

	amy_IupSetAttribute( data, dialog, "TITLE", "Iup Classes Information" );

  amy_IupMap( data, dialog );

  PopulateListOfClasses( data,  dialog );

  return dialog;
}
