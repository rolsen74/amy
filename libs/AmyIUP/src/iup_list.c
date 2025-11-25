
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"
#include "inc/iup_list.h"

// --

#if 0

/** \file
 * \brief List Control
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iup.h"
#include "iupcbs.h"

#include "iup_assert.h"
#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_drv.h"
#include "iup_drvfont.h"
#include "iup_drvinfo.h"
#include "iup_stdcontrols.h"
#include "iup_layout.h"
#include "iup_mask.h"
#include "iup_image.h"
#include "iup_list.h"

#endif

void iupListSingleCallDblClickCb( struct libData *data, Ihandle *ih, IFnis cb, int pos )
{
  char *text;

  if (pos<=0)
    return;

  text = amy_IupGetAttributeId( data, ih, "", pos );

  if (cb( data, ih, pos, text) == IUP_CLOSE)
    amy_IupExitLoop( data );
}

static void iListCallActionCallback( struct libData *data, Ihandle *ih, IFnsii cb, int pos, int state )
{
  char *text;

  if (pos<=0)
    return;

  text = amy_IupGetAttributeId( data, ih, "", pos );

  if (cb( data, ih, text, pos, state) == IUP_CLOSE)
    amy_IupExitLoop( data );
}

void iupListUpdateOldValue( struct libData *data, Ihandle *ih, int pos, int removed )
{
  if ( ! ih->data->has_editbox)
  {
    char *old_value = iupAttribGet( data, ih, "_IUPLIST_OLDVALUE" );
    if (old_value)
    {
      int old_pos = atoi(old_value)-1; /* was in IUP reference, starting at 1 */
      if (ih->data->is_dropdown || !ih->data->is_multiple)
      {
        if (old_pos >= pos)
        {
          if (removed && old_pos == pos)
          {
            /* when the current item is removed nothing remains selected */
            iupAttribSet( data, ih, "_IUPLIST_OLDVALUE", NULL );
          }
          else
            iupAttribSetInt( data, ih, "_IUPLIST_OLDVALUE", removed? old_pos-1: old_pos+1 );
        }
      }
      else
      {
        /* multiple selection on a non drop-down list. */
        char *value = amy_IupGetAttribute( data, ih, "VALUE" );
        iupAttribSetStr( data, ih, "_IUPLIST_OLDVALUE", value );
      }
    }
  }
}

void iupListSingleCallActionCb( struct libData *data, Ihandle *ih, IFnsii cb, int pos )
{
  char *old_str = iupAttribGet( data, ih, "_IUPLIST_OLDVALUE" );
  if (old_str)
  {
    int oldpos = atoi(old_str );
    if (oldpos != pos)
    {
      iListCallActionCallback( data, ih, cb, oldpos, 0 );
      iupAttribSetInt( data, ih, "_IUPLIST_OLDVALUE", pos );
      iListCallActionCallback( data, ih, cb, pos, 1 );
    }
  }
  else
  {
    iupAttribSetInt( data, ih, "_IUPLIST_OLDVALUE", pos );
    iListCallActionCallback( data, ih, cb, pos, 1 );
  }
}

void iupListMultipleCallActionCb( struct libData *data, Ihandle *ih, IFnsii cb, IFns multi_cb, int* pos, int sel_count)
{
  int i, count = iupdrvListGetCount( data, ih );

  char *old_str = iupAttribGet( data, ih, "_IUPLIST_OLDVALUE" );
  int old_count = old_str? (int)strlen(old_str): 0;

  char *str = malloc(count+1 );
  memset(str, '-', count );
  str[count]=0;
  for (i=0; i<sel_count; i++)
    str[pos[i]] = '+';

  if (old_count != count)
  {
    old_count = 0;
    old_str = NULL;
  }

  if (multi_cb)
  {
    int unchanged = 1;

    for (i=0; i<count && old_str; i++)
    {
      if (str[i] == old_str[i] )
        str[i] = 'x';    /* mark unchanged values */
      else
        unchanged = 0;
    }

    if (old_str && unchanged)
    {
      free(str );
      return;
    }

    if (multi_cb( data, ih, str) == IUP_CLOSE)
      amy_IupExitLoop( data );

    for (i=0; i<count && old_str; i++)
    {
      if (str[i] == 'x')
        str[i] = old_str[i];    /* restore unchanged values */
    }
  }
  else
  {
    /* must simulate the click on each item */
    for (i=0; i<count; i++)
    {
      if (i >= old_count)  /* new items, if selected then call the callback */
      {
        if (str[i] == '+')
          iListCallActionCallback( data, ih, cb, i+1, 1 );
      }
      else if (str[i] != old_str[i] )
      {
        if (str[i] == '+')
          iListCallActionCallback( data, ih, cb, i+1, 1 );
        else
          iListCallActionCallback( data, ih, cb, i+1, 0 );
      }
    }
  }

  iupAttribSetStr( data, ih, "_IUPLIST_OLDVALUE", str );
  free(str );
}

