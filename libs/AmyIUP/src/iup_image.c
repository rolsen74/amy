
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
 * \brief Image Resource.
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include "iup.h"

#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_image.h"
#include "iup_assert.h"
#include "iup_stdcontrols.h"
#include "iup_drvinfo.h"
#include "iup_array.h"

#endif

static void iDataResizeRGBA( struct libData *data, int src_width, int src_height, unsigned char *src_map, int dst_width, int dst_height, unsigned char *dst_map, int depth )
{
  /* Do bilinear interpolation */

  unsigned char *line_mapl, *line_maph;
  double t, u, src_x, src_y, factor;
  int xl, yl, xh, yh, x, y;
  unsigned char *fhh, *fll, *fhl, *flh;

  int *XL = (int*)malloc(dst_width * sizeof(int));
  double *T = (double*)malloc(dst_width * sizeof(double));

  factor = (double)src_width / (double)dst_width;
  for (x = 0; x < dst_width; x++)
  {
    src_x = x * factor;
    xl = (int)(src_x );
    T[x] = src_x - xl;
    XL[x] = xl;
  }

  factor = (double)src_height / (double)dst_height;

  for (y = 0; y < dst_height; y++)
  {
    src_y = y * factor;
    yl = (int)(src_y );
    yh = (yl == src_height - 1) ? yl : yl + 1;
    u = src_y - yl;

    line_mapl = src_map + yl * src_width * depth;
    line_maph = src_map + yh * src_width * depth;

    for (x = 0; x < dst_width; x++)
    {
      xl = XL[x];
      xh = (xl == src_width - 1) ? xl : xl + 1;
      t = T[x];

      fll = line_mapl + xl * depth;
      fhl = line_mapl + xh * depth;
      flh = line_maph + xl * depth;
      fhh = line_maph + xh * depth;

      dst_map[0] = (unsigned char)(u * t * (fhh[0] - flh[0] - fhl[0] + fll[0] ) + t * (fhl[0] - fll[0] ) + u * (flh[0] - fll[0] ) + fll[0] );
      dst_map[1] = (unsigned char)(u * t * (fhh[1] - flh[1] - fhl[1] + fll[1] ) + t * (fhl[1] - fll[1] ) + u * (flh[1] - fll[1] ) + fll[1] );
      dst_map[2] = (unsigned char)(u * t * (fhh[2] - flh[2] - fhl[2] + fll[2] ) + t * (fhl[2] - fll[2] ) + u * (flh[2] - fll[2] ) + fll[2] );
      if (depth == 4)
        dst_map[3] = (unsigned char)(u * t * (fhh[3] - flh[3] - fhl[3] + fll[3] ) + t * (fhl[3] - fll[3] ) + u * (flh[3] - fll[3] ) + fll[3] );

      dst_map += depth;
    }
  }

  free(XL );
  free(T );
}

static void iDataStretchMap( struct libData *data, int src_width, int src_height, unsigned char *src_map, int dst_width, int dst_height, unsigned char *dst_map )
{
  int x, y, offset;
  double factor;
  unsigned char *line_map;
  int* XTab = (int*)malloc(dst_width*sizeof(int));

  /* initialize conversion tables to speed up the stretch process */
  factor = (double)(src_width - 1) / (double)(dst_width - 1 );
  for (x = 0; x < dst_width; x++)
    XTab[x] = (int)(factor * x + 0.5 );

  factor = (double)(src_height - 1) / (double)(dst_height - 1 );

  line_map = src_map;

  for (y = 0; y < dst_height; y++)
  {
    for (x = 0; x < dst_width; x++)
    {
      offset = XTab[x];
      *(dst_map++) = line_map[offset];
    }

    offset = ((int)(factor * y + 0.5)) * src_width;
    line_map = src_map + offset;
  }

  free(XTab );
}

static void iImageResize( struct libData *data, Ihandle *ih, int new_width, int new_height)
{
  unsigned char *imgdata = (unsigned char*) iupAttribGet( data, ih, "WID" );
  int channels = iupAttribGetInt( data, ih, "CHANNELS" );
  int bpp = iupAttribGetInt( data, ih, "BPP" );
  int count = new_width*new_height*channels;
  unsigned char *new_imgdata = (unsigned char *)malloc(count );

  if (bpp == 8)
    iDataStretchMap( data, ih->currentwidth, ih->currentheight, imgdata, new_width, new_height, new_imgdata );
  else
    iDataResizeRGBA( data, ih->currentwidth, ih->currentheight, imgdata, new_width, new_height, new_imgdata, channels );

  ih->currentwidth = new_width;
  ih->currentheight = new_height;

  free(imgdata );
  iupAttribSet( data, ih, "WID", (char*)new_imgdata );
}

/**************************************************************************************************/

typedef struct _IimageStock
{
	iupImageStockCreateFunc func;
	Ihandle *image;            /* cache image */
	const char *native_name;   /* used to map to GTK stock images */
	int can_resize;
} IimageStock;

#if 0

static Itable *data->istock_table = NULL;   /* the image hash table indexed by the name string */

#endif

void iupImageStockInit( struct libData *data )
{
	data->istock_table = iupTableCreate( data, IUPTABLE_STRINGINDEXED );

	amy_IupSetGlobal( data, "IMAGESTOCKAUTOSCALE", "Yes" );
}

