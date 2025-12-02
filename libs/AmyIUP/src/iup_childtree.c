
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
 * \brief Control tree hierarchy manager.  
 * implements also amy_IupDestroy
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdio.h> 

#include "iup.h"

#include "iup_object.h"
#include "iup_dlglist.h"
#include "iup_childtree.h"
#include "iup_class.h"
#include "iup_attrib.h" 
#include "iup_assert.h" 
#include "iup_str.h" 
#include "iup_drv.h" 

#endif

IUP_API Ihandle *amy_IupGetDialog( struct libData *data, Ihandle *ih )
{
  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return NULL;

  for (; ih->parent; ih = ih->parent)
    ; /* empty*/

  if (ih->iclass->nativetype == IUP_TYPEDIALOG)
    return ih;
  else if (ih->iclass->nativetype == IUP_TYPEMENU)
  {
    Ihandle *dlg;
    /* if ih is a menu then */
    /* searches all the dialogs that may have been associated with the menu. */
    for (dlg = iupDlgListFirst( data ); dlg; dlg = iupDlgListNext( data ))
    {
      if (amy_IupGetAttributeHandle( data, dlg, "MENU" ) == ih)
        return dlg;
    }
  }

  return NULL;
}

static void iChildTreeDetach( struct libData *data, Ihandle *parent, Ihandle *child)
{
  Ihandle *c, 
          *c_prev = NULL;

  /* Removes the child entry inside the parent's child list */
  for (c = parent->firstchild; c; c = c->brother)
  {
    if (c == child) /* Found the right child */
    {
      if (c_prev == NULL)
        parent->firstchild = child->brother;
      else
        c_prev->brother = child->brother;
        
      child->brother = NULL;
      child->parent = NULL;
      return;
    }

    c_prev = c;
  }
}

IUP_API void amy_IupDetach( struct libData *data, Ihandle *child )
{
  Ihandle *parent;
  int pos;

  iupASSERT(iupObjectCheck( data, child));
  if ( ! iupObjectCheck( data, child))
    return;

  amy_IupUnmap( data, child );

  /* Not valid if does NOT has a parent */
  if ( ! child->parent)
    return;

  parent = child->parent;

  pos = amy_IupGetChildPos( data, parent, child );

  iChildTreeDetach( data, parent, child );
  iupClassObjectChildRemoved( data, parent, child, pos );
}

static int iChildTreeFind( struct libData *data, Ihandle *parent, Ihandle *child)
{
  Ihandle *c;

  /* Finds the reference child entry inside the parent's child list */
  for (c = parent->firstchild; c; c = c->brother)
  {
    if (c == child) /* Found the right child */
      return 1;
  }

  return 0;
}

static void iChildTreeInsert( struct libData *data, Ihandle *parent, Ihandle *ref_child, Ihandle *child)
{
  Ihandle *c, 
          *c_prev = NULL;

  if (parent->firstchild == NULL)
  {
    parent->firstchild = child;
    child->parent = parent;
    return;
  }

  if ( ! ref_child)
    ref_child = parent->firstchild;

  if ((ref_child == parent->firstchild) && (ref_child->flags & IUP_INTERNAL))
  {
    /* the first child is internal, so add after it */
    child->parent = parent;
    child->brother = ref_child->brother;
    ref_child->brother = child;
    return;
  }

  /* Finds the reference child entry inside the parent's child list */
  for (c = parent->firstchild; c; c = c->brother)
  {
    if (c == ref_child) /* Found the right child */
    {
      child->parent = parent;
      child->brother = ref_child;

      if (c_prev == NULL)
        parent->firstchild = child;
      else
        c_prev->brother = child;

      return;
    }

    c_prev = c;
  }
}

static int iChildTreeCount( struct libData *data, Ihandle *ih )
{
  int num = 0;

  ih = ih->firstchild;
  while( ih )
  {
    num++;
    ih = ih->brother;
  }

  return num;
}