int iupListGetPosAttrib( struct libData *data, Ihandle *ih, int pos )
{
  int count;

  pos--; /* IUP items start at 1 */

  if (pos < 0) 
    return -1;

  count = iupdrvListGetCount( data, ih );

  if (pos == count) return -2;
  if (pos > count) return -1;

  return pos;
}

void iupListSetInitialItems( struct libData *data, Ihandle *ih )
{
  char *value;
  int i = 1;
  while ((value = iupAttribGetId( data, ih, "", i))!=NULL)
  {
    iupdrvListAppendItem( data, ih, value );
    iupAttribSetId( data, ih, "", i, NULL );

    i++;
  }
}

char *iupListGetSpacingAttrib( struct libData *data, Ihandle *ih )
{
  if ( ! ih->data->is_dropdown)
    return amy_iupStrReturnInt( data, ih->data->spacing );
  else
    return NULL;
}

char *iupListGetPaddingAttrib( struct libData *data, Ihandle *ih )
{
  if (ih->data->has_editbox)
    return iupStrReturnIntInt(ih->data->horiz_padding, ih->data->vert_padding, 'x' );
  else
    return NULL;
}

char *iupListGetNCAttrib( struct libData *data, Ihandle *ih )
{
  if (ih->data->has_editbox)
    return amy_iupStrReturnInt( data, ih->data->nc );
  else
    return NULL;
}

int iupListSetIdValueAttrib( struct libData *data, Ihandle *ih, int pos, const char *value)
{
  int count = iupdrvListGetCount( data, ih );

  pos--; /* IUP starts at 1 */

  if ( ! value)
  {
    if (pos >= 0 && pos <= count-1)
    {
      if (pos == 0)
      {
        iupdrvListRemoveAllItems( data, ih );
        iupAttribSet( data, ih, "_IUPLIST_OLDVALUE", NULL );
      }
      else
      {
        int i = pos;
        while (i < count)
        {
          iupdrvListRemoveItem( data, ih, pos );
          i++;
        }
      }
    }
  }
  else
  {
    if (pos >= 0 && pos <= count-1)
    {
      iupdrvListRemoveItem( data, ih, pos );
      iupdrvListInsertItem( data, ih, pos, value );
    }
    else if (pos == count)
      iupdrvListAppendItem( data, ih, value );
  }
  return 0;
}

static int iListSetAppendItemAttrib( struct libData *data, Ihandle *ih, const char *value )
{
  if ( ! ih->handle)  /* do not do the action before map, and ignore the call */
    return 0;
  if (value)
    iupdrvListAppendItem( data, ih, value );
  return 0;
}

static int iListSetInsertItemAttrib( struct libData *data, Ihandle *ih, int id, const char *value )
{
  if ( ! ih->handle)  /* do not do the action before map, and ignore the call */
    return 0;
  if (value)
  {
    int pos = iupListGetPosAttrib( data, ih, id );
    if (pos >= 0)
      iupdrvListInsertItem( data, ih, pos, value );
    else if (pos == -2)
      iupdrvListAppendItem( data, ih, value );
  }
  return 0;
}

static int iListSetRemoveItemAttrib( struct libData *data, Ihandle *ih, const char *value )
{
  if ( ! ih->handle)  /* do not do the action before map, and ignore the call */
    return 0;
  if ( ! value || iupStrEqualNoCase(value, "ALL" ))
  {
    iupdrvListRemoveAllItems( data, ih );
    iupAttribSet( data, ih, "_IUPLIST_OLDVALUE", NULL );
  }
  else
  {
    int id;
    if (iupStrToInt( value, &id))
    {
      int pos = iupListGetPosAttrib( data, ih, id );
      if (pos >= 0)
        iupdrvListRemoveItem( data, ih, pos );
    }
  }
  return 0;
}

