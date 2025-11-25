
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"
#include "inc/iup_text.h"

// --

#if 0

/** \file
 * \brief Text Control.
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iup.h"
#include "iupcbs.h"

#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_drv.h"
#include "iup_drvfont.h"
#include "iup_stdcontrols.h"
#include "iup_register.h"
#include "iup_layout.h"
#include "iup_mask.h"
#include "iup_array.h"
#include "iup_text.h"
#include "iup_assert.h"

#endif

/* Used by List and Text, implemented in Text
   Can NOT use ih->data 
*/
int iupEditCallActionCb( struct libData *data, Ihandle *ih, IFnis cb, const char *insert_value, int start, int end, void *mask, int nc, int remove_dir, int utf8)
{
  char *new_value, *value;
  int ret = -1, /* normal processing */
      key = 0;

  if ( ! cb && !mask)
    return ret;

  value = amy_IupGetAttribute( data, ih, "VALUE" );  /* it will return a non NULL internal buffer */

  if ( ! insert_value)
  {
    new_value = value;
    iupStrRemove(new_value, start, end, remove_dir, utf8 );
  }
  else
  {
    if (value[0]==0)
      new_value = iupStrDup(insert_value );
    else
      new_value = iupStrInsert(value, insert_value, start, end, utf8 );
  }

  if (insert_value && insert_value[0]!=0 && insert_value[1]==0)
    key = insert_value[0];

  if ( ! new_value)
    return ret;

  if (nc && (int)strlen(new_value) > nc)
  {
    if (new_value != value) free(new_value );
    return 0; /* abort */
  }

  if (mask && iupMaskCheck( data, (Imask*)mask, new_value)==0)
  {
    IFns fail_cb = (IFns) amy_IupGetCallback( data, ih, "MASKFAIL_CB" );
    if (fail_cb) fail_cb( data, ih, new_value );
    if (new_value != value) free(new_value );
    return 0; /* abort */
  }

  if (cb)
  {
    int cb_ret = cb( data, ih, key, (char*)new_value );
    if (cb_ret==IUP_IGNORE)
      ret = 0; /* abort */
    else if (cb_ret==IUP_CLOSE)
    {
      amy_IupExitLoop( data );
      ret = 0; /* abort */
    }
    else if (cb_ret!=0 && key!=0 && 
             cb_ret != IUP_DEFAULT && cb_ret != IUP_CONTINUE)  
      ret = cb_ret; /* replace key */
  }

  if (new_value != value) free(new_value );
  return ret;
}

char *iupTextGetFormattingAttrib( struct libData *data, Ihandle *ih )
{
  return iupStrReturnBoolean( ih->data->has_formatting ); 
}

int iupTextSetFormattingAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if (ih->handle)  /* only before map */
    return 0;

  ih->data->has_formatting = iupStrBoolean(value );

  return 0;
}

static void iTextDestroyFormatTags( struct libData *data, Ihandle *ih )
{
  /* called if the element was destroyed before it was mapped */
  int i, count = iupArrayCount( data, ih->data->formattags );
  Ihandle** tag_array = (Ihandle**) iupArrayGetData( data, ih->data->formattags );
  for (i = 0; i < count; i++)
    amy_IupDestroy( data, tag_array[i] );
  iupArrayDestroy( data, ih->data->formattags );
  ih->data->formattags = NULL;
}

static void iTextUpdateValueAttrib( struct libData *data, Ihandle *ih )
{
  char *value = iupAttribGet( data, ih, "VALUE" );
  if (value)
  {
    iupAttribSetClassObject( data, ih, "VALUE", value );

    iupAttribSet( data, ih, "VALUE", NULL ); /* clear hash table */
  }
}

char *iupTextGetNCAttrib( struct libData *data, Ihandle *ih )
{
  return amy_iupStrReturnInt( data, ih->data->nc );
}

