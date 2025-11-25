/** \file
 * \brief Driver Font Management
 *
 * See Copyright Notice in "iup.h"
 */
 
#ifndef __IUP_DRVFONT_H 
#define __IUP_DRVFONT_H

#ifdef __cplusplus
extern "C" {
#endif


/** \defgroup drvfont Driver Font Interface 
 * \par
 * Each driver must export the symbols defined here.
 * \par
 * See \ref iup_drvfont.h 
 * \ingroup drv */

/* Called only from IupOpen/IupClose. */
void iupdrvFontInit( struct libData *data );
void iupdrvFontFinish( struct libData *data );

/** Retrieve the character size for the selected font.
 * Should be used only to calculate the SIZE attribute.
 * \ingroup drvfont */
IUP_SDK_API void iupdrvFontGetCharSize( struct libData *data, Ihandle *ih, int *charwidth, int *charheight );

/** Retrieve the string width for the selected font.
 * \ingroup drvfont */
IUP_SDK_API int iupdrvFontGetStringWidth( struct libData *data, Ihandle *ih, const char *str );

/** Retrieve the multi-lined string size for the selected font. \n
 * Width is the maximum line width. \n
 * Height is charheight*number_of_lines (this will avoid line size variations).
 * \ingroup drvfont */
IUP_SDK_API void iupdrvFontGetMultiLineStringSize( struct libData *data, Ihandle *ih, const char *str, int *w, int *h );

/** Same as \ref iupdrvFontGetMultiLineStringSize but not associated with a control. 
 * Used in IupDraw.\n
 *\ingroup drvfont */
IUP_SDK_API void iupdrvFontGetTextSize( struct libData *data, const char *font, const char *str, int len, int *w, int *h );

/** Returns information about the font. \n
 *\ingroup drvfont */
IUP_SDK_API void iupdrvFontGetFontDim( struct libData *data, const char *font, int *max_width, int *line_height, int *ascent, int *descent );

/** Returns the System default font.
 * \ingroup drvfont */
IUP_SDK_API char *iupdrvGetSystemFont( struct libData *data );

/** FONT attribute set function.
 * \ingroup drvfont */
IUP_SDK_API int iupdrvSetFontAttrib( struct libData *data, Ihandle *ih, const char *value );



/** Compensates IupMatrix limitation in Get FONT.
  * \ingroup drvfont */
IUP_SDK_API char *iupGetFontValue( struct libData *data, Ihandle *ih );

/** Parse the font format description.
 * Returns a non zero value if successful.
 * \ingroup drvfont */
IUP_SDK_API int iupGetFontInfo( struct libData *data, const char *font, char *typeface, int *size, int *is_bold, int *is_italic, int *is_underline, int *is_strikeout );

/** Parse the Pango font format description.
 * Returns a non zero value if successful.
 * \ingroup drvfont */
IUP_SDK_API int iupFontParsePango( struct libData *data, const char *value, char *typeface, int *size, int *bold, int *italic, int *underline, int *strikeout );

/** Parse the old IUP Windows font format description.
 * Returns a non zero value if successful.
 * \ingroup drvfont */
IUP_SDK_API int iupFontParseWin( struct libData *data, const char *value, char *typeface, int *size, int *bold, int *italic, int *underline, int *strikeout );

/** Parse the X-Windows font format description.
 * Returns a non zero value if successful.
 * \ingroup drvfont */
IUP_SDK_API int iupFontParseX( struct libData *data, const char *value, char *typeface, int *size, int *bold, int *italic, int *underline, int *strikeout );


/** Changes the FONT style only.
 * \ingroup attribfunc */
IUP_SDK_API int iupSetFontStyleAttrib( struct libData *data, Ihandle *ih, const char *value );

/** Changes the FONT size only.
 * \ingroup attribfunc */
IUP_SDK_API int iupSetFontSizeAttrib( struct libData *data, Ihandle *ih, const char *value );

/** Changes the FONT face only.
* \ingroup attribfunc */
IUP_SDK_API int iupSetFontFaceAttrib( struct libData *data, Ihandle *ih, const char *value );

/** Returns the FONT style.
 * \ingroup attribfunc */
IUP_SDK_API char *iupGetFontStyleAttrib( struct libData *data, Ihandle *ih );

/** Returns the FONT size.
 * \ingroup attribfunc */
IUP_SDK_API char *iupGetFontSizeAttrib( struct libData *data, Ihandle *ih );

/** Returns the FONT face.
 * \ingroup attribfunc */
IUP_SDK_API char *iupGetFontFaceAttrib( struct libData *data, Ihandle *ih );

/* Used in Global Attributes */
void  iupSetDefaultFontSizeGlobalAttrib(struct libData *data, const char *value );
char *iupGetDefaultFontSizeGlobalAttrib( struct libData *data );
int   iupSetDefaultFontStyleGlobalAttrib(struct libData *data, const char *value );
char *iupGetDefaultFontStyleGlobalAttrib( struct libData *data );
int   iupSetDefaultFontFaceGlobalAttrib(struct libData *data, const char *value );
char *iupGetDefaultFontFaceGlobalAttrib( struct libData *data );


/* Updates the FONT attrib.
 * Called only from IupMap.
 */
void iupUpdateFontAttrib( struct libData *data, Ihandle *ih );

/* Used to map foreign names into native names */
const char *iupFontGetWinName( struct libData *data, const char *typeface );
const char *iupFontGetXName( struct libData *data, const char *typeface );
const char *iupFontGetPangoName( struct libData *data, const char *typeface );
const char *iupFontGetMacName( struct libData *data, const char *typeface );


#ifdef __cplusplus
}
#endif

#endif