IUP_API Ihandle *amy_IupInsert( struct libData *data, Ihandle *parent, Ihandle *ref_child, Ihandle *child)
{
  /* ref_child can be NULL */

  iupASSERT(iupObjectCheck( data, parent ));
  if ( ! iupObjectCheck( data, parent ))
    return NULL;

  iupASSERT(iupObjectCheck( data, child));
  if ( ! iupObjectCheck( data, child))
    return NULL;

  iupASSERT(iupObjectCheck( data, child));

  if (child->parent != NULL && child->parent != parent)
  {
#ifdef IUP_ASSERT
    iupError("Child Already Inside a Parent!\n"
             "  child = type(%s) - name(%s)\n"
             "  child->parent = type(%s) - name(%s)\n"
             "  parent = type(%s) - name(%s)",
             child->iclass->name, amy_IupGetName( data, child),
             child->parent->iclass->name, amy_IupGetName( data, child->parent),
             parent->iclass->name, amy_IupGetName( data, parent)
           );
#endif
    return NULL;
  }

  if (parent->iclass->childtype == IUP_CHILDNONE)
    return NULL;
  if (parent->iclass->childtype > IUP_CHILDMANY && 
      iChildTreeCount( data, parent ) == parent->iclass->childtype-IUP_CHILDMANY)
    return NULL;


  /* if already at the parent box, allow to move even if mapped */
  if (parent->iclass->nativetype == IUP_TYPEVOID && iChildTreeFind( data, parent, child ))
  {
    iChildTreeDetach( data, parent, child );
    iChildTreeInsert( data, parent, ref_child, child );
  }
  else
  {
    /* Not valid if it is mapped */
    if (child->handle)
      return NULL;

    iChildTreeInsert( data, parent, ref_child, child );
    iupClassObjectChildAdded( data, parent, child );
  }

  return parent;
}

IUP_SDK_API void iupChildTreeAppend( struct libData *data, Ihandle *parent, Ihandle *child)
{
  child->parent = parent;

  if (parent->firstchild == NULL)
    parent->firstchild = child;
  else
  {
    Ihandle *c = parent->firstchild;
    while (c->brother)
      c = c->brother;
    c->brother = child;
  }
}

IUP_API Ihandle *amy_IupAppend( struct libData *data, Ihandle *parent, Ihandle *child )
{
  iupASSERT(iupObjectCheck( data, parent ));
  if ( ! iupObjectCheck( data, parent ))
    return NULL;

  iupASSERT(iupObjectCheck( data, child));
  if ( ! iupObjectCheck( data, child))
    return NULL;

  if (child->parent != NULL && child->parent != parent)
  {
#ifdef IUP_ASSERT
    iupError("Child Already Inside a Parent!\n"
             "  child = type(%s) - name(%s)\n"
             "  child->parent = type(%s) - name(%s)\n"
             "  parent = type(%s) - name(%s)",
             child->iclass->name, amy_IupGetName( data, child),
             child->parent->iclass->name, amy_IupGetName( data, child->parent),
             parent->iclass->name, amy_IupGetName( data, parent)
           );
#endif
    return NULL;
  }

  if (parent->iclass->childtype == IUP_CHILDNONE)
    return NULL;
  if (parent->iclass->childtype > IUP_CHILDMANY && 
      iChildTreeCount( data, parent ) == parent->iclass->childtype-IUP_CHILDMANY)
    return NULL;


  /* if already at the parent box, allow to move even if mapped */
  if (parent->iclass->nativetype == IUP_TYPEVOID && iChildTreeFind( data, parent, child ))
  {
    iChildTreeDetach( data, parent, child );
    iupChildTreeAppend( data, parent, child );
  }
  else
  {
    /* Not valid if it is mapped */
    if (child->handle)
      return NULL;

    iupChildTreeAppend( data, parent, child );
    iupClassObjectChildAdded( data, parent, child );
  }

  return parent;
}

static void iChildTreeReparent( struct libData *data, Ihandle *child, Ihandle *new_parent)
{
  Ihandle *c;

  /* Forward the reparent to all native children */

  for (c = child->firstchild; c; c = c->brother)
  {
    if (c->iclass->nativetype != IUP_TYPEVOID)
      iupdrvReparent( data, c );
    else
      iChildTreeReparent( data, c, new_parent );
  }
}