static int iListGetCount( struct libData *data, Ihandle *ih )
{
  int count;
  if (ih->handle)
    count = iupdrvListGetCount( data, ih );
  else
  {
    count = 0;
    while (iupAttribGetId( data, ih, "", count+1 ))
      count++;
  }
  return count;
}

static char *iListGetCountAttrib( struct libData *data, Ihandle *ih )
{
  return amy_iupStrReturnInt( data, iListGetCount( data, ih ));
}

static int iListSetDropdownAttrib( struct libData *data, Ihandle *ih, const char *value )
{
  /* valid only before map */
  if (ih->handle)
    return 0;

  if (iupStrBoolean(value))
  {
    ih->data->is_dropdown = 1;
    ih->data->is_multiple = 0;
  }
  else
    ih->data->is_dropdown = 0;

  return 0;
}

static char *iListGetDropdownAttrib( struct libData *data, Ihandle *ih )
{
  return iupStrReturnBoolean( ih->data->is_dropdown ); 
}

static int iListSetMultipleAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  /* valid only before map */
  if (ih->handle)
    return 0;

  if (iupStrBoolean(value))
  {
    ih->data->is_multiple = 1;
    ih->data->is_dropdown = 0;
    ih->data->has_editbox = 0;
  }
  else
    ih->data->is_multiple = 0;

  return 0;
}

static char *iListGetMultipleAttrib( struct libData *data, Ihandle *ih )
{
  return iupStrReturnBoolean( ih->data->is_multiple ); 
}

static int iListSetEditboxAttrib( struct libData *data, Ihandle *ih, const char *value )
{
  /* valid only before map */
  if (ih->handle)
    return 0;

  if (iupStrBoolean(value))
  {
    ih->data->has_editbox = 1;
    ih->data->is_multiple = 0;
  }
  else
    ih->data->has_editbox = 0;

  return 0;
}

static char *iListGetEditboxAttrib( struct libData *data, Ihandle *ih )
{
  return iupStrReturnBoolean( ih->data->has_editbox );
}

static int iListSetScrollbarAttrib( struct libData *data, Ihandle *ih, const char *value )
{
  /* valid only before map */
  if (ih->handle)
    return 0;

  else if (iupStrBoolean(value))
    ih->data->sb = 1;
  else
    ih->data->sb = 0;

  return 0;
}

static char *iListGetScrollbarAttrib( struct libData *data, Ihandle *ih )
{
  return iupStrReturnBoolean( ih->data->sb ); 
}

static char *iListGetMaskAttrib( struct libData *data, Ihandle *ih )
{
  if ( ! ih->data->has_editbox)
    return NULL;

  if (ih->data->mask)
    return iupMaskGetStr( data, ih->data->mask );
  else
    return NULL;
}

static int iListSetValueMaskedAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if ( ! ih->data->has_editbox)
    return 0;

  if (value)
  {
    if (ih->data->mask && iupMaskCheck( data, ih->data->mask, value) == 0)
      return 0; /* abort */
    amy_IupStoreAttribute( data, ih, "VALUE", value );
  }
  return 0;
}

static int iListSetMaskNoEmptyAttrib( struct libData *data, Ihandle *ih, const char *value )
{
  if (ih->data->mask)
  {
    int val = iupStrBoolean(value );
    iupMaskSetNoEmpty( data, ih->data->mask, val );
  }
  return 1;
}

static int iListSetMaskCaseIAttrib( struct libData *data, Ihandle *ih, const char *value )
{
  if (ih->data->mask)
  {
    int val = iupStrBoolean(value );
    iupMaskSetCaseI( data, ih->data->mask, val );
  }
  return 1;
}

static int iListSetMaskAttrib( struct libData *data, Ihandle *ih, const char *value )
{
  if ( ! ih->data->has_editbox)
    return 0;

  if ( ! value)
  {
    if (ih->data->mask)
    {
      iupMaskDestroy( data, ih->data->mask );
      ih->data->mask = NULL;
    }
  }
  else
  {
    Imask *mask = iupMaskCreate( data, value );
    if (mask)
    {
      int val = iupAttribGetInt( data, ih, "MASKCASEI" );
      iupMaskSetCaseI( data, mask, val );

      val = iupAttribGetInt( data, ih, "MASKNOEMPTY" );
      iupMaskSetNoEmpty( data, mask, val );

      if (ih->data->mask)
        iupMaskDestroy( data, ih->data->mask );

      ih->data->mask = mask;
      return 0;
    }
  }

  return 0;
}

