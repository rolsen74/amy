
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
 * \brief Keyboard Focus navigation
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdio.h>

#include "iup.h"
#include "iupcbs.h"

#include "iup_object.h"
#include "iup_focus.h"
#include "iup_class.h"
#include "iup_assert.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_drv.h"
#include "iup_childtree.h"

#endif

IUP_SDK_API Ihandle *iupFocusNextInteractive( struct libData *data, Ihandle *ih )
{
  Ihandle *c;

  if ( ! ih)
    return NULL;

  for (c = ih->brother; c; c = c->brother)
  {
    if (c->iclass->is_interactive)
      return c;
  }

  return NULL;
}

IUP_SDK_API int iupFocusCanAccept( struct libData *data, Ihandle *ih )
{
  if (ih->iclass->is_interactive &&  /* interactive */
      iupAttribGetBoolean( data, ih, "CANFOCUS" ) &&   /* can receive focus */
      ih->handle &&                  /* mapped  */
      amy_IupGetInt( data, ih, "ACTIVE" ) &&     /* active  */
      amy_IupGetInt( data, ih, "VISIBLE" ))      /* visible */
    return 1;
  else
    return 0;
}

static int iFocusCheckActiveRadio( struct libData *data, Ihandle *ih )
{
  if (amy_IupClassMatch( data, ih, "toggle" ) && 
      amy_IupGetInt( data, ih, "RADIO" ) &&
      !amy_IupGetInt( data, ih, "VALUE" ))
    return 0;
  else
    return 1;
}

static Ihandle *iFocusFindAtBrothers( struct libData *data, Ihandle *start, int checkradio )
{
  Ihandle *c;
  Ihandle *nf;

  for (c = start; c; c = c->brother)
  {
    /* check itself */
    if (iupFocusCanAccept( data, c ) && ( ! checkradio || iFocusCheckActiveRadio( data, c )))
      return c;

    /* then check its children */
    nf = iFocusFindAtBrothers( data, c->firstchild, checkradio );
    if (nf)
      return nf;
  }

  return NULL;
}

static Ihandle *iFocusFindNext( struct libData *data, Ihandle *ih, int checkradio)
{
  Ihandle *nf, *p;

  if ( ! ih)
    return NULL;

  /* look down in the child tree */
  if (ih->firstchild)
  {
    nf = iFocusFindAtBrothers( data, ih->firstchild, checkradio );
    if (nf) return nf;
  }

  /* look in the same level */
  if (ih->brother)
  {
    nf = iFocusFindAtBrothers( data, ih->brother, checkradio );
    if (nf) return nf;
  }

  /* look up in the brothers of the parent level */
  if (ih->parent)
  {
    for (p = ih->parent; p; p = p->parent)
    {
      if (p->brother)
      {
        nf = iFocusFindAtBrothers( data, p->brother, checkradio );
        if (nf) return nf;
      }
    }
  }

  return NULL;
}

IUP_API Ihandle *amy_IupNextField( struct libData *data, Ihandle *ih )
{
  Ihandle *ih_next;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return NULL;

  ih_next = iFocusFindNext( data, ih, 1 );
  if ( ! ih_next)
  {
    /* not found after the element, then start over from the beginning,
       at the dialog. */
    ih_next = iFocusFindNext( data, amy_IupGetDialog( data, ih ), 1 );
    if (ih_next == ih)
      return NULL;
  }

  if (ih_next)
  {
    iupdrvSetFocus( data, ih_next );
    return ih_next;
  }

  return NULL;
}

void iupFocusNext( struct libData *data, Ihandle *ih )
{
  Ihandle *ih_next = iFocusFindNext( data, ih, 0 );
  if ( ! ih_next)
  {
    /* not found after the element, then start over from the beginning,
       at the dialog. */
    ih_next = iFocusFindNext( data, amy_IupGetDialog( data, ih ), 0 );
    if (ih_next == ih)
      return;
  }
  if (ih_next)
    iupdrvSetFocus( data, ih_next );
}

static int iFocusFindPrevious( struct libData *data, Ihandle *parent, Ihandle **previous, Ihandle *ih, int checkradio)
{
  Ihandle *c;

  if ( ! parent)
    return 0;

  for (c = parent->firstchild; c; c = c->brother)
  {
    if (c == ih)
    {
      /* if found child, returns the current previous.
         but if previous is NULL, then keep searching until the last element. */
      if (*previous)
        return 1;
    }
    else
    {
      /* save the possible previous */
      if (iupFocusCanAccept( data, c ) && ( ! checkradio || iFocusCheckActiveRadio( data, c )))
        *previous = c;
    }

    /* then check its children */
    if (iFocusFindPrevious( data, c, previous, ih, checkradio))
      return 1;
  }

  return 0;
}

