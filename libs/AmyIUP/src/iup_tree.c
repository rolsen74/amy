
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"
#include "inc/iup_tree.h"

// --

#if 0

/** \file
 * \brief Tree control
 *
 * See Copyright Notice in iup.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "iup.h"
#include "iupcbs.h"

#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_drv.h"
#include "iup_drvfont.h"
#include "iup_drvinfo.h"
#include "iup_stdcontrols.h"
#include "iup_layout.h"
#include "iup_tree.h"
#include "iup_assert.h"

#endif

/************************************************************************************/

/* These utilities must work for amy_IupTree and amy_IupFlatTree */

typedef int (*IFnv)(Ihandle*, void* );

IUP_API int amy_IupTreeGetId( struct libData *data, Ihandle *ih, void *userdata )
{
  IFnv find_userdata_cb;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return -1;

  find_userdata_cb = (IFnv) amy_IupGetCallback( data, ih, "_IUPTREE_FIND_USERDATA_CB" );

  return find_userdata_cb( ih, userdata );
}

IUP_API int amy_IupTreeSetUserId( struct libData *data, Ihandle *ih, int id, void *userdata )
{
  int count;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return 0;

  count = amy_IupGetInt( data, ih, "COUNT" );
  if (id >= 0 && id < count)
  {
    amy_IupSetAttributeId( data, ih, "USERDATA", id, (char*)userdata );
    return 1;
  }

  return 0;
}

IUP_API void *amy_IupTreeGetUserId( struct libData *data, Ihandle *ih, int id )
{
  int count;

  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return NULL;

  count = amy_IupGetInt( data, ih, "COUNT" );
  if (id >= 0 && id < count)
    return amy_IupGetAttributeId( data, ih, "USERDATA", id );

  return NULL;
}

IUP_API void amy_IupTreeSetAttributeHandle( struct libData *data, Ihandle *ih, const char *a, int id, Ihandle *ih_named)
{
  amy_IupSetAttributeHandleId( data, ih, a, id, ih_named );
}


/************************************************************************************/


