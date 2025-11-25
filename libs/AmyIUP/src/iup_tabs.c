
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"
#include "inc/iup_tabs.h"

// --

#if 0

/** \file
* \brief iuptabs control
*
* See Copyright Notice in "iup.h"
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "iup.h"
#include "iupcbs.h"

#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_drv.h"
#include "iup_drvfont.h"
#include "iup_stdcontrols.h"
#include "iup_layout.h"
#include "iup_image.h"
#include "iup_tabs.h"
#include "iup_varg.h"

#endif

char *iupTabsGetTabPaddingAttrib( struct libData *data, Ihandle *ih)
{
  return iupStrReturnIntInt(ih->data->horiz_padding, ih->data->vert_padding, 'x' );
}

static int iTabsGetMaxWidth( struct libData *data, Ihandle *ih)
{
  int max_width = 0, width, pos;
  char *tabtitle, *tabimage;
  Ihandle *child;

  for (pos = 0, child = ih->firstchild; child; child = child->brother, pos++)
  {
    tabtitle = iupAttribGetId( data, ih, "TABTITLE", pos );
    if ( ! tabtitle) tabtitle = iupAttribGet( data, child, "TABTITLE" );
    tabimage = iupAttribGetId( data, ih, "TABIMAGE", pos );
    if ( ! tabimage) tabimage = iupAttribGet( data, child, "TABIMAGE" );
    if ( ! tabtitle && !tabimage)
      tabtitle = "     ";

    width = 0;
    if (tabtitle)
      width += iupdrvFontGetStringWidth( data, ih, tabtitle );

    if (tabimage)
    {
      void* img = iupImageGetImage( data, tabimage, ih, 0, NULL );
      if (img)
      {
        int w;
        iupdrvImageGetInfo( data, img, &w, NULL, NULL );
        width += w;
      }
    }

    if (width > max_width) max_width = width;
  }

  return max_width;
}

static int iTabsGetMaxHeight( struct libData *data, Ihandle *ih)
{
  int max_height = 0, h, pos;
  char *tabimage;
  Ihandle *child;

  for (pos = 0, child = ih->firstchild; child; child = child->brother, pos++)
  {
    tabimage = iupAttribGetId( data, ih, "TABIMAGE", pos );
    if ( ! tabimage) tabimage = iupAttribGet( data, child, "TABIMAGE" );

    if (tabimage)
    {
      void* img = iupImageGetImage( data, tabimage, ih, 0, NULL );
      if (img)
      {
        iupdrvImageGetInfo( data, img, NULL, &h, NULL );
        if (h > max_height) max_height = h;
      }
    }
  }

  iupdrvFontGetCharSize( data, ih, NULL, &h );
  if (h > max_height) max_height = h;

  return max_height;
}

static void iTabsGetDecorMargin( struct libData *data, int *m, int *s)
{
  int e = iupdrvTabsExtraMargin( data );
  *m = 4 + e;
  *s = 2 + 2*e;
}

static void iTabsGetDecorSize( struct libData *data, Ihandle *ih, int *width, int *height)
{
  int m, s;
  iTabsGetDecorMargin( data, &m, &s );

  if (ih->data->type == ITABS_LEFT || ih->data->type == ITABS_RIGHT)
  {
    if (ih->data->orientation == ITABS_HORIZONTAL)
    {
      int max_width = iTabsGetMaxWidth( data, ih );
      *width  = m + (3 + max_width + 3) + s + m;
      *height = m + m;

      if (iupdrvTabsExtraDecor( data, ih ))
      {
        int h;
        iupdrvFontGetCharSize( data, ih, NULL, &h );
        *height += h + m;
      }
    }
    else
    {
      int max_height = iTabsGetMaxHeight( data, ih );
      *width  = m + (3 + max_height + 3) + s + m;
      *height = m + m;

      if (ih->handle && ih->data->is_multiline)
      {
        int num_lin = iupdrvTabsGetLineCountAttrib( data, ih );
        *width += (num_lin-1)*(3 + max_height + 3 + 1 );
      }
    }
  }
  else /* "BOTTOM" or "TOP" */
  {
    if (ih->data->orientation == ITABS_HORIZONTAL)
    {
      int max_height = iTabsGetMaxHeight( data, ih );
      *width  = m + m;
      *height = m + (3 + max_height + 3) + s + m;

      if (ih->handle && ih->data->is_multiline)
      {
        int num_lin = iupdrvTabsGetLineCountAttrib( data, ih );
        *height += (num_lin-1)*(3 + max_height + 3 + 1 );
      }

      if (iupdrvTabsExtraDecor( data, ih ))
      {
        int h;
        iupdrvFontGetCharSize( data, ih, NULL, &h );
        *width += h + m;
      }
    }
    else
    {
      int max_width = iTabsGetMaxWidth( data, ih );
      *width  = m + m;
      *height = m + (3 + max_width + 3) + s + m;
    }
  }

  *width  += ih->data->horiz_padding;
  *height += ih->data->vert_padding;
}

