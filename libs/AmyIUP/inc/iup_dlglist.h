/** \file
 * \brief list of all created dialogs
 *
 * See Copyright Notice in "iup.h"
 */
 
#ifndef __IUP_DLGLIST_H 
#define __IUP_DLGLIST_H

#ifdef __cplusplus
extern "C" {
#endif


/** \defgroup dlglist List of Dialogs
 * \par
 * See \ref iup_dlglist.h
 * \ingroup cpi */


/** Adds a dialog to the list. Used only in IupDialog.
 * \ingroup dlglist */
IUP_SDK_API void iupDlgListAdd( struct libData *data, Ihandle *ih );

/** Removes a dialog from the list. Used only in IupDestroy.
 * \ingroup dlglist */
IUP_SDK_API void iupDlgListRemove( struct libData *data, Ihandle *ih );

/** Returns the number of dialogs.
 * \ingroup dlglist */
IUP_SDK_API int iupDlgListCount( struct libData *data );

/** Starts a loop for all the created dialogs. 
 * \ingroup dlglist */
IUP_SDK_API Ihandle *iupDlgListFirst( struct libData *data );

/** Retrieve the next dialog on the list. Must call iupDlgListFirst first.
 * \ingroup dlglist */
IUP_SDK_API Ihandle *iupDlgListNext( struct libData *data );

/** Increments the number of visible dialogs. 
 * \ingroup dlglist */
IUP_SDK_API void iupDlgListVisibleInc( struct libData *data );

/** Decrements the number of visible dialogs.
 * \ingroup dlglist */
IUP_SDK_API void iupDlgListVisibleDec( struct libData *data );

/** Returns the number of visible dialogs.
 * \ingroup dlglist */
IUP_SDK_API int iupDlgListVisibleCount( struct libData *data );


/* Destroy all dialogs and the list.
   Called only from IupClose. */
void iupDlgListDestroyAll( struct libData *data );


/* Destroy all dialogs that have the attribute defined with the given value.
   Called from language binding close. */
IUP_SDK_API void iupDlgListDestroySelected( struct libData *data, const char *name, void *value );


#ifdef __cplusplus
}
#endif

#endif
