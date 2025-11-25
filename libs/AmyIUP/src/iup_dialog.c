
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#define _IUPDLG_PRIVATE
#include "inc/All.h"
#include "inc/iup_dialog.h"

// --

#if 0

/** \file
 * \brief amy_IupDialog class
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdarg.h>
#include <assert.h>

#include "iup.h"
#include "iupcbs.h"

#include "iup_class.h"
#include "iup_object.h"
#include "iup_dlglist.h"
#include "iup_layout.h"
#include "iup_attrib.h"
#include "iup_drv.h"
#include "iup_drvinfo.h"
#include "iup_drvfont.h"
#include "iup_focus.h"
#include "iup_str.h"
#define _IUPDLG_PRIVATE
#include "iup_dialog.h"

#endif

static int dlg_popup_level = 1;

IUP_SDK_API InativeHandle *iupDialogGetNativeParent( struct libData *data, Ihandle *ih)
{
  Ihandle *parent = amy_IupGetAttributeHandle( data, ih, "PARENTDIALOG" );
  if (parent && parent->handle)
    return parent->handle;
  else
    return (InativeHandle*) iupAttribGet( data, ih, "NATIVEPARENT" );
}

static char *iDialogGetBorderSizeAttrib( struct libData *data, Ihandle *ih)
{
  int border, caption, menu;
  iupdrvDialogGetDecoration( data, ih, &border, &caption, &menu );
  return amy_iupStrReturnInt( data, border );
}

char *iupDialogGetClientSizeAttrib( struct libData *data, Ihandle *ih )
{
  int width = ih->currentwidth, height = ih->currentheight;
  int border = 0, caption = 0, menu = 0;
  iupdrvDialogGetDecoration( data, ih, &border, &caption, &menu );
  width -= 2 * border;
  height -= 2 * border + caption + menu;
  if (width < 0) width = 0;
  if (height < 0) height = 0;
  return iupStrReturnIntInt(width, height, 'x' );
}

int iupDialogSetClientSizeAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  int width = 0, height = 0;
  int border = 0, caption = 0, menu = 0;
  iupStrToIntInt(value, &width, &height, 'x' );
  iupdrvDialogGetDecoration( data, ih, &border, &caption, &menu );
  if (width) width = width + 2*border;
  if (height) height = height + 2*border + caption + menu;
  amy_IupSetfAttribute( data, ih, "RASTERSIZE", "%dx%d", width, height );
  return 0;
}

static void iDialogAdjustPos( struct libData *data, Ihandle *ih, int *x, int *y)
{
  int cursor_x = 0, cursor_y = 0;
  int screen_width = 0, screen_height = 0;
  int current_x = 0, current_y = 0;
  int parent_x = 0, parent_y = 0;
  int parent_width = 0, parent_height = 0;

  /* the dialog is already mapped here */

  if (*x == IUP_CURRENT || *y == IUP_CURRENT)
  {
    /* if first time, there is no current position */
    if ( ! ih->data->first_show)
    {
      int center = IUP_CENTER;
      InativeHandle *parent = iupDialogGetNativeParent( data, ih );
      if (parent)
        center = IUP_CENTERPARENT;

      if (*x == IUP_CURRENT) *x = center;
      if (*y == IUP_CURRENT) *y = center;
    }
    else
      iupdrvDialogGetPosition( data, ih, NULL, &current_x, &current_y );
  }

  if (*x == IUP_CENTER || *y == IUP_CENTER ||
      *x == IUP_RIGHT  || *y == IUP_RIGHT)
    iupdrvGetScreenSize( data, &screen_width, &screen_height );

  if (*x == IUP_CENTERPARENT || *y == IUP_CENTERPARENT ||
      *x == IUP_LEFTPARENT   || *y == IUP_TOPPARENT    || 
      *x == IUP_RIGHTPARENT  || *y == IUP_BOTTOMPARENT)
  {
    InativeHandle *parent = iupDialogGetNativeParent( data, ih );
    if (parent)
    {
      Ihandle *ih_parent = amy_IupGetAttributeHandle( data, ih, "PARENTDIALOG" );
      iupdrvDialogGetPosition( data, ih_parent, parent, &parent_x, &parent_y );
      iupdrvDialogGetSize( data, ih_parent, parent, &parent_width, &parent_height );
    }
    else
    {
      iupdrvGetScreenSize( data, &screen_width, &screen_height );
      parent_width = screen_width;
      parent_height = screen_height;
    }
  }

  if (*x == IUP_MOUSEPOS || *y == IUP_MOUSEPOS)
    iupdrvGetCursorPos( data, &cursor_x, &cursor_y );

  if (iupAttribGetBoolean( data, ih, "MDICHILD" ))
  {
    Ihandle *client = (Ihandle*) iupAttribGet( data, ih, "MDICLIENT_HANDLE" );
    if (client)
    {
      /* position is relative to mdi client */
      parent_x = 0; 
      parent_y = 0;

      /* screen/parent size is now the size of the mdi client */
      parent_width = screen_width = client->currentwidth;
      parent_height = screen_height = client->currentheight;

      iupdrvScreenToClient( data, client, &current_x, &current_y );
      iupdrvScreenToClient( data, client, &cursor_x, &cursor_y );
    }
  }

  switch (*x)
  {
  case IUP_CENTERPARENT:
    *x = (parent_width - ih->currentwidth)/2 + parent_x;
    break;
  case IUP_CENTER:
    *x = (screen_width - ih->currentwidth)/2;
    break;
  case IUP_LEFT:
    *x = 0;
    break;
  case IUP_RIGHT:
    *x = screen_width - ih->currentwidth;
    break;
  case IUP_LEFTPARENT:
    *x = parent_x;
    break;
  case IUP_RIGHTPARENT:
    *x = parent_width - ih->currentwidth + parent_x;
    break;
  case IUP_MOUSEPOS:
    *x = cursor_x;
    break;
  case IUP_CURRENT:
    *x = current_x;
    break;
  }

  switch (*y)
  {
  case IUP_CENTERPARENT:
    *y = (parent_height - ih->currentheight)/2 + parent_y;
    break;
  case IUP_CENTER:
    *y = (screen_height - ih->currentheight)/2;
    break;
  case IUP_TOP:
    *y = 0;
    break;
  case IUP_BOTTOM:
    *y = screen_height - ih->currentheight;
    break;
  case IUP_TOPPARENT:
    *y = parent_y;
    break;
  case IUP_BOTTOMPARENT:
    *y = parent_height - ih->currentheight + parent_y;
    break;
  case IUP_MOUSEPOS:
    *y = cursor_y;
    break;
  case IUP_CURRENT:
    *y = current_y;
    break;
  }

	iupdrvAddScreenOffset( data, x, y, 1 );
}