static void iTreeInitializeImages( struct libData *data )
{
  Ihandle *image_leaf, *image_blank, *image_paper;  
  Ihandle *image_collapsed, *image_expanded, *image_empty;

#define ITREE_IMG_WIDTH   16
#define ITREE_IMG_HEIGHT  16

  unsigned char img_leaf[ITREE_IMG_WIDTH*ITREE_IMG_HEIGHT] = 
  {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 4, 4, 5, 5, 5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 4, 5, 5, 1, 6, 1, 5, 0, 0, 0, 0,
    0, 0, 0, 0, 3, 4, 4, 5, 5, 1, 6, 1, 5, 0, 0, 0,
    0, 0, 0, 0, 3, 4, 4, 4, 5, 5, 1, 1, 5, 0, 0, 0,
    0, 0, 0, 0, 2, 3, 4, 4, 4, 5, 5, 5, 4, 0, 0, 0,
    0, 0, 0, 0, 2, 3, 3, 4, 4, 4, 5, 4, 4, 0, 0, 0,
    0, 0, 0, 0, 0, 2, 3, 3, 4, 4, 4, 4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, 2, 3, 3, 3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };

  unsigned char img_collapsed[ITREE_IMG_WIDTH*ITREE_IMG_HEIGHT] =
  {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
    0, 0, 0, 0, 2, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0,  
    0, 0, 0, 2, 6, 5, 5, 7, 2, 3, 0, 0, 0, 0, 0, 0, 
    0, 0, 2, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 0, 
    0, 0, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 4, 3, 
    0, 0, 2, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 1, 4, 3, 
    0, 0, 2, 5, 7, 7, 7, 7, 7, 7, 1, 7, 1, 7, 4, 3, 
    0, 0, 2, 5, 7, 7, 7, 7, 7, 7, 7, 1, 7, 1, 4, 3, 
    0, 0, 2, 5, 7, 7, 7, 7, 1, 7, 1, 7, 1, 7, 4, 3, 
    0, 0, 2, 5, 7, 7, 7, 7, 7, 1, 7, 1, 7, 1, 4, 3, 
    0, 0, 2, 5, 7, 7, 7, 7, 1, 7, 1, 7, 1, 1, 4, 3, 
    0, 0, 2, 5, 1, 7, 1, 1, 7, 1, 7, 1, 1, 1, 4, 3, 
    0, 0, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3,  
    0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
  };

  unsigned char img_expanded[ITREE_IMG_WIDTH*ITREE_IMG_HEIGHT] =
  {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 2, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 2, 1, 3, 3, 3, 3, 1, 2, 2, 2, 2, 2, 2, 0, 
    0, 0, 2, 1, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 6, 4, 
    0, 0, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 4, 
    0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 3, 6, 4, 
    0, 2, 1, 3, 3, 3, 3, 3, 5, 3, 5, 6, 4, 6, 6, 4, 
    0, 2, 1, 3, 3, 3, 3, 3, 3, 5, 3, 6, 4, 6, 6, 4, 
    0, 0, 2, 0, 3, 3, 3, 3, 5, 3, 5, 5, 2, 4, 2, 4, 
    0, 0, 2, 0, 3, 3, 5, 5, 3, 5, 5, 5, 6, 4, 2, 4, 
    0, 0, 0, 2, 0, 5, 3, 3, 5, 5, 5, 5, 6, 2, 4, 4, 
    0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 
    0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
  };

  unsigned char img_blank[ITREE_IMG_WIDTH*ITREE_IMG_HEIGHT] =
  {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 4, 3, 4, 3, 4, 3, 4, 3, 4, 3, 0, 0, 0, 0,
    0, 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 5, 4, 0, 0, 0,
    0, 0, 4, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 4, 0, 0,
    0, 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 0,
    0, 0, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 2, 0,
    0, 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 2, 0,
    0, 0, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 2, 0,
    0, 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 2, 0,
    0, 0, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 2, 0,
    0, 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 2, 0,
    0, 0, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 2, 0,
    0, 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 2, 0,
    0, 0, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 2, 0,
    0, 0, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 0,
    0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0
  };

  unsigned char img_paper[ITREE_IMG_WIDTH*ITREE_IMG_HEIGHT] =
  {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 4, 3, 4, 3, 4, 3, 4, 3, 4, 3, 0, 0, 0, 0,
    0, 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 5, 4, 0, 0, 0,
    0, 0, 4, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 4, 0, 0,
    0, 0, 3, 1, 4, 3, 4, 3, 4, 3, 4, 2, 2, 2, 2, 0,
    0, 0, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 2, 0,
    0, 0, 3, 1, 3, 4, 3, 4, 3, 4, 3, 4, 1, 5, 2, 0,
    0, 0, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 2, 0,
    0, 0, 3, 1, 4, 3, 4, 3, 4, 3, 4, 3, 1, 5, 2, 0,
    0, 0, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 2, 0,
    0, 0, 3, 1, 3, 4, 3, 4, 3, 4, 3, 4, 1, 5, 2, 0,
    0, 0, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 2, 0,
    0, 0, 3, 1, 4, 3, 4, 3, 4, 3, 4, 3, 1, 5, 2, 0,
    0, 0, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 2, 0,
    0, 0, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 0,
    0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0
  };

  image_leaf      = amy_IupImage( data, ITREE_IMG_WIDTH, ITREE_IMG_HEIGHT, img_leaf );
  image_collapsed = amy_IupImage( data, ITREE_IMG_WIDTH, ITREE_IMG_HEIGHT, img_collapsed );
  image_expanded  = amy_IupImage( data, ITREE_IMG_WIDTH, ITREE_IMG_HEIGHT, img_expanded );
  image_blank     = amy_IupImage( data, ITREE_IMG_WIDTH, ITREE_IMG_HEIGHT, img_blank );
  image_paper     = amy_IupImage( data, ITREE_IMG_WIDTH, ITREE_IMG_HEIGHT, img_paper );
  image_empty     = amy_IupImage( data, ITREE_IMG_WIDTH, ITREE_IMG_HEIGHT, NULL );

  amy_IupSetAttribute( data, image_leaf, "0", "BGCOLOR" );
  amy_IupSetAttribute( data, image_leaf, "1", "192 192 192" );
  amy_IupSetAttribute( data, image_leaf, "2", "56 56 56" );
  amy_IupSetAttribute( data, image_leaf, "3", "99 99 99" );
  amy_IupSetAttribute( data, image_leaf, "4", "128 128 128" );
  amy_IupSetAttribute( data, image_leaf, "5", "161 161 161" );
  amy_IupSetAttribute( data, image_leaf, "6", "222 222 222" );

  amy_IupSetAttribute( data, image_collapsed, "0", "BGCOLOR" );
  amy_IupSetAttribute( data, image_collapsed, "1", "255 206 156" );
  amy_IupSetAttribute( data, image_collapsed, "2", "156 156 0" );
  amy_IupSetAttribute( data, image_collapsed, "3", "0 0 0" );
  amy_IupSetAttribute( data, image_collapsed, "4", "206 206 99" );
  amy_IupSetAttribute( data, image_collapsed, "5", "255 255 206" );
  amy_IupSetAttribute( data, image_collapsed, "6", "247 247 247" );
  amy_IupSetAttribute( data, image_collapsed, "7", "255 255 156" );

  amy_IupSetAttribute( data, image_expanded, "0", "BGCOLOR" );
  amy_IupSetAttribute( data, image_expanded, "1", "255 255 255" );
  amy_IupSetAttribute( data, image_expanded, "2", "156 156 0" );
  amy_IupSetAttribute( data, image_expanded, "3", "255 255 156" );
  amy_IupSetAttribute( data, image_expanded, "4", "0 0 0" );
  amy_IupSetAttribute( data, image_expanded, "5", "255 206 156" );
  amy_IupSetAttribute( data, image_expanded, "6", "206 206 99" );

  amy_IupSetAttribute( data, image_blank, "0", "BGCOLOR" );
  amy_IupSetAttribute( data, image_blank, "1", "255 255 255" );
  amy_IupSetAttribute( data, image_blank, "2", "000 000 000" );
  amy_IupSetAttribute( data, image_blank, "3", "119 119 119" );
  amy_IupSetAttribute( data, image_blank, "4", "136 136 136" );
  amy_IupSetAttribute( data, image_blank, "5", "187 187 187" );

  amy_IupSetAttribute( data, image_paper, "0", "BGCOLOR" );
  amy_IupSetAttribute( data, image_paper, "1", "255 255 255" );
  amy_IupSetAttribute( data, image_paper, "2", "000 000 000" );
  amy_IupSetAttribute( data, image_paper, "3", "119 119 119" );
  amy_IupSetAttribute( data, image_paper, "4", "136 136 136" );
  amy_IupSetAttribute( data, image_paper, "5", "187 187 187" );

  amy_IupSetAttribute( data, image_empty, "0", "BGCOLOR" );
  amy_IupSetAttribute( data, image_empty, "FLAT_ALPHA", "Yes" ); /* necessary for Windows */

  amy_IupSetHandle( data, "IMGLEAF",      image_leaf );
  amy_IupSetHandle( data, "IMGCOLLAPSED", image_collapsed );
  amy_IupSetHandle( data, "IMGEXPANDED",  image_expanded );
  amy_IupSetHandle( data, "IMGBLANK",     image_blank );
  amy_IupSetHandle( data, "IMGPAPER",     image_paper );
  amy_IupSetHandle( data, "IMGEMPTY",     image_empty );

#undef ITREE_IMG_WIDTH
#undef ITREE_IMG_HEIGHT
}

