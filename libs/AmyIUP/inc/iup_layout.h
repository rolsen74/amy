/** \file
 * \brief Abstract Layout Management (not exported API)
 *
 * See Copyright Notice in "iup.h"
 */
 
#ifndef __IUP_LAYOUT_H 
#define __IUP_LAYOUT_H

#ifdef __cplusplus
extern "C" {
#endif

/* called from IupMap and IupRefresh */
void iupLayoutCompute( struct libData *data, Ihandle *ih );  /* can be called before map */
IUP_SDK_API void iupLayoutUpdate( struct libData *data, Ihandle *ih );   /* called after map */

IUP_SDK_API void iupLayoutApplyMinMaxSize( struct libData *data, Ihandle *ih, int *w, int *h );

/* Other functions declared in <iup.h> and implemented here. 
IupRefresh
*/

/* at iup_layout_dlg */

IUP_SDK_API Ihandle *iupLayoutFindElementDialog( struct libData *data, Ihandle *tree, Ihandle *elem );
IUP_SDK_API void iupLayoutPropertiesUpdate( struct libData *data, Ihandle *properties, Ihandle *elem );
IUP_SDK_API char *iupLayoutGetElementTitle( struct libData *data, Ihandle *elem );
IUP_SDK_API int iupLayoutAttributeHasChanged( struct libData *data, Ihandle *elem, const char *name, const char *value, const char *def_value, int flags );

enum { IUP_LAYOUT_EXPORT_LUA, IUP_LAYOUT_EXPORT_C, IUP_LAYOUT_EXPORT_LED };
/* at iup_export */
#if defined(FILE) || defined(_INC_STDIO) || defined(_STDIO_H_) || defined(_STDIO_H)
IUP_SDK_API void iupLayoutExportNamedElemList( struct libData *data, FILE* file, Ihandle **named_elem, int count, int export_format, int saved_info );
IUP_SDK_API void iupLayoutExportNamedImageListSetHandle( struct libData *data, FILE* file, Ihandle **named_elem, int count, int export_format );
IUP_SDK_API void iupLayoutExportNamedImageList( struct libData *data, FILE* file, Ihandle **named_elem, int count, int export_format );
#endif

#ifdef __cplusplus
}
#endif

#endif
