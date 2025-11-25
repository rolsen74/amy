
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#define _IUPDLG_PRIVATE
#include "inc/All.h"
#include "inc/iup_dialog.h"

// --

#if 0

/** \file
 * \brief DatePick Control
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <memory.h>
#include <stdarg.h>
#include <limits.h>
#include <time.h>

#include "iup.h"
#include "iupcbs.h"

#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_drv.h"
#include "iup_drvfont.h"
#include "iup_register.h"
#include "iup_childtree.h"

#endif

static int is_leap_year(int year)
{
  if (year % 400 == 0)
    return 1;
  else if (year % 100 == 0)
    return 0;
  else if (year % 4 == 0)
    return 1;
  else
    return 0;
}

static void iDatePickUpdateDayLimits( struct libData *data, Ihandle *ih )
{
  Ihandle *txt_month = (Ihandle *) iupAttribGet( data, ih, "_IUP_DATE_MONTH");
  Ihandle *txt_day = (Ihandle *) iupAttribGet( data, ih, "_IUP_DATE_DAY");
  int day = amy_IupGetInt( data, txt_day, "VALUE");
  int month = amy_IupGetInt( data, txt_month, "VALUE");
  if (month == 2)
  {
    Ihandle *txt_year = (Ihandle *) iupAttribGet( data, ih, "_IUP_DATE_YEAR");
    int year = amy_IupGetInt( data, txt_year, "VALUE");
    if (is_leap_year(year))
    {
      amy_IupSetAttribute( data, txt_day, "MASKINT", "1:29");
      if (day > 29)
        amy_IupSetInt( data, txt_day, "VALUE", 29);
    }
    else
    {
      amy_IupSetAttribute( data, txt_day, "MASKINT", "1:28");
      if (day > 28)
        amy_IupSetInt( data, txt_day, "VALUE", 28);
    }
  }
  else if (month == 4 || month == 6 || month == 9 || month == 11)
  {
    amy_IupSetAttribute( data, txt_day, "MASKINT", "1:30");
    if (day > 30)
      amy_IupSetInt( data, txt_day, "VALUE", 30);
  }
  else
    amy_IupSetAttribute( data, txt_day, "MASKINT", "1:31");
}

static int iDatePickCalendarValueChanged_CB( struct libData *data, Ihandle *ih_calendar )
{
  Ihandle *ih = (Ihandle *) iupAttribGet( data, ih_calendar, "_IUP_DATEPICK");

  amy_IupSetStrAttribute( data, ih, "VALUE", amy_IupGetAttribute( data, ih_calendar, "VALUE"));

  iupBaseCallValueChangedCb( data, ih );
  return IUP_DEFAULT;
}

static int iDatePickCalendarKillFocus_CB( struct libData *data, Ihandle *ih_calendar)
{
  Ihandle *ih_toggle = (Ihandle *) iupAttribGet( data, ih_calendar, "_IUP_DATEPICK_TOGGLE");
  if (!iupAttribGet( data, ih_toggle, "_IUP_DATEPICK_INSIDETOGGLE"))
    amy_IupSetAttribute( data, ih_toggle, "VALUE", "OFF");
  amy_IupHide( data, amy_IupGetDialog( data, ih_calendar));
  return IUP_DEFAULT;
}

static int iDatePickToggleEnterWindow_CB( struct libData *data, Ihandle *ih_toggle)
{
  iupAttribSet( data, ih_toggle, "_IUP_DATEPICK_INSIDETOGGLE", "1");
  return IUP_DEFAULT;
}

static int iDatePickToggleLeaveWindow_CB( struct libData *data, Ihandle *ih_toggle)
{
  iupAttribSet( data, ih_toggle, "_IUP_DATEPICK_INSIDETOGGLE", NULL);
  return IUP_DEFAULT;
}

static int iDatePickToggleAction_CB( struct libData *data, Ihandle *ih_toggle, int state)
{
  Ihandle *ih = amy_IupGetParent( data, amy_IupGetParent( data, ih_toggle));
  Ihandle *calendar = (Ihandle *) iupAttribGet( data, ih, "_IUP_CALENDAR");

  if (state == 1)
  {
    int x, y;

    if (!calendar)
    {
      Ihandle *dlg;
      char* weeknumbers;

      calendar = amy_IupCalendar( data );
      weeknumbers = iupAttribGet( data, ih, "CALENDARWEEKNUMBERS");
      if (weeknumbers) amy_IupSetStrAttribute( data, calendar, "WEEKNUMBERS", weeknumbers);
      amy_IupSetCallback( data, calendar, "VALUECHANGED_CB", iDatePickCalendarValueChanged_CB);
      amy_IupSetCallback( data, calendar, "KILLFOCUS_CB", iDatePickCalendarKillFocus_CB);
      iupAttribSet( data, calendar, "_IUP_DATEPICK", (char*)ih);
      iupAttribSet( data, calendar, "_IUP_DATEPICK_TOGGLE", (char*)ih_toggle);
      iupAttribSet( data, ih, "_IUP_CALENDAR", (char*)calendar);

      dlg = amy_IupDialog( data, calendar);
      amy_IupSetAttribute( data, dlg, "BORDER", "NO");
      amy_IupSetAttribute( data, dlg, "MENUBOX", "NO");
      amy_IupSetAttribute( data, dlg, "MAXBOX", "NO");
      amy_IupSetAttribute( data, dlg, "MINBOX", "NO");
      amy_IupSetAttribute( data, dlg, "RESIZE", "NO");
    }

    amy_IupSetStrAttribute( data, calendar, "VALUE", amy_IupGetAttribute( data, ih, "VALUE"));

    x = amy_IupGetInt( data, ih, "X");
    y = amy_IupGetInt( data, ih, "Y");
    y += amy_IupGetInt2( data, ih, "RASTERSIZE");

    amy_IupShowXY( data, amy_IupGetDialog( data, calendar), x, y);
    amy_IupSetFocus( data, calendar );
  }
  else
  {
    if (calendar)
      amy_IupHide( data, amy_IupGetDialog( data, calendar ));
  }

  return IUP_DEFAULT;
}

static int iDatePickTextValueChanged_CB( struct libData *data, Ihandle *ih_text )
{
  Ihandle *ih = amy_IupGetParent( data, amy_IupGetParent( data, ih_text ));

  if ((Ihandle *) iupAttribGet( data, ih, "_IUP_DATE_DAY") != ih_text)
    iDatePickUpdateDayLimits( data, ih );

  iupBaseCallValueChangedCb( data, ih );
  return IUP_DEFAULT;
}

static int iDatePickTextKAny_CB( struct libData *data, Ihandle *ih_text, int key )
{
  if (key == K_UP || key == K_plus || key == K_sPlus)
  {
    int value = amy_IupGetInt( data, ih_text, "VALUE");
    value++;
    if (iupAttribGetBoolean( data, ih_text, "ZEROPRECED"))
      amy_IupSetStrf( data, ih_text, "VALUEMASKED", "%02d", value);
    else
      amy_IupSetInt( data, ih_text, "VALUEMASKED", value);

    if ( amy_IupGetInt( data, ih_text, "VALUE") == value)
      iDatePickTextValueChanged_CB( data, ih_text);
    return IUP_IGNORE;
  }
  else if (key == K_DOWN || key == K_minus || key == K_sMinus)
  {
    int value = amy_IupGetInt( data, ih_text, "VALUE");
    value--;
    if (iupAttribGetBoolean( data, ih_text, "ZEROPRECED"))
      amy_IupSetStrf( data, ih_text, "VALUEMASKED", "%02d", value);
    else
      amy_IupSetInt( data, ih_text, "VALUEMASKED", value);

    if ( amy_IupGetInt( data, ih_text, "VALUE") == value)
      iDatePickTextValueChanged_CB( data, ih_text);
    return IUP_IGNORE;
  }
  else if (key == K_LEFT)
  {
    int caret = amy_IupGetInt( data, ih_text, "CARET");
    if (caret == 1)
    {
      int pos = amy_IupGetChildPos( data, amy_IupGetParent( data, ih_text), ih_text);
      if (pos == 2)
      {
        Ihandle *next = amy_IupGetChild( data, amy_IupGetParent( data, ih_text), 0);
        int count = amy_IupGetInt( data, next, "COUNT");
        amy_IupSetFocus( data, next);
        amy_IupSetInt( data, next, "CARET", count + 1);
      }
      else if (pos == 4)
      {
        Ihandle *next = amy_IupGetChild( data, amy_IupGetParent( data, ih_text), 2);
        int count = amy_IupGetInt( data, next, "COUNT");
        amy_IupSetFocus( data, next);
        amy_IupSetInt( data, next, "CARET", count + 1);
      }
    }
  }
  else if (key == K_RIGHT)
  {
    int caret = amy_IupGetInt( data, ih_text, "CARET");
    int count = amy_IupGetInt( data, ih_text, "COUNT");
    if (caret == count + 1)
    {
      int pos = amy_IupGetChildPos( data, amy_IupGetParent( data, ih_text), ih_text);
      if (pos == 0)
      {
        Ihandle *next = amy_IupGetChild( data, amy_IupGetParent( data, ih_text), 2);
        amy_IupSetFocus( data, next);
        amy_IupSetInt( data, next, "CARET", 1);
      }
      else if (pos == 2)
      {
        Ihandle *next = amy_IupGetChild( data, amy_IupGetParent( data, ih_text), 4);
        amy_IupSetFocus( data, next);
        amy_IupSetInt( data, next, "CARET", 1);
      }
    }
  }
  return IUP_CONTINUE;
}


/*********************************************************************************************/