IUP_API Ihandle *amy_IupPreviousField( struct libData *data, Ihandle *ih )
{
  Ihandle *previous = NULL;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return NULL;

  /* search from the dialog down to the element */
  iFocusFindPrevious( data, amy_IupGetDialog( data, ih ), &previous, ih, 1 );
  
  if (previous)
  {
    iupdrvSetFocus( data, previous );
    return previous;
  }

  return NULL;
}

void iupFocusPrevious( struct libData *data, Ihandle *ih )
{
  Ihandle *previous = NULL;

  /* search from the dialog down to the element */
  iFocusFindPrevious( data, amy_IupGetDialog( data, ih ), &previous, ih, 0 );
  
  if (previous)
    iupdrvSetFocus( data, previous );
}

/* local variables */
static Ihandle *iup_current_focus = NULL;
static Ihandle *iup_current_dialog_focus = NULL;

IUP_API Ihandle *amy_IupGetFocus( struct libData *data )
{
  return iup_current_focus;
}

void iupSetCurrentFocus( struct libData *data, Ihandle *ih )
{
  iup_current_focus = ih;

  if ( ih )
  {
    Ihandle *dialog = amy_IupGetDialog( data, ih );
    Ihandle *current_dialog = iup_current_dialog_focus;

    if (current_dialog != dialog)
    {
      IFni cb;

      /* change it before calling the callbacks 
         because focus can be changed again from inside the callbacks. */
      iup_current_dialog_focus = dialog;

      if (iupObjectCheck( data, current_dialog )) /* can be NULL at start or can be destroyed */
      {
        cb = (IFni) amy_IupGetCallback( data, current_dialog, "FOCUS_CB" );
        if (cb) cb( data,current_dialog, 0 );
      }

      cb = (IFni) amy_IupGetCallback( data, iup_current_dialog_focus, "FOCUS_CB" );
      if (cb) cb( data,iup_current_dialog_focus, 1 );
    }
  }
}

void iupResetCurrentFocus( struct libData *data, Ihandle *destroyed_ih)
{
  if (iup_current_focus == destroyed_ih)
    iup_current_focus = NULL;
  if (iup_current_dialog_focus == destroyed_ih)
    iup_current_dialog_focus = NULL;
}

IUP_API Ihandle *amy_IupSetFocus( struct libData *data, Ihandle *ih )
{
  Ihandle *old_focus = amy_IupGetFocus( data );

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return old_focus;

  /* Current focus is NOT set here, 
     only in the iupCallGetFocusCb */

  if (iupFocusCanAccept( data, ih ))  
    iupdrvSetFocus( data, ih );

  return old_focus;
}

IUP_SDK_API void iupCallGetFocusCb( struct libData *data, Ihandle *ih )
{
  Icallback cb;

  if (ih == amy_IupGetFocus( data ))  /* avoid duplicate messages */
    return;

  cb = (Icallback) amy_IupGetCallback( data, ih, "GETFOCUS_CB" );
  if (cb) cb( data,ih );

  if (ih->iclass->nativetype == IUP_TYPECANVAS)
  {
    IFni cb2 = (IFni) amy_IupGetCallback( data, ih, "FOCUS_CB" );
    if (cb2) cb2( data, ih, 1 );
  }

  iupSetCurrentFocus( data, ih );

  if (iupAttribGetBoolean( data, ih, "PROPAGATEFOCUS" ))
  {
    Ihandle *parent = iupChildTreeGetNativeParent( data, ih );
    while (parent)
    {
      IFni focus_cb = (IFni) amy_IupGetCallback( data, parent, "FOCUS_CB" );
      if (focus_cb)
      {
        focus_cb( data,parent, 1 );
        break;
      }

      parent = iupChildTreeGetNativeParent( data, parent );
    }
  }
}

IUP_SDK_API void iupCallKillFocusCb( struct libData *data, Ihandle *ih )
{
  Icallback cb;

  if (ih != amy_IupGetFocus( data ))  /* avoid duplicate messages */
    return;

  cb = amy_IupGetCallback( data, ih, "KILLFOCUS_CB" );
  if (cb) cb( data,ih );

  if (iupObjectCheck( data, ih ) && ih->iclass->nativetype == IUP_TYPECANVAS)
  {
    IFni cb2 = (IFni) amy_IupGetCallback( data, ih, "FOCUS_CB" );
    if (cb2) cb2( data, ih, 0 );
  }

  if (iupObjectCheck( data, ih ) && iupAttribGetBoolean( data, ih, "PROPAGATEFOCUS" ))
  {
    Ihandle *parent = iupChildTreeGetNativeParent( data, ih );
    while (parent)
    {
      IFni focus_cb = (IFni) amy_IupGetCallback( data, parent, "FOCUS_CB" );
      if (focus_cb)
      {
        focus_cb( data,parent, 0 );
        break;
      }

      parent = iupChildTreeGetNativeParent( data, parent );
    }
  }

  iupSetCurrentFocus( data, NULL );
}