static void iTextAddFormatTag( struct libData *data, Ihandle *ih, Ihandle *formattag)
{
  char *bulk = iupAttribGet( data, formattag, "BULK" );
  if (bulk && iupStrBoolean(bulk))
  {
    Ihandle *child;
    void* state = iupdrvTextAddFormatTagStartBulk( data, ih );

    char *cleanout = iupAttribGet( data, formattag, "CLEANOUT" );
    if (cleanout && iupStrBoolean(cleanout))
      amy_IupSetAttribute( data, ih, "REMOVEFORMATTING", "ALL" );

    for (child = formattag->firstchild; child; child = child->brother)
      iupdrvTextAddFormatTag( data, ih, child, 1 );

    iupdrvTextAddFormatTagStopBulk( data, ih, state );
  }
  else
    iupdrvTextAddFormatTag( data, ih, formattag, 0 );

  amy_IupDestroy( data, formattag );
}

void iupTextUpdateFormatTags( struct libData *data, Ihandle *ih )
{
  /* called when the element is mapped */
  int i, count = iupArrayCount( data, ih->data->formattags );
  Ihandle** tag_array = (Ihandle**) iupArrayGetData( data, ih->data->formattags );

  /* must update VALUE before updating the format */
  iTextUpdateValueAttrib( data, ih );

  for (i = 0; i < count; i++)
    iTextAddFormatTag( data, ih, tag_array[i] );

  iupArrayDestroy( data, ih->data->formattags );
  ih->data->formattags = NULL;
}

int iupTextSetAddFormatTagHandleAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  Ihandle *formattag = (Ihandle*)value;
  if ( ! iupObjectCheck( data, formattag ))
    return 0;

  if (ih->handle)
  {
    /* must update VALUE before updating the format */
    iTextUpdateValueAttrib( data, ih );

    iTextAddFormatTag( data, ih, formattag );
  }
  else
  {
    Ihandle** tag_array;
    int i;

    if ( ! ih->data->formattags)
      ih->data->formattags = iupArrayCreate( data, 10, sizeof(Ihandle*));

    i = iupArrayCount( data, ih->data->formattags );
    tag_array = (Ihandle**) iupArrayInc( data, ih->data->formattags );
    tag_array[i] = formattag;
  }
  return 0;
}

int iupTextSetAddFormatTagAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  iupTextSetAddFormatTagHandleAttrib( data, ih, (char*) amy_IupGetHandle( data, value));
  return 1;
}

static char *iTextGetMaskAttrib( struct libData *data, Ihandle *ih )
{
  if (ih->data->mask)
    return iupMaskGetStr( data, ih->data->mask );
  else
    return NULL;
}

static int iTextSetValueMaskedAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if (value)
  {
    if (ih->data->mask && iupMaskCheck( data, ih->data->mask, value)==0)
      return 0; /* abort */
    amy_IupStoreAttribute( data, ih, "VALUE", value );
  }
  return 0;
}

static int iTextSetMaskNoEmptyAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if (ih->data->mask)
  {
    int val = iupStrBoolean(value );
    iupMaskSetNoEmpty( data, ih->data->mask, val );
  }
  return 1;
}

static int iTextSetMaskCaseIAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if (ih->data->mask)
  {
    int val = iupStrBoolean(value );
    iupMaskSetCaseI( data, ih->data->mask, val );
  }
  return 1;
}

static int iTextSetMaskAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if ( ! value)
  {
    if (ih->data->mask)
    {
      iupMaskDestroy( data, ih->data->mask );
      ih->data->mask = NULL;
    }
  }
  else
  {
    Imask *mask = iupMaskCreate( data, value );
    if (mask)
    {
      int val = iupAttribGetInt( data, ih, "MASKCASEI" );
      iupMaskSetCaseI( data, mask, val );

      val = iupAttribGetInt( data, ih, "MASKNOEMPTY" );
      iupMaskSetNoEmpty( data, mask, val );

      if (ih->data->mask)
        iupMaskDestroy( data, ih->data->mask );

      ih->data->mask = mask;
      return 0;
    }
  }

  return 0;
}

