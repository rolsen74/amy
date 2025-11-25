/** \file
 * \brief Image Resources (not exported API)
 *
 * See Copyright Notice in "iup.h"
 */
 
#ifndef __IUP_IMAGE_H 
#define __IUP_IMAGE_H

#ifdef __cplusplus
extern "C" {
#endif


void *iupdrvImageCreateIcon( struct libData *data, Ihandle *ih );
void *iupdrvImageCreateCursor( struct libData *data, Ihandle *ih );
void *iupdrvImageCreateImage( struct libData *data, Ihandle *ih, const char *bgcolor, int make_inactive );

enum {IUPIMAGE_IMAGE, IUPIMAGE_ICON, IUPIMAGE_CURSOR};
void *iupdrvImageLoad( struct libData *data, const char *name, int type );
IUP_SDK_API void  iupdrvImageDestroy( struct libData *data, void *handle, int type );  /* exported to match iupdrvImageCreateImageRaw */
int   iupdrvImageGetInfo( struct libData *data, void *handle, int *w, int *h, int *bpp );  /* only for IUPIMAGE_IMAGE */
void  iupdrvImageGetData( struct libData *data, void *handle, unsigned char *imgdata );   /* only for IUPIMAGE_IMAGE */

void *iupImageGetIcon( struct libData *data, const char *name );
void *iupImageGetCursor( struct libData *data, const char *name );
void *iupImageGetImage( struct libData *data, const char *name, Ihandle *parent, int make_inactive, const char *bgcolor );
void iupImageGetInfo( struct libData *data, const char *name, int *w, int *h, int *bpp );
void iupImageRemoveFromCache( struct libData *data, Ihandle *ih, void *handle );

typedef struct _iupColor { 
  unsigned char r, g, b, a; 
} iupColor;

IUP_SDK_API int iupImageInitColorTable( struct libData *data, Ihandle *ih, iupColor* colors, int *colors_count );
void iupImageInitNonBgColors( struct libData *data, Ihandle *ih, unsigned char *colors );
IUP_SDK_API void iupImageColorMakeInactive( unsigned char *r, unsigned char *g, unsigned char *b,
                               unsigned char bg_r, unsigned char bg_g, unsigned char bg_b );
int iupImageNormBpp( struct libData *data, int bpp );

#define iupALPHABLEND(_src,_dst,_alpha) (unsigned char)(((_src) * (_alpha) + (_dst) * (255 - (_alpha))) / 255)

/* In Windows, RAW data is a DIB handle. 
   imgdata here is bottom-up arranged and has separated planes
   Used only by IupGetImageNativeHandle and IupGetNativeHandleImage */
IUP_SDK_API void *iupdrvImageCreateImageRaw( struct libData *data, int width, int height, int bpp, iupColor* colors, int colors_count, unsigned char *imgdata );
IUP_SDK_API int iupdrvImageGetRawInfo( struct libData *data, void *handle, int *w, int *h, int *bpp, iupColor* colors, int *colors_count );
IUP_SDK_API void iupdrvImageGetRawData( struct libData *data, void *handle, unsigned char *imgdata );

void iupImageSetHandleFromLoaded( struct libData *data, const char *name, void *handle );
Ihandle *iupImageGetImageFromName( struct libData *data, const char *name );

#if defined(FILE) || defined(_INC_STDIO) || defined(_STDIO_H_) || defined(_STDIO_H)
IUP_SDK_API int iupImageExportToFile( struct libData *data, Ihandle *ih, FILE* file, const char *format, const char *name );  /* Used only in IupView and IupVisualLED */
#endif
IUP_SDK_API int iupImageExportToString( struct libData *data, Ihandle *ih, char **str, const char *format, const char *name );  /* Used only in IupVisualLED */

void iupImageStockInit( struct libData *data );
void iupImageStockFinish( struct libData *data );
typedef Ihandle *(*iupImageStockCreateFunc)( struct libData *data );
IUP_SDK_API void iupImageStockSet( struct libData *data, const char *name, iupImageStockCreateFunc func, const char *native_name );
IUP_SDK_API void iupImageStockSetNoResize( struct libData *data, const char *name, iupImageStockCreateFunc func, const char *native_name );
IUP_SDK_API void iupImageStockLoadAll( struct libData *data );  /* Used only in IupView and IupVisualLED */
int iupImageStockGetSize( struct libData *data );
void iupImageStockGet( struct libData *data, const char *name, Ihandle **ih, const char **native_name );

int iupIsHighDpi( struct libData *data );


#ifdef __cplusplus
}
#endif

#endif
