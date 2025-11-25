
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
 * \brief global attributes environment
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdlib.h>      
#include <stdio.h>      
#include <string.h>      

#include "iup.h" 

#include "iup_table.h"
#include "iup_globalattrib.h"
#include "iup_table.h"
#include "iup_class.h"
#include "iup_drv.h"
#include "iup_drvfont.h"
#include "iup_drvinfo.h"
#include "iup_assert.h"
#include "iup_str.h"
#include "iup_strmessage.h"
#include "iup_attrib.h"


static Itable *data->iglobal_table = NULL;

#endif

void iupGlobalAttribInit( struct libData *data )
{
	data->iglobal_table = iupTableCreate( data, IUPTABLE_STRINGINDEXED );
}

void iupGlobalAttribFinish( struct libData *data )
{
  iupTableDestroy( data, data->iglobal_table );
  data->iglobal_table = NULL;
}

static int iGlobalChangingDefaultColor( struct libData *data, const char *name )
{
	if ( iupClassIsGlobalDefault( name, 1 ))
	{
		char str[50] = "_IUP_USER_DEFAULT_";
		strcat(str, name );
		iupTableSet( data, data->iglobal_table, str, (void*)"1", IUPTABLE_POINTER );  /* mark as changed by the User */
		return 1;
	}
	return 0;
}

int iupGlobalDefaultColorChanged( struct libData *data, const char *name)
{
  char str[50] = "_IUP_USER_DEFAULT_";
  strcat(str, name );
  return iupTableGet( data, data->iglobal_table, str) != NULL;
}

void iupGlobalSetDefaultColorAttrib( struct libData *data, const char *name, int r, int g, int b)
{
  if ( ! iupGlobalDefaultColorChanged( data, name ))
  {
    char value[50];
    sprintf(value, "%d %d %d", r, g, b );
    iupTableSet( data,  data->iglobal_table, name, (void*)value, IUPTABLE_STRING );
  }
}

static void iGlobalTableSet( struct libData *data, const char *name, const char *value, int store )
{
	if ( ! value)
		iupTableRemove( data, data->iglobal_table, name );
	else if (store)
		iupTableSet( data,  data->iglobal_table, name, (void*)value, IUPTABLE_STRING );
	else
		iupTableSet( data,  data->iglobal_table, name, (void*)value, IUPTABLE_POINTER );
}

static void iGlobalSet( struct libData *data, const char *name, const char *value, int store )
{
	iupASSERT(name!=NULL );
	if ( ! name) return;

	if ( iupStrEqual( name, "DEFAULTFONTSIZE" ))
	{
		iupSetDefaultFontSizeGlobalAttrib( data, value );
		return;
	}

	if ( iupStrEqual( name, "DEFAULTFONTSTYLE" ))
	{
		iupSetDefaultFontStyleGlobalAttrib( data, value );
		return;
	}

	if ( iupStrEqual( name, "DEFAULTFONTFACE" ))
	{
		iupSetDefaultFontFaceGlobalAttrib( data, value );
		return;
	}

	if ( iupStrEqual( name, "KEYPRESS" ))
	{
		int key;
		if ( iupStrToInt(value, &key))
		iupdrvSendKey( data, key, 0x01 );
		return;
	}

	if ( iupStrEqual( name, "KEYRELEASE" ))
	{
		int key;
		if ( iupStrToInt(value, &key))
		iupdrvSendKey( data, key, 0x02 );
		return;
	}

	if ( iupStrEqual( name, "KEY" ))
	{
		int key;
		if ( iupStrToInt(value, &key))
		iupdrvSendKey( data, key, 0x03 );
		return;
	}

	if ( iupStrEqual( name, "LANGUAGE" ))
	{
		char *old_language = (char*) iupTableGet( data, data->iglobal_table, "LANGUAGE" );
		if ( ! iupStrEqualNoCase(old_language, value))  /* if different than the current */
		{
			iGlobalTableSet( data, name, value, store );
			iupStrMessageUpdateLanguage( data, value );
		}
		return;
	}

	if ( iupStrEqual( name, "CURSORPOS" ))
	{
		int x, y;
		if ( iupStrToIntInt(value, &x, &y, 'x') == 2)
			iupdrvWarpPointer( data, x, y );
		return;
	}

	if ( iupStrEqual( name, "MOUSEBUTTON" ))
	{
		int x, y, status;
		char bt; 
		if (value && sscanf(value, "%dx%d %c %d", &x, &y, &bt, &status) == 4)
			iupdrvSendMouse( data, x, y, bt, status );
		return;
	}

	if ( iGlobalChangingDefaultColor( data, name ) || iupdrvSetGlobal( data, name, value))
		iGlobalTableSet( data, name, value, store );
}

