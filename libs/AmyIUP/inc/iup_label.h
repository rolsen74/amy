/** \file
 * \brief Label Control (not exported API)
 *
 * See Copyright Notice in "iup.h"
 */
 
#ifndef __IUP_LABEL_H 
#define __IUP_LABEL_H

#ifdef __cplusplus
extern "C" {
#endif


void iupdrvLabelInitClass( struct libData *data, Iclass *ic );
void iupdrvLabelAddExtraPadding( struct libData *data, Ihandle *ih, int *x, int *y );

char *iupLabelGetPaddingAttrib( struct libData *data, Ihandle *ih );
int iupLabelGetTypeBeforeMap( struct libData *data, Ihandle *ih );

/* label types */
enum{IUP_LABEL_SEP_HORIZ, IUP_LABEL_SEP_VERT, IUP_LABEL_IMAGE, IUP_LABEL_TEXT};

struct _IcontrolData 
{
  int type,   /* the 4 labels possibilities */
      horiz_padding, vert_padding;  /* label margin */

  /* used only by the Windows driver */
  int horiz_alignment, vert_alignment, 
      text_style;  
  unsigned long fgcolor;
};


#ifdef __cplusplus
}
#endif

#endif