void iupTreeUpdateImages( struct libData *data, Ihandle *ih )
{
  char *value = iupAttribGet( data, ih, "IMAGELEAF" );
  if ( ! value) value = "IMGLEAF";
  iupAttribSetClassObject( data, ih, "IMAGELEAF", value );

  value = iupAttribGet( data, ih, "IMAGEBRANCHCOLLAPSED" );
  if ( ! value) value = "IMGCOLLAPSED";
  iupAttribSetClassObject( data, ih, "IMAGEBRANCHCOLLAPSED", value );

  value = iupAttribGet( data, ih, "IMAGEBRANCHEXPANDED" );
  if ( ! value) value = "IMGEXPANDED";
  iupAttribSetClassObject( data, ih, "IMAGEBRANCHEXPANDED", value );
}

void iupTreeSelectLastCollapsedBranch( struct libData *data, Ihandle *ih, int *last_id)
{
  /* if last selected item is a branch, then select its children */
  if (iupStrEqual( amy_IupGetAttributeId( data, ih, "KIND", *last_id), "BRANCH" ) && 
      iupStrEqual( amy_IupGetAttributeId( data, ih, "STATE", *last_id), "COLLAPSED" ))
  {
    int childcount = amy_IupGetIntId( data, ih, "CHILDCOUNT", *last_id );
    if (childcount > 0)
    {
      int start = *last_id + 1;
      int end = *last_id + childcount;
      amy_IupSetfAttribute( data, ih, "MARK", "%d-%d", start, end );
      *last_id = *last_id + childcount;
    }
  }
}

int iupTreeForEach( struct libData *data, Ihandle *ih, iupTreeNodeFunc func, void *userdata)
{
  int i;
  for (i = 0; i < ih->data->node_count; i++)
  {
    if ( ! func( data, ih, ih->data->node_cache[i].node_handle, i, userdata))
      return 0;
  }

  return 1;
}

int iupTreeFindNodeId( struct libData *data, Ihandle *ih, InodeHandle* node_handle)
{
  /* Unoptimized version:
  int i;
  for (i = 0; i < ih->data->node_count; i++)
  {
    if (ih->data->node_cache[i].node_handle == node_handle)
      return i;
  }
  */
  InodeData *node_cache = ih->data->node_cache;
  while(node_cache->node_handle != node_handle && 
        node_cache->node_handle != NULL)   /* the cache always have zeros at the end */
    node_cache++;

  if (node_cache->node_handle != NULL)
    return (int)(node_cache - ih->data->node_cache );
  else
    return -1;
}

static int iTreeFindUserDataId( struct libData *data, Ihandle *ih, void *userdata)
{
  /* Unoptimized version:
  int i;
  for (i = 0; i < ih->data->node_count; i++)
  {
    if (ih->data->node_cache[i].userdata == userdata)
      return i;
  }
  */
  InodeData *node_cache = ih->data->node_cache;
  while(node_cache->userdata != userdata && 
        node_cache->node_handle != NULL)   /* the cache always have zeros at the end */
    node_cache++;

  if (node_cache->node_handle != NULL)
    return (int)(node_cache - ih->data->node_cache );
  else
    return -1;
}

InodeHandle* iupTreeGetNode( struct libData *data, Ihandle *ih, int id)
{
  if (id >= 0 && id < ih->data->node_count)
    return ih->data->node_cache[id].node_handle;
  else if (id == IUP_INVALID_ID && ih->data->node_count!=0)
    return iupdrvTreeGetFocusNode( data, ih );
  else
    return NULL;
}

InodeHandle* iupTreeGetNodeFromString( struct libData *data, Ihandle *ih, const char *name_id)
{
  int id = IUP_INVALID_ID;
  iupStrToInt(name_id, &id );
  return iupTreeGetNode( data, ih, id );
}

static void iTreeAddToCache( struct libData *data, Ihandle *ih, int id, InodeHandle* node_handle)
{
  iupASSERT(id >= 0 && id < ih->data->node_count );
  if (id < 0 || id >= ih->data->node_count)
    return;

  /* node_count here already contains the final count */

  if (id == ih->data->node_count-1)
    ih->data->node_cache[id].node_handle = node_handle;
  else
  {
    /* open space for the new id */
    int remain_count = ih->data->node_count-id;
    memmove(ih->data->node_cache+id+1, ih->data->node_cache+id, remain_count*sizeof(InodeData));
    ih->data->node_cache[id].node_handle = node_handle;
  }

  ih->data->node_cache[id].userdata = NULL;
}

