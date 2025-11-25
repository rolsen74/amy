
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
 * \brief iupsplit control
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "iup.h"
#include "iupcbs.h"
#include "iupkey.h"

#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_drv.h"
#include "iup_stdcontrols.h"
#include "iup_layout.h"
#include "iup_childtree.h"

#endif

enum { ISPLIT_VERT, ISPLIT_HORIZ };
enum { ISPLIT_HIDE, ISPLIT_SHOW };

struct _IcontrolData
{
  /* aux */
  int is_holding;
  int start_pos, start_bar, start_size;

  /* attributes */
  int layoutdrag, autohide, showgrip, barsize;
  int orientation;  /* one of the types: ISPLIT_VERT, ISPLIT_HORIZ */
  int val;  /* split value: 0-1000, default 500 */
  int min, max;  /* used only to crop val */
};

static void iSplitAutoHideChild( struct libData *data, Ihandle * child, int flag)
{
  if (flag==ISPLIT_HIDE)
  {
    if ( amy_IupGetInt( data, child, "VISIBLE" ))
    {
      amy_IupSetAttribute( data, child, "FLOATING", "IGNORE" );
      amy_IupSetAttribute( data, child, "VISIBLE", "NO" );
    }
  }
  else 
  {
    if ( ! amy_IupGetInt( data, child, "VISIBLE" ))
    {
      amy_IupSetAttribute( data, child, "FLOATING", "NO" );
      amy_IupSetAttribute( data, child, "VISIBLE", "YES" );
    }
  }
}

static void iSplitAutoHide( struct libData *data, Ihandle *ih )
{
  Ihandle *child1 = ih->firstchild->brother;
  if (child1)
  {
    int tol;
    Ihandle *child2 = child1->brother;

    if ( ih->data->orientation == ISPLIT_VERT)
    {
      if ( ih->currentwidth <= ih->data->barsize)
        tol = 50;
      else
        tol = (1000*ih->data->barsize)/ih->currentwidth;
    }
    else
    {
      if ( ih->currentheight <= ih->data->barsize)
        tol = 50;
      else
        tol = (1000 * ih->data->barsize) / ih->currentheight;
    }

    iSplitAutoHideChild( data, child1, ih->data->val<=tol? ISPLIT_HIDE: ISPLIT_SHOW );

    if (child2)
      iSplitAutoHideChild( data, child2, ih->data->val>=(1000-tol)? ISPLIT_HIDE: ISPLIT_SHOW );
  }
}

static int iupRoundUp(double d)
{
  return (int)ceil(d );
}

static int iSplitGetWidth1( struct libData *data, Ihandle *ih )
{
  /* This is the space available for the child,
     It does NOT depends on the child. */
  int width1 = iupRoundUp((( ih->currentwidth - ih->data->barsize)*ih->data->val) / 1000.0 );
  if (width1 < 0) width1 = 0;
  return width1;
}

static int iSplitGetWidth2( struct libData *data, Ihandle * ih, int width1)
{
  /* This is the space available for the child,
     It does NOT depends on the child. */
  int width2 = (ih->currentwidth-ih->data->barsize) - width1;
  if (width2 < 0) width2 = 0;
  return width2;
}

static int iSplitGetHeight1( struct libData *data, Ihandle *ih )
{
  /* This is the space available for the child,
     It does NOT depends on the child. */
  int height1 = iupRoundUp((( ih->currentheight - ih->data->barsize)*ih->data->val) / 1000.0 );
  if (height1 < 0) height1 = 0;
  return height1;
}

static int iSplitGetHeight2( struct libData *data, Ihandle * ih, int height1)
{
  /* This is the space available for the child,
     It does NOT depends on the child. */
  int height2 = (ih->currentheight-ih->data->barsize) - height1;
  if (height2 < 0) height2 = 0;
  return height2;
}

static void iSplitCalcVal( struct libData *data, Ihandle * ih, int size1)
{
  if ( ih->data->orientation == ISPLIT_VERT)
    ih->data->val = (size1 * 1000) / ( ih->currentwidth - ih->data->barsize );
  else
    ih->data->val = (size1 * 1000) / ( ih->currentheight - ih->data->barsize );
}

