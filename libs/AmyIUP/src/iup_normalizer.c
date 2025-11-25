
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
 * \brief Normalizer Element.
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdio.h>
#include <stdlib.h>

#include "iup.h"

#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_array.h"
#include "iup_stdcontrols.h"
#include "iup_normalizer.h"
#include "iup_varg.h"

#endif

enum {NORMALIZE_NONE, NORMALIZE_WIDTH, NORMALIZE_HEIGHT};

struct _IcontrolData 
{
  Iarray *ih_array;
  int ret_control;  /* for first/next attributes */
};

int iupNormalizeGetNormalizeSize( struct libData *data, const char *value )
{
  if ( ! value)
    return NORMALIZE_NONE;
  if (iupStrEqualNoCase(value, "HORIZONTAL" ))
    return NORMALIZE_WIDTH;
  if (iupStrEqualNoCase(value, "VERTICAL" ))
    return NORMALIZE_HEIGHT;
  if (iupStrEqualNoCase(value, "BOTH" ))
    return NORMALIZE_WIDTH|NORMALIZE_HEIGHT;
  return NORMALIZE_NONE;
}

char *iupNormalizeGetNormalizeSizeStr( struct libData *data, int normalize )
{
  char *int2str[] = {"NONE", "HORIZONTAL", "VERTICAL", "BOTH"};
  return int2str[normalize];
}

void iupNormalizeSizeBoxChild( struct libData *data, Ihandle *ih, int normalize, int children_natural_maxwidth, int children_natural_maxheight)
{
  /* It is called from Vbox and Hbox ComputeNaturalSizeMethod after the natural size is calculated */
  /* reset the natural width and/or height */
  Ihandle *child;
  for (child = ih->firstchild; child; child = child->brother)
  {
    if ( ! (child->flags & IUP_FLOATING) && 
        (child->iclass->nativetype != IUP_TYPEVOID || 
         !amy_IupClassMatch( data, child, "fill" )))
    {
      if (normalize & NORMALIZE_WIDTH) 
        child->naturalwidth = children_natural_maxwidth;
      if (normalize & NORMALIZE_HEIGHT)
        child->naturalheight = children_natural_maxheight;
    }
  }
}

static int iNormalizerSetNormalizeAttrib( struct libData *data, Ihandle *ih, const char *value )
{
  int i, count;
  Ihandle** ih_list;
  Ihandle *ih_control;
  int natural_maxwidth = 0, natural_maxheight = 0;
  int normalize = iupNormalizeGetNormalizeSize( data, value );
  if ( ! normalize)
    return 1;

  count = iupArrayCount( data, ih->data->ih_array );
  ih_list = (Ihandle**) iupArrayGetData( data, ih->data->ih_array );

  for (i = 0; i < count; i++)
  {
    ih_control = ih_list[i];
    iupBaseComputeNaturalSize( data, ih_control );
    natural_maxwidth = iupMAX(natural_maxwidth, ih_control->naturalwidth );
    natural_maxheight = iupMAX(natural_maxheight, ih_control->naturalheight );
  }

  for (i = 0; i < count; i++)
  {
    ih_control = ih_list[i];
    if ( ! (ih_control->flags & IUP_FLOATING) && 
        (ih_control->iclass->nativetype != IUP_TYPEVOID || 
         !amy_IupClassMatch( data, ih_control, "fill" )))
    {
      if (normalize & NORMALIZE_WIDTH)
        ih_control->userwidth = natural_maxwidth;
      if (normalize & NORMALIZE_HEIGHT)
        ih_control->userheight = natural_maxheight;
    }
  }
  return 1;
}

static int iNormalizerSetAddControlHandleAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  Ihandle *ih_control = (Ihandle*)value;
  if (iupObjectCheck( data, ih_control))
  {
    Ihandle** ih_list = (Ihandle**) iupArrayInc( data, ih->data->ih_array );
    int count = iupArrayCount( data, ih->data->ih_array );
    ih_list[count - 1] = ih_control;
  }
  return 0;
}

static int iNormalizerSetAddControlAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  return iNormalizerSetAddControlHandleAttrib( data, ih, (char*) amy_IupGetHandle( data, value));
}

static int iNormalizerSetDelControlHandleAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  Ihandle *ih_control = (Ihandle*)value;
  if (iupObjectCheck( data, ih_control))
  {
    int i, count = iupArrayCount( data, ih->data->ih_array );
    Ihandle** ih_list = (Ihandle**) iupArrayGetData( data, ih->data->ih_array );

    for (i = 0; i < count; i++)
    {
      if (ih_list[i] == ih_control)
      {
        iupArrayRemove( data, ih->data->ih_array, i, 1 );
        return 0;
      }
    }
  }
  return 0;
}

static int iNormalizerSetDelControlAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  return iNormalizerSetDelControlHandleAttrib( data, ih, (char*) amy_IupGetHandle( data, value));
}