void iupTreeIncCacheMem( struct libData *data, Ihandle *ih)
{
  /* node_count here already contains the final count */

  if (ih->data->node_count+10 > ih->data->node_cache_max)
  {
    int old_node_cache_max = ih->data->node_cache_max;
    ih->data->node_cache_max += 20;
    ih->data->node_cache = realloc(ih->data->node_cache, ih->data->node_cache_max*sizeof(InodeData));
    memset(ih->data->node_cache+old_node_cache_max, 0, 20*sizeof(InodeData));
  }
}

void iupTreeAddToCache( struct libData *data, Ihandle *ih, int add, int kindPrev, InodeHandle* prevNode, InodeHandle* node_handle)
{
  int new_id = 0;

  ih->data->node_count++;

  /* node_count here already contains the final count */
  iupTreeIncCacheMem( data, ih );

  if (prevNode)
  {
    if (add || kindPrev == ITREE_LEAF)
    {
      /* ADD implies always that id=prev_id+1 */
      /* INSERT after a leaf implies always that new_id=prev_id+1 */
      int prev_id = iupTreeFindNodeId( data, ih, prevNode );
      new_id = prev_id+1;
    }
    else
    {
      /* INSERT after a branch implies always that new_id=prev_id+1+child_count */
      int prev_id = iupTreeFindNodeId( data, ih, prevNode );
      int child_count = iupdrvTreeTotalChildCount( data, ih, prevNode );
      new_id = prev_id+1+child_count;
    }
  }

  iTreeAddToCache( data, ih, new_id, node_handle );
  iupAttribSetInt( data, ih, "LASTADDNODE", new_id );
}

void iupTreeDelFromCache( struct libData *data, Ihandle *ih, int id, int count)
{
  int remain_count, last_add_node;

  /* id can be the last node, actually==node_count becase node_count is already updated */
  iupASSERT(id >= 0 && id <= ih->data->node_count );  
  if (id < 0 || id > ih->data->node_count)
    return;

  /* minimum safety check for LASTADDNODE */
  last_add_node = iupAttribGetInt( data, ih, "LASTADDNODE" );
  if (last_add_node >= id && last_add_node < id+count)
    iupAttribSet( data, ih, "LASTADDNODE", NULL );
  else if (last_add_node >= id+count)
    iupAttribSetInt( data, ih, "LASTADDNODE", last_add_node-count );

  /* node_count here already contains the final count */

  /* remove id+count */
  remain_count = ih->data->node_count-id;
  memmove(ih->data->node_cache+id, ih->data->node_cache+id+count, remain_count*sizeof(InodeData));

  /* clear the remaining space */
  memset(ih->data->node_cache+ih->data->node_count, 0, count*sizeof(InodeData));
}

void iupTreeCopyMoveCache( struct libData *data, Ihandle *ih, int id_src, int id_dst, int count, int is_copy)
{
  int remain_count;

  iupASSERT(id_src >= 0 && id_src < ih->data->node_count );
  if (id_src < 0 || id_src >= ih->data->node_count)
    return;

  iupASSERT(id_dst >= 0 && id_dst < ih->data->node_count );
  if (id_dst < 0 || id_dst >= ih->data->node_count)
    return;

  /* dst can NOT be inside src+count area */
  iupASSERT(id_dst < id_src || id_dst > id_src+count );
  if (id_dst >= id_src && id_dst <= id_src+count)
    return;

  /* id_dst here points to the final position for a copy operation */

  /* node_count here contains the final count for a copy operation */
  iupTreeIncCacheMem( data, ih );

  /* add space for new nodes */
  remain_count = ih->data->node_count - (id_dst + count );
  memmove(ih->data->node_cache + id_dst+count, ih->data->node_cache + id_dst, remain_count * sizeof(InodeData));

  if (is_copy) 
  {
    /* during a copy, the userdata is not reused, so clear it */
    memset(ih->data->node_cache+id_dst, 0, count*sizeof(InodeData));
  }
  else /* move = copy + delete */
  {
    /* compensate because we added space for new nodes */
    if (id_src > id_dst)
      id_src += count;

    /* copy userdata from src to dst */
    memcpy(ih->data->node_cache+id_dst, ih->data->node_cache+id_src, count*sizeof(InodeData));

    /* remove the src */
    remain_count = ih->data->node_count - (id_src + count );
    memmove(ih->data->node_cache+id_src, ih->data->node_cache+id_src+count, remain_count*sizeof(InodeData));

    /* clear the remaining space */
    memset(ih->data->node_cache+ih->data->node_count-count, 0, count*sizeof(InodeData));
  }

  iupAttribSet( data, ih, "LASTADDNODE", NULL );
}


/*************************************************************************/


char *iupTreeGetSpacingAttrib( struct libData *data, Ihandle *ih)
{
  return amy_iupStrReturnInt( data, ih->data->spacing );
}

static char *iTreeGetMarkModeAttrib( struct libData *data, Ihandle *ih)
{
  if (ih->data->mark_mode==ITREE_MARK_SINGLE)
    return "SINGLE";
  else
    return "MULTIPLE";
}

