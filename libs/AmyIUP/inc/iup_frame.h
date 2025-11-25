/** \file
 * \brief Frame Control (not exported API)
 *
 * See Copyright Notice in "iup.h"
 */
 
#ifndef __IUP_FRAME_H 
#define __IUP_FRAME_H

#ifdef __cplusplus
extern "C" {
#endif

int iupdrvFrameHasClientOffset( struct libData *data, Ihandle *ih );
void iupdrvFrameInitClass( struct libData *data, Iclass *ic );
void iupdrvFrameGetDecorOffset( struct libData *data, Ihandle *ih, int *x, int *y );
int iupFrameGetTitleHeight( struct libData *data, Ihandle *ih );
char *iupFrameGetBgColorAttrib( struct libData *data, Ihandle *ih );
int iupdrvFrameGetDecorSize( struct libData *data, Ihandle *ih, int *w, int *h );
int iupdrvFrameGetTitleHeight( struct libData *data, Ihandle *ih, int *h );

#ifdef __cplusplus
}
#endif

#endif