void iupDialogEnterModal( struct libData *data, Ihandle *ih_popup, int popup_level)
{
  Ihandle *ih;

  assert(popup_level == dlg_popup_level );

  /* disable all visible dialogs, and mark popup level */
  for (ih = iupDlgListFirst( data ) ; ih ; ih = iupDlgListNext( data ))
  {
    if (ih != ih_popup &&
      ih->handle &&
      iupdrvDialogIsVisible( data, ih ) &&
      ih->data->popup_level == 0)
    {
      iupdrvSetActive( data, ih, 0 );
      ih->data->popup_level = dlg_popup_level;
    }
  }

  dlg_popup_level++;
}

static void iDialogSetModal( struct libData *data, Ihandle *ih_popup)
{
  iupAttribSet( data, ih_popup, "MODAL", "YES" );

  {
    IFi cb = (IFi) amy_IupGetFunction( data, "GLOBALENTERMODAL_CB" );
    int popup_level = dlg_popup_level;  /* save before it is changed */

    iupDialogEnterModal( data, ih_popup, popup_level );

    if (cb)
      cb(popup_level );
  }
}

void iupDialogLeaveModal( struct libData *data, int popup_level )
{
  Ihandle *ih;

  assert(popup_level == dlg_popup_level );

  /* must enable all visible dialogs at the marked popup level */
  for (ih = iupDlgListFirst( data ) ; ih ; ih = iupDlgListNext( data ))
  {
    if ( ih->handle)
    {
      if ( ih->data->popup_level == dlg_popup_level - 1)
      {
        iupdrvSetActive( data, ih, 1 );
        ih->data->popup_level = 0;
      }
    }
  }

  dlg_popup_level--;
}

static void iDialogUnSetModal( struct libData *data, Ihandle *ih_popup )
{
  if ( ! iupAttribGetBoolean( data, ih_popup, "MODAL" ))
    return;

  iupAttribSet( data, ih_popup, "MODAL", NULL );

  {
    IFi cb = (IFi) amy_IupGetFunction( data, "GLOBALLEAVEMODAL_CB" );
    int popup_level = dlg_popup_level;  /* save before it is changed */

    iupDialogLeaveModal( data, popup_level );

    if (cb)
      cb(popup_level );
  }
}

static int iDialogCreateMethod( struct libData *data, Ihandle *ih, void** params)
{
 ih->data = iupALLOCCTRLDATA();

  ih->data->child_id = 100; /* initial number */
  ih->data->show_state = IUP_HIDE;

  if (params)
  {
    Ihandle** iparams = (Ihandle**)params;
    if (*iparams)
      amy_IupAppend( data, ih, *iparams );
  }

  iupDlgListAdd( data, ih );

  return IUP_NOERROR;
}

static void iDialogDestroyMethod( struct libData *data, Ihandle *ih)
{
  if ( ih->data->menu)
  {
    amy_IupDestroy( data, ih->data->menu );
    ih->data->menu = NULL;
  }

  iupDlgListRemove( data, ih );
}

static int iDialogSetMenuAttrib( struct libData *data, Ihandle *ih, const char *value );

static void iDialogComputeNaturalSizeMethod( struct libData *data, Ihandle *ih, int *w, int *h, int *children_expand)
{
  int decorwidth, decorheight;
  Ihandle *child = ih->firstchild;

  /* if does not have a menu, but the attribute is defined,
     try to update the menu before retrieving the decoration. */
  char *value = iupAttribGet( data, ih, "MENU" );
  if ( ! ih->data->menu && value)
    iDialogSetMenuAttrib( data, ih, value );

  iupDialogGetDecorSize( data, ih, &decorwidth, &decorheight );
  *w = decorwidth;
  *h = decorheight;

  if (child)
  {
    /* update child natural size first */
    iupBaseComputeNaturalSize( data, child );

    *children_expand = child->expand;
    *w += child->naturalwidth;
    *h += child->naturalheight;
  }
}

static void iDialogSetChildrenCurrentSizeMethod( struct libData *data, Ihandle *ih, int shrink)
{
  int decorwidth, decorheight, client_width, client_height;

  if (shrink)
  {
    client_width = ih->currentwidth;
    client_height = ih->currentheight;
  }
  else
  {
    client_width  = iupMAX( ih->naturalwidth, ih->currentwidth );
    client_height = iupMAX( ih->naturalheight, ih->currentheight );
  }

  iupDialogGetDecorSize( data, ih, &decorwidth, &decorheight );

  client_width  -= decorwidth;
  client_height -= decorheight;
  if (client_width < 0) client_width = 0;
  if (client_height < 0) client_height = 0;

  iupBaseSetCurrentSize( data, ih->firstchild, client_width, client_height, shrink );
}

static void iDialogSetChildrenPositionMethod( struct libData *data, Ihandle *ih, int x, int y)
{
  if ( ih->firstchild)
  {
    char *offset = iupAttribGet( data, ih, "CHILDOFFSET" );

    /* Native container, position is reset */
    x = 0;
    y = 0;

    if (offset) iupStrToIntInt(offset, &x, &y, 'x' );

    if (iupAttribGetBoolean( data, ih, "CUSTOMFRAMEDRAW" ))  /* Windows Only */
    {
      int border, caption, menu;
      iupdrvDialogGetDecoration( data, ih, &border, &caption, &menu );

      x += border;
      y += border + caption + menu;
    }

    /* Child coordinates are relative to client left-top corner. */
    iupBaseSetPosition( data, ih->firstchild, x, y );
  }
}

static void iDialogAfterHide( struct libData *data, Ihandle *ih)
{
  IFni show_cb;

  /* process all pending messages, make sure the dialog is hidden */
  if ( ! iupAttribGetBoolean( data, ih, "NOFLUSH" ))
    amy_IupFlush( data );

  show_cb = (IFni) amy_IupGetCallback( data, ih, "SHOW_CB" );
  if (show_cb && show_cb( data, ih, ih->data->show_state) == IUP_CLOSE)
  {
    amy_IupExitLoop( data );
  }
}

