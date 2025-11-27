
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"

// --

#if 0

/** \file
 * \brief attributes environment management
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <limits.h>
#include <stdarg.h>

#include "iup.h"

#include "iup_object.h"
#include "iup_childtree.h"
#include "iup_str.h"
#include "iup_ledlex.h"
#include "iup_attrib.h"
#include "iup_assert.h"
#include "iup_varg.h"

#endif

#define iupATTRIB_LANGUAGE_STRING(_v)  (_v && _v[0] == '_' && _v[1] == '@') 
#define iupATTRIB_LANGUAGE_SHIFT 2

#define iupATTRIB_GET_LANGUAGE_STRING(data,_v, _s)                              \
  {                                                                        \
    char *new_value = amy_IupGetLanguageString(data,_v+iupATTRIB_LANGUAGE_SHIFT );   \
    if (new_value != _v+iupATTRIB_LANGUAGE_SHIFT)                          \
    {                                                                      \
      _v = new_value;                                                      \
      _s = 0;  /* no need to store it again, already stored internally */  \
    }                                                                      \
  }


void iupAttribSetTheme( struct libData *data, Ihandle *ih, Ihandle *theme)
{
  /* theme is a amy_IupUser, we assume all attributes are strings */
  /* only attributes registered on "ih" will be copied from the theme */
  char *name, *value;
  char class_name[100];

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return;

  iupASSERT(iupObjectCheck( data, theme ));
  if ( ! iupObjectCheck( data, theme ))
    return;

  name = iupTableFirst( data, theme->attrib );
  while (name)
  {
    if (iupClassObjectAttribCanCopy( data, ih, name))
    {
      value = iupTableGetCurr( data, theme->attrib );
      amy_IupStoreAttribute( data, ih, name, value );
    }

    name = iupTableNext( data, theme->attrib );
  }

  sprintf(class_name, "IUP%s", ih->iclass->name );
  iupStrUpper(class_name, class_name );
  value = iupAttribGet( data, theme, class_name );
  if (value)
  {
    theme = amy_IupGetHandle( data, value );
    if (theme)
      iupAttribSetTheme( data, ih, theme );
  }
}

IUP_API void amy_IupCopyAttributes( struct libData *data, Ihandle *src_ih, Ihandle *dst_ih)
{
  char *name, *value;

  iupASSERT(iupObjectCheck( data, src_ih ));
  if ( ! iupObjectCheck( data, src_ih ))
    return;

  iupASSERT(iupObjectCheck( data, dst_ih ));
  if ( ! iupObjectCheck( data, dst_ih ))
    return;

  name = iupTableFirst( data, src_ih->attrib );
  while (name)
  {
    if ( ! iupATTRIB_ISINTERNAL(name) && !iupAttribIsNotString( data, src_ih, name))
    {
      value = iupTableGetCurr( data, src_ih->attrib );
      amy_IupStoreAttribute( data, dst_ih, name, value );
    }

    name = iupTableNext( data, src_ih->attrib );
  }
}

#define iupATTRIB_ISSAVED(_name) (_name[0]  == '_' && \
                                  _name[1]  == 'I' && \
                                  _name[2]  == 'U' && \
                                  _name[3]  == 'P' && \
                                  _name[4]  == 'L' && \
                                  _name[5]  == 'E' && \
                                  _name[6]  == 'D' && \
                                  _name[7]  == '_' && \
                                  _name[8]  == 'S' && \
                                  _name[9]  == 'A' && \
                                  _name[10] == 'V' && \
                                  _name[11] == 'E' && \
                                  _name[12] == 'D' && \
                                  _name[13] == '_')  /* "_IUPLED_SAVED_" */

IUP_SDK_API int iupAttribGetAllSaved( struct libData *data, Ihandle *ih, char** names, int n)
{
  char *name;
  int i = 0;

  if ( ! names || n == 0 || n == -1)
    return iupTableCount( data, ih->attrib );

  name = iupTableFirst( data, ih->attrib );
  while (name)
  {
    if (iupATTRIB_ISSAVED(name))
    {
      names[i] = name + sizeof("_IUPLED_SAVED_" ) - 1;
      i++;

      if (i == n)
        break;
    }

    name = iupTableNext( data, ih->attrib );
  }

  return i;
}

IUP_API int amy_IupGetAllAttributes( struct libData *data, Ihandle *ih, char** names, int n)
{
  char *name;
  int i = 0;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return 0;

  if ( ! names || n == 0 || n == -1)
    return iupTableCount( data, ih->attrib );

  name = iupTableFirst( data, ih->attrib );
  while (name)
  {
    if ( ! iupATTRIB_ISINTERNAL(name))
    {
      names[i] = name;
      i++;

      if (i == n)
        break;
    }

    name = iupTableNext( data, ih->attrib );
  }

  return i;
}

IUP_API char *amy_IupGetAttributes( struct libData *data, Ihandle *ih )
{
  char *buffer;
  char *name, *value;
  char sb[128];
  int size;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return NULL;

  buffer = iupStrGetLargeMem(&size );
  buffer[0] = 0;

  name = iupTableFirst( data, ih->attrib );
  while (name && size)
  {
    if ( ! iupATTRIB_ISINTERNAL(name))
    {
      if (buffer[0] != 0)
        { strcat(buffer,"," ); size--; }

      value = iupTableGetCurr( data, ih->attrib );
      if (iupAttribIsNotString( data, ih, name))
      {
        sprintf(sb, "%p", (void*) value );
        value = sb;
      }

      strcat(buffer, name );  size -= (int)strlen(name );
      strcat(buffer,"=\"" );  size--;
      strcat(buffer, value );  size -= (int)strlen(value );
      strcat(buffer,"\"" );  size--;
    }

    name = iupTableNext( data, ih->attrib );
  }

  return buffer;
}

