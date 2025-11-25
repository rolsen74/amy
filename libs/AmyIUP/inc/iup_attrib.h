/** \file
 * \brief Attributes Environment Management
 *
 * See Copyright Notice in "iup.h"
 */
 
#ifndef __IUP_ATTRIB_H 
#define __IUP_ATTRIB_H

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup attrib Attribute Environment 
 * \par
 * When attributes are not stored at the control  
 * they are stored in a hash table (see \ref table).
 * \par
 * As a general rule use:
 * - IupGetAttribute, IupSetAttribute, ... : when care about control implementation, hash table, inheritance and default value
 * - iupAttribGetStr,Int,Float: when care about inheritance, hash table and default value
 * - iupAttribGet,... : ONLY access the hash table
 * These different functions have very different performances and results. So use them wiselly.
 * \par
 * See \ref iup_attrib.h 
 * \ingroup cpi */


/** Returns true if the attribute name if in the internal format "_IUP...".
 * \ingroup attrib */
#define iupATTRIB_ISINTERNAL(_name) ((_name[0] == '_' && _name[1] == 'I' && _name[2] == 'U' && _name[3] == 'P')? 1: 0)

/** Returns true if the attribute name is a known pointer. \n
 * \ingroup attrib */
IUP_SDK_API int iupAttribIsNotString( struct libData *data, Ihandle *ih, const char *name );

/** Returns true if the attribute name is a known Ihandle*. \n
* \ingroup attrib */
IUP_SDK_API int iupAttribIsIhandle( struct libData *data, Ihandle *ih, const char *name );



/** Sets the attribute only in the hash table as a pointer. \n
 * Only generic pointers and constant strings can be set as value. \n
 * It ignores children.
 * \ingroup attrib */
IUP_SDK_API void iupAttribSet( struct libData *data, Ihandle *ih, const char *name, const char *value );

/** Sets the attribute only in the hash table as a string. \n 
 * The string is internally duplicated. \n
 * It ignores children.
 * \ingroup attrib */
IUP_SDK_API void iupAttribSetStr( struct libData *data, Ihandle *ih, const char *name, const char *value );

/** Sets the attribute only in the hash table as a string. \n 
 * Use same format as sprintf. \n
 * It ignores children. \n
 * This is not supposed to be used for very large strings,
 * just for combinations of numeric data or constant strings.
 * \ingroup attrib */
IUP_SDK_API void iupAttribSetStrf( struct libData *data, Ihandle *ih, const char *name, const char *format, ... );

/** Sets an integer attribute only in the hash table. \n
 * It will be stored as a string. \n
 * It ignores children.
 * \ingroup attrib */
IUP_SDK_API void iupAttribSetInt( struct libData *data, Ihandle *ih, const char *name, int num );

/** Same as \ref iupAttribSet with an id.
 * \ingroup attrib */
IUP_SDK_API void iupAttribSetId( struct libData *data, Ihandle *ih, const char *name, int id, const char *value );

/** Same as \ref iupAttribSetStr with an id.
 * \ingroup attrib */
IUP_SDK_API void iupAttribSetStrId( struct libData *data, Ihandle *ih, const char *name, int id, const char *value );

/** Same as \ref iupAttribSet with lin and col.
 * \ingroup attrib */
IUP_SDK_API void iupAttribSetId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, const char *value );

/** Same as \ref iupAttribSetStr with lin and col.
 * \ingroup attrib */
IUP_SDK_API void iupAttribSetStrId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, const char *value );

/** Same as \ref iupAttribSetInt with an id.
 * \ingroup attrib */
IUP_SDK_API void iupAttribSetIntId( struct libData *data, Ihandle *ih, const char *name, int id, int num );

/** Same as \ref iupAttribSetInt with lin and col.
 * \ingroup attrib */
IUP_SDK_API void iupAttribSetIntId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, int num );

/** Sets an floating point attribute only in the hash table. \n
 * It will be stored as a string. \n
 * It ignores children.
 * \ingroup attrib */
IUP_SDK_API void iupAttribSetFloat( struct libData *data, Ihandle *ih, const char *name, float num );

/** Same as \ref iupAttribSetFloat with an id.
 * \ingroup attrib */