static int iTextSetMaskIntAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if ( ! value)
  {
    if (ih->data->mask)
    {
      iupMaskDestroy( data, ih->data->mask );
      ih->data->mask = NULL;
    }
  }
  else
  {
    Imask *mask;
    int min, max;

    if (iupStrToIntInt(value, &min, &max, ':')!=2)
      return 0;

    mask = iupMaskCreateInt( data, min, max );
    if (mask)
    {
      int val = iupAttribGetInt( data, ih, "MASKNOEMPTY" );
      iupMaskSetNoEmpty( data, mask, val );

      if (ih->data->mask)
        iupMaskDestroy( data, ih->data->mask );

      ih->data->mask = mask;
      return 1; /* store only a valid mask */
    }
  }

  return 0;
}

static int iTextSetMaskFloatAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if ( ! value)
  {
    if (ih->data->mask)
    {
      iupMaskDestroy( data, ih->data->mask );
      ih->data->mask = NULL;
    }
  }
  else
  {
    Imask *mask;
    float min, max;
    char *decimal_symbol = iupAttribGet( data, ih, "MASKDECIMALSYMBOL" );
    if ( ! decimal_symbol)
      decimal_symbol = amy_IupGetGlobal( data, "DEFAULTDECIMALSYMBOL" );

    if (iupStrToFloatFloat(value, &min, &max, ':')!=2)
      return 0;

    mask = iupMaskCreateFloat( data, min, max, decimal_symbol );
    if (mask)
    {
      int val = iupAttribGetInt( data, ih, "MASKNOEMPTY" );
      iupMaskSetNoEmpty( data, mask, val );

      if (ih->data->mask)
        iupMaskDestroy( data, ih->data->mask );

      ih->data->mask = mask;
      return 1; /* store only a valid mask */
    }
  }

  return 0;
}

static int iTextSetMaskRealAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if ( ! value)
  {
    if (ih->data->mask)
    {
      iupMaskDestroy( data, ih->data->mask );
      ih->data->mask = NULL;
    }
  }
  else
  {
    Imask *mask;
    char *decimal_symbol = iupAttribGet( data, ih, "MASKDECIMALSYMBOL" );
    int positive = 0;

    if (iupStrEqualNoCase(value, "UNSIGNED" ))
      positive = 1;

    mask = iupMaskCreateReal( data, positive, decimal_symbol );
    if (mask)
    {
      int val = iupAttribGetInt( data, ih, "MASKNOEMPTY" );
      iupMaskSetNoEmpty( data, mask, val );

      if (ih->data->mask)
        iupMaskDestroy( data, ih->data->mask );

      ih->data->mask = mask;
      return 1; /* store only a valid mask */
    }
  }

  return 0;
}

static int iTextSetChangeCaseAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  int case_flag = -1;

  if (iupStrEqualNoCase(value, "UPPER" ))
    case_flag = IUP_CASE_UPPER;
  else if (iupStrEqualNoCase(value, "LOWER" ))
    case_flag = IUP_CASE_LOWER;
  else if (iupStrEqualNoCase(value, "TOGGLE" ))
    case_flag = IUP_CASE_TOGGLE;
  else if (iupStrEqualNoCase(value, "TITLE" ))
    case_flag = IUP_CASE_TITLE;

  if (case_flag != -1)
  {
    int utf8 = amy_IupGetInt( data, NULL, "UTF8MODE" );
    char *str = amy_IupGetAttribute( data, ih, "VALUE" );
    iupStrChangeCase(str, str, case_flag, utf8 );
    amy_IupSetStrAttribute( data, ih, "VALUE", str );
  }

  return 0;
}