void iupAttribUpdateFromParent( struct libData *data, Ihandle *ih )
{
  Iclass *ic = ih->iclass;
  char *name = iupTableFirst( data, ic->attrib_func );
  while (name)
  {
    /* if inheritable and NOT defined at the element */
    if (iupClassObjectCurAttribIsInherit( data, ic ) && !iupAttribGet( data, ih, name))
    {
      /* check in the parent tree if the attribute is defined */
      Ihandle *parent = ih->parent;
      while (parent)
      {
        char *value = iupTableGet( data, parent->attrib, name );
        if (value)
        {
          int inherit;
          /* set on the class */
          iupClassObjectSetAttribute( data, ih, name, value, &inherit );
          break;
        }
        parent = parent->parent;
      }
    }

    name = iupTableNext( data, ic->attrib_func );
  }
}

static int iAttribIsInherit( struct libData *data, Ihandle *ih, const  char *name)
{
  int inherit;
  char *def_value;
  iupClassObjectGetAttributeInfo( data, ih, name, &def_value, &inherit );
  return inherit;
}

static void iAttribNotifyChildren( struct libData *data, Ihandle *ih, const char *name, const char *value)
{
  int inherit;
  Ihandle *child = ih->firstchild;
  while (child)
  {
    if ( ! iupTableGet( data, child->attrib, name))
    {
      /* set only if an inheritable attribute at the child */
      if (iAttribIsInherit( data, child, name))
      {
        /* set on the class */
        iupClassObjectSetAttribute( data, child, name, value, &inherit );

        iAttribNotifyChildren( data, child, name, value );
      }
    }

    child = child->brother;
  }
}

void iupAttribUpdateChildren( struct libData *data, Ihandle *ih )
{
  char *name = iupTableFirst( data, ih->attrib );
  while (name)
  {
    if ( ! iupATTRIB_ISINTERNAL(name) && iAttribIsInherit( data, ih, name))
    {
      /* retrieve from the table */
      char *value = iupTableGet( data, ih->attrib, name );
      iAttribNotifyChildren( data, ih, name, value );
    }

    name = iupTableNext( data, ih->attrib );
  }
}

void iupAttribUpdate( struct libData *data, Ihandle *ih )
{
  char** name_array;
  char *name, *value;
  int count, i = 0, inherit, store;

  count = iupTableCount( data, ih->attrib );
  if ( ! count)
    return;

  name_array = (char**)malloc(count * sizeof(char*));

  /* store the names before updating so we can add or remove attributes during the update */
  name = iupTableFirst( data, ih->attrib );
  while (name)
  {
    if ( ! iupATTRIB_ISINTERNAL(name))
    {
      name_array[i] = iupStrDup(name );
      i++;
    }

    name = iupTableNext( data, ih->attrib );
  }
  count = i;

  /* for all defined attributes updates the native system */
  for (i = 0; i < count; i++)
  {
    name = name_array[i];

    /* retrieve from the table */
    value = iupTableGet( data, ih->attrib, name );

    /* set on the class */
    store = iupClassObjectSetAttribute( data, ih, name, value, &inherit );

    if (inherit)
      iAttribNotifyChildren( data, ih, name, value );

    if (store == 0)
      iupTableRemove( data, ih->attrib, name ); /* remove from the table according to the class SetAttribute */

    free(name_array[i] );
  }

  free(name_array );
}

IUP_API void amy_IupSetAttributeId( struct libData *data, Ihandle *ih, const char *name, int id, const char *value)
{
  iupASSERT(name!=NULL );
  if ( ! name)
    return;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return;

  if (iupClassObjectSetAttributeId( data, ih, name, id, value)!=0) /* store strings and pointers */
    iupAttribSetId( data, ih, name, id, value );
}

IUP_API void amy_IupSetStrAttributeId( struct libData *data, Ihandle *ih, const char *name, int id, const char *value)
{
  amy_IupStoreAttributeId( data, ih, name, id, value );
}

IUP_API void amy_IupStoreAttributeId( struct libData *data, Ihandle *ih, const char *name, int id, const char *value)
{
  int store = 1;

  iupASSERT(name!=NULL );
  if ( ! name)
    return;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return;

  if (iupATTRIB_LANGUAGE_STRING(value))
    iupATTRIB_GET_LANGUAGE_STRING( data, value, store );

  if (iupClassObjectSetAttributeId( data, ih, name, id, value)==1) /* store only strings */
  {
    if (store)
      iupAttribSetStrId( data, ih, name, id, value );
    else
      iupAttribSetId( data, ih, name, id, value );
  }
}

IUP_API char *amy_IupGetAttributeId( struct libData *data, Ihandle *ih, const char *name, int id)
{
  char *value;

  iupASSERT(name!=NULL );
  if ( ! name)
    return NULL;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return NULL;

  value = iupClassObjectGetAttributeId( data, ih, name, id );
  if ( ! value)
    value = iupAttribGetId( data, ih, name, id );

  return value;
}

IUP_API void amy_IupSetAttributeId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, const char *value)
{
  iupASSERT(name!=NULL );
  if ( ! name)
    return;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return;

  if (iupClassObjectSetAttributeId2( data, ih, name, lin, col, value)!=0) /* store strings and pointers */
    iupAttribSetId2( data, ih, name, lin, col, value );
}

IUP_API void amy_IupSetStrAttributeId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, const char *value)
{
  amy_IupStoreAttributeId2( data, ih, name, lin, col, value );
}

IUP_API void amy_IupStoreAttributeId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, const char *value)
{
  int store = 1;

  iupASSERT(name!=NULL );
  if ( ! name)
    return;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return;

  if (iupATTRIB_LANGUAGE_STRING(value))
    iupATTRIB_GET_LANGUAGE_STRING( data, value, store );

  if (iupClassObjectSetAttributeId2( data, ih, name, lin, col, value)==1) /* store only strings */
  {
    if (store)
      iupAttribSetStrId2( data, ih, name, lin, col, value );
    else
      iupAttribSetId2( data, ih, name, lin, col, value );
  }
}

