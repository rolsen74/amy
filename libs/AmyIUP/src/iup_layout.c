
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
 * \brief Abstract Layout Management
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdlib.h>  
#include <stdio.h>  
#include <stdarg.h>  

#include "iup.h"

#include "iup_object.h"
#include "iup_drv.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_layout.h"
#include "iup_assert.h" 

#endif
 
IUP_API void amy_IupRefreshChildren( struct libData *data, Ihandle *ih )
{
  int shrink;
  Ihandle *dialog, *child;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return;

  /* must have children */
  if ( ! ih->firstchild)
    return;

  /* must be inside a dialog */
  /* it can not be a dialog */
  dialog = amy_IupGetDialog( data, ih );
  if ( ! dialog || dialog==ih)
    return;

  /****** local iupLayoutCompute,
     but ih will not be changed, only its children. */

  shrink = iupAttribGetBoolean( data, dialog, "SHRINK" );

  /* children only iupBaseComputeNaturalSize */
  {
    int w=0, h=0, children_expand=ih->expand;
    iupClassObjectComputeNaturalSize( data, ih, &w, &h, &children_expand );

    /* If the container natural size changed from inside, simply ignore the change */
  }

  /* children only iupBaseSetCurrentSize */
  iupClassObjectSetChildrenCurrentSize( data, ih, shrink );

  /* children only iupBaseSetPosition */
  iupClassObjectSetChildrenPosition( data, ih, ih->x, ih->y );


  /****** local iupLayoutUpdate,
     but ih will not be changed, only its children. */
  for (child = ih->firstchild; child; child = child->brother)
  {
    if (child->handle)
      iupLayoutUpdate( data, child );
  }
}

IUP_API void amy_IupRefresh( struct libData *data, Ihandle *ih )
{
  Ihandle *dialog;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return;

  dialog = amy_IupGetDialog( data, ih );
  if (dialog)
  {
    iupLayoutCompute( data, dialog );

    if (dialog->handle)
      iupLayoutUpdate( data, dialog );
  }
}

IUP_API void amy_IupUpdate( struct libData *data, Ihandle *ih )
{
  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return;

  if (ih->handle && ih->iclass->nativetype != IUP_TYPEVOID)
    iupdrvPostRedraw( data, ih );
}

static void iLayoutDisplayUpdateChildren( struct libData *data, Ihandle *ih )
{
  Ihandle *child;
  for (child = ih->firstchild; child; child = child->brother)
  {
    iLayoutDisplayUpdateChildren( data, child );
    amy_IupUpdate( data, child );
  }
}

IUP_API void amy_IupUpdateChildren( struct libData *data, Ihandle *ih )
{
  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return;

  iLayoutDisplayUpdateChildren( data, ih );
}

static void iLayoutDisplayRedrawChildren( struct libData *data, Ihandle *ih )
{
  Ihandle *child;
  for (child = ih->firstchild; child; child = child->brother)
  {
    iLayoutDisplayRedrawChildren( data, child );

    if (child->handle && child->iclass->nativetype != IUP_TYPEVOID)
      iupdrvRedrawNow( data, child );
  }
}

IUP_API void amy_IupRedraw( struct libData *data, Ihandle *ih, int children )
{
  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return;

  if (ih->handle && ih->iclass->nativetype != IUP_TYPEVOID)
    iupdrvRedrawNow( data, ih );

  if (children)
    iLayoutDisplayRedrawChildren( data, ih );
}

IUP_SDK_API void iupLayoutUpdate( struct libData *data, Ihandle *ih )
{
  Ihandle *child;

  if (ih->flags & IUP_FLOATING_IGNORE)
    return;

  /* update size and position of the native control */
  iupClassObjectLayoutUpdate( data, ih );

  /* update its children */
  for (child = ih->firstchild; child; child = child->brother)
  {
    if (child->handle)
      iupLayoutUpdate( data, child );
  }
}

void iupLayoutCompute( struct libData *data, Ihandle *ih )
{
  /* usually called only for the dialog */

  int shrink = iupAttribGetBoolean( data, ih, "SHRINK" );

  /* Compute the natural size for all elements in the dialog,   
     using the minimum visible size and the defined user size.
     The minimum visible size is the size where all the controls can display
     all their contents.
     The defined user size is used to increase the value of the minimum visible size for containers,
     for standard controls will replace the minimum visible size.
     So the native size will be the maximum value between 
     minimum visible size and defined user size.
     Also calculates the expand configuration for each element, but expand is used only in SetChildrenCurrentSize.
     SEQUENCE: will first calculate the native size for the children, then for the element. */
  iupBaseComputeNaturalSize( data, ih );

  /* Set the current size (not reflected in the native element yet) based on
     the natural size and the expand configuration. 
     If shrink is 0 (default) the current size of containers can be only larger than the natural size,
     the result will depend on the EXPAND attribute.
     If shrink is 1 the containers can be resized to sizes smaller than the natural size.
     SEQUENCE: will first calculate the current size of the element, then for the children. */
  iupBaseSetCurrentSize( data, ih, 0, 0, shrink );

  /* Now that the current size is known, set the position of the elements 
     relative to the parent.
     SEQUENCE: will first set the position of the element, then for the children. */
  iupBaseSetPosition( data, ih, 0, 0 );
}

