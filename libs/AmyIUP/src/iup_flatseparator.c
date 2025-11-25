
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
 * \brief Separator Control
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdarg.h>

#include "iup.h"
#include "iupcbs.h"

#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_drv.h"
#include "iup_drvfont.h"
#include "iup_image.h"
#include "iup_stdcontrols.h"
#include "iup_register.h"
#include "iup_drvdraw.h"
#include "iup_draw.h"
#include "iup_key.h"

#endif

enum { ISEPARATOR_VERT, ISEPARATOR_HORIZ };
enum { ISEPARATOR_FILL, ISEPARATOR_LINE, ISEPARATOR_SUNKENLINE, ISEPARATOR_DUALLINES, ISEPARATOR_GRIP, ISEPARATOR_EMPTY };

struct _IcontrolData
{
  iupCanvas canvas;  /* from amy_IupCanvas (must reserve it) */

  int orientation, 
      barsize, 
      style;
};

/****************************************************************/

static long iDrawGetDarkerColor(long color)
{
  unsigned char r = iupDrawRed(color), g = iupDrawGreen(color), b = iupDrawBlue(color), a = iupDrawAlpha( color );
  r = (r * 80) / 100;
  g = (g * 80) / 100;
  b = (b * 80) / 100;
  return iupDrawColor(r, g, b, a );
}

static int iFlatSeparatorRedraw_CB( struct libData *data, Ihandle *ih )
{
  IdrawCanvas* dc = iupdrvDrawCreateCanvas( data, ih );

  iupDrawParentBackground( data, dc, ih );

  if (ih->data->style != ISEPARATOR_FILL && ih->data->style != ISEPARATOR_EMPTY)
  {
    int x, y, w, h;
    long color = iupDrawStrToColor( data, iupAttribGetStr( data, ih, "COLOR" ), iupDrawColor(160, 160, 160, 255));

    iupdrvDrawGetSize( data, dc, &w, &h );

    if (ih->data->style == ISEPARATOR_GRIP)
    {
      int i, count;
      long sunken_color;
      if ( iupDrawRed(color) + iupDrawGreen(color) + iupDrawBlue(color) > 3 * 190)
        sunken_color = iupDrawColor(100, 100, 100, 255 );
      else
        sunken_color = iupDrawColor(255, 255, 255, 255 );

      if (ih->data->orientation == ISEPARATOR_VERT)
      {
        x = w / 2 - 1;
        y = 2;
        count = (h - 2) / ih->data->barsize;
      }
      else
      {
        x = 2;
        y = h / 2 - 1;
        count = (w - 2) / ih->data->barsize;
      }

      for (i = 0; i < count; i++)
      {
        iupdrvDrawRectangle( data, dc, x + 1, y + 1, x + 2, y + 2, sunken_color, IUP_DRAW_FILL, 1 );
        iupdrvDrawRectangle( data, dc, x, y, x + 1, y + 1, color, IUP_DRAW_FILL, 1 );

        if (ih->data->orientation == ISEPARATOR_VERT)
          y += ih->data->barsize;
        else
          x += ih->data->barsize;
      }
    }
    else if (ih->data->style == ISEPARATOR_DUALLINES)
    {
      if (ih->data->orientation == ISEPARATOR_VERT)
      {
        x = w / 2;

        iupdrvDrawLine( data, dc, x - 1, 0, x - 1, h - 1, color, IUP_DRAW_STROKE, 1 );
        iupdrvDrawLine( data, dc, x + 1, 0, x + 1, h - 1, color, IUP_DRAW_STROKE, 1 );
      }
      else
      {
        y = h / 2;

        iupdrvDrawLine( data, dc, 0, y - 1, w - 1, y - 1, color, IUP_DRAW_STROKE, 1 );
        iupdrvDrawLine( data, dc, 0, y + 1, w - 1, y + 1, color, IUP_DRAW_STROKE, 1 );
      }
    }
    else if (ih->data->style == ISEPARATOR_SUNKENLINE)
    {
      long sunken_color;
      if ( iupDrawRed(color) + iupDrawGreen(color) + iupDrawBlue(color) > 3 * 190)
        sunken_color = iupDrawColor(100, 100, 100, 255 );
      else
        sunken_color = iupDrawColor(255, 255, 255, 255 );

      if (ih->data->orientation == ISEPARATOR_VERT)
      {
        x = w / 2;

        iupdrvDrawLine( data, dc, x, 0, x, h - 1, color, IUP_DRAW_STROKE, 1 );
        iupdrvDrawLine( data, dc, x + 1, 0, x + 1, h - 1, sunken_color, IUP_DRAW_STROKE, 1 );
      }
      else
      {
        y = h / 2;

        iupdrvDrawLine( data, dc, 0, y, w - 1, y, color, IUP_DRAW_STROKE, 1 );
        iupdrvDrawLine( data, dc, 0, y + 1, w - 1, y + 1, sunken_color, IUP_DRAW_STROKE, 1 );
      }
    }
    else /* ISEPARATOR_LINE */
    {
      if (ih->data->orientation == ISEPARATOR_VERT)
      {
        x = w / 2;

        iupdrvDrawLine( data, dc, x, 0, x, h - 1, color, IUP_DRAW_STROKE, 1 );
      }
      else
      {
        y = h / 2;

        iupdrvDrawLine( data, dc, 0, y, w - 1, y, color, IUP_DRAW_STROKE, 1 );
      }
    }
  }
  else if (ih->data->style == ISEPARATOR_FILL)
  {
    int w, h;
    long color = iupDrawStrToColor( data, iupAttribGetStr( data, ih, "COLOR" ), iupDrawColor(160, 160, 160, 255));
    long border_color = iDrawGetDarkerColor(color );

    iupdrvDrawGetSize( data, dc, &w, &h );

    iupdrvDrawRectangle( data, dc, 1, 1, w - 2, h - 2, color, IUP_DRAW_FILL, 1 );
    iupdrvDrawRectangle( data, dc, 0, 0, w - 1, h - 1, border_color, IUP_DRAW_STROKE, 1 );
  }

  iupdrvDrawFlush( data, dc );

  iupdrvDrawKillCanvas( data, dc );

  return IUP_DEFAULT;
}