IUP_API char *amy_IupGetAttributeId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col)
{
  char *value;

  iupASSERT(name!=NULL );
  if ( ! name)
    return NULL;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return NULL;

  value = iupClassObjectGetAttributeId2( data, ih, name, lin, col );
  if ( ! value)
    value = iupAttribGetId2( data, ih, name, lin, col );

  return value;
}

IUP_API int amy_IupGetIntId( struct libData *data, Ihandle *ih, const char *name, int id )
{
  int i = 0;
  char *value = amy_IupGetAttributeId( data, ih, name, id );
  if (value)
  {
    if ( ! iupStrToInt(value, &i))
    {
      if (iupStrBoolean(value))
        i = 1;
    }
  }
  return i;
}

IUP_API float amy_IupGetFloatId( struct libData *data, Ihandle *ih, const char *name, int id)
{
  float f = 0;
  iupStrToFloat(amy_IupGetAttributeId( data, ih, name, id), &f );
  return f;
}

IUP_API double amy_IupGetDoubleId( struct libData *data, Ihandle *ih, const char *name, int id)
{
  double f = 0;
  iupStrToDouble(  amy_IupGetAttributeId( data, ih, name, id), &f );
  return f;
}

IUP_API void amy_IupGetRGBId( struct libData *data, Ihandle *ih, const char *name, int id, unsigned char *r, unsigned char *g, unsigned char *b)
{
  iupStrToRGB(amy_IupGetAttributeId( data, ih, name, id), r, g, b );
}

IUP_API void amy_IupSetStrfIdV( struct libData *data, Ihandle *ih, const char *name, int id, const char *f, va_list arglist)
{
  int size;
  char *value = iupStrGetLargeMem(&size );
  vsnprintf(value, size, f, arglist );
  amy_IupStoreAttributeId( data, ih, name, id, value );
}

IUP_API void amy_IupSetStrfId( struct libData *data, Ihandle *ih, const char *name, int id, const char *f, ...)
{
  int size;
  char *value = iupStrGetLargeMem(&size );
  va_list arglist;
  va_start(arglist, f );
  vsnprintf(value, size, f, arglist );
  va_end(arglist );
  amy_IupStoreAttributeId( data, ih, name, id, value );
}

IUP_API void amy_IupSetfAttributeId( struct libData *data, Ihandle *ih, const char *name, int id, const char *f, ... )
{
  int size;
  char *value = iupStrGetLargeMem(&size );
  va_list arglist;
  va_start(arglist, f );
  vsnprintf(value, size, f, arglist );
  va_end(arglist );
  amy_IupStoreAttributeId( data, ih, name, id, value );
}

IUP_API void amy_IupSetIntId( struct libData *data, Ihandle *ih, const char *name, int id, int num )
{
  char value[20];  /* +4,294,967,296 */
  sprintf(value, "%d", num );
  amy_IupStoreAttributeId( data, ih, name, id, value );
}

IUP_API void amy_IupSetFloatId( struct libData *data, Ihandle *ih, const char *name, int id, float num)
{
  char value[80];
  sprintf(value, IUP_FLOAT2STR, num );
  amy_IupStoreAttributeId( data, ih, name, id, value );
}

IUP_API void amy_IupSetDoubleId( struct libData *data, Ihandle *ih, const char *name, int id, double num)
{
  char value[80];
  sprintf(value, IUP_DOUBLE2STR, num );
  amy_IupStoreAttributeId( data, ih, name, id, value );
}

IUP_API void amy_IupSetRGBId( struct libData *data, Ihandle *ih, const char *name, int id, unsigned char r, unsigned char g, unsigned char b)
{
  char value[60];
  sprintf(value, "%d %d %d", (int)r, (int)g, (int)b );
  amy_IupStoreAttributeId( data, ih, name, id, value );
}

IUP_API int amy_IupGetIntId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col)
{
  int i = 0;
  char *value = amy_IupGetAttributeId2( data, ih, name, lin, col );
  if (value)
  {
    if ( ! iupStrToInt(value, &i))
    {
      if (iupStrBoolean(value))
        i = 1;
    }
  }
  return i;
}

IUP_API float amy_IupGetFloatId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col)
{
  float f = 0;
  iupStrToFloat(amy_IupGetAttributeId2( data, ih, name, lin, col), &f );
  return f;
}

IUP_API double amy_IupGetDoubleId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col)
{
  double f = 0;
  iupStrToDouble(  amy_IupGetAttributeId2( data, ih, name, lin, col), &f );
  return f;
}

IUP_API void amy_IupGetRGBId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, unsigned char *r, unsigned char *g, unsigned char *b)
{
  iupStrToRGB(amy_IupGetAttributeId2( data, ih, name, lin, col), r, g, b );
}

IUP_API void amy_IupSetStrfId2V( struct libData *data, Ihandle *ih, const char *name, int lin, int col, const char *f, va_list arglist)
{
  int size;
  char *value = iupStrGetLargeMem(&size );
  vsnprintf(value, size, f, arglist );
  amy_IupStoreAttributeId2( data, ih, name, lin, col, value );
}

IUP_API void amy_IupSetStrfId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, const char *f, ...)
{
  int size;
  char *value = iupStrGetLargeMem(&size );
  va_list arglist;
  va_start(arglist, f );
  vsnprintf(value, size, f, arglist );
  va_end(arglist );
  amy_IupStoreAttributeId2( data, ih, name, lin, col, value );
}

IUP_API void amy_IupSetfAttributeId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, const char *f, ...)
{
  int size;
  char *value = iupStrGetLargeMem(&size );
  va_list arglist;
  va_start(arglist, f );
  vsnprintf(value, size, f, arglist );
  va_end(arglist );
  amy_IupStoreAttributeId2( data, ih, name, lin, col, value );
}

IUP_API void amy_IupSetIntId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, int num)
{
  char value[20];  /* +4,294,967,296 */
  sprintf(value, "%d", num );
  amy_IupStoreAttributeId2( data, ih, name, lin, col, value );
}