static void iDialogAfterShow( struct libData *data, Ihandle *ih)
{
  Ihandle *old_focus;
  IFni show_cb;
  int old_show_state;

  /* process all pending messages, make sure the dialog is visible */
  if ( ! iupAttribGetBoolean( data, ih, "NOFLUSH" )) {
    amy_IupFlush( data );

    /**
     * check if any callback called by amy_IupFlush( data ) has destroyed the dialog.
     * if so, there is no point in doing anything else here.
     */
    if ( ! iupObjectCheck( data, ih ))
      return;
  }

  old_focus = amy_IupGetFocus( data );
  old_show_state = ih->data->show_state;

  show_cb = (IFni) amy_IupGetCallback( data, ih, "SHOW_CB" );
  if (show_cb && show_cb( data, ih, ih->data->show_state) == IUP_CLOSE)
  {
    amy_IupExitLoop( data );
    return;
  }

  if (old_show_state == IUP_SHOW)
  {
    if (show_cb)
    {
      if ( ! iupAttribGetBoolean( data, ih, "NOFLUSH" ))
        amy_IupFlush( data );  /* again to update focus */
    }

    /* do it only if show_cb did NOT changed the current focus */
    if (old_focus == amy_IupGetFocus( data ) && !iupAttribGetBoolean( data, ih, "SHOWNOFOCUS" ))
    {
      Ihandle *startfocus = amy_IupGetAttributeHandle( data, ih, "STARTFOCUS" );
      if (startfocus)
        amy_IupSetFocus( data, startfocus );
      else
        amy_IupNextField( data, ih );
    }
  }
}

int iupDialogGetChildId( struct libData *data, Ihandle *ih)
{
  int id;
  ih = amy_IupGetDialog( data, ih );
  if ( ! ih) return -1;
  id = ih->data->child_id;
  ih->data->child_id = id+1;
  return id;
}

char *iupDialogGetChildIdStr( struct libData *data, Ihandle *ih)
{
  /* Used only in Motif */
  Ihandle *dialog = amy_IupGetDialog( data, ih );
  return iupStrReturnStrf("iup-%s-%d", ih->iclass->name, dialog->data->child_id );
}

static void iDialogListCheckLastVisible( struct libData *data, int was_modal )
{
  if (iupDlgListVisibleCount( data ) <= 0)
  {
    /* if this is the last window visible,
    exit message loop except when LOCKLOOP==YES */
    if ( ! was_modal && !iupStrBoolean( amy_IupGetGlobal( data, "LOCKLOOP" )))
    {
      amy_IupExitLoop( data );
    }
  }
}

static int iDialogUpdateVisibility( struct libData *data, Ihandle *ih, int *x, int *y)
{
  /* save visible state before iupdrvDialogSetPlacement */
  /* because it can also show the window when changing placement. */
  int was_visible = iupdrvDialogIsVisible( data, ih );

  /* Update the position and placement */
  if ( ! iupdrvDialogSetPlacement( data, ih ))
  {
    iDialogAdjustPos( data, ih, x, y );
    iupdrvDialogSetPosition( data, ih, *x, *y );
  }

  if (was_visible) /* already visible */
  {
    /* only re-show to raise the window */
    iupdrvDialogSetVisible( data, ih, 1 );

    /* flush, then process show_cb and startfocus */
    iDialogAfterShow( data, ih );
    return 1;
  }

  return 0;
}

static void iDialogFirstShow( struct libData *data, Ihandle *ih)
{
  ih->data->first_show = 1;

  /* actually show the window */
  /* test if placement already turned the dialog visible */
  if ( ! iupdrvDialogIsVisible( data, ih ))
    iupdrvDialogSetVisible( data, ih, 1 );

  /* increment visible count */
  iupDlgListVisibleInc( data );

  /* flush, then process show_cb and startfocus */
  iDialogAfterShow( data, ih );
}

static void iDialogModalLoop( struct libData *data, Ihandle *ih)
{
  iDialogSetModal( data, ih );

  /* interrupt processing here */
  amy_IupMainLoop( data );

  /* if window is still valid ( amy_IupDestroy not called),
  hide the dialog if still visible. */
  if (iupObjectCheck( data, ih ))
  {
    iupAttribSet( data, ih, "_IUPDLG_WAS_MODAL", "1" );

    iDialogUnSetModal( data, ih );
    iupDialogHide( data, ih );

    if (iupObjectCheck( data, ih ))
      iupAttribSet( data, ih, "_IUPDLG_WAS_MODAL", NULL );
  }
  else
    iDialogListCheckLastVisible( data, 1 );
}

int iupDialogPopup( struct libData *data, Ihandle *ih, int x, int y)
{
  if (iupClassObjectHasDlgPopup( data, ih ))
  {
    int ret, automodal = amy_IupGetInt( data, ih, "AUTOMODAL" ); /* Used only for Windows MessageBox */

    if ( ! automodal)
      iDialogSetModal( data, ih );  /* make sure all other dialogs are inactive */

    ret = iupClassObjectDlgPopup( data, ih, x, y );

    if ( ! automodal)
      iDialogUnSetModal( data, ih );

    return ret;
  }

  ih->data->show_state = IUP_SHOW;

  if (iDialogUpdateVisibility( data, ih, &x, &y))
  {
    if ( ! iupAttribGetBoolean( data, ih, "MODAL" ))
      iDialogModalLoop( data, ih );

    return IUP_NOERROR;  /* if already visible, returns */
  }

  iDialogFirstShow( data, ih );

  iDialogModalLoop( data, ih );

  return IUP_NOERROR;
}

int iupDialogShowXY( struct libData *data, Ihandle *ih, int x, int y)
{
  if (iupAttribGetBoolean( data, ih, "MODAL" )) 
  {
    /* is modal, just update visibility and return */
    iDialogUpdateVisibility( data, ih, &x, &y );
    return IUP_NOERROR;
  }

  if ( ih->data->popup_level != 0)
  {
    /* was disabled by a Popup, re-enable it */
    iupdrvSetActive( data, ih, 1 );
    ih->data->popup_level = 0; /* Now it is at the current popup level */
  }

  if (iDialogUpdateVisibility( data, ih, &x, &y))
    return IUP_NOERROR;  /* if already visible, returns */

  iDialogFirstShow( data, ih );

  return IUP_NOERROR;
}