IUP_SDK_API void iupAttribSetFloatId( struct libData *data, Ihandle *ih, const char *name, int id, float num );

/** Same as \ref iupAttribSetFloat with lin and col.
 * \ingroup attrib */
IUP_SDK_API void iupAttribSetFloatId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, float num );


/** Sets an floating point attribute only in the hash table. \n
* It will be stored as a string. \n
* It ignores children.
* \ingroup attrib */
IUP_SDK_API void iupAttribSetDouble( struct libData *data, Ihandle *ih, const char *name, double num );

/** Same as \ref iupAttribSetDouble with an id.
* \ingroup attrib */
IUP_SDK_API void iupAttribSetDoubleId( struct libData *data, Ihandle *ih, const char *name, int id, double num );

/** Same as \ref iupAttribSetDouble with lin and col.
* \ingroup attrib */
IUP_SDK_API void iupAttribSetDoubleId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, double num );


/** Returns the attribute from the hash table only.  \n
 * NO inheritance, NO control implementation, NO defalt value here. \n
 * \ingroup attrib */
IUP_SDK_API char *iupAttribGet( struct libData *data, Ihandle *ih, const char *name );

/** Returns the attribute from the hash table as a string, 
 * but if not defined then checks in its parent tree if allowed by the control implementation, 
 * if still not defined then returns the registered default value if any.
 * NO control implementation, only checks inheritance and default value from it.
 * \ingroup attrib */
IUP_SDK_API char *iupAttribGetStr( struct libData *data, Ihandle *ih, const char *name );

/** Same as \ref iupAttribGetStr but returns an integer number.
 * Checks also for boolean values.
 * \ingroup attrib */
IUP_SDK_API int iupAttribGetInt( struct libData *data, Ihandle *ih, const char *name );

/** Same as \ref iupAttribGetInt but returns two integer numbers. \n
 * Returns the number of valid integers: 0, 1 or 2.
 * \ingroup attrib */
IUP_SDK_API int iupAttribGetIntInt( struct libData *data, Ihandle *ih, const char *name, int *i1, int *i2, char sep );

/** Same as \ref iupAttribGetStr but checks for boolean values.
 * Use \ref iupStrBoolean.
 * \ingroup attrib */
IUP_SDK_API int iupAttribGetBoolean( struct libData *data, Ihandle *ih, const char *name );

/** Same as \ref iupAttribGetStr but returns an floating point number.
 * \ingroup attrib */
IUP_SDK_API float iupAttribGetFloat( struct libData *data, Ihandle *ih, const char *name );

/** Same as \ref iupAttribGetStr but returns an floating point number.
* \ingroup attrib */
IUP_SDK_API double iupAttribGetDouble( struct libData *data, Ihandle *ih, const char *name );

/** Same as \ref iupAttribGet but with an id.
 * \ingroup attrib */
IUP_SDK_API char *iupAttribGetId( struct libData *data, Ihandle *ih, const char *name, int id );

/** Same as \ref iupAttribGetInt but with an id.
 * \ingroup attrib */
IUP_SDK_API int iupAttribGetIntId( struct libData *data, Ihandle *ih, const char *name, int id );

/** Same as \ref iupAttribGetBoolean but with an id.
 * \ingroup attrib */
IUP_SDK_API int iupAttribGetBooleanId( struct libData *data, Ihandle *ih, const char *name, int id );

/** Same as \ref iupAttribGetFloat but with an id.
 * \ingroup attrib */
IUP_SDK_API float iupAttribGetFloatId( struct libData *data, Ihandle *ih, const char *name, int id );

/** Same as \ref iupAttribGetDouble but with an id.
* \ingroup attrib */
IUP_SDK_API double iupAttribGetDoubleId( struct libData *data, Ihandle *ih, const char *name, int id );

/** Same as \ref iupAttribGet but with an lin and col.
 * \ingroup attrib */
IUP_SDK_API char *iupAttribGetId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col );

/** Same as \ref iupAttribGetInt but with lin and col.
 * \ingroup attrib */
IUP_SDK_API int iupAttribGetIntId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col );

/** Same as \ref iupAttribGetBoolean but with lin and col.
 * \ingroup attrib */
IUP_SDK_API int iupAttribGetBooleanId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col );

