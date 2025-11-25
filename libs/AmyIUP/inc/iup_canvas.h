/** \file
 * \brief Canvas Control (not exported API)
 *
 * See Copyright Notice in "iup.h"
 */
 
#ifndef __IUP_CANVAS_H 
#define __IUP_CANVAS_H

#ifdef __cplusplus
extern "C" {
#endif


void iupdrvCanvasInitClass( struct libData *data, Iclass *ic );
void iupCanvasCalcScrollIntPos( struct libData *data, double min, double max, double page, double pos, 
                                 int imin,   int imax,  int *ipage,  int *ipos );
void iupCanvasCalcScrollRealPos( struct libData *data, double min, double max, double *pos, 
                                 int imin,   int imax,  int ipage,  int *ipos );
char *iupCanvasGetPosXAttrib( struct libData *data, Ihandle *ih );
char *iupCanvasGetPosYAttrib( struct libData *data, Ihandle *ih );

#define IUP_SB_MIN 0
#define IUP_SB_MAX INT_MAX-1

/* this must match the iupCanvas public definition in "iup_stdcontrols.h" */
struct _IcontrolData 
{
  int sb;    /* scrollbar configuration, valid only after map, use iupBaseGetScrollbar before map */
  double posx, posy;
  int inside_resize;
};


#ifdef __cplusplus
}
#endif

#endif