static int iDatePickSetShowDropdownAttrib( struct libData *data, Ihandle *ih, const char* value)
{
  iDatePickToggleAction_CB( data, ih, iupStrBoolean(value));
  return 0;
}

static int iDatePickSetValueAttrib( struct libData *data, Ihandle *ih, const char* value)
{
  if (iupStrEqualNoCase(value, "TODAY"))
  {
    Ihandle *txt_year = (Ihandle *) iupAttribGet( data, ih, "_IUP_DATE_YEAR");
    Ihandle *txt_month = (Ihandle *) iupAttribGet( data, ih, "_IUP_DATE_MONTH");
    Ihandle *txt_day = (Ihandle *) iupAttribGet( data, ih, "_IUP_DATE_DAY");
    struct tm * timeinfo;
    time_t timer;
    time(&timer);
    timeinfo = localtime(&timer);

    if (iupAttribGetBoolean( data, ih, "ZEROPRECED"))
    {
      amy_IupSetInt( data, txt_year, "VALUE", timeinfo->tm_year + 1900);
      amy_IupSetStrf( data, txt_month, "VALUE", "%02d", timeinfo->tm_mon + 1);
      amy_IupSetStrf( data, txt_day, "VALUE", "%02d", timeinfo->tm_mday);
    }
    else
    {
      amy_IupSetInt( data, txt_year, "VALUE", timeinfo->tm_year + 1900);
      amy_IupSetInt( data, txt_month, "VALUE", timeinfo->tm_mon + 1);
      amy_IupSetInt( data, txt_day, "VALUE", timeinfo->tm_mday);
    }

    iDatePickUpdateDayLimits( data, ih );
  }
  else
  {
    int year, month, day;
    if (sscanf(value, "%d/%d/%d", &year, &month, &day) == 3)
    {
      Ihandle *txt_year = (Ihandle *) iupAttribGet( data, ih, "_IUP_DATE_YEAR");
      Ihandle *txt_month = (Ihandle *) iupAttribGet( data, ih, "_IUP_DATE_MONTH");
      Ihandle *txt_day = (Ihandle *) iupAttribGet( data, ih, "_IUP_DATE_DAY");

      if (month < 1) month = 1;
      if (month > 12) month = 12;

      amy_IupSetInt( data, txt_year, "VALUE", year);
      if (iupAttribGetBoolean( data, ih, "ZEROPRECED"))
        amy_IupSetStrf( data, txt_month, "VALUE", "%02d", month);
      else
       amy_IupSetInt( data, txt_month, "VALUE", month);

      iDatePickUpdateDayLimits( data, ih );

      if (iupAttribGetBoolean( data, ih, "ZEROPRECED"))
        amy_IupSetStrf( data, txt_day, "VALUEMASKED", "%02d", day);
      else
        amy_IupSetInt( data, txt_day, "VALUEMASKED", day);
    }
  }
  return 0; /* do not store value in hash table */
}

