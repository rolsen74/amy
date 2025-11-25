
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
 * \brief IUP Ihandle Class C Interface
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>

#include "iup.h"

#include "iup_object.h"
#include "iup_drv.h"
#include "iup_drvfont.h"
#include "iup_str.h"
#include "iup_attrib.h"
#include "iup_assert.h"

#endif

/*****************************************************************
                        Method Stubs
*****************************************************************/

static int iClassCreate( struct libData *data, Iclass *ic, Ihandle *ih, void** params)
{
  int ret = IUP_NOERROR;
  if (ic->parent)
    ret = iClassCreate( data, ic->parent, ih, params );

  if (ret == IUP_NOERROR && ic->Create)
    ret = ic->Create( data, ih, params );

  return ret;
}

static int iClassMap( struct libData *data, Iclass *ic, Ihandle *ih )
{
  int ret = IUP_NOERROR;
  if (ic->parent)
    ret = iClassMap( data, ic->parent, ih );

  if (ret == IUP_NOERROR && ic->Map)
    ret = ic->Map( data, ih );

  return ret;
}

static void iClassUnMap( struct libData *data, Iclass *ic, Ihandle *ih )
{
  /* must be before the parent class */
  if (ic->UnMap)
    ic->UnMap( data, ih );

  if (ic->parent)
    iClassUnMap( data, ic->parent, ih );
}

static void iClassDestroy( struct libData *data, Iclass *ic, Ihandle *ih )
{
  /* must destroy child class before the parent class */
  if (ic->Destroy)
    ic->Destroy( data, ih );

  if (ic->parent)
    iClassDestroy( data, ic->parent, ih );
}

static void iClassComputeNaturalSize( struct libData *data, Iclass *ic, Ihandle *ih, int *w, int *h, int *children_expand)
{
  if (ic->parent)
    iClassComputeNaturalSize( data, ic->parent, ih, w, h, children_expand );

  if (ic->ComputeNaturalSize)
    ic->ComputeNaturalSize( data, ih, w, h, children_expand );
}

static void iClassSetChildrenCurrentSize( struct libData *data, Iclass *ic, Ihandle *ih, int shrink)
{
  if (ic->parent)
    iClassSetChildrenCurrentSize( data, ic->parent, ih, shrink );

  if (ic->SetChildrenCurrentSize)
    ic->SetChildrenCurrentSize( data, ih, shrink );
}

static void iClassSetChildrenPosition( struct libData *data, Iclass *ic, Ihandle *ih, int x, int y)
{
  if (ic->parent)
    iClassSetChildrenPosition( data, ic->parent, ih, x, y );

  if (ic->SetChildrenPosition)
    ic->SetChildrenPosition( data, ih, x, y );
}

static void *iClassGetInnerNativeContainerHandle( struct libData *data, Iclass *ic, Ihandle *ih, Ihandle *child)
{
  void *container_handle = ih->handle;

  if (ic->parent)
    container_handle = iClassGetInnerNativeContainerHandle( data, ic->parent, ih, child );

  /* if the class implements the function it will ignore the result of the parent class */

  if (ic->GetInnerNativeContainerHandle)
    container_handle = ic->GetInnerNativeContainerHandle( data, ih, child );

  return container_handle;
}

static void iClassObjectChildAdded( struct libData *data, Iclass *ic, Ihandle *ih, Ihandle *child)
{
  if (ic->parent)
    iClassObjectChildAdded( data, ic->parent, ih, child );

  if (ic->ChildAdded)
    ic->ChildAdded( data, ih, child );
}

static void iClassObjectChildRemoved( struct libData *data, Iclass *ic, Ihandle *ih, Ihandle *child, int pos)
{
  if (ic->parent)
    iClassObjectChildRemoved( data, ic->parent, ih, child, pos );

  if (ic->ChildRemoved)
    ic->ChildRemoved( data, ih, child, pos );
}

static void iClassLayoutUpdate( struct libData *data, Iclass *ic, Ihandle *ih )
{
  if (ic->parent)
    iClassLayoutUpdate( data, ic->parent, ih );

  if (ic->LayoutUpdate)
    ic->LayoutUpdate( data, ih );
}

static int iClassDlgPopup( struct libData *data, Iclass *ic, Ihandle *ih, int x, int y)
{
  /* must be before the parent class */
  if (ic->DlgPopup)
    return ic->DlgPopup( data, ih, x, y );  /* ignore parent if implemented */

  if (ic->parent)
    return iClassDlgPopup( data, ic->parent, ih, x, y );

  return IUP_INVALID;  /* means it is not implemented */
}

static int iClassHasDlgPopup( struct libData *data, Iclass *ic)
{
  /* must be before the parent class */
  if (ic->DlgPopup)
    return 1;

  if (ic->parent)
    return iClassHasDlgPopup( data, ic->parent );

  return 0;
}


/*****************************************************************
                     Public Interface
*****************************************************************/