static int iTextSetMultilineAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  /* valid only before map */
  if (ih->handle)
    return 0;

  if (iupStrBoolean(value))
  {
    ih->data->is_multiline = 1;
    ih->data->sb = IUP_SB_HORIZ | IUP_SB_VERT;  /* reset SCROLLBAR to YES */
    iupAttribSet( data, ih, "_IUP_MULTILINE_TEXT", "1" );
  }
  else
  {
    ih->data->is_multiline = 0;
    iupAttribSet( data, ih, "_IUP_MULTILINE_TEXT", NULL );
  }

  return 0;
}

static char *iTextGetMultilineAttrib( struct libData *data, Ihandle *ih )
{
  return iupStrReturnBoolean( ih->data->is_multiline ); 
}

static int iTextSetAppendNewlineAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if (iupStrBoolean(value))
    ih->data->append_newline = 1;
  else
    ih->data->append_newline = 0;
  return 0;
}

static char *iTextGetAppendNewlineAttrib( struct libData *data, Ihandle *ih )
{
  return iupStrReturnBoolean( ih->data->append_newline ); 
}

static int iTextSetScrollbarAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  /* valid only before map */
  if (ih->handle || !ih->data->is_multiline)
    return 0;

  if ( ! value)
    value = "YES";    /* default, if multiline, is YES */

  if (iupStrEqualNoCase(value, "YES" ))
    ih->data->sb = IUP_SB_HORIZ | IUP_SB_VERT;
  else if (iupStrEqualNoCase(value, "HORIZONTAL" ))
    ih->data->sb = IUP_SB_HORIZ;
  else if (iupStrEqualNoCase(value, "VERTICAL" ))
    ih->data->sb = IUP_SB_VERT;
  else
    ih->data->sb = IUP_SB_NONE;

  return 0;
}

static char *iTextGetScrollbarAttrib( struct libData *data, Ihandle *ih )
{
  if ( ! ih->data->is_multiline)
    return NULL;
  if (ih->data->sb == (IUP_SB_HORIZ | IUP_SB_VERT))
    return "YES";
  if (ih->data->sb & IUP_SB_HORIZ)
    return "HORIZONTAL";
  if (ih->data->sb & IUP_SB_VERT)
    return "VERTICAL";
  return "NO";   /* IUP_SB_NONE */
}

char *iupTextGetPaddingAttrib( struct libData *data, Ihandle *ih )
{
  return iupStrReturnIntInt(ih->data->horiz_padding, ih->data->vert_padding, 'x' );
}


/********************************************************************/


static int iTextCreateMethod( struct libData *data, Ihandle *ih, void** params)
{
  if (params)
  {
    if (params[0] ) iupAttribSetStr( data, ih, "ACTION", (char*)(params[0] ));
  }
  ih->data = iupALLOCCTRLDATA();
  ih->data->append_newline = 1;
  return IUP_NOERROR;
}

static int iMultilineCreateMethod( struct libData *data, Ihandle *ih, void** params)
{
  (void)params;
  ih->data->is_multiline = 1;
  ih->data->sb = IUP_SB_HORIZ | IUP_SB_VERT;  /* default is YES */
  iupAttribSet( data, ih, "_IUP_MULTILINE_TEXT", "1" );
  return IUP_NOERROR;
}

