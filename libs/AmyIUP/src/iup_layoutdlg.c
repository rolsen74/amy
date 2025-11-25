
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
#include "iup_array.h"
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

enum {
  FIND_TYPE = 0,
  FIND_HANDLE = 1,
  FIND_NAME = 2,
  FIND_TITLE = 3,
  FIND_ATTRIBUTE = 4
};

typedef struct _iLayoutDialog {
  int destroy;  /* destroy the selected dialog, when the layout dialog is destroyed */
  int changed;
  Ihandle *dialog;  /* the selected dialog */
  Ihandle *tree, *status, *timer;
  Ihandle *properties;  /* elements from the layout dialog */
  Ihandle *globals;
  Ihandle *copy_elem;
  Ihandle *cut_elem;
  const char *new_elem_class;
} iLayoutDialog;

static int iLayoutFindItemMatch( struct libData *data, Ihandle *ih, const char *str, int searchType)
{
  if (searchType == FIND_TYPE)
    return iupStrEqualNoCase( amy_IupGetClassName( data, ih ), str );
  else if (searchType == FIND_TITLE)
  {
    char *title = iupAttribGetLocal( data, ih, "TITLE" );
    return title ? iupStrEqualNoCase(title, str) : 0;
  }
  else if (searchType == FIND_ATTRIBUTE)
  {
    char att[80], val[80];
    char *attVal;
    iupStrToStrStr(str, att, val, '=' );
    attVal = iupAttribGetLocal( data, ih, att );
    if (attVal == NULL)
      return 0;
    if (iupStrEqualNoCase(val, attVal))
      return 1;
  }

  return 0;
}

static Ihandle *iLayoutFindNode( struct libData *data, Ihandle *tree, const char *str, int start_id, int end_id, int searchType)
{
  Ihandle *elem;
  int id;

  for (id = start_id; id <= end_id; id++)
  {
    elem = (Ihandle*) amy_IupTreeGetUserId( data,  tree, id );

    if ( ! elem)  /* for the vled tree */
      continue;

    if (iLayoutFindItemMatch( data, elem, str, searchType ))
      return elem;
  }

  return NULL;
}

static int iLayoutFindDialogNext_CB( struct libData *data, Ihandle *ih)
{
  Ihandle *find_dlg = (Ihandle*) amy_IupGetAttribute( data, ih, "FIND_ELEM_DIALOG" );
  Ihandle *dialog = (Ihandle*) amy_IupGetAttribute( data, find_dlg, "DIALOG" );
  Ihandle *tree = (Ihandle*) amy_IupGetAttribute( data, find_dlg, "TREE" );
  Ihandle *lbl_result = amy_IupGetDialogChild( data, find_dlg, "FIND_RESULT" );

  Ihandle *target = amy_IupGetDialogChild( data, find_dlg, "TARGET" );
  Ihandle *targetValue = amy_IupGetAttributeHandle( data, target, "VALUE" );
  int searchType = amy_IupGetInt( data, targetValue, "SEARCH_TYPE" );

  char *str = amy_IupGetAttribute( data, amy_IupGetDialogChild( data, find_dlg, "FIND_TEXT" ), "VALUE" );

  int last_id = amy_IupGetInt( data, tree, "VALUE" );

  Ihandle *obj = NULL;

  if (searchType == FIND_HANDLE)
    obj = amy_IupGetHandle( data, str );
  else if (searchType == FIND_NAME)
    obj = amy_IupGetDialogChild( data, dialog, str );
  else 
  {
    int count = amy_IupGetInt( data, tree, "COUNT" );
    obj = iLayoutFindNode( data, tree, str, last_id + 1, count - 1, searchType );
    if ( ! obj)
      obj = iLayoutFindNode( data, tree, str, 0, last_id, searchType );
  }

  if (obj)
  {
    int id = amy_IupTreeGetId( data, tree, obj );
    IFnii cb = (IFnii) amy_IupGetCallback( data, tree, "SELECTION_CB" );
    cb( data, tree, last_id, 0 );
    amy_IupSetInt( data, tree, "VALUE", id );
    cb( data, tree, id, 1 );

    amy_IupSetAttribute( data, lbl_result, "TITLE", "" );
  }
  else
    amy_IupSetAttribute( data, lbl_result, "TITLE", "Not Found!" );

  return IUP_DEFAULT;
}

static int iLayoutFindDialogClose_CB( struct libData *data, Ihandle *ih )
{
  Ihandle *find_dlg = amy_IupGetDialog( data, ih );
  amy_IupHide( data, find_dlg );  /* do not destroy, just hide */
  return IUP_DEFAULT;
}

IUP_SDK_API Ihandle *iupLayoutFindElementDialog( struct libData *data, Ihandle *tree, Ihandle *elem )
{
  Ihandle *txt, *box, *find_dlg;
  Ihandle *type, *handle_name, *name, *title, *attribute, *radio;
  Ihandle *bt_next, *bt_close, *lbl_result;
  Ihandle *dialog = amy_IupGetDialog( data, elem );

  txt = amy_IupText( data, NULL );
  amy_IupSetAttribute( data, txt, "NAME", "FIND_TEXT" );
  amy_IupSetAttribute( data, txt, "VISIBLECOLUMNS", "20" );
  amy_IupSetAttribute( data, txt, "EXPAND", "HORIZONTAL" );

  type = amy_IupToggle( data, "Type", NULL );
  amy_IupSetAttribute( data, type, "NAME", "FIND_TYPE" );
  amy_IupSetInt( data, type, "SEARCH_TYPE", 0 );
  amy_IupSetAttribute( data, type, "TIP", "Element Type (Class Name)" );

  handle_name = amy_IupToggle( data, "Handle Name", NULL );
  amy_IupSetAttribute( data, handle_name, "NAME", "FIND_HANDLE" );
  amy_IupSetInt( data, handle_name, "SEARCH_TYPE", 1 );
  amy_IupSetAttribute( data, handle_name, "TIP", "Handle Name set using amy_IupSetHandle or declared in LED" );

  name = amy_IupToggle( data, "NAME Attribute", NULL );
  amy_IupSetAttribute( data, name, "NAME", "FIND_NAME" );
  amy_IupSetInt( data, name, "SEARCH_TYPE", 2 );
  amy_IupSetAttribute( data, name, "TIP", "NAME attribute used for amy_IupGetDialogChild" );

  title = amy_IupToggle( data, "Title", NULL );
  amy_IupSetAttribute( data, title, "NAME", "FIND_TITLE" );
  amy_IupSetInt( data, title, "SEARCH_TYPE", 3 );
  amy_IupSetAttribute( data, title, "TIP", "TITLE attribute" );

  attribute = amy_IupToggle( data, "Atribute", NULL );
  amy_IupSetAttribute( data, attribute, "NAME", "FIND_ATTRIBUTE" );
  amy_IupSetInt( data, attribute, "SEARCH_TYPE", 4 );
  amy_IupSetAttribute( data, attribute, "TIP", "Attribute=Value" );

  bt_next = amy_IupButton( data, "Find Next", NULL );
  amy_IupSetStrAttribute( data, bt_next, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
  amy_IupSetCallback( data, bt_next, "ACTION", (Icallback)iLayoutFindDialogNext_CB );
  bt_close = amy_IupButton( data, "Close", NULL );
  amy_IupSetCallback( data, bt_close, "ACTION", (Icallback)iLayoutFindDialogClose_CB );
  amy_IupSetStrAttribute( data, bt_close, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));

  lbl_result = amy_IupLabel( data, NULL );
  amy_IupSetAttribute( data, lbl_result, "SIZE", "30" );
  amy_IupSetAttribute( data, lbl_result, "NAME", "FIND_RESULT" );

  radio = amy_IupRadio( data, amy_IupVbox( data,
    type,
    handle_name,
    name,
    title,
    attribute,
    NULL));

  amy_IupSetAttribute( data, radio, "NAME", "TARGET" );
  amy_IupSetAttribute( data, radio, "VALUE_HANDLE", (char*)type );
  amy_IupSetAttribute( data, radio, "MARGIN", "10x10" );

  box = amy_IupVbox( data,
    amy_IupLabel( data, "Find What:" ),
    txt,
    amy_IupHbox( data,
      amy_IupSetAttributes(  data, amy_IupFrame( data, radio), "TITLE=\"What Kind:\"" ),
      amy_IupFill( data ),
      amy_IupSetAttributes(  data, amy_IupVbox( data, 
        bt_next,
        bt_close,
        lbl_result,
        NULL), "NORMALIZESIZE=HORIZONTAL, MARGIN=x20" ),
      NULL),
    NULL );
  amy_IupSetAttribute( data, box, "NMARGIN", "10x10" );
  amy_IupSetAttribute( data, box, "GAP", "5" );

  find_dlg = amy_IupDialog( data, box );
  amy_IupSetAttribute( data, find_dlg, "TITLE", "Find in Layout" );
  amy_IupSetAttribute( data, find_dlg, "DIALOGFRAME", "Yes" );
  amy_IupSetAttributeHandle( data, find_dlg, "DEFAULTENTER", bt_next );
  amy_IupSetAttributeHandle( data, find_dlg, "DEFAULTESC", bt_close );
  amy_IupSetAttributeHandle( data, find_dlg, "PARENTDIALOG", amy_IupGetDialog( data, tree ));

  /* Save the multiline to access it from the callbacks */
  amy_IupSetAttribute( data, find_dlg, "TREE", (char*)tree );

  /* Save the dialog to reuse it */
  amy_IupSetAttribute( data, find_dlg, "FIND_ELEM_DIALOG", (char*)find_dlg );  /* from itself */
  amy_IupSetAttribute( data, find_dlg, "DIALOG", (char*)dialog ); /* from the main dialog, use to find NAME */

  return find_dlg;
}

static char *iLayoutGetName( struct libData *data, Ihandle *ih)
{
  char *name = amy_IupGetName( data, ih );
  if (name && iupStrEqualPartial(name, "_IUP_NAME" ))
    name = NULL;
  if ( ! name && ih->iclass->nativetype == IUP_TYPEDIALOG)
    name = iupAttribGet( data, ih, "_IUP_DIALOG_NAME" );
  return name;
}

IUP_SDK_API char *iupLayoutGetElementTitle( struct libData *data, Ihandle *ih)
{
  char *title = iupAttribGetLocal( data, ih, "TITLE" );
  char *name = iLayoutGetName( data, ih );
  char *str = iupStrGetMemory(200 );
  if (title)
  {
    char buffer[51];

    if (iupStrLineCount(title, (int)strlen(title)) > 1)
    {
      int len;
      iupStrNextLine(title, &len ); /* get the size of the first line */
      if (len > 50) len = 50;
      iupStrCopyN(buffer, len + 1, title );
      title = &buffer[0];
    }

    if (name)
      sprintf(str, "[%s] \"%.50s\" (%.50s)", amy_IupGetClassName( data, ih ), title, name );
    else
      sprintf(str, "[%s] \"%.50s\"", amy_IupGetClassName( data, ih ), title );
  }
  else
  {
    if (name)
      sprintf(str, "[%s] (%.50s)", amy_IupGetClassName( data, ih ), name );
    else
      sprintf(str, "[%s]", amy_IupGetClassName( data, ih ));
  }

  if (ih->iclass->nativetype == IUP_TYPEIMAGE)
    sprintf(str + strlen(str), " - %s", amy_IupGetAttribute( data, ih, "RASTERSIZE" ));

  return str;
}

static void iLayoutRemoveExt( struct libData *data, char *title, const char *ext )
{
  int len = (int)strlen(title );
  int len_ext = (int)strlen(ext );
  if (len_ext == 1)
  {
    if (tolower(title[len - 1] ) == ext[0] &&
        title[len - 2] == '.')
        title[len - 2] = 0; /* place terminator at dot */
  }
  else
  {
    if (tolower(title[len - 1] ) == ext[2] &&
        tolower(title[len - 2] ) == ext[1] &&
        tolower(title[len - 3] ) == ext[0] &&
        title[len - 4] == '.')
        title[len - 4] = 0; /* place terminator at dot */
  }
}

static int iLayoutCompareClassNames( struct libData *data, const void *a, const void *b )
{
  int ret;
  const char *str1 = *(const char**)a;
  const char *str2 = *(const char**)b;
  int flat1 = 0, flat2 = 0;
  if (iupStrEqualPartial(str1, "flat" )) { str1 += 4; flat1 = 1; } /* don't consider "flat" prefix */
  if (iupStrEqualPartial(str2, "flat" )) { str2 += 4; flat2 = 1; }
  ret = strcmp(str1, str2 );
  if (ret == 0)
  {
    if (flat1)
      return 1;
    if (flat2)
      return -1;
    return 0;
  }
  return ret;
}

IUP_SDK_API int iupLayoutAttributeHasChanged( struct libData *data, Ihandle *ih, const char *name, const char *value, const char *def_value, int flags)
{
  if ((flags&IUPAF_NO_STRING) || /* not a string */
      (flags&IUPAF_HAS_ID) ||  /* has id */
      (flags&(IUPAF_READONLY | IUPAF_WRITEONLY)))  /* can only read or only write */
      return 0;

  if ( ! value || value[0] == 0 || iupATTRIB_ISINTERNAL(value))
    return 0;

  if ((flags&IUPAF_NO_SAVE) && iupBaseNoSaveCheck( data, ih, name))  /* can not be saved */
    return 0;

  if (def_value && iupStrEqualNoCase(def_value, value))  /* equal to the default value */
    return 0;

  if ( ! def_value && iupStrFalse(value))  /* default=NULL and value=NO */
    return 0;

  if ( ! (flags&IUPAF_NO_INHERIT) && ih->parent) /* if inherit, check if the same value is defined at parent */
  {
    char *parent_value = iupAttribGetInherit( data, ih->parent, name );
    if (parent_value && iupStrEqualNoCase(value, parent_value ))
      return 0;
  }

  return 1;
}


/***************************************************************************
                          Tree Utilities
***************************************************************************/


static void iLayoutTreeSetNodeColor( struct libData *data, Ihandle *tree, int id, Ihandle *ih )
{
  if (ih->handle != NULL)
    amy_IupSetAttributeId( data, tree, "COLOR", id, "0 0 0" );
  else
    amy_IupSetAttributeId( data, tree, "COLOR", id, "128 128 128" );
}

static void iLayoutTreeSetNodeInfo( struct libData *data, Ihandle *tree, int id, Ihandle *ih)
{
  amy_IupSetAttributeId( data, tree, "TITLE", id, iupLayoutGetElementTitle( data, ih ));
  iLayoutTreeSetNodeColor( data, tree, id, ih );
  amy_IupTreeSetUserId( data, tree, id, ih );
}

static Ihandle *iLayoutTreeGetFirstChild( struct libData *data, Ihandle *ih)
{
  Ihandle *firstchild = ih->firstchild;

  while (firstchild && firstchild->flags & IUP_INTERNAL)
    firstchild = firstchild->brother;

  return firstchild;
}

static void iLayoutTreeAddNewNode( struct libData *data, Ihandle *tree, Ihandle *new_ih)
{
  int id;

  if (new_ih->iclass->childtype != IUP_CHILDNONE)
  {
    if (new_ih == iLayoutTreeGetFirstChild( data, new_ih->parent ))  /* if new_ih is the first child use ADD */
    {
      Ihandle *ref_elem = new_ih->parent;
      int ref_id = amy_IupTreeGetId( data, tree, ref_elem );
      amy_IupSetAttributeId( data, tree, "ADDBRANCH", ref_id, "" );
    }
    else
    {
      Ihandle *ref_elem = iupChildTreeGetPrevBrother( data, new_ih );
      int ref_id = amy_IupTreeGetId( data, tree, ref_elem );
      amy_IupSetAttributeId( data, tree, "INSERTBRANCH", ref_id, "" );
    }
  }
  else
  {
    if (new_ih == iLayoutTreeGetFirstChild( data, new_ih->parent ))  /* if new_ih is the first child use ADD */
    {
      Ihandle *ref_elem = new_ih->parent;
      int ref_id = amy_IupTreeGetId( data, tree, ref_elem );
      amy_IupSetAttributeId( data, tree, "ADDLEAF", ref_id, "" );
    }
    else
    {
      Ihandle *ref_elem = iupChildTreeGetPrevBrother( data, new_ih );
      int ref_id = amy_IupTreeGetId( data, tree, ref_elem );
      amy_IupSetAttributeId( data, tree, "INSERTLEAF", ref_id, "" );
    }
  }

  id = amy_IupGetInt( data, tree, "LASTADDNODE" );
  iLayoutTreeSetNodeInfo( data, tree, id, new_ih );
}

static int iLayoutTreeAddNode( struct libData *data, Ihandle *tree, int ref_id, Ihandle *ih)
{
  int id;

  if (ih->iclass->childtype != IUP_CHILDNONE)
  {
    if (ih == iLayoutTreeGetFirstChild( data, ih->parent ))  /* if ih is the first child use ADD */
      amy_IupSetAttributeId( data, tree, "ADDBRANCH", ref_id, "" );
    else
      amy_IupSetAttributeId( data, tree, "INSERTBRANCH", ref_id, "" );
  }
  else
  {
    if (ih == iLayoutTreeGetFirstChild( data, ih->parent ))  /* if ih is the first child use ADD */
      amy_IupSetAttributeId( data, tree, "ADDLEAF", ref_id, "" );
    else
      amy_IupSetAttributeId( data, tree, "INSERTLEAF", ref_id, "" );
  }

  id = amy_IupGetInt( data, tree, "LASTADDNODE" );
  iLayoutTreeSetNodeInfo( data, tree, id, ih );
  return id;
}

static void iLayoutTreeAddChildren( struct libData *data, Ihandle *tree, int parent_id, Ihandle *parent )
{
  Ihandle *child;
  int ref_id = parent_id;

  for (child = parent->firstchild; child; child = child->brother)
  {
    if ( ! (child->flags & IUP_INTERNAL))
    {
      ref_id = iLayoutTreeAddNode( data, tree, ref_id, child );

      if (child->iclass->childtype != IUP_CHILDNONE)
        iLayoutTreeAddChildren( data, tree, ref_id, child );
    }
  }
}

static Ihandle *iLayoutGetCanvas( struct libData *data, iLayoutDialog *layoutdlg )
{
  Ihandle *canvas = amy_IupGetBrother( data, layoutdlg->tree );
  return canvas;
}

static void iLayoutRefreshLayout( struct libData *data, iLayoutDialog *layoutdlg )
{
  Ihandle *canvas = iLayoutGetCanvas( data, layoutdlg );
  int w = 0, h = 0;

  amy_IupRefresh( data, layoutdlg->dialog );

  amy_IupGetIntInt( data, layoutdlg->dialog, "CLIENTSIZE", &w, &h );
  amy_IupSetInt( data, canvas, "XMAX", w );
  amy_IupSetInt( data, canvas, "YMAX", h );

  amy_IupGetIntInt( data, canvas, "DRAWSIZE", &w, &h );
  amy_IupSetInt( data, canvas, "DX", w );
  amy_IupSetInt( data, canvas, "DY", h );

  /* redraw canvas */
  amy_IupUpdate( data, canvas );
}

static void iLayoutTreeSelectionChanged( struct libData *data, iLayoutDialog *layoutdlg, Ihandle *ih, int id );

