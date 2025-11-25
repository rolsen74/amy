
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
 * \brief get/set callback
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdlib.h> 
#include <stdarg.h>

#include "iup.h"

#include "iup_object.h"
#include "iup_assert.h"
#include "iup_varg.h"

#endif

char *iupGetCallbackName( struct libData *data, Ihandle *ih, const char *name)
{
  void *value;
  Icallback func = (Icallback) iupTableGetFunc( data, ih->attrib, name, &value );

  if ( ! func && value)
  {
    /* if not a IUPTABLE_FUNCPOINTER then it is an old fashion name */
    return value;
  }

  return NULL;
}

IUP_API Icallback amy_IupGetCallback( struct libData *data, Ihandle *ih, const char *name )
{
  Icallback func = NULL;
  void *value;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return NULL;

  iupASSERT(name!=NULL );
  if ( ! name) 
    return NULL;

  func = (Icallback) iupTableGetFunc( data, ih->attrib, name, &value );

  if ( ! func && value)
  {
    /* if not a IUPTABLE_FUNCPOINTER then it is an old fashion name */
    func = amy_IupGetFunction( data, (const char*)value );
  }

  return func;
}

IUP_API Icallback amy_IupSetCallback( struct libData *data, Ihandle *ih, const char *name, Icallback func)
{
  Icallback old_func = NULL;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return NULL;

  iupASSERT(name!=NULL );
  if ( ! name) 
    return NULL;

  if ( ! func)
    iupTableRemove( data, ih->attrib, name );
  else
  {
    void *value;
    old_func = (Icallback) iupTableGetFunc( data, ih->attrib, name, &value );
    if ( ! old_func && value)
      old_func = amy_IupGetFunction( data, (const char*)value );

    iupTableSetFunc( data, ih->attrib, name, (Ifunc)func );
  }

  return old_func;
}

IUP_API Ihandle *amy_IupSetCallbacksV( struct libData *data, Ihandle *ih, const char *name, Icallback func, va_list arglist)
{
  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return NULL;

  amy_IupSetCallback( data, ih, name, func );

  name = va_arg(arglist, const char *);
  while (name)
  {
    func = va_arg(arglist, Icallback );
    amy_IupSetCallback( data, ih, name, func );

    name = va_arg(arglist, const char *);
  }

  return ih;
}

IUP_API Ihandle *amy_IupSetCallbacks( struct libData *data, Ihandle *ih, const char *name, Icallback func, ... )
{
  va_list arglist;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return NULL;

  va_start(arglist, func );
  amy_IupSetCallbacksV( data, ih, name, func, arglist );
  va_end (arglist );
  return ih;
}