void iupDialogHide( struct libData *data, Ihandle *ih)
{
  int was_modal = iupAttribGet( data, ih, "_IUPDLG_WAS_MODAL" ) != NULL;

  /* hidden at the system and marked hidden in IUP */
  if ( ! iupdrvDialogIsVisible( data, ih ) && ih->data->show_state == IUP_HIDE) 
    return;

  /* marked hidden in IUP */
  ih->data->show_state = IUP_HIDE;

  /* if called amy_IupHide for a Popup window */
  if (iupAttribGetBoolean( data, ih, "MODAL" ))
  {
    was_modal = 1;
    iDialogUnSetModal( data, ih );
    amy_IupExitLoop( data );
  }

  ih->data->ignore_resize = 1;

  /* actually hide the window */
  iupdrvDialogSetVisible( data, ih, 0 );

  ih->data->ignore_resize = 0;

  /* decrement visible count */
  iupDlgListVisibleDec( data );
    
  /* process flush and process show_cb */
  iDialogAfterHide( data, ih );

  iDialogListCheckLastVisible( data, was_modal );
}


/****************************************************************/


int iupDialogCustomFrameRestore( struct libData *data, Ihandle *ih)
{
  if (iupAttribGet( data, ih, "_IUPDLG_OLD_MAXSIZE" ))
  {
    int width = 0, height = 0, x = 0, y = 0;
    amy_IupGetIntInt( data, ih, "_IUPDLG_OLD_MAXPOS", &x, &y );
    amy_IupGetIntInt( data, ih, "_IUPDLG_OLD_MAXSIZE", &width, &height );
    amy_IupSetStrf( data, ih, "RASTERSIZE", "%dx%d", width, height );

    iupAttribSet( data, ih, "_IUPDLG_OLD_MAXPOS", NULL );
    iupAttribSet( data, ih, "_IUPDLG_OLD_MAXSIZE", NULL );
    iupAttribSet( data, ih, "MAXIMIZED", NULL );

    amy_IupRefresh( data, ih );
    amy_IupFlush( data ); /* update size first */

    iupdrvDialogSetPosition( data, ih, x, y );
    return 1;
  }
  return 0;
}

void iupDialogCustomFrameMaximize( struct libData *data, Ihandle *ih)
{
  int width = 0, height = 0, x = 0, y = 0;
  iupdrvGetScreenSize( data, &width, &height );
  iupdrvDialogGetPosition( data, ih, NULL, &x, &y );

  iupAttribSetStrf( data, ih, "_IUPDLG_OLD_MAXPOS", "%dx%d", x, y );
  iupAttribSetStrf( data, ih, "_IUPDLG_OLD_MAXSIZE", "%dx%d", ih->currentwidth, ih->currentheight );
  amy_IupSetStrf( data, ih, "RASTERSIZE", "%dx%d", width, height );
  iupAttribSet( data, ih, "MAXIMIZED", "Yes" );

  amy_IupRefresh( data, ih );

  iupdrvDialogSetPosition( data, ih, 0, 0 );
}

typedef enum
{
  IUP_DLG_EDGE_NORTH_WEST,
  IUP_DLG_EDGE_NORTH,
  IUP_DLG_EDGE_NORTH_EAST,
  IUP_DLG_EDGE_WEST,
  IUP_DLG_EDGE_EAST,
  IUP_DLG_EDGE_SOUTH_WEST,
  IUP_DLG_EDGE_SOUTH,
  IUP_DLG_EDGE_SOUTH_EAST
} iupWindowEdge;

static int iDialogCustomFrameSimulateButton_CB( struct libData *data, Ihandle *ih, int button, int pressed, int x, int y, char *status)
{
  int is_resizing, border, edge;

  if (button != IUP_BUTTON1 || iup_isdouble(status))
    return IUP_DEFAULT;

  is_resizing = iupAttribGetInt( data, ih, "_IUPDLG_RESIZING" );
  border = 5;
  edge = -1;

  if (x < border)
  {
    if (y < 2 * border)
      edge = IUP_DLG_EDGE_NORTH_WEST;
    else if (y > ih->currentheight - 2 * border)
      edge = IUP_DLG_EDGE_SOUTH_WEST;
    else
      edge = IUP_DLG_EDGE_WEST;
  }
  else if (x > ih->currentwidth - border)
  {
    if (y < 2 * border)
      edge = IUP_DLG_EDGE_NORTH_EAST;
    else if (y > ih->currentheight - 2 * border)
      edge = IUP_DLG_EDGE_SOUTH_EAST;
    else
      edge = IUP_DLG_EDGE_EAST;
  }
  else
  {
    if (y < border)
    {
      if (x < 2 * border)
        edge = IUP_DLG_EDGE_NORTH_WEST;
      else if (x > ih->currentwidth - 2 * border)
        edge = IUP_DLG_EDGE_NORTH_EAST;
      else
        edge = IUP_DLG_EDGE_NORTH;
    }
    else if (y > ih->currentheight - border)
    {
      if (x < 2 * border)
        edge = IUP_DLG_EDGE_SOUTH_WEST;
      else if (x > ih->currentwidth - 2 * border)
        edge = IUP_DLG_EDGE_SOUTH_EAST;
      else
        edge = IUP_DLG_EDGE_SOUTH;
    }
  }

  if (edge != -1)
  {
    if ( ! is_resizing && pressed)  /* DRAG BEGIN */
    {
      int cur_start_x, cur_start_y, dlg_start_x, dlg_start_y;

      iupAttribSet( data, ih, "_IUPDLG_RESIZING", "1" );

      amy_IupGetIntInt( data, NULL, "CURSORPOS", &cur_start_x, &cur_start_y );
      dlg_start_x = amy_IupGetInt( data, ih, "X" );
      dlg_start_y = amy_IupGetInt( data, ih, "Y" );

      iupAttribSetInt( data, ih, "_IUPDLG_START_X", dlg_start_x );
      iupAttribSetInt( data, ih, "_IUPDLG_START_Y", dlg_start_y );
      iupAttribSetInt( data, ih, "_IUPDLG_START_W", ih->currentwidth );
      iupAttribSetInt( data, ih, "_IUPDLG_START_H", ih->currentheight );
      iupAttribSetInt( data, ih, "_IUPDLG_CUR_START_X", cur_start_x );
      iupAttribSetInt( data, ih, "_IUPDLG_CUR_START_Y", cur_start_y );

      iupAttribSetInt( data, ih, "_IUPDLG_RESIZE_EDGE", edge );
    }
    else if (is_resizing && !pressed)  /* DRAG END */
      iupAttribSet( data, ih, "_IUPDLG_RESIZING", NULL );
  }

  return IUP_DEFAULT;
}

