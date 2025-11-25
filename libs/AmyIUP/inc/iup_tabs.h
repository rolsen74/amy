/** \file
 * \brief Tabs Control (not exported API)
 *
 * See Copyright Notice in "iup.h"
 */
 
#ifndef __IUP_TABS_H 
#define __IUP_TABS_H

#ifdef __cplusplus
extern "C" {
#endif


char* iupTabsGetTabOrientationAttrib( struct libData *data, Ihandle *ih );
char* iupTabsGetTabTypeAttrib( struct libData *data, Ihandle *ih );
char* iupTabsGetTabPaddingAttrib( struct libData *data, Ihandle *ih );
char* iupTabsGetTabVisibleAttrib( struct libData *data, Ihandle* ih, int pos);
char* iupTabsGetTitleAttrib( struct libData *data, Ihandle *ih, int pos);

void iupTabsCheckCurrentTab( struct libData *data, Ihandle *ih, int pos, int removed );

int iupdrvTabsIsTabVisible( struct libData *data, Ihandle *child, int pos );
int iupdrvTabsExtraDecor( struct libData *data, Ihandle *ih );
int iupdrvTabsExtraMargin( struct libData *data );
int iupdrvTabsGetLineCountAttrib( struct libData *data, Ihandle *ih );
void iupdrvTabsSetCurrentTab( struct libData *data, Ihandle *ih, int pos );
int iupdrvTabsGetCurrentTab( struct libData *data, Ihandle *ih );
void iupdrvTabsInitClass( struct libData *data, Iclass *ic );

typedef enum
{
  ITABS_TOP, ITABS_BOTTOM, ITABS_LEFT, ITABS_RIGHT
} ItabsType;

typedef enum
{
  ITABS_HORIZONTAL, ITABS_VERTICAL
} ItabsOrientation;

/* Control context */
struct _IcontrolData
{
  ItabsType type;
  ItabsOrientation orientation;
  int horiz_padding, vert_padding;  /* tab title margin */
  int show_close;
  int is_multiline;   /* used only in Windows */
  int has_invisible;  /* used only in Windows */
};


#ifdef __cplusplus
}
#endif

#endif
