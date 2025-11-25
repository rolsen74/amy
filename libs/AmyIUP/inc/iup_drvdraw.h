/** \file
 * \brief Driver Draw API.
 *
 * See Copyright Notice in "iup.h"
 */
 
#ifndef __IUP_DRVDRAW_H 
#define __IUP_DRVDRAW_H

#ifdef __cplusplus
extern "C"
{
#endif

/** \defgroup drvdraw Driver Draw API
 * \par
 * See \ref iup_drvdraw.h
 * \ingroup util */



struct _IdrawCanvas;
typedef struct _IdrawCanvas IdrawCanvas;

enum{ IUP_DRAW_FILL, IUP_DRAW_STROKE, IUP_DRAW_STROKE_DASH, IUP_DRAW_STROKE_DOT, IUP_DRAW_STROKE_DASH_DOT, IUP_DRAW_STROKE_DASH_DOT_DOT };

/** Creates a draw canvas based on an IupCanvas.
 * This will create an image for offscreen drawing.
 * \ingroup drvdraw */
IUP_SDK_API IdrawCanvas* iupdrvDrawCreateCanvas( struct libData *data, Ihandle *ih );

/** Destroys the IdrawCanvas.
 * \ingroup drvdraw */
IUP_SDK_API void iupdrvDrawKillCanvas( struct libData *data, IdrawCanvas *dc );

/** Draws the ofscreen image on the screen.
 * \ingroup drvdraw */
IUP_SDK_API void iupdrvDrawFlush( struct libData *data, IdrawCanvas *dc );

/** Rebuild the offscreen image if the canvas size has changed.
 * Automatically done in iupdrvDrawCreateCanvas.
 * \ingroup drvdraw */
IUP_SDK_API void iupdrvDrawUpdateSize( struct libData *data, IdrawCanvas *dc );

/** Returns the canvas size available for drawing.
 * \ingroup drvdraw */
IUP_SDK_API void iupdrvDrawGetSize( struct libData *data, IdrawCanvas *dc, int *w, int *h );

/** Draws a line.
 * \ingroup drvdraw */
IUP_SDK_API void iupdrvDrawLine( struct libData *data, IdrawCanvas *dc, int x1, int y1, int x2, int y2, long color, int style, int line_width );

/** Draws a filled/hollow rectangle.
 * \ingroup drvdraw */
IUP_SDK_API void iupdrvDrawRectangle( struct libData *data, IdrawCanvas *dc, int x1, int y1, int x2, int y2, long color, int style, int line_width );

/** Draws a filled/hollow arc.
 * \ingroup drvdraw */
IUP_SDK_API void iupdrvDrawArc( struct libData *data, IdrawCanvas *dc, int x1, int y1, int x2, int y2, double a1, double a2, long color, int style, int line_width );

/** Draws a filled/hollow polygon.
 * points are arranged xyxyxy...
 * \ingroup drvdraw */
IUP_SDK_API void iupdrvDrawPolygon( struct libData *data, IdrawCanvas *dc, int* points, int count, long color, int style, int line_width );

#define IUP_DRAW_LEFT     0x0000
#define IUP_DRAW_CENTER   0x0001
#define IUP_DRAW_RIGHT    0x0002
#define IUP_DRAW_WRAP     0x0004
#define IUP_DRAW_ELLIPSIS 0x0008
#define IUP_DRAW_CLIP     0x0010
#define IUP_DRAW_LAYOUTCENTER 0x0020

/** Draws a text.
 * x,y is at left,top corner of the text.
 * \ingroup drvdraw */
IUP_SDK_API void iupdrvDrawText( struct libData *data, IdrawCanvas *dc, const char *text, int len, int x, int y, int w, int h, long color, const char *font, int flags, double text_orientation );

/** Draws an image.
 * x,y is at left,top corner of the image.
 * \ingroup drvdraw */
IUP_SDK_API void iupdrvDrawImage( struct libData *data, IdrawCanvas *dc, const char *name, int make_inactive, const char *bgcolor, int x, int y, int w, int h );

/** Sets a rectangle clipping area.
 * \ingroup drvdraw */
IUP_SDK_API void iupdrvDrawSetClipRect( struct libData *data, IdrawCanvas *dc, int x1, int y1, int x2, int y2 );

/** Removes clipping.
 * \ingroup drvdraw */
IUP_SDK_API void iupdrvDrawResetClip( struct libData *data, IdrawCanvas *dc );

/** Returns the last rectangle set in iupdrvDrawSetClipRect.
* \ingroup drvdraw */
IUP_SDK_API void iupdrvDrawGetClipRect( struct libData *data, IdrawCanvas *dc, int *x1, int *y1, int *x2, int *y2 );

/** Draws a selection rectangle.
 * \ingroup drvdraw */
IUP_SDK_API void iupdrvDrawSelectRect( struct libData *data, IdrawCanvas *dc, int x1, int y1, int x2, int y2 );

/** Draws a focus rectangle.
 * \ingroup drvdraw */
IUP_SDK_API void iupdrvDrawFocusRect( struct libData *data, IdrawCanvas *dc, int x1, int y1, int x2, int y2 );


#ifdef __cplusplus
}
#endif

#endif