IUP_API void amy_IupSetFloatId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, float num)
{
  char value[80];
  sprintf(value, IUP_FLOAT2STR, num );
  amy_IupStoreAttributeId2( data, ih, name, lin, col, value );
}

IUP_API void amy_IupSetDoubleId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, double num)
{
  char value[80];
  sprintf(value, IUP_DOUBLE2STR, num );
  amy_IupStoreAttributeId2( data, ih, name, lin, col, value );
}

IUP_API void amy_IupSetRGBId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, unsigned char r, unsigned char g, unsigned char b)
{
  char value[60];
  sprintf(value, "%d %d %d", (int)r, (int)g, (int)b );
  amy_IupStoreAttributeId2( data, ih, name, lin, col, value );
}

IUP_API void amy_IupSetAttribute( struct libData *data, Ihandle *ih, const char *name, const char *value)
{
  int inherit;

  iupASSERT(name!=NULL );
  if ( ! name)
    return;

  if ( ! ih)
  {
    amy_IupSetGlobal( data, name, value );
    return;
  }

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return;

  if (iupATTRIB_ISINTERNAL(name))
    iupAttribSet( data, ih, name, value );
  else
  {
    if (iupClassObjectSetAttribute( data, ih, name, value, &inherit)!=0) /* store strings and pointers */
      iupAttribSet( data, ih, name, value );

    if (inherit)
      iAttribNotifyChildren( data, ih, name, value );
  }
}

IUP_API void amy_IupSetStrAttribute( struct libData *data, Ihandle *ih, const char *name, const char *value )
{
	amy_IupStoreAttribute( data, ih, name, value );
}

IUP_API void amy_IupStoreAttribute( struct libData *data, Ihandle *ih, const char *name, const char *value)
{
  int inherit;

  if ( ! name)
    return;

  if ( ! ih)
  {
    amy_IupStoreGlobal( data, name, value );
    return;
  }

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return;

  if (iupATTRIB_ISINTERNAL(name))
    iupAttribSetStr( data, ih, name, value );
  else
  {
    int store = 1;

    if (iupATTRIB_LANGUAGE_STRING(value))
      iupATTRIB_GET_LANGUAGE_STRING( data, value, store );

    if (iupClassObjectSetAttribute( data, ih, name, value, &inherit)==1) /* store only strings */
    {
      if (store)
        iupAttribSetStr( data, ih, name, value );
      else
        iupAttribSet( data, ih, name, value );
    }

    if (inherit)
      iAttribNotifyChildren( data, ih, name, value );
  }
}

static void iAttribResetChildren( struct libData *data, Ihandle *ih, const char *name)
{
  Ihandle *child = ih->firstchild;
  while (child)
  {
    /* set only if an inheritable attribute at the child */
    if (iAttribIsInherit( data, child, name))
    {
      iupAttribSet( data, child, name, NULL );

      iAttribResetChildren( data, child, name );
    }

    child = child->brother;
  }
}

IUP_API void amy_IupResetAttribute( struct libData *data, Ihandle *ih, const char *name)
{
  iupASSERT(name!=NULL );
  if ( ! name)
    return;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return;

  iupAttribSet( data, ih, name, NULL );

  if (iAttribIsInherit( data, ih, name))
    iAttribResetChildren( data, ih, name );
}

IUP_API char *amy_IupGetAttribute( struct libData *data, Ihandle *ih, const char *name)
{
  iupASSERT(name!=NULL );
  if ( ! name)
    return NULL;

  if ( ! ih)
    return amy_IupGetGlobal( data, name );

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return NULL;

  if (iupATTRIB_ISINTERNAL(name))
    return iupAttribGet( data, ih, name );
  else
  {
    int inherit;
    char *value, *def_value;

    value = iupClassObjectGetAttribute( data, ih, name, &def_value, &inherit );

    if ( ! value)
      value = iupAttribGet( data, ih, name );

    if ( ! value && inherit)
    {
      while ( ! value)
      {
        ih = ih->parent;
        if ( ! ih)
          break;

        value = iupAttribGet( data, ih, name );
      }
    }

    if ( ! value)
      value = def_value;

    return value;
  }
}

IUP_API float amy_IupGetFloat( struct libData *data, Ihandle *ih, const char *name)
{
  float f = 0;
  iupStrToFloat(amy_IupGetAttribute( data, ih, name), &f );
  return f;
}

IUP_API double amy_IupGetDouble( struct libData *data, Ihandle *ih, const char *name)
{
  double f = 0;
  iupStrToDouble(  amy_IupGetAttribute( data, ih, name), &f );
  return f;
}

IUP_API int amy_IupGetInt( struct libData *data, Ihandle *ih, const char *name)
{
  int i = 0;
  char *value = amy_IupGetAttribute( data, ih, name );
  if (value)
  {
    if ( ! iupStrToInt(value, &i))
    {
      if (iupStrBoolean(value))
        i = 1;
    }
  }
  return i;
}

IUP_API int amy_IupGetInt2( struct libData *data, Ihandle *ih, const char *name )
{
  int i1 = 0, i2 = 0;
  char *value = amy_IupGetAttribute( data, ih, name );
  if (value)
  {
    char sep = 'x';
    if (strchr(value, ':')!=NULL)
      sep = ':';
    else if (strchr(value, ',')!=NULL)
      sep = ',';

    iupStrToIntInt(value, &i1, &i2, sep );
  }
  return i2;
}

IUP_API int amy_IupGetIntInt( struct libData *data, Ihandle *ih, const char *name, int *i1, int *i2 )
{
  int _i1 = 0, _i2 = 0;
  char *value = amy_IupGetAttribute( data, ih, name );
  if (value)
  {
    int count;

    char sep = 'x';
    if (strchr(value, ':')!=NULL)
      sep = ':';
    else if (strchr(value, ',')!=NULL)
      sep = ',';

    count = iupStrToIntInt(value, &_i1, &_i2, sep );
    if (i1) *i1 = _i1;
    if (i2) *i2 = _i2;
    return count;
  }
  return 0;
}