static int iTreeSetMarkModeAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if (iupStrEqualNoCase(value, "MULTIPLE" ))
    ih->data->mark_mode = ITREE_MARK_MULTIPLE;    
  else 
    ih->data->mark_mode = ITREE_MARK_SINGLE;

  if (ih->handle)
    iupdrvTreeUpdateMarkMode( data, ih ); /* for this to work, must update during map */

  return 0;
}

static int iTreeSetShiftAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if (iupStrBoolean(value) && iupAttribGetBoolean( data, ih, "CTRL" ))
    iTreeSetMarkModeAttrib( data, ih, "MULTIPLE" );
  else
    iTreeSetMarkModeAttrib( data, ih, "SINGLE" );
  return 1;
}

static int iTreeSetCtrlAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if (iupStrBoolean(value) && iupAttribGetBoolean( data, ih, "SHIFT" ))
    iTreeSetMarkModeAttrib( data, ih, "MULTIPLE" );
  else
    iTreeSetMarkModeAttrib( data, ih, "SINGLE" );
  return 1;
}

static char *iTreeGetShowRenameAttrib( struct libData *data, Ihandle *ih)
{
  return iupStrReturnBoolean( ih->data->show_rename ); 
}

static int iTreeSetShowRenameAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if (iupStrBoolean(value))
    ih->data->show_rename = 1;
  else
    ih->data->show_rename = 0;

  return 0;
}

static char *iTreeGetShowToggleAttrib( struct libData *data, Ihandle *ih)
{
  if (ih->data->show_toggle)
  {
    if (ih->data->show_toggle == 2)
      return "3STATE";
    else
      return "YES";
  }
  else
    return "NO";
}

static int iTreeSetShowToggleAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if (iupStrEqualNoCase(value, "3STATE" ))
    ih->data->show_toggle = 2;
  else if (iupStrBoolean(value))
    ih->data->show_toggle = 1;
  else
    ih->data->show_toggle = 0;

  return 0;
}

static char *iTreeGetShowDragDropAttrib( struct libData *data, Ihandle *ih)
{
  return iupStrReturnBoolean( ih->data->show_dragdrop ); 
}

static int iTreeSetShowDragDropAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  /* valid only before map */
  if (ih->handle)
    return 0;

  if (iupStrBoolean(value))
    ih->data->show_dragdrop = 1;
  else
    ih->data->show_dragdrop = 0;

  return 0;
}

static int iTreeSetAddLeafAttrib( struct libData *data, Ihandle *ih, int id, const char *value)
{
  if ( ! ih->handle)  /* do not do the action before map */
    return 0;
  iupdrvTreeAddNode( data, ih, id, ITREE_LEAF, value, 1 );
  return 0;
}

static int iTreeSetAddBranchAttrib( struct libData *data, Ihandle *ih, int id, const char *value)
{
  if ( ! ih->handle)  /* do not do the action before map */
    return 0;
  iupdrvTreeAddNode( data, ih, id, ITREE_BRANCH, value, 1 );
  return 0;
}

static int iTreeSetInsertLeafAttrib( struct libData *data, Ihandle *ih, int id, const char *value)
{
  if ( ! ih->handle)  /* do not do the action before map */
    return 0;
  iupdrvTreeAddNode( data, ih, id, ITREE_LEAF, value, 0 );
  return 0;
}

static int iTreeSetInsertBranchAttrib( struct libData *data, Ihandle *ih, int id, const char *value)
{
  if ( ! ih->handle)  /* do not do the action before map */
    return 0;
  iupdrvTreeAddNode( data, ih, id, ITREE_BRANCH, value, 0 );
  return 0;
}

static char *iTreeGetAddExpandedAttrib( struct libData *data, Ihandle *ih)
{
  return iupStrReturnBoolean( ih->data->add_expanded ); 
}

static int iTreeSetAddExpandedAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if (iupStrBoolean(value))
    ih->data->add_expanded = 1;
  else
    ih->data->add_expanded = 0;

  return 0;
}

static char *iTreeGetCountAttrib( struct libData *data, Ihandle *ih)
{
  return amy_iupStrReturnInt( data, ih->data->node_count );
}

static char *iTreeGetTotalChildCountAttrib( struct libData *data, Ihandle *ih, int id)
{
  InodeHandle* node_handle = iupTreeGetNode( data, ih, id );
  if ( ! node_handle)
    return NULL;

  return amy_iupStrReturnInt( data, iupdrvTreeTotalChildCount( data, ih, node_handle));
}

static char *iTreeGetUserDataAttrib( struct libData *data, Ihandle *ih, int id)
{
  if (id >= 0 && id < ih->data->node_count)
    return ih->data->node_cache[id].userdata;
  else if (id == IUP_INVALID_ID && ih->data->node_count!=0)
  {
    InodeHandle* node_handle = iupdrvTreeGetFocusNode( data, ih );
    id = iupTreeFindNodeId( data, ih, node_handle );
    if (id >= 0 && id < ih->data->node_count)
      return ih->data->node_cache[id].userdata;
  }
  return NULL;
}

static int iTreeSetUserDataAttrib( struct libData *data, Ihandle *ih, int id, const char *value)
{
  if (id >= 0 && id < ih->data->node_count)
    ih->data->node_cache[id].userdata = (void*)value;
  else if (id == IUP_INVALID_ID && ih->data->node_count!=0)
  {
    InodeHandle* node_handle = iupdrvTreeGetFocusNode( data, ih );
    id = iupTreeFindNodeId( data, ih, node_handle );
    if (id >= 0 && id < ih->data->node_count)
      ih->data->node_cache[id].userdata = (void*)value;
  }
  return 0;
}


