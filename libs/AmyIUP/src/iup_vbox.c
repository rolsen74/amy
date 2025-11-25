
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
 * \brief Vbox Control.
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

static int iVboxSetRasterSizeAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if ( ! value)
  {
    ih->userwidth = 0;
    ih->userheight = 0;
  }
  else
  {
    int s = 0, d = 0;
    iupStrToIntInt(value, &s, &d, 'x' );  /* first value will be ignored if second defined, can NOT set width */
    if (d != 0) s = d;
    if (s > 0) 
    {
      ih->userheight = s;
      ih->userwidth = 0;
    }
  }
  iupAttribSet( data, ih, "SIZE", NULL ); /* clear SIZE in hash table */
  return 0;
}

static int iVboxSetSizeAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if ( ! value)
  {
    ih->userwidth = 0;
    ih->userheight = 0;
  }
  else
  {
    int s = 0, d = 0;
    iupStrToIntInt( value, &s, &d, 'x' );  /* first value will be ignored if second defined, can NOT set width */
    if (d != 0) s = d;
    if (s > 0) 
    {
      int charwidth, charheight;
      iupdrvFontGetCharSize( data, ih, &charwidth, &charheight );
      ih->userheight = iupHEIGHT2RASTER(s, charheight );
      ih->userwidth = 0;
    }
  }
  return 1;  /* always save in the hash table, so when FONT is changed SIZE can be updated */
}

static int iVboxSetAlignmentAttrib( struct libData *data, Ihandle *ih, const char *value )
{
  if (iupStrEqualNoCase( value, "ARIGHT" ))
    ih->data->alignment = IUP_ALIGN_ARIGHT;
  else if (iupStrEqualNoCase( value, "ACENTER" ))
    ih->data->alignment = IUP_ALIGN_ACENTER;
  else if (iupStrEqualNoCase( value, "ALEFT" ))
    ih->data->alignment = IUP_ALIGN_ALEFT;
  return 0;
}

static char *iVboxGetAlignmentAttrib( struct libData *data, Ihandle *ih )
{
  char *align2str[3] = {"ALEFT", "ACENTER", "ARIGHT"};
  return iupStrReturnStr(align2str[ih->data->alignment] );
}

static char *iVboxGetOrientationAttrib( struct libData *data, Ihandle *ih )
{
  (void)ih;
  return "VERTICAL";
}

static void iVboxComputeNaturalSizeMethod( struct libData *data, Ihandle *ih, int *w, int *h, int *children_expand )
{
  Ihandle *child;
  int total_natural_width, total_natural_height;

  /* calculate total children natural size */
  int children_count = 0;
  int children_natural_maxwidth = 0;
  int children_natural_maxheight = 0;
  int children_natural_height = 0;

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
      children_natural_height += child->naturalheight;
  }

  /* leave room at the element for the maximum natural size of the children when is_homogeneous */
  if (ih->data->is_homogeneous)
    children_natural_height = children_natural_maxheight*children_count;

  /* compute the Vbox contents natural size */
  total_natural_width  = children_natural_maxwidth + 2*ih->data->margin_horiz;
  total_natural_height = children_natural_height + (children_count-1)*ih->data->gap + 2*ih->data->margin_vert;

  /* Store to be used in iVboxCalcEmptyHeight */
  ih->data->total_natural_size = total_natural_height;

  *w = total_natural_width;
  *h = total_natural_height;
}

static int iHboxCalcHomogeneousHeight( struct libData *data, Ihandle *ih )
{
  Ihandle *child;
  int homogeneous_height;

  int children_count=0;
  for (child = ih->firstchild; child; child = child->brother)
  {
    if ( ! (child->flags & IUP_FLOATING))
      children_count++;
  }
  if (children_count == 0)
    return 0;

  /* equal spaces for all elements */
  homogeneous_height = (ih->currentheight - (children_count-1)*ih->data->gap - 2*ih->data->margin_vert)/children_count;
  if (homogeneous_height < 0) homogeneous_height = 0;
  return homogeneous_height;
}

static int iVboxCalcEmptyHeight( struct libData *data, Ihandle *ih, int expand )
{
  /* This is the space that the child can be expanded. */
  Ihandle *child;
  int empty_height;

  int expand_count=0;
  for (child = ih->firstchild; child; child = child->brother)
  {
    if ( ! (child->flags & IUP_FLOATING) && child->expand & expand)
      expand_count++;
  }
  if (expand_count == 0)
    return 0;

  /* equal spaces for all expandable elements */
  empty_height = (ih->currentheight - ih->data->total_natural_size)/expand_count;  
  if (empty_height < 0) empty_height = 0;
  return empty_height;
}

