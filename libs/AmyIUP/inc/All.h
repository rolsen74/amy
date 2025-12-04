
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#ifndef AMYLIB_ALL_H
#define AMYLIB_ALL_H

// --

#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/AmyIUP.h>
#include <proto/AmyCLib.h>

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <setjmp.h>

struct libData;
struct _InativeHandle
{
	// aos4 imeplement me
	int dummy;
};	

#include "iup_array.h"
#include "iup_assert.h"
#include "iup_attrib.h"
#include "iup_cbs.h"
#include "iup_class.h"
#include "iup_classbase.h"
#include "iup_dlglist.h"
#include "iup_drv.h"
#include "iup_drvdraw.h"
#include "iup_drvfont.h"
#include "iup_drvinfo.h"
#include "iup_draw.h"		// Place after drvdraw.h
#include "iup_frame.h"
#include "iup_focus.h"
#include "iup_image.h"
#include "iup_key.h"
#include "iup_layout.h"
#include "iup_ledlex.h"
#include "iup_mask.h"
#include "iup_maskmatch.h"
#include "iup_maskparse.h"
#include "iup_menu.h"
#include "iup_object.h"
#include "iup_dialog.h"		// Place after object.h
#include "iup_register.h"
#include "iup_str.h"
#include "iup_stdcontrols.h"
#include "iup_table.h"
#include "iup_timer.h"

// include those in each gadget
// #include "iup_box.h"
// #include "iup_button.h"
// #include "iup_canvas.h"
// #include "iup_dialog.h"
// #include "iup_label.h"
// #include "iup_list.h"
// #include "iup_tabs.h"
// #include "iup_text.h"
// #include "iup_toggle.h"
// #include "iup_tree.h"
// #include "iup_val.h"

// --

#define LIBNAME				"AmyIUP.library"
#define VERSION				1
#define REVISION			1
#define DATE				"1.1.2025"
#define VERS				"AmyIUP.library 1.1"
#define VSTRING				"AmyIUP.library 1.1 (22.11.2025)\r\n"
#define VERSTAG				"\0$VER: AmyIUP.library 1.1 (22.11.2025)"

// --

struct libBase
{
	struct Library			lib_Base;
	U16						lib_Pad;
	PTR						lib_SegList;
};

// --

struct libData
{
	struct AmyIUPIFace *	IFace;

	Itable *				ifunc_table;
	Itable *				istock_table;
	Itable *				iglobal_table;
	Itable *				inames_strtable;
	Itable *				iregister_table;
	Itable *				istrmessage_table;
	const char *			ikey_map_ext[256];

	S8						iup_opened;
};

// --

extern const struct TagItem Main_Tags[];

void ROMFree( struct libBase *libBase );

U32	AMY_FUNC _manager_Obtain( struct LibraryManagerInterface *Self );
U32	AMY_FUNC _manager_Release( struct LibraryManagerInterface *Self );
PTR	AMY_FUNC _manager_Open( struct LibraryManagerInterface *Self, U32 version );
PTR AMY_FUNC _manager_Close( struct LibraryManagerInterface *Self );
PTR	AMY_FUNC _manager_Expunge( struct LibraryManagerInterface *Self );

U32	AMY_FUNC _Main_Obtain( struct AmyIUPIFace *Self );
U32	AMY_FUNC _Main_Release( struct AmyIUPIFace *Self );
PTR AMY_FUNC _Main_Clone( struct AmyIUPIFace *Self );
U32	AMY_FUNC _Main_Expunge( struct AmyIUPIFace *Self );

void AMY_FUNC _Main_IupClose( struct AmyIUPIFace *Self );
int	AMY_FUNC _Main_IupMainLoop( struct AmyIUPIFace *Self );
int	AMY_FUNC _Main_IupOpen( struct AmyIUPIFace *Self, int *argc, char ***argv );
void AMY_FUNC _Main_IupSetGlobal( struct AmyIUPIFace *Self, const char *name, const char *value );