/*****************************************************************************************/


static int iTreeDropData_CB( struct libData *data, Ihandle *ih, char *type, void *data2, int len, int x, int y)
{
  int id = amy_IupConvertXYToPos( data, ih, x, y );
  int is_ctrl = 0;
  char key[5];

  /* Data is not the pointer, it contains the pointer */
  Ihandle *ih_source;
  memcpy((void*)&ih_source, data2, len );

  /*TODO support amy_IupFlatTree??? */
  if ( !  amy_IupClassMatch( data, ih_source, "tree" ))
    return IUP_DEFAULT;

  /* A copy operation is enabled with the CTRL key pressed, or else a move operation will occur.
     A move operation will be possible only if the attribute DRAGSOURCEMOVE is Yes.
     When no key is pressed the default operation is copy when DRAGSOURCEMOVE=No and move when DRAGSOURCEMOVE=Yes. */
  iupdrvGetKeyState( data, key );
  if (key[1] == 'C')
    is_ctrl = 1;

  /* Here copy/move of multiple selection is not allowed,
     only a single node and its children. */

  if(ih_source->data->mark_mode == ITREE_MARK_SINGLE)
  {
    int src_id = iupAttribGetInt( data, ih_source, "_IUP_TREE_SOURCEID" );
    InodeHandle *itemDst, *itemSrc;

    itemSrc = iupTreeGetNode( data, ih_source, src_id );
    if ( ! itemSrc)
      return IUP_DEFAULT;

    itemDst = iupTreeGetNode( data, ih, id );
    if ( ! itemDst)
      return IUP_DEFAULT;

    /* Copy the node and its children to the new position */
    iupdrvTreeDragDropCopyNode( data, ih_source, ih, itemSrc, itemDst );

    if( amy_IupGetInt( data, ih_source, "DRAGSOURCEMOVE" ) && !is_ctrl)
      amy_IupSetAttribute( data, ih_source, "DELNODE0", "MARKED" );
  }

  (void)type;
  return IUP_DEFAULT;
}

static int iTreeDragData_CB( struct libData *data, Ihandle *ih, char *type, void *data2, int len)
{
  int id = iupAttribGetInt( data, ih, "_IUP_TREE_SOURCEID" );
  if (id < 0)
    return IUP_DEFAULT;

  if(ih->data->mark_mode == ITREE_MARK_SINGLE)
  {
    /* Single selection */
    amy_IupSetAttributeId( data, ih, "MARKED", id, "YES" );
  }

  /* Copy source handle */
  memcpy(data2, (void*)&ih, len );
 
  (void)type;
  return IUP_DEFAULT;
}

static int iTreeDragDataSize_CB( struct libData *data, Ihandle *ih, char *type)
{
  (void)ih;
  (void)type;
  return sizeof(Ihandle *);
}

static int iTreeDragEnd_CB( struct libData *data, Ihandle *ih, int del)
{
  iupAttribSetInt( data, ih, "_IUP_TREE_SOURCEID", -1 );
  (void)del;
  return IUP_DEFAULT;
}

static int iTreeDragBegin_CB( struct libData *data, Ihandle *ih, int x, int y)
{
  int id = amy_IupConvertXYToPos( data, ih, x, y );
  iupAttribSetInt( data, ih, "_IUP_TREE_SOURCEID", id );
  return IUP_DEFAULT;
}

static int iTreeSetDragDropTreeAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if (iupStrBoolean(value))
  {
    /* Register callbacks to enable drag and drop between trees, DRAG&DROP attributes must still be set by the application */
    amy_IupSetCallback( data, ih, "DRAGBEGIN_CB",    (Icallback)iTreeDragBegin_CB );
    amy_IupSetCallback( data, ih, "DRAGDATASIZE_CB", (Icallback)iTreeDragDataSize_CB );
    amy_IupSetCallback( data, ih, "DRAGDATA_CB",     (Icallback)iTreeDragData_CB );
    amy_IupSetCallback( data, ih, "DRAGEND_CB",      (Icallback)iTreeDragEnd_CB );
    amy_IupSetCallback( data, ih, "DROPDATA_CB",     (Icallback)iTreeDropData_CB );
  }
  else
  {
    /* Unregister callbacks */
    amy_IupSetCallback( data, ih, "DRAGBEGIN_CB",    NULL );
    amy_IupSetCallback( data, ih, "DRAGDATASIZE_CB", NULL );
    amy_IupSetCallback( data, ih, "DRAGDATA_CB",     NULL );
    amy_IupSetCallback( data, ih, "DRAGEND_CB",      NULL );
    amy_IupSetCallback( data, ih, "DROPDATA_CB",     NULL );
  }

  return 1;
}

static int iTreeSetTitleFontStyleAttrib( struct libData *data, Ihandle *ih, int id, const char *value)
{
  int size = 0;
  int is_bold = 0,
    is_italic = 0,
    is_underline = 0,
    is_strikeout = 0;
  char typeface[1024];
  char *font;

  if ( ! value)
    return 0;

  font = amy_IupGetAttributeId( data, ih, "TITLEFONT", id );
  if ( ! font)
    font = amy_IupGetAttribute( data, ih, "FONT" );

  if ( ! iupGetFontInfo( data, font, typeface, &size, &is_bold, &is_italic, &is_underline, &is_strikeout))
    return 0;

  amy_IupSetfAttributeId( data, ih, "TITLEFONT", id, "%s, %s %d", typeface, value, size );

  return 0;
}

