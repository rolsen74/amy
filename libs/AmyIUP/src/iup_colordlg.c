
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
 * \brief amy_IupColorDlg pre-defined dialog control
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iup.h"
#include "iupcbs.h"
#include "iupkey.h"
#include "iupcontrols.h"

#include "iupdraw.h"
#include "iup_drvdraw.h"
#include "iup_draw.h"

#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_strmessage.h"
#include "iup_drv.h"
#include "iup_stdcontrols.h"
#include "iup_register.h"
#include "iup_image.h"
#include "iup_colorhsi.h"
#include "iup_childtree.h"

#endif

#define COLORTABLE_MAX 20

static const char *default_colortable_cells[COLORTABLE_MAX] =
{
  "0 0 0", "64 64 64", "128 128 128", "144 144 144", "0 128 128", "128 0 128", "128 128 0", "128 0 0", "0 128 0", "0 0 128",
  "255 255 255", "240 240 240", "224 224 224", "192 192 192", "0 255 255", "255 0 255", "255 255 0", "255 0 0", "0 255 0", "0 0 255"
};

typedef struct _IcolorDlgData
{
  int status;

  long previous_color, 
       color; /* same as (red,green,blue,alpha) */

  double hue, saturation, intensity;
  unsigned char red, green, blue, alpha;

  Ihandle *red_txt, *green_txt, *blue_txt, *alpha_txt;
  Ihandle *hue_txt, *intensity_txt, *saturation_txt;
  Ihandle *color_browser, *color_cnv, *colorhex_txt;
  Ihandle *colortable_cbar, *alpha_val;
  Ihandle *help_bt;
} IcolorDlgData;


static void iColorDlgHSI2RGB( struct libData *data, IcolorDlgData *colordlg_data )
{
  iupColorHSI2RGB( colordlg_data->hue, colordlg_data->saturation, colordlg_data->intensity,
                  &colordlg_data->red, &colordlg_data->green, &colordlg_data->blue);
}

static void iColorDlgRGB2HSI( struct libData *data, IcolorDlgData *colordlg_data )
{
  iupColorRGB2HSI( colordlg_data->red, colordlg_data->green, colordlg_data->blue,
                  &( colordlg_data->hue), &( colordlg_data->saturation), &( colordlg_data->intensity));
}

static void iColorDlgHex_TXT_Update( struct libData *data, IcolorDlgData *colordlg_data)
{
  amy_IupSetfAttribute( data, colordlg_data->colorhex_txt, "VALUE", "#%02X%02X%02X", (int)colordlg_data->red, (int)colordlg_data->green, (int)colordlg_data->blue);
}

/*************************************************\
* Updates text fields with the current HSI values *
\*************************************************/
static void iColorDlgHSI_TXT_Update( struct libData *data, IcolorDlgData *colordlg_data)
{
  amy_IupSetInt( data, colordlg_data->hue_txt, "VALUE", iupROUND( colordlg_data->hue));
  amy_IupSetInt( data, colordlg_data->saturation_txt, "VALUE", iupRound( data, colordlg_data->saturation * 100));
  amy_IupSetInt( data, colordlg_data->intensity_txt, "VALUE", iupRound( data, colordlg_data->intensity * 100));
}

/*************************************************\
* Updates text fields with the current RGB values *
\*************************************************/
static void iColorDlgRGB_TXT_Update( struct libData *data, IcolorDlgData *colordlg_data)
{
  amy_IupSetInt( data, colordlg_data->red_txt, "VALUE", (int) colordlg_data->red);
  amy_IupSetInt( data, colordlg_data->green_txt, "VALUE", (int) colordlg_data->green);
  amy_IupSetInt( data, colordlg_data->blue_txt, "VALUE", (int) colordlg_data->blue);
}

static void iColorDlgBrowserRGB_Update( struct libData *data, IcolorDlgData *colordlg_data)
{
  amy_IupSetfAttribute( data, colordlg_data->color_browser, "RGB", "%d %d %d", colordlg_data->red, colordlg_data->green, colordlg_data->blue);
}

static void iColorDlgBrowserHSI_Update( struct libData *data, IcolorDlgData *colordlg_data)
{
  amy_IupSetfAttribute( data, colordlg_data->color_browser, "HSI", IUP_DOUBLE2STR" "IUP_DOUBLE2STR" "IUP_DOUBLE2STR, colordlg_data->hue, colordlg_data->saturation, colordlg_data->intensity);
}

/*****************************************\
* Sets the RGB color in the Color Canvas *
\*****************************************/
static void iColorDlgColor_Update( struct libData *data, IcolorDlgData *colordlg_data)
{
  colordlg_data->color = iupDrawColor( colordlg_data->red, colordlg_data->green, colordlg_data->blue, colordlg_data->alpha);
  amy_IupUpdate( data, colordlg_data->color_cnv);

  {
    Ihandle *ih = amy_IupGetDialog( data, colordlg_data->color_browser);
    Icallback cb = amy_IupGetCallback( data, ih, "COLORUPDATE_CB" );
    if (cb) cb( data,ih );
  }
}

static void iColorDlgHSIChanged( struct libData *data, IcolorDlgData *colordlg_data) 
{
  iColorDlgHSI2RGB( data, colordlg_data);
  iColorDlgBrowserHSI_Update( data, colordlg_data);
  iColorDlgHex_TXT_Update( data, colordlg_data);
  iColorDlgRGB_TXT_Update( data, colordlg_data);
  iColorDlgColor_Update( data, colordlg_data);
}

static void iColorDlgRGBChanged( struct libData *data, IcolorDlgData *colordlg_data) 
{
  iColorDlgRGB2HSI( data, colordlg_data);
  iColorDlgBrowserRGB_Update( data, colordlg_data);
  iColorDlgHex_TXT_Update( data, colordlg_data);
  iColorDlgHSI_TXT_Update( data, colordlg_data);
  iColorDlgColor_Update( data, colordlg_data);
}