// iup amiga specfic
//void				iupdrvTabsInitClass( struct libData *data, Iclass *ic );
//void				iupdrvToggleInitClass( struct libData *data, Iclass *ic );
//void				iupdrvTreeInitClass( struct libData *data, Iclass *ic );
//void				iupdrvValInitClass( struct libData *data, Iclass *ic );

IUP_API Ihandle *	amy_IupCalendar( struct libData *data );
IUP_API int			amy_IupLoopStep( struct libData *data );
IUP_API int			amy_IupLoopStepWait( struct libData *data );
IUP_API int			amy_IupMainLoop( struct libData *data );
IUP_API int			amy_IupMainLoopLevel( struct libData *data );
IUP_API void		amy_IupExitLoop( struct libData *data );
IUP_API void		amy_IupFlush( struct libData *data );
IUP_API char *		amy_IupVersion( struct libData *data );
IUP_API void		amy_IupVersionShow( struct libData *data );
IUP_API char *		amy_IupVersionDate( struct libData *data );
IUP_API char *		amy_IupVersionNumber( struct libData *data );

// iup_attrib
IUP_API void		amy_IupStoreAttribute( struct libData *data, Ihandle *ih, const char *name, const char *value );
IUP_API void		amy_IupStoreAttributeId( struct libData *data, Ihandle *ih, const char *name, int id, const char *value );
IUP_API void		amy_IupStoreAttributeId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, const char *value );
IUP_API int			amy_IupGetAllAttributes( struct libData *data, Ihandle *ih, char** names, int n );
IUP_API char *		amy_IupGetAttribute( struct libData *data, Ihandle *ih, const char *name );
IUP_API char *		amy_IupGetAttributeId( struct libData *data, Ihandle *ih, const char *name, int id );
IUP_API char *		amy_IupGetAttributeId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col );
IUP_API Ihandle *	amy_IupGetAttributeHandle( struct libData *data, Ihandle *ih, const char *name );
IUP_API int			amy_IupGetInt( struct libData *data, Ihandle *ih, const char *name );
IUP_API int			amy_IupGetInt2( struct libData *data, Ihandle *ih, const char *name );
IUP_API int			amy_IupGetIntId( struct libData *data, Ihandle *ih, const char *name, int id );
IUP_API int			amy_IupGetIntInt( struct libData *data, Ihandle *ih, const char *name, int *i1, int *i2 );
IUP_API double		amy_IupGetDouble( struct libData *data, Ihandle *ih, const char *name );
IUP_API void		amy_IupSetStrf( struct libData *data, Ihandle *ih, const char *name, const char *f, ... );
IUP_API void		amy_IupSetStrAttribute( struct libData *data, Ihandle *ih, const char *name, const char *value );
IUP_API void		amy_IupSetStrAttributeId( struct libData *data, Ihandle *ih, const char *name, int id, const char *value );
IUP_API void		amy_IupSetAttribute( struct libData *data, Ihandle *ih, const char *name, const char *value );
IUP_API Ihandle *	amy_IupSetAttributes( struct libData *data, Ihandle *ih, const char *str );
IUP_API void		amy_IupSetAttributeId( struct libData *data, Ihandle *ih, const char *name, int id, const char *value );
IUP_API void		amy_IupSetAttributeHandle( struct libData *data, Ihandle *ih, const char *name, Ihandle *ih_named );
IUP_API void		amy_IupSetAttributeHandleId( struct libData *data, Ihandle *ih, const char *name, int id, Ihandle *ih_named );
IUP_API void		amy_IupSetInt( struct libData *data, Ihandle *ih, const char *name, int num );
IUP_API void		amy_IupSetIntId( struct libData *data, Ihandle *ih, const char *name, int id, int num );
IUP_API void		amy_IupSetfAttribute( struct libData *data, Ihandle *ih, const char *name, const char *f, ... );
IUP_API void		amy_IupSetfAttributeId( struct libData *data, Ihandle *ih, const char *name, int id, const char *f, ... );
IUP_API void		amy_IupSetRGBId( struct libData *data, Ihandle *ih, const char *name, int id, unsigned char r, unsigned char g, unsigned char b );
IUP_API int			amy_IupConvertXYToPos( struct libData *data, Ihandle *ih, int x, int y );
IUP_API void		amy_IupSetDouble( struct libData *data, Ihandle *ih, const char *name, double num );
IUP_API Ihandle *	amy_IupSetAtt( struct libData *data, const char *handle_name, Ihandle *ih, const char *name, ... );