/***********************************************************************************************/


static int iFlatSeparatorSetOrientationAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if (iupStrEqualNoCase(value, "HORIZONTAL" ))
  {
    ih->data->orientation = ISEPARATOR_HORIZ;
    ih->expand = IUP_EXPAND_WFREE;
  }
  else  /* Default = VERTICAL */
  {
    ih->data->orientation = ISEPARATOR_VERT;
    ih->expand = IUP_EXPAND_HFREE;
  }

  return 0;  /* do not store value in hash table */
}

static char *iFlatSeparatorGetOrientationAttrib( struct libData *data, Ihandle *ih )
{
  const char *orientation_str[] = { "VERTICAL", "HORIZONTAL" };
  return (char*)orientation_str[ih->data->orientation];
}

static char *iFlatSeparatorGetStyleAttrib( struct libData *data, Ihandle *ih )
{
  const char *style_str[] = { "FILL", "LINE", "SUNKENLINE", "DUALLINES", "GRIP", "EMPTY" };
  return (char*)style_str[ih->data->style];
}

static int iFlatSeparatorSetStyleAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if (iupStrEqualNoCase(value, "FILL" ))
    ih->data->style = ISEPARATOR_FILL;
  else if (iupStrEqualNoCase(value, "LINE" ))
    ih->data->style = ISEPARATOR_LINE;
  else if (iupStrEqualNoCase(value, "DUALLINES" ))
    ih->data->style = ISEPARATOR_DUALLINES;
  else if (iupStrEqualNoCase(value, "EMPTY" ))
    ih->data->style = ISEPARATOR_EMPTY;
  else if (iupStrEqualNoCase(value, "GRIP" ))
    ih->data->style = ISEPARATOR_GRIP;
  else
    ih->data->style = ISEPARATOR_SUNKENLINE;
  amy_IupUpdate( data, ih );
  return 0; /* do not store value in hash table */
}

static int iFlatSeparatorSetBarSizeAttrib( struct libData *data, Ihandle *ih, const char *value)
{
	iupStrToInt(value, &ih->data->barsize );
	amy_IupUpdate( data, ih );
	return 0; /* do not store value in hash table */
}

static char *iFlatSeparatorGetBarSizeAttrib( struct libData *data, Ihandle *ih )
{
	return amy_iupStrReturnInt( data, ih->data->barsize );
}


/*****************************************************************************************/


static int iFlatSeparatorCreateMethod( struct libData *data, Ihandle *ih, void** params)
{
  (void)params;

  /* free the data allocated by amy_IupCanvas */
  free(ih->data );
  ih->data = iupALLOCCTRLDATA();

  ih->data->barsize = 5;
  ih->data->style = ISEPARATOR_SUNKENLINE;
  ih->data->orientation = ISEPARATOR_VERT;
  ih->expand = IUP_EXPAND_HFREE;

  /* change the amy_IupCanvas default values */
  iupAttribSet( data, ih, "BORDER", "NO" );
  iupAttribSet( data, ih, "CANFOCUS", "NO" );

  /* internal callbacks */
  amy_IupSetCallback( data, ih, "ACTION", (Icallback)iFlatSeparatorRedraw_CB );

  return IUP_NOERROR;
}

static void iFlatSeparatorComputeNaturalSizeMethod( struct libData *data, Ihandle *ih, int *w, int *h, int *children_expand)
{
  int natural_w = 0,
      natural_h = 0;

  if (ih->data->orientation == ISEPARATOR_HORIZ)
    natural_h = ih->data->barsize;
  else 
    natural_w = ih->data->barsize;

  *w = natural_w;
  *h = natural_h;

  (void)children_expand; /* unset if not a container */
}


/******************************************************************************/


Iclass *iupFlatSeparatorNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, iupRegisterFindClass( data, "canvas" ));

  ic->name = "flatseparator";
  ic->cons = "FlatSeparator";
  ic->format = NULL;  /* no parameters */
  ic->nativetype = IUP_TYPECANVAS;
  ic->childtype = IUP_CHILDNONE;
  ic->is_interactive = 0;

  /* Class functions */
  ic->New = iupFlatSeparatorNewClass;
  ic->Create = iFlatSeparatorCreateMethod;
  ic->ComputeNaturalSize = iFlatSeparatorComputeNaturalSizeMethod;

  iupClassRegisterAttribute( data, ic, "ORIENTATION", iFlatSeparatorGetOrientationAttrib, iFlatSeparatorSetOrientationAttrib, IUPAF_SAMEASSYSTEM, "VERTICAL", IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "STYLE", iFlatSeparatorGetStyleAttrib, iFlatSeparatorSetStyleAttrib, IUPAF_SAMEASSYSTEM, "SUNKENLINE", IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "COLOR", NULL, NULL, IUPAF_SAMEASSYSTEM, "160, 160, 160", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "BARSIZE", iFlatSeparatorGetBarSizeAttrib, iFlatSeparatorSetBarSizeAttrib, IUPAF_SAMEASSYSTEM, "5", IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );

  return ic;
}

IUP_API Ihandle *amy_IupFlatSeparator( struct libData *data )
{
  return amy_IupCreate( data, "flatseparator" );
}