IUP_API void amy_IupSetGlobal( struct libData *data, const char *name, const char *value)
{
  iGlobalSet( data, name, value, 0 );
}

IUP_API void amy_IupStoreGlobal( struct libData *data, const char *name, const char *value)
{
  iGlobalSet( data, name, value, 1 );
}

IUP_API void amy_IupSetStrGlobal( struct libData *data, const char *name, const char *value )
{
  iGlobalSet( data, name, value, 1 );
}

IUP_API char *amy_IupGetGlobal( struct libData *data, const char *name )
{
	char *value;
	
	iupASSERT(name!=NULL );
	if ( ! name) 
		return NULL;

	if ( iupStrEqual( name, "DEFAULTFONTSIZE" ))
		return iupGetDefaultFontSizeGlobalAttrib( data );
	if ( iupStrEqual( name, "DEFAULTFONTSTYLE" ))
		return iupGetDefaultFontStyleGlobalAttrib( data );
	if ( iupStrEqual( name, "DEFAULTFONTFACE" ))
		return iupGetDefaultFontFaceGlobalAttrib( data );
	if ( iupStrEqual( name, "CURSORPOS" ))
	{
		int x, y;
		iupdrvGetCursorPos( data, &x, &y );
		return iupStrReturnIntInt(x, y, 'x' );
	}
	if ( iupStrEqual( name, "SHIFTKEY" ))
	{
		char key[5];
		iupdrvGetKeyState( data, key );
		return iupStrReturnChecked(key[0] == 'S' );
	}
	if ( iupStrEqual( name, "CONTROLKEY" ))
	{
		char key[5];
		iupdrvGetKeyState( data, key );
		return iupStrReturnChecked(key[1] == 'C' );
	}
	if ( iupStrEqual( name, "MODKEYSTATE" ))
	{
		char *str = iupStrGetMemory(5 );
		iupdrvGetKeyState( data, str );
		return str;
	}
	if ( iupStrEqual( name, "SCREENSIZE" ))
	{
		int w, h;
		iupdrvGetScreenSize( data, &w, &h );
		return iupStrReturnIntInt(w, h, 'x' );
	}
	if ( iupStrEqual( name, "FULLSIZE" ))
	{
		int w, h;
		iupdrvGetFullSize( data, &w, &h );
		return iupStrReturnIntInt(w, h, 'x' );
	}
	if ( iupStrEqual( name, "SCREENDEPTH" ))
	{
		int bpp = iupdrvGetScreenDepth( data );
		return amy_iupStrReturnInt( data, bpp );
	}
	if ( iupStrEqual( name, "SCREENDPI" ))
	{
		double dpi = iupdrvGetScreenDpi( data );
		return iupStrReturnDouble(dpi );
	}
	if ( iupStrEqual( name, "SYSTEMLOCALE" ))
		return iupdrvLocaleInfo( data );
	if ( iupStrEqual( name, "SCROLLBARSIZE" ))
		return amy_iupStrReturnInt( data, iupdrvGetScrollbarSize( data ));

	value = iupdrvGetGlobal( data, name );

	if ( ! value)
		value = (char*) iupTableGet( data, data->iglobal_table, name );

	return value;
}

IUP_SDK_API int iupGlobalIsPointer( struct libData *data, const char *name )
{
  static struct {
    const char *name;
  } ptr_table[] = {
#ifndef GTK_MAC
  #ifdef WIN32
    {"HINSTANCE"},
    {"DLL_HINSTANCE"},
  #else
    {"XDISPLAY"},
    {"XSCREEN"},
    {"APPSHELL"},
  #endif
#endif
  };
#define PTR_TABLE_SIZE ((sizeof ptr_table)/(sizeof ptr_table[0] ))

  if (name)
  {
    int i;
    for (i = 0; i < PTR_TABLE_SIZE; i++)
    {
      if ( iupStrEqualNoCase( name, ptr_table[i].name))
        return 1;
    }
  }

  return 0;
}

int iupGetGlobalAttributes( struct libData *data, char **names, int n )
{
  int count = iupTableCount( data, data->iglobal_table );
  char * name;
  int i = 0;

  if (n == 0 || n == -1)
    return count;

  name = iupTableFirst( data, data->iglobal_table );
  while (name)
  {
    if ( ! iupATTRIB_ISINTERNAL(name))
    {
      names[i] = name;
      i++;
      if ( i == n)
        break;
    }

    name = iupTableNext( data, data->iglobal_table );
  }

  return i;
}