// iup_box
Iclass *			iupBoxNewClassBase( struct libData *data );

// iup_button
IUP_API Ihandle *	amy_IupButton( struct libData *data, const char *title, const char *action );

// iup_callback
IUP_API Ihandle *	amy_IupSetCallbacks( struct libData *data, Ihandle *ih, const char *name, Icallback func, ... );
IUP_API Icallback	amy_IupSetCallback( struct libData *data, Ihandle *ih, const char *name, Icallback func );
IUP_API Icallback	amy_IupGetCallback( struct libData *data, Ihandle *ih, const char *name );
char *				iupGetCallbackName( struct libData *data, Ihandle *ih, const char *name );

// iup_canvas
IUP_API Ihandle *	amy_IupCanvas( struct libData *data, const char *action );

// iup_childtree
IUP_API void		amy_IupDetach( struct libData *data, Ihandle *child );
IUP_API Ihandle *	amy_IupAppend( struct libData *data, Ihandle *parent, Ihandle *child );
IUP_API Ihandle *	amy_IupInsert( struct libData *data, Ihandle *parent, Ihandle *ref_child, Ihandle *child );
IUP_API int			amy_IupReparent( struct libData *data, Ihandle *child, Ihandle *parent, Ihandle *ref_child );
IUP_API Ihandle *	amy_IupGetChild( struct libData *data, Ihandle *ih, int pos );
IUP_API int			amy_IupGetChildPos( struct libData *data, Ihandle *ih, Ihandle *child );
IUP_API int			amy_IupGetChildCount( struct libData *data, Ihandle *ih );
IUP_API Ihandle *	amy_IupGetParent( struct libData *data, Ihandle *ih );
IUP_API Ihandle *	amy_IupGetDialog( struct libData *data, Ihandle *ih );
IUP_API Ihandle *	amy_IupGetBrother( struct libData *data, Ihandle *ih );
IUP_SDK_API int		iupChildTreeIsParent( struct libData *data, Ihandle *ih, Ihandle *parent );
IUP_SDK_API Ihandle*iupChildTreeGetPrevBrother( struct libData *data, Ihandle *ih );
IUP_SDK_API Ihandle*iupChildTreeGetNativeParent( struct libData *data, Ihandle *ih );
IUP_SDK_API void	iupChildTreeAppend( struct libData *data, Ihandle *parent, Ihandle *child );

// iup_class
IUP_API int			amy_IupClassMatch( struct libData *data, Ihandle *ih, const char *classname );
IUP_API char *		amy_IupGetClassName( struct libData *data, Ihandle *ih );

// iup_classattrib
IUP_API int			amy_IupGetClassAttributes( struct libData *data, const char *classname, char** names, int n );
IUP_API int			amy_IupGetClassCallbacks( struct libData *data, const char *classname, char** names, int n );
IUP_API void		amy_IupSaveClassAttributes( struct libData *data, Ihandle *ih );
IUP_API void		amy_IupCopyClassAttributes( struct libData *data, Ihandle *src_ih, Ihandle *dst_ih );

// iup_classbase
IUP_API Ihandle *	amy_IupGetDialogChild( struct libData *data, Ihandle *ih, const char *name );

// iup_colorbar
IUP_API Ihandle *	amy_IupColorbar( struct libData *data );

// iup_colorbrowser
IUP_API Ihandle *	amy_IupColorBrowser( struct libData *data );

// iup_colordlg
IUP_API Ihandle *	amy_IupColorDlg( struct libData *data );

// iup_colorhsi
int					iupStrToHSI( const char *str, double *h, double *s, double *i );
void				iupColorHSI2RGB( double h, double s, double i, unsigned char *r, unsigned char *g, unsigned char *b );
void				iupColorRGB2HSI( unsigned char r, unsigned char g, unsigned char b, double *h, double *s, double *i );