/***********************************************\
* Initializes the default values to the element *
\***********************************************/
static void iColorDlgInit_Defaults( struct libData *data, IcolorDlgData *colordlg_data)
{
  Ihandle *box;
  int i;

  amy_IupSetAttribute( data, colordlg_data->color_browser, "RGB", "0 0 0" );

  amy_IupSetAttribute( data, colordlg_data->red_txt,   "VALUE", "0" );
  amy_IupSetAttribute( data, colordlg_data->green_txt, "VALUE", "0" );
  amy_IupSetAttribute( data, colordlg_data->blue_txt,  "VALUE", "0" );

  amy_IupSetAttribute( data, colordlg_data->hue_txt,        "VALUE", "0" );
  amy_IupSetAttribute( data, colordlg_data->saturation_txt, "VALUE", "0" );
  amy_IupSetAttribute( data, colordlg_data->intensity_txt,  "VALUE", "0" );
  
  amy_IupSetAttribute( data, colordlg_data->colorhex_txt, "VALUE", "#000000" );

  colordlg_data->alpha = 255;
  amy_IupSetAttribute( data, colordlg_data->alpha_val, "VALUE", "255" );
  amy_IupSetAttribute( data, colordlg_data->alpha_txt, "VALUE", "255" );

  box = amy_IupGetParent( data, colordlg_data->alpha_val);
  amy_IupSetAttribute( data, box, "FLOATING", "YES" );
  amy_IupSetAttribute( data, box, "VISIBLE", "NO" );

  box = amy_IupGetParent( data, colordlg_data->colortable_cbar);
  amy_IupSetAttribute( data, box, "FLOATING", "YES" );
  amy_IupSetAttribute( data, box, "VISIBLE", "NO" );

  box = amy_IupGetParent( data, colordlg_data->colorhex_txt);
  amy_IupSetAttribute( data, box, "FLOATING", "YES" );
  amy_IupSetAttribute( data, box, "VISIBLE", "NO" );

  for (i = 0; i < COLORTABLE_MAX; i++)
    amy_IupSetAttributeId( data, colordlg_data->colortable_cbar, "CELL", i, default_colortable_cells[i]);
}


/**************************************************************************************************************/
/*                                 Internal Callbacks                                                         */
/**************************************************************************************************************/


static int iColorDlgButtonOK_CB( struct libData *data, Ihandle *ih )
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
  colordlg_data->status = 1;
  return IUP_CLOSE;
}

static int iColorDlgButtonCancel_CB( struct libData *data, Ihandle *ih )
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
  colordlg_data->status = 0;
  return IUP_CLOSE;
}

static int iColorDlgButtonHelp_CB( struct libData *data, Ihandle *ih )
{
  Icallback cb = amy_IupGetCallback( data, amy_IupGetDialog( data, ih ), "HELP_CB" );
  if (cb && cb( data,ih ) == IUP_CLOSE)
  {
    IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
    colordlg_data->status = 0;
    return IUP_CLOSE;
  }
  return IUP_DEFAULT;
}

static void iColorDrawTransparentRectangle( struct libData *data, Ihandle *color_cnv, int xmin, int ymin, int xmax, int ymax, long color)
{
  if (iupDrawAlpha( color) == 255)
  {
    iupDrawSetColor( data, color_cnv, "DRAWCOLOR", color);
    amy_IupDrawRectangle( data, color_cnv, xmin, ymin, xmax, ymax);
  }
  else
  {
    int w = xmax - xmin + 1;
    int h = ymax - ymin + 1;
    Ihandle *image = amy_IupImageRGBA( data, w,h,NULL);
    unsigned char *colors = (unsigned char*) iupAttribGet( data, image, "WID" );
    int x, y;
    unsigned char red = iupDrawRed(color);
    unsigned char green = iupDrawGreen(color);
    unsigned char blue = iupDrawBlue(color);
    unsigned char alpha = iupDrawAlpha( color);

    for (y = 0; y < h; y++)
    {
      for (x = 0; x < w; x++)
      {
        colors[0] = red;
        colors[1] = green;
        colors[2] = blue;
        colors[3] = alpha;

        colors += 4;
      }
    }

    iupAttribSetHandleName( data, image );
    amy_IupDrawImage( data, color_cnv, iupAttribGetHandleName( data, image ), xmin, ymin, -1, -1);

    amy_IupDestroy( data, image );
  }
}

static int iColorDlgColorCnvAction_CB( struct libData *data, Ihandle *color_cnv)
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, color_cnv, "_IUP_GC_DATA" );

  int x, y, w, h, width, height, box_size = 10;

  amy_IupDrawBegin( data, color_cnv);

  amy_IupDrawGetSize( data, color_cnv, &width, &height);

  iupDrawSetColor( data, color_cnv, "DRAWCOLOR", iupDrawColor(255, 255, 255, 255));
  iupAttribSet( data, color_cnv, "DRAWSTYLE", "FILL" );
  amy_IupDrawRectangle( data, color_cnv, 0, 0, width - 1, height - 1);

  w = (width + box_size - 1) / box_size;
  h = (height + box_size - 1) / box_size;

  iupDrawSetColor( data, color_cnv, "DRAWCOLOR", iupDrawColor(192, 192, 192, 255));

  for (y = 0; y < h; y++)
  {
    for (x = 0; x < w; x++)
    {
      if (((x % 2) && (y % 2)) || (((x + 1) % 2) && ((y + 1) % 2)))
      {
        int xmin = x*box_size;
        int xmax = xmin + box_size;
        int ymin = y*box_size;
        int ymax = ymin + box_size;

        amy_IupDrawRectangle( data, color_cnv, xmin, ymin, xmax, ymax);
      }
    }
  }

  iColorDrawTransparentRectangle( data, color_cnv, 0, 0, width / 2, height - 1, colordlg_data->previous_color);

  iColorDrawTransparentRectangle( data, color_cnv, width / 2 + 1, 0, width - 1, height - 1, colordlg_data->color);

  amy_IupDrawEnd( data, color_cnv );

  return IUP_DEFAULT;
}

static int iColorDlgRedAction_CB( struct libData *data, Ihandle *ih, int c, char *value) 
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
  int vi;

  if (iupStrToInt(value, &vi))
  {
    colordlg_data->red = (unsigned char)vi;
    iColorDlgRGBChanged( data, colordlg_data);
  }

  (void)c;
  return IUP_DEFAULT;
}

static int iColorDlgRedSpin_CB( struct libData *data, Ihandle *ih, int vi) 
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );

  colordlg_data->red = (unsigned char)vi;
  iColorDlgRGBChanged( data, colordlg_data);

  return IUP_DEFAULT;
}