static char* iDatePickGetValueAttrib( struct libData *data, Ihandle *ih )
{
  Ihandle *txt_year = (Ihandle *) iupAttribGet( data, ih, "_IUP_DATE_YEAR");
  int year = amy_IupGetInt( data, txt_year, "VALUE");

  Ihandle *txt_month = (Ihandle *) iupAttribGet( data, ih, "_IUP_DATE_MONTH");
  int month = amy_IupGetInt( data, txt_month, "VALUE");

  Ihandle *txt_day = (Ihandle *) iupAttribGet( data, ih, "_IUP_DATE_DAY");
  int day = amy_IupGetInt( data, txt_day, "VALUE");

  return iupStrReturnStrf("%d/%d/%d", year, month, day);
}

static int iDatePickSetSeparatorAttrib( struct libData *data, Ihandle *ih, const char* value)
{
  Ihandle *lbl = amy_IupGetChild( data, ih->firstchild, 1);
  amy_IupSetStrAttribute( data, lbl, "TITLE", value);
  lbl = amy_IupGetChild( data, ih->firstchild, 3);
  amy_IupSetStrAttribute( data, lbl, "TITLE", value);
  return 1;
}

static void iDatePickSetDayTextBox( struct libData *data, Ihandle *ih, int pos)
{
  Ihandle *txt = amy_IupGetChild( data, ih->firstchild, pos);
  amy_IupSetAttribute( data, txt, "MASKINT", "1:31");
  amy_IupSetAttribute( data, txt, "MASKNOEMPTY", "Yes");
  amy_IupSetAttribute( data, txt, "NC", "2");
  amy_IupSetAttribute( data, txt, "SIZE", "14x");

  iupAttribSet( data, ih, "_IUP_DATE_DAY", (char*)txt);
}

