
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
 * \brief function table manager
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdlib.h> 

#include "iup.h"

#include "iup_str.h"
#include "iup_table.h"
#include "iup_func.h"
#include "iup_drv.h"
#include "iup_assert.h"
#include "iup_attrib.h"


static Itable *data->ifunc_table = NULL;   /* the function hash table indexed by the name string */

#endif

void iupFuncInit( struct libData *data )
{
	data->ifunc_table = iupTableCreate( data, IUPTABLE_STRINGINDEXED );
}

void iupFuncFinish( struct libData *data )
{
  iupTableDestroy( data, data->ifunc_table );
  data->ifunc_table = NULL;
}

IUP_API Icallback amy_IupGetFunction( struct libData *data, const char *name )
{
  void *value;

  iupASSERT(name != NULL );
  if ( ! name)
    return NULL;

  return (Icallback) iupTableGetFunc( data, data->ifunc_table, name, &value );
}

IUP_API Icallback amy_IupSetFunction( struct libData *data, const char *name, Icallback func )
{
  void *value;
  Icallback old_func;

  iupASSERT(name != NULL );
  if ( ! name)
    return NULL;

  old_func = (Icallback) iupTableGetFunc( data, data->ifunc_table, name, &value );

  if ( ! func)
    iupTableRemove( data, data->ifunc_table, name );
  else
    iupTableSetFunc( data, data->ifunc_table, name, (Ifunc)func );

  /* notifies the driver if changing the Idle */
  if ( iupStrEqual( name, "IDLE_ACTION" ))
    iupdrvSetIdleFunction( data, func );

  return old_func;
}

int iupGetFunctions( struct libData *data, char **names, int n )
{
  int count = iupTableCount( data, data->ifunc_table );
  char * name;
  int i = 0;

  if (n == 0 || n == -1)
    return count;

  name = iupTableFirst( data, data->ifunc_table );
  while (name)
  {
    if ( ! iupATTRIB_ISINTERNAL(name))
    {
      names[i] = name;
      i++;
      if ( i == n)
        break;
    }

    name = iupTableNext( data, data->ifunc_table );
  }

  return i;
}
