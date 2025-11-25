/** \file
 * \brief List Control (not exported API)
 *
 * See Copyright Notice in "iup.h"
 */
 
#ifndef __IUP_LIST_H 
#define __IUP_LIST_H

#ifdef __cplusplus
extern "C" {
#endif


void iupdrvListInitClass( struct libData *data, Iclass *ic );
void iupdrvListAddBorders( struct libData *data, Ihandle *ih, int *w, int *h );
void iupdrvListAddItemSpace( struct libData *data, Ihandle *ih, int *h );
int iupdrvListGetCount( struct libData *data, Ihandle *ih );
void iupdrvListAppendItem( struct libData *data, Ihandle *ih, const char* value );
void iupdrvListInsertItem( struct libData *data, Ihandle *ih, int pos, const char* value );
void iupdrvListRemoveItem( struct libData *data, Ihandle *ih, int pos );
void iupdrvListRemoveAllItems( struct libData *data, Ihandle *ih );

/* Used by List and Text, implemented in Text */
int iupEditCallActionCb( struct libData *data, Ihandle *ih, IFnis cb, const char* insert_value, int start, int end, void *mask, int nc, int remove_dir, int utf8 );

int iupListGetPosAttrib( struct libData *data, Ihandle *ih, int id );
int iupListSetIdValueAttrib( struct libData *data, Ihandle *ih, int id, const char* value );
char* iupListGetNCAttrib( struct libData *data, Ihandle *ih );
char* iupListGetPaddingAttrib( struct libData *data, Ihandle *ih );
char* iupListGetSpacingAttrib( struct libData *data, Ihandle *ih );

void iupListSingleCallActionCb( struct libData *data, Ihandle *ih, IFnsii cb, int pos );
void iupListMultipleCallActionCb( struct libData *data, Ihandle *ih, IFnsii cb, IFns multi_cb, int* pos, int sel_count );
void iupListSingleCallDblClickCb( struct libData *data, Ihandle *ih, IFnis cb, int pos );
int iupListCallDragDropCb( struct libData *data, Ihandle *ih, int drag_id, int drop_id, int *is_ctrl );

void iupListSetInitialItems( struct libData *data, Ihandle *ih );
void iupListUpdateOldValue( struct libData *data, Ihandle *ih, int pos, int removed );
void* iupdrvListGetImageHandle( struct libData *data, Ihandle *ih, int id );
int iupdrvListSetImageHandle( struct libData *data, Ihandle *ih, int id, void* hImage );

struct _IcontrolData 
{
  int sb,  /* scrollbar configuration, can be changed only before map */
      nc,
      spacing,
      horiz_padding, 
      vert_padding,
      last_caret_pos,
      is_multiple,
      is_dropdown,
      has_editbox,
      maximg_w, maximg_h, /* used only in Windows */
      show_image,
      show_dragdrop;
  Imask *mask;
};


#ifdef __cplusplus
}
#endif

#endif