static void iLayoutTreeRebuild( struct libData *data, iLayoutDialog *layoutdlg )
{
  Ihandle *tree = layoutdlg->tree;
  amy_IupSetAttribute( data, tree, "DELNODE0", "CHILDREN" );

  layoutdlg->changed = 0;
  layoutdlg->copy_elem = NULL;
  layoutdlg->cut_elem = NULL;

  iLayoutTreeSetNodeInfo( data, tree, 0, layoutdlg->dialog );
  iLayoutTreeAddChildren( data, tree, 0, layoutdlg->dialog );

  amy_IupSetAttribute( data, tree, "VALUE", "ROOT" );
  iLayoutTreeSelectionChanged( data, layoutdlg, layoutdlg->dialog, 0 );

  iLayoutRefreshLayout( data, layoutdlg );
}


/***************************************************************************
                         Layout Export
***************************************************************************/


static void iLayoutFindNamedElem( struct libData *data, Ihandle *ih, Iarray* names_array)
{
  Ihandle *child;
  char *name;
  Ihandle **named_elem = NULL;

  /* this already sorts the elements in the order of dependency */

  for (child = ih->firstchild; child; child = child->brother)
  {
    if ( ! (child->flags & IUP_INTERNAL))
      iLayoutFindNamedElem( data, child, names_array );
  }

  name = iLayoutGetName( data, ih );
  if (name)
  {
    int count = iupArrayCount( data, names_array );
    named_elem = iupArrayAdd( data, names_array, 1 );
    named_elem[count] = ih;
  }
}

static void iLayoutExportDialog( struct libData *data, Ihandle *dialog, const char *dst_filename, int export_format)
{
  int count;
  char *name;
  Iarray* names_array;
  Ihandle **named_elem;
  FILE* file;
  char *title = NULL;

  names_array = iupArrayCreate( data, 1024, sizeof(Ihandle*));  /* just set an initial size, but count is 0 */

  /* can be an empty dialog */
  if (dialog->firstchild)
  {
    /* lists all elements of the dialog that have names */
    iLayoutFindNamedElem( data, dialog, names_array );
  }

  count = iupArrayCount( data, names_array );
  named_elem = iupArrayGetData( data, names_array );

  file = fopen(dst_filename, "wb" );
  if ( ! file)
  {
    iupArrayDestroy( data, names_array );
    return;
  }

  if (export_format == IUP_LAYOUT_EXPORT_LUA)
  {
    title = iupStrFileGetTitle(dst_filename );
    iLayoutRemoveExt( data, title, "lua" );
    iupStrReplaceReserved(title, '_' );

    name = amy_IupGetName( data, dialog );
    if ( ! name)
    {
      iupAttribSetStr( data, dialog, "_IUP_DIALOG_NAME", title );
      name = iupAttribGet( data, dialog, "_IUP_DIALOG_NAME" );

      named_elem = iupArrayInc( data, names_array );
      named_elem[count] = dialog;
      count++;
    }

    fprintf(file, "--   Generated by amy_IupLayoutDialog export to Lua.\n\n" );
  }
  else if (export_format == IUP_LAYOUT_EXPORT_C)
  {
    title = iupStrFileGetTitle(dst_filename );
    iLayoutRemoveExt( data, title, "c" );
    iupStrReplaceReserved(title, '_' );

    name = amy_IupGetName( data, dialog );
    if ( ! name)
    {
      iupAttribSetStr( data, dialog, "_IUP_DIALOG_NAME", title );
      name = iupAttribGet( data, dialog, "_IUP_DIALOG_NAME" );

      named_elem = iupArrayInc( data, names_array );
      named_elem[count] = dialog;
      count++;
    }

    fprintf(file, "/*   Generated by amy_IupLayoutDialog export to C.   */\n\n" );

    fprintf(file, "#include <stdlib.h>\n" );
    fprintf(file, "#include <iup.h>\n\n" );
  }
  else /* IUP_LAYOUT_EXPORT_LED */
  {
    name = amy_IupGetName( data, dialog );
    if ( ! name)
    {
      title = iupStrFileGetTitle(dst_filename );
      iLayoutRemoveExt( data, title, "led" );

      iupAttribSetStr( data, dialog, "_IUP_DIALOG_NAME", title );
      name = iupAttribGet( data, dialog, "_IUP_DIALOG_NAME" );

      named_elem = iupArrayInc( data, names_array );
      named_elem[count] = dialog;
      count++;
    }

    fprintf(file, "#   Generated by amy_IupLayoutDialog export to LED.\n\n" );
  }

  if (export_format == IUP_LAYOUT_EXPORT_LUA)
  {
    fprintf(file, "function create_dialog_%s( data )\n", title );
  }
  else if (export_format == IUP_LAYOUT_EXPORT_C)
  {
    fprintf(file, "Ihandle *create_dialog_%s(void)\n", title );
    fprintf(file, "{\n" );
  }

  iupLayoutExportNamedElemList( data, file, named_elem, count, export_format, 0 );  /* export the class attributes that changed, no custom attributes */

  if (export_format == IUP_LAYOUT_EXPORT_LUA)
  {
    fprintf(file, "\n" );
    fprintf(file, "  return %s\n", name );  /* return the dialog */
    fprintf(file, "end\n" );
  }
  else if (export_format == IUP_LAYOUT_EXPORT_C)
  {
    fprintf(file, "\n" );
    fprintf(file, "  return %s;\n", name );  /* return the dialog */
    fprintf(file, "}\n" );
  }

  if (title)
    free(title );
  iupArrayDestroy( data, names_array );
  fclose(file );
}

static int iLayoutGetExportFile( struct libData *data, Ihandle *parent, char *filename)
{
  Ihandle *file_dlg = 0;
  int ret;
  char filter[4096] = "*.*";
  static char dir[4096] = "";  /* static will make the dir persist from one call to another if not defined */

  file_dlg = amy_IupFileDlg( data );

  iupStrFileNameSplit(filename, dir, filter );

  amy_IupSetAttribute( data, file_dlg, "FILTER", filter );
  amy_IupSetAttribute( data, file_dlg, "DIRECTORY", dir );
  amy_IupSetAttribute( data, file_dlg, "DIALOGTYPE", "SAVE" );
  amy_IupSetAttribute( data, file_dlg, "ALLOWNEW", "YES" );
  amy_IupSetAttribute( data, file_dlg, "NOCHANGEDIR", "YES" );
  amy_IupSetAttributeHandle( data, file_dlg, "PARENTDIALOG", parent );
  amy_IupSetAttribute( data, file_dlg, "ICON", amy_IupGetGlobal( data, "ICON" ));

  amy_IupPopup( data, file_dlg, IUP_CENTERPARENT, IUP_CENTERPARENT );

  ret = amy_IupGetInt( data, file_dlg, "STATUS" );
  if (ret != -1)
  {
    char *value = amy_IupGetAttribute( data, file_dlg, "VALUE" );
    if (value)
    {
      strcpy(filename, value );
      iupStrFileNameSplit(filename, dir, NULL );
    }
  }

  amy_IupDestroy( data, file_dlg );

  return ret;
}


/***************************************************************************
                             Layout Dialog Menus
***************************************************************************/

static void iLayoutUpdateTitle( struct libData *data, Ihandle *dlg, iLayoutDialog *layoutdlg)
{
  if ( layoutdlg->dialog)
  {
    char *title = iupAttribGetLocal( data, layoutdlg->dialog, "TITLE" );
    char *name = iLayoutGetName( data, layoutdlg->dialog );
    if (title)
    {
      if (name)
        amy_IupSetStrf( data, dlg, "TITLE", "Dialog Layout - \"%.50s\" (%.50s)", title, name );
      else
        amy_IupSetStrf( data, dlg, "TITLE", "Dialog Layout - \"%.50s\"", title );
    }
    else
    {
      if (name)
        amy_IupSetStrf( data, dlg, "TITLE", "Dialog Layout - (%.50s)", name );
      else
        amy_IupSetAttribute( data, dlg, "TITLE", "Dialog Layout" );
    }
  }
  else
    amy_IupSetAttribute( data, dlg, "TITLE", "Dialog Layout" );
}

static int iLayoutMenuNew_CB( struct libData *data, Ihandle *ih )
{
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  if ( layoutdlg->destroy)
    amy_IupDestroy( data, layoutdlg->dialog );
  layoutdlg->dialog = amy_IupDialog( data, NULL );
  iLayoutUpdateTitle( data, dlg, layoutdlg );
  layoutdlg->destroy = 1;
  iLayoutTreeRebuild( data, layoutdlg );
  return IUP_DEFAULT;
}

static int iLayoutMenuRebuildTree_CB( struct libData *data, Ihandle *ih)
{
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  /* rebuild tree and redraw canvas */
  iLayoutTreeRebuild( data, layoutdlg );
  return IUP_DEFAULT;
}

static int iLayoutMenuExportLED_CB( struct libData *data, Ihandle *ih)
{
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  char filename[4096] = "*.led";
  int ret = iLayoutGetExportFile( data, dlg, filename );
  if (ret != -1)
    iLayoutExportDialog( data, layoutdlg->dialog, filename, IUP_LAYOUT_EXPORT_LED );
  return IUP_DEFAULT;
}

static int iLayoutMenuExportLua_CB( struct libData *data, Ihandle *ih)
{
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  char filename[4096] = "*.lua";
  int ret = iLayoutGetExportFile( data, dlg, filename );
  if (ret != -1)
    iLayoutExportDialog( data, layoutdlg->dialog, filename, IUP_LAYOUT_EXPORT_LUA );
  return IUP_DEFAULT;
}

static int iLayoutMenuExportC_CB( struct libData *data, Ihandle *ih)
{
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  char filename[4096] = "*.c";
  int ret = iLayoutGetExportFile( data, dlg, filename );
  if (ret != -1)
    iLayoutExportDialog( data, layoutdlg->dialog, filename, IUP_LAYOUT_EXPORT_C );
  return IUP_DEFAULT;
}

static int iLayoutMenuClose_CB( struct libData *data, Ihandle *ih)
{
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  if ( amy_IupGetInt( data, dlg, "DESTROYWHENCLOSED" ))
  {
    amy_IupDestroy( data, dlg );
    return IUP_IGNORE;
  }
  else
  {
    amy_IupHide( data, dlg );
    return IUP_DEFAULT;
  }
}

static int iLayoutMenuShowTree_CB( struct libData *data, Ihandle *ih)
{
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  Ihandle *split = amy_IupGetChild( data, amy_IupGetChild( data, dlg, 0), 0 );
  if ( ! amy_IupGetInt( data, ih, "VALUE" ))
    amy_IupSetAttribute( data, split, "VALUE", "0" );
  else
    amy_IupSetAttribute( data, split, "VALUE", "300" );
  return IUP_DEFAULT;
}

static int iLayoutMenuGlobals_CB( struct libData *data, Ihandle *ih)
{
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  if ( ! layoutdlg->globals)
  {
    layoutdlg->globals = amy_IupGlobalsDialog( data );
    amy_IupSetAttributeHandle( data, layoutdlg->globals, "PARENTDIALOG", dlg );
  }
  amy_IupShow( data, layoutdlg->globals );
  return IUP_DEFAULT;
}

static int iLayoutMenuRefresh_CB( struct libData *data, Ihandle *ih)
{
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  iLayoutRefreshLayout( data, layoutdlg );
  return IUP_DEFAULT;
}

static int iLayoutMenuReset_CB( struct libData *data, Ihandle *ih)
{
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  amy_IupSetAttribute( data, layoutdlg->dialog, "SIZE", NULL );
  iLayoutRefreshLayout( data, layoutdlg );
  return IUP_DEFAULT;
}

static int iLayoutTimerAutoRedraw_CB( struct libData *data, Ihandle *ih)
{
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, ih, "_IUP_LAYOUTDIALOG" );
  /* redraw canvas */
  amy_IupRedraw( data, iLayoutGetCanvas( data, layoutdlg), 0 );
  return IUP_DEFAULT;
}

static int iLayoutMenuShowHidden_CB( struct libData *data, Ihandle *ih)
{
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  if ( ! amy_IupGetInt( data, ih, "VALUE" ))
    iupAttribSet( data, dlg, "SHOWHIDDEN", "No" );
  else
    iupAttribSet( data, dlg, "SHOWHIDDEN", "Yes" );
  /* redraw canvas */
  amy_IupUpdate( data, iLayoutGetCanvas( data, layoutdlg));
  return IUP_DEFAULT;
}

static int iLayoutMenuShowInternal_CB( struct libData *data, Ihandle *ih)
{
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  if ( ! amy_IupGetInt( data, ih, "VALUE" ))
    iupAttribSet( data, dlg, "SHOWINTERNAL", "No" );
  else
    iupAttribSet( data, dlg, "SHOWINTERNAL", "Yes" );
  /* rebuild tree and redraw canvas */
  iLayoutTreeRebuild( data, layoutdlg );
  return IUP_DEFAULT;
}

static int iLayoutMenuAutoRedraw_CB( struct libData *data, Ihandle *ih)
{
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  if ( amy_IupGetInt( data, layoutdlg->timer, "RUN" ))
    amy_IupSetAttribute( data, layoutdlg->timer, "RUN", "No" );
  else
    amy_IupSetAttribute( data, layoutdlg->timer, "RUN", "Yes" );
  return IUP_DEFAULT;
}

static int iLayoutMenuRedraw_CB( struct libData *data, Ihandle *ih)
{
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  amy_IupRedraw( data, layoutdlg->dialog, 1 );
  return IUP_DEFAULT;
}

static int iLayoutGetParamOpacity_CB( struct libData *data, Ihandle *dialog, int param_index, void *user_data)
{
  if (param_index == 0)
  {
    Ihandle *dlg = (Ihandle*)user_data;
    Ihandle *param = (Ihandle*) amy_IupGetAttribute( data, dialog, "PARAM0" );
    int opacity = amy_IupGetInt( data, param, "VALUE" );
    amy_IupSetInt( data, dlg, "OPACITY", opacity );
  }
  return 1;
}

static int iLayoutMenuOpacity_CB( struct libData *data, Ihandle *ih)
{
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  int opacity = amy_IupGetInt( data, dlg, "OPACITY" );
  if (opacity == 0)
    opacity = 255;

  amy_IupStoreGlobal( data, "_IUP_OLD_PARENTDIALOG", amy_IupGetGlobal( data, "PARENTDIALOG" ));
  amy_IupSetAttributeHandle( data, NULL, "PARENTDIALOG", dlg );

  if ( amy_IupGetParam( data, "Dialog Layout", iLayoutGetParamOpacity_CB, dlg,
                  "Opacity: %i[0,255]\n",
                  &opacity, NULL))
  {

    if (opacity == 0 || opacity == 255)
      amy_IupSetAttribute( data, dlg, "OPACITY", NULL );
    else
      amy_IupSetInt( data, dlg, "OPACITY", opacity );
  }

  amy_IupStoreGlobal( data, "PARENTDIALOG", amy_IupGetGlobal( data, "_IUP_OLD_PARENTDIALOG" ));
  amy_IupSetGlobal( data, "_IUP_OLD_PARENTDIALOG", NULL );

  return IUP_DEFAULT;
}

static int iLayoutMenuFindElement_CB( struct libData *data, Ihandle *ih)
{
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  Ihandle *find_dlg = (Ihandle*) amy_IupGetAttribute( data, dlg, "FIND_ELEM_DIALOG" );
  Ihandle *tree = amy_IupGetDialogChild( data, ih, "TREE" );

  if ( ! find_dlg)
  {
    find_dlg = iupLayoutFindElementDialog( data, tree, layoutdlg->dialog );
    amy_IupSetAttribute( data, dlg, "FIND_ELEM_DIALOG", (char*)find_dlg );
  }

  amy_IupSetAttribute( data, amy_IupGetDialogChild( data, find_dlg, "FIND_NAME" ), "ACTIVE", "YES" ); /* we are going to disable it in other situations */

  amy_IupShow( data, find_dlg );

  return IUP_DEFAULT;
}

static int iLayoutMenuShow_CB( struct libData *data, Ihandle *ih)
{
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  amy_IupShow( data, layoutdlg->dialog );
  return IUP_DEFAULT;
}

static int iLayoutMenuHide_CB( struct libData *data, Ihandle *ih)
{
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  amy_IupHide( data, layoutdlg->dialog );
  return IUP_DEFAULT;
}

static int iLayoutDialogGetDialogs( struct libData *data, Ihandle **dlg_list, char **dlg_list_str, int count, int only_visible)
{
  int i;
  Ihandle *dlg;

  for (dlg = iupDlgListFirst( data ), i = 0; dlg && i < count; dlg = iupDlgListNext( data ))
  {
    if ( ! only_visible ||
        (dlg->handle && amy_IupGetInt( data, dlg, "VISIBLE" )))
    {
      dlg_list[i] = dlg;
      dlg_list_str[i] = iupStrDup(iupLayoutGetElementTitle( data, dlg ));
      i++;
    }
  }

  return i;
}

static void iLayoutDialogLoad( struct libData *data, Ihandle *dlg, iLayoutDialog *layoutdlg, int only_visible)
{
  int ret, count, i;
  Ihandle **dlg_list;
  char **dlg_list_str;

  if (only_visible)
    count = iupDlgListVisibleCount( data );
  else
    count = iupDlgListCount( data );

  dlg_list = (Ihandle**)malloc(count*sizeof(Ihandle*));
  dlg_list_str = (char**)malloc(count*sizeof(char*));

  i = iLayoutDialogGetDialogs( data, dlg_list, dlg_list_str, count, only_visible );

  iupASSERT(i == count );
  if (i != count)
    count = i;

  amy_IupStoreGlobal( data, "_IUP_OLD_PARENTDIALOG", amy_IupGetGlobal( data, "PARENTDIALOG" ));
  amy_IupSetAttributeHandle( data, NULL, "PARENTDIALOG", dlg );

  ret = amy_IupListDialog( data, 1, "Dialogs", count, (const char**)dlg_list_str, 1, 15, count < 15 ? count + 1 : 15, NULL );

  amy_IupStoreGlobal( data, "PARENTDIALOG", amy_IupGetGlobal( data, "_IUP_OLD_PARENTDIALOG" ));
  amy_IupSetGlobal( data, "_IUP_OLD_PARENTDIALOG", NULL );

  if (ret != -1)
  {
    int w = 0, h = 0;

    if ( layoutdlg->destroy)
      amy_IupDestroy( data, layoutdlg->dialog );
    layoutdlg->dialog = dlg_list[ret];
    iLayoutUpdateTitle( data, dlg, layoutdlg );
    layoutdlg->destroy = 0;

    amy_IupGetIntInt( data, layoutdlg->dialog, "CLIENTSIZE", &w, &h );
    if (w && h)
    {
      Ihandle *canvas = iLayoutGetCanvas( data, layoutdlg );
      amy_IupSetfAttribute( data, canvas, "USERSIZE", "%dx%d", w, h );
      amy_IupSetAttribute( data, dlg, "RASTERSIZE", NULL );

      amy_IupShow( data, dlg );  /* resize the layout dialog to show the hole layout */

      amy_IupSetAttribute( data, canvas, "USERSIZE", NULL );
    }
  }

  for (i = 0; i < count; i++)
    free(dlg_list_str[i] );

  free(dlg_list );
  free(dlg_list_str );
}

