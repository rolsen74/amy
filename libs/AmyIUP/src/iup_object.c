
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
 * \brief Ihandle management
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdio.h>  
#include <stdlib.h>  
#include <memory.h>  

#include "iup.h"

#include "iup_object.h"
#include "iup_assert.h"
#include "iup_register.h"
#include "iup_names.h"
#include "iup_varg.h"
#include "iup_focus.h"
#include "iup_attrib.h"

#endif

static Ihandle *iHandleCreate( struct libData *data )
{
  Ihandle *ih = (Ihandle*)malloc(sizeof(Ihandle));
  memset( ih, 0, sizeof(Ihandle));

  ih->sig[0] = 'I';
  ih->sig[1] = 'U';
  ih->sig[2] = 'P';
  ih->sig[3] = 0;

  ih->serial = -1;

  ih->attrib = iupTableCreate( data, IUPTABLE_STRINGINDEXED );

  return ih;
}

static void iHandleDestroy( struct libData *data, Ihandle *ih )
{
  iupTableDestroy( data, ih->attrib );
  memset( ih, 0, sizeof(Ihandle));
  free( ih );
}

IUP_SDK_API int iupObjectCheck( struct libData *data, Ihandle *ih )
{
  char *sig = (char*)ih;

  if ( ! ih) return 0;  

  if (sig[0] != 'I' ||
      sig[1] != 'U' ||
      sig[2] != 'P' ||
      sig[3] != 0)
    return 0;

  return 1;
}

IUP_SDK_API Ihandle *iupObjectCreate( struct libData *data, Iclass *iclass, void **params )
{
  char *name;

  /* create the base handle structure */
  Ihandle *ih = iHandleCreate( data );

  ih->iclass = iclass;

  /* create the element */
  if (iupClassObjectCreate( data, ih, params) == IUP_ERROR)
  {
    iupERROR1("IUP object creation failed (%s).", iclass->name );
    iHandleDestroy( data, ih );
    return NULL;
  }

  /* ensure attributes default values, at this time only the ones that can be set before map */
  iupClassObjectEnsureDefaultAttributes( data, ih );

  name = amy_IupGetGlobal( data, "DEFAULTTHEME" );
  if (name)
  {
    Ihandle *theme = amy_IupGetHandle( data, name );
    if (theme)
      iupAttribSetTheme( data, ih, theme );
  }

  return ih;
}

IUP_SDK_API void** iupObjectGetParamList( struct libData *data, void *first, va_list arglist )
{
  const int INITIAL_NUMBER = 50;
  void **params;
  void *param;
  int max_count = INITIAL_NUMBER, count = 0;

  params = (void **) malloc (sizeof (void *) * INITIAL_NUMBER );

  param = first;

  while (param != NULL)
  {
    params[count] = param;
    count++;

    /* check if needs to allocate memory */
    if (count >= max_count)
    {
      void **new_params = NULL;

      max_count += INITIAL_NUMBER;

      new_params = (void **) realloc (params, sizeof (void *) * max_count );

      params = new_params;
    }

    param = va_arg (arglist, void* );
  }
  params[count] = NULL;

  return params;
}

IUP_API Ihandle *amy_IupCreatev( struct libData *data, const char *name, void **params )
{
  Iclass *ic;
  iupASSERT(name!=NULL );
  ic = iupRegisterFindClass( data,  name );
  if (ic)
    return iupObjectCreate( data, ic, params );
  else
    return NULL;
}

IUP_API Ihandle *amy_IupCreateV( struct libData *data, const char *name, void *first, va_list arglist )
{
  void **params;
  Ihandle *ih;

  iupASSERT(name != NULL );

  params = iupObjectGetParamList( data, first, arglist );
  ih = amy_IupCreatev( data, name, params );
  free( params );

  return ih;
}

IUP_API Ihandle *amy_IupCreatep( struct libData *data, const char *name, void *first, ... )
{
  va_list arglist;
  Ihandle *ih;

  iupASSERT(name!=NULL );

  va_start( arglist, first );
  ih = amy_IupCreateV( data, name, first, arglist );
  va_end( arglist );

  return ih;
}

IUP_API Ihandle *amy_IupCreate( struct libData *data, const char *name )
{
  iupASSERT(name!=NULL );
  return amy_IupCreatev( data, name, NULL );
}

IUP_API void amy_IupDestroy( struct libData *data, Ihandle *ih )
{
  Icallback cb;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return;

  /* Hide before destroy to avoid children redraw */
  if (ih->iclass->nativetype == IUP_TYPEDIALOG)
    amy_IupHide( data, ih );

  cb = amy_IupGetCallback( data, ih, "DESTROY_CB" );
  if (cb) cb( data,ih );

  /* Destroy all its children.
     Just need to remove the first child,
     amy_IupDetach will update firstchild. */
  while (ih->firstchild)
    amy_IupDestroy( data, ih->firstchild );

  /* unmap if mapped and remove from its parent child list */
  amy_IupDetach( data, ih );

  cb = amy_IupGetCallback( data, ih, "LDESTROY_CB" );  /* for language bindings */
  if (cb) cb( data,ih );

  /* check if the element had the focus */
  iupResetCurrentFocus( data, ih );

  /* removes names associated with the element */
  iupRemoveNames( data, ih );

  /* destroy the element */
  iupClassObjectDestroy( data, ih );

  /* destroy the private data */
  if (ih->data)
    free(ih->data );

  /* destroy the base handle structure */
  iHandleDestroy( data, ih );
}