static void iDatePickSetMonthTextBox( struct libData *data, Ihandle *ih, int pos)
{
  Ihandle *txt = amy_IupGetChild( data, ih->firstchild, pos);

  amy_IupSetAttribute( data, txt, "MASKINT", "1:12");
  amy_IupSetAttribute( data, txt, "MASKNOEMPTY", "Yes");
  amy_IupSetAttribute( data, txt, "NC", "2");
  amy_IupSetAttribute( data, txt, "SIZE", "14x");

  iupAttribSet( data, ih, "_IUP_DATE_MONTH", (char*)txt);
}

static void iDatePickSetYearTextBox( struct libData *data, Ihandle *ih, int pos)
{
  Ihandle *txt = amy_IupGetChild( data, ih->firstchild, pos);
  amy_IupSetAttribute( data, txt, "MASK", IUP_MASK_UINT);
  amy_IupSetAttribute( data, txt, "MASKNOEMPTY", "Yes");
  amy_IupSetAttribute( data, txt, "NC", "4");
  amy_IupSetAttribute( data, txt, "SIZE", "26x");

  iupAttribSet( data, ih, "_IUP_DATE_YEAR", (char*)txt);
}

static int iDatePickSetOrderAttrib( struct libData *data, Ihandle *ih, const char* value)
{
  int i;

  if (!value || strlen(value) != 3)
    return 0;

  for (i = 0; i < 3; i++)
  {
    if (value[i] == 'D' || value[i] == 'd')
      iDatePickSetDayTextBox( data, ih, i * 2);
    else if (value[i] == 'M' || value[i] == 'm')
      iDatePickSetMonthTextBox( data, ih, i * 2);
    else if (value[i] == 'Y' || value[i] == 'y')
      iDatePickSetYearTextBox( data, ih, i * 2);
    else
      return 0;
  }
  return 1;
}