IUP_SDK_API int iupClassObjectCreate( struct libData *data, Ihandle *ih, void** params)
{
  return iClassCreate( data, ih->iclass, ih, params );
}

IUP_SDK_API int iupClassObjectMap( struct libData *data, Ihandle *ih )
{
  return iClassMap( data, ih->iclass, ih );
}

IUP_SDK_API void iupClassObjectUnMap( struct libData *data, Ihandle *ih )
{
  iClassUnMap( data, ih->iclass, ih );
}

IUP_SDK_API void iupClassObjectDestroy( struct libData *data, Ihandle *ih )
{
  iClassDestroy( data, ih->iclass, ih );
}

IUP_SDK_API void iupClassObjectComputeNaturalSize( struct libData *data, Ihandle *ih, int *w, int *h, int *children_expand)
{
  iClassComputeNaturalSize( data, ih->iclass, ih, w, h, children_expand );
}

IUP_SDK_API void iupClassObjectSetChildrenCurrentSize( struct libData *data, Ihandle *ih, int shrink)
{
  iClassSetChildrenCurrentSize( data, ih->iclass, ih, shrink );
}

IUP_SDK_API void iupClassObjectSetChildrenPosition( struct libData *data, Ihandle *ih, int x, int y)
{
  iClassSetChildrenPosition( data, ih->iclass, ih, x, y );
}

IUP_SDK_API void *iupClassObjectGetInnerNativeContainerHandle( struct libData *data, Ihandle *ih, Ihandle *child)
{
  return iClassGetInnerNativeContainerHandle( data, ih->iclass, ih, child );
}

IUP_SDK_API void iupClassObjectChildAdded( struct libData *data, Ihandle *ih, Ihandle *child)
{
  iClassObjectChildAdded( data, ih->iclass, ih, child );
}

IUP_SDK_API void iupClassObjectChildRemoved( struct libData *data, Ihandle *ih, Ihandle *child, int pos)
{
  iClassObjectChildRemoved( data, ih->iclass, ih, child, pos );
}

IUP_SDK_API void iupClassObjectLayoutUpdate( struct libData *data, Ihandle *ih )
{
  iClassLayoutUpdate( data, ih->iclass, ih );
}

IUP_SDK_API int iupClassObjectDlgPopup( struct libData *data, Ihandle *ih, int x, int y)
{
  return iClassDlgPopup( data, ih->iclass, ih, x, y );
}

IUP_SDK_API int iupClassObjectHasDlgPopup( struct libData *data, Ihandle *ih )
{
  return iClassHasDlgPopup( data, ih->iclass );
}

/*****************************************************************
                        Class Definition
*****************************************************************/


static void iClassReleaseAttribFuncTable( struct libData *data, Iclass *ic )
{
  char *name = iupTableFirst( data, ic->attrib_func );
  while (name)
  {
    void *afunc = iupTableGetCurr( data, ic->attrib_func );
    free(afunc );

    name = iupTableNext( data, ic->attrib_func );
  }

  iupTableDestroy( data, ic->attrib_func );
}

IUP_SDK_API Iclass *iupClassNew( struct libData *data, Iclass *parent )
{
  Iclass *ic = malloc(sizeof(Iclass));
  memset( ic, 0, sizeof(Iclass));

  if (parent)
  {
    parent = parent->New( data );
    ic->attrib_func = parent->attrib_func;
    ic->parent = parent;
  }
  else
    ic->attrib_func = iupTableCreate( data, IUPTABLE_STRINGINDEXED );

  return ic;
}

IUP_SDK_API void iupClassRelease( struct libData *data, Iclass *ic)
{
  Iclass *parent;

  /* must call Release only for the actual class */
  if (ic->Release)
    ic->Release( data, ic );

  /* must free the pointer for all classes, 
     since a new instance is created when we inherit */
  parent = ic->parent;
  while (parent)
  {
    Iclass *ic_tmp = parent;
    parent = parent->parent;
    free(ic_tmp );
  }

  /* attributes functions table is released only once */
  iClassReleaseAttribFuncTable( data, ic );

  free(ic );
}

IUP_SDK_API int iupClassMatch( struct libData *data, Iclass *ic, const char *classname)
{
  /* check for all classes in the hierarchy */
  while (ic)
  {
    if (iupStrEqualNoCase(ic->name, classname))
      return 1;
    ic = ic->parent;
  }
  return 0;
}

/*****************************************************************
                        Main API
*****************************************************************/


IUP_API char *amy_IupGetClassName( struct libData *data, Ihandle *ih )
{
  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return NULL;

  return (char*)ih->iclass->name;
}

IUP_API char *amy_IupGetClassType( struct libData *data, Ihandle *ih )
{
  static char *type2str[] = { "void", "control", "canvas", "dialog", "image", "menu", "other" };

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return NULL;

  return type2str[ih->iclass->nativetype];
}

IUP_API int amy_IupClassMatch( struct libData *data, Ihandle *ih, const char *classname )
{
  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return 0;

  return iupClassMatch( data, ih->iclass, classname );
}