IUP_API void amy_IupGetRGB( struct libData *data, Ihandle *ih, const char *name, unsigned char *r, unsigned char *g, unsigned char *b)
{
  iupStrToRGB(amy_IupGetAttribute( data, ih, name), r, g, b );
}

IUP_API void amy_IupGetRGBA( struct libData *data, Ihandle *ih, const char *name, unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *a)
{
  iupStrToRGBA(amy_IupGetAttribute( data, ih, name), r, g, b, a );
}

IUP_API void amy_IupSetStrfV( struct libData *data, Ihandle *ih, const char *name, const char *f, va_list arglist)
{
  int size;
  char *value = iupStrGetLargeMem(&size );
  vsnprintf(value, size, f, arglist );
  amy_IupStoreAttribute( data, ih, name, value );
}

IUP_API void amy_IupSetStrf( struct libData *data, Ihandle *ih, const char *name, const char *f, ...)
{
  int size;
  char *value = iupStrGetLargeMem(&size );
  va_list arglist;
  va_start(arglist, f );
  vsnprintf(value, size, f, arglist );
  va_end(arglist );
  amy_IupStoreAttribute( data, ih, name, value );
}

IUP_API void amy_IupSetfAttribute( struct libData *data, Ihandle *ih, const char *name, const char *f, ...)
{
  int size;
  char *value = iupStrGetLargeMem(&size );
  va_list arglist;
  va_start(arglist, f );
  vsnprintf(value, size, f, arglist );
  va_end(arglist );
  amy_IupStoreAttribute( data, ih, name, value );
}

IUP_API void amy_IupSetInt( struct libData *data, Ihandle *ih, const char *name, int num)
{
  char value[20];  /* +4,294,967,296 */
  sprintf(value, "%d", num );
  amy_IupStoreAttribute( data, ih, name, value );
}

IUP_API void amy_IupSetFloat( struct libData *data, Ihandle *ih, const char *name, float num)
{
  char value[80];
  sprintf(value, IUP_FLOAT2STR, num );
  amy_IupStoreAttribute( data, ih, name, value );
}

IUP_API void amy_IupSetDouble( struct libData *data, Ihandle *ih, const char *name, double num )
{
  char value[80];
  sprintf(value, IUP_DOUBLE2STR, num );
  amy_IupStoreAttribute( data, ih, name, value );
}

IUP_API void amy_IupSetRGB( struct libData *data, Ihandle *ih, const char *name, unsigned char r, unsigned char g, unsigned char b)
{
  char value[60];
  sprintf(value, "%d %d %d", (int)r, (int)g, (int)b );
  amy_IupStoreAttribute( data, ih, name, value );
}

IUP_API void amy_IupSetRGBA( struct libData *data, Ihandle *ih, const char *name, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
  char value[60];
  sprintf(value, "%d %d %d %d", (int)r, (int)g, (int)b, (int)a );
  amy_IupStoreAttribute( data, ih, name, value );
}

IUP_SDK_API void iupAttribSetHandleName( struct libData *data, Ihandle *ih )
{
  char str_name[100];
  sprintf(str_name, "_IUP_NAME(%p)", ih );
  amy_IupSetHandle( data, str_name, ih );
}

IUP_SDK_API char *iupAttribGetHandleName( struct libData *data, Ihandle *ih )
{
  char *name = iupAttribGet( data, ih, "HANDLENAME" );  /* amy_IupSetHandle was called at least once */
  if (name)
    return iupStrReturnStr(name );
  else
    return NULL;
}

IUP_API void amy_IupSetAttributeHandle( struct libData *data, Ihandle *ih, const char *name, Ihandle *ih_named )
{
  char *handle_name;

  iupASSERT(name!=NULL );
  if ( ! name)
    return;

  iupASSERT(ih_named!=NULL );
  if ( ! ih_named)
    return;

  /* make sure it has at least one name */
  handle_name = iupAttribGetHandleName( data, ih_named );
  if ( ! handle_name)
  {
    iupAttribSetHandleName( data, ih_named );
    handle_name = iupAttribGetHandleName( data, ih_named );
  }

  amy_IupStoreAttribute( data, ih, name, handle_name );
}

static void iAttribSetNameId2(char *nameid, const char *name, int lin, int col)
{
  if (lin == IUP_INVALID_ID && col == IUP_INVALID_ID)
    sprintf(nameid, "%s", name );
  else if (lin == IUP_INVALID_ID)
    sprintf(nameid, "%s*:%d", name, col );
  else if (col == IUP_INVALID_ID)
    sprintf(nameid, "%s%d:*", name, lin );
  else
    sprintf(nameid, "%s%d:%d", name, lin, col );
}

static void iAttribSetNameId(char *nameid, const char *name, int id)
{
  if (id == IUP_INVALID_ID)
    sprintf(nameid, "%s", name );
  else
    sprintf(nameid, "%s%d", name, id );
}

IUP_API void amy_IupSetAttributeHandleId( struct libData *data, Ihandle *ih, const char *name, int id, Ihandle *ih_named)
{
  char nameid[100];
  iAttribSetNameId(nameid, name, id );
  amy_IupSetAttributeHandle( data, ih, nameid, ih_named );
}

IUP_API Ihandle *amy_IupGetAttributeHandle( struct libData *data, Ihandle *ih, const char *name)
{
  char *handle_name;

  iupASSERT(name!=NULL );
  if ( ! name)
    return NULL;

  handle_name = amy_IupGetAttribute( data, ih, name );
  return amy_IupGetHandle( data, handle_name );
}

IUP_API Ihandle *amy_IupGetAttributeHandleId( struct libData *data, Ihandle *ih, const char *name, int id)
{
  char nameid[100];
  iAttribSetNameId(nameid, name, id );
  return amy_IupGetAttributeHandle( data, ih, nameid );
}