static void iSplitAdjustVal( struct libData *data, Ihandle *ih )
{
  if ( ih->data->val < ih->data->min) 
    ih->data->val = ih->data->min;
  if ( ih->data->val > ih->data->max) 
    ih->data->val = ih->data->max;

  if ( ih->data->autohide)
    iSplitAutoHide( data, ih );  
}

static int iSplitAdjustWidth1( struct libData *data, Ihandle * ih, int *width1)
{
  Ihandle *child1 = ih->firstchild->brother;
  if (child1)
  {
    Ihandle *child2 = child1->brother;

    int min_width1 = *width1;
    iupLayoutApplyMinMaxSize( data, child1, &min_width1, NULL );
    if (min_width1 > *width1)
    {
      *width1 = min_width1;  /* minimum value for width1 */
      return 1;
    }

    if (child2)
    {
      int width2 = iSplitGetWidth2( data, ih, *width1 );
      int min_width2 = width2;
      iupLayoutApplyMinMaxSize( data, child2, &min_width2, NULL );
      if (min_width2 > width2)
      {
        width2 = min_width2;  /* minimum value for width2 */
        *width1 = (ih->currentwidth-ih->data->barsize) - width2;  /* maximum value for width1 */
        return 1;
      }
    }
  }
  return 0;
}

static int iSplitAdjustHeight1( struct libData *data, Ihandle * ih, int *height1)
{
  Ihandle *child1 = ih->firstchild->brother;
  if (child1)
  {
    Ihandle *child2 = child1->brother;

    int min_height1 = *height1;
    iupLayoutApplyMinMaxSize( data, child1, NULL, &min_height1 );
    if (min_height1 > *height1)
    {
      *height1 = min_height1;  /* minimum value for height1 */
      return 1;
    }

    if (child2)
    {
      int height2 = iSplitGetHeight2( data, ih, *height1 );
      int min_height2 = height2;
      iupLayoutApplyMinMaxSize( data, child2, NULL, &min_height2 );
      if (min_height2 > height2)
      {
        height2 = min_height2;  /* minimum value for height2 */
        *height1 = ( ih->currentheight-ih->data->barsize) - height2;  /* maximum value for height1 */
        return 1;
      }
    }
  }
  return 0;
}

static void iSplitSetBarPosition( struct libData *data, Ihandle *ih )
{
  /* Update only the bar position, 
     used only when LAYOUTDRAG=NO */
  int x = ih->x, 
      y = ih->y;

  if ( ih->data->orientation == ISPLIT_VERT)
  {
    /* bar */
    x += iSplitGetWidth1( data, ih );
    iupBaseSetPosition( data, ih->firstchild, x, y );
  }
  else /* ISPLIT_HORIZ */
  {
    /* bar */
    y += iSplitGetHeight1( data, ih );
    iupBaseSetPosition( data, ih->firstchild, x, y );
  }

  amy_IupSetAttribute( data, ih->firstchild, "ZORDER", "TOP" );
  iupClassObjectLayoutUpdate( data, ih->firstchild );
}


/*****************************************************************************\
|* Callbacks of canvas bar                                                   *|
\*****************************************************************************/

static int iSplitMotion_CB( struct libData *data, Ihandle * bar, int x, int y, char *status)
{
  Ihandle *ih = bar->parent;

  if ( ih->data->is_holding)
  {
    if (iup_isbutton1(status))  /* DRAG MOVE */
    {
      int old_val = ih->data->val;
      int cur_x, cur_y;

      iupStrToIntInt( amy_IupGetGlobal( data, "CURSORPOS" ), &cur_x, &cur_y, 'x' );

      if ( ih->data->orientation == ISPLIT_VERT)
      {
        int width1 = ih->data->start_size + (cur_x - ih->data->start_pos );
        iSplitAdjustWidth1( data, ih, &width1 );
        iSplitCalcVal( data, ih, width1 );
      }
      else
      {
        int height1 = ih->data->start_size + (cur_y - ih->data->start_pos );
        iSplitAdjustHeight1( data, ih, &height1 );
        iSplitCalcVal( data, ih, height1 );
      }

      iSplitAdjustVal( data, ih );

      if (old_val != ih->data->val)
        iupBaseCallValueChangedCb( data, ih );

      if ( ih->data->layoutdrag)
      {
        amy_IupRefreshChildren( data, ih );
        amy_IupFlush( data );
      }
      else
        iSplitSetBarPosition( data, ih );
    }
    else
      ih->data->is_holding = 0;
  }

  (void)x;
  (void)y;
  return IUP_DEFAULT;
}