/** Same as \ref iupAttribGetFloat but with lin and col.
 * \ingroup attrib */
IUP_SDK_API float iupAttribGetFloatId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col );

/** Same as \ref iupAttribGetDouble but with lin and col.
* \ingroup attrib */
IUP_SDK_API double iupAttribGetDoubleId( struct libData *data, Ihandle *ih, const char *name, int id );


/** Returns the attribute from the hash table only, 
 * but if not defined then checks in its parent tree. \n
 * NO control implementation, NO defalt value here. \n
 * Used for EXPAND and internal attributes inside a dialog.
 * \ingroup attrib */
IUP_SDK_API char *iupAttribGetInherit( struct libData *data, Ihandle *ih, const char *name );

/** Returns the attribute from the hash table of a native parent.
 * Don't check for default values. Don't check at the element.
 * Used for BGCOLOR and BACKGROUND attributes.
 * \ingroup attrib */
IUP_SDK_API char *iupAttribGetInheritNativeParent( struct libData *data, Ihandle *ih, const char *name );

/** Returns the attribute from the hash table as a string, 
 * but if not defined then checks in the control implementation, 
 * if still not defined then returns the registered default value if any. \n
 * NO inheritance here. Used only in the IupLayoutDialog.
 * \ingroup attrib */
IUP_SDK_API char *iupAttribGetLocal( struct libData *data, Ihandle *ih, const char *name );

/** Parse a string of attributes.
 *\ingroup attrib */
IUP_SDK_API void iupAttribParse( struct libData *data, Ihandle *ih, const char *str, int save_led_info );

/** Return all saved attributes.
 *\ingroup attrib */
IUP_SDK_API int iupAttribGetAllSaved( struct libData *data, Ihandle *ih, char** names, int n );



/** Set an internal name to a handle.
 * \ingroup attrib */
IUP_SDK_API void iupAttribSetHandleName( struct libData *data, Ihandle *ih );

/** Returns the internal name if set.
 * \ingroup attrib */
IUP_SDK_API char *iupAttribGetHandleName( struct libData *data, Ihandle *ih );



/** Sets the attribute only at the element. \n
 * If set method is not defined will not be set,
 * neither will be stored in the hash table. \n
 * Only generic pointers and constant strings can be set as value. \n
 * It ignores children.
 * \ingroup attrib */
IUP_SDK_API void iupAttribSetClassObject( struct libData *data, Ihandle *ih, const char *name, const char *value );
IUP_SDK_API void iupAttribSetClassObjectId( struct libData *data, Ihandle *ih, const char *name, int id, const char *value );
IUP_SDK_API void iupAttribSetClassObjectId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, const char *value );
IUP_SDK_API char *iupAttribGetClassObject( struct libData *data, Ihandle *ih, const char *name );
IUP_SDK_API char *iupAttribGetClassObjectId( struct libData *data, Ihandle *ih, const char *name, int id );
IUP_SDK_API char *iupAttribGetClassObjectId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col );



/* For all attributes in the environment, call the class SetAttribute only.
 * Called only after the element is mapped, but before the children are mapped. */
void iupAttribUpdate( struct libData *data, Ihandle *ih ); 

/* For all registered inherited attributes, checks the parent tree and 
 * call the class SetAttribute if the attribute is defined.
 * Called only after the element is mapped, but before the children are mapped. */
void iupAttribUpdateFromParent( struct libData *data, Ihandle *ih );

/* For all attributes in the environment, call the class SetAttribute only for the children.
 * Called only after the element is mapped, and after the children are mapped. */
void iupAttribUpdateChildren( struct libData *data, Ihandle *ih );

/* Parse attributes from theme and set at element.
   Called only in Create and when a theme is explicitly set */
void iupAttribSetTheme( struct libData *data, Ihandle *ih, Ihandle *theme );


/* Other functions declared in <iup.h> and implemented here. 
IupCopyAttributes
IupGetAllAttributes
IupGetAttributes
IupSetAttributes
IupSetAttribute
IupStoreAttribute
IupGetAttribute
IupGetFloat
IupGetInt
IupGetInt2
IupSetfAttribute
IupSetAttributeHandle
IupGetAttributeHandle
*/


#ifdef __cplusplus
}
#endif

#endif