void iupImageStockFinish( struct libData *data )
{
	char *name = iupTableFirst( data, data->istock_table );

	while (name)
	{
		IimageStock* istock = (IimageStock*) iupTableGetCurr( data, data->istock_table );
		if ( iupObjectCheck( data, istock->image ))
		amy_IupDestroy( data, istock->image );
		memset(istock, 0, sizeof(IimageStock));
		free(istock );
		name = iupTableNext( data, data->istock_table );
	}

	iupTableDestroy( data, data->istock_table );
	data->istock_table = NULL;
}

IUP_SDK_API void iupImageStockSet( struct libData *data, const char *name, iupImageStockCreateFunc func, const char *native_name )
{
	IimageStock* istock = (IimageStock*) iupTableGet( data, data->istock_table, name );
	if ( istock)
		free(istock );  /* overwrite a previous registration */

	istock = (IimageStock*)malloc(sizeof(IimageStock));
	istock->func = func;
	istock->image = NULL;
	istock->native_name = native_name;
	istock->can_resize = 1;

	if ( iupStrEqualNoCasePartial( name, "IUP_Logo" ) || iupStrEqualNoCasePartial( name, "IUP_Icon" ))
		istock->can_resize = 0;

	iupTableSet( data, data->istock_table, name, (void*)istock, IUPTABLE_POINTER );
}

IUP_SDK_API void iupImageStockSetNoResize( struct libData *data, const char *name, iupImageStockCreateFunc func, const char *native_name )
{
	IimageStock* istock = (IimageStock*) iupTableGet( data, data->istock_table, name );
	if ( istock)
		free(istock );  /* overwrite a previous registration */

	istock = (IimageStock*)malloc(sizeof(IimageStock));
	istock->func = func;
	istock->image = NULL;
	istock->native_name = native_name;
	istock->can_resize = 0;

	iupTableSet( data, data->istock_table, name, (void*)istock, IUPTABLE_POINTER );
}

int iupIsHighDpi( struct libData *data )
{
	int dpi = iupRound( data, iupdrvGetScreenDpi( data ));
	if (dpi > 144)
		return 1;
	else
		return 0;
}

int iupImageStockGetSize( struct libData *data )
{
	char *stock_size = amy_IupGetGlobal( data, "IMAGESTOCKSIZE" );
	if (stock_size)
	{
		int size = 16;
		iupStrToInt(stock_size, &size );

		/*  if (size <= 16)
		return 16; */
		if (size <= 24)
			return 24;
		if (size <= 32)
			return 32;
		return 48;
	}
	else
	{
		int dpi = iupRound( data, iupdrvGetScreenDpi( data ));
		/*  if (dpi <= 96)
		return 16; */
		if (dpi <= 144)
			return 24;
		if (dpi <= 192)
			return 32;
		return 48;
	}
}

void iupImageStockGet( struct libData *data, const char *name, Ihandle **ih, const char **native_name )
{
	IimageStock* istock = (IimageStock*) iupTableGet( data, data->istock_table, name );
	if ( istock)
	{
		if ( istock->image)
		*ih = istock->image;
		else if ( istock->native_name)
		*native_name = istock->native_name;
		else if ( istock->func)
		{
		int stock_size;
		int autoscale = amy_IupGetInt( data, NULL, "IMAGESTOCKAUTOSCALE" );

		istock->image = istock->func( data );

		*ih = istock->image;

		stock_size = iupImageStockGetSize( data );

		if (autoscale && istock->can_resize && istock->image->currentheight != stock_size)
		{
			int new_height = stock_size;
			int new_width = stock_size;
			if ( istock->image->currentwidth != istock->image->currentheight)
			new_width = (new_height * istock->image->currentwidth) / istock->image->currentheight; /* preserve height */

			iupAttribSet( data, istock->image, "SCALED", "Yes" );
			iupAttribSetStrf( data, istock->image, "ORIGINALSCALE", "%dx%d", istock->image->currentwidth, istock->image->currentheight );

			iImageResize( data, istock->image, new_width, new_height );
		}
		}
	}
}

static void iImageStockUnload( struct libData *data, const char *name )
{
	IimageStock* istock = (IimageStock*) iupTableGet( data, data->istock_table, name );
	if ( istock)
		istock->image = NULL;
}

static void iImageStockLoad( struct libData *data, const char *name )
{
	/* Used only in iupImageStockLoadAll */
	const char *native_name = NULL;
	Ihandle *ih = NULL;
	iupImageStockGet( data, name, &ih, &native_name );
	if ( ih)
	{
		amy_IupSetHandle( data, name, ih );
		iupAttribSetStr( data, ih, "_IUPIMAGE_STOCK_LOAD", name );
	}
	else if (native_name)
	{
		/* dummy image to save the GTK stock name */
		void *handle = iupdrvImageLoad( data, native_name, IUPIMAGE_IMAGE );

		if (handle)
			iupImageSetHandleFromLoaded( data, native_name, handle );  /* next time iupImageGetImageFromName will return the new handle */
	}
}

static int iImageStockExtended( struct libData *data, const char *name )
{
	int len = (int)strlen(name );
	if (len > 2 && iup_isdigit(name[len - 1] ) && iup_isdigit(name[len - 2] ))
		return 1;
	return 0;
}