static char *iTreeGetTitleFontStyleAttrib( struct libData *data, Ihandle *ih, int id)
{
  int size = 0;
  int is_bold = 0,
    is_italic = 0,
    is_underline = 0,
    is_strikeout = 0;
  char typeface[1024];

  char *font = amy_IupGetAttributeId( data, ih, "TITLEFONT", id );
  if ( ! font)
    font = amy_IupGetAttribute( data, ih, "FONT" );

  if ( ! iupGetFontInfo( data, font, typeface, &size, &is_bold, &is_italic, &is_underline, &is_strikeout))
    return NULL;

  return iupStrReturnStrf("%s%s%s%s", is_bold ? "Bold " : "", is_italic ? "Italic " : "", is_underline ? "Underline " : "", is_strikeout ? "Strikeout " : "" );
}

static int iTreeSetTitleFontSizeAttrib( struct libData *data, Ihandle *ih, int id, const char *value)
{
  int size = 0;
  int is_bold = 0,
    is_italic = 0,
    is_underline = 0,
    is_strikeout = 0;
  char typeface[1024];
  char *font;

  if ( ! value)
    return 0;

  font = amy_IupGetAttributeId( data, ih, "TITLEFONT", id );
  if ( ! font)
    font = amy_IupGetAttribute( data, ih, "FONT" );

  if ( ! iupGetFontInfo( data, font, typeface, &size, &is_bold, &is_italic, &is_underline, &is_strikeout))
    return 0;

  amy_IupSetfAttributeId( data, ih, "TITLEFONT", id, "%s, %s%s%s%s %s", typeface, is_bold ? "Bold " : "", is_italic ? "Italic " : "", is_underline ? "Underline " : "", is_strikeout ? "Strikeout " : "", value );

  return 0;
}

static char *iTreeGetTitleFontSizeAttrib( struct libData *data, Ihandle *ih, int id)
{
  int size = 0;
  int is_bold = 0,
    is_italic = 0,
    is_underline = 0,
    is_strikeout = 0;
  char typeface[1024];

  char *font = amy_IupGetAttributeId( data, ih, "TITLEFONT", id );
  if ( ! font)
    font = amy_IupGetAttribute( data, ih, "FONT" );

  if ( ! iupGetFontInfo( data, font, typeface, &size, &is_bold, &is_italic, &is_underline, &is_strikeout))
    return NULL;

  return amy_iupStrReturnInt( data, size );
}


/*************************************************************************/


static int iTreeCreateMethod( struct libData *data, Ihandle *ih, void **params)
{
  (void)params;

  ih->data = iupALLOCCTRLDATA();

  amy_IupSetAttribute( data, ih, "RASTERSIZE", "400x200" );
  amy_IupSetAttribute( data, ih, "EXPAND", "YES" );

  amy_IupSetCallback( data, ih, "_IUPTREE_FIND_USERDATA_CB", (Icallback)iTreeFindUserDataId );

  ih->data->add_expanded = 1;
  ih->data->node_cache_max = 20;
  ih->data->node_cache = calloc(ih->data->node_cache_max, sizeof(InodeData));

  return IUP_NOERROR;
}

static void iTreeDestroyMethod( struct libData *data, Ihandle *ih)
{
  if (ih->data->node_cache)
    free(ih->data->node_cache );
}

/*************************************************************************/

IUP_API Ihandle *amy_IupTree( struct libData *data )
{
  return amy_IupCreate( data, "tree" );
}