static int iLayoutMenuLoad_CB( struct libData *data, Ihandle *ih)
{
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  iLayoutDialogLoad( data, dlg, layoutdlg, 0 );
  iLayoutTreeRebuild( data, layoutdlg );
  return IUP_DEFAULT;
}

static int iLayoutMenuLoadVisible_CB( struct libData *data, Ihandle *ih)
{
  Ihandle *dlg = amy_IupGetDialog( data, ih );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  iLayoutDialogLoad( data, dlg, layoutdlg, 1 );
  iLayoutTreeRebuild( data, layoutdlg );
  return IUP_DEFAULT;
}


/***************************************************************************
                               Canvas Drawing
***************************************************************************/


static void iLayoutDrawElement( struct libData *data, IdrawCanvas* dc, Ihandle *ih, int marked, int native_parent_x, int native_parent_y, int clip_x1, int clip_y1, int clip_x2, int clip_y2)
{
  int x, y, w, h;
  char *bgcolor;
  long color, fg, fg_void, bg, fg_max;
  int box_x1, box_y1, box_x2, box_y2;

  x = ih->x + native_parent_x;
  y = ih->y + native_parent_y;
  w = ih->currentwidth;
  h = ih->currentheight;
  if (w <= 0) w = 1;
  if (h <= 0) h = 1;

  box_x1 = x;
  box_y1 = y;
  box_x2 = x + w - 1;
  box_y2 = y + h - 1;

  if (box_x1 > clip_x2) return;
  if (box_y1 > clip_y2) return;
  if (box_x2 < clip_x1) return;
  if (box_y2 < clip_y1) return;

  if (box_x1 < clip_x1) box_x1 = clip_x1;
  if (box_y1 < clip_y1) box_y1 = clip_y1;
  if (box_x2 > clip_x2) box_x2 = clip_x2;
  if (box_y2 > clip_y2) box_y2 = clip_y2;

  bg = iupDrawColor(255, 255, 255, 255 );  /* background color */
  fg = iupDrawColor(0, 0, 0, 255 );        /* foreground color */
  fg_void = iupDrawColor(160, 160, 160, 255 );  /* foreground color for void elements */
  fg_max = iupDrawColor(255, 0, 0, 255 );      /* foreground color for elements that are maximizing parent size */

  bgcolor = amy_IupGetAttribute( data, ih, "BGCOLOR" );
  if (bgcolor && ih->iclass->nativetype != IUP_TYPEVOID)
  {
    color = iupDrawStrToColor( data, bgcolor, bg );
    iupdrvDrawRectangle( data, dc, box_x1, box_y1, box_x2, box_y2, color, IUP_DRAW_FILL, 1 );
  }

  if (ih->iclass->nativetype == IUP_TYPEVOID)
    iupdrvDrawRectangle( data, dc, box_x1, box_y1, box_x2, box_y2, fg_void, IUP_DRAW_STROKE_DASH, 1 );
  else
    iupdrvDrawRectangle( data, dc, box_x1, box_y1, box_x2, box_y2, fg, IUP_DRAW_STROKE, 1 );

  iupdrvDrawSetClipRect( data, dc, box_x1, box_y1, box_x2, box_y2 );

  if (ih->iclass->childtype == IUP_CHILDNONE)
  {
    int pw, ph;
    amy_IupGetIntInt( data, ih->parent, "CLIENTSIZE", &pw, &ph );

    if (ih->currentwidth == pw && ih->currentwidth == ih->naturalwidth)
    {
      iupdrvDrawLine( data, dc, x + 1, y + 1, x + w - 2, y + 1, fg_max, IUP_DRAW_STROKE, 1 );
      iupdrvDrawLine( data, dc, x + 1, y + h - 2, x + w - 2, y + h - 2, fg_max, IUP_DRAW_STROKE, 1 );
    }

    if (ih->currentheight == ph && ih->currentheight == ih->naturalheight)
    {
      iupdrvDrawLine( data, dc, x + 1, y + 1, x + 1, y + h - 2, fg_max, IUP_DRAW_STROKE, 1 );
      iupdrvDrawLine( data, dc, x + w - 2, y + 1, x + w - 2, y + h - 2, fg_max, IUP_DRAW_STROKE, 1 );
    }
  }
  else if (ih->iclass->nativetype != IUP_TYPEVOID)
  {
    /* if ih is a Tabs, position the title accordingly */
    if ( amy_IupClassMatch( data, ih, "tabs" ))
    {
      /* TABORIENTATION is ignored */
      char *tabtype = amy_IupGetAttribute( data, ih, "TABTYPE" );
      if (iupStrEqualNoCase(tabtype, "BOTTOM" ))
      {
        int cw = 0, ch = 0;
        amy_IupGetIntInt( data, ih, "CLIENTSIZE", &cw, &ch );
        y += ch;  /* position after the client area */
      }
      else if (iupStrEqualNoCase(tabtype, "RIGHT" ))
      {
        int cw = 0, ch = 0;
        amy_IupGetIntInt( data, ih, "CLIENTSIZE", &cw, &ch );
        x += cw;  /* position after the client area */
      }
    }
  }

  /* always draw the image first */
  if (ih->iclass->nativetype != IUP_TYPEVOID)
  {
    char *title, *image;

    image = amy_IupGetAttribute( data, ih, "IMAGE0" );  /* Tree root node title */
    if ( ! image)
      image = amy_IupGetAttribute( data, ih, "TABIMAGE0" );  /* Tabs first tab image */
    if (image)
    {
      /* returns the image of the active tab */
      int pos = amy_IupGetInt( data, ih, "VALUEPOS" );
      image = amy_IupGetAttributeId( data, ih, "TABIMAGE", pos );
    }
    if ( ! image)
      image = amy_IupGetAttribute( data, ih, "IMAGE" );
    if (image)
    {
      char *position;
      int img_w = 0, img_h = 0;

      iupImageGetInfo( data, image, &img_w, &img_h, NULL );

      iupdrvDrawImage( data, dc, image, 0, bgcolor, x + 1, y + 1, img_w, img_h );

      position = amy_IupGetAttribute( data, ih, "IMAGEPOSITION" );  /* used only for buttons */
      if (position &&
          (iupStrEqualNoCase(position, "BOTTOM" ) ||
          iupStrEqualNoCase(position, "TOP" )))
          y += img_h;
      else
        x += img_w;  /* position text usually at right */
    }

    title = amy_IupGetAttribute( data, ih, "0:0" );  /* Matrix title cell */
    if ( ! title)
      title = amy_IupGetAttribute( data, ih, "1" );  /* List first item */
    if ( ! title)
      title = amy_IupGetAttribute( data, ih, "TITLE0" );  /* Tree root node title */
    if ( ! title)
    {
      title = amy_IupGetAttribute( data, ih, "TABTITLE0" );  /* Tabs first tab title */
      if (title)
      {
        /* returns the title of the active tab */
        int pos = amy_IupGetInt( data, ih, "VALUEPOS" );
        title = amy_IupGetAttributeId( data, ih, "TABTITLE", pos );
      }
    }
    if ( ! title)
      title = iupAttribGetLocal( data, ih, "TITLE" );
    if (title)
    {
      int len;
      iupStrNextLine(title, &len );  /* get the size of the first line */
      color = iupDrawStrToColor( data,  amy_IupGetAttribute( data, ih, "FGCOLOR" ), fg );
      iupdrvDrawText( data, dc, title, len, x + 1, y + 1, w, h, color, amy_IupGetAttribute( data, ih, "FONT" ), IUP_DRAW_LEFT, 0 );
    }

    if (ih->iclass->childtype == IUP_CHILDNONE &&
        !title && !image)
    {
      if ( amy_IupClassMatch( data, ih, "progressbar" ) || amy_IupClassMatch( data, ih, "gauge" ))
      {
        double min = amy_IupGetDouble( data, ih, "MIN" );
        double max = amy_IupGetDouble( data, ih, "MAX" );
        double val = amy_IupGetDouble( data, ih, "VALUE" );
        color = iupDrawStrToColor( data,  amy_IupGetAttribute( data, ih, "FGCOLOR" ), fg );
        if (iupStrEqualNoCase( amy_IupGetAttribute( data, ih, "ORIENTATION" ), "VERTICAL" ))
        {
          int ph = (int)(((max - val)*(h - 5)) / (max - min));
          iupdrvDrawRectangle( data, dc, x + 2, y + 2, x + w - 3, y + ph, color, IUP_DRAW_FILL, 1 );
        }
        else
        {
          int pw = (int)(((val - min)*(w - 5)) / (max - min));
          iupdrvDrawRectangle( data, dc, x + 2, y + 2, x + pw, y + h - 3, color, IUP_DRAW_FILL, 1 );
        }
      }
      else if ( amy_IupClassMatch( data, ih, "val" ))
      {
        double min = amy_IupGetDouble( data, ih, "MIN" );
        double max = amy_IupGetDouble( data, ih, "MAX" );
        double val = amy_IupGetDouble( data, ih, "VALUE" );
        color = iupDrawStrToColor( data,  amy_IupGetAttribute( data, ih, "FGCOLOR" ), fg );
        if (iupStrEqualNoCase( amy_IupGetAttribute( data, ih, "ORIENTATION" ), "VERTICAL" ))
        {
          int ph = (int)(((max - val)*(h - 5)) / (max - min));
          iupdrvDrawRectangle( data, dc, x + 2, y + ph - 1, x + w - 3, y + ph + 1, color, IUP_DRAW_FILL, 1 );
        }
        else
        {
          int pw = (int)(((val - min)*(w - 5)) / (max - min));
          iupdrvDrawRectangle( data, dc, x + pw - 1, y + 2, x + pw + 1, y + h - 3, color, IUP_DRAW_FILL, 1 );
        }
      }
    }
  }

  iupdrvDrawResetClip( data, dc );

  if (marked)
    iupdrvDrawSelectRect( data, dc, box_x1, box_y1, box_x2, box_y2 );
}

static int iLayoutElementIsVisible( struct libData *data, Ihandle *ih, int dlgvisible)
{
  if (dlgvisible)
    return iupStrBoolean(iupAttribGetLocal( data, ih, "VISIBLE" ));
  else
  {
    /* can not check at native implementation because it will be always not visible */
    char *value = iupAttribGet( data, ih, "VISIBLE" );
    if ( ! value)
      return 1; /* default is visible */
    else
      return iupStrBoolean(value );
  }
}

static void iLayoutDrawElementTree( struct libData *data, IdrawCanvas* dc, int showhidden, int dlgvisible, int shownotmapped, int showinternal, Ihandle *mark, Ihandle *ih, int native_parent_x, int native_parent_y, int clip_x1, int clip_y1, int clip_x2, int clip_y2)
{
  Ihandle *child;
  int dx, dy;

  if ((showhidden || iLayoutElementIsVisible( data, ih, dlgvisible)) &&
      (shownotmapped || ih->handle))
  {
    /* draw the element */
    iLayoutDrawElement( data, dc, ih, ih == mark, native_parent_x, native_parent_y, clip_x1, clip_y1, clip_x2, clip_y2 );

    /* if ih is a native parent, then update the offset and clipping */
    if (ih->iclass->childtype != IUP_CHILDNONE && ih->iclass->nativetype != IUP_TYPEVOID)
    {
      dx = 0, dy = 0;
      amy_IupGetIntInt( data, ih, "CLIENTOFFSET", &dx, &dy );
      native_parent_x += ih->x + dx;
      native_parent_y += ih->y + dy;

      if (native_parent_x > clip_x1) clip_x1 = native_parent_x;
      if (native_parent_y > clip_y1) clip_y1 = native_parent_y;
      if (native_parent_x + ih->currentwidth < clip_x2) clip_x2 = native_parent_x + ih->currentwidth;
      if (native_parent_y + ih->currentheight < clip_y2) clip_y2 = native_parent_y + ih->currentheight;
    }

    /* draw its children */
    /* if ih is a Zbox like, then draw only the active child */
    if ( amy_IupClassMatch( data, ih, "zbox" ) || amy_IupClassMatch( data, ih, "tabs" ) || amy_IupClassMatch( data, ih, "flattabs" ))
    {
      child = (Ihandle*) amy_IupGetAttribute( data, ih, "VALUE_HANDLE" );
      if (child)
        iLayoutDrawElementTree( data, dc, showhidden, dlgvisible, shownotmapped, showinternal, mark, child, native_parent_x, native_parent_y, clip_x1, clip_y1, clip_x2, clip_y2 );
    }
    else
    {
      for (child = ih->firstchild; child; child = child->brother)
      {
        if ( ! (child->flags & IUP_INTERNAL) || showinternal)
          iLayoutDrawElementTree( data, dc, showhidden, dlgvisible, shownotmapped, showinternal, mark, child, native_parent_x, native_parent_y, clip_x1, clip_y1, clip_x2, clip_y2 );
      }
    }
  }
}

static void iLayoutDrawDialog( struct libData *data, iLayoutDialog *layoutdlg, int showhidden, int showinternal, IdrawCanvas* dc, Ihandle *mark, int posx, int posy)
{
  int w, h;

  iupdrvDrawGetSize( data, dc, &w, &h );
  iupdrvDrawRectangle( data, dc, 0, 0, w - 1, h - 1, iupDrawColor(255, 255, 255, 255), IUP_DRAW_FILL, 1 );

  /* draw the dialog */
  amy_IupGetIntInt( data, layoutdlg->dialog, "CLIENTSIZE", &w, &h );
  iupdrvDrawRectangle( data, dc, 0, 0, w - 1, h - 1, iupDrawColor(0, 0, 0, 255), IUP_DRAW_STROKE, 1 );

  if ( layoutdlg->dialog->firstchild)
  {
    int native_parent_x = 0, native_parent_y = 0;
    int shownotmapped = layoutdlg->dialog->handle == NULL;  /* only show not mapped if dialog is also not mapped */
    int dlgvisible = amy_IupGetInt( data, layoutdlg->dialog, "VISIBLE" );
    amy_IupGetIntInt( data, layoutdlg->dialog, "CLIENTOFFSET", &native_parent_x, &native_parent_y );
    native_parent_x -= posx;
    native_parent_y -= posy;
    iLayoutDrawElementTree( data, dc, showhidden, dlgvisible, shownotmapped, showinternal, mark, layoutdlg->dialog->firstchild, native_parent_x, native_parent_y, native_parent_x, native_parent_y, native_parent_x + layoutdlg->dialog->currentwidth-1, native_parent_y + layoutdlg->dialog->currentheight -1 );
  }
}

static void iLayoutDrawCursor( struct libData *data, Ihandle *canvas, IdrawCanvas* dc, int posx, int posy)
{
  if (iupAttribGet( data, canvas, "INSERTCURSOR" ))
  {
    long fg_insert = iupDrawColor(0, 255, 0, 255 );

    if (iupAttribGet( data, canvas, "INSERTCURSOR_POINT" ))
    {
      int x, y;
      int IC_PS = 10;
      sscanf(iupAttribGet( data, canvas, "INSERTCURSOR_POINT" ), "%d,%d", &x, &y );
      x -= posx;
      y -= posy;

      iupdrvDrawLine( data, dc, x - IC_PS, y, x + IC_PS, y, fg_insert, IUP_DRAW_STROKE, 2 );
      iupdrvDrawLine( data, dc, x, y - IC_PS, x, y + IC_PS, fg_insert, IUP_DRAW_STROKE, 2 );

      IC_PS = 3;
      iupdrvDrawArc( data, dc, x - IC_PS, y - IC_PS, x + IC_PS, y + IC_PS, 0, 360, fg_insert, IUP_DRAW_STROKE, 2 );
    }
    else if (iupAttribGet( data, canvas, "INSERTCURSOR_LINE" ))
    {
      int IC_PS = 3;
      int x1, x2, y1, y2, xc, yc;
      sscanf(iupAttribGet( data, canvas, "INSERTCURSOR_LINE" ), "%d,%d,%d,%d", &x1, &y1, &x2, &y2 );
      x1 -= posx;
      y1 -= posy;
      x2 -= posx;
      y2 -= posy;

      iupdrvDrawLine( data, dc, x1, y1, x2, y2, fg_insert, IUP_DRAW_STROKE, 2 );

      xc = (x1 + x2) / 2;
      yc = (y1 + y2) / 2;
      iupdrvDrawArc( data, dc, xc - IC_PS, yc - IC_PS, xc + IC_PS, yc + IC_PS, 0, 360, fg_insert, IUP_DRAW_STROKE, 2 );
    }
  }
}

static Ihandle *iLayoutGetSelectedElement( struct libData *data, Ihandle *dlg )
{
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  int id = amy_IupGetInt( data, layoutdlg->tree, "VALUE" );
  Ihandle *elem = (Ihandle*) amy_IupTreeGetUserId( data,  layoutdlg->tree, id );
  return elem;
}

static int iLayoutCanvasRedraw_CB( struct libData *data, Ihandle *canvas, float fposx, float fposy)
{
  Ihandle *dlg = amy_IupGetDialog( data, canvas );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  IdrawCanvas* dc = iupdrvDrawCreateCanvas( data, canvas );
  int showhidden = amy_IupGetInt( data, dlg, "SHOWHIDDEN" );
  int showinternal = amy_IupGetInt( data, dlg, "SHOWINTERNAL" );
  Ihandle *mark = iLayoutGetSelectedElement( data, dlg );

  iLayoutDrawDialog( data, layoutdlg, showhidden, showinternal, dc, mark, (int)fposx, (int)fposy );

  iLayoutDrawCursor( data, canvas, dc, (int)fposx, (int)fposy );

  iupdrvDrawFlush( data, dc );

  iupdrvDrawKillCanvas( data, dc );

  return IUP_DEFAULT;
}


/***************************************************************************
                          Context Menu
***************************************************************************/

static int iLayoutAttribChanged_CB( struct libData *data, Ihandle *properties, char *name)
{
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, properties, "_IUP_LAYOUTDIALOG" );
  Ihandle *elem = (Ihandle*) amy_IupGetAttribute( data, properties, "ELEM" );
  Ihandle *dlg = amy_IupGetDialog( data, layoutdlg->tree );
  IFns cb = (IFns) amy_IupGetCallback( data, dlg, "ATTRIBCHANGED_CB" );

  if (cb)
  {
    amy_IupSetAttribute( data, dlg, "ELEM", (char*)elem );
    cb( data,dlg, name );
    amy_IupSetAttribute( data, dlg, "ELEM", NULL );
  }

  layoutdlg->changed = 1;

  /* redraw canvas */
  amy_IupUpdate( data, iLayoutGetCanvas( data, layoutdlg));
  return IUP_DEFAULT;
}

static int iLayoutContextMenuProperties_CB( struct libData *data, Ihandle *menu)
{
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDIALOG" );
  Ihandle *elem = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTCONTEXTELEMENT" );
  Ihandle *dlg = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDLG" );

  if ( ! layoutdlg->properties)
  {
    layoutdlg->properties = amy_IupElementPropertiesDialog( data, dlg, elem );
    amy_IupSetAttribute( data, layoutdlg->properties, "_IUP_LAYOUTDIALOG", (char*)layoutdlg );
    amy_IupSetCallback( data, layoutdlg->properties, "ATTRIBCHANGED_CB", (Icallback)iLayoutAttribChanged_CB );
  }
  else
    iupLayoutPropertiesUpdate( data, layoutdlg->properties, elem );

  amy_IupSetAttribute( data, layoutdlg->properties, "ELEM", (char*)elem );

  amy_IupShow( data, layoutdlg->properties );

  return IUP_DEFAULT;
}

