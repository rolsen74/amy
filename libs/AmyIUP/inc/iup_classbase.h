/** \file
 * \brief Base Class
 *
 * See Copyright Notice in "iup.h"
 */
 
#ifndef __IUP_CLASSBASE_H 
#define __IUP_CLASSBASE_H

#ifdef __cplusplus
extern "C" {
#endif


/** \defgroup iclassbase Base Class
 * \par
 * See \ref iup_classbase.h
 * \ingroup iclass
 */


/** Register all common base attributes: \n
 * WID                                   \n
 * SIZE, RASTERSIZE, POSITION            \n
 * FONT (and derived)                    \n\n
 * All controls that are positioned inside a dialog must register all common base attributes.
 * \ingroup iclassbase */
  IUP_SDK_API void iupBaseRegisterCommonAttrib( struct libData *data, Iclass *ic );

/** Register all visual base attributes: \n
 * VISIBLE, ACTIVE                       \n
 * ZORDER, X, Y                          \n
 * TIP (and derived)                     \n\n
 * All controls that are positioned inside a dialog must register all visual base attributes.
 * \ingroup iclassbase */
IUP_SDK_API void iupBaseRegisterVisualAttrib( struct libData *data, Iclass *ic );

/** Register all base callbacks: \n
* MAP_CB, UNMAP_CB, DESTROY_CB, LDESTROY_CB.
* \ingroup iclassbase */
IUP_SDK_API void iupBaseRegisterBaseCallbacks( struct libData *data, Iclass *ic );

/** Register all base and common callbacks: \n
* MAP_CB, UNMAP_CB, DESTROY_CB, LDESTROY_CB, GETFOCUS_CB, KILLFOCUS_CB, ENTERWINDOW_CB, LEAVEWINDOW_CB, K_ANY, HELP_CB.
* \ingroup iclassbase */
IUP_SDK_API void iupBaseRegisterCommonCallbacks( struct libData *data, Iclass *ic );

/* Register driver dependent common attributes. 
   Used only from iupBaseRegisterCommonAttrib */
IUP_SDK_API void iupdrvBaseRegisterCommonAttrib( struct libData *data, Iclass *ic );

/* Register driver dependent visual attributes. 
   Used only from iupBaseRegisterVisualAttrib */
IUP_SDK_API void iupdrvBaseRegisterVisualAttrib( struct libData *data, Iclass *ic );

/** Updates the expand member of the IUP object from the EXPAND attribute.
 * Should be called in the beginning of the ComputeNaturalSize for a container.
 * \ingroup iclassbase */
IUP_SDK_API void iupBaseContainerUpdateExpand( struct libData *data, Ihandle *ih );

/** Initializes the natural size using the user size, then
 * if a container then update the "expand" member from the EXPAND attribute, then
 * call \ref iupClassObjectComputeNaturalSize for containers if they have children or
 * call \ref iupClassObjectComputeNaturalSize for non-containers if user size is not defined.
 * Must be called for each children in the container. \n
 * First call is in iupLayoutCompute.
 * \ingroup iclassbase */
IUP_SDK_API void iupBaseComputeNaturalSize( struct libData *data, Ihandle *ih );

/** Update the current size from the available size, the natural size, expand and shrink.
 * Call \ref iupClassObjectSetChildrenCurrentSize for containers if they have children.
 * Must be called for each children in the container. \n
 * First call is in iupLayoutCompute.
 * \ingroup iclassbase */
IUP_SDK_API void iupBaseSetCurrentSize( struct libData *data, Ihandle *ih, int w, int h, int shrink );

/** Set the current position and update children position for containers.
 * Call \ref iupClassObjectSetChildrenPosition for containers if they have children.
 * Must be called for each children in the container. \n
 * First call is in iupLayoutCompute.
 * \ingroup iclassbase */
IUP_SDK_API void iupBaseSetPosition( struct libData *data, Ihandle *ih, int x, int y );

/* Updates the SIZE attribute if defined. 
   Called only from iupdrvSetFontAttrib. */
IUP_SDK_API void iupBaseUpdateAttribFromFont( struct libData *data, Ihandle *ih );


/** \defgroup iclassbasemethod Base Class Methods
 * \par
 * See \ref iup_classbase.h
 * \ingroup iclassbase
 */

/** Driver dependent \ref Iclass::LayoutUpdate method.
 * \ingroup iclassbasemethod */
IUP_SDK_API void iupdrvBaseLayoutUpdateMethod( struct libData *data, Ihandle *ih );

/** Driver dependent \ref Iclass::UnMap method.
 * \ingroup iclassbasemethod */
IUP_SDK_API void iupdrvBaseUnMapMethod( struct libData *data, Ihandle *ih );

/** Native type void \ref Iclass::Map method.
 * \ingroup iclassbasemethod */
IUP_SDK_API int iupBaseTypeVoidMapMethod( struct libData *data, Ihandle *ih );


/** \defgroup iclassbaseattribfunc Base Class Attribute Functions
 * \par
 * Used by the controls for iupClassRegisterAttribute. 
 * \par
 * See \ref iup_classbase.h
 * \ingroup iclassbase
 * @{
 */

/* common */
IUP_SDK_API char *iupBaseGetWidAttrib( struct libData *data, Ihandle *ih );
IUP_SDK_API int iupBaseSetNameAttrib( struct libData *data, Ihandle *ih, const char *value );
IUP_SDK_API int iupBaseSetRasterSizeAttrib( struct libData *data, Ihandle *ih, const char *value );
IUP_SDK_API int iupBaseSetSizeAttrib( struct libData *data, Ihandle *ih, const char *value );
IUP_SDK_API char *iupBaseGetSizeAttrib( struct libData *data, Ihandle *ih );
IUP_SDK_API char *iupBaseGetCurrentSizeAttrib( struct libData *data, Ihandle *ih );
IUP_SDK_API char *iupBaseGetRasterSizeAttrib( struct libData *data, Ihandle *ih );
IUP_SDK_API char *iupBaseGetClientOffsetAttrib( struct libData *data, Ihandle *ih );
IUP_SDK_API char *iupBaseGetClientSizeAttrib( struct libData *data, Ihandle *ih );
IUP_SDK_API char *iupBaseCanvasGetClientOffsetAttrib( struct libData *data, Ihandle *ih );
IUP_SDK_API char *iupBaseCanvasGetClientSizeAttrib( struct libData *data, Ihandle *ih );
IUP_SDK_API int iupBaseSetMaxSizeAttrib( struct libData *data, Ihandle *ih, const char *value );
IUP_SDK_API int iupBaseSetMinSizeAttrib( struct libData *data, Ihandle *ih, const char *value );
IUP_SDK_API char *iupBaseGetExpandAttrib( struct libData *data, Ihandle *ih );
IUP_SDK_API int iupBaseSetExpandAttrib( struct libData *data, Ihandle *ih, const char *value );

/* visual */
IUP_SDK_API char *iupBaseGetVisibleAttrib( struct libData *data, Ihandle *ih );
IUP_SDK_API int iupBaseSetVisibleAttrib( struct libData *data, Ihandle *ih, const char *value );
IUP_SDK_API char *iupBaseGetActiveAttrib( struct libData *data, Ihandle *ih );
IUP_SDK_API int iupBaseSetActiveAttrib( struct libData *data, Ihandle *ih, const char *value );
IUP_SDK_API int iupdrvBaseSetZorderAttrib( struct libData *data, Ihandle *ih, const char *value );
IUP_SDK_API int iupdrvBaseSetTipAttrib( struct libData *data, Ihandle *ih, const char *value );
IUP_SDK_API int iupdrvBaseSetTipVisibleAttrib( struct libData *data, Ihandle *ih, const char *value );
IUP_SDK_API char *iupdrvBaseGetTipVisibleAttrib( struct libData *data, Ihandle *ih );
IUP_SDK_API int iupdrvBaseSetBgColorAttrib( struct libData *data, Ihandle *ih, const char *value );
IUP_SDK_API int iupdrvBaseSetFgColorAttrib( struct libData *data, Ihandle *ih, const char *value );
IUP_SDK_API char *iupBaseNativeParentGetBgColorAttrib( struct libData *data, Ihandle *ih );
IUP_SDK_API int iupBaseSetCPaddingAttrib( struct libData *data, Ihandle *ih, const char *value );
IUP_SDK_API char *iupBaseGetCPaddingAttrib( struct libData *data, Ihandle *ih );
IUP_SDK_API int iupBaseSetCSpacingAttrib( struct libData *data, Ihandle *ih, const char *value );
IUP_SDK_API char *iupBaseGetCSpacingAttrib( struct libData *data, Ihandle *ih );

/* other */
IUP_SDK_API char *iupBaseContainerGetExpandAttrib( struct libData *data, Ihandle *ih );
IUP_SDK_API int iupdrvBaseSetCursorAttrib( struct libData *data, Ihandle *ih, const char *value );

/* drag&drop */
IUP_SDK_API void iupdrvRegisterDragDropAttrib( struct libData *data, Iclass *ic );

/* util */
IUP_SDK_API int iupBaseNoSaveCheck( struct libData *data, Ihandle *ih, const char *name );


/** @} */



/** \defgroup iclassbaseutil Base Class Utilities
 * \par
 * See \ref iup_classbase.h
 * \ingroup iclassbase
 * @{
 */

#define iupMAX(_a,_b) ((_a)>(_b)?(_a):(_b))
#define iupMIN(_a,_b) ((_a)<(_b)?(_a):(_b))
#define iupROUND(_x) ((int)((_x)>0? (_x)+0.5: (_x)-0.5))
IUP_SDK_API int     iupRound( struct libData *data, double x );

#define iupCOLOR8TO16(_x) ((unsigned short)(_x*257))  
#define iupCOLOR16TO8(_x) ((unsigned char)(_x/257))   /* 65535/257 = 255 */

#define iupBYTECROP(_x)   ((unsigned char)((_x)<0?0:((_x)>255)?255:(_x)))

enum{IUP_ALIGN_ALEFT, IUP_ALIGN_ACENTER, IUP_ALIGN_ARIGHT};
#define IUP_ALIGN_ABOTTOM IUP_ALIGN_ARIGHT
#define IUP_ALIGN_ATOP IUP_ALIGN_ALEFT

enum{IUP_SB_NONE, IUP_SB_HORIZ, IUP_SB_VERT};
IUP_SDK_API int iupBaseGetScrollbar( struct libData *data, Ihandle *ih );

IUP_SDK_API char *iupBaseNativeParentGetBgColor( struct libData *data, Ihandle *ih );
IUP_SDK_API void iupBaseCallValueChangedCb( struct libData *data, Ihandle *ih );

/** @} */


#ifdef __cplusplus
}
#endif

#endif
