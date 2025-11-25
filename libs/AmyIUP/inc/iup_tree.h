/** \file
 * \brief Tree control (not exported API)
 *
 * See Copyright Notice in iup.h
 */

#ifndef __IUP_TREE_H 
#define __IUP_TREE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Kinds of node */
#define ITREE_BRANCH        0
#define ITREE_LEAF          1

#define ITREE_MARK_SINGLE 0
#define ITREE_MARK_MULTIPLE 1

#define ITREE_UPDATEIMAGE_LEAF      1
#define ITREE_UPDATEIMAGE_COLLAPSED 2
#define ITREE_UPDATEIMAGE_EXPANDED  3

void iupdrvTreeInitClass( struct libData *data, Iclass *ic );
void iupTreeUpdateImages( struct libData *data, Ihandle *ih);
void iupdrvTreeAddNode( struct libData *data, Ihandle *ih, int id, int kind, const char* title, int add);
void iupdrvTreeUpdateMarkMode( struct libData *data, Ihandle *ih);

char* iupTreeGetSpacingAttrib( struct libData *data, Ihandle *ih);

#if defined(GTK_MAJOR_VERSION)
typedef char InodeHandle;   /* should be void, but we use char to force compiler checks */
#elif defined(XmVERSION)
typedef struct _WidgetRec InodeHandle;
#elif defined(WINVER)
typedef struct _TREEITEM InodeHandle;
#elif defined(__APPLE__)
typedef void InodeHandle;   /* should be id, but don't want Obj-C in C header, and don't want id* */
#else
typedef struct _InodeData InodeHandle;
#endif

typedef struct _InodeData
{
  InodeHandle* node_handle;  /* HTREEITEM (Windows), Widget (Motif), user_data (model-specific GTK), id (Apple) */
  void* userdata;
} InodeData;

typedef int (*iupTreeNodeFunc)( struct libData *data, Ihandle *ih, InodeHandle* node_handle, int id, void* userdata);
int iupTreeForEach( struct libData *data, Ihandle *ih, iupTreeNodeFunc func, void* userdata);
InodeHandle* iupTreeGetNode( struct libData *data, Ihandle *ih, int id);
InodeHandle* iupTreeGetNodeFromString( struct libData *data, Ihandle *ih, const char* name_id);
int iupTreeFindNodeId( struct libData *data, Ihandle *ih, InodeHandle* node_handle);

InodeHandle* iupdrvTreeGetFocusNode( struct libData *data, Ihandle *ih);
int iupdrvTreeTotalChildCount( struct libData *data, Ihandle *ih, InodeHandle* node_handle);
void iupTreeSelectLastCollapsedBranch( struct libData *data, Ihandle *ih, int *last_id);

void iupTreeDelFromCache( struct libData *data, Ihandle *ih, int id, int count);
void iupTreeIncCacheMem( struct libData *data, Ihandle *ih); /* needed for IupCocoa */
void iupTreeAddToCache( struct libData *data, Ihandle *ih, int add, int kindPrev, InodeHandle* prevNode, InodeHandle* node_handle);
void iupTreeCopyMoveCache( struct libData *data, Ihandle *ih, int id_src, int id_new, int count, int is_copy);

/* copy from one control to another control */
void iupdrvTreeDragDropCopyNode( struct libData *data, Ihandle *src, Ihandle *dst, InodeHandle *itemSrc, InodeHandle *itemDst );

/* Structure of the tree */
struct _IcontrolData
{
  int mark_mode,
      add_expanded,
      show_dragdrop,
      show_rename,
      show_toggle,
      stamp,    /* GTK only */
      spacing;

  void* def_image_leaf;       /* Default image leaf */
  void* def_image_collapsed;  /* Default image collapsed */
  void* def_image_expanded;   /* Default image expanded */

  void* def_image_leaf_mask;       /* Motif Only */
  void* def_image_collapsed_mask;  
  void* def_image_expanded_mask;  

  InodeData *node_cache;   /* given the id returns node native handle and user_data */
  int node_cache_max, node_count;
};


#ifdef __cplusplus
}
#endif

#endif