static char *iNormalizerGetFirstControlHandleAttrib( struct libData *data, Ihandle *ih)
{
  int count = iupArrayCount( data, ih->data->ih_array );
  Ihandle** ih_list = (Ihandle**) iupArrayGetData( data, ih->data->ih_array );

  if (count == 0)
    return NULL;

  ih->data->ret_control = 0;
  return (char*)ih_list[ih->data->ret_control];
}

static char *iNormalizerGetNextControlHandleAttrib( struct libData *data, Ihandle *ih)
{
  int count = iupArrayCount( data, ih->data->ih_array );
  Ihandle** ih_list = (Ihandle**) iupArrayGetData( data, ih->data->ih_array );

  if (count == 0 || ih->data->ret_control >= count - 1)
    return NULL;

  ih->data->ret_control++;
  return (char*)ih_list[ih->data->ret_control];
}

/*******************************************************************************/


static void iNormalizerComputeNaturalSizeMethod( struct libData *data, Ihandle *ih, int *w, int *h, int *children_expand)
{
  (void)w;
  (void)h;
  (void)children_expand;
  iNormalizerSetNormalizeAttrib( data, ih, iupAttribGetStr( data, ih, "NORMALIZE" ));
}

static int iNormalizerCreateMethod( struct libData *data, Ihandle *ih, void** params)
{
  ih->data = iupALLOCCTRLDATA();
  ih->data->ih_array = iupArrayCreate( data, 10, sizeof(Ihandle*));

  if (params)
  {
    Ihandle** iparams = (Ihandle**)params;
    Ihandle** ih_list;
    int i = 0;
    while (*iparams) 
    {
      ih_list = (Ihandle**) iupArrayInc( data, ih->data->ih_array );
      ih_list[i] = *iparams;
      i++;
      iparams++;
    }
  }

  return IUP_NOERROR;
}

static void iNormalizerDestroy( struct libData *data, Ihandle *ih )
{
  iupArrayDestroy( data, ih->data->ih_array );
}

Iclass *iupNormalizerNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, NULL );

  ic->name = "normalizer";
  ic->format = "g"; /* array of Ihandle */
  ic->nativetype = IUP_TYPEVOID;
  ic->childtype = IUP_CHILDNONE;
  ic->is_interactive = 0;

  /* Class functions */
  ic->New = iupNormalizerNewClass;
  ic->Create = iNormalizerCreateMethod;
  ic->Map = iupBaseTypeVoidMapMethod;
  ic->ComputeNaturalSize = iNormalizerComputeNaturalSizeMethod;
  ic->Destroy = iNormalizerDestroy;

  /* Base Callbacks */
  iupBaseRegisterBaseCallbacks( data, ic );

  iupClassRegisterAttribute( data, ic, "NORMALIZE", NULL, iNormalizerSetNormalizeAttrib, IUPAF_SAMEASSYSTEM, "HORIZONTAL", IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "ADDCONTROL_HANDLE", NULL, iNormalizerSetAddControlHandleAttrib, NULL, NULL, IUPAF_WRITEONLY | IUPAF_IHANDLE | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "ADDCONTROL", NULL, iNormalizerSetAddControlAttrib, NULL, NULL, IUPAF_WRITEONLY | IUPAF_IHANDLENAME | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DELCONTROL_HANDLE", NULL, iNormalizerSetDelControlHandleAttrib, NULL, NULL, IUPAF_WRITEONLY | IUPAF_IHANDLE | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DELCONTROL", NULL, iNormalizerSetDelControlAttrib, NULL, NULL, IUPAF_WRITEONLY | IUPAF_IHANDLENAME | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "FIRST_CONTROL_HANDLE", iNormalizerGetFirstControlHandleAttrib, NULL, NULL, NULL, IUPAF_READONLY | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT | IUPAF_IHANDLE | IUPAF_NO_STRING );
  iupClassRegisterAttribute( data, ic, "NEXT_CONTROL_HANDLE", iNormalizerGetNextControlHandleAttrib, NULL, NULL, NULL, IUPAF_READONLY | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT | IUPAF_IHANDLE | IUPAF_NO_STRING );

  return ic;
}

IUP_API Ihandle *amy_IupNormalizerv( struct libData *data, Ihandle **ih_list )
{
  return amy_IupCreatev( data, "normalizer", (void**)ih_list );
}

IUP_API Ihandle *amy_IupNormalizerV( struct libData *data, Ihandle *ih_first, va_list arglist )
{
  return amy_IupCreateV( data, "normalizer", ih_first, arglist );
}

IUP_API Ihandle *amy_IupNormalizer( struct libData *data, Ihandle *ih_first, ... )
{
  Ihandle *ih;

  va_list arglist;
  va_start(arglist, ih_first );
  ih = amy_IupCreateV( data, "normalizer", ih_first, arglist );
  va_end(arglist );

  return ih;
}