IUP_API int amy_IupReparent( struct libData *data, Ihandle *child, Ihandle *parent, Ihandle *ref_child )
{
  Ihandle *old_parent;
  int pos;

  iupASSERT(iupObjectCheck( data, parent ));
  if ( ! iupObjectCheck( data, parent ))
    return IUP_ERROR;

  iupASSERT(iupObjectCheck( data, child));
  if ( ! iupObjectCheck( data, child))
    return IUP_ERROR;

  if (ref_child)
  {
    /* can be NULL, but if not NULL must be a valid object */
    iupASSERT(iupObjectCheck( data, ref_child ));
    if ( ! iupObjectCheck( data, ref_child ))
      return IUP_ERROR;
  }

  /* can not be at the same place */
  if (parent == child->parent && (ref_child == child || (ref_child == NULL && child->brother == NULL)))
    return IUP_ERROR;

  /* child can not be grand-parent of parent */
  if (iupChildTreeIsParent( data, child, parent ))
    return IUP_ERROR;

  if (parent->iclass->childtype == IUP_CHILDNONE)
    return IUP_ERROR;
  if (parent->iclass->childtype > IUP_CHILDMANY && 
      iChildTreeCount( data, parent ) == parent->iclass->childtype-IUP_CHILDMANY)
    return IUP_ERROR;


  /* both must be already mapped or both unmapped */
  if (( ! parent->handle &&  child->handle) ||
      ( parent->handle && !child->handle))
    return IUP_ERROR;


  /* detach from old parent */
  old_parent = child->parent;

  pos = amy_IupGetChildPos( data, old_parent, child );

  iChildTreeDetach( data, old_parent, child );
  iupClassObjectChildRemoved( data, old_parent, child, pos );

 
  /* attach to new parent */
  if (ref_child)
    iChildTreeInsert( data, parent, ref_child, child );
  else
    iupChildTreeAppend( data, parent, child );
  iupClassObjectChildAdded( data, parent, child );


  /* no need to remap, just notify the native system */
  if (child->handle && parent->handle)
  {
    if (child->iclass->nativetype != IUP_TYPEVOID)
      iupdrvReparent( data, child );
    else
      iChildTreeReparent( data, child, parent );
  }

  return IUP_NOERROR;
}

IUP_API Ihandle *amy_IupGetChild( struct libData *data, Ihandle *ih, int pos )
{
  int p;
  Ihandle *child;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return NULL;

  for (p = 0, child = ih->firstchild; child; child = child->brother, p++)
  {
    if (p == pos)
      return child;
  }

  return NULL;
}

IUP_API int amy_IupGetChildPos( struct libData *data, Ihandle *ih, Ihandle *child )
{
  int pos;
  Ihandle *c;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return -1;

  for (pos = 0, c = ih->firstchild; c; c = c->brother, pos++)
  {
    if (c == child)
      return pos;
  }
  return -1;
}

IUP_SDK_API Ihandle *iupChildTreeGetPrevBrother( struct libData *data, Ihandle *ih )
{
  Ihandle *c, *prev = NULL;

  for (c = ih->parent->firstchild; c; c = c->brother)
  {
    if (c == ih)
      return prev;

    prev = c;
  }

  return NULL;
}

IUP_API int amy_IupGetChildCount( struct libData *data, Ihandle *ih )
{
  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return -1;

  return iChildTreeCount( data, ih );
}

IUP_API Ihandle *amy_IupGetNextChild( struct libData *data, Ihandle *ih, Ihandle *child)
{
  if ( ! child)
  {
    iupASSERT(iupObjectCheck( data, ih ));
    if ( ! iupObjectCheck( data, ih ))
      return NULL;

    return ih->firstchild;
  }
  else
  {
    iupASSERT(iupObjectCheck( data, child));
    if ( ! iupObjectCheck( data, child))
      return NULL;

    return child->brother;
  }
}

IUP_API Ihandle *amy_IupGetBrother( struct libData *data, Ihandle *ih )
{
  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return NULL;

  return ih->brother;
}

IUP_API Ihandle *amy_IupGetParent( struct libData *data, Ihandle *ih )
{
  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return NULL;
    
  return ih->parent;
}

IUP_SDK_API int iupChildTreeIsParent( struct libData *data, Ihandle *ih, Ihandle *parent )
{
  while (parent)
  {
    if (parent == ih)
      return 1;

    parent = parent->parent;
  }

  return 0;
}

IUP_SDK_API Ihandle *iupChildTreeGetNativeParent( struct libData *data, Ihandle *ih )
{
  Ihandle *parent = ih->parent;
  while (parent && parent->iclass->nativetype == IUP_TYPEVOID)
    parent = parent->parent;
  return parent;
}

IUP_SDK_API InativeHandle* iupChildTreeGetNativeParentHandle( struct libData *data, Ihandle *ih )
{
  Ihandle *native_parent = iupChildTreeGetNativeParent( data, ih );
  return (InativeHandle*) iupClassObjectGetInnerNativeContainerHandle( data, native_parent, ih );
}