static char* iDatePickGetTodayAttrib( struct libData *data, Ihandle *ih )
{
  struct tm * timeinfo;
  time_t timer;
  time(&timer);
  timeinfo = localtime(&timer);
  (void)ih;
  return iupStrReturnStrf("%d/%d/%d", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
}


/*********************************************************************************************/


static Ihandle *iDatePickCreateText( struct libData *data )
{
  Ihandle *txt = amy_IupText( data, NULL );
  amy_IupSetAttribute( data, txt, "BORDER", "NO");
  amy_IupSetAttribute( data, txt, "NOHIDESEL", "NO");
  amy_IupSetAttribute( data, txt, "ALIGNMENT", "ACENTER");
  amy_IupSetCallback( data, txt, "K_ANY", (Icallback)iDatePickTextKAny_CB);
  amy_IupSetCallback( data, txt, "VALUECHANGED_CB", iDatePickTextValueChanged_CB);
  return txt;
}

static int iDatePickCreateMethod( struct libData *data, Ihandle *ih, void **params )
{
  Ihandle *box, *tgl;
  (void)params;
  
  tgl = amy_IupToggle( data, NULL, NULL);
  amy_IupSetAttribute( data, tgl, "IMAGE", "IupArrowDown");
  amy_IupSetAttribute( data, tgl, "EXPAND", "VERTICALFREE");
  amy_IupSetAttribute( data, tgl, "FLAT", "YES");
  amy_IupSetAttribute( data, tgl, "IGNOREDOUBLECLICK", "YES");
  amy_IupSetCallback( data, tgl, "ACTION", (Icallback)iDatePickToggleAction_CB);
  amy_IupSetCallback( data, tgl, "ENTERWINDOW_CB", (Icallback)iDatePickToggleEnterWindow_CB);
  amy_IupSetCallback( data, tgl, "LEAVEWINDOW_CB", (Icallback)iDatePickToggleLeaveWindow_CB);

  box = amy_IupHbox( data, iDatePickCreateText( data ), amy_IupLabel( data, "/"), iDatePickCreateText( data ), amy_IupLabel( data, "/"), iDatePickCreateText( data ), tgl, NULL);
  amy_IupSetAttribute( data, box, "MARGIN", "0x0");
  amy_IupSetAttribute( data, box, "GAP", "0");

  iupChildTreeAppend( data, ih, box);
  box->flags |= IUP_INTERNAL;

  iDatePickSetOrderAttrib( data, ih, "DMY");
  iDatePickSetValueAttrib( data, ih, iDatePickGetTodayAttrib( data, ih ));
  
#if 1 /* GTK_CHECK_VERSION(3, 16, 0) */
  amy_IupSetAttribute( data, ih, "BACKCOLOR", amy_IupGetGlobal( data, "TXTBGCOLOR")); /* workaround */
#else
  amy_IupSetAttribute( data, ih, "BGCOLOR", amy_IupGetGlobal( data, "TXTBGCOLOR")); /* NOT Working in GTK > 3.16 */
#endif

  return IUP_NOERROR;
}

static void iDatePickUnMapMethod( struct libData *data, Ihandle *ih )
{
  Ihandle *calendar = (Ihandle*) iupAttribGet( data, ih, "_IUP_CALENDAR");
  if (iupObjectCheck( data, calendar))
  {
    amy_IupDestroy( data, amy_IupGetDialog( data, calendar ));
    iupAttribSet( data, ih, "_IUP_CALENDAR", NULL);
  }
}

Iclass *iupDatePickNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, iupRegisterFindClass( data, "frame" ));

  ic->name = "datepick";
  ic->cons = "DatePick";
  ic->format = NULL;  /* no parameters */
  ic->nativetype = IUP_TYPECONTROL;
  ic->childtype = IUP_CHILDNONE;
  ic->is_interactive = 1;

  /* Class functions */
  ic->New = iupDatePickNewClass;
  ic->Create = iDatePickCreateMethod;
  ic->UnMap = iDatePickUnMapMethod;

  /* Callbacks */
  iupClassRegisterCallback( data, ic, "VALUECHANGED_CB", "");

  iupClassRegisterAttribute( data, ic, "VALUE", iDatePickGetValueAttrib, iDatePickSetValueAttrib, IUPAF_SAMEASSYSTEM, "TODAY", IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT);
  iupClassRegisterAttribute( data, ic, "TODAY", iDatePickGetTodayAttrib, NULL, NULL, NULL, IUPAF_NOT_MAPPED | IUPAF_READONLY | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT);

  iupClassRegisterAttribute( data, ic, "SEPARATOR", NULL, iDatePickSetSeparatorAttrib, IUPAF_SAMEASSYSTEM, "/", IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT);
  iupClassRegisterAttribute( data, ic, "ORDER", NULL, iDatePickSetOrderAttrib, IUPAF_SAMEASSYSTEM, "DMY", IUPAF_NOT_MAPPED|IUPAF_NO_INHERIT);
  iupClassRegisterAttribute( data, ic, "ZEROPRECED", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT);

  iupClassRegisterAttribute( data, ic, "CALENDARWEEKNUMBERS", NULL, NULL, NULL, NULL, IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT);
  iupClassRegisterAttribute( data, ic, "SHOWDROPDOWN", NULL, iDatePickSetShowDropdownAttrib, NULL, NULL, IUPAF_WRITEONLY | IUPAF_NO_INHERIT);

  return ic;
}

IUP_API Ihandle *amy_IupDatePick( struct libData *data )
{
  return amy_IupCreate( data, "datepick" );
}