static int iSplitButton_CB( struct libData *data, Ihandle * bar, int button, int pressed, int x, int y, char *status)
{
  Ihandle *ih = bar->parent;

  if (button!=IUP_BUTTON1)
    return IUP_DEFAULT;

  if ( ! ih->data->is_holding && pressed)  /* DRAG BEGIN */
  {
    int cur_x, cur_y;

    ih->data->is_holding = 1;

    iupStrToIntInt( amy_IupGetGlobal( data, "CURSORPOS" ), &cur_x, &cur_y, 'x' );

    /* Save the cursor position and size */
    if ( ih->data->orientation == ISPLIT_VERT)
    {
      ih->data->start_bar = ih->firstchild->x;
      ih->data->start_pos = cur_x;
      ih->data->start_size = ih->firstchild->x - ih->x;
    }
    else
    {
      ih->data->start_bar = ih->firstchild->y;
      ih->data->start_pos = cur_y;
      ih->data->start_size = ih->firstchild->y - ih->y;
    }
  }
  else if ( ih->data->is_holding && !pressed)  /* DRAG END */
  {
    ih->data->is_holding = 0;

    /* Always refresh when releasing the mouse */
    amy_IupRefreshChildren( data, ih );  
  }

  (void)x;
  (void)y;
  (void)status;
  return IUP_DEFAULT;
}

static int iSplitFocus_CB( struct libData *data, Ihandle * bar, int focus)
{
  Ihandle *ih = bar->parent;

  if ( ! ih || focus) /* use only kill focus */
    return IUP_DEFAULT;

  if ( ih->data->is_holding)
    ih->data->is_holding = 0;

  return IUP_DEFAULT;
}


/*****************************************************************************\
|* Attributes                                                                *|
\*****************************************************************************/


static char *iSplitGetClientSizeAttrib( struct libData *data, Ihandle *ih )
{
  int width = ih->currentwidth;
  int height = ih->currentheight;

  if ( ih->data->orientation == ISPLIT_VERT)
    width -= ih->data->barsize;
  else
    height -= ih->data->barsize;

  if (width < 0) width = 0;
  if (height < 0) height = 0;
  return iupStrReturnIntInt(width, height, 'x' );
}

static int iSplitSetColorAttrib( struct libData *data, Ihandle * ih, const char *value)
{
  if (value != NULL && ih->data->showgrip == 0)
    amy_IupSetAttribute( data, ih->firstchild, "STYLE", "FILL" );

  amy_IupSetStrAttribute( data, ih->firstchild, "COLOR", value );
  return 0;
}

static char *iSplitGetColorAttrib( struct libData *data, Ihandle *ih )
{
  return amy_IupGetAttribute( data, ih->firstchild, "COLOR" );
}

static int iSplitSetOrientationAttrib( struct libData *data, Ihandle * ih, const char *value)
{
  if ( ih->handle) /* only before map */
    return 0;

  amy_IupSetStrAttribute( data, ih->firstchild, "ORIENTATION", value );

  if (iupStrEqualNoCase(value, "HORIZONTAL" ))
    ih->data->orientation = ISPLIT_HORIZ;
  else  /* Default = VERTICAL */
    ih->data->orientation = ISPLIT_VERT;

  if ( ih->data->orientation == ISPLIT_VERT)
    amy_IupSetAttribute( data, ih->firstchild, "CURSOR", "SPLITTER_VERT" );
  else
    amy_IupSetAttribute( data, ih->firstchild, "CURSOR", "SPLITTER_HORIZ" );

  return 0;  /* do not store value in hash table */
}

