/** \file
 * \brief Driver Information Functions
 *
 * See Copyright Notice in "iup.h"
 */
 
#ifndef __IUP_DRVINFO_H 
#define __IUP_DRVINFO_H

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup drvinfo Driver Information Interface 
 * \par
 * Each driver must export the symbols defined here. 
 * But in this case the functions are shared by different drivers in the same system.
 * \par
 * For example, the GTK driver and the Windows driver share the same implementation 
 * of these functions when the GTK driver is compiled in Windows. 
 * The GTK driver and the Motif driver share the same implementation 
 * of these functions when the GTK driver is compiled in UNIX. 
 * \par
 * See \ref iup_drvinfo.h 
 * \ingroup drv */


/** Retrieve the main desktop full size ( struct libData *data, size of the main monitor).
 * \ingroup drvinfo */
IUP_SDK_API void iupdrvGetFullSize( struct libData *data, int *width, int *height );

/** Retrieve the main desktop available size ( struct libData *data, full size less taskbar/menubar space).
 * \ingroup drvinfo */
IUP_SDK_API void iupdrvGetScreenSize( struct libData *data, int *width, int *height );

/** Adds the main desktop offset because of a taskbar/menubar positioning.
 * Only useful in Windows. In X-Windows the position of the origin 0,0 is already adjusted
 * to be after the taskbar/menubar.
 * \ingroup drvinfo */
IUP_SDK_API void iupdrvAddScreenOffset( struct libData *data, int *x, int *y, int add );

/** Retrieve the default desktop bits per pixel.
 * \ingroup drvinfo */
IUP_SDK_API int iupdrvGetScreenDepth( struct libData *data );

/** Retrieve the default desktop resolution in dpi ( struct libData *data, dots or pixels per inch).
 * \ingroup drvinfo */
IUP_SDK_API double iupdrvGetScreenDpi( struct libData *data );

/** Returns a string with the system version number.
 * \ingroup drvinfo */
IUP_SDK_API char *iupdrvGetSystemVersion( struct libData *data );

/** Returns a string with the system name.
 * \ingroup drvinfo */
IUP_SDK_API char *iupdrvGetSystemName( struct libData *data );

/** Returns a string with the computer name.
 * \ingroup drvinfo */
IUP_SDK_API char *iupdrvGetComputerName( struct libData *data );

/** Returns a string with the user name.
 * \ingroup drvinfo */
IUP_SDK_API char *iupdrvGetUserName( struct libData *data );

/** Returns the key state for Shift, Ctrl, Alt and sYs, in this order.
 * Left and right keys are considered.
 * Should declare "char key[5]".
 * Values could be space ( struct libData *data, " ") or "SCAY".
 * \ingroup drvinfo */
IUP_SDK_API void iupdrvGetKeyState( struct libData *data, char *key );

/** Returns the current position of the mouse cursor.
 * \ingroup drvinfo */
IUP_SDK_API void iupdrvGetCursorPos( struct libData *data, int *x, int *y );

/** Returns the driver "Display" in UNIX and NULL in Windows.
 * Must be implemented somewhere else.
 * \ingroup drvinfo */
IUP_SDK_API void *iupdrvGetDisplay( struct libData *data );

/** Returns the current locale name.
 * \ingroup drvinfo */
IUP_SDK_API char *iupdrvLocaleInfo( struct libData *data );

/** Returns the path to the preference directory.
 * Path will always have a trailing slash.
 * Return 1 on success, 0 on failure.
 * \ingroup drvinfo */
IUP_SDK_API int iupdrvGetPreferencePath( struct libData *data, char *filename, int use_system );

/** Changes the current directory.
* \ingroup drvinfo */
IUP_SDK_API int iupdrvSetCurrentDirectory( struct libData *data, const char *dir );

/** Returns the current directory.
* \ingroup drvinfo */
IUP_SDK_API char *iupdrvGetCurrentDirectory( struct libData *data );


#ifdef __cplusplus
}
#endif

#endif
