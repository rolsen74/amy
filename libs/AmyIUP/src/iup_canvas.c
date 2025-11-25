
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"
#include "inc/iup_canvas.h"

// --

#if 0

/** \file
 * \brief Canvas Control.
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdio.h>
#include <stdlib.h>

#include "iup.h"
#include "iupcbs.h"
#include "iupdraw.h"

#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_drv.h"
#include "iup_drvfont.h"
#include "iup_stdcontrols.h"
#include "iup_layout.h"
#include "iup_canvas.h"

#endif

void iupCanvasCalcScrollIntPos( struct libData *data, 
	double min, double max, double page, double pos, 
    int imin,   int imax,  int *ipage,  int *ipos)
{
  double range = max-min;
  int irange = imax-imin;
  double ratio = ((double)irange)/range;

  *ipage = (int)(page*ratio );
  if (*ipage > irange) *ipage = irange;
  if (*ipage < 1) *ipage = 1;

  if (ipos)
  {
    *ipos = (int)((pos-min)*ratio) + imin;
    if (*ipos < imin) *ipos = imin;
    if (*ipos > (imax - *ipage)) *ipos = imax - *ipage;
  }
}

void iupCanvasCalcScrollRealPos( struct libData *data, 
	double min, double max, double *pos, 
    int imin,   int imax,  int ipage,  int *ipos)
{
  double range = max-min;
  int irange = imax-imin;
  double ratio = ((double)irange)/range;

  if (*ipos < imin) *ipos = imin;
  if (*ipos > (imax - ipage)) *ipos = imax - ipage;

  *pos = min + ((double)(*ipos-imin))/ratio;
}

char *iupCanvasGetPosXAttrib( struct libData *data, Ihandle *ih )
{
  return iupStrReturnDouble(ih->data->posx );
}

char *iupCanvasGetPosYAttrib( struct libData *data, Ihandle *ih )
{
  return iupStrReturnDouble(ih->data->posy );
}

static char *iCanvasGetScrollbarAttrib( struct libData *data, Ihandle *ih )
{
  if ( ! ih->handle)
    return NULL; /* get from the hash table */

  if (ih->data->sb & IUP_SB_HORIZ && ih->data->sb & IUP_SB_VERT)
    return "YES";
  else if (ih->data->sb & IUP_SB_HORIZ)
    return "HORIZONTAL";
  else if (ih->data->sb & IUP_SB_VERT)
    return "VERTICAL";
  else
    return "NO";
}

static int iCanvasCreateMethod( struct libData *data, Ihandle *ih, void** params)
{
  if (params && params[0] )
  {
    char *action = (char*)params[0];
    iupAttribSetStr( data, ih, "ACTION", action );
  }

  ih->data = iupALLOCCTRLDATA();

  /* default EXPAND is YES */
  ih->expand = IUP_EXPAND_BOTH;
  
  return IUP_NOERROR;
}

static void iCanvasComputeNaturalSizeMethod( struct libData *data, Ihandle *ih, int *w, int *h, int *children_expand)
{
  int natural_w = 0, natural_h = 0;
  (void)children_expand; /* unset if not a container */

  /* canvas natural size is 1 character */
  iupdrvFontGetCharSize( data, ih, &natural_w, &natural_h );

  *w = natural_w;
  *h = natural_h;
}


/******************************************************************************/

IUP_API Ihandle *amy_IupCanvas( struct libData *data, const char *action )
{
  void *params[2];
  params[0] = (void*)action;
  params[1] = NULL;
  return amy_IupCreatev( data, "canvas", params );
}

Iclass *iupCanvasNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, NULL );

  ic->name = "canvas";
  ic->format = "a"; /* one ACTION callback name */
  ic->nativetype = IUP_TYPECANVAS;
  ic->childtype = IUP_CHILDNONE;
  ic->is_interactive = 1;

  /* Class functions */
  ic->New = iupCanvasNewClass;
  ic->Create = iCanvasCreateMethod;
  ic->ComputeNaturalSize = iCanvasComputeNaturalSizeMethod;

  ic->LayoutUpdate = iupdrvBaseLayoutUpdateMethod;
  ic->UnMap = iupdrvBaseUnMapMethod;

  /* Callbacks */
  iupClassRegisterCallback( data, ic, "RESIZE_CB", "ii" );
  iupClassRegisterCallback( data, ic, "FOCUS_CB", "i" );
  iupClassRegisterCallback( data, ic, "WOM_CB", "i" );
  iupClassRegisterCallback( data, ic, "BUTTON_CB", "iiiis" );
  iupClassRegisterCallback( data, ic, "MOTION_CB", "iis" );
  iupClassRegisterCallback( data, ic, "KEYPRESS_CB", "ii" );
  iupClassRegisterCallback( data, ic, "ACTION", "ff" );
  iupClassRegisterCallback( data, ic, "SCROLL_CB", "iff" );
  iupClassRegisterCallback( data, ic, "WHEEL_CB", "fiis" );

  /* Common Callbacks */
  iupBaseRegisterCommonCallbacks( data, ic );

  /* Common */
  iupBaseRegisterCommonAttrib( data, ic );

  /* Change the default to YES */
  iupClassRegisterReplaceAttribDef( data, ic, "EXPAND", IUPAF_SAMEASSYSTEM, "YES" );

  /* Visual */
  iupBaseRegisterVisualAttrib( data, ic );

  /* Drag&Drop */
  iupdrvRegisterDragDropAttrib( data, ic );

  /* amy_IupCanvas only */
  iupClassRegisterAttribute( data, ic, "CURSOR", NULL, iupdrvBaseSetCursorAttrib, IUPAF_SAMEASSYSTEM, "ARROW", IUPAF_IHANDLENAME|IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "XMIN", NULL, NULL, IUPAF_SAMEASSYSTEM, "0", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "XMAX", NULL, NULL, IUPAF_SAMEASSYSTEM, "1", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "YMIN", NULL, NULL, IUPAF_SAMEASSYSTEM, "0", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "YMAX", NULL, NULL, IUPAF_SAMEASSYSTEM, "1", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "LINEX", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "LINEY", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "SCROLLBAR", iCanvasGetScrollbarAttrib, NULL, NULL, NULL, IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "YAUTOHIDE", NULL, NULL, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "XAUTOHIDE", NULL, NULL, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "XHIDDEN", NULL, NULL, NULL, NULL, IUPAF_READONLY | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "YHIDDEN", NULL, NULL, NULL, NULL, IUPAF_READONLY | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "SB_RESIZE", NULL, NULL, NULL, NULL, IUPAF_READONLY | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "WHEELDROPFOCUS", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "BORDER", NULL, NULL, IUPAF_SAMEASSYSTEM, "YES", IUPAF_DEFAULT );

  iupClassRegisterAttribute( data, ic, "DRAWFONT", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DRAWCOLOR", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DRAWSTYLE", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DRAWTEXTALIGNMENT", NULL, NULL, IUPAF_SAMEASSYSTEM, "ALEFT", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DRAWTEXTWRAP", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DRAWTEXTELLIPSIS", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DRAWTEXTCLIP", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DRAWTEXTORIENTATION", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DRAWTEXTLAYOUTCENTER", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DRAWLINEWIDTH", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DRAWBGCOLOR", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );  /* used only for images */
  iupClassRegisterAttribute( data, ic, "DRAWMAKEINACTIVE", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );  /* used only for images */
  iupClassRegisterAttribute( data, ic, "DRAWDRIVER", NULL, NULL, NULL, NULL, IUPAF_READONLY | IUPAF_NO_INHERIT );
  
  iupdrvCanvasInitClass( data, ic );

  return ic;
}

