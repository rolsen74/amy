/** \file
 * \brief Standard Controls Class Initialization functions (not exported API)
 *
 * See Copyright Notice in "iup.h"
 */
 
#ifndef __IUP_STDCONTROLS_H 
#define __IUP_STDCONTROLS_H

#ifdef __cplusplus
extern "C" {
#endif


Iclass *iupDialogNewClass( struct libData *data );
Iclass *iupMessageDlgNewClass( struct libData *data );
Iclass *iupColorDlgNewClass( struct libData *data );
Iclass *iupFontDlgNewClass( struct libData *data );
Iclass *iupFileDlgNewClass( struct libData *data );
Iclass *iupProgressDlgNewClass( struct libData *data );

Iclass *iupLabelNewClass( struct libData *data );
Iclass *iupButtonNewClass( struct libData *data );
Iclass *iupToggleNewClass( struct libData *data );
Iclass *iupRadioNewClass( struct libData *data );
Iclass *iupCanvasNewClass( struct libData *data );
Iclass *iupFrameNewClass( struct libData *data );
Iclass *iupProgressBarNewClass( struct libData *data );
Iclass *iupTextNewClass( struct libData *data );
Iclass *iupMultilineNewClass( struct libData *data );
Iclass *iupValNewClass( struct libData *data );
Iclass *iupTabsNewClass( struct libData *data );
Iclass *iupSpinNewClass( struct libData *data );
Iclass *iupSpinboxNewClass( struct libData *data );
Iclass *iupListNewClass( struct libData *data );
Iclass *iupTreeNewClass( struct libData *data );
Iclass *iupLinkNewClass( struct libData *data );
Iclass *iupFlatLabelNewClass( struct libData *data );
Iclass *iupFlatButtonNewClass( struct libData *data );
Iclass *iupFlatToggleNewClass( struct libData *data );
Iclass *iupDropButtonNewClass( struct libData *data );
Iclass *iupFlatSeparatorNewClass( struct libData *data );
Iclass *iupFlatFrameNewClass( struct libData *data );
Iclass *iupFlatTabsNewClass( struct libData *data );
Iclass *iupDialNewClass( struct libData *data );
Iclass *iupGaugeNewClass( struct libData *data );
Iclass *iupColorbarNewClass( struct libData *data );
Iclass *iupColorBrowserNewClass( struct libData *data );
Iclass *iupSpaceNewClass( struct libData *data );
Iclass *iupThreadNewClass( struct libData *data );

Iclass *iupMenuNewClass( struct libData *data );
Iclass *iupItemNewClass( struct libData *data );
Iclass *iupSeparatorNewClass( struct libData *data );
Iclass *iupSubmenuNewClass( struct libData *data );

Iclass *iupFillNewClass( struct libData *data );
Iclass *iupHboxNewClass( struct libData *data );
Iclass *iupVboxNewClass( struct libData *data );
Iclass *iupZboxNewClass( struct libData *data );
Iclass *iupCboxNewClass( struct libData *data );
Iclass *iupSboxNewClass( struct libData *data );
Iclass *iupNormalizerNewClass( struct libData *data );
Iclass *iupSplitNewClass( struct libData *data );
Iclass *iupScrollBoxNewClass( struct libData *data );
Iclass *iupFlatScrollBoxNewClass( struct libData *data );
Iclass *iupGridBoxNewClass( struct libData *data );
Iclass *iupExpanderNewClass( struct libData *data );
Iclass *iupDetachBoxNewClass( struct libData *data );
Iclass *iupBackgroundBoxNewClass( struct libData *data );
Iclass *iupAnimatedLabelNewClass( struct libData *data );
Iclass *iupCalendarNewClass( struct libData *data );
Iclass *iupDatePickNewClass( struct libData *data );
Iclass *iupParamBoxNewClass( struct libData *data );
Iclass *iupParamNewClass( struct libData *data );
Iclass *iupMultiBoxNewClass( struct libData *data );
Iclass *iupFlatListNewClass( struct libData *data );
Iclass *iupFlatValNewClass( struct libData *data );
Iclass *iupFlatTreeNewClass( struct libData *data );

Iclass *iupTimerNewClass( struct libData *data );
Iclass *iupImageNewClass( struct libData *data );
Iclass *iupImageRGBNewClass( struct libData *data );
Iclass *iupImageRGBANewClass( struct libData *data );
Iclass *iupUserNewClass( struct libData *data );
Iclass *iupClipboardNewClass( struct libData *data );

/*************************************************/

void iupdrvMessageDlgInitClass( struct libData *data, Iclass *ic );
void iupdrvColorDlgInitClass( struct libData *data, Iclass *ic );
void iupdrvFontDlgInitClass( struct libData *data, Iclass *ic );
void iupdrvFileDlgInitClass( struct libData *data, Iclass *ic );

/************************************************/

IUP_SDK_API Iclass *iupBackgroundBoxNewBaseClass(Iclass *ic_base );

/* Common definition of the canvas class */
typedef struct _iupCanvas {
  int sb;    /* scrollbar configuration, valid only after map, use iupBaseGetScrollbar before map */
  double posx, posy;
  int inside_resize;
} iupCanvas;

#ifdef __cplusplus
}
#endif

#endif