IUP_SDK_API void iupImageStockLoadAll( struct libData *data )
{
	/* Used only in amy_IupView and amy_IupVisualLED */
	char *name = iupTableFirst( data, data->istock_table );
	while (name)
	{
		if ( ! iImageStockExtended( data, name ))
			iImageStockLoad( data, name );
		name = iupTableNext( data, data->istock_table );
	}
}

/**************************************************************************************************/

int iupImageNormBpp( struct libData *data, int bpp )
{
	if (bpp <= 8) return 8;
	if (bpp <= 24) return 24;
	return 32;
}

static void iupColorSet( struct libData *data, iupColor *c, unsigned char r, unsigned char g, unsigned char b, unsigned char a )
{
	c->r = r;
	c->g = g;
	c->b = b;
	c->a = a;
}

IUP_SDK_API int iupImageInitColorTable( struct libData *data, Ihandle *ih, iupColor* colors, int *colors_count)
{
  char *value;
  unsigned char red, green, blue;
  int i, has_alpha = 0;
  static iupColor default_colors[16] = {
    { 0, 0, 0, 255 }, { 128, 0, 0, 255 }, { 0, 128, 0, 255 }, { 128, 128, 0, 255 },
    { 0, 0, 128, 255 }, { 128, 0, 128, 255 }, { 0, 128, 128, 255 }, { 192, 192, 192, 255 },
    { 128, 128, 128, 255 }, { 255, 0, 0, 255 }, { 0, 255, 0, 255 }, { 255, 255, 0, 255 },
    { 0, 0, 255, 255 }, { 255, 0, 255, 255 }, { 0, 255, 255, 255 }, { 255, 255, 255, 255 } };

  memset(colors, 0, sizeof(iupColor)* 256 );

  for (i = 0; i < 16; i++)
  {
    value = iupAttribGetId( data, ih, "", i );

    if (value)
    {
      if ( iupStrEqual(value, "BGCOLOR" ))
      {
        iupColorSet( data, &colors[i], 0, 0, 0, 0 );
        has_alpha = 1;
      }
      else
      {
        if ( ! iupStrToRGB(value, &red, &green, &blue))
          iupColorSet( data, &colors[i], default_colors[i].r, default_colors[i].g, default_colors[i].b, 255 );
        else
          iupColorSet( data, &colors[i], red, green, blue, 255 );
      }
    }
    else
    {
      iupColorSet( data, &colors[i], default_colors[i].r, default_colors[i].g, default_colors[i].b, 255 );
    }
  }

  for (; i < 256; i++)
  {
    value = iupAttribGetId( data, ih, "", i );
    if ( ! value)
      break;

    if ( iupStrEqual(value, "BGCOLOR" ))
    {
      iupColorSet( data, &colors[i], 0, 0, 0, 0 );
      has_alpha = 1;
    }
    else
    {
      if ( ! iupStrToRGB(value, &red, &green, &blue))
        break;

      iupColorSet( data, &colors[i], red, green, blue, 255 );
    }
  }

  if (colors_count) *colors_count = i;

  return has_alpha;
}

void iupImageInitNonBgColors( struct libData *data, Ihandle *ih, unsigned char *colors )
{
  char *value;
  int i;

  memset(colors, 0, 256 );

  for (i = 0; i < 16; i++)
  {
    value = iupAttribGetId( data, ih, "", i );
    if ( ! iupStrEqual(value, "BGCOLOR" ))
      colors[i] = 1;
  }

  for (; i < 256; i++)
  {
    value = iupAttribGetId( data, ih, "", i );
    if ( ! value)
      break;

    if ( ! iupStrEqual(value, "BGCOLOR" ))
      colors[i] = 1;
  }
}

IUP_SDK_API void iupImageColorMakeInactive( unsigned char *r, unsigned char *g, unsigned char *b, unsigned char bg_r, unsigned char bg_g, unsigned char bg_b )
{
  if (*r != bg_r || *g != bg_g || *b != bg_b)  /* preserve colors identical to the background color */
  {
    int ir = 0, ig = 0, ib = 0,
      i = (*r + *g + *b) / 3,
      bg_i = (bg_r + bg_g + bg_b) / 3;

    if (bg_i)
    {
      ir = (bg_r*i) / bg_i;
      ig = (bg_g*i) / bg_i;
      ib = (bg_b*i) / bg_i;
    }

#define LIGHTER(_c) ((255 + _c)/2)
    ir = LIGHTER(ir );
    ig = LIGHTER(ig );
    ib = LIGHTER(ib );

    *r = iupBYTECROP(ir );
    *g = iupBYTECROP(ig );
    *b = iupBYTECROP(ib );
  }
}


/**************************************************************************************************/


void iupImageSetHandleFromLoaded( struct libData *data, const char *name, void *handle )
{
  int w, h, bpp;
  unsigned char *imgdata;
  Ihandle *ih;

  iupdrvImageGetInfo( data, handle, &w, &h, &bpp );

  if (bpp == 32)
    ih = amy_IupImageRGBA( data, w, h, NULL );
  else if (bpp > 8)
    ih = amy_IupImageRGB( data, w, h, NULL );
  else
    ih = amy_IupImage( data, w, h, NULL );

  imgdata = (unsigned char*) iupAttribGet( data, ih, "WID" );
  free(imgdata );
  iupAttribSet( data, ih, "WID", NULL );

  iupAttribSet( data, ih, "_IUPIMAGE_LOADED_HANDLE", (char*)handle );
  amy_IupSetHandle( data, name, ih );
}