IUP_API void amy_IupSetAttributeHandleId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, Ihandle *ih_named)
{
  char nameid[100];
  iAttribSetNameId2(nameid, name, lin, col );
  amy_IupSetAttributeHandle( data, ih, nameid, ih_named );
}

IUP_API Ihandle *amy_IupGetAttributeHandleId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col)
{
  char nameid[100];
  iAttribSetNameId2(nameid, name, lin, col );
  return amy_IupGetAttributeHandle( data, ih, nameid );
}

IUP_API Ihandle *amy_IupSetAttV( struct libData *data, const char *handle_name, Ihandle *ih, const char *name, va_list arglist)
{
  const char *attr, *val;
  attr = name;
  while (attr)
  {
    val = va_arg(arglist, const char *);
    amy_IupSetAttribute( data, ih, attr, val );
    attr = va_arg(arglist, const char *);
  }
  if (handle_name)
    amy_IupSetHandle( data, handle_name, ih );
  return ih;
}

IUP_API Ihandle *amy_IupSetAtt( struct libData *data, const char *handle_name, Ihandle *ih, const char *name, ...)
{
  va_list arglist;
  va_start(arglist, name );
  amy_IupSetAttV( data, handle_name, ih, name, arglist );
  va_end(arglist );
  return ih;
}

IUP_SDK_API void iupAttribSetClassObject( struct libData *data, Ihandle *ih, const char *name, const char *value)
{
  int inherit;
  iupClassObjectSetAttribute( data, ih, name, value, &inherit );
}

IUP_SDK_API void iupAttribSetClassObjectId( struct libData *data, Ihandle *ih, const char *name, int id, const char *value)
{
  iupClassObjectSetAttributeId( data, ih, name, id, value );
}

IUP_SDK_API void iupAttribSetClassObjectId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, const char *value)
{
  iupClassObjectSetAttributeId2( data, ih, name, lin, col, value );
}

IUP_SDK_API char *iupAttribGetClassObject( struct libData *data, Ihandle *ih, const char *name)
{
  int inherit;
  char *def_value;
  return iupClassObjectGetAttribute( data, ih, name, &def_value, &inherit );
}

IUP_SDK_API char *iupAttribGetClassObjectId( struct libData *data, Ihandle *ih, const char *name, int id)
{
  return iupClassObjectGetAttributeId( data, ih, name, id );
}

IUP_SDK_API char *iupAttribGetClassObjectId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col)
{
  return iupClassObjectGetAttributeId2( data, ih, name, lin, col );
}

IUP_SDK_API void iupAttribSet( struct libData *data, Ihandle *ih, const char *name, const char *value)
{
  if ( ! value)
    iupTableRemove( data, ih->attrib, name );
  else
    iupTableSet( data, ih->attrib, name, (void*)value, IUPTABLE_POINTER );
}

IUP_SDK_API void iupAttribSetStr( struct libData *data, Ihandle *ih, const char *name, const char *value)
{
  if ( ! value)
    iupTableRemove( data, ih->attrib, name );
  else
  {
    int store = 1;

    if (iupATTRIB_LANGUAGE_STRING(value))
      iupATTRIB_GET_LANGUAGE_STRING( data, value, store );

    if (store)
      iupTableSet( data, ih->attrib, name, (void*)value, IUPTABLE_STRING );
    else
      iupTableSet( data, ih->attrib, name, (void*)value, IUPTABLE_POINTER );
  }
}

IUP_SDK_API void iupAttribSetStrf( struct libData *data, Ihandle *ih, const char *name, const char *f, ...)
{
  char *value = iupStrGetMemory(10240 );
  va_list arglist;
  va_start(arglist, f );
  vsnprintf(value, 10240, f, arglist );
  va_end(arglist );
  iupAttribSetStr( data, ih, name, value );
}

IUP_SDK_API void iupAttribSetInt( struct libData *data, Ihandle *ih, const char *name, int num)
{
  char value[20];  /* +4,294,967,296 */
  sprintf(value, "%d", num );
  iupAttribSetStr( data, ih, name, value );
}

IUP_SDK_API void iupAttribSetFloat( struct libData *data, Ihandle *ih, const char *name, float num)
{
  char value[80];
  sprintf(value, IUP_FLOAT2STR, num );
  iupAttribSetStr( data, ih, name, value );
}

IUP_SDK_API void iupAttribSetDouble( struct libData *data, Ihandle *ih, const char *name, double num)
{
  char value[80];
  sprintf(value, IUP_DOUBLE2STR, num );
  iupAttribSetStr( data, ih, name, value );
}

IUP_SDK_API void iupAttribSetId( struct libData *data, Ihandle *ih, const char *name, int id, const char *value)
{
  char nameid[100];
  iAttribSetNameId(nameid, name, id );
  iupAttribSet( data, ih, nameid, value );
}

IUP_SDK_API void iupAttribSetStrId( struct libData *data, Ihandle *ih, const char *name, int id, const char *value)
{
  char nameid[100];
  iAttribSetNameId(nameid, name, id );
  iupAttribSetStr( data, ih, nameid, value );
}

IUP_SDK_API void iupAttribSetId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, const char *value)
{
  char nameid[100];
  iAttribSetNameId2(nameid, name, lin, col );
  iupAttribSet( data, ih, nameid, value );
}

IUP_SDK_API void iupAttribSetStrId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, const char *value)
{
  char nameid[100];
  iAttribSetNameId2(nameid, name, lin, col );
  iupAttribSetStr( data, ih, nameid, value );
}

IUP_SDK_API void iupAttribSetIntId( struct libData *data, Ihandle *ih, const char *name, int id, int num)
{
  char nameid[100];
  iAttribSetNameId(nameid, name, id );
  iupAttribSetInt( data, ih, nameid, num );
}

IUP_SDK_API void iupAttribSetIntId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, int num)
{
  char nameid[100];
  iAttribSetNameId2(nameid, name, lin, col );
  iupAttribSetInt( data, ih, nameid, num );
}