static int iSplitSetValueAttrib( struct libData *data, Ihandle * ih, const char *value)
{
  if ( ! value)
  {
    ih->data->val = -1;  /* reset to calculate in Natural size */

    if ( ih->handle)
      amy_IupRefreshChildren( data, ih );  
  }
  else
  {
    int val;
    if (iupStrToInt(value, &val))
    {
      ih->data->val = val;
      iSplitAdjustVal( data, ih );

      if ( ih->handle)
        amy_IupRefreshChildren( data, ih );  
    }
  }

  return 0; /* do not store value in hash table */
}

static char *iSplitGetValueAttrib( struct libData *data, Ihandle *ih )
{
  return amy_iupStrReturnInt( data, ih->data->val );
}

static int iSplitSetBarSizeAttrib( struct libData *data, Ihandle * ih, const char *value)
{
  if (iupStrToInt(value, &ih->data->barsize))
  {
    amy_IupSetInt( data, ih->firstchild, "BARSIZE", ih->data->barsize );

    if ( ih->data->barsize == 0)
      amy_IupSetAttribute( data, ih->firstchild, "VISIBLE", "NO" );
    else
      amy_IupSetAttribute( data, ih->firstchild, "VISIBLE", "YES" );

    if ( ih->data->val != -1)
      iSplitAdjustVal( data, ih );  /* because of autohide */

    if ( ih->handle)
      amy_IupRefreshChildren( data, ih );  
  }
  return 0; /* do not store value in hash table */
}

static char *iSplitGetBarSizeAttrib( struct libData *data, Ihandle *ih )
{
  return amy_iupStrReturnInt( data, ih->data->barsize );
}

static int iSplitSetMinMaxAttrib( struct libData *data, Ihandle * ih, const char *value)
{
  if (iupStrToIntInt(value, &ih->data->min, &ih->data->max, ':'))
  {
    if ( ih->data->min > ih->data->max)
    {
      int t = ih->data->min;
      ih->data->min = ih->data->max;
      ih->data->max = t;
    }
    if ( ih->data->min < 0) ih->data->min = 0;
    if ( ih->data->max > 1000) ih->data->max = 1000;

    if ( ih->data->val != -1)
      iSplitAdjustVal( data, ih );

    if ( ih->handle)
      amy_IupRefreshChildren( data, ih );  
  }
  return 0; /* do not store value in hash table */
}

static char *iSplitGetMinMaxAttrib( struct libData *data, Ihandle *ih )
{
  return iupStrReturnIntInt( ih->data->min, ih->data->max, ':' );
}

static int iSplitSetLayoutDragAttrib( struct libData *data, Ihandle * ih, const char *value)
{
  if (iupStrBoolean(value))
    ih->data->layoutdrag = 1;
  else
    ih->data->layoutdrag = 0;

  return 0; /* do not store value in hash table */
}

static char *iSplitGetLayoutDragAttrib( struct libData *data, Ihandle *ih )
{
  return iupStrReturnBoolean( ih->data->layoutdrag ); 
}

static int iSplitSetShowGripAttrib( struct libData *data, Ihandle * ih, const char *value)
{
  if (iupStrBoolean(value))
  {
    ih->data->showgrip = 1;
    amy_IupSetAttribute( data, ih->firstchild, "STYLE", "GRIP" );
  }
  else
  {
    if (iupStrEqualNoCase(value, "LINES" ))
    {
      amy_IupSetAttribute( data, ih->firstchild, "STYLE", "DUALLINES" );
      ih->data->showgrip = 2;
    }
    else
    {
      if (iupAttribGet( data, ih, "COLOR" ) != NULL)
        amy_IupSetAttribute( data, ih->firstchild, "STYLE", "FILL" );
      else
        amy_IupSetAttribute( data, ih->firstchild, "STYLE", "EMPTY" );

      ih->data->showgrip = 0;

      if ( ih->data->barsize == 5)
        iSplitSetBarSizeAttrib( data, ih, "3" );
    }
  }

  return 0; /* do not store value in hash table */
}

static char *iSplitGetShowGripAttrib( struct libData *data, Ihandle *ih )
{
  if ( ih->data->showgrip == 2)
    return "LINES";
  else
    return iupStrReturnBoolean( ih->data->showgrip ); 
}