static int iColorDlgGreenAction_CB( struct libData *data, Ihandle *ih, int c, char *value) 
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
  int vi;

  if (iupStrToInt(value, &vi))
  {
    colordlg_data->green = (unsigned char)vi;
    iColorDlgRGBChanged( data, colordlg_data);
  }

  (void)c;
  return IUP_DEFAULT;
}

static int iColorDlgGreenSpin_CB( struct libData *data, Ihandle *ih, int vi) 
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );

  colordlg_data->green = (unsigned char)vi;
  iColorDlgRGBChanged( data, colordlg_data);

  return IUP_DEFAULT;
}

static int iColorDlgBlueAction_CB( struct libData *data, Ihandle *ih, int c, char *value) 
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
  int vi;

  if (iupStrToInt(value, &vi))
  {
    colordlg_data->blue = (unsigned char)vi;
    iColorDlgRGBChanged( data, colordlg_data);
  }

  (void)c;
  return IUP_DEFAULT;
}

static int iColorDlgBlueSpin_CB( struct libData *data, Ihandle *ih, int vi) 
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );

  colordlg_data->blue = (unsigned char)vi;
  iColorDlgRGBChanged( data, colordlg_data);

  return IUP_DEFAULT;
}

static int iColorDlgHueAction_CB( struct libData *data, Ihandle *ih, int c, char *value) 
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
  int vi;

  if (iupStrToInt(value, &vi))
  {
    colordlg_data->hue = (double)vi;
    iColorDlgHSIChanged( data, colordlg_data);
  }

  (void)c;
  return IUP_DEFAULT;
}

static int iColorDlgHueSpin_CB( struct libData *data, Ihandle *ih, int vi) 
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );

  colordlg_data->hue = (double)vi;
  iColorDlgHSIChanged( data, colordlg_data);

  return IUP_DEFAULT;
}

static int iColorDlgSaturationAction_CB( struct libData *data, Ihandle *ih, int c, char *value) 
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
  int vi;

  if (iupStrToInt(value, &vi))
  {
    colordlg_data->saturation = (double)vi/100.0;
    iColorDlgHSIChanged( data, colordlg_data);
  }

  (void)c;
  return IUP_DEFAULT;
}

static int iColorDlgSaturationSpin_CB( struct libData *data, Ihandle *ih, int vi) 
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );

  colordlg_data->saturation = (double)vi/100.0;
  iColorDlgHSIChanged( data, colordlg_data);

  return IUP_DEFAULT;
}

static int iColorDlgIntensityAction_CB( struct libData *data, Ihandle *ih, int c, char *value) 
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
  int vi;

  if (iupStrToInt(value, &vi))
  {
    colordlg_data->intensity = (double)vi/100.0;
    iColorDlgHSIChanged( data, colordlg_data);
  }

  (void)c;
  return IUP_DEFAULT;
}

static int iColorDlgIntensitySpin_CB( struct libData *data, Ihandle *ih, int vi) 
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );

  colordlg_data->intensity = (double)vi/100.0;
  iColorDlgHSIChanged( data, colordlg_data);

  return IUP_DEFAULT;
}

static int iColorDlgHexAction_CB( struct libData *data, Ihandle *ih, int c, char *value) 
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );

  if (iupStrToRGB(value, &( colordlg_data->red), &( colordlg_data->green), &( colordlg_data->blue)))
  {
    iColorDlgRGB2HSI( data, colordlg_data);
    iColorDlgBrowserRGB_Update( data, colordlg_data);
    iColorDlgHSI_TXT_Update( data, colordlg_data);
    iColorDlgRGB_TXT_Update( data, colordlg_data);
    iColorDlgColor_Update( data, colordlg_data);
  }

  (void)c;
  return IUP_DEFAULT;
}

static int iColorDlgColorSelDrag_CB( struct libData *data, Ihandle *ih, unsigned char r, unsigned char g, unsigned char b)
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );

  colordlg_data->red   = r;
  colordlg_data->green = g;
  colordlg_data->blue  = b;

  iColorDlgRGB2HSI( data, colordlg_data);
  iColorDlgHex_TXT_Update( data, colordlg_data);
  iColorDlgHSI_TXT_Update( data, colordlg_data);
  iColorDlgRGB_TXT_Update( data, colordlg_data);

  iColorDlgColor_Update( data, colordlg_data);

  return IUP_DEFAULT;
}

static int iColorDlgAlphaVal_CB( struct libData *data, Ihandle *ih, double val)
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );

  colordlg_data->alpha = (unsigned char)val;
  amy_IupSetInt( data, colordlg_data->alpha_txt, "VALUE", (int)colordlg_data->alpha);

  iColorDlgColor_Update( data, colordlg_data);

  return IUP_DEFAULT;  
}

static int iColorDlgAlphaAction_CB( struct libData *data, Ihandle *ih, int c, char *value) 
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
  int vi;

  if (iupStrToInt(value, &vi))
  {
    colordlg_data->alpha = (unsigned char)vi;
    amy_IupSetInt( data, colordlg_data->alpha_val, "VALUE", (int)colordlg_data->alpha);

    iColorDlgColor_Update( data, colordlg_data);
  }

  (void)c;
  return IUP_DEFAULT;
}

static int iColorDlgAlphaSpin_CB( struct libData *data, Ihandle *ih, int vi) 
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );

  colordlg_data->alpha = (unsigned char)vi;
  amy_IupSetInt( data, colordlg_data->alpha_val, "VALUE", (int)colordlg_data->alpha);

  iColorDlgColor_Update( data, colordlg_data);

  return IUP_DEFAULT;
}

static int iColorDlgColorTableSelect_CB( struct libData *data, Ihandle *ih, int cell, int type)
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );

  iupStrToRGB( amy_IupGetAttributeId( data, ih, "CELL", cell), &colordlg_data->red, &colordlg_data->green, &colordlg_data->blue);

  iColorDlgRGB_TXT_Update( data, colordlg_data);
  iColorDlgRGBChanged( data, colordlg_data);

  (void)type;
  return IUP_DEFAULT;
}