Iclass *iupTreeNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, NULL );

  ic->name = "tree";
  ic->format = NULL; /* no parameters */
  ic->nativetype = IUP_TYPECONTROL;
  ic->childtype = IUP_CHILDNONE;
  ic->is_interactive = 1;
  ic->has_attrib_id = 1;   /* has attributes with IDs that must be parsed */

  /* Class functions */
  ic->New = iupTreeNewClass;
  ic->Create = iTreeCreateMethod;
  ic->LayoutUpdate = iupdrvBaseLayoutUpdateMethod;
  ic->Destroy = iTreeDestroyMethod;

  /* Callbacks */
  iupClassRegisterCallback( data, ic, "TOGGLEVALUE_CB",    "ii" );
  iupClassRegisterCallback( data, ic, "SELECTION_CB",      "ii" );
  iupClassRegisterCallback( data, ic, "MULTISELECTION_CB", "Ii" );
  iupClassRegisterCallback( data, ic, "MULTIUNSELECTION_CB", "Ii" );
  iupClassRegisterCallback( data, ic, "BRANCHOPEN_CB",     "i" );
  iupClassRegisterCallback( data, ic, "BRANCHCLOSE_CB",    "i" );
  iupClassRegisterCallback( data, ic, "EXECUTELEAF_CB",    "i" );
  iupClassRegisterCallback( data, ic, "EXECUTEBRANCH_CB",  "i" );
  iupClassRegisterCallback( data, ic, "SHOWRENAME_CB",     "i" );
  iupClassRegisterCallback( data, ic, "RENAME_CB",         "is" );
  iupClassRegisterCallback( data, ic, "DRAGDROP_CB",       "iiii" );
  iupClassRegisterCallback( data, ic, "RIGHTCLICK_CB",     "i" );
  iupClassRegisterCallback( data, ic, "MOTION_CB", "iis" );
  iupClassRegisterCallback( data, ic, "BUTTON_CB", "iiiis" );
  iupClassRegisterCallback( data, ic, "NODEREMOVED_CB", "s" );

  /* Common Callbacks */
  iupBaseRegisterCommonCallbacks( data, ic );

  /* Common */
  iupBaseRegisterCommonAttrib( data, ic );

  /* Visual */
  iupBaseRegisterVisualAttrib( data, ic );

  /* Drag&Drop */
  iupdrvRegisterDragDropAttrib( data, ic );

  /* amy_IupTree Attributes - GENERAL */
  iupClassRegisterAttribute( data, ic, "DRAGDROPTREE", NULL, iTreeSetDragDropTreeAttrib, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "SHOWDRAGDROP", iTreeGetShowDragDropAttrib, iTreeSetShowDragDropAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "SHOWRENAME",   iTreeGetShowRenameAttrib,   iTreeSetShowRenameAttrib,   NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "SHOWTOGGLE",   iTreeGetShowToggleAttrib,   iTreeSetShowToggleAttrib,   NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "ADDEXPANDED",  iTreeGetAddExpandedAttrib,  iTreeSetAddExpandedAttrib,  IUPAF_SAMEASSYSTEM, "YES", IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "COUNT",        iTreeGetCountAttrib, NULL, NULL, NULL, IUPAF_NO_DEFAULTVALUE|IUPAF_READONLY|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "LASTADDNODE", NULL, NULL, IUPAF_SAMEASSYSTEM, NULL, IUPAF_READONLY|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "ADDROOT", NULL, NULL, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DROPEQUALDRAG", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "HIDELINES", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "HIDEBUTTONS", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "RENAMECARET", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "RENAMESELECTION", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CPADDING", iupBaseGetCPaddingAttrib, iupBaseSetCPaddingAttrib, NULL, NULL, IUPAF_NO_SAVE | IUPAF_NOT_MAPPED );
  iupClassRegisterAttribute( data, ic, "CSPACING", iupBaseGetCSpacingAttrib, iupBaseSetCSpacingAttrib, NULL, NULL, IUPAF_NO_SAVE | IUPAF_NOT_MAPPED );

  /* amy_IupTree Attributes - MARKS */
  iupClassRegisterAttribute( data, ic, "CTRL",  NULL, iTreeSetCtrlAttrib,  NULL, NULL, IUPAF_NOT_MAPPED );
  iupClassRegisterAttribute( data, ic, "SHIFT", NULL, iTreeSetShiftAttrib, NULL, NULL, IUPAF_NOT_MAPPED );
  iupClassRegisterAttribute( data, ic, "MARKMODE",  iTreeGetMarkModeAttrib, iTreeSetMarkModeAttrib,  IUPAF_SAMEASSYSTEM, "SINGLE", IUPAF_NOT_MAPPED );

  /* amy_IupTree Attributes - ACTION */
  iupClassRegisterAttributeId( data, ic, "ADDLEAF",   NULL, iTreeSetAddLeafAttrib,   IUPAF_NOT_MAPPED|IUPAF_WRITEONLY|IUPAF_NO_INHERIT );
  iupClassRegisterAttributeId( data, ic, "ADDBRANCH", NULL, iTreeSetAddBranchAttrib, IUPAF_NOT_MAPPED|IUPAF_WRITEONLY|IUPAF_NO_INHERIT );
  iupClassRegisterAttributeId( data, ic, "INSERTLEAF",   NULL, iTreeSetInsertLeafAttrib,   IUPAF_NOT_MAPPED|IUPAF_WRITEONLY|IUPAF_NO_INHERIT );
  iupClassRegisterAttributeId( data, ic, "INSERTBRANCH", NULL, iTreeSetInsertBranchAttrib, IUPAF_NOT_MAPPED|IUPAF_WRITEONLY|IUPAF_NO_INHERIT );

  /* amy_IupTree Attributes - NODES */
  iupClassRegisterAttributeId( data, ic, "TOTALCHILDCOUNT", iTreeGetTotalChildCountAttrib,   NULL, IUPAF_READONLY|IUPAF_NO_INHERIT );
  iupClassRegisterAttributeId( data, ic, "USERDATA", iTreeGetUserDataAttrib, iTreeSetUserDataAttrib, IUPAF_NO_STRING|IUPAF_NO_INHERIT );
  iupClassRegisterAttributeId( data, ic, "TITLEFONTSTYLE", iTreeGetTitleFontStyleAttrib, iTreeSetTitleFontStyleAttrib, IUPAF_NO_INHERIT );
  iupClassRegisterAttributeId( data, ic, "TITLEFONTSIZE", iTreeGetTitleFontSizeAttrib, iTreeSetTitleFontSizeAttrib, IUPAF_NO_INHERIT );

  /* Default node images */
  if ( !  amy_IupGetHandle( data, "IMGLEAF" ) || ! amy_IupGetHandle( data, "IMGBLANK" ) || ! amy_IupGetHandle( data, "IMGPAPER" ))
    iTreeInitializeImages( data );

  iupdrvTreeInitClass( data, ic );

  return ic;
}

