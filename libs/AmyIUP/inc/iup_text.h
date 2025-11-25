/** \file
 * \brief Text Control ( struct libData *data, not exported API)
 *
 * See Copyright Notice in "iup.h"
 */
 
#ifndef __IUP_TEXT_H 
#define __IUP_TEXT_H

#ifdef __cplusplus
extern "C" {
#endif


void iupdrvTextInitClass( struct libData *data, Iclass *ic );
void iupdrvTextAddBorders( struct libData *data, Ihandle *ih, int *w, int *h );
void iupdrvTextAddSpin( struct libData *data, Ihandle *ih, int *w, int h );
void* iupdrvTextAddFormatTagStartBulk( struct libData *data, Ihandle *ih );
void iupdrvTextAddFormatTagStopBulk( struct libData *data, Ihandle *ih, void* state );
void iupdrvTextAddFormatTag( struct libData *data, Ihandle *ih, Ihandle *formattag, int bulk );
void iupdrvTextConvertLinColToPos( struct libData *data, Ihandle *ih, int lin, int col, int *pos );
void iupdrvTextConvertPosToLinCol( struct libData *data, Ihandle *ih, int pos, int *lin, int *col );

/* Used by List and Text, implemented in Text */
int iupEditCallActionCb( struct libData *data, Ihandle *ih, IFnis cb, const char *insert_value, int start, int end, void *mask, int nc, int remove_dir, int utf8 );

void iupTextUpdateFormatTags( struct libData *data, Ihandle *ih );

char *iupTextGetPaddingAttrib( struct libData *data, Ihandle *ih );
char *iupTextGetNCAttrib( struct libData *data, Ihandle *ih );
int iupTextSetFormattingAttrib( struct libData *data, Ihandle *ih, const char *value );
char *iupTextGetFormattingAttrib( struct libData *data, Ihandle *ih );
int iupTextSetAddFormatTagAttrib( struct libData *data, Ihandle *ih, const char *value );
int iupTextSetAddFormatTagHandleAttrib( struct libData *data, Ihandle *ih, const char *value );

struct _IcontrolData 
{
  int is_multiline,
      has_formatting,
      append_newline,
      disable_callbacks,
      nc,
      sb,                           /* scrollbar configuration, can be changed only before map */
      horiz_padding, vert_padding,  /* button margin */
      last_caret_pos;
  Iarray* formattags;
  Imask *mask;
};


#ifdef __cplusplus
}
#endif

#endif
