
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
 * \brief Radio Control.
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdio.h>
#include <stdlib.h>

#include "iup.h"
#include "iupcbs.h"

#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_drv.h"
#include "iup_drvfont.h"
#include "iup_stdcontrols.h"
#include "iup_layout.h"

#endif

IUP_SDK_API Ihandle *iupRadioFindToggleParent( struct libData *data, Ihandle *ih_toggle )
{
  Ihandle *p;

  if (iupAttribGetBoolean( data, ih_toggle, "IGNORERADIO" ))
    return NULL;

  for (p = ih_toggle; p->parent; p = p->parent)
  {
    if (p->iclass->nativetype == IUP_TYPEVOID &&
        amy_IupClassMatch( data, p, "radio" ))
      return p;
  }

  return NULL;
}

static int iRadioFindToggleChild( struct libData *data, Ihandle *ih, Ihandle *ih_toggle )
{
  Ihandle *child;

  if (ih == ih_toggle) /* found child that match the toggle */
    return 1;

  for (child = ih->firstchild; child; child = child->brother)
  {
    if (iRadioFindToggleChild( data, child, ih_toggle ))
      return 1;
  }

  return 0;
}

static int iRadioChildIsToggle( struct libData *data, Ihandle *child )
{
  if ( amy_IupClassMatch( data, child, "toggle" ) || 
      amy_IupClassMatch( data, child, "gltoggle" ) ||
      amy_IupClassMatch( data, child, "flattoggle" ) ||
      ( amy_IupClassMatch( data, child, "flatbutton" ) && iupAttribGetBoolean( data, child, "TOGGLE" )))
    return 1;
  else
    return 0;
}

static Ihandle *iRadioGetToggleChildOn( struct libData *data, Ihandle *ih )
{
  Ihandle *child;

  /* found child that is a toggle and it is ON */
  if (iRadioChildIsToggle( data, ih ) && amy_IupGetInt( data, ih, "VALUE" ))
    return ih;

  for (child = ih->firstchild; child; child = child->brother)
  {
    Ihandle *ih_toggle = iRadioGetToggleChildOn( data, child );
    if (ih_toggle)
      return ih_toggle;
  }

  return NULL;
}

/******************************************************************************/


static int iRadioSetValueHandleAttrib( struct libData *data, Ihandle *ih, const char *value )
{
  Ihandle *ih_toggle = (Ihandle*)value;
  if ( ! iupObjectCheck( data, ih_toggle))
    return 0;

  if ( ! iRadioChildIsToggle( data, ih_toggle ))
    return 0;

  if (iRadioFindToggleChild( data, ih->firstchild, ih_toggle))
    amy_IupSetAttribute( data, ih_toggle, "VALUE", "ON" );
 
  return 0;
}

static char *iRadioGetValueHandleAttrib( struct libData *data, Ihandle *ih )
{
  return (char*)iRadioGetToggleChildOn( data, ih->firstchild );
}

static int iRadioSetValueAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  Ihandle *ih_toggle;

  if ( ! value)
    return 0;

  ih_toggle = amy_IupGetHandle( data, value );
  if ( ! ih_toggle)
    return 0;

  iRadioSetValueHandleAttrib( data, ih, (char*)ih_toggle );
  return 0;
}

static char *iRadioGetValueAttrib( struct libData *data, Ihandle *ih )
{
  Ihandle *ih_toggle = (Ihandle*)iRadioGetValueHandleAttrib( data, ih );
  return amy_IupGetName( data, ih_toggle );  /* Name is guarantied at Toggle MapMethod */
}

/******************************************************************************/


static int iRadioCreateMethod( struct libData *data, Ihandle *ih, void** params )
{
  if (params)
  {
    Ihandle** iparams = (Ihandle**)params;
    if (*iparams)
      amy_IupAppend( data, ih, *iparams );
  }
  return IUP_NOERROR;
}

static void iRadioComputeNaturalSizeMethod( struct libData *data, Ihandle *ih, int *w, int *h, int *children_expand)
{
  Ihandle *child = ih->firstchild;
  if (child)
  {
    /* update child natural size first */
    iupBaseComputeNaturalSize( data, child );

    *children_expand = child->expand;
    *w = child->naturalwidth;
    *h = child->naturalheight;
  }
}

static void iRadioSetChildrenCurrentSizeMethod( struct libData *data, Ihandle *ih, int shrink)
{
  if (ih->firstchild)
    iupBaseSetCurrentSize( data, ih->firstchild, ih->currentwidth, ih->currentheight, shrink );
}

static void iRadioSetChildrenPositionMethod( struct libData *data, Ihandle *ih, int x, int y)
{
  if (ih->firstchild)
    iupBaseSetPosition( data, ih->firstchild, x, y );
}


/******************************************************************************/

IUP_API Ihandle *amy_IupRadio( struct libData *data, Ihandle *child )
{
  void *children[2];
  children[0] = (void*)child;
  children[1] = NULL;
  return amy_IupCreatev( data, "radio", children );
}

Iclass *iupRadioNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, NULL );

  ic->name = "radio";
  ic->format = "h"; /* one Ihandle **/
  ic->nativetype = IUP_TYPEVOID;
  ic->childtype = IUP_CHILDMANY+1;  /* 1 child */
  ic->is_interactive = 0;

  /* Class functions */
  ic->New = iupRadioNewClass;
  ic->Create = iRadioCreateMethod;
  ic->Map = iupBaseTypeVoidMapMethod;
  ic->ComputeNaturalSize = iRadioComputeNaturalSizeMethod;
  ic->SetChildrenCurrentSize = iRadioSetChildrenCurrentSizeMethod;
  ic->SetChildrenPosition = iRadioSetChildrenPositionMethod;

  /* Base Callbacks */
  iupBaseRegisterBaseCallbacks( data, ic );

  /* Common */
  iupBaseRegisterCommonAttrib( data, ic );

  /* Base Container */
  iupClassRegisterAttribute( data, ic, "EXPAND", iupBaseContainerGetExpandAttrib, NULL, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CLIENTSIZE", iupBaseGetClientSizeAttrib, NULL, NULL, NULL, IUPAF_READONLY|IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CLIENTOFFSET", iupBaseGetClientOffsetAttrib, NULL, NULL, NULL, IUPAF_READONLY|IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );

  /* Radio only */
  iupClassRegisterAttribute( data, ic, "VALUE", iRadioGetValueAttrib, iRadioSetValueAttrib, NULL, NULL, IUPAF_IHANDLENAME|IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "VALUE_HANDLE", iRadioGetValueHandleAttrib, iRadioSetValueHandleAttrib, NULL, NULL, IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT | IUPAF_IHANDLE | IUPAF_NO_STRING );

  return ic;
}