static void iLayoutTreeUpdateTitle( struct libData *data, iLayoutDialog *layoutdlg, Ihandle *ih)
{
  int id = amy_IupTreeGetId( data, layoutdlg->tree, ih );
  amy_IupSetAttributeId( data, layoutdlg->tree, "TITLE", id, iupLayoutGetElementTitle( data, ih ));
}

static void iLayoutSaveAttrib( struct libData *data, iLayoutDialog *layoutdlg, Ihandle *elem, const char *name)
{
  if ( ! layoutdlg->destroy && iupAttribGet( data, layoutdlg->dialog, "_IUPLED_FILENAME" ))
  {
    char led_name[200] = "_IUPLED_SAVED_";
    strcat(led_name, name );
    iupAttribSet( data, elem, led_name, "1" );
  }
}

static void iLayoutCallLayoutChangedCb( struct libData *data, iLayoutDialog *layoutdlg, Ihandle *elem)
{
  Ihandle *dlg = amy_IupGetDialog( data, layoutdlg->tree );
  IFnn cb = (IFnn) amy_IupGetCallback( data, dlg, "LAYOUTCHANGED_CB" );
  if (cb)
    cb( data,dlg, elem );
}

static int iLayoutContextMenuHandleName_CB( struct libData *data, Ihandle *menu)
{
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDIALOG" );
  Ihandle *elem = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTCONTEXTELEMENT" );
  char name[512] = "";

  char *elem_name = iLayoutGetName( data, elem );
  if (elem_name)
    strcpy(name, elem_name );

  amy_IupStoreGlobal( data, "_IUP_OLD_PARENTDIALOG", amy_IupGetGlobal( data, "PARENTDIALOG" ));
  amy_IupSetAttributeHandle( data, NULL, "PARENTDIALOG", amy_IupGetDialog( data, layoutdlg->tree));

  if ( amy_IupGetParam( data, "Handle Name", NULL, NULL,
                  "Name: %s{Leave it empty to remove the handle}\n",
                  name, NULL))
  {
    if (name[0] == 0 || name[0] == ' ')
    {
      if (elem_name)
      {
        amy_IupSetHandle( data, elem_name, NULL );
        iLayoutTreeUpdateTitle( data, layoutdlg, elem );
        iLayoutCallLayoutChangedCb( data, layoutdlg, elem );
      }
    }
    else
    {
      Ihandle *old_elem = amy_IupGetHandle( data, name );
      int ret = 1;
      if (old_elem != elem)
        ret = amy_IupMessageAlarm( data, amy_IupGetDialog( data, layoutdlg->tree), "Handle Name", "Name is already associated with another handle. Replace it?", "YESNO" );

      if (ret == 1)
      {
        amy_IupSetHandle( data, name, elem );
        iLayoutTreeUpdateTitle( data, layoutdlg, elem );
        iLayoutCallLayoutChangedCb( data, layoutdlg, elem );
      }
    }
  }

  amy_IupStoreGlobal( data, "PARENTDIALOG", amy_IupGetGlobal( data, "_IUP_OLD_PARENTDIALOG" ));
  amy_IupSetGlobal( data, "_IUP_OLD_PARENTDIALOG", NULL );

  return IUP_DEFAULT;
}

static int iLayoutSelectClassOK_CB( struct libData *data, Ihandle *ih)
{
  iupAttribSet( data, amy_IupGetDialog( data, ih ), "STATUS", "1" );
  return IUP_CLOSE;
}

static int iLayoutSelectClassCancel_CB( struct libData *data, Ihandle *ih)
{
  iupAttribSet( data, amy_IupGetDialog( data, ih ), "STATUS", "-1" );
  return IUP_CLOSE;
}

static int iLayoutSelectClassTreeExecuteLeaf_CB( struct libData *data, Ihandle *ih, int id)
{
  (void)id;
  iupAttribSet( data, amy_IupGetDialog( data, ih ), "STATUS", "1" );
  amy_IupExitLoop( data );
  return IUP_DEFAULT;
}

static const char *iLayoutSelectClassDialog( struct libData *data, Ihandle *parent)
{
  Ihandle *tree, *ok, *dlg, *cancel, *dlg_box, *button_box;
  int last_containers_id, last_standard_id, last_additional_id;
  const char *value = NULL;
  int count, i;
  char** class_list_str, **p_str;

  tree = amy_IupTree( data );
  amy_IupSetAttribute( data, tree, "ADDROOT", "NO" );
  amy_IupSetAttribute( data, tree, "IMAGELEAF", "IMGEMPTY" );
  amy_IupSetAttribute( data, tree, "SIZE", "120x160" );

  ok = amy_IupButton( data, "_@IUP_OK", NULL );
  amy_IupSetStrAttribute( data, ok, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
  amy_IupSetCallback( data, ok, "ACTION", (Icallback)iLayoutSelectClassOK_CB );

  cancel = amy_IupButton( data, "_@IUP_CANCEL", NULL );
  amy_IupSetStrAttribute( data, cancel, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
  amy_IupSetCallback( data, cancel, "ACTION", (Icallback)iLayoutSelectClassCancel_CB );

  button_box = amy_IupHbox( data,
    amy_IupFill( data ),
    ok,
    cancel,
    NULL );
  amy_IupSetAttribute( data, button_box, "MARGIN", "0x0" );
  amy_IupSetAttribute( data, button_box, "NORMALIZESIZE", "HORIZONTAL" );

  dlg_box = amy_IupVbox( data,
    tree,
    button_box,
    NULL );

  amy_IupSetAttribute( data, dlg_box, "MARGIN", "10x10" );
  amy_IupSetAttribute( data, dlg_box, "GAP", "10" );

  dlg = amy_IupDialog( data, dlg_box );

  amy_IupSetCallback( data, tree, "EXECUTELEAF_CB", (Icallback)iLayoutSelectClassTreeExecuteLeaf_CB );

  amy_IupSetStrAttribute( data, dlg, "TITLE", "New Element Class" );
  amy_IupSetAttribute( data, dlg, "MINBOX", "NO" );
  amy_IupSetAttribute( data, dlg, "MAXBOX", "NO" );
  amy_IupSetAttributeHandle( data, dlg, "DEFAULTENTER", ok );
  amy_IupSetAttributeHandle( data, dlg, "DEFAULTESC", cancel );
  amy_IupSetAttributeHandle( data, dlg, "PARENTDIALOG", parent );
  amy_IupSetAttribute( data, dlg, "ICON", amy_IupGetGlobal( data, "ICON" ));

  amy_IupMap( data, dlg );

  amy_IupSetAttribute( data, tree, "ADDBRANCH-1", "Containers" );
  last_containers_id = 0;
  amy_IupSetAttribute( data, tree, "INSERTBRANCH0", "Standard" );
  last_standard_id = 1;
  amy_IupSetAttribute( data, tree, "INSERTBRANCH1", "Additional" );
  last_additional_id = 2;

  count = amy_IupGetAllClasses( data, NULL, 0 );
  class_list_str = (char**)malloc(count * sizeof(char*));

  amy_IupGetAllClasses( data, class_list_str, count );
  qsort(class_list_str, count, sizeof(char*), iLayoutCompareClassNames );

  /* filter the list of classes */
  p_str = class_list_str;
  for (i = 0; i < count; i++)
  {
    Iclass *iclass = iupRegisterFindClass( data, class_list_str[i] );
    if (iclass->nativetype == IUP_TYPEVOID ||
        iclass->nativetype == IUP_TYPECONTROL ||
        iclass->nativetype == IUP_TYPECANVAS)
      *p_str++ = class_list_str[i];
  }
  count = (int)(p_str - class_list_str );

  for (i = 0; i < count; i++)
  {
    char *name = class_list_str[i];
    Iclass *elemClass = iupRegisterFindClass( data, name );
    char constructor[50];

    if (elemClass->cons)
      strcpy(constructor, elemClass->cons );
    else
    {
      strcpy(constructor, name );
      constructor[0] = (char)toupper(constructor[0] );
    }

    if (elemClass->childtype != IUP_CHILDNONE && elemClass->is_internal) /* internal containers */
    {
      amy_IupSetStrAttributeId( data, tree, "ADDLEAF", last_containers_id, constructor );
      last_containers_id++;
      last_standard_id++;
      last_additional_id++;
    }
    else if (elemClass->is_internal)
    {
      amy_IupSetStrAttributeId( data, tree, "ADDLEAF", last_standard_id, constructor );
      last_standard_id++;
      last_additional_id++;
    }
    else /* additional */
    {
      amy_IupSetStrAttributeId( data, tree, "ADDLEAF", last_additional_id, constructor );
      last_additional_id++;
    }
  }

  amy_IupSetAttribute( data, tree, "USERSIZE", NULL );

  amy_IupPopup( data, dlg, IUP_CENTERPARENT, IUP_CENTERPARENT );

  if ( amy_IupGetInt( data, dlg, "STATUS" ) == 1)
  {
    Iclass *elemClass;
    int id = amy_IupGetInt( data, tree, "VALUE" );
    char *name = amy_IupGetAttributeId( data, tree, "TITLE", id );
    iupStrLower(name, name );
    elemClass = iupRegisterFindClass( data, name );
    value = elemClass->name;
  }

  amy_IupDestroy( data, dlg );

  free(class_list_str );
  return value;
}

static int iLayoutElemOptionToggle_cb( struct libData *data, Ihandle *ih_toggle, int state)
{
  if (state == 1)
  {
    iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, ih_toggle, "_IUP_LAYOUTDIALOG" );
    char *name = iupAttribGet( data, ih_toggle, "_IUP_CLASS" );
    if ( ! name)
      layoutdlg->new_elem_class = NULL;
    else
    {
      if ( amy_IupGetInt( data, NULL, "SHIFTKEY" ))
      {
        char *alt_name = iupAttribGet( data, ih_toggle, "_IUP_CLASS_ALT" );
        if (alt_name)
          name = alt_name;
      }

      layoutdlg->new_elem_class = name;
    }
  }

  return IUP_DEFAULT;
}

static void iLayoutError( struct libData *data, iLayoutDialog *layoutdlg, const char *msg )
{
  amy_IupMessageError( data, amy_IupGetDialog( data, layoutdlg->tree), msg );
}

static int iLayoutContextMenuNewInsertBrother_CB( struct libData *data, Ihandle *menu)
{
  Ihandle *dlg = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDLG" );
  const char *name = iLayoutSelectClassDialog( data, dlg );
  if (name)
  {
    iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDIALOG" );
    Ihandle *ref_elem = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTCONTEXTELEMENT" );
    Ihandle *ret_ih = NULL;

    Ihandle *new_ih = amy_IupCreate( data, name );

    /* add as brother after reference */
    if (ref_elem->brother)
      /* add before the brother, so it will be the brother */
      ret_ih = amy_IupInsert( data, ref_elem->parent, ref_elem->brother, new_ih );
    else
      ret_ih = amy_IupAppend( data, ref_elem->parent, new_ih );

    if ( ! ret_ih)
    {
      if (ref_elem->brother)
        iLayoutError( data, layoutdlg, "Insert failed. Invalid operation for this node." );
      else
        iLayoutError( data, layoutdlg, "Append failed. Invalid operation for this node." );
      amy_IupDestroy( data, new_ih );
      return IUP_DEFAULT;
    }

    layoutdlg->changed = 1;

    /* add to the tree */
    iLayoutTreeAddNewNode( data, layoutdlg->tree, new_ih );

    /* allow the dialog to expand current size */
    amy_IupSetAttribute( data, layoutdlg->dialog, "SIZE", NULL );

    iLayoutRefreshLayout( data, layoutdlg );

    iLayoutCallLayoutChangedCb( data, layoutdlg, new_ih );
  }

  return IUP_DEFAULT;
}

static int iLayoutContextMenuNewInsertChild_CB( struct libData *data, Ihandle *menu)
{
  Ihandle *dlg = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDLG" );
  const char *name = iLayoutSelectClassDialog( data, dlg );
  if (name)
  {
    iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDIALOG" );
    Ihandle *ref_elem = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTCONTEXTELEMENT" );

    Ihandle *new_ih = amy_IupCreate( data, name );

    /* add as first child */
    if ( ! amy_IupInsert( data, ref_elem, NULL, new_ih))
    {
      iLayoutError( data, layoutdlg, "Insert failed. Invalid operation for this node." );
      amy_IupDestroy( data, new_ih );
      return IUP_DEFAULT;
    }

    layoutdlg->changed = 1;

    /* add to the tree */
    iLayoutTreeAddNewNode( data, layoutdlg->tree, new_ih );

    /* allow the dialog to expand current size */
    amy_IupSetAttribute( data, layoutdlg->dialog, "SIZE", NULL );

    iLayoutRefreshLayout( data, layoutdlg );

    iLayoutCallLayoutChangedCb( data, layoutdlg, new_ih );
  }

  return IUP_DEFAULT;
}

static int iLayoutContextMenuNewAppendChild_CB( struct libData *data, Ihandle *menu)
{
  Ihandle *dlg = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDLG" );
  const char *name = iLayoutSelectClassDialog( data, dlg );
  if (name)
  {
    iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDIALOG" );
    Ihandle *ref_elem = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTCONTEXTELEMENT" );

    Ihandle *new_ih = amy_IupCreate( data, name );

    /* add as last child */
    if ( ! amy_IupAppend( data, ref_elem, new_ih))
    {
      iLayoutError( data, layoutdlg, "Append failed. Invalid operation for this node." );
      amy_IupDestroy( data, new_ih );
      return IUP_DEFAULT;
    }

    layoutdlg->changed = 1;

    /* add to the tree */
    iLayoutTreeAddNewNode( data, layoutdlg->tree, new_ih );

    /* allow the dialog to expand current size */
    amy_IupSetAttribute( data, layoutdlg->dialog, "SIZE", NULL );

    iLayoutRefreshLayout( data, layoutdlg );

    iLayoutCallLayoutChangedCb( data, layoutdlg, new_ih );
  }

  return IUP_DEFAULT;
}

static void iLayoutNewInsertCursor( struct libData *data, Ihandle *ih, const char *name)
{
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, ih, "_IUP_LAYOUTDIALOG" );
  Ihandle *container = (Ihandle*) iupAttribGetInherit( data, ih, "INSERTCURSOR" ); /* the container */
  Ihandle *ref_elem = (Ihandle*) iupAttribGetInherit( data, ih, "INSERTCURSOR_ELEMENT" );
  Ihandle *ret_ih = NULL;
  Ihandle *new_ih;
  int insert = 0;

  if ( ! container)
    return;

  new_ih = amy_IupCreate( data, name );

  if (iupStrEqual(name, "label" ) || iupStrEqual(name, "flatlabel" ))
  {
    static int new_label_count = 1;
    amy_IupSetStrf( data,new_ih, "TITLE", "Label%d", new_label_count );
    new_label_count++;
  }
  else if (iupStrEqual(name, "button" ) || iupStrEqual(name, "flatbutton" ))
  {
    static int new_button_count = 1;
    amy_IupSetStrf( data,new_ih, "TITLE", "Button%d", new_button_count );
    new_button_count++;
  }
  else if (iupStrEqual(name, "toggle" ) || iupStrEqual(name, "flattoggle" ))
  {
    static int new_toggle_count = 1;
    amy_IupSetStrf( data,new_ih, "TITLE", "Toggle%d", new_toggle_count );
    new_toggle_count++;
  }

  if ( ! ref_elem)
  {
    int cx, cy;
    if ( amy_IupGetIntInt( data, ih, "INSERTCURSOR_ELEMENT_POS", &cx, &cy) == 2) /* cbox */
    {
      ret_ih = amy_IupAppend( data, container, new_ih );
      amy_IupSetInt( data, new_ih, "CX", cx );  iLayoutSaveAttrib( data, layoutdlg, new_ih, "CX" );
      amy_IupSetInt( data, new_ih, "CY", cy );  iLayoutSaveAttrib( data, layoutdlg, new_ih, "CY" );
    }
    else /* empty box */
      ret_ih = amy_IupAppend( data, container, new_ih );
  }
  else
  {
    int insert_before = amy_IupGetInt( data, ih, "INSERTCURSOR_BEFORE" );

    if (insert_before)
    {
      ret_ih = amy_IupInsert( data, container, ref_elem, new_ih );
      insert = 1;
    }
    else
    {
      /* add as brother after reference */
      if (ref_elem->brother)
      {
        /* add before the brother, so it will be the brother */
        ret_ih = amy_IupInsert( data, container, ref_elem->brother, new_ih );
        insert = 1;
      }
      else
        ret_ih = amy_IupAppend( data, container, new_ih );
    }
  }

  if ( ! ret_ih)
  {
    if (insert)
      iLayoutError( data, layoutdlg, "Insert failed. Invalid operation for this node." );
    else
      iLayoutError( data, layoutdlg, "Append failed. Invalid operation for this node." );
    amy_IupDestroy( data, new_ih );
    return;
  }

  layoutdlg->changed = 1;

  /* add to the tree */
  iLayoutTreeAddNewNode( data, layoutdlg->tree, new_ih );

  /* allow the dialog to expand current size */
  amy_IupSetAttribute( data, layoutdlg->dialog, "SIZE", NULL );

  iLayoutRefreshLayout( data, layoutdlg );

  iLayoutCallLayoutChangedCb( data, layoutdlg, new_ih );
}

static int iLayoutContextMenuNewInsertCursor_CB( struct libData *data, Ihandle *menu)
{
  Ihandle *dlg = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDLG" );
  const char *name = iLayoutSelectClassDialog( data, dlg );
  if (name)
    iLayoutNewInsertCursor( data, menu, name );

  return IUP_DEFAULT;
}

static void iLayoutUpdateColors( struct libData *data, Ihandle *tree, Ihandle *ih)
{
  iLayoutTreeSetNodeColor( data, tree, amy_IupTreeGetId( data, tree, ih), ih );

  if (ih->iclass->childtype != IUP_CHILDNONE)
  {
    Ihandle *child;
    for (child = ih->firstchild; child; child = child->brother)
    {
      iLayoutUpdateColors( data, tree, child );
    }
  }
}

static int iLayoutContextMenuMap_CB( struct libData *data, Ihandle *menu)
{
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDIALOG" );
  Ihandle *elem = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTCONTEXTELEMENT" );

  if ( amy_IupMap( data, elem ) == IUP_ERROR)
  {
    iLayoutError( data, layoutdlg, "IupMap failed." );
    return IUP_DEFAULT;
  }

  iLayoutUpdateColors( data, layoutdlg->tree, elem );

  iLayoutRefreshLayout( data, layoutdlg );

  return IUP_DEFAULT;
}

static int iLayoutContextMenuRefreshChildren_CB( struct libData *data, Ihandle *menu)
{
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDIALOG" );

  amy_IupRefreshChildren( data, layoutdlg->dialog );

  /* redraw canvas */
  amy_IupUpdate( data, iLayoutGetCanvas( data, layoutdlg));

  return IUP_DEFAULT;
}