static int iListSetMaskIntAttrib( struct libData *data, Ihandle *ih, const char *value )
{
  if ( ! ih->data->has_editbox)
    return 0;

  if ( ! value)
  {
    if (ih->data->mask)
    {
      iupMaskDestroy( data, ih->data->mask );
      ih->data->mask = NULL;
    }
  }
  else
  {
    Imask *mask;
    int min, max;

    if (iupStrToIntInt(value, &min, &max, ':')!=2)
      return 0;

    mask = iupMaskCreateInt( data, min, max );
    if (mask)
    {
      int val = iupAttribGetInt( data, ih, "MASKNOEMPTY" );
      iupMaskSetNoEmpty( data, mask, val );

      if (ih->data->mask)
        iupMaskDestroy( data, ih->data->mask );

      ih->data->mask = mask;
      return 1; /* store only a valid mask */
    }
  }

  return 0;
}

static int iListSetMaskFloatAttrib( struct libData *data, Ihandle *ih, const char *value )
{
  if ( ! ih->data->has_editbox)
    return 0;

  if ( ! value)
  {
    if (ih->data->mask)
    {
      iupMaskDestroy( data, ih->data->mask );
      ih->data->mask = NULL;
    }
  }
  else
  {
    Imask *mask;
    float min, max;
    char *decimal_symbol = iupAttribGet( data, ih, "MASKDECIMALSYMBOL" );
    if ( ! decimal_symbol)
      decimal_symbol = amy_IupGetGlobal( data, "DEFAULTDECIMALSYMBOL" );

    if (iupStrToFloatFloat(value, &min, &max, ':')!=2)
      return 0;

    mask = iupMaskCreateFloat( data, min, max, decimal_symbol );
    if (mask)
    {
      int val = iupAttribGetInt( data, ih, "MASKNOEMPTY" );
      iupMaskSetNoEmpty( data, mask, val );

      if (ih->data->mask)
        iupMaskDestroy( data, ih->data->mask );

      ih->data->mask = mask;
      return 1; /* store only a valid mask */
    }
  }

  return 0;
}

static int iListSetMaskRealAttrib( struct libData *data, Ihandle *ih, const char *value )
{
  if ( ! ih->data->has_editbox)
    return 0;

  if ( ! value)
  {
    if (ih->data->mask)
    {
      iupMaskDestroy( data, ih->data->mask );
      ih->data->mask = NULL;
    }
  }
  else
  {
    Imask *mask;
    char *decimal_symbol = iupAttribGet( data, ih, "MASKDECIMALSYMBOL" );
    int positive = 0;

    if (iupStrEqualNoCase(value, "UNSIGNED" ))
      positive = 1;

    mask = iupMaskCreateReal( data, positive, decimal_symbol );
    if (mask)
    {
      int val = iupAttribGetInt( data, ih, "MASKNOEMPTY" );
      iupMaskSetNoEmpty( data, mask, val );

      if (ih->data->mask)
        iupMaskDestroy( data, ih->data->mask );

      ih->data->mask = mask;
      return 1; /* store only a valid mask */
    }
  }

  return 0;
}

static int iListSetShowImageAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  /* valid only before map */
  if (ih->handle)
    return 0;

  if (iupStrBoolean(value))
    ih->data->show_image = 1;
  else
    ih->data->show_image = 0;

  return 0;
}

static char *iListGetShowImageAttrib( struct libData *data, Ihandle *ih )
{
  return iupStrReturnBoolean( ih->data->show_image ); 
}

int iupListCallDragDropCb( struct libData *data, Ihandle *ih, int drag_id, int drop_id, int *is_ctrl)
{
  IFniiii cbDragDrop = (IFniiii) amy_IupGetCallback( data, ih, "DRAGDROP_CB" );
  int is_shift = 0;
  char key[5];
  iupdrvGetKeyState( data, key );
  if (key[0] == 'S')
    is_shift = 1;
  if (key[1] == 'C')
    *is_ctrl = 1;
  else
    *is_ctrl = 0;

  /* ignore a drop that will do nothing */
  if ((*is_ctrl)==0 && (drag_id+1 == drop_id || drag_id == drop_id))
    return IUP_DEFAULT;
  if ((*is_ctrl)!=0 && drag_id == drop_id)
    return IUP_DEFAULT;

  drag_id++;
  if (drop_id < 0)
    drop_id = -1;
  else
    drop_id++;

  if (cbDragDrop)
    return cbDragDrop( data, ih, drag_id, drop_id, is_shift, *is_ctrl );  /* starts at 1 */

  return IUP_CONTINUE; /* allow to move/copy by default if callback not defined */
}

