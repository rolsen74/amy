
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
 * \brief String Utilities
 *
 * See Copyright Notice in "iup.h"
 */

 
#include <string.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <limits.h>  
#include <stdarg.h>

#include "iup.h"

#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_strmessage.h"
#include "iup_table.h"
#include "iup_register.h"

static Itable *data->istrmessage_table = NULL;   /* the message hash table indexed by the name string */

#endif

void iupStrMessageInit( struct libData *data )
{
	data->istrmessage_table = iupTableCreate( data, IUPTABLE_STRINGINDEXED );
}

void iupStrMessageFinish( struct libData *data )
{
  iupTableDestroy( data, data->istrmessage_table );
  data->istrmessage_table = NULL;
}

IUP_API char *amy_IupGetLanguageString( struct libData *data, const char *name )
{
  char *value;
  if ( ! name) return NULL;
  value = (char*) iupTableGet( data, data->istrmessage_table, name );
  if ( ! value)
    return (char*)name;
  return value;
}

IUP_API void amy_IupSetLanguageString( struct libData *data, const char *name, const char *str )
{
	iupTableSet( data, data->istrmessage_table, name, (char*)str, IUPTABLE_POINTER );
}

IUP_API void amy_IupStoreLanguageString( struct libData *data, const char *name, const char *str )
{
	iupTableSet( data, data->istrmessage_table, name, (char*)str, IUPTABLE_STRING );
}

IUP_API void amy_IupSetLanguagePack( struct libData *data, Ihandle *ih )
{
	if ( ! ih)
		iupTableClear( data, data->istrmessage_table );
	else
	{
		char *name, *value;

		name = iupTableFirst( data, ih->attrib );

		while (name)
		{
			value = (char*) iupTableGetCurr( data, ih->attrib );

			if ( iupTableGetCurrType( data, ih->attrib )==IUPTABLE_STRING)
				iupTableSet( data, data->istrmessage_table, name, value, IUPTABLE_STRING );
			else
				iupTableSet( data, data->istrmessage_table, name, value, IUPTABLE_POINTER );

			name = iupTableNext( data, ih->attrib );
		}
	}
}

IUP_API void amy_IupSetLanguage( struct libData *data, const char *language )
{
	amy_IupStoreGlobal( data, "LANGUAGE", language );
}

IUP_API char *amy_IupGetLanguage( struct libData *data )
{
	return amy_IupGetGlobal( data, "LANGUAGE" );
}


/**********************************************************************************/

static void iupSetLngAttV( struct libData *data, const char *first, va_list arglist )
{
  const char *name, *str;
  name = first;
  while (name)
  {
    str = va_arg(arglist, const char *);

    amy_IupSetLanguageString( data, name, str );

    name = va_arg(arglist, const char *);
  }
}

static void iupSetLngAtt( struct libData *data, const char *first, ... )
{
  va_list arglist;
  va_start(arglist, first );
  iupSetLngAttV( data, first, arglist );
  va_end(arglist );
}

#include "iup_lng_english.h"
#include "iup_lng_portuguese.h"
#include "iup_lng_portuguese_utf8.h"
#include "iup_lng_spanish.h"
#include "iup_lng_spanish_utf8.h"
#ifdef IUP_CZECH
#include "iup_lng_czech_utf8.h"
#endif
#ifdef IUP_RUSSIAN
#include "iup_lng_russian_utf8.h"
#endif

static void iStrMessageRegisterInternal( struct libData *data, const char *language )
{
	Ihandle *lng = NULL;

	if ( iupStrEqualNoCase(language, "ENGLISH" ))
	{
		lng = iup_load_lng_english( data );
	}
	else if ( iupStrEqualNoCase(language, "PORTUGUESE" ))
	{
		if ( amy_IupGetInt( data, NULL, "UTF8MODE" ))
			lng = iup_load_lng_portuguese_utf8( data );
		else
			lng = iup_load_lng_portuguese( data );
	}
	else if ( iupStrEqualNoCase(language, "SPANISH" ))
	{
		if ( amy_IupGetInt( data, NULL, "UTF8MODE" ))
			lng = iup_load_lng_spanish_utf8( data );
		else
			lng = iup_load_lng_spanish( data );
	}
	/* To add a custom language */
#ifdef IUP_CZECH
	else if ( iupStrEqualNoCase(language, "CZECH" ))
	{
		if ( amy_IupGetInt( data, NULL, "UTF8MODE" ))
			lng = iup_load_lng_czech_utf8( data );
	}
#endif
#ifdef IUP_RUSSIAN
	else if ( iupStrEqualNoCase(language, "RUSSIAN" ))
	{
		if ( amy_IupGetInt( data, NULL, "UTF8MODE" ))
			lng = iup_load_lng_russian_utf8( data );
	}
#endif

	if (lng)
	{
		amy_IupSetLanguagePack( data, lng );
		amy_IupDestroy( data, lng );
	}
}

void iupStrMessageUpdateLanguage( struct libData *data, const char *language )
{
	/* called after the global attribute is changed */

	iStrMessageRegisterInternal(data, language );

	iupRegisterUpdateClasses( data );
}

void iupSaveLanguagePack( struct libData *data, const char *filename )
{
  char *name, *value;
  int utf8mode = amy_IupGetInt( data, NULL, "UTF8MODE" );
  char *lng = amy_IupGetLanguage( data );

  FILE* file = fopen(filename, "wb" );

  fprintf(file, "%s%s = user[\n", lng, utf8mode? "_UTF8": "" );

  name = iupTableFirst( data, data->istrmessage_table );
  while (name)
  {
    value = (char*) iupTableGetCurr( data, data->istrmessage_table );

    fprintf(file, "  %s = \"%s\",\n", name, value );

    name = iupTableNext( data, data->istrmessage_table );
  }

  fprintf(file, "NULL = NULL\n" );
  fprintf(file, "]( data )\n" );

  fclose(file );
}