Ihandle *iupImageGetImageFromName( struct libData *data, const char *name )
{
  Ihandle *ih = amy_IupGetHandle( data, name );
  if ( ih && !iupAttribGet( data, ih, "_IUPIMAGE_LOADED_HANDLE" ) && !iupAttribGet( data, ih, "_IUPIMAGE_LOADED_WD_HANDLE" ))
  {
    char *autoscale = iupAttribGet( data, ih, "AUTOSCALE" );
    if ( ! autoscale) autoscale = amy_IupGetGlobal( data, "IMAGEAUTOSCALE" );
    if (autoscale && !iupAttribGet( data, ih, "SCALED" ))
    {
      double scale = 0;

      if ( iupStrEqualNoCase(autoscale, "DPI" ))
      {
        int dpi = iupRound( data, iupdrvGetScreenDpi( data ));
        int image_dpi = amy_IupGetInt( data, ih, "DPI" );
        if ( image_dpi == 0) image_dpi = amy_IupGetInt( data, NULL, "IMAGESDPI" );
        if ( image_dpi == 0) image_dpi = 96;

        if (dpi <= 96)
          dpi = 96;
        else if (dpi <= 144)
          dpi = 144;
        else if (dpi <= 192)
          dpi = 192;
        else
          dpi = 288;

        scale = (double)dpi / (double)image_dpi;
      }
      else
        iupStrToDouble(  autoscale, &scale );

      if (scale > 0 && (scale < 0.99 || scale > 1.01))
      {
        char *hotspot = iupAttribGet( data, ih, "HOTSPOT" );

        int new_width = iupRound( data, scale*ih->currentwidth );
        int new_height = iupRound( data, scale*ih->currentheight );

        if (new_height < 24)
        {
          new_height = 24;
          new_width = (new_height * ih->currentwidth) / ih->currentheight;
        }

        if (new_width != ih->currentwidth || new_height != ih->currentheight)
        {
          iupAttribSet( data, ih, "SCALED", "Yes" );
          iupAttribSetStrf( data, ih, "ORIGINALSCALE", "%dx%d", ih->currentwidth, ih->currentheight );

          iImageResize( data, ih, new_width, new_height );

          if (hotspot)
          {
            int x = 0, y = 0;
            iupStrToIntInt(hotspot, &x, &y, ':' );

            x = iupRound( data, scale*x );
            y = iupRound( data, scale*y );

            iupAttribSetStrf( data, ih, "HOTSPOT", "%d:%d", x, y );
          }
        }
      }
    }
  }

  return ih;
}

void *iupImageGetIcon( struct libData *data, const char *name )
{
  void *icon;
  Ihandle *ih;

  if ( ! name)
    return NULL;

  ih = iupImageGetImageFromName( data, name );
  if ( ! ih)
  {
    const char *native_name = NULL;

    /* Check in the system resources. */
    icon = iupdrvImageLoad( data, name, IUPIMAGE_ICON );
    if ( icon)
      return icon;

    /* Check in the stock images. */
    iupImageStockGet( data, name, &ih, &native_name );
    if (native_name)
    {
      icon = iupdrvImageLoad( data, native_name, IUPIMAGE_ICON );
      if ( icon)
        return icon;
    }

    return NULL;
  }

  /* Check for an already created icon */
  icon = iupAttribGet( data, ih, "_IUPIMAGE_ICON" );
  if ( icon)
    return icon;

  /* Not created, tries to create the icon */
  icon = iupdrvImageCreateIcon( data, ih );

  /* save the icon */
  iupAttribSet( data, ih, "_IUPIMAGE_ICON", (char*)icon );

  return icon;
}

void *iupImageGetCursor( struct libData *data, const char *name )
{
  void *cursor;
  Ihandle *ih;

  if ( ! name)
    return NULL;

  ih = iupImageGetImageFromName( data, name );
  if ( ! ih)
  {
    /* Check in the system resources. */
    cursor = iupdrvImageLoad( data, name, IUPIMAGE_CURSOR );
    if (cursor)
      return cursor;

    return NULL;
  }

  /* Check for an already created cursor */
  cursor = iupAttribGet( data, ih, "_IUPIMAGE_CURSOR" );
  if (cursor)
    return cursor;

  /* Not created, tries to create the cursor */
  cursor = iupdrvImageCreateCursor( data, ih );

  /* save the cursor */
  iupAttribSet( data, ih, "_IUPIMAGE_CURSOR", (char*)cursor );

  return cursor;
}