static void iLayoutSelectTreeItem( struct libData *data, iLayoutDialog *layoutdlg, Ihandle *elem );

static int iLayoutContextMenuGoToParent_CB( struct libData *data, Ihandle *menu)
{
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDIALOG" );
  Ihandle *elem = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTCONTEXTELEMENT" );

  if (elem->parent)
    iLayoutSelectTreeItem( data, layoutdlg, elem->parent );

  return IUP_DEFAULT;
}

static int iLayoutContextMenuGoToBrother_CB( struct libData *data, Ihandle *menu)
{
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDIALOG" );
  Ihandle *elem = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTCONTEXTELEMENT" );

  if (elem->brother)
    iLayoutSelectTreeItem( data, layoutdlg, elem->brother );

  return IUP_DEFAULT;
}

static int iLayoutContextMenuCollapseAll_CB( struct libData *data, Ihandle *menu)
{
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDIALOG" );
  amy_IupSetAttribute( data, layoutdlg->tree, "EXPANDALL", "NO" );
  return IUP_DEFAULT;
}

static int iLayoutContextMenuExpandAll_CB( struct libData *data, Ihandle *menu)
{
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDIALOG" );
  amy_IupSetAttribute( data, layoutdlg->tree, "EXPANDALL", "YES" );
  return IUP_DEFAULT;
}

static void iLayoutSaveAttributes( struct libData *data, Ihandle *ih)
{
  amy_IupSaveClassAttributes( data, ih );

  if (ih->iclass->childtype != IUP_CHILDNONE)
  {
    Ihandle *child;
    for (child = ih->firstchild; child; child = child->brother)
    {
      iLayoutSaveAttributes( data, child );
    }
  }
}

static int iLayoutContextMenuUnmap_CB( struct libData *data, Ihandle *menu)
{
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDIALOG" );
  Ihandle *elem = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTCONTEXTELEMENT" );

  iLayoutSaveAttributes( data, elem );

  amy_IupUnmap( data, elem );

  iLayoutUpdateColors( data, layoutdlg->tree, elem );

  iLayoutRefreshLayout( data, layoutdlg );

  return IUP_DEFAULT;
}

static int iLayoutContextMenuSetFocus_CB( struct libData *data, Ihandle *menu)
{
  Ihandle *elem = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTCONTEXTELEMENT" );

  amy_IupShow( data, amy_IupGetDialog( data, elem )); /* must be the active dialog to get the focus */

  amy_IupSetFocus( data, elem );

  return IUP_DEFAULT;
}

static void iLayoutBlink( struct libData *data, Ihandle *ih );

static int iLayoutContextMenuBlink_CB( struct libData *data, Ihandle *menu)
{
  Ihandle *elem = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTCONTEXTELEMENT" );

  iLayoutBlink( data, elem );

  return IUP_DEFAULT;
}

static int iLayoutContextMenuRemove_CB( struct libData *data, Ihandle *menu)
{
  Ihandle *msg_dlg;
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDIALOG" );
  Ihandle *elem = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTCONTEXTELEMENT" );
  if ( ! elem)  /* can be called from a key press */
    elem = (Ihandle*) amy_IupTreeGetUserId( data,  layoutdlg->tree, amy_IupGetInt( data, layoutdlg->tree, "VALUE" ));
  if ( ! elem)
    return IUP_DEFAULT;

  if (elem->flags & IUP_INTERNAL)
  {
    iLayoutError( data, layoutdlg, "Can NOT remove this child. It is an internal element of the container." );
    return IUP_DEFAULT;
  }

  if ( amy_IupClassMatch( data, elem, "dialog" ))
  {
    iLayoutError( data, layoutdlg, "Can NOT remove the dialog." );
    return IUP_DEFAULT;
  }

  msg_dlg = amy_IupMessageDlg( data );
  amy_IupSetAttribute( data, msg_dlg, "DIALOGTYPE", "QUESTION" );
  amy_IupSetAttribute( data, msg_dlg, "BUTTONS", "OKCANCEL" );
  amy_IupSetAttribute( data, msg_dlg, "TITLE", "Element Remove" );
  amy_IupSetAttribute( data, msg_dlg, "VALUE", "Remove the selected element?" );
  amy_IupSetAttributeHandle( data, msg_dlg, "PARENTDIALOG", amy_IupGetDialog( data, layoutdlg->tree));

  amy_IupPopup( data, msg_dlg, IUP_MOUSEPOS, IUP_MOUSEPOS );

  if ( amy_IupGetInt( data, msg_dlg, "BUTTONRESPONSE" ) == 1)
  {
    int id = amy_IupTreeGetId( data, layoutdlg->tree, elem );

    layoutdlg->changed = 1;

    /* remove from the tree */
    amy_IupSetAttributeId( data, layoutdlg->tree, "DELNODE", id, "SELECTED" );

    /* update properties if necessary */
    if ( layoutdlg->properties && amy_IupGetInt( data, layoutdlg->properties, "VISIBLE" ))
    {
      Ihandle *propelem = (Ihandle*) iupAttribGetInherit( data, layoutdlg->properties, "_IUP_PROPELEMENT" );
      if (iupChildTreeIsParent( data, elem, propelem ))
      {
        /* if current element will be removed, then use the previous element on the tree |*/
        iupLayoutPropertiesUpdate( data, layoutdlg->properties, (Ihandle*) amy_IupTreeGetUserId( data,  layoutdlg->tree, id - 1));
      }
    }

    amy_IupDestroy( data, elem );

    iLayoutRefreshLayout( data, layoutdlg );

    iLayoutCallLayoutChangedCb( data, layoutdlg, NULL );
  }

  amy_IupDestroy( data, msg_dlg );

  return IUP_DEFAULT;
}

static int iLayoutContextMenuCopy_CB( struct libData *data, Ihandle *menu)
{
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDIALOG" );
  Ihandle *elem = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTCONTEXTELEMENT" );
  layoutdlg->copy_elem = elem;
  layoutdlg->cut_elem = NULL;
  return IUP_DEFAULT;
}

static int iLayoutContextMenuCut_CB( struct libData *data, Ihandle *menu)
{
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDIALOG" );
  Ihandle *elem = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTCONTEXTELEMENT" );
  layoutdlg->copy_elem = NULL;
  layoutdlg->cut_elem = elem;
  return IUP_DEFAULT;
}

static int iLayoutContextMenuPasteInsertBrother_CB( struct libData *data, Ihandle *menu)
{
  Ihandle *ret_ih = NULL;
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDIALOG" );
  Ihandle *ref_elem = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTCONTEXTELEMENT" );

  if ( layoutdlg->copy_elem)
  {
	Ihandle *new_ih = amy_IupCreate( data, layoutdlg->copy_elem->iclass->name );
    amy_IupCopyClassAttributes( data, layoutdlg->copy_elem, new_ih );

    /* add as brother after reference */
    if (ref_elem->brother)
      /* add before the brother, so it will be the brother */
      ret_ih = amy_IupInsert( data, ref_elem->parent, ref_elem->brother, new_ih );
    else
      ret_ih = amy_IupAppend( data, ref_elem->parent, new_ih );

    if ( ! ret_ih)
    {
      iLayoutError( data, layoutdlg, "Paste failed (Copy). Invalid operation for this node." );
      amy_IupDestroy( data, new_ih );
      return IUP_DEFAULT;
    }

    layoutdlg->changed = 1;

    /* add to the tree */
    iLayoutTreeAddNewNode( data, layoutdlg->tree, new_ih );

    /* allow the dialog to expand current size */
    amy_IupSetAttribute( data, layoutdlg->dialog, "SIZE", NULL );

    iLayoutRefreshLayout( data, layoutdlg );

    iLayoutCallLayoutChangedCb( data, layoutdlg, new_ih );
  }
  else
  {
    if ( amy_IupReparent( data, layoutdlg->cut_elem, ref_elem->parent, ref_elem->brother) == IUP_ERROR)
    {
      iLayoutError( data, layoutdlg, "Paste failed (Cut). Invalid operation for this node." );
      return IUP_DEFAULT;
    }

    iLayoutTreeRebuild( data, layoutdlg );

    iLayoutCallLayoutChangedCb( data, layoutdlg, layoutdlg->cut_elem );

    layoutdlg->cut_elem = NULL;
  }

  return IUP_DEFAULT;
}

static int iLayoutContextMenuPasteInsertChild_CB( struct libData *data, Ihandle *menu)
{
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDIALOG" );
  Ihandle *ref_elem = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTCONTEXTELEMENT" );

  if ( layoutdlg->copy_elem)
  {
    Ihandle *new_ih = amy_IupCreate( data, layoutdlg->copy_elem->iclass->name );
    amy_IupCopyClassAttributes( data, layoutdlg->copy_elem, new_ih );

    /* add as first child */
    if ( ! amy_IupInsert( data, ref_elem, NULL, new_ih))
    {
      iLayoutError( data, layoutdlg, "Paste failed (Copy). Invalid operation for this node." );
      amy_IupDestroy( data, new_ih );
      return IUP_DEFAULT;
    }

    layoutdlg->changed = 1;

    /* add to the tree */
    iLayoutTreeAddNewNode( data, layoutdlg->tree, new_ih );

    /* allow the dialog to expand current size */
    amy_IupSetAttribute( data, layoutdlg->dialog, "SIZE", NULL );

    iLayoutRefreshLayout( data, layoutdlg );

    iLayoutCallLayoutChangedCb( data, layoutdlg, new_ih );
  }
  else
  {
    if ( amy_IupReparent( data, layoutdlg->cut_elem, ref_elem, ref_elem->firstchild) == IUP_ERROR)
    {
      iLayoutError( data, layoutdlg, "Paste failed (Cut). Invalid operation for this node." );
      return IUP_DEFAULT;
    }

    iLayoutTreeRebuild( data, layoutdlg );

    iLayoutCallLayoutChangedCb( data, layoutdlg, layoutdlg->cut_elem );

    layoutdlg->cut_elem = NULL;
  }

  return IUP_DEFAULT;
}

static int iLayoutContextMenuPasteAppendChild_CB( struct libData *data, Ihandle *menu)
{
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDIALOG" );
  Ihandle *ref_elem = (Ihandle*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTCONTEXTELEMENT" );

  if ( layoutdlg->copy_elem)
  {
    Ihandle *new_ih = amy_IupCreate( data, layoutdlg->copy_elem->iclass->name );
    amy_IupCopyClassAttributes( data, layoutdlg->copy_elem, new_ih );

    /* add as last child */
    if ( ! amy_IupAppend( data, ref_elem, new_ih))
    {
      iLayoutError( data, layoutdlg, "Paste failed (Copy). Invalid operation for this node." );
      amy_IupDestroy( data, new_ih );
      return IUP_DEFAULT;
    }

    layoutdlg->changed = 1;

    /* add to the tree */
    iLayoutTreeAddNewNode( data, layoutdlg->tree, new_ih );

    /* allow the dialog to expand current size */
    amy_IupSetAttribute( data, layoutdlg->dialog, "SIZE", NULL );

    iLayoutRefreshLayout( data, layoutdlg );

    iLayoutCallLayoutChangedCb( data, layoutdlg, new_ih );
  }
  else
  {
    if ( amy_IupReparent( data, layoutdlg->cut_elem, ref_elem, NULL) == IUP_ERROR)
    {
      iLayoutError( data, layoutdlg, "Paste failed (Cut). Invalid operation for this node." );
      return IUP_DEFAULT;
    }

    iLayoutTreeRebuild( data, layoutdlg );

    iLayoutCallLayoutChangedCb( data, layoutdlg, layoutdlg->cut_elem );

    layoutdlg->cut_elem = NULL;
  }

  return IUP_DEFAULT;
}

static int iLayoutContextMenuPasteCursor_CB( struct libData *data, Ihandle *menu)
{
  Ihandle *ret_ih = NULL;
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGetInherit( data, menu, "_IUP_LAYOUTDIALOG" );
  Ihandle *container = (Ihandle*) iupAttribGetInherit( data, menu, "INSERTCURSOR" ); /* the container */
  Ihandle *ref_elem = (Ihandle*) iupAttribGetInherit( data, menu, "INSERTCURSOR_ELEMENT" );

  if ( layoutdlg->copy_elem)
  {
    Ihandle *new_ih = amy_IupCreate( data, layoutdlg->copy_elem->iclass->name );
    amy_IupCopyClassAttributes( data, layoutdlg->copy_elem, new_ih );

    if ( ! ref_elem)
    {
      int cx, cy;
      if ( amy_IupGetIntInt( data, menu, "INSERTCURSOR_ELEMENT_POS", &cx, &cy) == 2) /* cbox */
      {
        ret_ih = amy_IupAppend( data, container, new_ih );
        amy_IupSetInt( data, new_ih, "CX", cx );  iLayoutSaveAttrib( data, layoutdlg, new_ih, "CX" );
        amy_IupSetInt( data, new_ih, "CY", cy );  iLayoutSaveAttrib( data, layoutdlg, new_ih, "CY" );
      }
      else /* empty box */
        ret_ih = amy_IupAppend( data, container, new_ih );
    }
    else
    {
      int insert_before = amy_IupGetInt( data, menu, "INSERTCURSOR_BEFORE" );

      if (insert_before)
        ret_ih = amy_IupInsert( data, container, ref_elem, new_ih );
      else
      {
        /* add as brother after reference */
        if (ref_elem->brother)
          /* add before the brother, so it will be the brother */
          ret_ih = amy_IupInsert( data, container, ref_elem->brother, new_ih );
        else
          ret_ih = amy_IupAppend( data, container, new_ih );
      }
    }

    if ( ! ret_ih)
    {
      iLayoutError( data, layoutdlg, "Paste failed (Copy). Invalid operation for this node." );
      amy_IupDestroy( data, new_ih );
      return IUP_DEFAULT;
    }

    layoutdlg->changed = 1;

    /* add to the tree */
    iLayoutTreeAddNewNode( data, layoutdlg->tree, new_ih );

    /* allow the dialog to expand current size */
    amy_IupSetAttribute( data, layoutdlg->dialog, "SIZE", NULL );

    iLayoutRefreshLayout( data, layoutdlg );

    iLayoutCallLayoutChangedCb( data, layoutdlg, new_ih );
  }
  else
  {
    if (ref_elem)
    {
      int insert_before = amy_IupGetInt( data, menu, "INSERTCURSOR_BEFORE" );
      if ( ! insert_before)
        ref_elem = ref_elem->brother;
    }

    if ( amy_IupReparent( data, layoutdlg->cut_elem, container, ref_elem) == IUP_ERROR)
    {
      iLayoutError( data, layoutdlg, "Paste failed (Cut). Invalid operation for this node." );
      return IUP_DEFAULT;
    }

    if ( amy_IupClassMatch( data, container, "cbox" ))
    {
      int cx, cy;
      if ( amy_IupGetIntInt( data, menu, "INSERTCURSOR_ELEMENT_POS", &cx, &cy) == 2) /* cbox */
      {
        amy_IupSetInt( data, layoutdlg->cut_elem, "CX", cx );  iLayoutSaveAttrib( data, layoutdlg, layoutdlg->cut_elem, "CX" );
        amy_IupSetInt( data, layoutdlg->cut_elem, "CY", cy );  iLayoutSaveAttrib( data, layoutdlg, layoutdlg->cut_elem, "CY" );
      }
    }

    iLayoutTreeRebuild( data, layoutdlg );

    iLayoutCallLayoutChangedCb( data, layoutdlg, layoutdlg->cut_elem );

    layoutdlg->cut_elem = NULL;
  }

  return IUP_DEFAULT;
}

static int iLayoutIsEmptyContainer( struct libData *data, Ihandle *elem)
{
  int child_count = amy_IupGetChildCount( data, elem );
  if (elem->firstchild && (elem->firstchild->flags & IUP_INTERNAL))
    child_count--;
  return child_count == 0;
}

static void iLayoutContextMenu( struct libData *data, iLayoutDialog *layoutdlg, Ihandle *elem, Ihandle *dlg)
{
  Ihandle *menu;
  int is_container = elem->iclass->childtype != IUP_CHILDNONE;
  int can_copy = !is_container || iLayoutIsEmptyContainer( data, elem );
  int can_paste, can_cut = 1;
  int can_map = (elem->handle == NULL) && (elem->parent == NULL || elem->parent->handle != NULL );
  int can_unmap = elem->handle != NULL;
  int can_blink = (elem->iclass->nativetype != IUP_TYPEVOID && amy_IupGetInt( data, elem, "VISIBLE" ));
  int can_focus = iupFocusCanAccept( data, elem );
  Ihandle *canvas = iLayoutGetCanvas( data, layoutdlg );
  Ihandle *insert_cursor = (Ihandle*) amy_IupGetAttribute( data, canvas, "INSERTCURSOR" );
  int can_cursor = insert_cursor != NULL;
  int can_brother = 1;
  int can_child = 1;
  int can_paste_cut = 1;
  int can_paste_cut_cursor = 1;

  if ( ! iupObjectCheck( data, layoutdlg->copy_elem))
    layoutdlg->copy_elem = NULL;
  if ( ! iupObjectCheck( data, layoutdlg->cut_elem))
    layoutdlg->cut_elem = NULL;

  can_paste = layoutdlg->copy_elem != NULL || layoutdlg->cut_elem != NULL;

  if ( amy_IupClassMatch( data, elem, "dialog" ))
  {
    can_copy = 0;
    can_cut = 0;
  }

  if ( layoutdlg->cut_elem)
  {
    if (iupChildTreeIsParent( data, layoutdlg->cut_elem, elem))
      can_paste_cut = 0;

    if (iupChildTreeIsParent( data, layoutdlg->cut_elem, insert_cursor))
      can_paste_cut_cursor = 0;
  }

  if (elem->iclass->childtype == IUP_CHILDNONE)  /* not a container */
    can_child = 0;
  if (elem->iclass->childtype > IUP_CHILDMANY &&    /* container is full */
      amy_IupGetChildCount( data, elem ) == elem->iclass->childtype - IUP_CHILDMANY)
    can_child = 0;

  if ( ! elem->parent)
    can_brother = 0;
  else
  {
    if (elem->parent->iclass->childtype == IUP_CHILDNONE)
      can_brother = 0;
    if (elem->parent->iclass->childtype > IUP_CHILDMANY &&
        amy_IupGetChildCount( data, elem->parent ) == elem->parent->iclass->childtype - IUP_CHILDMANY)
      can_brother = 0;
  }

  menu = amy_IupMenu( data,
    amy_IupSetCallbacks( data, amy_IupItem( data, "Properties...", NULL), "ACTION", iLayoutContextMenuProperties_CB, NULL),
    amy_IupSetCallbacks( data, amy_IupItem( data, "Handle Name...", NULL), "ACTION", iLayoutContextMenuHandleName_CB, NULL),
    amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupItem( data, "Map", NULL), can_map ? "ACTIVE=Yes" : "ACTIVE=No" ), "ACTION", iLayoutContextMenuMap_CB, NULL),
    amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupItem( data, "Unmap", NULL), can_unmap ? "ACTIVE=Yes" : "ACTIVE=No" ), "ACTION", iLayoutContextMenuUnmap_CB, NULL),
    amy_IupSetCallbacks( data, amy_IupItem( data, "Refresh Children", NULL), "ACTION", iLayoutContextMenuRefreshChildren_CB, NULL),
    amy_IupSeparator( data ),
    amy_IupSetCallbacks( data, amy_IupItem( data, "Collapse All", NULL), "ACTION", iLayoutContextMenuCollapseAll_CB, NULL),
    amy_IupSetCallbacks( data, amy_IupItem( data, "Expand All", NULL), "ACTION", iLayoutContextMenuExpandAll_CB, NULL),
    amy_IupSetCallbacks( data, amy_IupItem( data, "Go to Parent\tLeft", NULL), "ACTION", iLayoutContextMenuGoToParent_CB, NULL),
    amy_IupSetCallbacks( data, amy_IupItem( data, "Go to Brother\tDown", NULL), "ACTION", iLayoutContextMenuGoToBrother_CB, NULL),
    amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupItem( data, "Blink", NULL), can_blink ? "ACTIVE=Yes" : "ACTIVE=No" ), "ACTION", iLayoutContextMenuBlink_CB, NULL),
    amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupItem( data, "Set Focus", NULL), can_focus ? "ACTIVE=Yes" : "ACTIVE=No" ), "ACTION", iLayoutContextMenuSetFocus_CB, NULL),
    amy_IupSeparator( data ),
    amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupItem( data, "Copy", NULL), can_copy ? "ACTIVE=Yes" : "ACTIVE=No" ), "ACTION", iLayoutContextMenuCopy_CB, NULL),
    amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupItem( data, "Cut", NULL), can_cut ? "ACTIVE=Yes" : "ACTIVE=No" ), "ACTION", iLayoutContextMenuCut_CB, NULL),
    amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupItem( data, "Paste Insert Child", NULL), can_paste && can_child && can_paste_cut ? "ACTIVE=Yes" : "ACTIVE=No" ), "ACTION", iLayoutContextMenuPasteInsertChild_CB, NULL),
    amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupItem( data, "Paste Insert at Cursor", NULL), can_paste && can_cursor && can_paste_cut_cursor ? "ACTIVE=Yes" : "ACTIVE=No" ), "ACTION", iLayoutContextMenuPasteCursor_CB, NULL),
    amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupItem( data, "Paste Append Child", NULL), can_paste && can_child && can_paste_cut ? "ACTIVE=Yes" : "ACTIVE=No" ), "ACTION", iLayoutContextMenuPasteAppendChild_CB, NULL),
    amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupItem( data, "Paste Insert Brother", NULL), can_paste && can_brother && can_paste_cut ? "ACTIVE=Yes" : "ACTIVE=No" ), "ACTION", iLayoutContextMenuPasteInsertBrother_CB, NULL),
    amy_IupSeparator( data ),
    amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupItem( data, "New Insert Child...", NULL), can_child ? "ACTIVE=Yes" : "ACTIVE=No" ), "ACTION", iLayoutContextMenuNewInsertChild_CB, NULL),
    amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupItem( data, "New Insert at Cursor...", NULL), can_cursor ? "ACTIVE=Yes" : "ACTIVE=No" ), "ACTION", iLayoutContextMenuNewInsertCursor_CB, NULL),
    amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupItem( data, "New Append Child...", NULL), can_child ? "ACTIVE=Yes" : "ACTIVE=No" ), "ACTION", iLayoutContextMenuNewAppendChild_CB, NULL),
    amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupItem( data, "New Insert Brother...", NULL), can_brother ? "ACTIVE=Yes" : "ACTIVE=No" ), "ACTION", iLayoutContextMenuNewInsertBrother_CB, NULL),
    amy_IupSeparator( data ),
    amy_IupSetCallbacks( data, amy_IupItem( data, "Remove...\tDel", NULL), "ACTION", iLayoutContextMenuRemove_CB, NULL),
    NULL );

  if (can_cursor)
  {
    iupAttribSet( data, menu, "INSERTCURSOR", (char*)insert_cursor );
    iupAttribSetStr( data, menu, "INSERTCURSOR_ELEMENT_POS", iupAttribGet( data, canvas, "INSERTCURSOR_ELEMENT_POS" ));
    iupAttribSet( data, menu, "INSERTCURSOR_ELEMENT", iupAttribGet( data, canvas, "INSERTCURSOR_ELEMENT" ));
    iupAttribSetStr( data, menu, "INSERTCURSOR_BEFORE", iupAttribGet( data, canvas, "INSERTCURSOR_BEFORE" ));
  }

  iupAttribSet( data, menu, "_IUP_LAYOUTCONTEXTELEMENT", (char*)elem );
  iupAttribSet( data, menu, "_IUP_LAYOUTDIALOG", (char*)layoutdlg );
  iupAttribSet( data, menu, "_IUP_LAYOUTDLG", (char*)dlg );

  amy_IupPopup( data, menu, IUP_MOUSEPOS, IUP_MOUSEPOS );

  amy_IupDestroy( data, menu );
}

