/** \file
 * \brief Dialog (not exported API)
 *
 * See Copyright Notice in "iup.h"
 */
 
#ifndef __IUP_DIALOG_H 
#define __IUP_DIALOG_H

#ifdef __cplusplus
extern "C" {
#endif


/* PUBLIC */

/* Shows the dialog in the given position and disable interaction with other dialogs.
 * The element must be already mapped.
 * Must return IUP_ERROR or IUP_NOERROR.
 * Called only from IupPopup. */
int iupDialogPopup( struct libData *data, Ihandle *ih, int x, int y );

/* Shows the dialog in the given position.
 * The dialog must be already mapped.
 * Must return IUP_ERROR or IUP_NOERROR.
 * Called only from IupShow and IupShowXY. */
int iupDialogShowXY( struct libData *data, Ihandle *ih, int x, int y );

/* Hides the dialog.
 * Called only from IupHide. */
void iupDialogHide( struct libData *data, Ihandle *ih );

/* Returns a unique number to be as child id. */
int iupDialogGetChildId( struct libData *data, Ihandle *ih );
char *iupDialogGetChildIdStr( struct libData *data, Ihandle *ih );

/* Returns the size of the decoration */
void iupdrvDialogGetDecoration( struct libData *data, Ihandle *ih, int *border, int *caption, int *menu );

/* Returns the native parent. Can be PARENTDIALOG or NATIVEPARENT attributes. Parent must be mapped. */
IUP_SDK_API InativeHandle *iupDialogGetNativeParent( struct libData *data, Ihandle *ih );

/* Changes the parent dialog (works only if already set at map) */
void iupdrvDialogSetParent( struct libData *data, Ihandle *ih, InativeHandle* native_parent );

/* Updates the dialog initial position from internal attributes.
   Used mostly by the native pre-defined dialogs. */
void iupDialogUpdatePosition( struct libData *data, Ihandle *ih );

/* For external modal dialog stack control */
void iupDialogLeaveModal( struct libData *data, int popup_level );
void iupDialogEnterModal( struct libData *data, Ihandle *ih_popup, int popup_level );


/*********************************************************************/
                        /* PRIVATE */
/*********************************************************************/

#ifdef _IUPDLG_PRIVATE

/* retrieve the decorations size that offsets the window size of the client size. */
void iupDialogGetDecorSize( struct libData *data, Ihandle *ih, int *decorwidth, int *decorheight );

void iupDialogCustomFrameSimulateCheckCallbacks( struct libData *data, Ihandle *ih );
int  iupDialogCustomFrameRestore( struct libData *data, Ihandle *ih );
void iupDialogCustomFrameMaximize( struct libData *data, Ihandle *ih );

struct _IcontrolData 
{
  int show_state,     /* save the state to be used used in SHOW_CB */
    first_show,     /* boolean flag to indicate that the dialog was shown for the first time */
    ignore_resize,  /* flag to ignore the next resize */
    popup_level,    /* popup level of the dialog if IupPopup used */
    child_id,       /* serial number used by child controls */
    cmd_show;       /* parameters for ShowWindow in Windows driver */
  Ihandle *menu;
};


/******************************/
/* Driver dependent functions */
/******************************/

void iupdrvDialogInitClass( struct libData *data, Iclass *iclass );

void iupdrvDialogGetPosition( struct libData *data, Ihandle *ih, InativeHandle* handle, int *x, int *y );
void iupdrvDialogSetVisible( struct libData *data, Ihandle *ih, int visible );
int iupdrvDialogSetPlacement( struct libData *data, Ihandle *ih );
void iupdrvDialogSetPosition(struct libData *data, Ihandle *ih, int x, int y );
void iupdrvDialogGetSize( struct libData *data, Ihandle *ih, InativeHandle *handle, int *w, int *h );
int iupdrvDialogIsVisible( struct libData *data, Ihandle *ih );
int iupDialogSetClientSizeAttrib( struct libData *data, Ihandle *ih, const char *value );
char *iupDialogGetClientSizeAttrib( struct libData *data, Ihandle *ih );


#endif

#ifdef __cplusplus
}
#endif

#endif