IUP_SDK_API void iupAttribSetFloatId( struct libData *data, Ihandle *ih, const char *name, int id, float num)
{
  char nameid[100];
  iAttribSetNameId(nameid, name, id );
  iupAttribSetFloat( data, ih, nameid, num );
}

IUP_SDK_API void iupAttribSetDoubleId( struct libData *data, Ihandle *ih, const char *name, int id, double num)
{
  char nameid[100];
  iAttribSetNameId(nameid, name, id );
  iupAttribSetDouble( data, ih, nameid, num );
}

IUP_SDK_API void iupAttribSetFloatId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, float num)
{
  char nameid[100];
  iAttribSetNameId2(nameid, name, lin, col );
  iupAttribSetFloat( data, ih, nameid, num );
}

IUP_SDK_API void iupAttribSetDoubleId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col, double num)
{
  char nameid[100];
  iAttribSetNameId2(nameid, name, lin, col );
  iupAttribSetDouble( data, ih, nameid, num );
}

IUP_SDK_API char *iupAttribGetId( struct libData *data, Ihandle *ih, const char *name, int id)
{
  char nameid[100];
  iAttribSetNameId(nameid, name, id );
  return iupAttribGet( data, ih, nameid );
}

IUP_SDK_API int iupAttribGetIntId( struct libData *data, Ihandle *ih, const char *name, int id)
{
  char nameid[100];
  iAttribSetNameId(nameid, name, id );
  return iupAttribGetInt( data, ih, nameid );
}

IUP_SDK_API int iupAttribGetBooleanId( struct libData *data, Ihandle *ih, const char *name, int id)
{
  char nameid[100];
  iAttribSetNameId(nameid, name, id );
  return iupAttribGetBoolean( data, ih, nameid );
}

IUP_SDK_API float iupAttribGetFloatId( struct libData *data, Ihandle *ih, const char *name, int id)
{
  char nameid[100];
  iAttribSetNameId(nameid, name, id );
  return iupAttribGetFloat( data, ih, nameid );
}

IUP_SDK_API double iupAttribGetDoubleId( struct libData *data, Ihandle *ih, const char *name, int id)
{
  char nameid[100];
  iAttribSetNameId(nameid, name, id );
  return iupAttribGetDouble( data, ih, nameid );
}

IUP_SDK_API char *iupAttribGetId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col)
{
  char nameid[100];
  iAttribSetNameId2(nameid, name, lin, col );
  return iupAttribGet( data, ih, nameid );
}

IUP_SDK_API int iupAttribGetIntId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col)
{
  char nameid[100];
  iAttribSetNameId2(nameid, name, lin, col );
  return iupAttribGetInt( data, ih, nameid );
}

IUP_SDK_API int iupAttribGetBooleanId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col)
{
  char nameid[100];
  iAttribSetNameId2(nameid, name, lin, col );
  return iupAttribGetBoolean( data, ih, nameid );
}

IUP_SDK_API float iupAttribGetFloatId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col)
{
  char nameid[100];
  iAttribSetNameId2(nameid, name, lin, col );
  return iupAttribGetFloat( data, ih, nameid );
}

IUP_SDK_API double iupAttribGetDoubleId2( struct libData *data, Ihandle *ih, const char *name, int lin, int col)
{
  char nameid[100];
  iAttribSetNameId2(nameid, name, lin, col );
  return iupAttribGetDouble( data, ih, nameid );
}

IUP_SDK_API int iupAttribGetBoolean( struct libData *data, Ihandle *ih, const char *name)
{
  char *value = iupAttribGetStr( data, ih, name );
  if (value)
  {
    if (iupStrBoolean(value))
      return 1;
  }
  return 0;
}

IUP_SDK_API int iupAttribGetInt( struct libData *data, Ihandle *ih, const char *name)
{
  int i = 0;
  char *value = iupAttribGetStr( data, ih, name );
  if (value)
  {
    if ( ! iupStrToInt(value, &i))
    {
      if (iupStrBoolean(value))
        i = 1;
    }
  }
  return i;
}

IUP_SDK_API int iupAttribGetIntInt( struct libData *data, Ihandle *ih, const char *name, int *i1, int *i2, char sep)
{
  int _i1 = 0, _i2 = 0;
  char *value = iupAttribGetStr( data, ih, name );
  if (value)
  {
    int count = iupStrToIntInt(value, &_i1, &_i2, sep );
    if (i1) *i1 = _i1;
    if (i2) *i2 = _i2;
    return count;
  }
  return 0;
}

IUP_SDK_API float iupAttribGetFloat( struct libData *data, Ihandle *ih, const char *name)
{
  float f = 0;
  char *value = iupAttribGetStr( data, ih, name );
  if (value)
    iupStrToFloat(value, &f );
  return f;
}

IUP_SDK_API double iupAttribGetDouble( struct libData *data, Ihandle *ih, const char *name)
{
  double f = 0;
  char *value = iupAttribGetStr( data, ih, name );
  if (value)
    iupStrToDouble(  value, &f );
  return f;
}

IUP_SDK_API char *iupAttribGet( struct libData *data, Ihandle *ih, const char *name)
{
  if ( ! ih || !name)
    return NULL;
  return iupTableGet( data, ih->attrib, name );
}

IUP_SDK_API char *iupAttribGetStr( struct libData *data, Ihandle *ih, const char *name)
{
  char *value;
  if ( ! ih || !name)
    return NULL;

  value = iupTableGet( data, ih->attrib, name );

  if ( ! value && !iupATTRIB_ISINTERNAL(name))
  {
    int inherit;
    char *def_value;
    iupClassObjectGetAttributeInfo( data, ih, name, &def_value, &inherit );

    if (inherit)
    {
      while ( ! value)
      {
        ih = ih->parent;
        if ( ! ih)
          break;

        value = iupAttribGet( data, ih, name );
      }
    }

    if ( ! value)
      value = def_value;
  }

  return value;
}

