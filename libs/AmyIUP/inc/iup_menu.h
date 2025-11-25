/** \file
 * \brief IUP Menu Class ( struct libData *data, not exported API)
 *
 * See Copyright Notice in "iup.h"
 */
 
#ifndef __IUP_MENU_H 
#define __IUP_MENU_H

#ifdef __cplusplus
extern "C" {
#endif

/* Shows a popup menu in the given position.
* Must return IUP_ERROR or IUP_NOERROR.
* Called only from IupPopup.
*/
int iupMenuPopup( struct libData *data, Ihandle *ih, int x, int y );

int iupdrvMenuPopup( struct libData *data, Ihandle *ih, int x, int y );
void iupdrvSeparatorInitClass( struct libData *data, Iclass *ic );
void iupdrvItemInitClass( struct libData *data, Iclass *ic );
void iupdrvMenuInitClass( struct libData *data, Iclass *ic );
void iupdrvSubmenuInitClass( struct libData *data, Iclass *ic );

char *iupMenuProcessTitle( struct libData *data, Ihandle *ih, const char *title );
int iupMenuGetChildId( struct libData *data, Ihandle *ih );
char *iupMenuGetChildIdStr( struct libData *data, Ihandle *ih );
int iupMenuIsMenuBar( struct libData *data, Ihandle *ih );

#ifdef __cplusplus
}
#endif

#endif