// iup_datepick
IUP_API Ihandle *	amy_IupDatePick( struct libData *data );

// iup_dialog
IUP_API Ihandle *	amy_IupDialog( struct libData *data, Ihandle *child );
void				iupDialogGetDecorSize( struct libData *data, Ihandle *ih, int *decorwidth, int *decorheight );
char *				iupDialogGetChildIdStr( struct libData *data, Ihandle *ih );

// iup_draw
IUP_API void		amy_IupDrawEnd( struct libData *data, Ihandle *ih );
IUP_API void		amy_IupDrawArc( struct libData *data, Ihandle *ih, int x1, int y1, int x2, int y2, double a1, double a2 );
IUP_API void		amy_IupDrawLine( struct libData *data, Ihandle *ih, int x1, int y1, int x2, int y2 );
IUP_API void		amy_IupDrawBegin( struct libData *data, Ihandle *ih );
IUP_API void		amy_IupDrawImage( struct libData *data, Ihandle *ih, const char *name, int x, int y, int w, int h );
IUP_API void		amy_IupDrawGetSize( struct libData *data, Ihandle *ih, int *w, int *h );
IUP_API void		amy_IupDrawFocusRect( struct libData *data, Ihandle *ih, int x1, int y1, int x2, int y2 );
IUP_API void		amy_IupDrawRectangle( struct libData *data, Ihandle *ih, int x1, int y1, int x2, int y2 );
IUP_API void		amy_IupDrawParentBackground( struct libData *data, Ihandle *ih );

// iup_elemprodpdlg
IUP_API Ihandle *	amy_IupElementPropertiesDialog( struct libData *data, Ihandle *parent, Ihandle *elem );

// iup_export
IUP_SDK_API int		iupImageExportToFile( struct libData *data, Ihandle *ih, FILE *packfile, const char *format, const char *p_name );
IUP_SDK_API void	iupLayoutExportNamedElemList( struct libData *data, FILE *file, Ihandle* *named_elem, int count, int export_format, int saved_info );

// iup_file
IUP_API Ihandle *	amy_IupFileDlg( struct libData *data );

// iup_fill
IUP_API Ihandle *	amy_IupFill( struct libData *data );

// iup_flatseparator
IUP_API Ihandle *	amy_IupFlatSeparator( struct libData *data );

// iup_flattoggle
IUP_API Ihandle *	amy_IupFlatToggle( struct libData *data, const char *title );

// iup_focus
IUP_API Ihandle *	amy_IupGetFocus( struct libData *data );
IUP_API Ihandle *	amy_IupSetFocus( struct libData *data, Ihandle *ih );
IUP_API Ihandle *	amy_IupNextField( struct libData *data, Ihandle *ih );
IUP_API Ihandle *	amy_IupPreviousField( struct libData *data, Ihandle *ih );

// iup_fontdlg
IUP_API Ihandle *	amy_IupFontDlg( struct libData *data );

// iup_frame
IUP_API Ihandle *	amy_IupFrame( struct libData *data, Ihandle *child );

// iup_func
IUP_API Icallback	amy_IupGetFunction( struct libData *data, const char *name );
IUP_API Icallback	amy_IupSetFunction( struct libData *data, const char *name, Icallback func );
void				iupFuncInit( struct libData *data );
void				iupFuncFinish( struct libData *data );
int					iupGetFunctions( struct libData *data, char **names, int n );

// iup_getparam
IUP_API Ihandle *	amy_IupParam( struct libData *data, const char *format );
IUP_API Ihandle *	amy_IupParamBoxv( struct libData *data, Ihandle **children );
IUP_API int			amy_IupGetParam( struct libData *data, const char *title, Iparamcb action, void* user_data, const char *format, ... );

// iup_globaldlg
IUP_API Ihandle *	amy_IupGlobalsDialog( struct libData *data );