void *iupImageGetImage( struct libData *data, const char *name, Ihandle *ih_parent, int make_inactive, const char *bgcolor )
{
  char cache_name[100] = "_IUPIMAGE_IMAGE";
  char *img_bgcolor;
  void *handle;
  Ihandle *ih;
  int bg_concat = 0;

  if ( ! name)
    return NULL;

  ih = iupImageGetImageFromName( data, name );
  if ( ! ih)
  {
    const char *native_name = NULL;

    /* Check in the system resources. */
    handle = iupdrvImageLoad( data, name, IUPIMAGE_IMAGE );
    if (handle)
    {
      iupImageSetHandleFromLoaded( data, name, handle );  /* next time iupImageGetImageFromName will return the new handle */
      return handle;
    }

    /* Check in the stock images. */
    iupImageStockGet( data, name, &ih, &native_name );
    if (native_name)
    {
      handle = iupdrvImageLoad( data, native_name, IUPIMAGE_IMAGE );
      if (handle)
      {
        iupImageSetHandleFromLoaded( data, name, handle );  /* next time iupImageGetImageFromName will return the new handle */
        return handle;
      }
    }

    if ( ! ih)
      return NULL;
  }

  handle = iupAttribGet( data, ih, "_IUPIMAGE_LOADED_HANDLE" );
  if (handle)
    return handle;

  img_bgcolor = iupAttribGet( data, ih, "BGCOLOR" );
  if ( ih_parent && !img_bgcolor)
  {
    if ( ! bgcolor)
      bgcolor = amy_IupGetAttribute( data, ih_parent, "BGCOLOR" ); /* Use amy_IupGetAttribute to use inheritance and native implementation */
  }
  else
    bgcolor = img_bgcolor;

  if (make_inactive)
    strcat(cache_name, "_INACTIVE" );

  if ( iupAttribGet( data, ih, "_IUP_BGCOLOR_DEPEND" ) && bgcolor)
  {
    strcat(cache_name, "(" );
    strcat(cache_name, bgcolor );
    strcat(cache_name, " )" );
    bg_concat = 1;
  }

  /* Check for an already created native image */
  handle = (void*) iupAttribGet( data, ih, cache_name );
  if (handle)
    return handle;

  if ( ih_parent && iupAttribGetStr( data, ih_parent, "FLAT_ALPHA" ))
    iupAttribSet( data, ih, "FLAT_ALPHA", "1" );

  /* Creates the native image */
  handle = iupdrvImageCreateImage( data, ih, bgcolor, make_inactive );

  if ( ih_parent && iupAttribGetStr( data, ih_parent, "FLAT_ALPHA" ))
    iupAttribSet( data, ih, "FLAT_ALPHA", NULL );

  if ( iupAttribGet( data, ih, "_IUP_BGCOLOR_DEPEND" ) && bgcolor && !bg_concat)  /* _IUP_BGCOLOR_DEPEND could be set during creation */
  {
    strcat(cache_name, "(" );
    strcat(cache_name, bgcolor );
    strcat(cache_name, " )" );
  }

  /* save the native image in the cache */
  iupAttribSet( data, ih, cache_name, (char*)handle );

  return handle;
}

void iupImageGetInfo( struct libData *data, const char *name, int *w, int *h, int *bpp )
{
  Ihandle *ih;

  if ( ! name)
    return;

  ih = iupImageGetImageFromName( data, name );
  if ( ! ih)
  {
    const char *native_name = NULL;
    void *handle;

    /* Check in the system resources. */
    handle = iupdrvImageLoad( data, name, IUPIMAGE_IMAGE );
    if (handle)
    {
      iupdrvImageGetInfo( data, handle, w, h, bpp );
      iupImageSetHandleFromLoaded( data, name, handle );  /* next time iupImageGetImageFromName will return the new handle */
      return;
    }

    /* Check in the stock images. */
    iupImageStockGet( data, name, &ih, &native_name );
    if (native_name)
    {
      handle = iupdrvImageLoad( data, native_name, IUPIMAGE_IMAGE );
      if (handle)
      {
        iupdrvImageGetInfo( data, handle, w, h, bpp );
        iupImageSetHandleFromLoaded( data, name, handle );  /* next time iupImageGetImageFromName will return the new handle */
        return;
      }
    }

    if ( ! ih)
      return;
  }

  if (w) *w = ih->currentwidth;
  if (h) *h = ih->currentheight;
  if (bpp) *bpp = amy_IupGetInt( data, ih, "BPP" );
}

static Ihandle *iImageGetHandleFromImage( struct libData *data, void *handle )
{
  int w, h, bpp;
  iupColor colors[256];
  int colors_count = 0;
  if ( iupdrvImageGetRawInfo( data, handle, &w, &h, &bpp, colors, &colors_count ))
  {
    Ihandle *ih;
    unsigned char *imgdata;

    if (bpp == 32)
      ih = amy_IupImageRGBA( data, w, h, NULL );
    else if (bpp > 8)
      ih = amy_IupImageRGB( data, w, h, NULL );
    else
      ih = amy_IupImage( data, w, h, NULL );

    if (bpp <= 8 && colors_count)
    {
	  int i;
      for (i = 0; i < colors_count; i++)
        amy_IupSetRGBId( data, ih, "", i, colors[i].r, colors[i].g, colors[i].b );
    }

    imgdata = (unsigned char*) iupAttribGet( data, ih, "WID" );
    iupdrvImageGetData( data, handle, imgdata );
	return ih;
  }

  return NULL;
}