static char *iListGetShowDragDropAttrib( struct libData *data, Ihandle *ih )
{
  return iupStrReturnBoolean( ih->data->show_dragdrop ); 
}

static int iListSetShowDragDropAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  /* valid only before map */
  if (ih->handle)
    return 0;

  if (iupStrBoolean(value))
    ih->data->show_dragdrop = 1;
  else
    ih->data->show_dragdrop = 0;

  return 0;
}


/*****************************************************************************************/


static int iListDropData_CB( struct libData *data, Ihandle *ih, char *type, void *node, int len, int x, int y)
{
  int pos = amy_IupConvertXYToPos( data, ih, x, y );
  int is_ctrl = 0;
  char key[5];

  /* Data is not the pointer, it contains the pointer */
  Ihandle *ih_source;
  memcpy((void*)&ih_source, node, len );  /* but ih_source can be amy_IupList or amy_IupFlatList, can NOT use ih_source->data here */

  if ( ! amy_IupClassMatch( data, ih_source, "list" ) && !amy_IupClassMatch( data, ih_source, "flatlist" ))
    return IUP_DEFAULT;

  /* A copy operation is enabled with the CTRL key pressed, or else a move operation will occur.
     A move operation will be possible only if the attribute DRAGSOURCEMOVE is Yes.
     When no key is pressed the default operation is copy when DRAGSOURCEMOVE=No and move when DRAGSOURCEMOVE=Yes. */
  iupdrvGetKeyState( data, key );
  if (key[1] == 'C')
    is_ctrl = 1;

  if ( amy_IupGetInt( data, ih_source, "MULTIPLE" ))
  {
    char *buffer = amy_IupGetAttribute( data, ih_source, "VALUE" );

    /* Copy all selected items */
    int src_pos = 1;  /* IUP starts at 1 */
    while (buffer[src_pos - 1] != '\0')
    {
      if (buffer[src_pos - 1] == '+')
      {
        iupdrvListInsertItem( data, ih, pos, amy_IupGetAttributeId( data, ih_source, "", src_pos));
        iupdrvListSetImageHandle( data, ih, pos, amy_IupGetAttributeId( data, ih_source, "IMAGENATIVEHANDLE", src_pos));     /* works for amy_IupList and amy_IupFlatList */
        pos++;
      }

      src_pos++;
    }

    if ( amy_IupGetInt( data, ih_source, "DRAGSOURCEMOVE" ) && !is_ctrl)
    {
      /* Remove all item from source if MOVE */
      src_pos = 1;  /* IUP starts at 1 */
      while(*buffer != '\0')
      {
        if (*buffer == '+')
          amy_IupSetInt( data, ih_source, "REMOVEITEM", src_pos );  /* update index in the source */

        src_pos++;
        buffer++;
      }
    }
  }
  else
  {
    int src_pos = amy_IupGetInt( data, ih_source, "VALUE" );
    iupdrvListInsertItem( data, ih, pos, amy_IupGetAttributeId( data, ih_source, "", src_pos));
    iupdrvListSetImageHandle( data, ih, pos, amy_IupGetAttributeId( data, ih_source, "IMAGENATIVEHANDLE", src_pos));    /* works for amy_IupList and amy_IupFlatList */

    if ( amy_IupGetInt( data, ih_source, "DRAGSOURCEMOVE" ) && !is_ctrl)
    {
      src_pos = iupAttribGetInt( data, ih_source, "_IUP_LIST_SOURCEPOS" );
      amy_IupSetInt( data, ih_source, "REMOVEITEM", src_pos );
    }
  }

  (void)type;
  return IUP_DEFAULT;
}

static int iListDragData_CB( struct libData *data, Ihandle *ih, char *type, void *node, int len )
{
  int pos = iupAttribGetInt( data, ih, "_IUP_LIST_SOURCEPOS" );
  if (pos < 1)
    return IUP_DEFAULT;

  if (ih->data->is_multiple)
  {
    char *buffer = amy_IupGetAttribute( data, ih, "VALUE" );

    /* It will not drag all selected items only
       when the user begins to drag an item not selected.
       In this case, unmark all and mark only this item.  */
    if(buffer[pos-1] == '-')
    {
      int buf_len = (int)strlen(buffer );
      amy_IupSetAttribute( data, ih, "SELECTION", "NONE" );
      memset(buffer, '-', buf_len );
      buffer[pos-1] = '+';
      amy_IupSetAttribute( data, ih, "VALUE", buffer );
    }
  }
  else
  {
    /* Single selection */
    amy_IupSetInt( data, ih, "VALUE", pos );
  }

  /* Copy source handle */
  memcpy(node, (void*)&ih, len );
 
  (void)type;
  return IUP_DEFAULT;
}