// iup_globalattrib
IUP_API char *		amy_IupGetGlobal( struct libData *data, const char *name );
IUP_API void		amy_IupSetGlobal( struct libData *data, const char *name, const char *value );
IUP_API void		amy_IupSetStrGlobal( struct libData *data, const char *name, const char *value );
IUP_API void		amy_IupStoreGlobal( struct libData *data, const char *name, const char *value );
int					iupGlobalDefaultColorChanged( struct libData *data, const char *name );
void				iupGlobalAttribFinish( struct libData *data );
IUP_SDK_API int		iupGlobalIsPointer( struct libData *data, const char *name );
void				iupStrMessageUpdateLanguage( struct libData *data, const char *language );
int					iupGetGlobalAttributes( struct libData *data, char **names, int n );
void				iupGlobalAttribInit( struct libData *data );

// iup_hbox
IUP_API Ihandle *	amy_IupHbox( struct libData *data, Ihandle *child, ... );

// iup_help
IUP_API int			amy_IupHelp( struct libData *data, const char *url );

// iup_image
IUP_API Ihandle *	amy_IupImageRGB( struct libData *data, int width, int height, const unsigned char *imgdata );
IUP_API Ihandle *	amy_IupImageRGBA( struct libData *data, int width, int height, const unsigned char *imgdata );
IUP_API Ihandle *	amy_IupImage( struct libData *data, int width, int height, const unsigned char *imgdata );

// iup_key

// iup_label
IUP_API Ihandle *	amy_IupLabel( struct libData *data, const char *title );

// iup_layout
IUP_API void		amy_IupUpdate( struct libData *data, Ihandle *ih );
IUP_API void		amy_IupRedraw( struct libData *data, Ihandle *ih, int children );
IUP_API void		amy_IupRefresh( struct libData *data, Ihandle *ih );
IUP_API void		amy_IupRefreshChildren( struct libData *data, Ihandle *ih );

// iup_layoutdlg
IUP_API Ihandle *	amy_IupLayoutDialog( struct libData *data, Ihandle *dialog );

// iup_list
IUP_API Ihandle *	amy_IupList( struct libData *data, const char *action );

// iup_mask
IUP_SDK_API Imask *	iupMaskCreateReal( struct libData *data, int positive, const char* decimal_symbol );

// iup_names
IUP_API Ihandle *	amy_IupGetHandle( struct libData *data, const char *name );
IUP_API Ihandle *	amy_IupSetHandle( struct libData *data, const char *name, Ihandle *ih );
IUP_API char *		amy_IupGetName( struct libData *data, Ihandle *ih );
IUP_API int			amy_IupGetAllNames( struct libData *data, char **names, int n );
void				iupRemoveNames( struct libData *data, Ihandle *ih );
int					iupNamesFindAll( struct libData *data, Ihandle *ih, char **names, int n );
void				iupNamesDestroyHandles( struct libData *data );
void				iupNamesFinish( struct libData *data );
void				iupNamesInit( struct libData *data );

// iup_menu
IUP_API Ihandle *	amy_IupMenu( struct libData *data, Ihandle *child, ... );
IUP_API Ihandle *	amy_IupItem( struct libData *data, const char *title, const char *action );
IUP_API Ihandle *	amy_IupSubmenu( struct libData *data, const char *title, Ihandle *child );
IUP_API Ihandle *	amy_IupSeparator( struct libData *data );

// iup_messagedlg
IUP_API void		amy_IupMessage( struct libData *data, const char *title, const char *message );
IUP_API void		amy_IupMessagef( struct libData *data, const char *title, const char *format, ... );
IUP_API Ihandle *	amy_IupMessageDlg( struct libData *data );
IUP_API int			amy_IupMessageAlarm( struct libData *data, Ihandle *parent, const char *title, const char *message, const char *buttons );
IUP_API void		amy_IupMessageError( struct libData *data, Ihandle *parent, const char *message );

