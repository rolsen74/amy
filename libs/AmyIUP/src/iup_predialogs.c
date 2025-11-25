
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
 * \brief pre-defined dialogs
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdarg.h>
#include <time.h>

#include "iup.h" 

#include "iup_predialogs.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_strmessage.h"
               
#endif

static int CB_button_OK( struct libData *data, Ihandle *ih )
{
  iupAttribSet( data, amy_IupGetDialog( data, ih ), "STATUS", "1" );
  return IUP_CLOSE;
}

static int CB_button_CANCEL( struct libData *data, Ihandle *ih )
{
  iupAttribSet( data, amy_IupGetDialog( data, ih ), "STATUS", "-1" );
  return IUP_CLOSE;
}

static int CB_dblclick( struct libData *data, Ihandle *ih, int item, char *text )
{
  (void)text;
  iupAttribSetInt( data, amy_IupGetDialog( data, ih ), "_IUP_LIST_NUMBER", item-1 );
  iupAttribSet( data, amy_IupGetDialog( data, ih ), "STATUS", "1" );
  return IUP_CLOSE;
}

static int CB_list(  struct libData *data, Ihandle *ih, char *text, int item, int state )
{
  (void)text;
  if (state)
    iupAttribSetInt( data, amy_IupGetDialog( data, ih ), "_IUP_LIST_NUMBER", item-1 );
  return IUP_DEFAULT;
}

