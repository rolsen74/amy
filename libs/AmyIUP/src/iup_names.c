
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
 * \brief Ihandle <-> Name table manager.
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdlib.h>
#include <memory.h>

#include "iup.h"

#include "iup_str.h"
#include "iup_table.h"
#include "iup_names.h"
#include "iup_object.h"
#include "iup_class.h"
#include "iup_assert.h"
#include "iup_attrib.h"
#include "iup_str.h"


/* An Ihandle *may have many different handle names. 
   Do not confuse with the NAME attribute. */

static Itable *inames_strtable = NULL;   /* table indexed by name containing Ihandle *address */
#endif

void iupNamesInit( struct libData *data )
{
	data->inames_strtable = iupTableCreate( data, IUPTABLE_STRINGINDEXED );
}

void iupNamesFinish( struct libData *data )
{
  iupTableDestroy( data, data->inames_strtable );
  data->inames_strtable = NULL;
}

static Ihandle *iNameGetTopParent( struct libData *data, Ihandle *ih )
{
  Ihandle *parent = ih;
  while (parent->parent)
    parent = parent->parent;
  return parent;
}

static int iNameCheckArray( struct libData *data, Ihandle **ih_array, int count, Ihandle *ih )
{
  int i;
  for (i = 0; i < count; i++)
  {
    if ( ih_array[i] == ih)
      return 0;
  }
  return 1;
}

void iupNamesDestroyHandles( struct libData *data )
{
  char *name;
  Ihandle** ih_array, *ih;
  int count, i = 0;

  count = iupTableCount( data, data->inames_strtable );
  if ( ! count)
    return;

  ih_array = (Ihandle**)malloc(count * sizeof(Ihandle*));
  memset(ih_array, 0, count * sizeof(Ihandle*));

  /* store the handles before updating so we can remove elements in the loop */
  name = iupTableFirst( data, data->inames_strtable );
  while (name)
  {
    ih = (Ihandle*) iupTableGetCurr( data, data->inames_strtable );
    if ( iupObjectCheck( data, ih ))   /* here must be a handle */
    {
      /* only need to destroy the top parent handle */
      ih = iNameGetTopParent( data, ih );

      /* check if already in the array */
      if ( iNameCheckArray( data, ih_array, i, ih ))
      {
        ih_array[i] = ih;
        i++;
      }
    }
    name = iupTableNext( data, data->inames_strtable );
  }

  count = i;
  for (i = 0; i < count; i++)
  {
    if ( iupObjectCheck( data, ih_array[i] ))  /* here must be a handle */
      amy_IupDestroy( data, ih_array[i] );
  }

  free(ih_array );
}

IUP_SDK_API void iupNamesDestroyHandlesSelected( struct libData *data, const char *attrib_name, void *attrib_value)
{
  char *name;
  Ihandle** ih_array, *ih;
  int count, i = 0;

  count = iupTableCount( data, data->inames_strtable );
  if ( ! count)
    return;

  ih_array = (Ihandle**)malloc(count * sizeof(Ihandle*));
  memset(ih_array, 0, count * sizeof(Ihandle*));

  /* store the handles before updating so we can remove elements in the loop */
  name = iupTableFirst( data, data->inames_strtable );
  while (name)
  {
    ih = (Ihandle*) iupTableGetCurr( data, data->inames_strtable );
    if ( iupObjectCheck( data, ih ) && ((attrib_value && iupAttribGet( data, ih, attrib_name) == attrib_value) || ( ! attrib_value && iupAttribGet( data, ih, attrib_name))))
    {
      /* only need to destroy the top parent handle */
      ih = iNameGetTopParent( data, ih );

      /* check if already in the array */
      if ( iNameCheckArray( data, ih_array, i, ih ))
      {
        ih_array[i] = ih;
        i++;
      }
    }
    name = iupTableNext( data, data->inames_strtable );
  }

  count = i;
  for (i = 0; i < count; i++)
  {
    if ( iupObjectCheck( data, ih_array[i] ))  /* here must be a handle */
      amy_IupDestroy( data, ih_array[i] );
  }

  free(ih_array );
}

void iupRemoveNames( struct libData *data, Ihandle *ih )
{
  /* called from amy_IupDestroy */
  char *name;

  /* ih here is an Ihandle **/

  /* check for at least one name (the last one set) */
  name = iupAttribGetHandleName( data, ih );
  if (name)
    iupTableRemove( data, data->inames_strtable, name );

  /* clear also the NAME attribute */
  iupBaseSetNameAttrib( data, ih, NULL );

  /* Do NOT search for other names, this would implying in checking in all store names.
     So, some names may have left invalid on the handle names database. */
}

