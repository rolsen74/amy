
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
 * \brief show/popup/hide/map
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdlib.h>
#include <stdarg.h>

#include "iup.h"

#include "iup_object.h"
#include "iup_layout.h"
#include "iup_attrib.h"
#include "iup_class.h"
#include "iup_dialog.h"
#include "iup_menu.h"
#include "iup_assert.h"
#include "iup_str.h"
#include "iup_drv.h"
#include "iup_drvfont.h"

#endif

IUP_API void amy_IupUnmap( struct libData *data, Ihandle *ih )
{
  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return;

  /* Invalid if it is NOT mapped. */
  if ( ! ih->handle)
    return;

  /* unmap children */
  {
    Ihandle *child = ih->firstchild;
    while (child)
    {
      amy_IupUnmap( data, child );
      child = child->brother;
    }
  }

  /* only call UNMAP_CB for controls that have a native representation */
  if (ih->iclass->nativetype != IUP_TYPEVOID)
  {
    Icallback unmap_cb = amy_IupGetCallback( data, ih, "UNMAP_CB" );
    if (unmap_cb) unmap_cb( data,ih );
  }

  /* unmap from the native system */
  iupClassObjectUnMap( data, ih );
  ih->handle = NULL;
}

IUP_API int amy_IupMap( struct libData *data, Ihandle *ih )
{
  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return IUP_INVALID;

  /* already mapped, only update the dialog layout */
  if (ih->handle)
  {
    /* if the dialog is visible, then it will be reflected in the user interface */

    /* the result is equivalent of calling amy_IupRefresh( data, ih ) when it is a dialog */
    if (ih->iclass->nativetype == IUP_TYPEDIALOG)
    {
      /* calculate position and size for all children */
      iupLayoutCompute( data, ih );
      /* moves and resizes the elements to reflect the layout computation */
      iupLayoutUpdate( data, ih );
    }

    /* does nothing if not a dialog and already mapped */
    return IUP_NOERROR;
  }

  /* parent must be mapped to map child */
  if (ih->parent && !(ih->parent->handle))
    return IUP_ERROR;
    
  /* map to the native system */
  if (iupClassObjectMap( data, ih ) == IUP_ERROR)
  {
    iupERROR("Error during amy_IupMap." );
    return IUP_ERROR;
  }

  /* update FONT, must be before several other attributes, so we do it here */
  if (ih->iclass->nativetype != IUP_TYPEVOID &&
      ih->iclass->nativetype != IUP_TYPEIMAGE &&
      ih->iclass->nativetype != IUP_TYPEMENU)
    iupUpdateFontAttrib( data, ih );

  /* ensure attributes default values, at this time only the ones that need to be set after map */
  iupClassObjectEnsureDefaultAttributes( data, ih );

  /* updates the defined attributes from the hash table (this) to the native system (this). */
  iupAttribUpdate( data, ih ); 

  /* updates inheritable attributes defined in the parent tree */
  iupAttribUpdateFromParent( data, ih );

  /* map children independent from childtype */
  if (ih->firstchild)
  {
    Ihandle *child = ih->firstchild;
    while (child)
    {
      if (amy_IupMap( data, child ) == IUP_ERROR)
        return IUP_ERROR;

      child = child->brother;
    }

    /* updates the defined attributes from the hash table (this) to the native system (children). */
    iupAttribUpdateChildren( data, ih );
  }

  /* the result is equivalent of calling amy_IupRefresh( data, ih ) when it is a dialog */
  if (ih->iclass->nativetype == IUP_TYPEDIALOG)
  {
    /* calculate position and size for all children */
    iupLayoutCompute( data, ih );
    /* moves and resizes the elements to reflect the layout computation */
    iupLayoutUpdate( data, ih );
  }

  /* only call MAP_CB for controls that have a native representation */
  if (ih->iclass->nativetype != IUP_TYPEVOID)
  {
    Icallback map_cb = amy_IupGetCallback( data, ih, "MAP_CB" );
    if (map_cb) map_cb( data,ih );
  }

  return IUP_NOERROR;
}

IUP_API int amy_IupPopup( struct libData *data, Ihandle *ih, int x, int y )
{
  int ret;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return IUP_INVALID;

  if (ih->iclass->nativetype != IUP_TYPEDIALOG && 
      ih->iclass->nativetype != IUP_TYPEMENU)
  {
    iupERROR("Must be a menu or dialog in amy_IupPopup." );
    return IUP_INVALID;
  }

  ret = amy_IupMap( data, ih );
  if (ret == IUP_ERROR) 
    return ret;

  if (ih->iclass->nativetype == IUP_TYPEDIALOG)
    ret = iupDialogPopup( data, ih, x, y );
  else
    ret = iupMenuPopup( data, ih, x, y );

  if (ret != IUP_NOERROR) 
  {
    iupERROR("Error during amy_IupPopup." );
    return ret;
  }

  return IUP_NOERROR;
}

IUP_API int amy_IupShowXY( struct libData *data, Ihandle *ih, int x, int y )
{
  int ret;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return IUP_INVALID;

  if (ih->iclass->nativetype != IUP_TYPEDIALOG)
  {
    iupERROR("Must be a dialog in amy_IupShowXY." );
    return IUP_INVALID;
  }

  ret = amy_IupMap( data, ih );
  if (ret == IUP_ERROR) 
    return ret;

  ret = iupDialogShowXY( data, ih, x, y );
  if (ret != IUP_NOERROR) 
  {
    iupERROR("Error during amy_IupShowXY." );
    return ret;
  }

  return IUP_NOERROR;
}

IUP_API int amy_IupShow( struct libData *data, Ihandle *ih )
{
  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return IUP_INVALID;

  if (ih->iclass->nativetype != IUP_TYPEDIALOG)
    amy_IupSetAttribute( data, ih, "VISIBLE", "YES" );
  else   
  {
    int ret = amy_IupMap( data, ih );
    if (ret == IUP_ERROR) 
      return ret;
      
    ret = iupDialogShowXY( data, ih, IUP_CURRENT, IUP_CURRENT );
    if (ret != IUP_NOERROR) 
    {
      iupERROR("Error during amy_IupShow." );
      return ret;
    }
  }

  return IUP_NOERROR;
}

IUP_API int amy_IupHide( struct libData *data, Ihandle *ih )
{
  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return IUP_INVALID; 

  if (ih->iclass->nativetype != IUP_TYPEDIALOG)
    amy_IupSetAttribute( data, ih, "VISIBLE", "NO" );
  else if (ih->handle)
    iupDialogHide( data, ih );

  return IUP_NOERROR;
}