static int iListDragDataSize_CB( struct libData *data, Ihandle *ih, char *type )
{
  (void)ih;
  (void)type;
  return sizeof(Ihandle *);
}

static int iListDragEnd_CB( struct libData *data, Ihandle *ih, int del)
{
  iupAttribSetInt( data, ih, "_IUP_LIST_SOURCEPOS", 0 );
  (void)del;
  return IUP_DEFAULT;
}

static int iListDragBegin_CB( struct libData *data, Ihandle *ih, int x, int y )
{
  int pos = amy_IupConvertXYToPos( data, ih, x, y );
  iupAttribSetInt( data, ih, "_IUP_LIST_SOURCEPOS", pos );
  return IUP_DEFAULT;
}

static int iListSetDragDropListAttrib( struct libData *data, Ihandle *ih, const char *value )
{
  if (iupStrBoolean(value))
  {
    /* Register callbacks to enable drag and drop between lists */
    amy_IupSetCallback( data, ih, "DRAGBEGIN_CB",    (Icallback)iListDragBegin_CB );
    amy_IupSetCallback( data, ih, "DRAGDATASIZE_CB", (Icallback)iListDragDataSize_CB );
    amy_IupSetCallback( data, ih, "DRAGDATA_CB",     (Icallback)iListDragData_CB );
    amy_IupSetCallback( data, ih, "DRAGEND_CB",      (Icallback)iListDragEnd_CB );
    amy_IupSetCallback( data, ih, "DROPDATA_CB",     (Icallback)iListDropData_CB );
  }
  else
  {
    /* Unregister callbacks */
    amy_IupSetCallback( data, ih, "DRAGBEGIN_CB",    NULL );
    amy_IupSetCallback( data, ih, "DRAGDATASIZE_CB", NULL );
    amy_IupSetCallback( data, ih, "DRAGDATA_CB",     NULL );
    amy_IupSetCallback( data, ih, "DRAGEND_CB",      NULL );
    amy_IupSetCallback( data, ih, "DROPDATA_CB",     NULL );
  }

  return 1;
}

static char *iListGetValueStringAttrib( struct libData *data, Ihandle *ih )
{
  if ( ! ih->data->has_editbox && (ih->data->is_dropdown || !ih->data->is_multiple))
  {
    int i = amy_IupGetInt( data, ih, "VALUE" );
    return amy_IupGetAttributeId( data, ih, "", i );
  }
  return NULL;
}

static int iListSetValueStringAttrib( struct libData *data, Ihandle *ih, const char *value )
{
  if ( ! ih->data->has_editbox && (ih->data->is_dropdown || !ih->data->is_multiple))
  {
    int i, count = iListGetCount( data, ih );

    for (i = 1; i <= count; i++)
    {
      char *item = amy_IupGetAttributeId( data, ih, "", i );
      if (iupStrEqual(value, item))
      {
        amy_IupSetInt( data, ih, "VALUE", i );
        return 0;
      }
    }
  }

  return 0;
}


/*****************************************************************************************/

static int iListCreateMethod( struct libData *data, Ihandle *ih, void **params)
{
  if (params && params[0] )
    iupAttribSetStr( data, ih, "ACTION", (char*)(params[0] ));

  ih->data = iupALLOCCTRLDATA();
  ih->data->sb = 1;

  return IUP_NOERROR;
}

static void iListGetItemImageInfo( struct libData *data, Ihandle *ih, int id, int *img_w, int *img_h )
{
  *img_w = 0;
  *img_h = 0;

  if ( ! ih->handle)
  {
    char *value = iupAttribGetId( data, ih, "IMAGE", id );
    if (value)
      iupImageGetInfo( data, value, img_w, img_h, NULL );
  }
  else
  {
    void *handle = iupdrvListGetImageHandle( data, ih, id );
    if (handle)
    {
      int bpp;
      iupdrvImageGetInfo( data, handle, img_w, img_h, &bpp );
    }
  }
}