static int iSplitSetAutoHideAttrib( struct libData *data, Ihandle * ih, const char *value)
{
  if (iupStrBoolean(value))
    ih->data->autohide = 1;
  else
  {
    Ihandle *child1 = ih->firstchild->brother;
    if (child1)
    {
      Ihandle *child2 = child1->brother;
      iSplitAutoHideChild( data, child1, ISPLIT_SHOW );
      if (child2)
        iSplitAutoHideChild( data, child2, ISPLIT_SHOW );
    }

    ih->data->autohide = 0;
  }

  if ( ih->data->val != -1)
    iSplitAdjustVal( data, ih );

  if ( ih->handle)
    amy_IupRefreshChildren( data, ih );  

  return 0; /* do not store value in hash table */
}

static char *iSplitGetAutoHideAttrib( struct libData *data, Ihandle *ih )
{
  return iupStrReturnBoolean( ih->data->autohide ); 
}


/*****************************************************************************\
|* Methods                                                                   *|
\*****************************************************************************/


static void iSplitComputeNaturalSizeMethod( struct libData *data, Ihandle * ih, int *w, int *h, int *children_expand)
{
  int natural_w = 0, 
      natural_h = 0;
  Ihandle *child1, *child2 = NULL;
  child1 = ih->firstchild->brother;
  if (child1)
    child2 = child1->brother;

  /* bar */
  if ( ih->data->orientation == ISPLIT_VERT)
    natural_w += ih->data->barsize;
  else
    natural_h += ih->data->barsize;

  if (child1 && !(child1->flags & IUP_FLOATING_IGNORE))
  {
    /* update child natural size first */
    iupBaseComputeNaturalSize( data, child1 );

    if ( ih->data->orientation == ISPLIT_VERT)
    {
      natural_w += child1->naturalwidth;
      natural_h = iupMAX(natural_h, child1->naturalheight );
    }
    else
    {
      natural_w = iupMAX(natural_w, child1->naturalwidth );
      natural_h += child1->naturalheight;
    }

    *children_expand |= child1->expand;
  }

  if (child2 && !(child2->flags & IUP_FLOATING_IGNORE))
  {
    /* update child natural size first */
    iupBaseComputeNaturalSize( data, child2 );

    if ( ih->data->orientation == ISPLIT_VERT)
    {
      natural_w += child2->naturalwidth;
      natural_h = iupMAX(natural_h, child2->naturalheight );
    }
    else
    {
      natural_w = iupMAX(natural_w, child2->naturalwidth );
      natural_h += child2->naturalheight;
    }

    *children_expand |= child2->expand;
  }

  if ( ih->data->val == -1)  /* first time or reset, re-compute value from natural size */
  {
    if (child1)
    {
      /* just is just an initial value based on natural size of the split and the child, similar to iSplitCalcVal */
      if ( ih->data->orientation == ISPLIT_VERT)
        ih->data->val = (child1->naturalwidth*1000)/(natural_w - ih->data->barsize );
      else
        ih->data->val = (child1->naturalheight*1000)/(natural_h - ih->data->barsize );
    }
    else
      ih->data->val = ih->data->min;

    iSplitAdjustVal( data, ih );
  }

  *w = natural_w;
  *h = natural_h;
}