static void iDialogCustomFrameSimulateSetCursor( struct libData *data, Ihandle *ih, const char *value)
{
  iupdrvBaseSetCursorAttrib( data, ih, value );
  iupAttribSet( data, ih, "_IUPDLG_RESETCURSOR", "1" );
}

static int iDialogCustomFrameSimulateMotion_CB( struct libData *data, Ihandle *ih, int x, int y, char *status)
{
  int is_resizing = iupAttribGetInt( data, ih, "_IUPDLG_RESIZING" );
  int border = 5;
  int set = 0;

  if (x < border)
  {
    if (y < 2 * border)
      iDialogCustomFrameSimulateSetCursor( data, ih, "RESIZE_NW" );
    else if (y > ih->currentheight - 2 * border)
      iDialogCustomFrameSimulateSetCursor( data, ih, "RESIZE_SW" );
    else
      iDialogCustomFrameSimulateSetCursor( data, ih, "RESIZE_W" );

    set = 1;
  }
  else if (x > ih->currentwidth - border)
  {
    if (y < 2 * border)
      iDialogCustomFrameSimulateSetCursor( data, ih, "RESIZE_NE" );
    else if (y > ih->currentheight - 2 * border)
      iDialogCustomFrameSimulateSetCursor( data, ih, "RESIZE_SE" );
    else
      iDialogCustomFrameSimulateSetCursor( data, ih, "RESIZE_E" );

    set = 1;
  }
  else
  {
    if (y < border)
    {
      if (x < 2 * border)
        iDialogCustomFrameSimulateSetCursor( data, ih, "RESIZE_NW" );
      else if (x > ih->currentwidth - 2 * border)
        iDialogCustomFrameSimulateSetCursor( data, ih, "RESIZE_NE" );
      else
        iDialogCustomFrameSimulateSetCursor( data, ih, "RESIZE_N" );

      set = 1;
    }
    else if (y > ih->currentheight - border)
    {
      if (x < 2 * border)
        iDialogCustomFrameSimulateSetCursor( data, ih, "RESIZE_SW" );
      else if (x > ih->currentwidth - 2 * border)
        iDialogCustomFrameSimulateSetCursor( data, ih, "RESIZE_SE" );
      else
        iDialogCustomFrameSimulateSetCursor( data, ih, "RESIZE_S" );

      set = 1;
    }
  }

  if ( ! is_resizing && !set && iupAttribGet( data, ih, "_IUPDLG_RESETCURSOR" ))
  {
    iupdrvBaseSetCursorAttrib( data, ih, amy_IupGetAttribute( data, ih, "CURSOR" ));
    iupAttribSet( data, ih, "_IUPDLG_RESETCURSOR", NULL );
  }

  if (is_resizing)
  {
    if (iup_isbutton1(status))  /* DRAG MOVE */
    {
      int cur_end_x, cur_end_y, cur_start_x, cur_start_y, dlg_start_x, dlg_start_y;
      int width, height, dlg_start_w, dlg_start_h, diff_x, diff_y;
      int edge = iupAttribGetInt( data, ih, "_IUPDLG_RESIZE_EDGE" );

      amy_IupGetIntInt( data, NULL, "CURSORPOS", &cur_end_x, &cur_end_y );
      dlg_start_x = iupAttribGetInt( data, ih, "_IUPDLG_START_X" );
      dlg_start_y = iupAttribGetInt( data, ih, "_IUPDLG_START_Y" );
      dlg_start_w = iupAttribGetInt( data, ih, "_IUPDLG_START_W" );
      dlg_start_h = iupAttribGetInt( data, ih, "_IUPDLG_START_H" );
      cur_start_x = iupAttribGetInt( data, ih, "_IUPDLG_CUR_START_X" );
      cur_start_y = iupAttribGetInt( data, ih, "_IUPDLG_CUR_START_Y" );

      x = dlg_start_x;
      y = dlg_start_y;
      width = dlg_start_w;
      height = dlg_start_h;

      diff_x = (cur_end_x - cur_start_x );
      diff_y = (cur_end_y - cur_start_y );

      switch (edge)
      {
      case IUP_DLG_EDGE_NORTH_WEST:
        y += diff_y;
        height -= diff_y;
        x += diff_x;
        width -= diff_x;
        break;
      case IUP_DLG_EDGE_NORTH:
        y += diff_y;
        height -= diff_y;
        break;
      case IUP_DLG_EDGE_NORTH_EAST:
        y += diff_y;
        height -= diff_y;
        width += diff_x;
        break;
      case IUP_DLG_EDGE_WEST:
        x += diff_x;
        width -= diff_x;
        break;
      case IUP_DLG_EDGE_EAST:
        width += diff_x;
        break;
      case IUP_DLG_EDGE_SOUTH_WEST:
        x += diff_x;
        width -= diff_x;
        height += diff_y;
        break;
      case IUP_DLG_EDGE_SOUTH:
        height += diff_y;
        break;
      case IUP_DLG_EDGE_SOUTH_EAST:
        width += diff_x;
        height += diff_y;
        break;
      }

      if (width != dlg_start_w || height != dlg_start_h)
      {
        amy_IupSetStrf( data, ih, "RASTERSIZE", "%dx%d", width, height );
        amy_IupRefresh( data, ih );
      }

      if (x != dlg_start_x || y != dlg_start_y)
        iupdrvDialogSetPosition( data, ih, x, y );
    }
    else
      iupAttribSet( data, ih, "_IUPDLG_RESIZING", NULL );
  }

  (void)status;
  return IUP_DEFAULT;
}

static int iDialogCustomFrameSimulateCaptionButton_CB( struct libData *data, Ihandle *caption, int button, int pressed, int x, int y, char *status)
{
  Ihandle *ih = amy_IupGetDialog( data, caption );
  int is_moving = iupAttribGetInt( data, ih, "_IUPDLG_MOVING" );

  if (button != IUP_BUTTON1)
    return IUP_DEFAULT;

  if ( iup_isdouble(status))
  {
    if ( amy_IupGetInt( data, ih, "MAXIMIZED" ))
      amy_IupSetAttribute( data, ih, "PLACEMENT", NULL );
    else
      amy_IupSetAttribute( data, ih, "PLACEMENT", "MAXIMIZED" );

    amy_IupShow( data, ih );

    return IUP_DEFAULT;
  }

  if ( ! is_moving && pressed)  /* DRAG BEGIN */
  {
    int cur_start_x, cur_start_y, dlg_start_x, dlg_start_y;

    iupAttribSet( data, ih, "_IUPDLG_MOVING", "1" );

    amy_IupGetIntInt( data, NULL, "CURSORPOS", &cur_start_x, &cur_start_y );
    dlg_start_x = amy_IupGetInt( data, ih, "X" );
    dlg_start_y = amy_IupGetInt( data, ih, "Y" );

    iupAttribSetInt( data, ih, "_IUPDLG_START_X", dlg_start_x );
    iupAttribSetInt( data, ih, "_IUPDLG_START_Y", dlg_start_y );
    iupAttribSetInt( data, ih, "_IUPDLG_CUR_START_X", cur_start_x );
    iupAttribSetInt( data, ih, "_IUPDLG_CUR_START_Y", cur_start_y );
  }
  else if (is_moving)  /* DRAG END */
  {
    iupAttribSet( data, ih, "_IUPDLG_MOVING", NULL );
  }

  (void)x;
  (void)y;
  return IUP_DEFAULT;
}