static int iColorDlgColorCnvButton_CB( struct libData *data, Ihandle *ih, int b, int press, int x, int y)
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
  int width;
  (void)y;

  if (b != IUP_BUTTON1 || !press)
    return IUP_DEFAULT;

  width = colordlg_data->color_cnv->currentwidth;

  if (x < width/2)
  {
    /* reset color to previous */
    colordlg_data->red = iupDrawRed( colordlg_data->previous_color);
    colordlg_data->green = iupDrawGreen( colordlg_data->previous_color);
    colordlg_data->blue = iupDrawBlue( colordlg_data->previous_color);
    colordlg_data->alpha = iupDrawAlpha( colordlg_data->previous_color);

    amy_IupSetInt( data, colordlg_data->alpha_txt, "VALUE", (int)colordlg_data->alpha);
    amy_IupSetInt( data, colordlg_data->alpha_val, "VALUE", (int)colordlg_data->alpha);

    iColorDlgRGB_TXT_Update( data, colordlg_data);
    iColorDlgRGBChanged( data, colordlg_data);
  }

  return IUP_DEFAULT;
}


/**************************************************************************************************************/
/*                                     Attributes                                                             */
/**************************************************************************************************************/


static char *iColorDlgGetStatusAttrib( struct libData *data, Ihandle *ih )
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
  if ( colordlg_data->status) 
    return "1";
  else 
    return NULL;
}

static int iColorDlgSetShowHelpAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
  amy_IupSetAttribute( data, colordlg_data->help_bt, "VISIBLE", iupStrBoolean(value)? "YES": "NO" );
  return 1;
}

static int iColorDlgSetShowHexAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );

  /* valid only before map */
  if (ih->handle)
    return 1;

  if (iupStrBoolean(value))
  {
    Ihandle *box = amy_IupGetParent( data, colordlg_data->colorhex_txt);
    amy_IupSetAttribute( data, box, "FLOATING", NULL);
    amy_IupSetAttribute( data, box, "VISIBLE", "YES" );
  }

  return 1;
}

static int iColorDlgSetShowColorTableAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );

  /* valid only before map */
  if (ih->handle)
    return 1;

  if (iupStrBoolean(value))
  {
    Ihandle *box = amy_IupGetParent( data, colordlg_data->colortable_cbar);
    amy_IupSetAttribute( data, box, "FLOATING", NULL);
    amy_IupSetAttribute( data, box, "VISIBLE", "YES" );
  }

  return 1;
}

static int iColorDlgSetShowAlphaAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );

  /* valid only before map */
  if (ih->handle)
    return 1;

  if (iupStrBoolean(value))
  {
    Ihandle *box = amy_IupGetParent( data, colordlg_data->alpha_val);
    amy_IupSetAttribute( data, box, "FLOATING", NULL);
    amy_IupSetAttribute( data, box, "VISIBLE", "YES" );
  }

  return 1;
}

static int iColorDlgSetAlphaAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
  int alpha;
  if (iupStrToInt(value, &alpha))
  {
    colordlg_data->alpha = (unsigned char)alpha;
    amy_IupSetInt( data, colordlg_data->alpha_txt, "VALUE", (int)colordlg_data->alpha);
    amy_IupSetInt( data, colordlg_data->alpha_val, "VALUE", (int)colordlg_data->alpha);

    colordlg_data->previous_color = iupDrawColor( iupDrawRed( colordlg_data->previous_color), iupDrawGreen( colordlg_data->previous_color), iupDrawBlue( colordlg_data->previous_color), colordlg_data->alpha);

    iColorDlgColor_Update( data, colordlg_data);

    if ( ! ih->handle)  /* do it only before map */
      amy_IupSetAttribute( data, ih, "SHOWALPHA", "YES" );
  }
 
  return 1;
}

static char *iColorDlgGetAlphaAttrib( struct libData *data, Ihandle *ih )
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
  return amy_iupStrReturnInt( data, (int)colordlg_data->alpha );
}

static int iStrToRGBA(const char *str, unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *a)
{
  unsigned int ri = 0, gi = 0, bi = 0, ai = 0, ret;
  if ( ! str) return 0;
  if (str[0]=='#')
  {
    str++;
    ret = sscanf(str, "%2X%2X%2X%2X", &ri, &gi, &bi, &ai);
  }
  else
    ret = sscanf(str, "%u %u %u %u", &ri, &gi, &bi, &ai);

  if (ret < 3) return 0;
  if (ri > 255 || gi > 255 || bi > 255 || ai > 255) return 0;
  *r = (unsigned char)ri;
  *g = (unsigned char)gi;
  *b = (unsigned char)bi;
  if (ret == 4)
  {
    *a = (unsigned char)ai;
    return 4;
  }
  else
    return 3;
}

static int iColorDlgSetValueAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
  int ret = iStrToRGBA(value, &colordlg_data->red, &colordlg_data->green, &colordlg_data->blue, &colordlg_data->alpha);
  if ( ! ret)
    return 0;
  
  colordlg_data->previous_color = iupDrawColor( colordlg_data->red, colordlg_data->green, colordlg_data->blue, colordlg_data->alpha);

  if (ret == 4)
  {
    amy_IupSetInt( data, colordlg_data->alpha_txt, "VALUE", (int)colordlg_data->alpha);
    amy_IupSetInt( data, colordlg_data->alpha_val, "VALUE", (int)colordlg_data->alpha);

    if ( ! ih->handle)  /* do it only before map */
      amy_IupSetAttribute( data, ih, "SHOWALPHA", "YES" );
  }

  iColorDlgRGB_TXT_Update( data, colordlg_data);
  iColorDlgRGBChanged( data, colordlg_data);

  return 0;
}

static char *iColorDlgGetValueAttrib( struct libData *data, Ihandle *ih )
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
  if (iupAttribGetBoolean( data, ih, "SHOWALPHA" ))
    return iupStrReturnStrf("%d %d %d %d", (int)colordlg_data->red, (int)colordlg_data->green, (int)colordlg_data->blue, (int)colordlg_data->alpha);
  else
    return iupStrReturnRGB( colordlg_data->red, colordlg_data->green, colordlg_data->blue);
}

static int iupStrToHSI_Int(const char *str, int *h, int *s, int *i)
{
  int fh, fs, fi;
  if ( ! str) return 0;
  if (sscanf(str, "%d %d %d", &fh, &fs, &fi) != 3) return 0;
  if (fh > 359 || fs > 100 || fi > 100) return 0;
  if (fh < 0 || fs < 0 || fi < 0) return 0;
  *h = fh;
  *s = fs;
  *i = fi;
  return 1;
}

static int iColorDlgSetValueHSIAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
  int hue, saturation, intensity;

  if ( ! iupStrToHSI_Int(value, &hue, &saturation, &intensity))
    return 0;
  
  colordlg_data->hue = (double)hue;
  colordlg_data->saturation = (double)saturation/100.0;
  colordlg_data->intensity = (double)intensity/100.0;

  iColorDlgHSI2RGB( data, colordlg_data);
  colordlg_data->previous_color = iupDrawColor( colordlg_data->red, colordlg_data->green, colordlg_data->blue, colordlg_data->alpha);
 
  iColorDlgHSIChanged( data, colordlg_data);
  return 0;
}

static char *iColorDlgGetValueHSIAttrib( struct libData *data, Ihandle *ih )
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
  return iupStrReturnStrf("%d %d %d",(int)colordlg_data->hue, (int)( data, colordlg_data->saturation*100), (int)( data, colordlg_data->intensity*100));
}

static int iColorDlgSetValueHexAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );

  if ( ! iupStrToRGB(value, &( colordlg_data->red), &( colordlg_data->green), &( colordlg_data->blue)))
    return 0;

  colordlg_data->previous_color = iupDrawColor( colordlg_data->red, colordlg_data->green, colordlg_data->blue, colordlg_data->alpha);

  iColorDlgRGB2HSI( data, colordlg_data);
  iColorDlgBrowserRGB_Update( data, colordlg_data);
  iColorDlgHSI_TXT_Update( data, colordlg_data);
  iColorDlgRGB_TXT_Update( data, colordlg_data);
  iColorDlgColor_Update( data, colordlg_data);
  return 0;
}

static char *iColorDlgGetValueHexAttrib( struct libData *data, Ihandle *ih )
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
  return iupStrReturnStrf("#%02X%02X%02X", (int)colordlg_data->red, (int)colordlg_data->green, (int)colordlg_data->blue);
}

static char *iColorDlgGetColorTableAttrib( struct libData *data, Ihandle *ih )
{
  int i, inc, off = 0;
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
  char *color_str;
  char *str = iupStrGetMemory(COLORTABLE_MAX * 3 * 20);
  for (i = 0; i < COLORTABLE_MAX; i++)
  {
    color_str = amy_IupGetAttributeId( data, colordlg_data->colortable_cbar, "CELL", i);
    inc = (int)strlen(color_str);
    memcpy(str+off, color_str, inc);
    memcpy(str+off+inc, ";", 1);
    off += inc+1;
  }
  str[off-1] = 0; /* remove last separator */
  return str;
}

static int iColorDlgSetColorTableAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  int i = 0;
  unsigned char r, g, b;
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );

  if ( ! ih->handle)    /* do it only before map */
    iColorDlgSetShowColorTableAttrib( data, ih, "YES" );

  while (value && *value && i < COLORTABLE_MAX)
  {
    if (iupStrToRGB(value, &r, &g, &b))
      amy_IupSetRGBId( data, colordlg_data->colortable_cbar, "CELL", i, r, g, b);

    value = strchr(value, ';');
    if (value) value++;
    i++;
  }

  return 1;
}


/**************************************************************************************************************/
/*                                     Methods                                                                */
/**************************************************************************************************************/

static int iColorDlgMapMethod( struct libData *data, Ihandle *ih )
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );

  if ( ! amy_IupGetCallback( data, ih, "HELP_CB" ))
    amy_IupSetAttribute( data, colordlg_data->help_bt, "VISIBLE", "NO" );

  return IUP_NOERROR;
}

static void iColorDlgDestroyMethod( struct libData *data, Ihandle *ih )
{
  IcolorDlgData* colordlg_data = (IcolorDlgData*) iupAttribGetInherit( data, ih, "_IUP_GC_DATA" );
  free( colordlg_data );
}

