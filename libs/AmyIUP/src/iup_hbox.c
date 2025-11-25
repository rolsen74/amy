
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"
#include "inc/iup_box.h"

// --

#if 0

/** \file
 * \brief Hbox Control.
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdio.h>
#include <stdlib.h>

#include "iup.h"
#include "iupcbs.h"

#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_drv.h"
#include "iup_drvfont.h"
#include "iup_stdcontrols.h"
#include "iup_layout.h"
#include "iup_box.h"
#include "iup_normalizer.h"
#include "iup_varg.h"

#endif

static int iHboxSetRasterSizeAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if ( ! value)
  {
    ih->userwidth = 0;
    ih->userheight = 0;
  }
  else
  {
    int s = 0, d = 0;
    iupStrToIntInt(value, &s, &d, 'x' );  /* second value will be ignored, can NOT set height */
    if (s > 0) 
    {
      ih->userheight = 0;
      ih->userwidth = s;
    }
  }
  iupAttribSet( data, ih, "SIZE", NULL ); /* clear SIZE in hash table */
  return 0;
}

static int iHboxSetSizeAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if ( ! value)
  {
    ih->userwidth = 0;
    ih->userheight = 0;
  }
  else
  {
    int s = 0, d = 0;
    iupStrToIntInt(value, &s, &d, 'x' );  /* second value will be ignored, can NOT set height */
    if (s > 0) 
    {
      int charwidth, charheight;
      iupdrvFontGetCharSize( data, ih, &charwidth, &charheight );
      ih->userheight = 0;
      ih->userwidth = iupWIDTH2RASTER(s, charwidth );
    }
  }
  return 1;  /* always save in the hash table, so when FONT is changed SIZE can be updated */
}

static int iHboxSetAlignmentAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if (iupStrEqualNoCase(value, "ABOTTOM" ))
    ih->data->alignment = IUP_ALIGN_ABOTTOM;
  else if (iupStrEqualNoCase(value, "ACENTER" ))
    ih->data->alignment = IUP_ALIGN_ACENTER;
  else if (iupStrEqualNoCase(value, "ATOP" ))
    ih->data->alignment = IUP_ALIGN_ATOP;
  return 0;
}

static char *iHboxGetAlignmentAttrib( struct libData *data, Ihandle *ih)
{
  static char *align2str[3] = {"ATOP", "ACENTER", "ABOTTOM"};
  return align2str[ih->data->alignment];
}

static char *iHboxGetOrientationAttrib( struct libData *data, Ihandle *ih)
{
  (void)ih;
  return "HORIZONTAL";
}

static void iHboxComputeNaturalSizeMethod( struct libData *data, Ihandle *ih, int *w, int *h, int *children_expand)
{
  Ihandle *child;
  int total_natural_width, total_natural_height;

  /* calculate total children natural size */
  int children_count = 0;
  int children_natural_width = 0;
  int children_natural_maxwidth = 0;
  int children_natural_maxheight = 0;

  for (child = ih->firstchild; child; child = child->brother)
  {
    if (ih->data->expand_children)
      child->expand = ih->data->expand_children;

    /* update child natural size first */
    if ( ! (child->flags & IUP_FLOATING_IGNORE))
      iupBaseComputeNaturalSize( data, child );

    if ( ! (child->flags & IUP_FLOATING))
    {
      *children_expand |= child->expand;
      children_natural_maxwidth = iupMAX(children_natural_maxwidth, child->naturalwidth );
      children_natural_maxheight = iupMAX(children_natural_maxheight, child->naturalheight );
      children_count++;
    }
  }

  /* reset to max natural width and/or height if NORMALIZESIZE is defined */
  if (ih->data->normalize_size)
    iupNormalizeSizeBoxChild( data, ih, ih->data->normalize_size, children_natural_maxwidth, children_natural_maxheight );

  /* must be done after normalize */
  for (child = ih->firstchild; child; child = child->brother)
  {
    if ( ! (child->flags & IUP_FLOATING))
      children_natural_width += child->naturalwidth;
  }

  /* leave room at the element for the maximum natural size of the children when is_homogeneous */
  if (ih->data->is_homogeneous)
    children_natural_width = children_natural_maxwidth*children_count;

  /* compute the Hbox contents natural size */
  total_natural_width  = children_natural_width + (children_count-1)*ih->data->gap + 2*ih->data->margin_horiz;
  total_natural_height = children_natural_maxheight + 2*ih->data->margin_vert;

  /* Store to be used in iHboxCalcEmptyWidth */
  ih->data->total_natural_size = total_natural_width;

  *w = total_natural_width;
  *h = total_natural_height;
}

static int iHboxCalcHomogeneousWidth( struct libData *data, Ihandle *ih)
{
  Ihandle *child;
  int homogeneous_width;

  int children_count=0;
  for (child = ih->firstchild; child; child = child->brother)
  {
    if ( ! (child->flags & IUP_FLOATING))
      children_count++;
  }
  if (children_count == 0)
    return 0;

  /* equal spaces for all elements */
  homogeneous_width = (ih->currentwidth - (children_count-1)*ih->data->gap - 2*ih->data->margin_horiz)/children_count;
  if (homogeneous_width<0) homogeneous_width = 0;
  return homogeneous_width;
}

static int iHboxCalcEmptyWidth( struct libData *data, Ihandle *ih, int expand)
{
  /* This is the space that the child can be expanded. */
  Ihandle *child;
  int empty_width;

  int expand_count=0;
  for (child = ih->firstchild; child; child = child->brother)
  {
    if ( ! (child->flags & IUP_FLOATING) && child->expand & expand)
      expand_count++;
  }
  if (expand_count == 0)
    return 0;

  /* equal spaces for all expandable elements */
  empty_width = (ih->currentwidth - ih->data->total_natural_size)/expand_count;
  if (empty_width < 0) empty_width = 0;
  return empty_width;
}