static void iTabsGetDecorOffset( struct libData *data, Ihandle *ih, int *dx, int *dy)
{
  int m, s;
  iTabsGetDecorMargin( data, &m, &s );

  if (ih->data->type == ITABS_LEFT || ih->data->type == ITABS_RIGHT)
  {
    if (ih->data->type == ITABS_LEFT)
    {
      if (ih->data->orientation == ITABS_HORIZONTAL)
      {
        int max_width = iTabsGetMaxWidth( data, ih );
        *dx = m + (3 + max_width + 3) + s;
      }
      else
      {
        int max_height = iTabsGetMaxHeight( data, ih );
        *dx = m + (3 + max_height + 3) + s;

        if (ih->handle && ih->data->is_multiline)
        {
          int num_lin = iupdrvTabsGetLineCountAttrib( data, ih );
          *dx += (num_lin-1)*(3 + max_height + 3 + 1 );
        }
      }
    }
    else
      *dx = m;

    *dy = m;
  }
  else /* "BOTTOM" or "TOP" */
  {
    if (ih->data->type == ITABS_TOP)
    {
      if (ih->data->orientation == ITABS_HORIZONTAL)
      {
        int max_height = iTabsGetMaxHeight( data, ih );
        *dy = m + (3 + max_height + 3) + s;

        if (ih->handle && ih->data->is_multiline)
        {
          int num_lin = iupdrvTabsGetLineCountAttrib( data, ih );
          *dy += (num_lin-1)*(3 + max_height + 3 + 1 );
        }
      }
      else
      {
        int max_width = iTabsGetMaxWidth( data, ih );
        *dy = m + (3 + max_width + 3) + s;
      }
    }
    else
      *dy = m;

    *dx = m;
  }

  *dx += ih->data->horiz_padding;
  *dy += ih->data->vert_padding;
}

void iupTabsCheckCurrentTab( struct libData *data, Ihandle *ih, int pos, int removed)
{
  int cur_pos = iupdrvTabsGetCurrentTab( data, ih );
  if (cur_pos == pos)
  {
    int p;

    /* if given tab is the current tab, 
       then the current tab must be changed to a visible tab */
    Ihandle *child;

    /* this function is called after the child has being removed from the hierarchy,
       but before the system tab being removed. */

    p = 0;
    if (removed && p == pos)
      p++;

    for (child = ih->firstchild; child; child = child->brother)
    {
      if (p != pos && iupdrvTabsIsTabVisible( data, child, p ))
      {
        iupdrvTabsSetCurrentTab( data, ih, p );

        if ( ! iupAttribGetBoolean( data, ih, "CHILDSIZEALL" ))
          amy_IupRefresh( data, ih );

        return;
      }

      p++;
      if (removed && p == pos)
        p++;  /* increment twice to compensate for child already removed */
    }
  }
}

static void iTabsSetTab( struct libData *data, Ihandle *ih, Ihandle *child, int pos)
{
  if (ih->handle)
  {
    int cur_pos = iupdrvTabsGetCurrentTab( data, ih );
    if (cur_pos != pos && iupdrvTabsIsTabVisible( data, child, pos ))
    {
      iupdrvTabsSetCurrentTab( data, ih, pos );

      if ( ! iupAttribGetBoolean( data, ih, "CHILDSIZEALL" ))
        amy_IupRefresh( data, ih );
    }
  }
  else
    iupAttribSet( data, ih, "_IUPTABS_VALUE_HANDLE", (char*)child );
}