IUP_SDK_API void iupLayoutApplyMinMaxSize( struct libData *data, Ihandle *ih, int *w, int *h )
{
  if (ih->flags & IUP_MINSIZE)
  {
    char *value = iupAttribGet( data, ih, "MINSIZE" );
    int min_w = 0, min_h = 0;          /* MINSIZE default value */
    iupStrToIntInt(value, &min_w, &min_h, 'x' );
    if (w && *w < min_w) *w = min_w;
    if (h && *h < min_h) *h = min_h;
  }

  if (ih->flags & IUP_MAXSIZE)
  {
    char *value = iupAttribGet( data, ih, "MAXSIZE" );
    int max_w = 65535, max_h = 65535;  /* MAXSIZE default value */
    iupStrToIntInt(value, &max_w, &max_h, 'x' );
    if (w && *w > max_w) *w = max_w;
    if (h && *h > max_h) *h = max_h;
  }
}

void iupBaseComputeNaturalSize( struct libData *data, Ihandle *ih )
{
  /* always initialize the natural size using the user size */
  ih->naturalwidth = ih->userwidth;
  ih->naturalheight = ih->userheight;

  if (ih->iclass->childtype != IUP_CHILDNONE || 
      ih->iclass->nativetype == IUP_TYPEDIALOG)  /* pre-defined dialogs can restrict the number of children */
  {
    int w=0, h=0, children_expand=0;  /* if there is no children will not expand, when not a dialog */

    /* If a container then update the "expand" member from the EXPAND attribute.
       The ih->expand member can not be used for the container attribute because
       it is used to combine the container value with the children value. */
    iupBaseContainerUpdateExpand( data, ih );

    /* for containers always compute */
    iupClassObjectComputeNaturalSize( data, ih, &w, &h, &children_expand );

    if (ih->iclass->nativetype == IUP_TYPEDIALOG)
    {
      /* only update the natural size if user size is not defined. */
      /* amy_IupDialog is the only container where this must be done */ 
      /* if the natural size is bigger than the actual dialog size then
         the dialog will be resized, if smaller then the dialog remains with the same size. */
      ih->expand |= children_expand;
      if (ih->naturalwidth <= 0) ih->naturalwidth = iupMAX(ih->currentwidth, w );
      if (ih->naturalheight <= 0) ih->naturalheight = iupMAX(ih->currentheight, h );
    }
    else
    {
      /* combine to only expand if the children can expand */
      ih->expand &= children_expand; 
      ih->naturalwidth = iupMAX(ih->naturalwidth, w );
      ih->naturalheight = iupMAX(ih->naturalheight, h );
    }
  }
  else 
  {
    /* for non-container only compute if user size is not defined */
    if (ih->naturalwidth <= 0 || ih->naturalheight <= 0)
    {
      int w=0, h=0, 
          children_expand;  /* unused if not a container */
      iupClassObjectComputeNaturalSize( data, ih, &w, &h, &children_expand );

      if (ih->naturalwidth <= 0) ih->naturalwidth = w;
      if (ih->naturalheight <= 0) ih->naturalheight = h;
    }
  }

  /* crop the natural size */
  iupLayoutApplyMinMaxSize( data, ih, &(ih->naturalwidth), &(ih->naturalheight));
}

void iupBaseSetCurrentSize( struct libData *data, Ihandle *ih, int w, int h, int shrink )
{
  if (ih->iclass->nativetype == IUP_TYPEDIALOG)
  {
    /* w and h parameters here are ignored, because they are always 0 for the dialog. */

    /* current size is zero before map and when reset by the application */
    /* after that the current size must follow the actual size of the dialog */
    if ( ! ih->currentwidth)  ih->currentwidth  = ih->naturalwidth;
    if ( ! ih->currentheight) ih->currentheight = ih->naturalheight;
  }
  else
  {
    if (ih->iclass->childtype != IUP_CHILDNONE && !shrink)
    {
      /* shrink is only used by containers, usually is 0 */
      /* for non containers is always 1, so they always can be smaller than the natural size */
      w = iupMAX(ih->naturalwidth, w );
      h = iupMAX(ih->naturalheight, h );
    }

    /* if expand use the given size, else use the natural size */
    ih->currentwidth = (ih->expand & IUP_EXPAND_WIDTH || ih->expand & IUP_EXPAND_WFREE) ? w : ih->naturalwidth;
    ih->currentheight = (ih->expand & IUP_EXPAND_HEIGHT || ih->expand & IUP_EXPAND_HFREE) ? h : ih->naturalheight;
  }

  /* crop also the current size if some expanded */
  if (ih->expand & IUP_EXPAND_WIDTH || ih->expand & IUP_EXPAND_HEIGHT ||
      ih->expand & IUP_EXPAND_WFREE || ih->expand & IUP_EXPAND_HFREE)
    iupLayoutApplyMinMaxSize( data, ih, &(ih->currentwidth), &(ih->currentheight));

  if (ih->firstchild)
    iupClassObjectSetChildrenCurrentSize( data, ih, shrink );
}

void iupBaseSetPosition( struct libData *data, Ihandle *ih, int x, int y )
{
  ih->x = x;
  ih->y = y;

  if (ih->firstchild)
    iupClassObjectSetChildrenPosition( data, ih, x, y );
}
