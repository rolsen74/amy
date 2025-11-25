/** \file
 * \brief Toggle Controls (not exported API)
 *
 * See Copyright Notice in "iup.h"
 */
 
#ifndef __IUP_TOGGLE_H 
#define __IUP_TOGGLE_H

#ifdef __cplusplus
extern "C" {
#endif


/* some drivers reuses iupdrvButtonAddBorders */
void iupdrvButtonAddBorders( struct libData *data, Ihandle *ih, int *x, int *y );

void iupdrvToggleAddBorders( struct libData *data, Ihandle *ih, int *x, int *y );

void iupdrvToggleInitClass( struct libData *data, Iclass *ic );
void iupdrvToggleAddCheckBox( struct libData *data, Ihandle *ih, int *x, int *y, const char* str );

IUP_SDK_API Ihandle *iupRadioFindToggleParent( struct libData *data, Ihandle* ih_toggle );
char* iupToggleGetPaddingAttrib( struct libData *data, Ihandle *ih );

enum {IUP_TOGGLE_IMAGE, IUP_TOGGLE_TEXT};

struct _IcontrolData 
{
  int type,                         /* the 2 toggle possibilities */
      is_radio,
      flat,
      horiz_padding, vert_padding;  /* toggle margin for images */
};


#ifdef __cplusplus
}
#endif

#endif