/* ------------------------------------------------------------------------- */
/* TABS - Sets and Gets - Attribs                                           */
/* ------------------------------------------------------------------------- */

char *iupTabsGetTabTypeAttrib( struct libData *data, Ihandle *ih)
{
  switch(ih->data->type)
  {
  case ITABS_BOTTOM:
    return "BOTTOM";
  case ITABS_LEFT:
    return "LEFT";
  case ITABS_RIGHT:
    return "RIGHT";
  default:
    return "TOP";
  }
}

char *iupTabsGetTabOrientationAttrib( struct libData *data, Ihandle *ih)
{
  if (ih->data->orientation == ITABS_HORIZONTAL)
    return "HORIZONTAL";
  else
    return "VERTICAL";
}

static char *iTabsGetCountAttrib( struct libData *data, Ihandle *ih)
{
  return amy_iupStrReturnInt( data, amy_IupGetChildCount( data, ih ));
}

static int iTabsSetValueHandleAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  int pos;
  Ihandle *child;

  child = (Ihandle *)value;

  if ( ! iupObjectCheck( data, child))
    return 0;

  pos = amy_IupGetChildPos( data, ih, child );
  if (pos != -1) /* found child */
    iTabsSetTab( data, ih, child, pos );

  return 0;
}

static char *iTabsGetValueHandleAttrib( struct libData *data, Ihandle *ih)
{
  if (ih->handle)
  {
    int pos = iupdrvTabsGetCurrentTab( data, ih );
    return (char*) amy_IupGetChild( data, ih, pos );
  }
  else
    return iupAttribGet( data, ih, "_IUPTABS_VALUE_HANDLE" );
}

static int iTabsSetValuePosAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  Ihandle *child;
  int pos;

  if ( ! iupStrToInt(value, &pos))
    return 0;

  child = amy_IupGetChild( data, ih, pos );
  if (child) /* found child */
    iTabsSetTab( data, ih, child, pos );
 
  return 0;
}

static char *iTabsGetValuePosAttrib( struct libData *data, Ihandle *ih)
{
  if (ih->handle)
  {
    int pos = iupdrvTabsGetCurrentTab( data, ih );
    return amy_iupStrReturnInt( data, pos );
  }
  else
  {
    Ihandle *child = (Ihandle *) iupAttribGet( data, ih, "_IUPTABS_VALUE_HANDLE" );
    int pos = amy_IupGetChildPos( data, ih, child );
    if (pos != -1) /* found child */
      return amy_iupStrReturnInt( data, pos );
  }

  return NULL;
}

static int iTabsSetValueAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  Ihandle *child;

  if ( ! value)
    return 0;

  child = amy_IupGetHandle( data, value );
  if ( ! child)
    return 0;

  iTabsSetValueHandleAttrib( data, ih, (char*)child );

  return 0;
}

static char *iTabsGetValueAttrib( struct libData *data, Ihandle *ih)
{
  Ihandle *child = (Ihandle *)iTabsGetValueHandleAttrib( data, ih );
  return amy_IupGetName( data, child );  /* Name is guarantied at AddedMethod */
}

static char *iTabsGetClientSizeAttrib( struct libData *data, Ihandle *ih)
{
  int width, height, decorwidth, decorheight;
  width = ih->currentwidth;
  height = ih->currentheight;
  iTabsGetDecorSize( data, ih, &decorwidth, &decorheight );
  width -= decorwidth;
  height -= decorheight;
  if (width < 0) width = 0;
  if (height < 0) height = 0;
  return iupStrReturnIntInt(width, height,'x' );
}

static char *iTabsGetClientOffsetAttrib( struct libData *data, Ihandle *ih)
{
  int dx, dy;
  iTabsGetDecorOffset( data, ih, &dx, &dy );
  return iupStrReturnIntInt(dx, dy, 'x' );
}