static int iLayoutItemShowContext_CB( struct libData *data, Ihandle *ih_item)
{
  Ihandle *dlg = amy_IupGetDialog( data, ih_item );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  int focus_id = amy_IupGetInt( data, layoutdlg->tree, "VALUE" );
  Ihandle *elem = (Ihandle*) amy_IupTreeGetUserId( data,  layoutdlg->tree, focus_id );
  iLayoutContextMenu( data, layoutdlg, elem, dlg );
  return IUP_DEFAULT;
}



/***************************************************************************
                       Layout Canvas Interaction
***************************************************************************/


static void iLayoutBlink( struct libData *data, Ihandle *ih)
{
  if (ih->iclass->nativetype != IUP_TYPEVOID && amy_IupGetInt( data, ih, "VISIBLE" ))
  {
    int i;
    for (i = 0; i < 3; i++)
    {
      amy_IupSetAttribute( data, ih, "VISIBLE", "NO" );
      amy_IupFlush( data );
      iupdrvSleep( data, 100 );
      amy_IupSetAttribute( data, ih, "VISIBLE", "Yes" );
      amy_IupFlush( data );
      iupdrvSleep( data, 100 );
    }
  }
}

static void iLayoutTreeSelectionChanged( struct libData *data, iLayoutDialog *layoutdlg, Ihandle *ih, int id)
{
  if (ih->iclass->childtype != IUP_CHILDNONE)
  {
    int x = 0, y = 0;
    int w, h;
    amy_IupGetIntInt( data, ih, "CLIENTOFFSET", &x, &y );
    amy_IupGetIntInt( data, ih, "CLIENTSIZE", &w, &h );

    if ( !  amy_IupClassMatch( data, ih, "dialog" ))
    {
      amy_IupSetfAttribute( data, layoutdlg->status, "TITLE", "Position:%4d,%4d | User:%4d,%4d | Natural:%4d,%4d | Current:%4d,%4d\n"
                                                   "Client Offset: %4d, %4d | Client Size: %4d, %4d",
                       ih->x, ih->y, ih->userwidth, ih->userheight, ih->naturalwidth, ih->naturalheight, ih->currentwidth, ih->currentheight,
                       x, y, w, h );
    }
    else
    {
      int border, caption, menu;
      iupdrvDialogGetDecoration( data, ih, &border, &caption, &menu );
      amy_IupSetfAttribute( data, layoutdlg->status, "TITLE", "Position:%4d,%4d | User:%4d,%4d | Natural:%4d,%4d | Current:%4d,%4d\n"
                                                   "Client Offset: %4d, %4d | Client Size: %4d, %4d | Border: %3d, Caption: %3d, Menu: %3d",
                       ih->x, ih->y, ih->userwidth, ih->userheight, ih->naturalwidth, ih->naturalheight, ih->currentwidth, ih->currentheight,
                       x, y, w, h, border, caption, menu );
    }
  }
  else
  {
    amy_IupSetfAttribute( data, layoutdlg->status, "TITLE", "Position:%4d,%4d | User:%4d,%4d | Natural:%4d,%4d | Current:%4d,%4d\n",
                     ih->x, ih->y, ih->userwidth, ih->userheight, ih->naturalwidth, ih->naturalheight, ih->currentwidth, ih->currentheight );
  }


  if ( ! ih->handle)
    amy_IupSetAttributeId( data, layoutdlg->tree, "COLOR", id, "128 0 0" );
  else
    amy_IupSetAttributeId( data, layoutdlg->tree, "COLOR", id, "255 0 0" );

  if ( layoutdlg->properties && amy_IupGetInt( data, layoutdlg->properties, "VISIBLE" ))
    iupLayoutPropertiesUpdate( data, layoutdlg->properties, ih );
}

static Ihandle *iLayoutGetElementByPos( struct libData *data, Ihandle *ih, int native_parent_x, int native_parent_y, int x, int y, int showhidden, int dlgvisible, int shownotmapped)
{
  if ((showhidden || iLayoutElementIsVisible( data, ih, dlgvisible)) &&
      (shownotmapped || ih->handle))
  {
    /* check the element */
    if (x >= ih->x + native_parent_x &&
        y >= ih->y + native_parent_y &&
        x < ih->x + native_parent_x + ih->currentwidth &&
        y < ih->y + native_parent_y + ih->currentheight)
    {
      Ihandle *child, *elem;
      if (ih->iclass->childtype != IUP_CHILDNONE)
      {
        /* if ih is a native parent, then update the offset */
        if (ih->iclass->nativetype != IUP_TYPEVOID)
        {
          int dx = 0, dy = 0;
          amy_IupGetIntInt( data, ih, "CLIENTOFFSET", &dx, &dy );
          native_parent_x += ih->x + dx;
          native_parent_y += ih->y + dy;

          /* if ih is a Zbox like, then draw only the active child */
          if ( amy_IupClassMatch( data, ih, "zbox" ) || amy_IupClassMatch( data, ih, "tabs" ) || amy_IupClassMatch( data, ih, "flattabs" ))
          {
            child = (Ihandle*) amy_IupGetAttribute( data, ih, "VALUE_HANDLE" );
            if (child)
            {
              elem = iLayoutGetElementByPos( data, child, native_parent_x, native_parent_y, x, y, showhidden, dlgvisible, shownotmapped );
              if (elem)
                return elem;
            }

            return ih;
          }
        }
      }

      /* check its children */
      for (child = ih->firstchild; child; child = child->brother)
      {
        elem = iLayoutGetElementByPos( data, child, native_parent_x, native_parent_y, x, y, showhidden, dlgvisible, shownotmapped );
        if (elem)
          return elem;
      }

      return ih;
    }
  }
  return NULL;
}

static Ihandle *iLayoutGetDialogElementByPos( struct libData *data, iLayoutDialog *layoutdlg, int x, int y)
{
  int w, h;
  amy_IupGetIntInt( data, layoutdlg->dialog, "CLIENTSIZE", &w, &h );

  if ( layoutdlg->dialog->firstchild &&
      x >= 0 && y >= 0 &&
      x < w && y < h)
  {
    Ihandle *elem;
    Ihandle *canvas = iLayoutGetCanvas( data, layoutdlg );
    int native_parent_x = 0, native_parent_y = 0;
    Ihandle *dlg = amy_IupGetDialog( data, canvas );
    int showhidden = amy_IupGetInt( data, dlg, "SHOWHIDDEN" );
    int shownotmapped = layoutdlg->dialog->handle == NULL;  /* only check not mapped if dialog is also not mapped */
    int dlgvisible = amy_IupGetInt( data, layoutdlg->dialog, "VISIBLE" );
    amy_IupGetIntInt( data, layoutdlg->dialog, "CLIENTOFFSET", &native_parent_x, &native_parent_y );
    native_parent_x -= amy_IupGetInt( data, canvas, "POSX" );
    native_parent_y -= amy_IupGetInt( data, canvas, "POSY" );
    elem = iLayoutGetElementByPos( data, layoutdlg->dialog->firstchild, native_parent_x, native_parent_y, x, y, showhidden, dlgvisible, shownotmapped );
    if (elem)
      return elem;
    return layoutdlg->dialog;
  }
  return NULL;
}

static void iLayoutSelectTreeItem( struct libData *data, iLayoutDialog *layoutdlg, Ihandle *elem)
{
  int id = amy_IupTreeGetId( data, layoutdlg->tree, elem );
  int old_id = amy_IupGetInt( data, layoutdlg->tree, "VALUE" );
  Ihandle *old_elem = (Ihandle*) amy_IupTreeGetUserId( data,  layoutdlg->tree, old_id );
  iLayoutTreeSetNodeColor( data, layoutdlg->tree, old_id, old_elem );
  amy_IupSetInt( data, layoutdlg->tree, "VALUE", id );
  iLayoutTreeSelectionChanged( data, layoutdlg, elem, id );
  amy_IupUpdate( data, iLayoutGetCanvas( data, layoutdlg));
}

static int iLayoutCanvasButton_CB( struct libData *data, Ihandle *canvas, int but, int pressed, int x, int y, char *status)
{
  if (but == IUP_BUTTON1 && pressed)
  {
    Ihandle *dlg = amy_IupGetDialog( data, canvas );
    iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
    Ihandle *elem = iLayoutGetDialogElementByPos( data, layoutdlg, x, y );

    iupAttribSet( data, canvas, "_IUP_PRESS_X", NULL );
    iupAttribSet( data, canvas, "_IUP_PRESS_Y", NULL );
    iupAttribSet( data, canvas, "_IUP_PRESS_ELEM", NULL );

    if (elem)
    {
      if (iup_isdouble(status))
      {
        iLayoutBlink( data, elem );
        amy_IupRedraw( data, canvas, 0 );
      }
      else
      {
        if ( layoutdlg->new_elem_class)
        {
          /* use new_elem_class to insert a new element at cursor */
          iLayoutNewInsertCursor( data, canvas, layoutdlg->new_elem_class );
        }
        else
        {
          iupAttribSetInt( data, canvas, "_IUP_PRESS_X", x );
          iupAttribSetInt( data, canvas, "_IUP_PRESS_Y", y );
          iupAttribSetInt( data, canvas, "_IUP_PRESS_CX", amy_IupGetInt( data, elem, "CX" ));
          iupAttribSetInt( data, canvas, "_IUP_PRESS_CY", amy_IupGetInt( data, elem, "CY" ));
          iupAttribSet( data, canvas, "_IUP_PRESS_ELEM", (char*)elem );
        }
      }
    }
    else if ( layoutdlg->new_elem_class)
    {
      /* use new_elem_class to insert a new element at cursor */
      iLayoutNewInsertCursor( data, canvas, layoutdlg->new_elem_class );
    }
  }
  else if (but == IUP_BUTTON1 && !pressed)
  {
    Ihandle *elem = (Ihandle*) iupAttribGet( data, canvas, "_IUP_PRESS_ELEM" );
    if (elem)
    {
      Ihandle *dlg = amy_IupGetDialog( data, canvas );
      iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
      int press_x = iupAttribGetInt( data, canvas, "_IUP_PRESS_X" );
      int press_y = iupAttribGetInt( data, canvas, "_IUP_PRESS_Y" );
      if (press_x == x && press_y == y)
        iLayoutSelectTreeItem( data, layoutdlg, elem );   /* select only when button is released, so pressed and selected can be different elements */
      else
      {
        /* drag and drop the element at INSERTCURSOR */
        Ihandle *container = (Ihandle*) iupAttribGetInherit( data, canvas, "INSERTCURSOR" ); /* the container */
        if (container && container != elem)
        {
          int reparent = 1;
          Ihandle *ref_elem = (Ihandle*) iupAttribGetInherit( data, canvas, "INSERTCURSOR_ELEMENT" );
          if (ref_elem)
          {
            int insert_before = amy_IupGetInt( data, canvas, "INSERTCURSOR_BEFORE" );
            if ( ! insert_before)
              ref_elem = ref_elem->brother;
          }

          if ( amy_IupClassMatch( data, container, "cbox" ) && elem->parent == container) /* moving child inside the cbox parent */
          {
            reparent = 0;
            iLayoutSaveAttrib( data, layoutdlg, elem, "CX" );
            iLayoutSaveAttrib( data, layoutdlg, elem, "CY" );
          }

          if (reparent && amy_IupReparent( data, elem, container, ref_elem) == IUP_ERROR)
          {
            iLayoutError( data, layoutdlg, "Move failed. Invalid operation for this node." );
            return IUP_DEFAULT;
          }

          if (reparent && amy_IupClassMatch( data, container, "cbox" ))
          {
            int cx, cy;
            if ( amy_IupGetIntInt( data, canvas, "INSERTCURSOR_ELEMENT_POS", &cx, &cy) == 2) /* cbox */
            {
              amy_IupSetInt( data, elem, "CX", cx );  iLayoutSaveAttrib( data, layoutdlg, elem, "CX" );
              amy_IupSetInt( data, elem, "CY", cy );  iLayoutSaveAttrib( data, layoutdlg, elem, "CY" );
            }
          }

          iLayoutTreeRebuild( data, layoutdlg );

          iLayoutCallLayoutChangedCb( data, layoutdlg, elem );
        }
        else
        {
          if ( amy_IupClassMatch( data, elem->parent, "cbox" )) /* can drag immediate cbox children */
          {
            /* since two attributes are changed simultaneously we call layoutchanged_cb instead of attribchanged_cb */
            iLayoutSaveAttrib( data, layoutdlg, elem, "CX" );            
            iLayoutSaveAttrib( data, layoutdlg, elem, "CY" );

            iLayoutCallLayoutChangedCb( data, layoutdlg, elem );
          }
        }
      }
    }

    if ( ! iupStrEqual( amy_IupGetAttribute( data, canvas, "CURSOR" ), "ARROW" ))
      amy_IupSetAttribute( data, canvas, "CURSOR", "ARROW" );
  }
  else if (but == IUP_BUTTON3 && pressed)
  {
    Ihandle *dlg = amy_IupGetDialog( data, canvas );
    iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
    Ihandle *elem = iLayoutGetDialogElementByPos( data, layoutdlg, x, y );
    if (elem)
      iLayoutContextMenu( data, layoutdlg, elem, dlg );
  }
  return IUP_DEFAULT;
}

static void iLayoutGetNativeParentOffset( struct libData *data, Ihandle *elem, int *native_parent_x, int *native_parent_y)
{
  Ihandle *native_parent = iupChildTreeGetNativeParent( data, elem );
  if (native_parent)
  {
    int dx = 0, dy = 0;
    amy_IupGetIntInt( data, native_parent, "CLIENTOFFSET", &dx, &dy );
    *native_parent_x += native_parent->x + dx;
    *native_parent_y += native_parent->y + dy;

    if (native_parent->parent)
      iLayoutGetNativeParentOffset( data, native_parent, native_parent_x, native_parent_y );
  }
}

static int iSqr(int x)
{
  return x*x;
}

static int iLayoutGetBetweenPosX( struct libData *data, Ihandle *child1, Ihandle *child2)
{
  if (child1 == NULL)
  {
    /* find previous child */
    child1 = iupChildTreeGetPrevBrother( data, child2 );
    if ( ! child1)
      return child2->x;
    else
      return (child1->x + child1->currentwidth-1 + child2->x) / 2;
  }
  else /* child2 == NULL */
  {
    /* find next child */
    child2 = child1->brother;
    if ( ! child2)
      return child1->x + child1->currentwidth-1;
    else
      return (child1->x + child1->currentwidth-1 + child2->x) / 2;
  }
}