static int iDialogCustomFrameSimulateCaptionMotion_CB( struct libData *data, Ihandle *caption, int x, int y, char *status)
{
  Ihandle *ih = amy_IupGetDialog( data, caption );
  int is_moving = iupAttribGetInt( data, ih, "_IUPDLG_MOVING" );

  if (iupAttribGet( data, ih, "_IUPDLG_RESETCURSOR" ) && !iupAttribGetInt( data, ih, "_IUPDLG_RESIZING" ))
  {
    iupdrvBaseSetCursorAttrib( data, ih, amy_IupGetAttribute( data, ih, "CURSOR" ));
    iupAttribSet( data, ih, "_IUPDLG_RESETCURSOR", NULL );
  }

  if (is_moving)
  {
    if ( iup_isbutton1(status))  /* DRAG MOVE */
    {
      int cur_end_x, cur_end_y, cur_start_x, cur_start_y, dlg_start_x, dlg_start_y;

      amy_IupGetIntInt( data, NULL, "CURSORPOS", &cur_end_x, &cur_end_y );
      dlg_start_x = iupAttribGetInt( data, ih, "_IUPDLG_START_X" );
      dlg_start_y = iupAttribGetInt( data, ih, "_IUPDLG_START_Y" );
      cur_start_x = iupAttribGetInt( data, ih, "_IUPDLG_CUR_START_X" );
      cur_start_y = iupAttribGetInt( data, ih, "_IUPDLG_CUR_START_Y" );

      x = dlg_start_x + (cur_end_x - cur_start_x );
      y = dlg_start_y + (cur_end_y - cur_start_y );

      iupdrvDialogSetPosition( data, ih, x, y );
    }
    else
      iupAttribSet( data, ih, "_IUPDLG_MOVING", NULL );
  }

  return IUP_DEFAULT;
}

void iupDialogCustomFrameSimulateCheckCallbacks( struct libData *data, Ihandle *ih)
{
  Ihandle *ih_caption = amy_IupGetDialogChild( data, ih, "CUSTOMFRAMECAPTION" );
  if (ih_caption)
  {
    if ( ! amy_IupGetCallback( data, ih_caption, "BUTTON_CB" ))
      amy_IupSetCallback( data, ih_caption, "BUTTON_CB", (Icallback)iDialogCustomFrameSimulateCaptionButton_CB );

    if ( ! amy_IupGetCallback( data, ih_caption, "MOTION_CB" ))
      amy_IupSetCallback( data, ih_caption, "MOTION_CB", (Icallback)iDialogCustomFrameSimulateCaptionMotion_CB );
  }
}

static int iDialogSetCustomFrameSimulateAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if (iupStrBoolean(value))
  {
    iupDialogCustomFrameSimulateCheckCallbacks( data, ih );

    amy_IupSetCallback( data, ih, "BUTTON_CB", (Icallback)iDialogCustomFrameSimulateButton_CB );
    amy_IupSetCallback( data, ih, "MOTION_CB", (Icallback)iDialogCustomFrameSimulateMotion_CB );

    iupAttribSet( data, ih, "RESIZE", "NO" );
    iupAttribSet( data, ih, "MENUBOX", "NO" );
    iupAttribSet( data, ih, "MAXBOX", "NO" );
    iupAttribSet( data, ih, "MINBOX", "NO" );
    iupAttribSet( data, ih, "BORDER", "NO" );

    iupAttribSet( data, ih, "TITLE", NULL );

    iupAttribSet( data, ih, "MENU", NULL ); /* can NOT have a menu */

    iupAttribSet( data, ih, "TASKBARBUTTON", "SHOW" );
  }

  return 1;
}

static int iDialogSizeGetScale(const char *sz)
{
  if ( ! sz || sz[0] == 0) return 0;
  if (iupStrEqualNoCase(sz, "FULL" ))     return 1;
  if (iupStrEqualNoCase(sz, "HALF" ))     return 2;
  if (iupStrEqualNoCase(sz, "THIRD" ))    return 3;
  if (iupStrEqualNoCase(sz, "QUARTER" ))  return 4;
  if (iupStrEqualNoCase(sz, "EIGHTH" ))   return 8;
  return 0;
}

static int iDialogSetSizeAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if ( ! value)
  {
    ih->userwidth = 0;
    ih->userheight = 0;
  }
  else
  {
    char *sh, sw[40];
    strcpy(sw, value );
    sh = strchr(sw, 'x' );
    if ( ! sh)
      sh = "";
    else
    {
      *sh = '\0';  /* to mark the end of sw */
      ++sh;
    }

    {
      int charwidth, charheight;
      int screen_width, screen_height;
      int wscale = iDialogSizeGetScale( sw );
      int hscale = iDialogSizeGetScale( sh );

      int width = 0, height = 0; 
      iupStrToIntInt(value, &width, &height, 'x' );
      if (width < 0) width = 0;
      if (height < 0) height = 0;

      iupdrvFontGetCharSize( data, ih, &charwidth, &charheight );

      /* desktop size, excluding task bars and menu bars */
      iupdrvGetScreenSize( data, &screen_width, &screen_height );

      if (wscale)
        width = screen_width/wscale;
      else
        width = iupWIDTH2RASTER(width, charwidth );

      if (hscale)
        height = screen_height/hscale;
      else
        height = iupHEIGHT2RASTER(height, charheight );

      ih->userwidth = width;
      ih->userheight = height;
    }
  }

  /* must reset the current size,  */
  /* so the user or the natural size will be used to resize the dialog */
  ih->currentwidth = 0;
  ih->currentheight = 0;

  return 0;
}