char *iupTabsGetTabVisibleAttrib( struct libData *data, Ihandle *ih, int pos )
{
  Ihandle *child = amy_IupGetChild( data, ih, pos );
  if (child)
    return iupStrReturnBoolean( iupdrvTabsIsTabVisible( data, child, pos ));
  else
    return NULL;
}

char *iupTabsGetTitleAttrib( struct libData *data, Ihandle *ih, int pos)
{
  Ihandle *child = amy_IupGetChild( data, ih, pos );
  if (child)
    return iupAttribGet( data, child, "TABTITLE" );
  else
    return NULL;
}

static char *iTabsGetShowCloseAttrib( struct libData *data, Ihandle *ih)
{
  return iupStrReturnBoolean( ih->data->show_close ); 
}

static int iTabsSetShowCloseAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if (iupStrBoolean(value))
    ih->data->show_close = 1;
  else
    ih->data->show_close = 0;

  return 0;
}

/* ------------------------------------------------------------------------- */
/* TABS - Methods                                                            */
/* ------------------------------------------------------------------------- */

static void iTabsComputeNaturalSizeMethod( struct libData *data, Ihandle *ih, int *w, int *h, int *children_expand)
{
  Ihandle *child;
  int children_naturalwidth, children_naturalheight;
  int decorwidth, decorheight;
  int childSizeAll = iupAttribGetBoolean( data, ih, "CHILDSIZEALL" );
  Ihandle *current_child = childSizeAll? NULL: amy_IupGetChild( data, ih, iupdrvTabsGetCurrentTab( data, ih ));

  /* calculate total children natural size (even for hidden children) */
  children_naturalwidth = 0;
  children_naturalheight = 0;

  for (child = ih->firstchild; child; child = child->brother)
  {
    /* update child natural size first */
    if ( ! (child->flags & IUP_FLOATING_IGNORE))
      iupBaseComputeNaturalSize( data, child );

    if ( ! childSizeAll && child != current_child)
      continue;

    if ( ! (child->flags & IUP_FLOATING))
    {
      *children_expand |= child->expand;
      children_naturalwidth = iupMAX(children_naturalwidth, child->naturalwidth );
      children_naturalheight = iupMAX(children_naturalheight, child->naturalheight );
    }
  }

  iTabsGetDecorSize( data, ih, &decorwidth, &decorheight );

  *w = children_naturalwidth + decorwidth;
  *h = children_naturalheight + decorheight;
}

static void iTabsSetChildrenCurrentSizeMethod( struct libData *data, Ihandle *ih, int shrink)
{
  Ihandle *child;
  int width, height, decorwidth, decorheight;

  iTabsGetDecorSize( data, ih, &decorwidth, &decorheight );

  width = ih->currentwidth-decorwidth;
  height = ih->currentheight-decorheight;
  if (width < 0) width = 0;
  if (height < 0) height = 0;

  for (child = ih->firstchild; child; child = child->brother)
  {
    if ( ! (child->flags & IUP_FLOATING))
      iupBaseSetCurrentSize( data, child, width, height, shrink );
  }
}

static void iTabsSetChildrenPositionMethod( struct libData *data, Ihandle *ih, int x, int y)
{
  /* In all systems, each tab is a native window covering the client area.
     Child coordinates are relative to client left-top corner of the tab page. */
  Ihandle *child;
  char *offset = iupAttribGet( data, ih, "CHILDOFFSET" );

  /* Native container, position is reset */
  x = 0;
  y = 0;

  if (offset) iupStrToIntInt(offset, &x, &y, 'x' );

  for (child = ih->firstchild; child; child = child->brother)
  {
    if ( ! (child->flags & IUP_FLOATING))
      iupBaseSetPosition( data, child, x, y );
  }
}

static void* iTabsGetInnerNativeContainerHandleMethod( struct libData *data, Ihandle *ih, Ihandle *child)
{
  while (child && child->parent != ih)
    child = child->parent;
  if (child)
    return iupAttribGet( data, child, "_IUPTAB_CONTAINER" );
  else
    return NULL;
}