IUP_API Ihandle *amy_IupGetHandle( struct libData *data, const char *name )
{
  if ( ! name) /* no iupASSERT needed here */
    return NULL;
  return (Ihandle*) iupTableGet( data, data->inames_strtable, name );
}

int iupNamesFindAll( struct libData *data, Ihandle *ih, char **names, int n )
{
  int i = 0;
  char *name = iupTableFirst( data, data->inames_strtable );
  while (name)
  {
    if ((Ihandle*) iupTableGetCurr( data, data->inames_strtable) == ih)
    {
      if (names)
        names[i] = name;

      i++;
      if ( i == n && n != 0 && n != -1)
        break;
    }

    name = iupTableNext( data, data->inames_strtable );
  }

  return i;
}

static char *iNameFindHandle( struct libData *data, Ihandle *ih )
{
  /* search for a name */
  char *name = iupTableFirst( data, data->inames_strtable );
  while (name)
  {
    /* return the first one found */
    if ((Ihandle*) iupTableGetCurr( data, data->inames_strtable) == ih)
      return name;

    name = iupTableNext( data, data->inames_strtable );
  }
  return NULL;
}

IUP_API Ihandle *amy_IupSetHandle( struct libData *data, const char *name, Ihandle *ih )
{
  Ihandle *old_ih;

  iupASSERT(name!=NULL );
  if ( ! name)
    return NULL;

  /* ih here can be also an user pointer, not just an Ihandle **/

  /* we do not check if the handle already has names, it may has many different names */

  old_ih = iupTableGet( data, data->inames_strtable, name );

  if ( ih != NULL)
  {
    iupTableSet( data, data->inames_strtable, name, ih, IUPTABLE_POINTER );

    /* save the name in the cache if it is a valid handle */
    if ( iupObjectCheck( data, ih ))
      iupAttribSetStr( data, ih, "HANDLENAME", name );
  }
  else
  {
    iupTableRemove( data, data->inames_strtable, name );

    /* clear the name from the cache if it is a valid handle */
    if ( iupObjectCheck( data, old_ih ))
    {
      char *last_name = iupAttribGet( data, old_ih, "HANDLENAME" );
      if (last_name && iupStrEqual(last_name, name))
      {
        iupAttribSet( data, old_ih, "HANDLENAME", NULL );  /* remove also from the cache */

        last_name = iNameFindHandle( data, old_ih );
        if (last_name)
          iupAttribSetStr( data, old_ih, "HANDLENAME", last_name );  /* if found another name save it in the cache */
      }
    }
  }

  return old_ih;
}

IUP_API char *amy_IupGetName( struct libData *data, Ihandle *ih )
{
  if ( ! ih) /* no iupASSERT needed here */
    return NULL;

  /* ih here can be also an user pointer, not just an Ihandle **/

  if ( iupObjectCheck( data, ih )) /* if ih is an Ihandle **/
  {
    /* check for a name */
    return iupAttribGetHandleName( data, ih );
  }

  /* search for a name */
  return iNameFindHandle( data, ih );
}

IUP_API int amy_IupGetAllNames( struct libData *data, char **names, int n )
{
  int i = 0;
  char *name;

  if ( ! names || n == 0 || n == -1)
    return iupTableCount( data, data->inames_strtable );

  name = iupTableFirst( data, data->inames_strtable );
  while (name)
  {
    names[i] = name;
    i++;
    if ( i == n)
      break;

    name = iupTableNext( data, data->inames_strtable );
  }
  return i;
}

static int iNamesCountDialogs( struct libData *data )
{
  int i = 0;
  char *name = iupTableFirst( data, data->inames_strtable );
  while (name)
  {
    Ihandle *dlg = (Ihandle*) iupTableGetCurr( data, data->inames_strtable );
    if ( iupObjectCheck( data, dlg ) &&  /* here must be a handle */
        dlg->iclass->nativetype == IUP_TYPEDIALOG)
      i++;

    name = iupTableNext( data, data->inames_strtable );
  }
  return i;
}

IUP_API int amy_IupGetAllDialogs( struct libData *data, char** names, int n )
{
  int i = 0;
  char *name;

  if ( ! names || n==0 || n==-1)
    return iNamesCountDialogs( data );

  name = iupTableFirst( data, data->inames_strtable );
  while (name)
  {
    Ihandle *dlg = (Ihandle*) iupTableGetCurr( data, data->inames_strtable );
    if ( iupObjectCheck( data, dlg ) &&  /* here must be a handle */
        dlg->iclass->nativetype == IUP_TYPEDIALOG)
    {
      names[i] = name;
      i++;
      if ( i == n)
        break;
    }

    name = iupTableNext( data, data->inames_strtable );
  }
  return i;
}