static char *iDialogGetSizeAttrib( struct libData *data, Ihandle *ih)
{
  int charwidth, charheight, width, height;

  if ( ih->handle)
  {
    /* ih->currentwidth and/or ih->currentheight could have been reset in SetSize */
    iupdrvDialogGetSize( data, ih, NULL, &width, &height );
  }
  else
  {
    width = ih->userwidth;
    height = ih->userheight;
  }

  iupdrvFontGetCharSize( data, ih, &charwidth, &charheight );
  if (charwidth == 0 || charheight == 0)
    return NULL;  /* if font failed get from the hash table */

  return iupStrReturnIntInt(iupRASTER2WIDTH(width, charwidth), iupRASTER2HEIGHT(height, charheight), 'x' );
}

static int iDialogSetRasterSizeAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if ( ! value)
  {
    ih->userwidth = 0;
    ih->userheight = 0;
  }
  else
  {
    int w = 0, h = 0;
    iupStrToIntInt(value, &w, &h, 'x' );
    if (w < 0) w = 0;
    if (h < 0) h = 0;
    ih->userwidth = w;
    ih->userheight = h;
  }

  /* must reset the current size also,  */
  /* so the user or the natural size will be used to resize the dialog */
  ih->currentwidth = 0;
  ih->currentheight = 0;

  return 0;
}

static char *iDialogGetRasterSizeAttrib( struct libData *data, Ihandle *ih)
{
  int width, height;

  if ( ih->handle)
  {
    /* ih->currentwidth and/or ih->currentheight could have been reset in SetRasterSize */
    iupdrvDialogGetSize( data, ih, NULL, &width, &height );
  }
  else
  {
    width = ih->userwidth;
    height = ih->userheight;
  }

  if ( ! width && !height)
    return NULL;

  return iupStrReturnIntInt( width, height, 'x' );
}

static int iDialogSetNActiveAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  iupdrvSetActive( data, ih, iupStrBoolean(value));
  return 0;
}

static int iDialogSetVisibleAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if (iupStrBoolean(value))
    amy_IupShow( data, ih );
  else
    amy_IupHide( data, ih );
  return 0;
}

void iupDialogUpdatePosition( struct libData *data, Ihandle *ih)
{
  /* This function is used only by pre-defined popup native dialogs */

  int x = iupAttribGetInt( data, ih, "_IUPDLG_X" );
  int y = iupAttribGetInt( data, ih, "_IUPDLG_Y" );

  iupdrvDialogGetSize( data, ih, NULL, &( ih->currentwidth), &( ih->currentheight));

  /* handle always as visible for the first time */
  ih->data->first_show = 0;

  iDialogAdjustPos( data, ih, &x, &y );
  iupdrvDialogSetPosition( data, ih, x, y );
}

void iupDialogGetDecorSize( struct libData *data, Ihandle *ih, int *decorwidth, int *decorheight )
{
  int border, caption, menu;
  iupdrvDialogGetDecoration( data, ih, &border, &caption, &menu );

  if (iupAttribGetBoolean( data, ih, "CUSTOMFRAME" ))
  {
    *decorwidth = 0;
    *decorheight = 0;
  }
  else
  {
    *decorwidth = 2 * border;
    *decorheight = 2 * border + caption + menu;
  }
}

static int iDialogSetHideTaskbarAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  iupdrvDialogSetVisible( data, ih, ! iupStrBoolean( value ));
  return 0;
}

static int iDialogSetSimulateModalAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  Ihandle *ih_dlg;

  int sim_modal = iupStrBoolean( value );

  /* disable all visible dialogs different than this one */
  for (ih_dlg = iupDlgListFirst( data ); ih_dlg; ih_dlg = iupDlgListNext( data ))
  {
    if (ih_dlg != ih &&
        ih_dlg->handle &&
        iupdrvDialogIsVisible( data, ih_dlg ))
    {
      if (sim_modal)
        iupdrvSetActive( data, ih_dlg, 0 );
      else
        iupdrvSetActive( data, ih_dlg, 1 );
    }
  }

  return 0;
}

static int iDialogSetParentDialogAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  Ihandle *parent = amy_IupGetHandle( data, value );
  InativeHandle *native_parent;
  if (parent && parent->handle)
    native_parent = parent->handle;
  else
    native_parent = (InativeHandle*) iupAttribGet( data, ih, "NATIVEPARENT" );

  if (native_parent != iupDialogGetNativeParent( data, ih ))
    iupdrvDialogSetParent( data, ih, native_parent );

  return 1;
}

static int iDialogSetDialogFrameAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if (iupStrBoolean(value))
  {
    iupAttribSet( data, ih, "RESIZE", "NO" );
    iupAttribSet( data, ih, "MAXBOX", "NO" );
    iupAttribSet( data, ih, "MINBOX", "NO" );
  }
  else
  {
    iupAttribSet( data, ih, "RESIZE", NULL );
    iupAttribSet( data, ih, "MAXBOX", NULL );
    iupAttribSet( data, ih, "MINBOX", NULL );
  }
  return 1;
}

static char *iDialogGetXAttrib( struct libData *data, Ihandle *ih)
{
  int x = 0;
  iupdrvDialogGetPosition( data, ih, NULL, &x, NULL );
  return amy_iupStrReturnInt( data, x );
}

static char *iDialogGetYAttrib( struct libData *data, Ihandle *ih)
{
  int y = 0;
  iupdrvDialogGetPosition( data, ih, NULL, NULL, &y );
  return amy_iupStrReturnInt( data, y );
}

static char *iDialogGetScreenPositionAttrib( struct libData *data, Ihandle *ih)
{
  int x = 0, y = 0;
  iupdrvDialogGetPosition( data, ih, NULL, &x, &y );
  return iupStrReturnIntInt( x, y, ',' );
}

static int iDialogSetMenuAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if ( ! ih->handle)
  {
    Ihandle *menu = amy_IupGetHandle( data , value );
    ih->data->menu = menu;
    return 1;
  }

  if ( ! value)
  {
    if ( ih->data->menu && ih->data->menu->handle)
    {
      ih->data->ignore_resize = 1;
      amy_IupUnmap( data, ih->data->menu );  /* this will remove the menu from the dialog */
      ih->data->ignore_resize = 0;

      ih->data->menu = NULL;
    }
  }
  else
  {
    Ihandle *menu = amy_IupGetHandle( data, value );
    if ( ! menu || menu->iclass->nativetype != IUP_TYPEMENU || menu->parent)
      return 0;

    /* already the current menu and it is mapped */
    if ( ih->data->menu && ih->data->menu==menu && menu->handle)
      return 1;

    /* the current menu is mapped, so unmap it */
    if ( ih->data->menu && ih->data->menu->handle && ih->data->menu!=menu)
    {
      ih->data->ignore_resize = 1;
      amy_IupUnmap( data, ih->data->menu );   /* this will remove the menu from the dialog */
      ih->data->ignore_resize = 0;
    }

    ih->data->menu = menu;

    menu->parent = ih;    /* use this to create a menu bar instead of a popup menu */

    ih->data->ignore_resize = 1;
    amy_IupMap( data, menu );     /* this will automatically add the menu to the dialog */
    ih->data->ignore_resize = 0;
  }
  return 1;
}


