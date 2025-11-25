
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
 * \brief list of all created dialogs
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdlib.h>

#include "iup.h"

#include "iup_dlglist.h"
#include "iup_object.h"
#include "iup_assert.h"
#include "iup_attrib.h"

#endif

typedef struct Idiallst_
{
  Ihandle *ih;
  struct Idiallst_ *next;
} Idiallst;

static Idiallst *idlglist = NULL;  /* list of all created dialogs */
static int idlg_count = 0;

IUP_SDK_API void iupDlgListAdd( struct libData *data, Ihandle *ih )
{
  if ( ih )
  {
    Idiallst *p=(Idiallst *)malloc(sizeof(Idiallst));
    if ( ! p)
      return;
    p->ih = ih;
    p->next = idlglist;
    idlglist = p;
    idlg_count++;
  }
}

IUP_SDK_API void iupDlgListRemove( struct libData *data, Ihandle *ih )
{
  if ( ! idlglist || !ih)
    return;

  if (idlglist->ih == ih)    /* ih is header */
  {
    Idiallst *p = idlglist->next;
    free(idlglist );
    idlglist = p;
    idlg_count--;
  }
  else
  {
    Idiallst *p;    /* current pointer */
    Idiallst *b;    /* before pointer */
    for (b = idlglist, p = idlglist->next; p; b = p, p = p->next)
    {
      if (p->ih == ih)
      {
        b->next = p->next;
        free (p );
        idlg_count--;
        return;
      }
    }
  }
}

static Idiallst *idlg_first = NULL;

IUP_SDK_API int iupDlgListCount( struct libData *data )
{
  return idlg_count;
}

IUP_SDK_API Ihandle *iupDlgListFirst( struct libData *data )
{
  idlg_first = idlglist;
  return iupDlgListNext( data );
}

IUP_SDK_API Ihandle *iupDlgListNext( struct libData *data )
{
  Ihandle *ih = NULL;
  if (idlg_first)
  {
    ih = idlg_first->ih;
    idlg_first = idlg_first->next;
  }
  return ih;
}

static int idlg_nvisiblewin = 0;

IUP_SDK_API void iupDlgListVisibleInc( struct libData *data )
{
  iupASSERT(idlg_nvisiblewin < idlg_count );
  if (idlg_nvisiblewin == idlg_count)
    return;
  idlg_nvisiblewin++;
}

IUP_SDK_API void iupDlgListVisibleDec( struct libData *data )
{
  iupASSERT(idlg_nvisiblewin > 0 );
  idlg_nvisiblewin--;
}

IUP_SDK_API int iupDlgListVisibleCount( struct libData *data )
{
  return idlg_nvisiblewin;
}

void iupDlgListDestroyAll( struct libData *data )
{
  int i, count = 0;
  Ihandle** ih_array = (Ihandle**)malloc(idlg_count * sizeof(Ihandle*));
  Idiallst *list;
  for (list = idlglist; list; list = list->next)
  {
    if (iupObjectCheck( data, list->ih ))
    {
      ih_array[count] = list->ih;
      count++;
    }
  }

  for (i = 0; i < count; i++)
  {
    if (iupObjectCheck( data, ih_array[i] ))
      amy_IupDestroy( data, ih_array[i] );   /* this will also destroy the list eventually */
  }

  free(ih_array );
}

IUP_SDK_API void iupDlgListDestroySelected( struct libData *data, const char *name, void *value )
{
  int i, count = 0;
  Ihandle** ih_array = (Ihandle**)malloc(idlg_count * sizeof(Ihandle*));
  Idiallst *list;
  for (list = idlglist; list; list = list->next)
  {
    if (iupObjectCheck( data, list->ih ) && ((value && iupAttribGet( data, list->ih, name ) == value) || ( ! value && iupAttribGet( data, list->ih, name ))))
    {
      ih_array[count] = list->ih;
      count++;
    }
  }

  for (i = 0; i < count; i++)
  {
    if (iupObjectCheck( data, ih_array[i] ))
      amy_IupDestroy( data, ih_array[i] );
  }

  free(ih_array );
}