static void iTextComputeNaturalSizeMethod( struct libData *data, Ihandle *ih, int *w, int *h, int *children_expand)
{
  int natural_w = 0, 
      natural_h = 0,
      visiblecolumns = iupAttribGetInt( data, ih, "VISIBLECOLUMNS" ),
      visiblelines = iupAttribGetInt( data, ih, "VISIBLELINES" );
  (void)children_expand; /* unset if not a container */

  /* Since the contents can be changed by the user, the size can not be dependent on it. */
  iupdrvFontGetCharSize( data, ih, NULL, &natural_h );  /* one line height */
  natural_w = iupdrvFontGetStringWidth( data, ih, "WWWWWWWWWW" );
  natural_w = (visiblecolumns*natural_w)/10;
  if (ih->data->is_multiline)
    natural_h = visiblelines*natural_h;

  /* compute the borders space */
  if (iupAttribGetBoolean( data, ih, "BORDER" ))
    iupdrvTextAddBorders( data, ih, &natural_w, &natural_h );

  if (iupAttribGetBoolean( data, ih, "SPIN" ))
    iupdrvTextAddSpin( data, ih, &natural_w, natural_h );

  natural_w += 2*ih->data->horiz_padding;
  natural_h += 2*ih->data->vert_padding;

  /* add scrollbar */
  if (ih->data->is_multiline && ih->data->sb)
  {
    int sb_size = iupdrvGetScrollbarSize( data );
    if (ih->data->sb & IUP_SB_HORIZ)
      natural_h += sb_size;  /* sb horizontal affects vertical size */
    if (ih->data->sb & IUP_SB_VERT)
      natural_w += sb_size;  /* sb vertical affects horizontal size */
  }

  *w = natural_w;
  *h = natural_h;
}

static void iTextDestroyMethod( struct libData *data, Ihandle *ih )
{
  if (ih->data->formattags)
    iTextDestroyFormatTags( data, ih );
  if (ih->data->mask)
    iupMaskDestroy( data, ih->data->mask );
}


/******************************************************************************/

typedef void (*Iconvertlincol2pos)( struct libData *data, Ihandle *ih, int lin, int col, int *pos );
typedef void (*Iconvertpos2lincol)( struct libData *data, Ihandle *ih, int pos, int *lin, int *col );

IUP_API void amy_IupTextConvertLinColToPos( struct libData *data, Ihandle *ih, int lin, int col, int *pos)
{
  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return;

  if ( ! ih->handle)
    return;
    
  if ( amy_IupClassMatch( data, ih, "text" ))
  {
    if (ih->data->is_multiline)
      iupdrvTextConvertLinColToPos( data, ih, lin, col, pos );
    else
      *pos = col - 1; /* IUP starts at 1 */
  }
  else 
  {
    Iconvertlincol2pos convert = (Iconvertlincol2pos) amy_IupGetCallback( data, ih, "_IUP_LINCOL2POS_CB" );
    if (convert)
      convert( data, ih, lin, col, pos );
  }
}

IUP_API void amy_IupTextConvertPosToLinCol( struct libData *data, Ihandle *ih, int pos, int *lin, int *col)
{
  iupASSERT(iupObjectCheck( data, ih ));
  if ( ! iupObjectCheck( data, ih ))
    return;

  if ( ! ih->handle)
    return;
    
  if ( amy_IupClassMatch( data, ih, "text" ))
  {
    if (ih->data->is_multiline)
      iupdrvTextConvertPosToLinCol( data, ih, pos, lin, col );
    else
    {
      *col = pos + 1; /* IUP starts at 1 */
      *lin = 1;
    }
  }
  else 
  {
    Iconvertpos2lincol convert = (Iconvertpos2lincol) amy_IupGetCallback( data, ih, "_IUP_POS2LINCOL_CB" );
    if (convert)
      convert( data, ih, pos, lin, col );
  }
}

IUP_API Ihandle *amy_IupText( struct libData *data, const char *action )
{
  void *params[2];
  params[0] = (void*)action;
  params[1] = NULL;
  return amy_IupCreatev( data, "text", params );
}