IUP_API Ihandle *amy_IupImageGetHandle( struct libData *data, const char *name )
{
  /* Used in CD or OpenGL based controls where WID is mandatory - amy_IupMatrix, amy_IupGLControls and amy_IupPlot */
  Ihandle *ih;
  const char *native_name = NULL;
  void *handle;

  if ( ! name)
    return NULL;

  ih = iupImageGetImageFromName( data, name );
  if ( ih)
    return ih;

  /* Check in the system resources. */
  handle = iupdrvImageLoad( data, name, IUPIMAGE_IMAGE );
  if (handle)
  {
    /* the loaded image is converted and destroyed */

    ih = iImageGetHandleFromImage( data, handle );
    iupdrvImageDestroy( data, handle, IUPIMAGE_IMAGE );

    if ( ih)
    {
      amy_IupSetHandle( data, name, ih );
      return ih;
    }
  }

  /* Check in the stock images. */
  iupImageStockGet( data, name, &ih, &native_name );
  if ( ih)
  {
    amy_IupSetHandle( data, name, ih );
    return ih;
  }

  if (native_name)
  {
    handle = iupdrvImageLoad( data, native_name, IUPIMAGE_IMAGE );
    if (handle)
    {
      /* the loaded image is converted and destroyed */

      ih = iImageGetHandleFromImage( data, handle );
      iupdrvImageDestroy( data, handle, IUPIMAGE_IMAGE );

      if ( ih)
      {
        amy_IupSetHandle( data, name, ih );
        return ih;
      }
    }
  }

  return NULL;
}

void iupImageRemoveFromCache( struct libData *data, Ihandle *ih, void *handle)
{
  char *name;
  void *cur_handle;

  name = iupTableFirst( data, ih->attrib );
  while (name)
  {
    if ( iupStrEqualPartial( name, "_IUPIMAGE_" ))
    {
      cur_handle = iupTableGetCurr( data, ih->attrib );
      if (cur_handle == handle)
      {
        iupTableRemoveCurr( data, ih->attrib );
        return;
      }
    }

    name = iupTableNext( data, ih->attrib );
  }
}

static void iImageClearCache( struct libData *data, Ihandle *ih )
{
	// char *name;
	// void *handle;

	// handle = iupAttribGet( data, ih, "_IUPIMAGE_MASK" );
	// if (handle)
	// {
	// 	iupdrvImageDestroy( data, handle, IUPIMAGE_IMAGE );
	// 	iupAttribSet( data, ih, "_IUPIMAGE_MASK", NULL );
	// }

	// handle = iupAttribGet( data, ih, "_IUPIMAGE_ICON" );
	// if (handle)
	// {
	// 	iupdrvImageDestroy( data, handle, IUPIMAGE_ICON );
	// 	iupAttribSet( data, ih, "_IUPIMAGE_ICON", NULL );
	// }

	// handle = iupAttribGet( data, ih, "_IUPIMAGE_CURSOR" );
	// if (handle)
	// {
	// 	iupdrvImageDestroy( data, handle, IUPIMAGE_CURSOR );
	// 	iupAttribSet( data, ih, "_IUPIMAGE_CURSOR", NULL );
	// }

	// /* the remaining native images are all IUPIMAGE_IMAGE(*) - depends on BGCOLOR/INACTIVE/etc  */
	// name = iupTableFirst( data, ih->attrib );
	// while (name)
	// {
	// 	if ( iupStrEqualPartial( name, "_IUPIMAGE_IMAGE" ))
	// 	{
	// 	handle = iupTableGetCurr( data, ih->attrib );
	// 	if (handle)
	// 	{
	// 		iupdrvImageDestroy( data, handle, IUPIMAGE_IMAGE );
	// 		iupTableSetCurr( data, ih->attrib, NULL, IUPTABLE_POINTER );
	// 	}
	// 	}

	// 	name = iupTableNext( data, ih->attrib );
	// }

	// name = iupTableFirst( data, ih->attrib );
	// while (name)
	// {
	// 	if ( iupStrEqualPartial( name, "_IUPIMAGE_WD_IMAGE" ))
	// 	{
	// 	handle = iupTableGetCurr( data, ih->attrib );
	// 	if (handle)
	// 	{
	// 		Icallback wdImageDestroy = amy_IupGetFunction( data, "_IUPIMAGE_WD_IMAGEDESTROY" );
	// 		if (wdImageDestroy) wdImageDestroy( (Ihandle*)handle, data );
	// 		iupTableSetCurr( data, ih->attrib, NULL, IUPTABLE_POINTER );
	// 	}
	// 	}

	// 	name = iupTableNext( data, ih->attrib );
	// }

	// handle = iupAttribGet( data, ih, "_IUPIMAGE_LOADED_HANDLE" );
	// if (handle)
	// {
	// 	iupdrvImageDestroy( data, handle, IUPIMAGE_IMAGE );
	// 	iupAttribSet( data, ih, "_IUPIMAGE_LOADED_HANDLE", NULL );
	// }

	// handle = iupAttribGet( data, ih, "_IUPIMAGE_LOADED_WD_HANDLE" );
	// if (handle)
	// {
	// 	Icallback wdImageDestroy = amy_IupGetFunction( data, "_IUPIMAGE_WD_IMAGEDESTROY" );
	// 	if (wdImageDestroy) wdImageDestroy( (Ihandle*)handle, data );
	// 	iupAttribSet( data, ih, "_IUPIMAGE_LOADED_WD_HANDLE", NULL );
	// }

	// /* additional image buffer when an amy_IupImage is converted to one (CD, OpenGL, etc) */
	// handle = iupAttribGet( data, ih, "_IUPIMAGE_BUFFER" );
	// if (handle)
	// {
	// 	iupAttribSet( data, ih, "_IUPIMAGE_BUFFER", NULL );
	// 	free(handle );
	// }

	// handle = iupAttribGet( data, ih, "_IUPIMAGE_BUFFER_INACTIVE" );
	// if (handle)
	// {
	// 	iupAttribSet( data, ih, "_IUPIMAGE_BUFFER_INACTIVE", NULL );
	// 	free(handle );
	// }
}