static void iHboxSetChildrenCurrentSizeMethod( struct libData *data, Ihandle *ih, int shrink)
{
  /* update children */
  Ihandle *child;
  int empty_w0 = 0, empty_w1 = 0, client_height;

  if (ih->data->is_homogeneous)
    ih->data->homogeneous_size = iHboxCalcHomogeneousWidth( data, ih );
  else
  {
    ih->data->homogeneous_size = 0;

    /* must calculate the space left for each control to grow inside the container */
    /* W1 means there is an EXPAND enabled inside */
    if (ih->expand & IUP_EXPAND_W1)
      empty_w1 = iHboxCalcEmptyWidth( data, ih, IUP_EXPAND_W1 );
    /* Not W1 and W0 means that EXPAND is not enabled but there are some amy_IupFill inside */
    else if (ih->expand & IUP_EXPAND_W0)
      empty_w0 = iHboxCalcEmptyWidth( data, ih, IUP_EXPAND_W0 );
  }

  client_height = ih->currentheight - 2*ih->data->margin_vert;
  if (client_height<0) client_height=0;

  for (child = ih->firstchild; child; child = child->brother)
  {
    if ( ! (child->flags & IUP_FLOATING))
    {
      if (ih->data->homogeneous_size)
        iupBaseSetCurrentSize( data, child, ih->data->homogeneous_size, client_height, shrink );
      else
      {
        int empty = (child->expand & IUP_EXPAND_W1)? empty_w1: ((child->expand & IUP_EXPAND_W0)? empty_w0: 0 );
        char *weight_str = iupAttribGet( data, child, "EXPANDWEIGHT" );
        if (weight_str)
        {
          double weight;
          if (iupStrToDouble(  weight_str, &weight))
            empty = iupRound( data, empty *weight );
        }
        iupBaseSetCurrentSize( data, child, child->naturalwidth+empty, client_height, shrink );
      }
    }
    else if ( ! (child->flags & IUP_FLOATING_IGNORE))
    {
      /* update children to their own natural size */
      iupBaseSetCurrentSize( data, child, child->naturalwidth, child->naturalheight, shrink );
    }
  }
}

static void iHboxSetChildrenPositionMethod( struct libData *data, Ihandle *ih, int x, int y)
{
  int dy, client_height;
  Ihandle *child;

  x += ih->data->margin_horiz;
  y += ih->data->margin_vert;

  client_height = ih->currentheight - 2*ih->data->margin_vert;
  if (client_height<0) client_height=0;

  for (child = ih->firstchild; child; child = child->brother)
  {
    if ( ! (child->flags & IUP_FLOATING))
    {
      if (ih->data->alignment == IUP_ALIGN_ACENTER)
        dy = (client_height - child->currentheight)/2;
      else if (ih->data->alignment == IUP_ALIGN_ABOTTOM)
        dy = client_height - child->currentheight;
      else  /* IUP_ALIGN_ATOP */
        dy = 0;
      if (dy<0) dy = 0;
                      
      /* update child */
      iupBaseSetPosition( data, child, x, y+dy );

      /* calculate next */
      if (ih->data->homogeneous_size)
        x += ih->data->homogeneous_size + ih->data->gap;
      else
        x += child->currentwidth + ih->data->gap;
    }
  }
}


/******************************************************************************/


IUP_API Ihandle *amy_IupHboxv( struct libData *data, Ihandle **children )
{
  return amy_IupCreatev( data, "hbox", (void**)children );
}

IUP_API Ihandle *amy_IupHboxV( struct libData *data, Ihandle *child, va_list arglist )
{
  return amy_IupCreateV( data, "hbox", child, arglist );
}

IUP_API Ihandle *amy_IupHbox( struct libData *data, Ihandle *child, ... )
{
  Ihandle *ih;

  va_list arglist;
  va_start(arglist, child );
  ih = amy_IupCreateV( data, "hbox", child, arglist );
  va_end(arglist );

  return ih;
}

Iclass *iupHboxNewClass( struct libData *data )
{
  Iclass *ic = iupBoxNewClassBase( data );

  ic->name = "hbox";

  /* Class functions */
  ic->New = iupHboxNewClass;
  ic->ComputeNaturalSize = iHboxComputeNaturalSizeMethod;
  ic->SetChildrenCurrentSize = iHboxSetChildrenCurrentSizeMethod;
  ic->SetChildrenPosition = iHboxSetChildrenPositionMethod;

  /* Overwrite Common */
  iupClassRegisterAttribute( data, ic, "SIZE", iupBaseGetSizeAttrib, iHboxSetSizeAttrib, NULL, NULL, IUPAF_NO_SAVE|IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "RASTERSIZE", iupBaseGetRasterSizeAttrib, iHboxSetRasterSizeAttrib, NULL, NULL, IUPAF_NO_SAVE|IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "ORIENTATION", iHboxGetOrientationAttrib, NULL, IUPAF_SAMEASSYSTEM, "HORIZONTAL", IUPAF_READONLY | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );

  /* Hbox only */
  iupClassRegisterAttribute( data, ic, "ALIGNMENT", iHboxGetAlignmentAttrib, iHboxSetAlignmentAttrib, IUPAF_SAMEASSYSTEM, "ATOP", IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );

  return ic;
}