static int iLayoutGetBetweenPosY( struct libData *data, Ihandle *child1, Ihandle *child2)
{
  if (child1 == NULL)
  {
    /* find previous child */
    child1 = iupChildTreeGetPrevBrother( data, child2 );
    if ( ! child1)
      return child2->y;
    else
      return (child1->y + child1->currentheight-1 + child2->y) / 2;
  }
  else /* child2 == NULL */
  {
    /* find next child */
    child2 = child1->brother;
    if ( ! child2)
      return child1->y + child1->currentheight-1;
    else
      return (child1->y + child1->currentheight-1 + child2->y) / 2;
  }
}

static int iLayoutCanvasMotion_CB( struct libData *data, Ihandle *canvas, int x, int y, char *status)
{
  Ihandle *container;
  Ihandle *dlg = amy_IupGetDialog( data, canvas );
  Ihandle *mark = iLayoutGetSelectedElement( data, dlg );
  int container_x, container_y, container_w, container_h;
  int native_parent_x = 0, native_parent_y = 0;
  (void)status;

  if (iup_isbutton1(status))
  {
    Ihandle *elem = (Ihandle*) iupAttribGet( data, canvas, "_IUP_PRESS_ELEM" );
    if (elem)
    {
      if ( ! iupStrEqual( amy_IupGetAttribute( data, canvas, "CURSOR" ), "MOVE" ))
        amy_IupSetAttribute( data, canvas, "CURSOR", "MOVE" );

      if ( amy_IupClassMatch( data, elem->parent, "cbox" )) /* can drag immediate cbox children */
      {
        int press_x = iupAttribGetInt( data, canvas, "_IUP_PRESS_X" );
        int press_y = iupAttribGetInt( data, canvas, "_IUP_PRESS_Y" );
        int press_cx = iupAttribGetInt( data, canvas, "_IUP_PRESS_CX" );
        int press_cy = iupAttribGetInt( data, canvas, "_IUP_PRESS_CY" );
        int off_x = x - press_x;
        int off_y = y - press_y;
        amy_IupSetInt( data, elem, "CX", press_cx + off_x ); 
        amy_IupSetInt( data, elem, "CY", press_cy + off_y ); 
        amy_IupRefreshChildren( data, elem->parent );
        amy_IupRedraw( data, canvas, 0 );

        /* but notify only when button is released */
      }
    }
  }

  /* starting here is all for the INSERTCURSOR management */

  if (mark->iclass->childtype == IUP_CHILDNONE)
  {
    if (iupAttribGet( data, canvas, "INSERTCURSOR" ))
    {
      iupAttribSet( data, canvas, "INSERTCURSOR", NULL );
      iupAttribSet( data, canvas, "INSERTCURSOR_POINT", NULL );
      iupAttribSet( data, canvas, "INSERTCURSOR_ELEMENT_POS", NULL );
      iupAttribSet( data, canvas, "INSERTCURSOR_LINE", NULL );
      iupAttribSet( data, canvas, "INSERTCURSOR_ELEMENT", NULL );
      iupAttribSet( data, canvas, "INSERTCURSOR_BEFORE", NULL );
      amy_IupRedraw( data, canvas, 0 );
    }
    return IUP_DEFAULT;
  }

  x += amy_IupGetInt( data, canvas, "POSX" );
  y += amy_IupGetInt( data, canvas, "POSY" );

  container = mark;
  iLayoutGetNativeParentOffset( data, container, &native_parent_x, &native_parent_y );
  container_x = container->x + native_parent_x;
  container_y = container->y + native_parent_y;
  if ( amy_IupClassMatch( data, container, "dialog" ))
    amy_IupGetIntInt( data, container, "CLIENTSIZE", &container_w, &container_h );
  else
  {
    container_w = container->currentwidth;
    container_h = container->currentheight;
  }

  if (x >= container_x &&
      y >= container_y &&
      x < container_x + container_w &&
      y < container_y + container_h)
  {
    /* check if container still has room for more children */
    if (container->iclass->childtype == IUP_CHILDMANY ||
        amy_IupGetChildCount( data, container ) < container->iclass->childtype - IUP_CHILDMANY)
    {
      int r_x = x - native_parent_x;
      int r_y = y - native_parent_y;

      iupAttribSet( data, canvas, "INSERTCURSOR", (char*)container );

      if ( amy_IupClassMatch( data, container, "cbox" ))
      {
        iupAttribSetStrf( data, canvas, "INSERTCURSOR_POINT", "%d,%d", x, y );
        iupAttribSetStrf( data, canvas, "INSERTCURSOR_ELEMENT_POS", "%d,%d", r_x - container->x, r_y - container->y );
        iupAttribSet( data, canvas, "INSERTCURSOR_LINE", NULL );
        iupAttribSet( data, canvas, "INSERTCURSOR_ELEMENT", NULL );
        iupAttribSet( data, canvas, "INSERTCURSOR_BEFORE", NULL );
        amy_IupRedraw( data, canvas, 0 );
        return IUP_DEFAULT;
      }
      else 
      {
        Ihandle *child_near = NULL;
        int is_horizontal = iupStrEqualNoCase( amy_IupGetAttribute( data, container, "ORIENTATION" ), "HORIZONTAL" );
        int is_multi = amy_IupClassMatch( data, container, "gridbox" ) || amy_IupClassMatch( data, container, "multibox" );

        if ( amy_IupClassMatch( data, container, "zbox" ) || amy_IupClassMatch( data, container, "tabs" ) || amy_IupClassMatch( data, container, "flattabs" ))
        {
          child_near = (Ihandle*) amy_IupGetAttribute( data, container, "VALUE_HANDLE" );
        }
        else
        {
          Ihandle *child;
          int d_min = 0, d;

          /* find the closest child to the cursor */
          for (child = container->firstchild; child; child = child->brother)
          {
            int c_x = child->x + child->currentwidth / 2;
            int c_y = child->y + child->currentheight / 2;

            if (is_multi)
              d = iSqr(c_x - r_x) + iSqr(c_y - r_y );
            else
            {
              if (is_horizontal)
                d = abs(c_x - r_x );
              else
                d = abs(c_y - r_y );
            }

            if (child == container->firstchild || d < d_min)
            {
              d_min = d;
              child_near = child;
            }
          }
        }

        if ( ! child_near) /* empty container */
        {
          if (is_horizontal)  /* insertion line will be a vertical line to mark an horizontal position */
          {
            int y1 = container_y;
            int y2 = container_y + container_h - 1;
            int xx = container_x;

            iupAttribSetStrf( data, canvas, "INSERTCURSOR_LINE", "%d,%d,%d,%d", xx, y1, xx, y2 );
            iupAttribSet( data, canvas, "INSERTCURSOR_POINT", NULL );
            iupAttribSet( data, canvas, "INSERTCURSOR_ELEMENT_POS", NULL );
            iupAttribSet( data, canvas, "INSERTCURSOR_ELEMENT", NULL );
            iupAttribSet( data, canvas, "INSERTCURSOR_BEFORE", NULL );
            amy_IupRedraw( data, canvas, 0 );
            return IUP_DEFAULT;
          }
          else /* ORIENTATION=VERTICAL */    /* insertion line will be an horizontal line to mark a vertical position */
          {
            int x1 = container_x;
            int x2 = container_x + container_w - 1;
            int yy = container_y;

            iupAttribSetStrf( data, canvas, "INSERTCURSOR_LINE", "%d,%d,%d,%d", x1, yy, x2, yy );
            iupAttribSet( data, canvas, "INSERTCURSOR_POINT", NULL );
            iupAttribSet( data, canvas, "INSERTCURSOR_ELEMENT_POS", NULL );
            iupAttribSet( data, canvas, "INSERTCURSOR_ELEMENT", NULL );
            iupAttribSet( data, canvas, "INSERTCURSOR_BEFORE", NULL );
            amy_IupRedraw( data, canvas, 0 );
            return IUP_DEFAULT;
          }
        }
        else
        {
          if (is_horizontal)  /* insertion line will be a vertical line to mark an horizontal position */
          {
            int c_x = child_near->x + child_near->currentwidth / 2;
            int xx;
            int y1;
            int y2;
            int insert_before = 0;

            if (is_multi)
            {
              y1 = native_parent_y + child_near->y;
              y2 = native_parent_y + child_near->y + child_near->currentheight - 1;

              if (r_x < c_x)
              {
                insert_before = 1;
                xx = native_parent_x + child_near->x;
              }
              else
                xx = native_parent_x + child_near->x + child_near->currentwidth - 1;
            }
            else
            {
              y1 = container_y;
              y2 = container_y + container_h - 1;

              if (r_x < c_x)
              {
                insert_before = 1;
                xx = native_parent_x + iLayoutGetBetweenPosX( data, NULL, child_near );
              }
              else
                xx = native_parent_x + iLayoutGetBetweenPosX( data, child_near, NULL );
            }

            iupAttribSetStrf( data, canvas, "INSERTCURSOR_LINE", "%d,%d,%d,%d", xx, y1, xx, y2 );
            iupAttribSet( data, canvas, "INSERTCURSOR_ELEMENT", (char*)child_near );
            iupAttribSetInt( data, canvas, "INSERTCURSOR_BEFORE", insert_before );
            iupAttribSet( data, canvas, "INSERTCURSOR_POINT", NULL );
            iupAttribSet( data, canvas, "INSERTCURSOR_ELEMENT_POS", NULL );
            amy_IupRedraw( data, canvas, 0 );
            return IUP_DEFAULT;
          }
          else /* ORIENTATION=VERTICAL */    /* insertion line will be an horizontal line to mark a vertical position */
          {
            int c_y = child_near->y + child_near->currentheight / 2;
            int yy;
            int x1;
            int x2;
            int insert_before = 0;

            if (is_multi)
            {
              x1 = native_parent_x + child_near->x;
              x2 = native_parent_x + child_near->x + child_near->currentwidth - 1;

              if (r_y < c_y)
              {
                insert_before = 1;
                yy = native_parent_y + child_near->y;
              }
              else
                yy = native_parent_y + child_near->y + child_near->currentheight - 1;
            }
            else
            {
              x1 = container_x;
              x2 = container_x + container_w - 1;

              if (r_y < c_y)
              {
                insert_before = 1;
                yy = native_parent_y + iLayoutGetBetweenPosY( data, NULL, child_near );
              }
              else
                yy = native_parent_y + iLayoutGetBetweenPosY( data, child_near, NULL );
            }

            iupAttribSetStrf( data, canvas, "INSERTCURSOR_LINE", "%d,%d,%d,%d", x1, yy, x2, yy );
            iupAttribSet( data, canvas, "INSERTCURSOR_ELEMENT", (char*)child_near );
            iupAttribSetInt( data, canvas, "INSERTCURSOR_BEFORE", insert_before );
            iupAttribSet( data, canvas, "INSERTCURSOR_POINT", NULL );
            iupAttribSet( data, canvas, "INSERTCURSOR_ELEMENT_POS", NULL );
            amy_IupRedraw( data, canvas, 0 );
            return IUP_DEFAULT;
          }
        }
      }
    }
  }
  
  if (iupAttribGet( data, canvas, "INSERTCURSOR" ))
  {
    iupAttribSet( data, canvas, "INSERTCURSOR", NULL );
    iupAttribSet( data, canvas, "INSERTCURSOR_POINT", NULL );
    iupAttribSet( data, canvas, "INSERTCURSOR_ELEMENT_POS", NULL );
    iupAttribSet( data, canvas, "INSERTCURSOR_LINE", NULL );
    iupAttribSet( data, canvas, "INSERTCURSOR_ELEMENT", NULL );
    iupAttribSet( data, canvas, "INSERTCURSOR_BEFORE", NULL );
    amy_IupRedraw( data, canvas, 0 );
  }

  return IUP_DEFAULT;
}

static int iLayoutCanvasResize_CB( struct libData *data, Ihandle *canvas, int canvas_w, int canvas_h)
{
  amy_IupSetInt( data, canvas, "DX", canvas_w );
  amy_IupSetInt( data, canvas, "DY", canvas_h );
  return IUP_DEFAULT;
}

/***************************************************************************
                              Layout Tree
***************************************************************************/


static int iLayoutTreeExecuteNode_CB( struct libData *data, Ihandle *tree, int id)
{
  Ihandle *elem = (Ihandle*) amy_IupTreeGetUserId( data,  tree, id );
  Ihandle *dlg = amy_IupGetDialog( data, tree );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );

  if ( layoutdlg->new_elem_class)
  {
    Ihandle *canvas = iLayoutGetCanvas( data, layoutdlg );

    if (elem->iclass->childtype == IUP_CHILDNONE)
    {
      iupAttribSet( data, canvas, "INSERTCURSOR", (char*)elem->parent );  /* container */
      iupAttribSet( data, canvas, "INSERTCURSOR_ELEMENT", (char*)elem );
    }
    else
    {
      iupAttribSet( data, canvas, "INSERTCURSOR", (char*)elem );
      iupAttribSet( data, canvas, "INSERTCURSOR_ELEMENT", NULL );
    }

    iupAttribSet( data, canvas, "INSERTCURSOR_ELEMENT_POS", NULL );
    iupAttribSet( data, canvas, "INSERTCURSOR_BEFORE", NULL );
    iupAttribSet( data, canvas, "INSERTCURSOR_POINT", NULL );
    iupAttribSet( data, canvas, "INSERTCURSOR_LINE", NULL );

    /* use new_elem_class to insert a new element at cursor */
    iLayoutNewInsertCursor( data, canvas, layoutdlg->new_elem_class );

    iupAttribSet( data, tree, "_IUP_NEWELEM_EXECUTE", "1" );
  }
  else
  {
    iLayoutBlink( data, elem );

    iupAttribSet( data, tree, "_IUP_NEWELEM_EXECUTE", NULL );
  }

  return IUP_DEFAULT;
}

static int iLayoutTreeBranchClose_CB( struct libData *data, Ihandle *tree, int id)
{
  Ihandle *dlg = amy_IupGetDialog( data, tree );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );

  if ( layoutdlg->new_elem_class && iupAttribGet( data, tree, "_IUP_NEWELEM_EXECUTE" ))
    return IUP_IGNORE;

  (void)id;
  return IUP_DEFAULT;
}

static int iLayoutTreeRightClick_CB( struct libData *data, Ihandle *tree, int id)
{
  Ihandle *dlg = amy_IupGetDialog( data, tree );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  Ihandle *elem = (Ihandle*) amy_IupTreeGetUserId( data,  tree, id );
  iLayoutContextMenu( data, layoutdlg, elem, dlg );
  return IUP_DEFAULT;
}

static int iLayoutTreeDragDrop_CB( struct libData *data, Ihandle *tree, int drag_id, int drop_id, int isshift, int iscontrol)
{
  Ihandle *dlg = amy_IupGetDialog( data, tree );
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  Ihandle *drag_elem = (Ihandle*) amy_IupTreeGetUserId( data,  tree, drag_id );
  Ihandle *drop_elem = (Ihandle*) amy_IupTreeGetUserId( data,  tree, drop_id );
  int error;

  /* no support for copy */
  if (iscontrol)
  {
    iLayoutError( data, layoutdlg, "Copy not supported for drag&drop." );
    return IUP_IGNORE;
  }

  if (drag_elem->flags & IUP_INTERNAL)
  {
    iLayoutError( data, layoutdlg, "Can NOT drag an internal element. This element exists only inside this container." );
    return IUP_IGNORE;
  }

  if (iupStrEqualNoCase( amy_IupGetAttributeId( data, tree, "KIND", drop_id), "BRANCH" ) &&
      iupStrEqualNoCase( amy_IupGetAttributeId( data, tree, "STATE", drop_id), "EXPANDED" ))
  {
    Ihandle *ref_child = drop_elem->firstchild;   /* the first child as reference */

    /* if first element is internal, use the next one. */
    if (drop_elem->firstchild && (drop_elem->firstchild->flags & IUP_INTERNAL))
    {
      /* the first child is internal, so use brother as reference */
      if (drop_elem->firstchild->brother)
        ref_child = drop_elem->firstchild->brother;
    }

    if (drop_elem == drag_elem->parent && ref_child == drag_elem)
    {
      /* dropped at the same place, just ignore it */
      return IUP_IGNORE;
    }

    /* If the drop node is a branch and it is expanded, */
    /* add as first child */
    error = amy_IupReparent( data, drag_elem, drop_elem, ref_child );  /* add before the reference */
  }
  else
  {
    if ( ! drop_elem->parent)
    {
      iLayoutError( data, layoutdlg, "Can NOT drop here as brother." );
      return IUP_IGNORE;
    }

    if (drop_elem->parent == drag_elem->parent && drop_elem->brother == drag_elem)
    {
      /* dropped at the same place, just ignore it */
      return IUP_IGNORE;
    }

    /* If the branch is not expanded or the drop node is a leaf, */
    /* add as brother after reference */
    error = amy_IupReparent( data, drag_elem, drop_elem->parent, drop_elem->brother );  /* drop_elem->brother can be NULL here */
  }

  if (error == IUP_ERROR)
  {
    iLayoutError( data, layoutdlg, "Drop failed. Invalid operation for this node." );
    return IUP_IGNORE;
  }

  layoutdlg->changed = 1;

  iLayoutRefreshLayout( data, layoutdlg );

  iLayoutCallLayoutChangedCb( data, layoutdlg, drag_elem );

  /* since we are only moving existing nodes,
     title, map state, and user data was not changed.
     there is no need to update the node info */

  (void)isshift;
  return IUP_CONTINUE;  /* the nodes of the tree will be automatically moved */
}

static int iLayoutTreeSelection_CB( struct libData *data, Ihandle *tree, int id, int status)
{
  Ihandle *elem = (Ihandle*) amy_IupTreeGetUserId( data,  tree, id );
  if (status == 1)
  {
    Ihandle *dlg = amy_IupGetDialog( data, tree );
    iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
    iLayoutTreeSelectionChanged( data, layoutdlg, elem, id );
    amy_IupUpdate( data, iLayoutGetCanvas( data, layoutdlg));
  }
  else
    iLayoutTreeSetNodeColor( data, tree, id, elem );

  iupAttribSet( data, tree, "_IUP_NEWELEM_EXECUTE", NULL );
  return IUP_DEFAULT;
}


/***************************************************************************
                            Layout Dialog Callbacks
***************************************************************************/


static int iLayoutDialogKAny_CB( struct libData *data, Ihandle *dlg, int key)
{
  switch (key)
  {
  case K_DEL:
    return iLayoutContextMenuRemove_CB( data, dlg );
  case K_cF5:
    return iLayoutMenuRebuildTree_CB( data, dlg );
  case K_ESC:
  {
    iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
    if ( layoutdlg->new_elem_class)
    {
      Ihandle *tgl = amy_IupGetDialogChild( data, dlg, "TOGGLE_SELECT" );
      amy_IupSetAttribute( data, tgl, "VALUE", "ON" );
      layoutdlg->new_elem_class = NULL;
    }
    else
      return iLayoutMenuClose_CB( data, dlg );
  }
  case K_F5:
    return iLayoutMenuRefresh_CB( data, dlg );
  case K_F3:
  {
    Ihandle *find_dlg = (Ihandle*) amy_IupGetAttribute( data, dlg, "FIND_ELEM_DIALOG" );
    if ( ! find_dlg)
      return iLayoutMenuFindElement_CB( data, dlg );
    else
      return iLayoutFindDialogNext_CB( data, find_dlg );
  }
  case K_cF:
    return iLayoutMenuFindElement_CB( data, dlg );
  case K_cMinus:
  case K_cPlus:
    {
      int opacity = amy_IupGetInt( data, dlg, "OPACITY" );
      if (opacity == 0)
        opacity = 255;
      if (key == K_cPlus)
        opacity++;
      else
        opacity--;
      if (opacity == 0 || opacity == 255)
        amy_IupSetAttribute( data, dlg, "OPACITY", NULL );
      else
        amy_IupSetInt( data, dlg, "OPACITY", opacity );
      break;
    }
  }

  return IUP_DEFAULT;
}

