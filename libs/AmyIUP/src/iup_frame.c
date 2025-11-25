
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
 * \brief Frame Control.
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
#include "iup_frame.h"

#endif

int iupFrameGetTitleHeight( struct libData *data, Ihandle *ih )
{
  int height;
  if (iupdrvFrameGetTitleHeight( data, ih, &height))
    return height;

  iupdrvFontGetCharSize( data, ih, NULL, &height );
  return height;
}

static void iFrameGetDecorSize( struct libData *data, Ihandle *ih, int *width, int *height)
{
  if (iupdrvFrameGetDecorSize( data, ih, width, height))
    return;

  *width = 5;
  *height = 5;

  if (iupAttribGet( data, ih, "_IUPFRAME_HAS_TITLE" ) || iupAttribGet( data, ih, "TITLE" ))
    (*height) += iupFrameGetTitleHeight( data, ih );
}

char *iupFrameGetBgColorAttrib( struct libData *data, Ihandle *ih )
{
  if (iupAttribGet( data, ih, "_IUPFRAME_HAS_BGCOLOR" ))
    return NULL;  /* get from the hash table */
  else
    return iupBaseNativeParentGetBgColorAttrib( data, ih );
}

static char *iFrameGetClientSizeAttrib( struct libData *data, Ihandle *ih )
{
  int width, height, decorwidth, decorheight;
  width = ih->currentwidth;
  height = ih->currentheight;
  iFrameGetDecorSize( data, ih, &decorwidth, &decorheight );
  width -= decorwidth;
  height -= decorheight;
  if (width < 0) width = 0;
  if (height < 0) height = 0;
  return iupStrReturnIntInt(width, height, 'x' );
}

static char *iFrameGetClientOffsetAttrib( struct libData *data, Ihandle *ih )
{
  int dx = 0, dy = 0;

  /* In Windows the position of the child is still
  relative to the top-left corner of the frame.
  So we must manually add the decorations. */
  if ( ! iupdrvFrameHasClientOffset( data, ih ))
  {
    /* GTK and Motif Only */

    iupdrvFrameGetDecorOffset( data, ih, &dx, &dy );

    if (iupAttribGet( data, ih, "_IUPFRAME_HAS_TITLE" ) || iupAttribGet( data, ih, "TITLE" ))
      dy += iupFrameGetTitleHeight( data, ih );
  }

  return iupStrReturnIntInt(dx, dy, 'x' );
}

static int iFrameCreateMethod( struct libData *data, Ihandle *ih, void** params)
{
  if (params)
  {
    Ihandle** iparams = (Ihandle**)params;
    if (*iparams)
      amy_IupAppend( data, ih, *iparams );
  }

  return IUP_NOERROR;
}

static void iFrameComputeNaturalSizeMethod( struct libData *data, Ihandle *ih, int *w, int *h, int *children_expand)
{
  int decorwidth, decorheight;
  Ihandle *child = ih->firstchild;

  iFrameGetDecorSize( data, ih, &decorwidth, &decorheight );
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

static void iFrameSetChildrenCurrentSizeMethod( struct libData *data, Ihandle *ih, int shrink)
{
  int width, height, decorwidth, decorheight;

  iFrameGetDecorSize( data, ih, &decorwidth, &decorheight );

  width = ih->currentwidth-decorwidth;
  height = ih->currentheight-decorheight;
  if (width < 0) width = 0;
  if (height < 0) height = 0;

  if (ih->firstchild)
    iupBaseSetCurrentSize( data, ih->firstchild, width, height, shrink );
}

static void iFrameSetChildrenPositionMethod( struct libData *data, Ihandle *ih, int x, int y)
{
  if (ih->firstchild)
  {
    char *offset = iupAttribGet( data, ih, "CHILDOFFSET" );

    /* Native container, position is reset */
    x = 0;
    y = 0;

    if (offset) iupStrToIntInt(offset, &x, &y, 'x' );

    /* In Windows the position of the child is still
    relative to the top-left corner of the frame.
    So we must manually add the decorations. */
    if (iupdrvFrameHasClientOffset( data, ih ))
    {
      /* Windows Only */
      int dx = 0, dy = 0;
      iupdrvFrameGetDecorOffset( data, ih, &dx, &dy );

      if (iupAttribGet( data, ih, "_IUPFRAME_HAS_TITLE" ) || iupAttribGet( data, ih, "TITLE" ))
        dy += iupFrameGetTitleHeight( data, ih );

      x += dx;
      y += dy;
    }

    /* Child coordinates are relative to client left-top corner. */
    iupBaseSetPosition( data, ih->firstchild, x, y );
  }
}


/******************************************************************************/


IUP_API Ihandle *amy_IupFrame( struct libData *data, Ihandle *child )
{
  void *children[2];
  children[0] = (void*)child;
  children[1] = NULL;
  return amy_IupCreatev( data, "frame", children );
}

Iclass *iupFrameNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, NULL );

  ic->name = "frame";
  ic->format = "h"; /* one Ihandle **/
  ic->nativetype = IUP_TYPECONTROL;
  ic->childtype = IUP_CHILDMANY+1;   /* 1 child */
  ic->is_interactive = 0;

  /* Class functions */
  ic->New = iupFrameNewClass;
  ic->Create = iFrameCreateMethod;

  ic->ComputeNaturalSize = iFrameComputeNaturalSizeMethod;
  ic->SetChildrenCurrentSize = iFrameSetChildrenCurrentSizeMethod;
  ic->SetChildrenPosition = iFrameSetChildrenPositionMethod;

  ic->LayoutUpdate = iupdrvBaseLayoutUpdateMethod;
  ic->UnMap = iupdrvBaseUnMapMethod;

  /* Common Callbacks */
  iupClassRegisterCallback( data, ic, "MAP_CB", "" );
  iupClassRegisterCallback( data, ic, "UNMAP_CB", "" );
  iupClassRegisterCallback( data, ic, "FOCUS_CB", "i" );

  /* Common */
  iupBaseRegisterCommonAttrib( data, ic );

  /* Visual */
  iupBaseRegisterVisualAttrib( data, ic );

  /* Base Container */
  iupClassRegisterAttribute( data, ic, "CLIENTSIZE", iFrameGetClientSizeAttrib, NULL, NULL, NULL, IUPAF_READONLY | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CLIENTOFFSET", iFrameGetClientOffsetAttrib, NULL, NULL, NULL, IUPAF_READONLY | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "EXPAND", iupBaseContainerGetExpandAttrib, NULL, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );

  /* Native Container */
  iupClassRegisterAttribute( data, ic, "CHILDOFFSET", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );

  /* amy_IupFrame only */
  iupClassRegisterAttribute( data, ic, "SUNKEN", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );

  iupdrvFrameInitClass( data, ic );

  return ic;
}