IUP_API int amy_IupListDialog( struct libData *data,
	int type, const char *title, int size, const char **list_str,
	int op, int max_col, int max_lin, int *marks )
{
  Ihandle *lst, *ok, *dlg, *cancel, *dlg_box, *button_box;
  int i, bt;
  char *m=NULL;

  lst = amy_IupList( data, NULL );

  for (i=0;i<size;i++)
    amy_IupSetAttributeId( data, lst,"",i+1,list_str[i] );
  amy_IupSetAttributeId( data, lst,"",i+1,NULL );
  amy_IupSetAttribute( data, lst,"EXPAND","YES" );

  ok = amy_IupButton( data, "_@IUP_OK", NULL );
  amy_IupSetStrAttribute( data, ok, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
  amy_IupSetCallback( data, ok, "ACTION", (Icallback)CB_button_OK );

  cancel = amy_IupButton( data, "_@IUP_CANCEL", NULL );
  amy_IupSetStrAttribute( data, cancel, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
  amy_IupSetCallback( data, cancel, "ACTION", (Icallback)CB_button_CANCEL );

  button_box = amy_IupHbox( data,
    amy_IupFill( data ), 
    ok,
    cancel,
    NULL );
  amy_IupSetAttribute( data, button_box,"MARGIN","0x0" );
  amy_IupSetAttribute( data, button_box, "NORMALIZESIZE", "HORIZONTAL" );

  dlg_box = amy_IupVbox( data,
    lst,
    button_box,
    NULL );

  amy_IupSetAttribute( data, dlg_box,"MARGIN","10x10" );
  amy_IupSetAttribute( data, dlg_box,"GAP","10" );

  dlg = amy_IupDialog( data, dlg_box );

  if (type == 1)
  {
    if (op<1 || op>size) op=1;
    iupAttribSetInt( data, dlg, "_IUP_LIST_NUMBER", op-1 );
    amy_IupSetInt( data, lst,"VALUE",op );
    amy_IupSetCallback( data, lst, "ACTION", (Icallback)CB_list );
    amy_IupSetCallback( data, lst, "DBLCLICK_CB", (Icallback)CB_dblclick );
  }
  else if ((type == 2) && (marks != NULL))
  {
    m=(char *)marks;
    for (i=0;i<size;i++)
      m[i] = marks[i] ? '+' : '-';
    m[i]='\0';
    amy_IupSetAttribute( data, lst,"MULTIPLE","YES" );
    amy_IupSetAttribute( data, lst,"VALUE",m );
  }

  if (max_lin < 4) max_lin = 4;
  amy_IupSetInt( data, lst, "VISIBLELINES", max_lin );
  amy_IupSetInt( data, lst, "VISIBLECOLUMNS", max_col );

  amy_IupSetStrAttribute( data, dlg,"TITLE", title );
  amy_IupSetAttribute( data, dlg,"MINBOX","NO" );
  amy_IupSetAttribute( data, dlg,"MAXBOX","NO" );
  amy_IupSetAttributeHandle( data, dlg,"DEFAULTENTER", ok );
  amy_IupSetAttributeHandle( data, dlg,"DEFAULTESC", cancel );
  amy_IupSetAttribute( data, dlg,"PARENTDIALOG", amy_IupGetGlobal( data, "PARENTDIALOG" ));
  amy_IupSetAttribute( data, dlg,"ICON", amy_IupGetGlobal( data, "ICON" ));

  amy_IupPopup( data, dlg,IUP_CENTERPARENT,IUP_CENTERPARENT );

  if ((type == 2) && (marks != NULL))
  {
    m=amy_IupGetAttribute( data, lst, "VALUE" );
    for (i=0;i<size;i++)
      marks[i] = (m[i] == '+' );
  }

  bt = amy_IupGetInt( data, dlg, "STATUS" );
  if (type == 1)
  {
    if (bt == 1)
      bt = iupAttribGetInt( data, dlg, "_IUP_LIST_NUMBER" );
    else
      bt = -1;
  }
  else
  {
    if (bt != 1)
      bt = -1;
  }

  amy_IupDestroy( data, dlg );

  return bt;
}

static int iAlarmButtonAction_CB( struct libData *data, Ihandle *ih )
{
  iupAttribSet( data, amy_IupGetDialog( data, ih ), "_IUP_BUTTON_NUMBER", iupAttribGet( data, ih, "_IUP_BUTTON_NUMBER" ));
  return IUP_CLOSE;
}

IUP_API int amy_IupAlarm( struct libData *data, const char *title, const char *msg, const char *b1, const char *b2, const char *b3 )
{
  Ihandle  *dlg, *dlg_box, *button_box, *button, *default_esc, *default_enter;
  int bt;

  msg = msg? msg: "";

  if (b1 == NULL)
    return 0;

  button_box = amy_IupHbox( data, NULL );
  amy_IupSetAttribute( data, button_box, "NORMALIZESIZE", "HORIZONTAL" );
  amy_IupSetAttribute( data, button_box,"MARGIN","0x0" );
  amy_IupAppend( data, button_box, amy_IupFill( data )); /* to center the buttons */

  button = amy_IupButton( data, b1, NULL );
  iupAttribSet( data, button, "_IUP_BUTTON_NUMBER", "1" );
  amy_IupSetStrAttribute( data, button, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
  amy_IupAppend( data, button_box, button );
  amy_IupSetCallback( data, button, "ACTION", (Icallback)iAlarmButtonAction_CB );
  default_enter = button;
  default_esc = button;

  if (b2 != NULL)
  {
    button = amy_IupButton( data, b2, NULL );
    iupAttribSet( data, button, "_IUP_BUTTON_NUMBER", "2" );
    amy_IupSetStrAttribute( data, button, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
    amy_IupAppend( data, button_box, button );
    amy_IupSetCallback( data, button, "ACTION", (Icallback)iAlarmButtonAction_CB );
    default_esc = button;
  }

  if (b3 != NULL)
  {
    button = amy_IupButton( data, b3, NULL );
    iupAttribSet( data, button, "_IUP_BUTTON_NUMBER", "3" );
    amy_IupSetStrAttribute( data, button, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
    amy_IupAppend( data, button_box, button );
    amy_IupSetCallback( data, button, "ACTION", (Icallback)iAlarmButtonAction_CB );
    default_esc = button;
  }

  amy_IupAppend( data, button_box, amy_IupFill( data )); /* to center the buttons */

  dlg_box = amy_IupVbox( data,
    amy_IupLabel( data, msg ),
    amy_IupSetAttributes( data, amy_IupLabel( data, NULL ), "SEPARATOR=HORIZONTAL" ),
    button_box,
    NULL );

  amy_IupSetAttribute( data, dlg_box,"MARGIN","10x10" );
  amy_IupSetAttribute( data, dlg_box,"GAP","10" );

  dlg = amy_IupDialog( data, dlg_box );

  amy_IupSetStrAttribute( data, dlg,"TITLE", title );
  amy_IupSetAttribute( data, dlg,"DIALOGFRAME","YES" );
  amy_IupSetAttribute( data, dlg,"DIALOGHINT","YES" );
  amy_IupSetAttributeHandle( data, dlg,"DEFAULTENTER", default_enter );
  amy_IupSetAttributeHandle( data, dlg,"DEFAULTESC", default_esc );
  amy_IupSetAttribute( data, dlg,"PARENTDIALOG", amy_IupGetGlobal( data, "PARENTDIALOG" ));
  amy_IupSetAttribute( data, dlg,"ICON", amy_IupGetGlobal( data, "ICON" ));

  amy_IupPopup( data, dlg,IUP_CENTERPARENT,IUP_CENTERPARENT );

  bt = iupAttribGetInt( data, dlg, "_IUP_BUTTON_NUMBER" );

  amy_IupDestroy( data, dlg );

  return bt;
}

IUP_SDK_API int  iupDataEntry( struct libData *data, 
	int    maxlin,
    int*   maxcol,
    int*   maxscr,
    char * etitle,
    char** etext,
    char** edata)
{
  int i, bt;
  Ihandle *ok, *cancel, *dlg, *vb, *hb, **txt, **lbl, *button_box, *dlg_box;

  txt = (Ihandle **)calloc(maxlin, sizeof(Ihandle*));
  if (txt == NULL) return -2;
  lbl = (Ihandle **)calloc(maxlin+1, sizeof(Ihandle*));

  vb = amy_IupVbox( data, NULL );

  for (i=0; i<maxlin; i++)
  {
    txt[i] = amy_IupText( data, NULL );
    amy_IupSetAttribute( data, txt[i],"VALUE",edata[i] );
    amy_IupSetInt( data, txt[i],"VISIBLECOLUMNS", maxscr[i] );
    amy_IupSetInt( data, txt[i],"NC", maxcol[i] );
    amy_IupSetAttribute( data, txt[i],"EXPAND","HORIZONTAL" );

    hb = amy_IupHbox( data, lbl[i] = amy_IupLabel( data, etext[i] ), txt[i], NULL );
    amy_IupSetAttribute( data, hb,"MARGIN","0x0" );
    amy_IupSetAttribute( data, hb,"ALIGNMENT","ACENTER" );
    amy_IupAppend( data, vb, hb );
  }
  lbl[i] = NULL;
  amy_IupInsert( data, vb, NULL, amy_IupNormalizerv( data, lbl ));

  ok = amy_IupButton( data, "_@IUP_OK", NULL );
  amy_IupSetStrAttribute( data, ok, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
  amy_IupSetCallback( data, ok, "ACTION", (Icallback)CB_button_OK );

  cancel = amy_IupButton( data, "_@IUP_CANCEL", NULL );
  amy_IupSetStrAttribute( data, cancel, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
  amy_IupSetCallback( data, cancel, "ACTION", (Icallback)CB_button_CANCEL );

  button_box = amy_IupHbox( data,
    amy_IupFill( data ), 
    ok,
    cancel,
    NULL );
  amy_IupSetAttribute( data, button_box,"MARGIN","0x0" );
  amy_IupSetAttribute( data, button_box, "NORMALIZESIZE", "HORIZONTAL" );

  dlg_box = amy_IupVbox( data,
    amy_IupFrame( data, vb ),
    button_box,
    NULL );
  amy_IupSetAttribute( data, dlg_box,"MARGIN","10x10" );
  amy_IupSetAttribute( data, dlg_box,"GAP","5" );

  dlg = amy_IupDialog( data, dlg_box );

  amy_IupSetStrAttribute( data, dlg,"TITLE",etitle );
  amy_IupSetAttribute( data, dlg,"MINBOX","NO" );
  amy_IupSetAttribute( data, dlg,"MAXBOX","NO" );
  amy_IupSetAttributeHandle( data, dlg,"DEFAULTENTER", ok );
  amy_IupSetAttributeHandle( data, dlg,"DEFAULTESC", cancel );
  amy_IupSetAttribute( data, dlg,"PARENTDIALOG",amy_IupGetGlobal( data, "PARENTDIALOG" ));
  amy_IupSetAttribute( data, dlg,"ICON", amy_IupGetGlobal( data, "ICON" ));

  amy_IupMap( data, dlg );

  amy_IupSetfAttribute( data, dlg,"MAXSIZE", "65535x%d", amy_IupGetInt2( data, dlg, "RASTERSIZE" ));
  amy_IupSetAttribute( data, dlg,"MINSIZE", amy_IupGetAttribute( data, dlg, "RASTERSIZE" ));

  amy_IupPopup( data, dlg,IUP_CENTERPARENT,IUP_CENTERPARENT );

  for (i=0; i<maxlin; i++)
  {
    iupStrCopyN(edata[i], maxcol[i]+1, amy_IupGetAttribute( data, txt[i], "VALUE" ));
  }

  free(lbl );
  free(txt );

  bt = amy_IupGetInt( data, dlg, "STATUS" );
  amy_IupDestroy( data, dlg );
  return bt;
}

IUP_API int amy_IupGetFile( struct libData *data, char *filename )
{
  Ihandle *dlg = 0;
  int ret;
  char filter[4096] = "*.*";
  static char dir[4096] = "";  /* static will make the dir persist from one call to another if not defined */

  if ( ! filename) return -1;

  dlg = amy_IupFileDlg( data );

  iupStrFileNameSplit(filename, dir, filter );

  amy_IupSetAttribute( data, dlg, "FILTER", filter );
  amy_IupSetAttribute( data, dlg, "DIRECTORY", dir );
  amy_IupSetAttribute( data, dlg, "ALLOWNEW", "YES" );
  amy_IupSetAttribute( data, dlg, "NOCHANGEDIR", "YES" );
  amy_IupSetAttribute( data, dlg, "PARENTDIALOG", amy_IupGetGlobal( data, "PARENTDIALOG" ));
  amy_IupSetAttribute( data, dlg, "ICON", amy_IupGetGlobal( data, "ICON" ));

  amy_IupPopup( data, dlg, IUP_CENTERPARENT, IUP_CENTERPARENT );

  ret = amy_IupGetInt( data, dlg, "STATUS" );
  if (ret != -1)
  {
    char *value = amy_IupGetAttribute( data, dlg, "VALUE" );
    if (value) 
    {
      iupStrCopyN(filename, 4096, value );
      iupStrFileNameSplit(filename, dir, NULL );
    }
  }

  amy_IupDestroy( data, dlg );

  return ret;
}

IUP_API int amy_IupGetText( struct libData *data, const char *title, char *text, int maxsize )
{
  Ihandle *ok, *cancel = NULL, *multi_text, *button_box, *dlg_box, *dlg;
  int bt;

  if (maxsize == 0)
    maxsize = (int)strlen(text );

  multi_text = amy_IupMultiLine( data, NULL );
  amy_IupSetAttribute( data, multi_text,"EXPAND", "YES" );
  amy_IupSetAttribute( data, multi_text,"VALUE", text );
  amy_IupSetAttribute( data, multi_text,"FONT", "Courier, 12" );
  amy_IupSetAttribute( data, multi_text, "VISIBLELINES", "10" );
  amy_IupSetAttribute( data, multi_text, "VISIBLECOLUMNS", "50" );
  if (maxsize <= 0) amy_IupSetAttribute( data, multi_text, "READONLY", "YES" );

  ok = amy_IupButton( data, "_@IUP_OK", NULL );
  amy_IupSetStrAttribute( data, ok, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
  amy_IupSetCallback( data, ok, "ACTION", (Icallback)CB_button_OK );

  if (maxsize > 0)
  {
    cancel = amy_IupButton( data, "_@IUP_CANCEL", NULL );
    amy_IupSetStrAttribute( data, cancel, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
    amy_IupSetCallback( data, cancel, "ACTION", (Icallback)CB_button_CANCEL );
  }

  button_box = amy_IupHbox( data,
    amy_IupFill( data ),
    ok,
    cancel,
    NULL );
  amy_IupSetAttribute( data, button_box,"MARGIN","0x0" );
  amy_IupSetAttribute( data, button_box, "NORMALIZESIZE", "HORIZONTAL" );

  dlg_box = amy_IupVbox( data, multi_text, button_box, NULL );

  amy_IupSetAttribute( data, dlg_box,"MARGIN","10x10" );
  amy_IupSetAttribute( data, dlg_box,"GAP","10" );

  dlg = amy_IupDialog ( data, dlg_box );

  amy_IupSetStrAttribute( data, dlg,"TITLE", title );
  amy_IupSetAttribute( data, dlg,"MINBOX","NO" );
  amy_IupSetAttribute( data, dlg,"MAXBOX","NO" );
  amy_IupSetAttributeHandle( data, dlg,"DEFAULTENTER", ok );
  if (cancel) amy_IupSetAttributeHandle( data, dlg,"DEFAULTESC", cancel );
  else amy_IupSetAttributeHandle( data, dlg, "DEFAULTESC", ok );
  amy_IupSetAttribute( data, dlg,"PARENTDIALOG", amy_IupGetGlobal( data, "PARENTDIALOG" ));
  amy_IupSetAttribute( data, dlg,"ICON", amy_IupGetGlobal( data, "ICON" ));

  amy_IupMap( data, dlg );

  amy_IupSetAttribute( data, multi_text, "VISIBLELINES", NULL );
  amy_IupSetAttribute( data, multi_text, "VISIBLECOLUMNS", NULL );

  amy_IupPopup( data, dlg, IUP_CENTERPARENT, IUP_CENTERPARENT );

  bt = amy_IupGetInt( data, dlg, "STATUS" );
  if (bt==1 && maxsize > 0)
    iupStrCopyN(text, maxsize, amy_IupGetAttribute( data, multi_text, "VALUE" ));
  else
    bt = 0; /* return 0 instead of -1 */

  amy_IupDestroy( data, dlg );
  return bt;
}

IUP_API int amy_IupGetColor( struct libData *data, int x, int y, unsigned char *r, unsigned char *g, unsigned char *b )
{
  int ret;
  Ihandle *dlg = amy_IupColorDlg( data );

  amy_IupSetStrAttribute( data, dlg, "TITLE",  "_@IUP_GETCOLOR" );
  amy_IupSetfAttribute( data, dlg, "VALUE", "%d %d %d", *r, *g, *b );
  amy_IupSetAttribute( data, dlg, "PARENTDIALOG", amy_IupGetGlobal( data, "PARENTDIALOG" ));
  amy_IupSetAttribute( data, dlg, "ICON", amy_IupGetGlobal( data, "ICON" ));

  amy_IupPopup( data, dlg, x, y );

  ret = amy_IupGetInt( data, dlg, "STATUS" );
  if (ret)
    iupStrToRGB( amy_IupGetAttribute( data, dlg, "VALUE" ), r, g, b );

  amy_IupDestroy( data, dlg );

  return ret;
}