static void iListGetNaturalItemsSize( struct libData *data, Ihandle *ih, int *w, int *h)
{
  int visiblecolumns, i, 
      max_h = 0,
      count = iListGetCount( data, ih );

  *w = 0;
  *h = 0;

  iupdrvFontGetCharSize( data, ih, w, h );   /* one line height, and one character width */

  visiblecolumns = iupAttribGetInt( data, ih, "VISIBLECOLUMNS" );
  if (visiblecolumns)
  {
    *w = iupdrvFontGetStringWidth( data, ih, "WWWWWWWWWW" );
    *w = (visiblecolumns*(*w))/10;
  }
  else
  {
    char *value;
    int item_w;

    for (i=1; i<=count; i++)
    {
      item_w = 0;

      value = amy_IupGetAttributeId( data, ih, "", i );  /* must use amy_IupGetAttribute to check the native system */
      if (value)
        item_w = iupdrvFontGetStringWidth( data, ih, value );

      if (item_w > *w)
        *w = item_w;
    }

    if (*w == 0) /* default is 5 characters in 1 item */
      *w = iupdrvFontGetStringWidth( data, ih, "WWWWW" );
  }

  if (ih->data->show_image)
  {
    int max_w = 0;
    for (i=1; i<=count; i++)
    {
      int img_w, img_h;
      iListGetItemImageInfo( data, ih, i, &img_w, &img_h );
      if (img_w > max_w)
        max_w = img_w;
      if (img_h > max_h)
        max_h = img_h;
    }

    /* Used only in Windows */
    ih->data->maximg_w = max_w;
    ih->data->maximg_h = max_h;

    *w += max_w;
  }

  /* compute height for multiple lines, dropdown is just 1 line */
  if ( ! ih->data->is_dropdown)
  {
    int visiblelines, num_lines, 
        edit_line_size = *h;  /* don't include the highest image */

    if (ih->data->show_image && max_h > *h)  /* use the highest image to compute the natural size */
      *h = max_h;

    iupdrvListAddItemSpace( data, ih, h );  /* this is independent from spacing */

    *h += 2*ih->data->spacing;  /* this will be multiplied by the number of lines */
    *w += 2*ih->data->spacing;  /* include also horizontal spacing */

    num_lines = count;
    if (num_lines == 0) num_lines = 1;

    visiblelines = iupAttribGetInt( data, ih, "VISIBLELINES" );
    if (visiblelines)
      num_lines = visiblelines;   

    *h = *h * num_lines;

    if (ih->data->has_editbox) 
      *h += edit_line_size;
  }
  else
  {
    if ( ! ih->data->has_editbox)
    {
      if (ih->data->show_image && max_h > *h)  /* use the highest image to compute the natural size */
        *h = max_h;
    }
  }
}

static void iListComputeNaturalSizeMethod(  struct libData *data, Ihandle *ih, int *w, int *h, int *children_expand)
{
  int natural_w, natural_h;
  int sb_size = iupdrvGetScrollbarSize( data );
  (void)children_expand; /* unset if not a container */

  iListGetNaturalItemsSize( data, ih, &natural_w, &natural_h );

  /* compute the borders space */
  iupdrvListAddBorders( data, ih, &natural_w, &natural_h );

  if (ih->data->is_dropdown)
  {
    /* add room for dropdown box */
    natural_w += sb_size;

    if (natural_h < sb_size)
      natural_h = sb_size;
  }
  else
  {
    /* add room for scrollbar */
    if (ih->data->sb)
    {
      natural_h += sb_size;
      natural_w += sb_size;
    }
  }

  if (ih->data->has_editbox)
  {
    natural_w += 2*ih->data->horiz_padding;
    natural_h += 2*ih->data->vert_padding;
  }

  *w = natural_w;
  *h = natural_h;
}

static void iListDestroyMethod( struct libData *data, Ihandle *ih )
{
  if (ih->data->mask)
    iupMaskDestroy( data, ih->data->mask );
}


/******************************************************************************/

IUP_API Ihandle *amy_IupList( struct libData *data, const char *action )
{
  void *params[2];
  params[0] = (void*)action;
  params[1] = NULL;
  return amy_IupCreatev( data, "list", params );
}