static int iTabsCreateMethod( struct libData *data, Ihandle *ih, void **params)
{
  ih->data = iupALLOCCTRLDATA();

  /* add children */
  if(params)
  {
    Ihandle** iparams = (Ihandle**)params;
    while (*iparams) 
    {
      amy_IupAppend( data, ih, *iparams );
      iparams++;
    }
  }
  return IUP_NOERROR;
}

Iclass *iupTabsNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, NULL );

  ic->name = "tabs";
  ic->format = "g"; /* array of Ihandle */
  ic->nativetype = IUP_TYPECONTROL;
  ic->childtype = IUP_CHILDMANY;  /* can have children */
  ic->is_interactive = 1;
  ic->has_attrib_id = 1;

  /* Class functions */
  ic->New = iupTabsNewClass;
  ic->Create  = iTabsCreateMethod;
  ic->GetInnerNativeContainerHandle = iTabsGetInnerNativeContainerHandleMethod;

  ic->ComputeNaturalSize = iTabsComputeNaturalSizeMethod;
  ic->SetChildrenCurrentSize     = iTabsSetChildrenCurrentSizeMethod;
  ic->SetChildrenPosition        = iTabsSetChildrenPositionMethod;

  ic->LayoutUpdate = iupdrvBaseLayoutUpdateMethod;
  ic->UnMap = iupdrvBaseUnMapMethod;

  /* amy_IupTabs Callbacks */
  iupClassRegisterCallback( data, ic, "TABCHANGE_CB", "nn" );
  iupClassRegisterCallback( data, ic, "TABCHANGEPOS_CB", "ii" );
  iupClassRegisterCallback( data, ic, "RIGHTCLICK_CB", "i" );
  iupClassRegisterCallback( data, ic, "FOCUS_CB", "i" );

  /* Common Callbacks */
  iupBaseRegisterCommonCallbacks( data, ic );

  /* Common */
  iupBaseRegisterCommonAttrib( data, ic );

  /* Visual */
  iupBaseRegisterVisualAttrib( data, ic );

  /* amy_IupTabs only */
  iupClassRegisterAttribute( data, ic, "VALUE", iTabsGetValueAttrib, iTabsSetValueAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "VALUEPOS", iTabsGetValuePosAttrib, iTabsSetValuePosAttrib, IUPAF_SAMEASSYSTEM, "0", IUPAF_NO_SAVE|IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "VALUE_HANDLE", iTabsGetValueHandleAttrib, iTabsSetValueHandleAttrib, NULL, NULL, IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT | IUPAF_IHANDLE | IUPAF_NO_STRING );
  iupClassRegisterAttribute( data, ic, "COUNT", iTabsGetCountAttrib, NULL, NULL, NULL, IUPAF_READONLY|IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "SHOWCLOSE", iTabsGetShowCloseAttrib, iTabsSetShowCloseAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CHILDSIZEALL", NULL, NULL, IUPAF_SAMEASSYSTEM, "Yes", IUPAF_NO_INHERIT );

  /* Base Container */
  iupClassRegisterAttribute( data, ic, "CLIENTSIZE", iTabsGetClientSizeAttrib, NULL, NULL, NULL, IUPAF_READONLY|IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CLIENTOFFSET", iTabsGetClientOffsetAttrib, NULL, NULL, NULL, IUPAF_READONLY|IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "EXPAND", iupBaseContainerGetExpandAttrib, NULL, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );

  /* Native Container */
  iupClassRegisterAttribute( data, ic, "CHILDOFFSET", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );

  iupdrvTabsInitClass( data, ic );

  return ic;
}

IUP_API Ihandle *amy_IupTabsv( struct libData *data, Ihandle**params )
{
	return amy_IupCreatev( data, "tabs", (void**)params );
}

IUP_API Ihandle *amy_IupTabsV( struct libData *data, Ihandle *child, va_list arglist)
{
	return amy_IupCreateV( data, "tabs", child, arglist );
}

IUP_API Ihandle *amy_IupTabs( struct libData *data, Ihandle *child, ... )
{
	Ihandle *ih;

	va_list arglist;
	va_start(arglist, child );
	ih = amy_IupCreateV( data, "tabs", child, arglist );
	va_end(arglist );

	return ih;
}