static void iSplitSetChildrenCurrentSizeMethod( struct libData *data, Ihandle * ih, int shrink)
{
  int old_val = ih->data->val;
  Ihandle *child1, *child2 = NULL;
  child1 = ih->firstchild->brother;
  if (child1)
    child2 = child1->brother;

  if ( ih->data->orientation == ISPLIT_VERT)
  {
    int width1 = iSplitGetWidth1( data, ih );
    if (iSplitAdjustWidth1( data, ih, &width1))    /* this will check for child1 and child2 */
      iSplitCalcVal( data, ih, width1 );  /* has a MINMAX size, must fix split value */

    if (child1 && !(child1->flags & IUP_FLOATING_IGNORE))
    {
      iupBaseSetCurrentSize( data, child1, width1, ih->currentheight, shrink );

      if ( ! (child1->flags & IUP_FLOATING_IGNORE) && child1->currentwidth > width1)
      {
        /* has a minimum size, must fix split value */
        width1 = child1->currentwidth;
        iSplitCalcVal( data, ih, width1 );
      }
    }

    /* bar */
    ih->firstchild->currentwidth  = ih->data->barsize;
    ih->firstchild->currentheight = ih->currentheight;

    if (child2 && !(child2->flags & IUP_FLOATING_IGNORE))
    {
      int width2 = iSplitGetWidth2( data, ih, width1 );
      iupBaseSetCurrentSize( data, child2, width2, ih->currentheight, shrink );

      if (child2->currentwidth > width2)
      {
        /* has a minimum size, must fix split value */
        width2 = child2->currentwidth;
        width1 = (ih->currentwidth-ih->data->barsize) - width2;
        iSplitCalcVal( data, ih, width1 );
        if (child1)
          iupBaseSetCurrentSize( data, child1, width1, ih->currentheight, shrink );
      }
    }
  }
  else /* ISPLIT_HORIZ */
  {
    int height1 = iSplitGetHeight1( data, ih );
    if (iSplitAdjustHeight1( data, ih, &height1))  /* this will check for child1 and child2 */
      iSplitCalcVal( data, ih, height1 );  /* has a MINMAX size, must fix split value */

    if (child1 && !(child1->flags & IUP_FLOATING_IGNORE))
    {
      iupBaseSetCurrentSize( data, child1, ih->currentwidth, height1, shrink );

      if (child1->currentheight > height1)
      {
        /* has a minimum size, must fix split value */
        height1 = child1->currentheight;
        iSplitCalcVal( data, ih, height1 );
      }
    }

    /* bar */
    ih->firstchild->currentwidth  = ih->currentwidth;
    ih->firstchild->currentheight = ih->data->barsize;

    if (child2 && !(child2->flags & IUP_FLOATING_IGNORE))
    {
      int height2 = iSplitGetHeight2( data, ih, height1 );
      iupBaseSetCurrentSize( data, child2, ih->currentwidth, height2, shrink );

      if (child2->currentheight > height2)
      {
        /* has a minimum size, must fix split value */
        height2 = child2->currentheight;
        height1 = (ih->currentheight-ih->data->barsize) - height2;
        iSplitCalcVal( data, ih, height1 );
        if (child1)
          iupBaseSetCurrentSize( data, child1, ih->currentwidth, height1, shrink );
      }
    }
  }

  if (old_val != ih->data->val)
    iupBaseCallValueChangedCb( data, ih );
}

static void iSplitSetChildrenPositionMethod( struct libData *data, Ihandle * ih, int x, int y)
{
  Ihandle *child1, *child2 = NULL;
  child1 = ih->firstchild->brother;
  if (child1)
    child2 = child1->brother;

  if ( ih->data->orientation == ISPLIT_VERT)
  {
    if (child1 && !(child1->flags & IUP_FLOATING_IGNORE))
      iupBaseSetPosition( data, child1, x, y );

    /* bar */
    x += iSplitGetWidth1( data, ih );
    iupBaseSetPosition( data, ih->firstchild, x, y );

    if (child2 && !(child2->flags & IUP_FLOATING_IGNORE))
    {
      x += ih->data->barsize;
      iupBaseSetPosition( data, child2, x, y );
    }
  }
  else /* ISPLIT_HORIZ */
  {
    if (child1 && !(child1->flags & IUP_FLOATING_IGNORE))
      iupBaseSetPosition( data, child1, x, y );

    /* bar */
    y += iSplitGetHeight1( data, ih );
    iupBaseSetPosition( data, ih->firstchild, x, y );

    if (child2 && !(child2->flags & IUP_FLOATING_IGNORE))
    {
      y += ih->data->barsize;
      iupBaseSetPosition( data, child2, x, y );
    }
  }
}