/******************************************************************************/

static int iImageSetClearCacheAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  iImageClearCache( data, ih );
  (void)value;
  return 0;
}

static int iImageSetReshapeAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  int w, h;

  if ( iupAttribGet( data, ih, "_IUPIMAGE_LOADED_HANDLE" ) || iupAttribGet( data, ih, "_IUPIMAGE_LOADED_WD_HANDLE" ))
    return 0;

  if ( iupStrToIntInt(value, &w, &h, 'x') == 2)
  {
    int old_w = ih->currentwidth;
    int old_h = ih->currentheight;

    if (w*h > old_w*old_h)
    {
      /* must allocate more memory */
      unsigned char *imgdata = (unsigned char*) iupAttribGet( data, ih, "WID" );
      imgdata = (unsigned char *)realloc(imgdata, sizeof(unsigned char)*w*h * 3 );
      iupAttribSet( data, ih, "WID", (char*)imgdata );
    }

    ih->currentwidth = w;
    ih->currentheight = h;
  }
  return 0;
}

static int iImageSetResizeAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  int new_width, new_height;

  if ( iupAttribGet( data, ih, "_IUPIMAGE_LOADED_HANDLE" ) || iupAttribGet( data, ih, "_IUPIMAGE_LOADED_WD_HANDLE" ))
    return 0;

  if ( iupStrToIntInt(value, &new_width, &new_height, 'x') == 2)
  {
    if (new_width != ih->currentwidth || new_height != ih->currentheight)
    {
      iupAttribSet( data, ih, "SCALED", "Yes" );
      iupAttribSetStrf( data, ih, "ORIGINALSCALE", "%dx%d", ih->currentwidth, ih->currentheight );

      iImageResize( data, ih, new_width, new_height );
    }
  }
  return 0;
}

static char *iImageGetWidthAttrib( struct libData *data, Ihandle *ih )
{
	return amy_iupStrReturnInt( data, ih->currentwidth );
}

static char *iImageGetHeightAttrib( struct libData *data, Ihandle *ih )
{
	return amy_iupStrReturnInt( data, ih->currentheight );
}

static char *iImageGetRasterSizeAttrib( struct libData *data, Ihandle *ih )
{
  int width = ih->currentwidth;
  int height = ih->currentheight;

  if (width < 0) width = 0;
  if (height < 0) height = 0;

  if (width == 0 && height == 0)
    return NULL;

  return iupStrReturnIntInt(width, height, 'x' );
}

static int iImageSetIdValueAttrib( struct libData *data, Ihandle *ih, int id, const char *value)
{
  (void)ih;
  (void)value;
  (void)id;
  /*  iupAttribSetStrId( data, ih, "", id, value ); */
  return 1;
}

static char *iImageGetIdValueAttrib( struct libData *data, Ihandle *ih, int id)
{
  return iupAttribGetId( data, ih, "", id );
}

/***************************************************************************************************/


static int iImageCreate( struct libData *data, Ihandle *ih, void** params, int bpp)
{
  int width, height, channels, count;
  unsigned char *imgdata;

  iupASSERT(params != NULL );
  if ( ! params)
    return IUP_ERROR;

  width = (int)(params[0] );
  height = (int)(params[1] );

  iupASSERT(width > 0 );
  iupASSERT(height > 0 );

  if (width <= 0 || height <= 0)
    return IUP_ERROR;

  ih->currentwidth = width;
  ih->currentheight = height;

  channels = 1;  /* bpp == 8 */
  if (bpp == 24)
    channels = 3;
  else if (bpp == 32)
    channels = 4;

  count = width*height*channels;
  imgdata = (unsigned char *)malloc(count );

  if (((int)(params[2] ) == -1) || ((int)(params[3] ) == -1)) /* NULL or compacted in one pointer */
  {
    if ((int)(params[2] ) != -1)
      memcpy(imgdata, params[2], count );
    else
      memset(imgdata, 0, count );
  }
  else /* one param for each pixel/plane */
  {
    int i;
    for (i = 0; i < count; i++)
    {
      imgdata[i] = (unsigned char)((int)(params[i + 2] ));
    }
  }

  iupAttribSet( data, ih, "WID", (char*)imgdata );
  iupAttribSetInt( data, ih, "BPP", bpp );
  iupAttribSetInt( data, ih, "CHANNELS", channels );

  return IUP_NOERROR;
}

static int iImageCreateMethod( struct libData *data, Ihandle *ih, void** params)
{
  return iImageCreate( data, ih, params, 8 );
}