/****************************************************************/


IUP_API Ihandle *amy_IupDialog( struct libData *data, Ihandle *child )
{
  void *children[2];
  children[0] = child;
  children[1] = NULL;
  return amy_IupCreatev( data, "dialog", children );
}

Iclass *iupDialogNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, NULL );

  ic->name = "dialog";
  ic->format = "h"; /* one Ihandle **/
  ic->nativetype = IUP_TYPEDIALOG;
  ic->childtype = IUP_CHILDMANY+1;  /* 1 child */
  ic->is_interactive = 1;

  /* Class functions */
  ic->New = iupDialogNewClass;
  ic->Create = iDialogCreateMethod;
  ic->Destroy = iDialogDestroyMethod;
  ic->ComputeNaturalSize = iDialogComputeNaturalSizeMethod;
  ic->SetChildrenCurrentSize = iDialogSetChildrenCurrentSizeMethod;
  ic->SetChildrenPosition = iDialogSetChildrenPositionMethod;

  /* Callbacks */
  iupClassRegisterCallback( data, ic, "SHOW_CB", "i" );
  iupClassRegisterCallback( data, ic, "RESIZE_CB", "ii" );
  iupClassRegisterCallback( data, ic, "CLOSE_CB", "" );
  iupClassRegisterCallback( data, ic, "FOCUS_CB", "i" );

  /* Common Callbacks */
  iupBaseRegisterCommonCallbacks( data, ic );

  /* Attribute functions */

  /* Common */
  iupBaseRegisterCommonAttrib( data, ic );

  /* Overwrite Common */
  iupClassRegisterAttribute( data, ic, "SIZE", iDialogGetSizeAttrib, iDialogSetSizeAttrib, NULL, NULL, IUPAF_NO_SAVE|IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "RASTERSIZE", iDialogGetRasterSizeAttrib, iDialogSetRasterSizeAttrib, NULL, NULL, IUPAF_NO_SAVE|IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "POSITION", NULL, NULL, NULL, NULL, IUPAF_NOT_SUPPORTED ); /* forbidden in dialog */

  /* Base Container */
  iupClassRegisterAttribute( data, ic, "EXPAND", iupBaseContainerGetExpandAttrib, NULL, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );

  /* Native Container */
  iupClassRegisterAttribute( data, ic, "CHILDOFFSET", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );

  /* Visual */
  iupBaseRegisterVisualAttrib( data, ic );

  /* Dialog only */
  iupClassRegisterAttribute( data, ic, "NACTIVE", iupBaseGetActiveAttrib, iDialogSetNActiveAttrib, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NO_INHERIT );

  /* Drag&Drop */
  iupdrvRegisterDragDropAttrib( data, ic );

  /* Overwrite Visual */
  /* the only case where VISIBLE default is NO, and must not be propagated to the dialog children */
  iupClassRegisterAttribute( data, ic, "VISIBLE", iupBaseGetVisibleAttrib, iDialogSetVisibleAttrib, IUPAF_SAMEASSYSTEM, "NO", IUPAF_NO_SAVE|IUPAF_NO_INHERIT );

  /* X and Y here are at the top left corner of the window, not the client area. */
  iupClassRegisterAttribute( data, ic, "X", iDialogGetXAttrib, NULL, NULL, NULL, IUPAF_NO_DEFAULTVALUE|IUPAF_READONLY|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "Y", iDialogGetYAttrib, NULL, NULL, NULL, IUPAF_NO_DEFAULTVALUE|IUPAF_READONLY|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "SCREENPOSITION", iDialogGetScreenPositionAttrib, NULL, NULL, NULL, IUPAF_NO_DEFAULTVALUE|IUPAF_READONLY|IUPAF_NO_INHERIT );

  /* amy_IupDialog only */
  iupClassRegisterAttribute( data, ic, "MENU", NULL, iDialogSetMenuAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CURSOR", NULL, iupdrvBaseSetCursorAttrib, IUPAF_SAMEASSYSTEM, "ARROW", IUPAF_IHANDLENAME|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "HIDETASKBAR", NULL, iDialogSetHideTaskbarAttrib, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MAXBOX", NULL, NULL, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MENUBOX", NULL, NULL, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MINBOX", NULL, NULL, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "RESIZE", NULL, NULL, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "BORDER", NULL, NULL, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "BORDERSIZE", iDialogGetBorderSizeAttrib, NULL, NULL, NULL, IUPAF_READONLY | IUPAF_NO_INHERIT );
  
  iupClassRegisterAttribute( data, ic, "DEFAULTENTER", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DEFAULTESC",   NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DIALOGFRAME",  NULL, iDialogSetDialogFrameAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "PARENTDIALOG", NULL, iDialogSetParentDialogAttrib, NULL, NULL, IUPAF_NO_DEFAULTVALUE | IUPAF_IHANDLENAME | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "SHRINK",       NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "STARTFOCUS",   NULL, NULL, NULL, NULL, IUPAF_NO_DEFAULTVALUE | IUPAF_IHANDLENAME | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MODAL",        NULL, NULL, NULL, NULL, IUPAF_READONLY|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "PLACEMENT",    NULL, NULL, "NORMAL", NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "NOFLUSH", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "SHOWNOFOCUS", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "SIMULATEMODAL", NULL, iDialogSetSimulateModalAttrib, NULL, NULL, IUPAF_WRITEONLY | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CUSTOMFRAMESIMULATE", NULL, iDialogSetCustomFrameSimulateAttrib, IUPAF_SAMEASSYSTEM, NULL, IUPAF_NOT_MAPPED );

  iupClassRegisterAttribute( data, ic, "NATIVEPARENT", NULL, NULL, NULL, NULL, IUPAF_NO_STRING );

  iupdrvDialogInitClass( data, ic );

  return ic;
}