static int iLayoutDialogClose_CB( struct libData *data, Ihandle *dlg )
{
  if ( amy_IupGetInt( data, dlg, "DESTROYWHENCLOSED" ))
  {
    amy_IupDestroy( data, dlg );
    return IUP_IGNORE;
  }
  return IUP_DEFAULT;
}

static int iLayoutDialogDestroy_CB( struct libData *data, Ihandle *dlg )
{
  iLayoutDialog *layoutdlg = (iLayoutDialog*) iupAttribGet( data, dlg, "_IUP_LAYOUTDIALOG" );
  amy_IupDestroy( data, layoutdlg->timer );
  if (iupObjectCheck( data, layoutdlg->globals))
    amy_IupDestroy( data, layoutdlg->globals );
  if (iupObjectCheck( data, layoutdlg->properties))
    amy_IupDestroy( data, layoutdlg->properties );
  if ( layoutdlg->destroy && iupObjectCheck( data, layoutdlg->dialog))
    amy_IupDestroy( data, layoutdlg->dialog );
  free( layoutdlg );
  return IUP_DEFAULT;
}

IUP_API Ihandle *amy_IupLayoutDialog( struct libData *data, Ihandle *dialog )
{
  Ihandle *tree, *canvas, *dlg, *menu, *status, *split;
  iLayoutDialog *layoutdlg;

  layoutdlg = calloc(1, sizeof(iLayoutDialog));

  layoutdlg->timer = amy_IupTimer( data );
  amy_IupSetCallback( data, layoutdlg->timer, "ACTION_CB", iLayoutTimerAutoRedraw_CB );
  amy_IupSetAttribute( data, layoutdlg->timer, "TIME", "300" );
  amy_IupSetAttribute( data, layoutdlg->timer, "_IUP_LAYOUTDIALOG", (char*)layoutdlg );

  canvas = amy_IupCanvas( data, NULL );
  amy_IupSetCallback( data, canvas, "ACTION", (Icallback)iLayoutCanvasRedraw_CB );
  amy_IupSetCallback( data, canvas, "BUTTON_CB", (Icallback)iLayoutCanvasButton_CB );
  amy_IupSetCallback( data, canvas, "MOTION_CB", (Icallback)iLayoutCanvasMotion_CB );
  amy_IupSetCallback( data, canvas, "RESIZE_CB", (Icallback)iLayoutCanvasResize_CB );
  amy_IupSetAttribute( data, canvas, "SCROLLBAR", "YES" );
  amy_IupSetAttribute( data, canvas, "XAUTOHIDE", "NO" );
  amy_IupSetAttribute( data, canvas, "YAUTOHIDE", "NO" );
  amy_IupSetAttribute( data, canvas, "BORDER", "NO" );

  tree = amy_IupTree( data );
  layoutdlg->tree = tree;
  amy_IupSetAttribute( data, tree, "NAME", "TREE" );
  amy_IupSetAttribute( data, tree, "RASTERSIZE", NULL );
  amy_IupSetAttribute( data, tree, "USERSIZE", "200x" );
  amy_IupSetAttribute( data, tree, "SHOWDRAGDROP", "Yes" );
  amy_IupSetCallback( data, tree, "SELECTION_CB", (Icallback)iLayoutTreeSelection_CB );
  amy_IupSetCallback( data, tree, "EXECUTELEAF_CB", (Icallback)iLayoutTreeExecuteNode_CB );
  amy_IupSetCallback( data, tree, "EXECUTEBRANCH_CB", (Icallback)iLayoutTreeExecuteNode_CB );
  amy_IupSetCallback( data, tree, "BRANCHCLOSE_CB", (Icallback)iLayoutTreeBranchClose_CB );
  amy_IupSetCallback( data, tree, "RIGHTCLICK_CB", (Icallback)iLayoutTreeRightClick_CB );
  amy_IupSetCallback( data, tree, "DRAGDROP_CB", (Icallback)iLayoutTreeDragDrop_CB );
  amy_IupSetAttribute( data, tree, "IMAGELEAF", "IMGEMPTY" );

  split = amy_IupSplit( data, tree, canvas );
  amy_IupSetAttribute( data, split, "VALUE", "300" );
  amy_IupSetAttribute( data, split, "AUTOHIDE", "Yes" );

  status = amy_IupLabel( data, NULL );
  amy_IupSetAttribute( data, status, "EXPAND", "HORIZONTAL" );
  amy_IupSetAttribute( data, status, "FONT", "Courier, 11" );
  amy_IupSetAttribute( data, status, "SIZE", "x20" );
  layoutdlg->status = status;

  if ( ! layoutdlg->destroy && iupAttribGet( data, dialog, "_IUPLED_FILENAME" ))
  {
    /* these images are available only in amy_IupVisualLED */
    Ihandle *new_elem_box = amy_IupVbox( data,
      amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutArrowCursor, TIP=\"Select elements on layout.\nThe other options are only part of the IUP available classes,\nother classes can be selected at the dialog from the context menu\", NAME=TOGGLE_SELECT" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
      amy_IupSetAttributes( data, amy_IupFlatSeparator( data ), "RASTERSIZE=x14, ORIENTATION=HORIZONTAL" ),
      amy_IupHbox( data,
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutHbox, TIP=\"Insert a Hbox at cursor when click at layout or double click at tree \", _IUP_CLASS=hbox" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutVbox, TIP=\"Insert a Vbox at cursor when click at layout or double click at tree \", _IUP_CLASS=vbox" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        NULL),
      amy_IupHbox( data,
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutZbox, TIP=\"Insert a Zbox at cursor when click at layout or double click at tree \", _IUP_CLASS=zbox" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutCbox, TIP=\"Insert a Cbox at cursor when click at layout or double click at tree \", _IUP_CLASS=cbox" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        NULL),
      amy_IupHbox( data,
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutGridBox, TIP=\"Insert a GridBox at cursor when click at layout or double click at tree .\nPress Shift to select a MultiBox\", _IUP_CLASS=gridbox, _IUP_CLASS_ALT=multibox" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutScrollBox, TIP=\"Insert a ScrollBox at cursor when click at layout or double click at tree .\nPress Shift to select a FlatScrollBox\", _IUP_CLASS=scrollbox, _IUP_CLASS_ALT=flatscrollbox" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        NULL),
      amy_IupHbox( data,
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutSplit, TIP=\"Insert a Split at cursor when click at layout or double click at tree \", _IUP_CLASS=split" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutExpander, TIP=\"Insert a Expander at cursor when click at layout or double click at tree \", _IUP_CLASS=expander" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        NULL),
      amy_IupHbox( data,
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutFill, TIP=\"Insert a Fill at cursor when click at layout or double click at tree .\nPress Shift to select a Space\", _IUP_CLASS=fill, _IUP_CLASS_ALT=space" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutFlatSeparator, TIP=\"Insert a FlatSeparator at cursor when click at layout or double click at tree \", _IUP_CLASS=flatseparator" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        NULL),
      amy_IupHbox( data,
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutFrame, TIP=\"Insert a Frame at cursor when click at layout or double click at tree .\nPress Shift to select a FlatFrame\", _IUP_CLASS=frame, _IUP_CLASS_ALT=flatframe" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutTabs, TIP=\"Insert a Tabs at cursor when click at layout or double click at tree .\nPress Shift to select a FlatTabs\", _IUP_CLASS=tabs, _IUP_CLASS_ALT=flattabs" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        NULL),
      amy_IupSetAttributes( data, amy_IupFlatSeparator( data ), "RASTERSIZE=x14, ORIENTATION=HORIZONTAL" ),
      amy_IupHbox( data,
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutLabel, TIP=\"Insert a Label at cursor when click at layout or double click at tree .\nPress Shift to select a FlatLabel\", _IUP_CLASS=label, _IUP_CLASS_ALT=flatlabel" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutButton, TIP=\"Insert a Button at cursor when click at layout or double click at tree .\nPress Shift to select a FlatButton\", _IUP_CLASS=button, _IUP_CLASS_ALT=flatbutton" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        NULL),
      amy_IupHbox( data,
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutToggle, TIP=\"Insert a Toggle at cursor when click at layout or double click at tree .\nPress Shift to select a FlatToggle\", _IUP_CLASS=toggle, _IUP_CLASS_ALT=flattoggle" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutRadio, TIP=\"Insert a Radio at cursor when click at layout or double click at tree \", _IUP_CLASS=radio" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        NULL),
      amy_IupHbox( data,
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutList, TIP=\"Insert a List at cursor when click at layout or double click at tree .\nPress Shift to select a FlatList\", _IUP_CLASS=list, _IUP_CLASS_ALT=flatlist" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutTree, TIP=\"Insert a Tree at cursor when click at layout or double click at tree .\nPress Shift to select a FlatTree\", _IUP_CLASS=tree, _IUP_CLASS_ALT=flattree" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        NULL),
      amy_IupHbox( data,
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutVal, TIP=\"Insert a Val at cursor when click at layout or double click at tree .\nPress Shift to select a FlatVal\", _IUP_CLASS=val, _IUP_CLASS_ALT=flatval" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutProgressBar, TIP=\"Insert a ProgressBar at cursor when click at layout or double click at tree .\nPress Shift to select a Gauge\", _IUP_CLASS=progressbar, _IUP_CLASS_ALT=gauge" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        NULL),
      amy_IupHbox( data,
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutText, TIP=\"Insert a Text at cursor when click at layout or double click at tree .\nPress Shift to select a Multiline\", _IUP_CLASS=text, _IUP_CLASS_ALT=multiline" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutCanvas, TIP=\"Insert a Canvas at cursor when click at layout or double click at tree .\nPress Shift to select a GLCanvas\", _IUP_CLASS=canvas, _IUP_CLASS_ALT=glcanvas" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        NULL),
      amy_IupSetAttributes( data, amy_IupFlatSeparator( data ), "RASTERSIZE=x14, ORIENTATION=HORIZONTAL" ),
      amy_IupHbox( data,
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutMatrix, TIP=\"Insert a Matrix at cursor when click at layout or double click at tree .\nPress Shift to select a MatrixEx\", _IUP_CLASS=matrix, _IUP_CLASS_ALT=matrixex" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupFlatToggle( data, NULL ), "CHECKSIZE=0, IMAGE=IupLayoutPlot, TIP=\"Insert a Plot at cursor when click at layout or double click at tree \", _IUP_CLASS=plot" ), "FLAT_ACTION", (Icallback)iLayoutElemOptionToggle_cb, NULL),
        NULL),
      NULL );
    amy_IupSetAttribute( data, new_elem_box, "NMARGIN", "5x5" );

    split = amy_IupHbox( data, amy_IupRadio( data, new_elem_box ), split, NULL );
  }

  menu = amy_IupMenu( data,
    amy_IupSubmenu( data, "&Layout", amy_IupMenu( data,
      amy_IupSetCallbacks( data, amy_IupItem( data, "Refresh\tF5", NULL), "ACTION", iLayoutMenuRefresh_CB, NULL),
      amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupItem( data, "Auto Redraw (Timer)", NULL), "AUTOTOGGLE=YES, VALUE=OFF" ), "ACTION", iLayoutMenuAutoRedraw_CB, NULL),
      amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupItem( data, "Show Hidden", NULL), "AUTOTOGGLE=YES, VALUE=OFF" ), "ACTION", iLayoutMenuShowHidden_CB, NULL),
      amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupItem( data, "Show Internal", NULL), "AUTOTOGGLE=YES, VALUE=OFF" ), "ACTION", iLayoutMenuShowInternal_CB, NULL),
      amy_IupSeparator( data ),
      amy_IupSetCallbacks( data, amy_IupSetAttributes( data, amy_IupItem( data, "&Show Tree", NULL), "AUTOTOGGLE=YES, VALUE=ON" ), "ACTION", iLayoutMenuShowTree_CB, NULL),
      amy_IupSetCallbacks( data, amy_IupItem( data, "Rebuild Tree\tCtrl+F5", NULL), "ACTION", iLayoutMenuRebuildTree_CB, NULL),
      amy_IupSeparator( data ),
      amy_IupSetCallbacks( data, amy_IupItem( data, "Opacity\tCtrl+/Ctrl-", NULL), "ACTION", iLayoutMenuOpacity_CB, NULL),
      amy_IupSeparator( data ),
      amy_IupSetCallbacks( data, amy_IupItem( data, "Find Element...\tCtrl+F", NULL), "ACTION", iLayoutMenuFindElement_CB, NULL),
      NULL)),
    amy_IupSetCallbacks( data, amy_IupItem( data, "Element", NULL), "ACTION", iLayoutItemShowContext_CB, NULL),
    NULL );

  if ( layoutdlg->destroy || !iupAttribGet( data, dialog, "_IUPLED_FILENAME" ))
  {
    Ihandle *dlg_menu = amy_IupSubmenu( data, "&Dialog", amy_IupMenu( data,
      amy_IupSetCallbacks( data, amy_IupItem( data, "New", NULL), "ACTION", iLayoutMenuNew_CB, NULL),
      amy_IupSetCallbacks( data, amy_IupItem( data, "Load...\tCtrl+O", NULL), "ACTION", iLayoutMenuLoad_CB, NULL),
      amy_IupSetCallbacks( data, amy_IupItem( data, "Load Visible...", NULL), "ACTION", iLayoutMenuLoadVisible_CB, NULL),
      amy_IupSubmenu( data, "&Export", amy_IupMenu( data,
      amy_IupSetCallbacks( data, amy_IupItem( data, "C...", NULL), "ACTION", iLayoutMenuExportC_CB, NULL),
      amy_IupSetCallbacks( data, amy_IupItem( data, "LED...", NULL), "ACTION", iLayoutMenuExportLED_CB, NULL),
      amy_IupSetCallbacks( data, amy_IupItem( data, "Lua...", NULL), "ACTION", iLayoutMenuExportLua_CB, NULL),
      NULL)),
      amy_IupSeparator( data ),
      amy_IupSetCallbacks( data, amy_IupItem( data, "Reset Size", NULL), "ACTION", iLayoutMenuReset_CB, NULL),
      amy_IupSetCallbacks( data, amy_IupItem( data, "Redraw", NULL), "ACTION", iLayoutMenuRedraw_CB, NULL),
      amy_IupSetCallbacks( data, amy_IupItem( data, "Show", NULL), "ACTION", iLayoutMenuShow_CB, NULL),
      amy_IupSetCallbacks( data, amy_IupItem( data, "Hide", NULL), "ACTION", iLayoutMenuHide_CB, NULL),
      amy_IupSeparator( data ),
      amy_IupSetCallbacks( data, amy_IupItem( data, "&Globals...", NULL), "ACTION", iLayoutMenuGlobals_CB, NULL),
      amy_IupSetCallbacks( data, amy_IupItem( data, "&Close\tEsc", NULL), "ACTION", iLayoutMenuClose_CB, NULL),
      NULL));

    amy_IupInsert( data, menu, NULL, dlg_menu );
  }
  else
  {
    Ihandle *dlg_menu = amy_IupSubmenu( data, "&Dialog", amy_IupMenu( data,
      amy_IupSetCallbacks( data, amy_IupItem( data, "Reset Size", NULL), "ACTION", iLayoutMenuReset_CB, NULL),
      amy_IupSetCallbacks( data, amy_IupItem( data, "Redraw", NULL), "ACTION", iLayoutMenuRedraw_CB, NULL),
      amy_IupSetCallbacks( data, amy_IupItem( data, "Show", NULL), "ACTION", iLayoutMenuShow_CB, NULL),
      amy_IupSetCallbacks( data, amy_IupItem( data, "Hide", NULL), "ACTION", iLayoutMenuHide_CB, NULL),
      NULL));

    amy_IupInsert( data, menu, NULL, dlg_menu );
  }

  dlg = amy_IupDialog( data, amy_IupVbox( data, split, status, NULL));
  amy_IupSetAttribute( data, dlg, "TITLE", "Dialog Layout" );
  amy_IupSetAttribute( data, dlg, "SHRINK", "Yes" );
  amy_IupSetAttribute( data, dlg, "PARENTDIALOG", amy_IupGetGlobal( data, "PARENTDIALOG" ));
  amy_IupSetAttribute( data, dlg, "TREE", (char*)tree );
  amy_IupSetAttribute( data, dlg, "ICON", amy_IupGetGlobal( data, "ICON" ));
  amy_IupSetCallback( data, dlg, "DESTROY_CB", iLayoutDialogDestroy_CB );
  amy_IupSetCallback( data, dlg, "K_ANY", (Icallback)iLayoutDialogKAny_CB );
  amy_IupSetCallback( data, dlg, "CLOSE_CB", iLayoutDialogClose_CB );
  iupAttribSet( data, dlg, "_IUP_LAYOUTDIALOG", (char*)layoutdlg );
  iupAttribSet( data, dlg, "_IUP_LAYOUTDIALOG_DIALOG", (char*)dialog );
  amy_IupSetAttributeHandle( data, dlg, "MENU", menu );
  iupAttribSet( data, dlg, "OPACITY", "255" );

  iupAttribSet( data, dlg, "DESTROYWHENCLOSED", "Yes" );

  if (dialog)
    layoutdlg->dialog = dialog;
  else
  {
    layoutdlg->dialog = amy_IupDialog( data, NULL );
    layoutdlg->destroy = 1;
  }
  iLayoutUpdateTitle( data, dlg, layoutdlg );

  if ( layoutdlg->destroy || !iupAttribGet( data, dialog, "_IUPLED_FILENAME" ))
  {
    amy_IupSetCallback( data, dlg, "K_cO", (Icallback)iLayoutMenuLoad_CB );
  }

  {
    int w = 0, h = 0;
    amy_IupGetIntInt( data, layoutdlg->dialog, "CLIENTSIZE", &w, &h );
    if (w == 0 && h == 0)
    {
      amy_IupRefresh( data, layoutdlg->dialog );
      amy_IupGetIntInt( data, layoutdlg->dialog, "CLIENTSIZE", &w, &h );
    }

    if (w && h)
    {
      int sb = iupdrvGetScrollbarSize( data );
      w += sb;
      h += sb;
      amy_IupSetfAttribute( data, canvas, "USERSIZE", "%dx%d", w, h );
    }
    else
      amy_IupSetAttribute( data, canvas, "USERSIZE", "600x400" );
  }

  amy_IupMap( data, dlg );

  amy_IupSetAttribute( data, canvas, "USERSIZE", NULL );

  iLayoutTreeRebuild( data, layoutdlg );

  return dlg;
}