static int iImageRGBCreateMethod( struct libData *data, Ihandle *ih, void** params)
{
  return iImageCreate( data, ih, params, 24 );
}

static int iImageRGBACreateMethod( struct libData *data, Ihandle *ih, void** params)
{
  return iImageCreate( data, ih, params, 32 );
}

static void iImageDestroyMethod( struct libData *data, Ihandle *ih )
{
  char *stock_load;

  unsigned char *imgdata = (unsigned char*) iupAttribGet( data, ih, "WID" );
  if ( imgdata)
  {
    iupAttribSet( data, ih, "WID", NULL );
    free(imgdata );
  }

  stock_load = iupAttribGet( data, ih, "_IUPIMAGE_STOCK_LOAD" );
  if (stock_load)
  {
    iImageStockUnload( data, stock_load );
    iupAttribSetStr( data, ih, "_IUPIMAGE_STOCK_LOAD", NULL );
  }

  iImageClearCache( data, ih );
}


/******************************************************************************/

IUP_API Ihandle *amy_IupImage( struct libData *data, int width, int height, const unsigned char *imgdata )
{
  void *params[4];
  params[0] = (void*)width;
  params[1] = (void*)height;
  params[2] = imgdata ? (void*)imgdata : (void*)-1;
  params[3] = (void*)-1;
  return amy_IupCreatev( data, "image", params );
}

IUP_API Ihandle *amy_IupImageRGB( struct libData *data, int width, int height, const unsigned char *imgdata )
{
  void *params[4];
  params[0] = (void*)width;
  params[1] = (void*)height;
  params[2] = imgdata ? (void*)imgdata : (void*)-1;
  params[3] = (void*)-1;
  return amy_IupCreatev( data, "imagergb", params );
}

IUP_API Ihandle *amy_IupImageRGBA( struct libData *data, int width, int height, const unsigned char *imgdata )
{
  void *params[4];
  params[0] = (void*)width;
  params[1] = (void*)height;
  params[2] = imgdata ? (void*)imgdata : (void*)-1;
  params[3] = (void*)-1;
  return amy_IupCreatev( data, "imagergba", params );
}

static Iclass *iImageNewClassBase( struct libData *data, const char *name, const char *cons )
{
  Iclass *ic = iupClassNew( data, NULL );

  ic->name = name;
  ic->cons = cons;
  ic->format = "iic"; /* (int,int,unsigned char*) */
  ic->nativetype = IUP_TYPEIMAGE;
  ic->childtype = IUP_CHILDNONE;
  ic->is_interactive = 0;

  /* Class functions */
  ic->Destroy = iImageDestroyMethod;

  /* Attribute functions */
  iupClassRegisterAttribute( data, ic, "WID", NULL, NULL, NULL, NULL, IUPAF_READONLY | IUPAF_NO_INHERIT | IUPAF_NO_STRING );
  iupClassRegisterAttribute( data, ic, "WIDTH", iImageGetWidthAttrib, NULL, NULL, NULL, IUPAF_READONLY | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "HEIGHT", iImageGetHeightAttrib, NULL, NULL, NULL, IUPAF_READONLY | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "RASTERSIZE", iImageGetRasterSizeAttrib, NULL, NULL, NULL, IUPAF_READONLY | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "BGCOLOR", NULL, NULL, IUPAF_SAMEASSYSTEM, "DLGBGCOLOR", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "HANDLENAME", NULL, NULL, NULL, NULL, IUPAF_NO_SAVE | IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "BPP", NULL, NULL, NULL, NULL, IUPAF_READONLY | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CHANNELS", NULL, NULL, NULL, NULL, IUPAF_READONLY | IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "HOTSPOT", NULL, NULL, "0:0", NULL, IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "CLEARCACHE", NULL, iImageSetClearCacheAttrib, NULL, NULL, IUPAF_WRITEONLY | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "RESHAPE", NULL, iImageSetReshapeAttrib, NULL, NULL, IUPAF_WRITEONLY | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "RESIZE", NULL, iImageSetResizeAttrib, NULL, NULL, IUPAF_WRITEONLY | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "SCALED", NULL, NULL, NULL, NULL, IUPAF_READONLY | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "ORIGINALSCALE", NULL, NULL, NULL, NULL, IUPAF_READONLY | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "AUTOSCALE", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DPI", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );

  return ic;
}

Iclass *iupImageNewClass( struct libData *data )
{
  Iclass *ic = iImageNewClassBase( data, "image", NULL );
  ic->New = iupImageNewClass;
  ic->Create = iImageCreateMethod;
  ic->has_attrib_id = 1;

  iupClassRegisterAttributeId( data, ic, "IDVALUE", iImageGetIdValueAttrib, iImageSetIdValueAttrib, IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );

  return ic;
}

Iclass *iupImageRGBNewClass( struct libData *data )
{
  Iclass *ic = iImageNewClassBase( data, "imagergb", "ImageRGB" );
  ic->New = iupImageRGBNewClass;
  ic->Create = iImageRGBCreateMethod;
  return ic;
}

Iclass *iupImageRGBANewClass( struct libData *data )
{
  Iclass *ic = iImageNewClassBase( data, "imagergba", "ImageRGBA" );
  ic->New = iupImageRGBANewClass;
  ic->Create = iImageRGBACreateMethod;
  return ic;
}