static int iSplitCreateMethod( struct libData *data, Ihandle * ih, void** params)
{
  Ihandle *bar;

  ih->data = iupALLOCCTRLDATA();

  ih->data->orientation = ISPLIT_VERT;
  ih->data->val = -1;
  ih->data->layoutdrag = 1;
  ih->data->autohide = 0;
  ih->data->barsize = 5;
  ih->data->showgrip = 1;
  ih->data->min = 0; 
  ih->data->max = 1000;

  bar = amy_IupFlatSeparator( data );
  iupChildTreeAppend( data, ih, bar );  /* bar will always be the firstchild */
  bar->flags |= IUP_INTERNAL;

  amy_IupSetAttribute( data, bar, "EXPAND", "NO" );
  amy_IupSetAttribute( data, bar, "CURSOR", "SPLITTER_VERT" );
  amy_IupSetAttribute( data, bar, "STYLE", "GRIP" );
  amy_IupSetAttribute( data, bar, "ORIENTATION", "VERTICAL" );

  /* Setting callbacks */
  amy_IupSetCallback( data, bar, "BUTTON_CB", (Icallback) iSplitButton_CB );
  amy_IupSetCallback( data, bar, "FOCUS_CB",  (Icallback) iSplitFocus_CB );
  amy_IupSetCallback( data, bar, "MOTION_CB", (Icallback) iSplitMotion_CB );

  if (params)
  {
    Ihandle** iparams = (Ihandle **)params;
    if (iparams[0] ) amy_IupAppend( data, ih, iparams[0] );
    if (iparams[1] ) amy_IupAppend( data, ih, iparams[1] );
  }

  return IUP_NOERROR;
}

Iclass *iupSplitNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, NULL );

  ic->name   = "split";
  ic->format = "hh";   /* two Ihandle*(s) */
  ic->nativetype = IUP_TYPEVOID;
  ic->childtype = IUP_CHILDMANY+3;  /* canvas+child+child */
  ic->is_interactive = 0;

  /* Class functions */
  ic->New = iupSplitNewClass;
  ic->Create  = iSplitCreateMethod;
  ic->Map     = iupBaseTypeVoidMapMethod;

  ic->ComputeNaturalSize = iSplitComputeNaturalSizeMethod;
  ic->SetChildrenCurrentSize = iSplitSetChildrenCurrentSizeMethod;
  ic->SetChildrenPosition    = iSplitSetChildrenPositionMethod;

  /* Base Callbacks */
  iupBaseRegisterBaseCallbacks( data, ic );

  /* Callbacks */
  iupClassRegisterCallback( data, ic, "VALUECHANGED_CB", "" );

  /* Common */
  iupBaseRegisterCommonAttrib( data, ic );

  /* Base Container */
  iupClassRegisterAttribute( data, ic, "EXPAND", iupBaseContainerGetExpandAttrib, NULL, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CLIENTSIZE", iSplitGetClientSizeAttrib, NULL, NULL, NULL, IUPAF_NOT_MAPPED | IUPAF_READONLY | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CLIENTOFFSET", iupBaseGetClientOffsetAttrib, NULL, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_READONLY|IUPAF_NO_INHERIT );

  /* amy_IupSplit only */
  iupClassRegisterAttribute( data, ic, "DIRECTION", NULL, iSplitSetOrientationAttrib, IUPAF_SAMEASSYSTEM, "VERTICAL", IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "VALUE", iSplitGetValueAttrib, iSplitSetValueAttrib, IUPAF_SAMEASSYSTEM, "500", IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "LAYOUTDRAG", iSplitGetLayoutDragAttrib, iSplitSetLayoutDragAttrib, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "AUTOHIDE", iSplitGetAutoHideAttrib, iSplitSetAutoHideAttrib, IUPAF_SAMEASSYSTEM, "NO", IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MINMAX", iSplitGetMinMaxAttrib, iSplitSetMinMaxAttrib, IUPAF_SAMEASSYSTEM, "0:1000", IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );


  iupClassRegisterAttribute( data, ic, "COLOR", iSplitGetColorAttrib, iSplitSetColorAttrib, IUPAF_SAMEASSYSTEM, "160 160 160", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "ORIENTATION", NULL, iSplitSetOrientationAttrib, IUPAF_SAMEASSYSTEM, "VERTICAL", IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "SHOWGRIP", iSplitGetShowGripAttrib, iSplitSetShowGripAttrib, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "BARSIZE", iSplitGetBarSizeAttrib, iSplitSetBarSizeAttrib, IUPAF_SAMEASSYSTEM, "5", IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );


  return ic;
}

IUP_API Ihandle *amy_IupSplit( struct libData *data, Ihandle * child1, Ihandle *child2)
{
  void *children[3];
  children[0] = (void*)child1;
  children[1] = (void*)child2;
  children[2] = NULL;
  return amy_IupCreatev( data, "split", children );
}