Iclass *iupListNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, NULL );

  ic->name = "list";
  ic->format = "a"; /* one ACTION callback name */
  ic->nativetype = IUP_TYPECONTROL;
  ic->childtype = IUP_CHILDNONE;
  ic->is_interactive = 1;
  ic->has_attrib_id = 1;

  /* Class functions */
  ic->New = iupListNewClass;
  ic->Create = iListCreateMethod;
  ic->Destroy = iListDestroyMethod;
  ic->ComputeNaturalSize = iListComputeNaturalSizeMethod;

  ic->LayoutUpdate = iupdrvBaseLayoutUpdateMethod;
  ic->UnMap = iupdrvBaseUnMapMethod;

  /* Callbacks */
  iupClassRegisterCallback( data, ic, "ACTION", "sii" );
  iupClassRegisterCallback( data, ic, "MULTISELECT_CB", "s" );
  iupClassRegisterCallback( data, ic, "DROPDOWN_CB", "i" );
  iupClassRegisterCallback( data, ic, "DBLCLICK_CB", "is" );
  iupClassRegisterCallback( data, ic, "VALUECHANGED_CB", "" );
  iupClassRegisterCallback( data, ic, "MOTION_CB", "iis" );
  iupClassRegisterCallback( data, ic, "BUTTON_CB", "iiiis" );
  iupClassRegisterCallback( data, ic, "DRAGDROP_CB", "iiii" );

  iupClassRegisterCallback( data, ic, "EDIT_CB", "is" );
  iupClassRegisterCallback( data, ic, "CARET_CB", "iii" );

  /* Common Callbacks */
  iupBaseRegisterCommonCallbacks( data, ic );

  /* Common */
  iupBaseRegisterCommonAttrib( data, ic );

  /* Visual */
  iupBaseRegisterVisualAttrib( data, ic );

  /* Drag&Drop */
  iupdrvRegisterDragDropAttrib( data, ic );

  /* amy_IupList only */
  iupClassRegisterAttribute( data, ic, "SCROLLBAR", iListGetScrollbarAttrib, iListSetScrollbarAttrib, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "AUTOHIDE", NULL, NULL, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "MULTIPLE", iListGetMultipleAttrib, iListSetMultipleAttrib, NULL, NULL, IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DROPDOWN", iListGetDropdownAttrib, iListSetDropdownAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "EDITBOX", iListGetEditboxAttrib, iListSetEditboxAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "COUNT", iListGetCountAttrib, NULL, NULL, NULL, IUPAF_READONLY|IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "VALUESTRING", iListGetValueStringAttrib, iListSetValueStringAttrib, NULL, NULL, IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CPADDING", iupBaseGetCPaddingAttrib, iupBaseSetCPaddingAttrib, NULL, NULL, IUPAF_NO_SAVE | IUPAF_NOT_MAPPED );
  iupClassRegisterAttribute( data, ic, "CSPACING", iupBaseGetCSpacingAttrib, iupBaseSetCSpacingAttrib, NULL, NULL, IUPAF_NO_SAVE | IUPAF_NOT_MAPPED );

  iupClassRegisterAttributeId( data, ic, "INSERTITEM", NULL, iListSetInsertItemAttrib, IUPAF_WRITEONLY | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "APPENDITEM", NULL, iListSetAppendItemAttrib, NULL, NULL, IUPAF_WRITEONLY | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "REMOVEITEM", NULL, iListSetRemoveItemAttrib, NULL, NULL, IUPAF_WRITEONLY | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "VALUEMASKED", NULL, iListSetValueMaskedAttrib, NULL, NULL, IUPAF_WRITEONLY | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MASKCASEI", NULL, iListSetMaskCaseIAttrib, NULL, NULL, IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MASKDECIMALSYMBOL", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MASK", iListGetMaskAttrib, iListSetMaskAttrib, NULL, NULL, IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MASKINT", NULL, iListSetMaskIntAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MASKFLOAT", NULL, iListSetMaskFloatAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MASKREAL", NULL, iListSetMaskRealAttrib, NULL, NULL, IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MASKNOEMPTY", NULL, iListSetMaskNoEmptyAttrib, NULL, NULL, IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "VISIBLECOLUMNS", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "VISIBLELINES", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "SHOWIMAGE", iListGetShowImageAttrib, iListSetShowImageAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "SHOWDRAGDROP", iListGetShowDragDropAttrib, iListSetShowDragDropAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DRAGDROPLIST", NULL, iListSetDragDropListAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );

  iupdrvListInitClass( data, ic );

  return ic;
}