static int iColorDlgCreateMethod( struct libData *data, Ihandle *ih, void** params)
{
  Ihandle *ok_bt, *cancel_bt;
  Ihandle *rgb_vb, *hsi_vb, *clr_vb;
  Ihandle *lin1, *lin2, *col1, *col2;

  IcolorDlgData* colordlg_data = (IcolorDlgData*)malloc(sizeof(IcolorDlgData));
  memset( colordlg_data, 0, sizeof(IcolorDlgData));
  iupAttribSet( data, ih, "_IUP_GC_DATA", (char*)colordlg_data);

  /* ======================================================================= */
  /* BUTTONS   ============================================================= */
  /* ======================================================================= */
  ok_bt = amy_IupButton( data, "_@IUP_OK", NULL);                      /* Ok Button */
  amy_IupSetStrAttribute( data, ok_bt, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
  amy_IupSetCallback( data, ok_bt, "ACTION", (Icallback)iColorDlgButtonOK_CB);
  amy_IupSetAttributeHandle( data, ih, "DEFAULTENTER", ok_bt);

  cancel_bt = amy_IupButton( data, "_@IUP_CANCEL", NULL);          /* Cancel Button */
  amy_IupSetStrAttribute( data, cancel_bt, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
  amy_IupSetCallback( data, cancel_bt, "ACTION", (Icallback)iColorDlgButtonCancel_CB);
  amy_IupSetAttributeHandle( data, ih, "DEFAULTESC", cancel_bt);

  colordlg_data->help_bt = amy_IupButton( data, "_@IUP_HELP", NULL);            /* Help Button */
  amy_IupSetStrAttribute( data, colordlg_data->help_bt, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
  amy_IupSetCallback( data, colordlg_data->help_bt, "ACTION", (Icallback)iColorDlgButtonHelp_CB);

  /* ======================================================================= */
  /* COLOR   =============================================================== */
  /* ======================================================================= */
  colordlg_data->color_browser = amy_IupColorBrowser( data );
  amy_IupSetAttribute( data, colordlg_data->color_browser, "EXPAND", "YES" );  
  amy_IupSetCallback( data, colordlg_data->color_browser, "DRAG_CB",   (Icallback)iColorDlgColorSelDrag_CB);
  amy_IupSetCallback( data, colordlg_data->color_browser, "CHANGE_CB", (Icallback)iColorDlgColorSelDrag_CB);

  colordlg_data->color_cnv = amy_IupCanvas( data, NULL );  /* Canvas of the color */
  amy_IupSetAttribute( data, colordlg_data->color_cnv, "SIZE", "x12" );
  amy_IupSetAttribute( data, colordlg_data->color_cnv, "CANFOCUS", "NO" );
  amy_IupSetAttribute( data, colordlg_data->color_cnv, "EXPAND", "HORIZONTAL" );
  amy_IupSetCallback ( data, colordlg_data->color_cnv, "ACTION", (Icallback)iColorDlgColorCnvAction_CB);
  amy_IupSetCallback ( data, colordlg_data->color_cnv, "BUTTON_CB", (Icallback)iColorDlgColorCnvButton_CB);

  colordlg_data->colorhex_txt = amy_IupText( data, NULL );      /* Hex of the color */
  amy_IupSetAttribute( data, colordlg_data->colorhex_txt, "VISIBLECOLUMNS", "7" );
  amy_IupSetCallback ( data, colordlg_data->colorhex_txt, "ACTION", (Icallback)iColorDlgHexAction_CB);
  amy_IupSetAttribute( data, colordlg_data->colorhex_txt, "MASK", "#[0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F]" );

  /* ======================================================================= */
  /* ALPHA TRANSPARENCY   ================================================== */
  /* ======================================================================= */
  colordlg_data->alpha_val = amy_IupVal( data, "HORIZONTAL" );
  amy_IupSetAttribute( data, colordlg_data->alpha_val, "EXPAND", "HORIZONTAL" );
  amy_IupSetAttribute( data, colordlg_data->alpha_val, "MIN", "0" );
  amy_IupSetAttribute( data, colordlg_data->alpha_val, "MAX", "255" );
  amy_IupSetAttribute( data, colordlg_data->alpha_val, "VALUE", "255" );
  amy_IupSetAttribute( data, colordlg_data->alpha_val, "SIZE", "80x12" );
  amy_IupSetCallback ( data, colordlg_data->alpha_val, "MOUSEMOVE_CB", (Icallback)iColorDlgAlphaVal_CB);
  amy_IupSetCallback ( data, colordlg_data->alpha_val, "BUTTON_PRESS_CB", (Icallback)iColorDlgAlphaVal_CB);
  amy_IupSetCallback ( data, colordlg_data->alpha_val, "BUTTON_RELEASE_CB", (Icallback)iColorDlgAlphaVal_CB);

  colordlg_data->alpha_txt = amy_IupText( data, NULL );                        /* Alpha value */
  amy_IupSetAttribute( data, colordlg_data->alpha_txt, "VISIBLECOLUMNS", "3" );
  amy_IupSetAttribute( data, colordlg_data->alpha_txt, "SPIN", "YES" );
  amy_IupSetAttribute( data, colordlg_data->alpha_txt, "SPINMIN", "0" );
  amy_IupSetAttribute( data, colordlg_data->alpha_txt, "SPINMAX", "255" );
  amy_IupSetAttribute( data, colordlg_data->alpha_txt, "SPININC", "1" );
  amy_IupSetCallback ( data, colordlg_data->alpha_txt, "ACTION", (Icallback)iColorDlgAlphaAction_CB);
  amy_IupSetCallback ( data, colordlg_data->alpha_txt, "SPIN_CB", (Icallback)iColorDlgAlphaSpin_CB);
  amy_IupSetAttribute( data, colordlg_data->alpha_txt, "MASKINT", "0:255" );

  /* ======================================================================= */
  /* COLOR TABLE   ========================================================= */
  /* ======================================================================= */
  colordlg_data->colortable_cbar = amy_IupColorbar( data );
  amy_IupSetAttribute( data, colordlg_data->colortable_cbar, "ORIENTATION", "HORIZONTAL" );
  amy_IupSetAttribute( data, colordlg_data->colortable_cbar, "NUM_PARTS", "2" );  
  amy_IupSetInt( data, colordlg_data->colortable_cbar, "NUM_CELLS", COLORTABLE_MAX);
  amy_IupSetAttribute( data, colordlg_data->colortable_cbar, "SHOW_PREVIEW", "NO" );
  amy_IupSetAttribute( data, colordlg_data->colortable_cbar, "SIZE", "138x22" );
  amy_IupSetAttribute( data, colordlg_data->colortable_cbar, "SQUARED", "NO" );
  amy_IupSetCallback ( data, colordlg_data->colortable_cbar, "SELECT_CB",   (Icallback)iColorDlgColorTableSelect_CB);

  /* ======================================================================= */
  /* RGB TEXT FIELDS   ===================================================== */
  /* ======================================================================= */
  colordlg_data->red_txt = amy_IupText( data, NULL );                            /* Red value */
  amy_IupSetAttribute( data, colordlg_data->red_txt, "VISIBLECOLUMNS", "3" );
  amy_IupSetAttribute( data, colordlg_data->red_txt, "SPIN", "YES" );
  amy_IupSetAttribute( data, colordlg_data->red_txt, "SPINMIN", "0" );
  amy_IupSetAttribute( data, colordlg_data->red_txt, "SPINMAX", "255" );
  amy_IupSetAttribute( data, colordlg_data->red_txt, "SPININC", "1" );
  amy_IupSetCallback ( data, colordlg_data->red_txt, "ACTION", (Icallback)iColorDlgRedAction_CB);
  amy_IupSetCallback ( data, colordlg_data->red_txt, "SPIN_CB", (Icallback)iColorDlgRedSpin_CB);
  amy_IupSetAttribute( data, colordlg_data->red_txt, "MASKINT", "0:255" );

  colordlg_data->green_txt = amy_IupText( data, NULL );                        /* Green value */
  amy_IupSetAttribute( data, colordlg_data->green_txt, "VISIBLECOLUMNS", "3" );
  amy_IupSetAttribute( data, colordlg_data->green_txt, "SPIN", "YES" );
  amy_IupSetAttribute( data, colordlg_data->green_txt, "SPINMIN", "0" );
  amy_IupSetAttribute( data, colordlg_data->green_txt, "SPINMAX", "255" );
  amy_IupSetAttribute( data, colordlg_data->green_txt, "SPININC", "1" );
  amy_IupSetCallback ( data, colordlg_data->green_txt, "ACTION", (Icallback)iColorDlgGreenAction_CB);
  amy_IupSetCallback ( data, colordlg_data->green_txt, "SPIN_CB", (Icallback)iColorDlgGreenSpin_CB);
  amy_IupSetAttribute( data, colordlg_data->green_txt, "MASKINT", "0:255" );

  colordlg_data->blue_txt = amy_IupText( data, NULL );                          /* Blue value */
  amy_IupSetAttribute( data, colordlg_data->blue_txt, "VISIBLECOLUMNS", "3" );
  amy_IupSetAttribute( data, colordlg_data->blue_txt, "SPIN", "YES" );
  amy_IupSetAttribute( data, colordlg_data->blue_txt, "SPINMIN", "0" );
  amy_IupSetAttribute( data, colordlg_data->blue_txt, "SPINMAX", "255" );
  amy_IupSetAttribute( data, colordlg_data->blue_txt, "SPININC", "1" );
  amy_IupSetCallback ( data, colordlg_data->blue_txt, "ACTION", (Icallback)iColorDlgBlueAction_CB);
  amy_IupSetCallback ( data, colordlg_data->blue_txt, "SPIN_CB", (Icallback)iColorDlgBlueSpin_CB);
  amy_IupSetAttribute( data, colordlg_data->blue_txt, "MASKINT", "0:255" );

  /* ======================================================================= */
  /* HSI TEXT FIELDS   ===================================================== */
  /* ======================================================================= */
  colordlg_data->hue_txt = amy_IupText( data, NULL );                            /* Hue value */
  amy_IupSetAttribute( data, colordlg_data->hue_txt, "VISIBLECOLUMNS", "3" );
  amy_IupSetAttribute( data, colordlg_data->hue_txt, "SPIN", "YES" );
  amy_IupSetAttribute( data, colordlg_data->hue_txt, "SPINMIN", "0" );
  amy_IupSetAttribute( data, colordlg_data->hue_txt, "SPINMAX", "359" );
  amy_IupSetAttribute( data, colordlg_data->hue_txt, "SPINWRAP", "YES" );
  amy_IupSetAttribute( data, colordlg_data->hue_txt, "SPININC", "1" );
  amy_IupSetCallback( data, colordlg_data->hue_txt, "ACTION", (Icallback)iColorDlgHueAction_CB);
  amy_IupSetCallback( data, colordlg_data->hue_txt, "SPIN_CB", (Icallback)iColorDlgHueSpin_CB);
  amy_IupSetAttribute( data, colordlg_data->hue_txt, "MASKINT", "0:359" );

  colordlg_data->saturation_txt = amy_IupText( data, NULL );              /* Saturation value */
  amy_IupSetAttribute( data, colordlg_data->saturation_txt, "VISIBLECOLUMNS", "3" );
  amy_IupSetAttribute( data, colordlg_data->saturation_txt, "SPIN", "YES" );
  amy_IupSetAttribute( data, colordlg_data->saturation_txt, "SPINMIN", "0" );
  amy_IupSetAttribute( data, colordlg_data->saturation_txt, "SPINMAX", "100" );
  amy_IupSetAttribute( data, colordlg_data->saturation_txt, "SPININC", "1" );
  amy_IupSetCallback( data, colordlg_data->saturation_txt, "ACTION", (Icallback)iColorDlgSaturationAction_CB);
  amy_IupSetCallback( data, colordlg_data->saturation_txt, "SPIN_CB", (Icallback)iColorDlgSaturationSpin_CB);
  amy_IupSetAttribute( data, colordlg_data->saturation_txt, "MASKINT", "0:100" );

  colordlg_data->intensity_txt = amy_IupText( data, NULL );                /* Intensity value */
  amy_IupSetAttribute( data, colordlg_data->intensity_txt, "VISIBLECOLUMNS", "3" );
  amy_IupSetAttribute( data, colordlg_data->intensity_txt, "SPIN", "YES" );
  amy_IupSetAttribute( data, colordlg_data->intensity_txt, "SPINMIN", "0" );
  amy_IupSetAttribute( data, colordlg_data->intensity_txt, "SPINMAX", "100" );
  amy_IupSetAttribute( data, colordlg_data->intensity_txt, "SPININC", "1" );
  amy_IupSetCallback( data, colordlg_data->intensity_txt, "ACTION", (Icallback)iColorDlgIntensityAction_CB);
  amy_IupSetCallback( data, colordlg_data->intensity_txt, "SPIN_CB", (Icallback)iColorDlgIntensitySpin_CB);
  amy_IupSetAttribute( data, colordlg_data->intensity_txt, "MASKINT", "0:100" );

  /* =================== */
  /* 1st line = Controls */
  /* =================== */

  col1 = amy_IupVbox( data, colordlg_data->color_browser, amy_IupSetAttributes( data, amy_IupHbox( data, colordlg_data->color_cnv, NULL), "MARGIN=30x0" ),NULL);

  hsi_vb = amy_IupVbox( data, amy_IupSetAttributes( data, amy_IupHbox( data, amy_IupLabel( data, "_@IUP_HUE" ), 
                                            colordlg_data->hue_txt, 
                                            NULL), "ALIGNMENT=ACENTER" ),
                   amy_IupSetAttributes( data, amy_IupHbox( data, amy_IupLabel( data, "_@IUP_SATURATION" ), 
                                            colordlg_data->saturation_txt, 
                                            NULL), "ALIGNMENT=ACENTER" ),
                   amy_IupSetAttributes( data, amy_IupHbox( data, amy_IupLabel( data, "_@IUP_INTENSITY" ), 
                                            colordlg_data->intensity_txt, 
                                            NULL), "ALIGNMENT=ACENTER" ),
                   NULL);
  amy_IupSetAttribute( data, hsi_vb, "GAP", "5" );
  
  rgb_vb = amy_IupVbox( data, amy_IupSetAttributes( data, amy_IupHbox( data, amy_IupLabel( data, "_@IUP_RED" ), 
                                            colordlg_data->red_txt, 
                                            NULL), "ALIGNMENT=ACENTER" ),
                   amy_IupSetAttributes( data, amy_IupHbox( data, amy_IupLabel( data, "_@IUP_GREEN" ), 
                                            colordlg_data->green_txt, 
                                            NULL), "ALIGNMENT=ACENTER" ),
                   amy_IupSetAttributes( data, amy_IupHbox( data, amy_IupLabel( data, "_@IUP_BLUE" ), 
                                            colordlg_data->blue_txt, 
                                            NULL), "ALIGNMENT=ACENTER" ),
                   NULL);
  amy_IupSetAttribute( data, rgb_vb, "GAP", "5" );
  
  clr_vb = amy_IupVbox( data, amy_IupSetAttributes( data, amy_IupHbox( data, amy_IupLabel( data, "_@IUP_OPACITY" ), 
                                            colordlg_data->alpha_txt, colordlg_data->alpha_val, 
                                            NULL), "ALIGNMENT=ACENTER" ),
                   amy_IupSetAttributes( data, amy_IupHbox( data, amy_IupLabel( data, "He&xa:" ), 
                                            colordlg_data->colorhex_txt, 
                                            NULL), "ALIGNMENT=ACENTER" ),
                   amy_IupSetAttributes( data, amy_IupVbox( data, amy_IupLabel( data, "_@IUP_PALETTE" ), 
                                            colordlg_data->colortable_cbar,
                                            NULL), "GAP=3" ),
                   NULL);
  amy_IupSetAttribute( data, clr_vb, "GAP", "5" );
  amy_IupSetAttribute( data, clr_vb, "EXPAND", "YES" );

  amy_IupDestroy( data, amy_IupSetAttributes( data, amy_IupNormalizer( data, amy_IupGetChild( data, amy_IupGetChild( data, hsi_vb, 0), 0),  /* Hue Label */
                                            amy_IupGetChild( data, amy_IupGetChild( data, hsi_vb, 1), 0),  /* Saturation Label */
                                            amy_IupGetChild( data, amy_IupGetChild( data, hsi_vb, 2), 0),  /* Intensity Label */
                                            amy_IupGetChild( data, amy_IupGetChild( data, clr_vb, 0), 0),  /* Opacity Label */
                                            amy_IupGetChild( data, amy_IupGetChild( data, clr_vb, 1), 0),  /* Hexa Label */
                                            NULL), "NORMALIZE=HORIZONTAL" ));

  amy_IupDestroy( data, amy_IupSetAttributes( data, amy_IupNormalizer( data, amy_IupGetChild( data, amy_IupGetChild( data, rgb_vb, 0), 0),  /* Red Label */
                                            amy_IupGetChild( data, amy_IupGetChild( data, rgb_vb, 1), 0),  /* Green Label */
                                            amy_IupGetChild( data, amy_IupGetChild( data, rgb_vb, 2), 0),  /* Blue Label */
                                            NULL), "NORMALIZE=HORIZONTAL" ));

  col2 = amy_IupVbox( data, amy_IupSetAttributes( data, amy_IupHbox( data, hsi_vb, amy_IupFill( data ), rgb_vb, NULL), "EXPAND=YES" ), 
                 amy_IupSetAttributes( data, amy_IupLabel( data, NULL ), "SEPARATOR=HORIZONTAL" ), 
                 clr_vb,
                 NULL);
  amy_IupSetAttributes( data, col2, "EXPAND=NO, GAP=10" );

  lin1 = amy_IupHbox( data, col1, col2, NULL);
  amy_IupSetAttribute( data, lin1, "GAP", "10" );
  amy_IupSetAttribute( data, lin1, "MARGIN", "0x0" );

  /* ================== */
  /* 2nd line = Buttons */
  /* ================== */

  lin2 = amy_IupHbox( data, amy_IupFill( data ), ok_bt, cancel_bt, colordlg_data->help_bt, NULL);
  amy_IupSetAttribute( data, lin2, "GAP", "5" );
  amy_IupSetAttribute( data, lin2, "MARGIN", "0x0" );
  amy_IupSetAttribute( data, lin2, "NORMALIZESIZE", "HORIZONTAL" );

  /* Do not use amy_IupAppend because we set childtype=IUP_CHILDNONE */
  iupChildTreeAppend( data, ih, amy_IupSetAttributes( data, amy_IupVbox( data, lin1, amy_IupSetAttributes( data, amy_IupLabel( data, NULL ), "SEPARATOR=HORIZONTAL" ), lin2, NULL), "MARGIN=10x10, GAP=10" ));

  amy_IupRefresh( data, ih );

  if ( colordlg_data->color_browser->currentwidth < colordlg_data->color_browser->currentheight)
  {
    amy_IupSetStrf( data, colordlg_data->color_browser, "RASTERSIZE", "%dx%d", colordlg_data->color_browser->currentheight, colordlg_data->color_browser->currentheight);
    amy_IupSetAttribute( data, ih, "RASTERSIZE", NULL);
  }

  iColorDlgInit_Defaults( data, colordlg_data);

  (void)params;
  return IUP_NOERROR;
}

Iclass *iupColorDlgNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, iupRegisterFindClass( data, "dialog" ));

  ic->New = iupColorDlgNewClass;
  ic->Create = iColorDlgCreateMethod;
  ic->Destroy = iColorDlgDestroyMethod;
  ic->Map = iColorDlgMapMethod;

  ic->name = "colordlg";
  ic->cons = "ColorDlg";
  ic->nativetype = IUP_TYPEDIALOG;
  ic->is_interactive = 1;
  ic->childtype = IUP_CHILDNONE;

  iupClassRegisterCallback( data, ic, "COLORUPDATE_CB", "" );

  iupClassRegisterAttribute( data, ic, "COLORTABLE", iColorDlgGetColorTableAttrib, iColorDlgSetColorTableAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT);
  iupClassRegisterAttribute( data, ic, "STATUS", iColorDlgGetStatusAttrib, NULL, NULL, NULL, IUPAF_READONLY|IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT);
  iupClassRegisterAttribute( data, ic, "VALUE", iColorDlgGetValueAttrib, iColorDlgSetValueAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT);
  iupClassRegisterAttribute( data, ic, "ALPHA", iColorDlgGetAlphaAttrib, iColorDlgSetAlphaAttrib, IUPAF_SAMEASSYSTEM, "255", IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT);
  iupClassRegisterAttribute( data, ic, "VALUEHSI", iColorDlgGetValueHSIAttrib, iColorDlgSetValueHSIAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT);
  iupClassRegisterAttribute( data, ic, "VALUEHEX", iColorDlgGetValueHexAttrib, iColorDlgSetValueHexAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT);
  iupClassRegisterAttribute( data, ic, "SHOWALPHA", NULL, iColorDlgSetShowAlphaAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT);
  iupClassRegisterAttribute( data, ic, "SHOWCOLORTABLE", NULL, iColorDlgSetShowColorTableAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT);
  iupClassRegisterAttribute( data, ic, "SHOWHEX", NULL, iColorDlgSetShowHexAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT);
  iupClassRegisterAttribute( data, ic, "SHOWHELP", NULL, iColorDlgSetShowHelpAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT);

  return ic;
}

IUP_API Ihandle *amy_IupColorDlg( struct libData *data )
{
  return amy_IupCreate( data, "colordlg" );
}