static void iVboxSetChildrenCurrentSizeMethod(  struct libData *data, Ihandle *ih, int shrink )
{
  Ihandle *child;
  int empty_h0 = 0, empty_h1 = 0, client_width;

  if (ih->data->is_homogeneous)
    ih->data->homogeneous_size = iHboxCalcHomogeneousHeight( data, ih );
  else
  {
    ih->data->homogeneous_size = 0;

    /* must calculate the space left for each control to grow inside the container */
    /* H1 means there is an EXPAND enabled inside */
    if (ih->expand & IUP_EXPAND_H1)
      empty_h1 = iVboxCalcEmptyHeight( data, ih, IUP_EXPAND_H1 );
    /* Not H1 and H0 means that EXPAND is not enabled, but there are some amy_IupFill inside */
    else if (ih->expand & IUP_EXPAND_H0)
      empty_h0 = iVboxCalcEmptyHeight( data, ih, IUP_EXPAND_H0 );
  }

  client_width = ih->currentwidth - 2*ih->data->margin_horiz;
  if (client_width<0) client_width=0;

  for (child = ih->firstchild; child; child = child->brother)
  {
    if ( ! (child->flags & IUP_FLOATING))
    {
      if (ih->data->homogeneous_size)
        iupBaseSetCurrentSize( data, child, client_width, ih->data->homogeneous_size, shrink );
      else
      {
        int empty = (child->expand & IUP_EXPAND_H1)? empty_h1: ((child->expand & IUP_EXPAND_H0)? empty_h0: 0 );
        char *weight_str = iupAttribGet( data, child, "EXPANDWEIGHT" );
        if (weight_str)
        {
          double weight; 
          if (iupStrToDouble( weight_str, &weight))
            empty = iupRound( data, empty * weight );
        }
        iupBaseSetCurrentSize( data, child, client_width, child->naturalheight+empty, shrink );
      }
    }
    else if ( ! (child->flags & IUP_FLOATING_IGNORE))
    {
      /* update children to their own natural size */
      iupBaseSetCurrentSize( data, child, child->naturalwidth, child->naturalheight, shrink );
    }
  }
}

static void iVboxSetChildrenPositionMethod( struct libData *data, Ihandle *ih, int x, int y )
{
  int dx, client_width;
  Ihandle *child;

  x += ih->data->margin_horiz;
  y += ih->data->margin_vert;

  client_width = ih->currentwidth - 2*ih->data->margin_horiz;
  if (client_width<0) client_width=0;

  for (child = ih->firstchild; child; child = child->brother)
  {
    if ( ! (child->flags & IUP_FLOATING))
    {
      if (ih->data->alignment == IUP_ALIGN_ACENTER)
        dx = (client_width - child->currentwidth)/2;
      else if (ih->data->alignment == IUP_ALIGN_ARIGHT)
        dx = client_width - child->currentwidth;
      else  /* IUP_ALIGN_ALEFT */
        dx = 0;
      if (dx<0) dx = 0;
                      
      /* update child */
      iupBaseSetPosition( data, child, x+dx, y );

      /* calculate next */
      if (ih->data->homogeneous_size)
        y += ih->data->homogeneous_size + ih->data->gap;
      else
        y += child->currentheight + ih->data->gap;
    }
  }
}

/******************************************************************************/

IUP_API Ihandle *amy_IupVboxv( struct libData *data, Ihandle **children )
{
  return amy_IupCreatev( data, "vbox", (void**)children );
}

IUP_API Ihandle *amy_IupVboxV( struct libData *data, Ihandle *child, va_list arglist )
{
  return amy_IupCreateV( data, "vbox", child, arglist );
}

IUP_API Ihandle *amy_IupVbox( struct libData *data, Ihandle *child, ... )
{
  Ihandle *ih;

  va_list arglist;
  va_start(arglist, child );
  ih = amy_IupCreateV( data, "vbox", child, arglist );
  va_end(arglist );

  return ih;
}

Iclass *iupVboxNewClass( struct libData *data )
{
  Iclass *ic = iupBoxNewClassBase( data );

  ic->name = "vbox";

  /* Class functions */
  ic->New = iupVboxNewClass;
  ic->ComputeNaturalSize = iVboxComputeNaturalSizeMethod;
  ic->SetChildrenCurrentSize = iVboxSetChildrenCurrentSizeMethod;
  ic->SetChildrenPosition = iVboxSetChildrenPositionMethod;

  /* Overwrite Common */
  iupClassRegisterAttribute( data, ic, "SIZE", iupBaseGetSizeAttrib, iVboxSetSizeAttrib, NULL, NULL, IUPAF_NO_SAVE|IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "RASTERSIZE", iupBaseGetRasterSizeAttrib, iVboxSetRasterSizeAttrib, NULL, NULL, IUPAF_NO_SAVE|IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "ORIENTATION", iVboxGetOrientationAttrib, NULL, IUPAF_SAMEASSYSTEM, "VERTICAL", IUPAF_READONLY | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );

  /* Vbox only */
  iupClassRegisterAttribute( data, ic, "ALIGNMENT", iVboxGetAlignmentAttrib, iVboxSetAlignmentAttrib, IUPAF_SAMEASSYSTEM, "ALEFT", IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );

  return ic;
}