Iclass *iupTextNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, NULL );

  ic->name = "text";
  ic->format = "a"; /* one ACTION callback name */
  ic->nativetype = IUP_TYPECONTROL;
  ic->childtype = IUP_CHILDNONE;
  ic->is_interactive = 1;

  /* Class functions */
  ic->New = iupTextNewClass;
  ic->Create = iTextCreateMethod;
  ic->Destroy = iTextDestroyMethod;
  ic->ComputeNaturalSize = iTextComputeNaturalSizeMethod;
  ic->LayoutUpdate = iupdrvBaseLayoutUpdateMethod;
  ic->UnMap = iupdrvBaseUnMapMethod;

  /* Callbacks */
  iupClassRegisterCallback( data, ic, "CARET_CB", "iii" );
  iupClassRegisterCallback( data, ic, "ACTION", "is" );
  iupClassRegisterCallback( data, ic, "BUTTON_CB", "iiiis" );
  iupClassRegisterCallback( data, ic, "MOTION_CB", "iis" );
  iupClassRegisterCallback( data, ic, "SPIN_CB", "i" );
  iupClassRegisterCallback( data, ic, "VALUECHANGED_CB", "" );

  /* Common Callbacks */
  iupBaseRegisterCommonCallbacks( data, ic );

  /* Common */
  iupBaseRegisterCommonAttrib( data, ic );

  /* Visual */
  iupBaseRegisterVisualAttrib( data, ic );

  /* Drag&Drop */
  iupdrvRegisterDragDropAttrib( data, ic );

  /* amy_IupText only */
  iupClassRegisterAttribute( data, ic, "SCROLLBAR", iTextGetScrollbarAttrib, iTextSetScrollbarAttrib, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "AUTOHIDE", NULL, NULL, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MULTILINE", iTextGetMultilineAttrib, iTextSetMultilineAttrib, NULL, NULL, IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "APPENDNEWLINE", iTextGetAppendNewlineAttrib, iTextSetAppendNewlineAttrib, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CPADDING", iupBaseGetCPaddingAttrib, iupBaseSetCPaddingAttrib, NULL, NULL, IUPAF_NO_SAVE | IUPAF_NOT_MAPPED );

  iupClassRegisterAttribute( data, ic, "VALUEMASKED", NULL, iTextSetValueMaskedAttrib, NULL, NULL, IUPAF_WRITEONLY|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MASKCASEI", NULL, iTextSetMaskCaseIAttrib, NULL, NULL, IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MASKDECIMALSYMBOL", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MASK", iTextGetMaskAttrib, iTextSetMaskAttrib, NULL, NULL, IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MASKINT", NULL, iTextSetMaskIntAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MASKFLOAT", NULL, iTextSetMaskFloatAttrib, NULL, NULL, IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MASKREAL", NULL, iTextSetMaskRealAttrib, NULL, NULL, IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MASKNOEMPTY", NULL, iTextSetMaskNoEmptyAttrib, NULL, NULL, IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "BORDER", NULL, NULL, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "SPIN", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "SPINALIGN", NULL, NULL, IUPAF_SAMEASSYSTEM, "RIGHT", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "SPINAUTO", NULL, NULL, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "SPINWRAP", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "VISIBLECOLUMNS", NULL, NULL, IUPAF_SAMEASSYSTEM, "5", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "VISIBLELINES", NULL, NULL, IUPAF_SAMEASSYSTEM, "1", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "WORDWRAP", NULL, NULL, NULL, NULL, IUPAF_DEFAULT );
  iupClassRegisterAttribute( data, ic, "CHANGECASE", NULL, iTextSetChangeCaseAttrib, NULL, NULL, IUPAF_WRITEONLY | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );

  iupdrvTextInitClass( data, ic );

  return ic;
}

IUP_API Ihandle *amy_IupMultiLine( struct libData *data, const char *action )
{
  void *params[2];
  params[0] = (void*)action;
  params[1] = NULL;
  return amy_IupCreatev( data, "multiline", params );
}

Iclass *iupMultilineNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, iupRegisterFindClass( data, "text" ));

  ic->name = "multiline";   /* register the multiline name, so LED will work */
  ic->cons = "MultiLine";
  ic->format = "a"; /* one ACTION callback name */
  ic->nativetype = IUP_TYPECONTROL;
  ic->childtype = IUP_CHILDNONE;
  ic->is_interactive = 1;

  ic->Create = iMultilineCreateMethod;

  return ic;
}