// iup_normalizer
IUP_API Ihandle *	amy_IupNormalizer( struct libData *data, Ihandle *ih_first, ... );
IUP_API Ihandle *	amy_IupNormalizerv( struct libData *data, Ihandle **ih_list );
void				iupNormalizeSizeBoxChild( struct libData *data, Ihandle *ih, int normalize, int children_natural_maxwidth, int children_natural_maxheight );
int					iupNormalizeGetNormalizeSize( struct libData *data, const char *value );
char *				iupNormalizeGetNormalizeSizeStr( struct libData *data, int normalize );

// iup_object
IUP_API Ihandle *	amy_IupCreate( struct libData *data, const char *name );
IUP_API Ihandle *	amy_IupCreatev( struct libData *data, const char *name, void **params );
IUP_API Ihandle *	amy_IupCreateV( struct libData *data, const char *name, void *first, va_list arglist );
IUP_API void		amy_IupDestroy( struct libData *data, Ihandle *ih );

// iup_open
IUP_API int			amy_IupOpen( struct libData *data, int *argc, char ***argv );
IUP_API void		amy_IupClose( struct libData *data );

// iup_predialogs
IUP_API int			amy_IupListDialog( struct libData *data, int type, const char *title, int size, const char **list_str,
					int op, int max_col, int max_lin, int *marks );
IUP_API int			amy_IupGetText( struct libData *data, const char *title, char *text, int maxsize );

// iup_radio
IUP_API Ihandle *	amy_IupRadio( struct libData *data, Ihandle *child );

// iup_register
IUP_API int			amy_IupGetAllClasses( struct libData *data, char** list, int n );

// iup_show
IUP_API int			amy_IupMap( struct libData *data, Ihandle *ih );
IUP_API void		amy_IupUnmap( struct libData *data, Ihandle *ih );
IUP_API int			amy_IupShow( struct libData *data, Ihandle *ih );
IUP_API int			amy_IupShowXY( struct libData *data, Ihandle *ih, int x, int y );
IUP_API int			amy_IupHide( struct libData *data, Ihandle *ih );
IUP_API int			amy_IupPopup( struct libData *data, Ihandle *ih, int x, int y );

// iup_split
IUP_API Ihandle *	amy_IupSplit( struct libData *data, Ihandle * child1, Ihandle *child2 );

// iup_str
IUP_SDK_API char *	amy_iupStrReturnUInt( struct libData *data, unsigned int i );
IUP_SDK_API char *	amy_iupStrReturnInt( struct libData *data, int i );
IUP_SDK_API int		amy_iupStrCompare( struct libData *data, const char *l, const char *r, int casesensitive, int utf8 );

// iup_strmessage
IUP_API void		amy_IupSetLanguage( struct libData *data, const char *language );
IUP_API char *		amy_IupGetLanguageString( struct libData *data, const char *name );
IUP_API void		amy_IupSetLanguageString( struct libData *data, const char *name, const char *str );
void				iupStrMessageInit( struct libData *data );
void				iupStrMessageFinish( struct libData *data );

// iup_table

// iup_tabs
IUP_API Ihandle *	amy_IupTabs( struct libData *data, Ihandle *child, ... );

// iup_text
IUP_API Ihandle *	amy_IupText( struct libData *data, const char *action );
IUP_API Ihandle *	amy_IupMultiLine( struct libData *data, const char *action );

// iup_timer
IUP_API Ihandle *	amy_IupTimer( struct libData *data );

// iup_toggle
IUP_API Ihandle *	amy_IupToggle( struct libData *data, const char *title, const char *action );

// iup_tree
IUP_API Ihandle *	amy_IupTree( struct libData *data );
IUP_API int			amy_IupTreeGetId( struct libData *data, Ihandle *ih, void *userdata );
IUP_API void *		amy_IupTreeGetUserId( struct libData *data, Ihandle *ih, int id );
IUP_API int			amy_IupTreeSetUserId( struct libData *data, Ihandle *ih, int id, void *userdata );

// iup_user
IUP_API Ihandle *	amy_IupUser( struct libData *data );

// iup_val
IUP_API Ihandle *	amy_IupVal( struct libData *data, const char *orientation );

// iup_vbox
IUP_API Ihandle *	amy_IupVbox( struct libData *data, Ihandle *child, ... );

// --

#endif
