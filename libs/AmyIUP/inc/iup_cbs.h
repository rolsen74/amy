/** \file
 * \brief Contains all function pointer typedefs.
 *
 * See Copyright Notice in "iup.h"
 */

/* rwo note : I renamed the file iupcbs.h to iup_cbs.h */

#ifndef __IUPCBS_H 
#define __IUPCBS_H

struct _cdCanvas;

typedef int  (*IFidle)(void );  /* idle */
typedef void (*IFentry)(void );  /* entry */

typedef void (*IFi)(int ); /* globalentermodal_cb, globalleavemodal_cb,  */
typedef void (*IFs)(char *);  /* openurl_cb */
typedef void (*IFii)(int, int ); /* globalkeypress_cb */
typedef void (*IFiis)(int, int, char *);  /* globalmotion_cb, openfiles_cb */
typedef void (*IFiiiis)(int, int, int, int, char *);  /* globalbutton_cb */
typedef void (*IFfiis)(float,int,int,char *);  /* globalwheel_cb */
typedef void (*IFvs)(void*, char *);  /* handleadd_cb, handleremove_cb, imagecreate_cb, imagedestroy_cb */

typedef int (*IFn)(struct libData *, Ihandle*);  /* default definition, same as Icallback */
typedef int (*IFni)(struct libData *, Ihandle*, int );   /* k_any, show_cb, toggle_action, spin_cb, branchopen_cb, branchclose_cb, executeleaf_cb, showrename_cb, rightclick_cb, extended_cb, height_cb, width_cb */
typedef int (*IFnii)(struct libData *, Ihandle*, int, int );  /* resize_cb, caret_cb, matrix_mousemove_cb, enteritem_cb, leaveitem_cb, scrolltop_cb, dropcheck_cb, selection_cb, select_cb, switch_cb, scrolling_cb, vspan_cb, hspan_cb */
typedef int (*IFniii)(struct libData *, Ihandle*, int, int, int ); /* trayclick_cb, edition_cb */
typedef int (*IFniiii)(struct libData *, Ihandle*, int, int, int, int ); /* dragdrop_cb */
typedef int (*IFniiiiiiC)(struct libData *, Ihandle*, int, int, int, int, int, int, struct _cdCanvas* );  /* draw_cb */
typedef int (*IFniiiiii)(struct libData *, Ihandle*, int, int, int, int, int, int );  /* OLD draw_cb */
typedef int (*IFnsidv)(struct libData *, Ihandle*, char*, int, double, void* ); /* postmessage_cb */

typedef int (*IFnff)(struct libData *, Ihandle*, float, float );    /* canvas_action */
typedef int (*IFniff)(struct libData *, Ihandle*,int,float,float );  /* scroll_cb */
typedef int (*IFnfiis)(struct libData *, Ihandle*,float,int,int,char *);  /* wheel_cb */

typedef int (*IFnsVi)(struct libData *, Ihandle*, char*, void*, int );  /* dragdata_cb */
typedef int (*IFnsViii)(struct libData *, Ihandle*, char*, void*, int, int, int );  /* dropdata_cb */
typedef int (*IFnsiii)(struct libData *, Ihandle*, char*, int, int, int );  /* dropfiles_cb */
typedef int (*IFnssi)(struct libData *, Ihandle*, char*, char*, int );  /* dragfilecreatename_cb */

typedef int (*IFnnii)(struct libData *, Ihandle*, Ihandle*, int, int ); /* drop_cb */
typedef int (*IFnn)(struct libData *, Ihandle*, Ihandle *); /* savemarkers_cb, restoremarkers_cb */
typedef int (*IFnnn)(struct libData *, Ihandle*, Ihandle*, Ihandle *); /* tabchange_cb */
typedef int (*IFnss)(struct libData *, Ihandle*, char *, char * );  /* file_cb */
typedef int (*IFns)(struct libData *, Ihandle*, char * );  /* multiselect_cb */
typedef int (*IFnsi)(struct libData *, Ihandle*, char *, int );  /* copydata_cb */
typedef int (*IFnis)(struct libData *, Ihandle*, int, char * );  /* text_action, multiline_action, edit_cb, rename_cb */
typedef int (*IFnsii)(struct libData *, Ihandle*, char*, int, int );  /* list_action */
typedef int (*IFniis)(struct libData *, Ihandle*, int, int, char *);  /* motion_cb, click_cb, value_edit_cb */
typedef int (*IFniiis)(struct libData *, Ihandle*, int, int, int, char *);  /* touch_cb, dblclick_cb */
typedef int (*IFniiiis)(struct libData *, Ihandle*, int, int, int, int, char *);  /* button_cb, matrix_action, mousemotion_cb */
typedef int (*IFniiiiiis)(struct libData *, Ihandle*, int, int, int, int, int, int, char *);  /* mouseclick_cb */

typedef int (*IFnIi)(struct libData *, Ihandle*, int*, int ); /* multiselection_cb, multiunselection_cb */
typedef int (*IFnd)(struct libData *, Ihandle*, double );  /* mousemove_cb, button_press_cb, button_release_cb */
typedef int (*IFniiIII)(struct libData *, Ihandle*, int, int, int*, int*, int* ); /* fgcolor_cb, bgcolor_cb */
typedef int (*IFniinsii)(struct libData *, Ihandle*, int, int, Ihandle*, char*, int, int ); /* dropselect_cb */
typedef int (*IFnccc)(struct libData *, Ihandle*, unsigned char, unsigned char, unsigned char ); /* drag_cb, change_cb */
typedef int (*IFniIIII)(struct libData *, Ihandle*, int, int*, int*, int*, int* ); /* multitouch_cb */

typedef int (*IFnC)(struct libData *, Ihandle*, struct _cdCanvas* ); /* postdraw_cb, predraw_cb */
typedef int (*IFniidd)(struct libData *, Ihandle*, int, int, double, double ); /* delete_cb */
typedef int (*IFniiddi)(struct libData *, Ihandle*, int, int, double, double, int ); /* select_cb */
typedef int (*IFniiddiddi)(struct libData *, Ihandle*, int, int, double, double, int, double, double, int ); /* clicksegment_cb */
typedef int (*IFniidds)(struct libData *, Ihandle*, int, int, double, double, char *);  /* plotbutton_cb */
typedef int (*IFndds)(struct libData *, Ihandle*, double, double, char *);    /* plotmotion_cb */
typedef int (*IFnssds)(struct libData *, Ihandle*, char*, char*, double, char *); /* plottickformat_cb */
typedef int (*IFnni)(struct libData *, Ihandle*, Ihandle*, int );

typedef char *(*sIFnii)(struct libData *, Ihandle*, int, int );  /* value_cb, font_cb */
typedef char *(*sIFni)(struct libData *, Ihandle*, int );  /* cell_cb */
typedef char *(*sIFniis)(struct libData *, Ihandle*, int, int, char *);  /* translatevalue_cb */

typedef double (*dIFnii)(struct libData *, Ihandle*, int, int );  /* numericgetvalue_cb */
typedef int    (*IFniid)(struct libData *, Ihandle*, int, int, double );  /* numericsetvalue_cb */

typedef void (*IFniiv)(struct libData *, Ihandle*, int, int, void* );  /* android_onactivityresult_cb */

#endif