IUP_SDK_API char *iupAttribGetLocal( struct libData *data, Ihandle *ih, const char *name)
{
  char *value;
  if ( ! ih || !name)
    return NULL;

  value = iupTableGet( data, ih->attrib, name );

  if ( ! value && !iupATTRIB_ISINTERNAL(name))
  {
    int inherit;
    char *def_value;
    value = iupClassObjectGetAttribute( data, ih, name, &def_value, &inherit );

    if ( ! value)
      value = def_value;
  }

  return value;
}

IUP_SDK_API char *iupAttribGetInherit( struct libData *data, Ihandle *ih, const char *name)
{
  char *value;
  if ( ! ih || !name)
    return NULL;

  value = iupAttribGet( data, ih, name );   /* Check on the element first */
  while ( ! value)
  {
    ih = ih->parent;   /* iheritance here independs on the attribute */
    if ( ! ih)
      return NULL;

    value = iupAttribGet( data, ih, name );
  }
  return value;
}

IUP_SDK_API char *iupAttribGetInheritNativeParent( struct libData *data, Ihandle *ih, const char *name)
{
  char *value;
  if ( ! ih || !name)
    return NULL;

  value = NULL;    /* Do NOT check on the element first */
  while ( ! value)
  {
    ih = iupChildTreeGetNativeParent( data, ih );
    if ( ! ih)
      return NULL;

    value = iupAttribGet( data, ih, name );
  }

  return value;
}

static const char *env_str = NULL;
static void iAttribCapture(char *env_buffer, char *dlm)
{
  int i=0;
  int c;
  do
  {
    c = *env_str; ++env_str;
    if (i < 256)
      env_buffer[i++] = (char) c;
  } while (c && !strchr(dlm,c));
  env_buffer[i-1]='\0';                                /* discard delimiter */
}

static void iAttribSkipComment( void )
{
  int c;
  do
  {
    c = *env_str; ++env_str;
  } while ((c > 0) && (c != '\n'));
}

static int iAttribToken( char *env_buffer )
{
  for (;;)
  {
    int c = *env_str; ++env_str;
    switch (c)
    {
    case 0:
      return IUPLEX_TK_END;

    case '#':          /* Skip comment */
    case '%':          /* Skip comment */
      iAttribSkipComment();
      continue;

    case ' ':          /* ignore whitespace */
    case '\t':
    case '\n':
    case '\r':
    case '\f':
    case '\v':
      continue;

    case '=':          /* attribuicao */
      return IUPLEX_TK_SET;

    case ',':
      return IUPLEX_TK_COMMA;

    case '\"':          /* string */
      iAttribCapture(env_buffer, "\"" );
      return IUPLEX_TK_NAME;

    default:
      if (c > 32)          /* identifier */
      {
        --env_str;                     /* unget first character of env_buffer */
        iAttribCapture(env_buffer, "=, \t\n\r\f\v" ); /* get env_buffer until delimiter */
        --env_str;                     /* unget delimiter */
        return IUPLEX_TK_NAME;
      }
    }
  }
}

IUP_SDK_API void iupAttribParse( struct libData *data, Ihandle *ih, const char *str, int save_led_info)
{
  char env_buffer[256];
  char *name=NULL;
  char *value=NULL;
  char state = 'a';               /* get attribute */
  int end = 0;

  env_str = str;

  for (;;)
  {
    switch (iAttribToken(env_buffer))
    {
    case IUPLEX_TK_END:           /* same as IUPLEX_TK_COMMA */
      end = 1;
      /* fall-through */
    case IUPLEX_TK_COMMA:
      if (name)
      {
        amy_IupStoreAttribute( data, ih, name, value );

        if (save_led_info)
        {
          char led_name[200] = "_IUPLED_SAVED_";
          strcat(led_name, name );
          iupAttribSet( data, ih, led_name, "1" );
        }

        free(name );
      }
      if (end)
        return;
      name = value = NULL;
      state = 'a';
      break;

    case IUPLEX_TK_SET:
      state = 'v';                /* get value */
      break;

    case IUPLEX_TK_NAME:
      if (state == 'a')
      {
        if (name) free(name );
        name = iupStrDup(env_buffer );
      }
      else
        value = env_buffer;
      break;
    }
  }
}

IUP_API Ihandle *amy_IupSetAttributes( struct libData *data, Ihandle *ih, const char *str)
{
  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return ih;
  if (str)
    iupAttribParse( data, ih, str, 0 );
  return ih;
}

IUP_SDK_API int iupAttribIsNotString( struct libData *data, Ihandle *ih, const char *name)
{
  return iupClassObjectAttribIsNotString( data, ih, name );
}

IUP_SDK_API int iupAttribIsIhandle( struct libData *data, Ihandle *ih, const char *name)
{
  return iupClassObjectAttribIsIhandle( data, ih, name );
}

typedef int (*Iconvertxytopos)( struct libData *, Ihandle *, int, int );

IUP_API int amy_IupConvertXYToPos( struct libData *data, Ihandle *ih, int x, int y )
{
	Iconvertxytopos drvConvertXYToPos;

	iupASSERT(iupObjectCheck( data, ih ));

	if ( ! iupObjectCheck( data, ih ))
		return -1;

	if ( ! ih->handle )
		return -1;

	drvConvertXYToPos = (Iconvertxytopos) amy_IupGetCallback( data, ih, "_IUP_XY2POS_CB" );

	if (drvConvertXYToPos)
		return drvConvertXYToPos( data, ih, x, y );

	return -1;
}

IUP_API int amy_IupStringCompare( struct libData *data, const char *str1, const char *str2, int casesensitive, int lexicographic)
{
  if (lexicographic)
  {
    int utf8 = amy_IupGetInt( data, NULL, "UTF8MODE" );
    return amy_iupStrCompare( data, str1, str2, casesensitive, utf8 );
  }
  else
  {
    if (casesensitive)
      return !iupStrEqual(str1, str2 );  /* return 0 if equal */
    else
      return !iupStrEqualNoCase(str1, str2 );  /* return 0 if equal */
  }
}
