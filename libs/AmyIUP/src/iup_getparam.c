
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
 * \brief amy_IupGetParam
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "iup.h"

#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_assert.h"
#include "iup_strmessage.h"
#include "iup_layout.h"
#include "iup_drvfont.h"
#include "iup_register.h"
#include "iup_stdcontrols.h"
#include "iup_varg.h"

#endif

#define IUP_RAD2DEG  57.295779513   /* radians to degrees (deg = IUP_RAD2DEG * rad) */


static void iParamSetDoublePrec( struct libData *data, Ihandle *ih, const char *name, double num, int prec)
{
  char value[80];
  char format[30];
  if (prec <= 0) prec = amy_IupGetInt( data, NULL, "DEFAULTPRECISION" );
  sprintf(format, "%%.%df", prec );
  iupStrPrintfDoubleLocale(value, format, num, amy_IupGetGlobal( data, "DEFAULTDECIMALSYMBOL" ));

  amy_IupStoreAttribute( data, ih, name, value );
}

/*******************************************************************************************
                    Internal Callbacks
*******************************************************************************************/

static int iParamDlgClose_CB( struct libData *data, Ihandle *dlg)
{
  Ihandle *param_box = (Ihandle*) iupAttribGetInherit( data, dlg, "PARAMBOX" );
  Iparamcb cb = (Iparamcb) amy_IupGetCallback( data, param_box, "PARAM_CB" );
  iupAttribSet( data, param_box, "STATUS", "0" );
  if (cb && !cb(param_box, IUP_GETPARAM_CLOSE, (void*) iupAttribGet( data, param_box, "USERDATA" )))
    return IUP_IGNORE;
  else
    return IUP_CLOSE;
}

static int iParamButton1_CB( struct libData *data, Ihandle *self)
{
  Ihandle *param_box = (Ihandle*) iupAttribGetInherit( data, self, "PARAMBOX" );
  Iparamcb cb = (Iparamcb) amy_IupGetCallback( data, param_box, "PARAM_CB" );
  iupAttribSet( data, param_box, "STATUS", "1" );
  if (cb && !cb(param_box, IUP_GETPARAM_BUTTON1, (void*) iupAttribGet( data, param_box, "USERDATA" )))
    return IUP_DEFAULT;
  else
    return IUP_CLOSE;
}

static int iParamButton2_CB( struct libData *data, Ihandle *self)
{
  Ihandle *param_box = (Ihandle*) iupAttribGetInherit( data, self, "PARAMBOX" );
  Iparamcb cb = (Iparamcb) amy_IupGetCallback( data, param_box, "PARAM_CB" );
  iupAttribSet( data, param_box, "STATUS", "0" );
  if (cb && !cb(param_box, IUP_GETPARAM_BUTTON2, (void*) iupAttribGet( data, param_box, "USERDATA" )))
    return IUP_DEFAULT;
  else
    return IUP_CLOSE;
}

static int iParamButton3_CB( struct libData *data, Ihandle *self)
{
  Ihandle *param_box = (Ihandle*) iupAttribGetInherit( data, self, "PARAMBOX" );
  Iparamcb cb = (Iparamcb) amy_IupGetCallback( data, param_box, "PARAM_CB" );
  if (cb) 
    cb(param_box, IUP_GETPARAM_BUTTON3, (void*) iupAttribGet( data, param_box, "USERDATA" ));
  return IUP_DEFAULT;
}


/***********************************************************************/


static int iParamToggleAction_CB( struct libData *data, Ihandle *self, int v)
{
  Ihandle *param = (Ihandle*) iupAttribGetInherit( data, self, "PARAM" );
  Ihandle *param_box = (Ihandle*) iupAttribGetInherit( data, self, "PARAMBOX" );
  Iparamcb cb = (Iparamcb) amy_IupGetCallback( data, param_box, "PARAM_CB" );
  int old_v = iupAttribGetInt( data, param, "VALUE" );

  if (v == 1)
    iupAttribSet( data, param, "VALUE", "1" );
  else
    iupAttribSet( data, param, "VALUE", "0" );

  if (cb && !cb(param_box, iupAttribGetInt( data, param, "INDEX" ), (void*) iupAttribGet( data, param_box, "USERDATA" ))) 
  {
    /* Undo */
    if (old_v == 1)
    {
      iupAttribSet( data, param, "VALUE", "1" );
      amy_IupSetAttribute( data, self, "VALUE", "1" );
    }
    else
    {
      iupAttribSet( data, param, "VALUE", "0" );
      amy_IupSetAttribute( data, self, "VALUE", "0" );
    }

    /* there is no IUP_IGNORE for amy_IupToggle */
    return IUP_DEFAULT;
  }

  /* update the interface */
  if (v == 1)
    amy_IupStoreAttribute( data, self, "TITLE", iupAttribGet( data, param, "TRUE" ));
  else
    amy_IupStoreAttribute( data, self, "TITLE", iupAttribGet( data, param, "FALSE" ));

  return IUP_DEFAULT;
}

static int iParamDateValueChanged_CB( struct libData *data, Ihandle *self)
{
  Ihandle *param = (Ihandle*) iupAttribGetInherit( data, self, "PARAM" );
  Ihandle *param_box = (Ihandle*) iupAttribGetInherit( data, self, "PARAMBOX" );
  Iparamcb cb = (Iparamcb) amy_IupGetCallback( data, param_box, "PARAM_CB" );

  iupAttribSetStr( data, param, "OLD_VALUE", iupAttribGet( data, param, "VALUE" ));
  iupAttribSetStr( data, param, "VALUE", amy_IupGetAttribute( data, self, "VALUE" ));

  if (cb && !cb(param_box, iupAttribGetInt( data, param, "INDEX" ), (void*) iupAttribGet( data, param_box, "USERDATA" )))
  {
    /* Undo */
    amy_IupSetStrAttribute( data, self, "VALUE", iupAttribGet( data, param, "OLD_VALUE" ));
    iupAttribSetStr( data, param, "VALUE", iupAttribGet( data, param, "OLD_VALUE" ));
    iupAttribSet( data, param, "OLD_VALUE", NULL );
    return IUP_IGNORE;
  }

  return IUP_DEFAULT;
}

static int iParamTextAction_CB( struct libData *data, Ihandle *self, int c, char *after)
{
  Ihandle *param = (Ihandle*) iupAttribGetInherit( data, self, "PARAM" );
  Ihandle *param_box = (Ihandle*) iupAttribGetInherit( data, self, "PARAMBOX" );
  Iparamcb cb = (Iparamcb) amy_IupGetCallback( data, param_box, "PARAM_CB" );
  Ihandle *aux = (Ihandle*) iupAttribGet( data, param, "AUXCONTROL" );
  int ret = IUP_DEFAULT;
  (void)c;

  if ( !  amy_IupGetInt( data, self, "MULTILINE" ) && (iupStrLineCount(after, (int)strlen(after)) > 1))
  {
    /* get only the first line */
    int len;
    iupStrNextLine(after, &len );
    after[len] = 0;
    amy_IupSetStrAttribute( data, self, "VALUE", after );
    ret = IUP_IGNORE;
  }
 
  if (iupStrEqual(iupAttribGet( data, param, "TYPE" ), "REAL" ))
  {
    double val = 0;
    if (iupStrToDoubleLocale(after, &val, amy_IupGetGlobal( data, "DEFAULTDECIMALSYMBOL" )))
      iupAttribSetDouble( data, param, "VALUE", val );
    else
      iupAttribSetStr( data, param, "VALUE", after );
  }
  else
    iupAttribSetStr( data, param, "VALUE", after );

  if (cb && !cb(param_box, iupAttribGetInt( data, param, "INDEX" ), (void*) iupAttribGet( data, param_box, "USERDATA" ))) 
  {
    /* Undo */
    iupAttribSetStr( data, param, "VALUE", amy_IupGetAttribute( data, self, "VALUE" ));
    return IUP_IGNORE;
  }

  if (aux)
  {
    if (iupStrEqual(iupAttribGet( data, param, "TYPE" ), "COLOR" ))
      amy_IupStoreAttribute( data, aux, "BGCOLOR", after );
    else
      amy_IupStoreAttribute( data, aux, "VALUE", after );
  }

  if ( amy_IupGetInt( data, self, "SPIN" ))
  {
    if (iupAttribGet( data, self, "_IUPGP_SPINREAL" ))
    {
      double min = iupAttribGetDouble( data, param, "MIN" );
      double step = iupAttribGetDouble( data, self, "_IUPGP_INCSTEP" );
      double val = iupAttribGetDouble( data, param, "VALUE" );
      amy_IupSetInt( data, self, "SPINVALUE", iupRound( data, (val - min) / step));
    }
    else
    {
      int val;
      if (iupStrToInt(after, &val))
        amy_IupSetInt( data, self, "SPINVALUE", val );
    }
  }

  return ret;
}

static int iParamValAction_CB( struct libData *data, Ihandle *self)
{
  Ihandle *param = (Ihandle*) iupAttribGetInherit( data, self, "PARAM" );
  Ihandle *ctrl = (Ihandle*) iupAttribGetInherit( data, self, "CONTROL" );
  Ihandle *param_box = (Ihandle*) iupAttribGetInherit( data, self, "PARAMBOX" );
  Iparamcb cb = (Iparamcb) amy_IupGetCallback( data, param_box, "PARAM_CB" );
  double old_value = iupAttribGetDouble( data, param, "VALUE" );
  double val = amy_IupGetDouble( data, self, "VALUE" );

  char *type = iupAttribGet( data, param, "TYPE" );
  if (iupStrEqual(type, "INTEGER" ))
  {
    iupAttribSetInt( data, param, "VALUE", (int)val );
  }
  else
  {
    if (iupAttribGetInt( data, param, "ANGLE" ))
    {
      double old_angle;

      if (val == 0)
      {
        old_angle = iupAttribGetDouble( data, param, "VALUE" );
        iupAttribSetDouble( data, param, "_IUPGP_OLD_ANGLE", old_angle );
      }
      else
        old_angle = iupAttribGetDouble( data, param, "_IUPGP_OLD_ANGLE" );

      val = old_angle + val*IUP_RAD2DEG;

      if (iupAttribGetInt( data, param, "INTERVAL" ))
      {
        double min = iupAttribGetDouble( data, param, "MIN" );
        double max = iupAttribGetDouble( data, param, "MAX" );
        if (val < min)
          val = min;
        if (val > max)
          val = max;
      }
      else if (iupAttribGetInt( data, param, "PARTIAL" ))
      {
        double min = iupAttribGetDouble( data, param, "MIN" );
        if (val < min)
          val = min;
      }
    }

    iupAttribSetDouble( data, param, "VALUE", val );
  }

  if (cb && !cb(param_box, iupAttribGetInt( data, param, "INDEX" ), (void*) iupAttribGet( data, param_box, "USERDATA" ))) 
  {
    /* Undo */
    iupAttribSetDouble( data, param, "VALUE", old_value );

    if ( ! iupAttribGetInt( data, param, "ANGLE" ))
      amy_IupSetDouble( data, self, "VALUE", old_value );

    /* there is no IUP_IGNORE for amy_IupVal */
    return IUP_DEFAULT;
  }

  type = iupAttribGet( data, param, "TYPE" );
  if (iupStrEqual(type, "INTEGER" ))
    amy_IupSetInt( data, ctrl, "VALUE", (int)val );
  else
  {
    int prec = amy_IupGetInt( data, param, "PRECISION" );
    iParamSetDoublePrec( data, ctrl, "VALUE", val, prec );
  }

  if ( amy_IupGetInt( data, ctrl, "SPIN" ))
  {
    if (iupAttribGet( data, ctrl, "_IUPGP_SPINREAL" ))
    {
      double min = iupAttribGetDouble( data, param, "MIN" );
      double step = iupAttribGetDouble( data, ctrl, "_IUPGP_INCSTEP" );
      val = iupAttribGetDouble( data, param, "VALUE" );
      amy_IupSetInt( data, ctrl, "SPINVALUE", iupRound( data, (val - min) / step));
    }
    else
    {
      int ival = amy_IupGetInt( data, ctrl, "VALUE" );
      amy_IupSetInt( data, ctrl, "SPINVALUE", ival );
    }
  }

  return IUP_DEFAULT;
}

static int iParamListAction_CB( struct libData *data, Ihandle *self, char *t, int i, int v)
{
  (void)t;
  if (v == 1)
  {
    Ihandle *param = (Ihandle*) iupAttribGetInherit( data, self, "PARAM" );
    Ihandle *param_box = (Ihandle*) iupAttribGetInherit( data, self, "PARAMBOX" );
    Iparamcb cb = (Iparamcb) amy_IupGetCallback( data, param_box, "PARAM_CB" );
    int old_i = iupAttribGetInt( data, param, "VALUE" );

    iupAttribSetInt( data, param, "VALUE", i-1 );

    if (cb && !cb(param_box, iupAttribGetInt( data, param, "INDEX" ), (void*) iupAttribGet( data, param_box, "USERDATA" ))) 
    {
      /* Undo */
      iupAttribSetInt( data, param, "VALUE", old_i );
      amy_IupSetInt( data, self, "VALUE", old_i+1 );

      /* there is no IUP_IGNORE for amy_IupList */
      return IUP_DEFAULT;
    }
  }

  return IUP_DEFAULT;
}

static int iParamOptionsAction_CB( struct libData *data, Ihandle *self, int v)
{
  if (v == 1)
  {
    Ihandle *param = (Ihandle*) iupAttribGetInherit( data, self, "PARAM" );
    Ihandle *param_box = (Ihandle*) iupAttribGetInherit( data, self, "PARAMBOX" );
    Iparamcb cb = (Iparamcb) amy_IupGetCallback( data, param_box, "PARAM_CB" );
    int old_v = iupAttribGetInt( data, param, "VALUE" );
    int new_v = iupAttribGetInt( data, self, "OPT" );

    iupAttribSetInt( data, param, "VALUE", new_v );

    if (cb && !cb(param_box, iupAttribGetInt( data, param, "INDEX" ), (void*) iupAttribGet( data, param_box, "USERDATA" ))) 
    {
      /* Undo */
      iupAttribSetInt( data, param, "VALUE", old_v );
      amy_IupSetAttribute( data, amy_IupGetParent( data, amy_IupGetParent( data, self )), "VALUE_HANDLE", (char*) amy_IupGetChild( data, amy_IupGetParent( data, self), old_v));
    }
  }

  return IUP_DEFAULT;
}

static int iParamFileButton_CB( struct libData *data, Ihandle *self)
{
  Ihandle *param   = (Ihandle*) iupAttribGetInherit( data, self, "PARAM" );
  Ihandle *ctrl = (Ihandle*) iupAttribGetInherit( data, self, "CONTROL" );
  Ihandle *param_box = (Ihandle*) iupAttribGetInherit( data, self, "PARAMBOX" );
  Iparamcb cb = (Iparamcb) amy_IupGetCallback( data, param_box, "PARAM_CB" );

  Ihandle *file_dlg = amy_IupFileDlg( data );

  char *dir = iupAttribGet( data, param, "DIRECTORY" );

  amy_IupSetAttributeHandle( data, file_dlg, "PARENTDIALOG", amy_IupGetDialog( data, self ));
  amy_IupSetStrAttribute( data, file_dlg, "TITLE", iupAttribGet( data, param, "TITLE" ));
  amy_IupSetAttribute( data, file_dlg, "VALUE", iupAttribGet( data, param, "VALUE" ));

  amy_IupSetAttribute( data, file_dlg, "DIALOGTYPE", iupAttribGet( data, param, "DIALOGTYPE" ));
  amy_IupSetAttribute( data, file_dlg, "FILTER", iupAttribGet( data, param, "FILTER" ));
  amy_IupSetAttribute( data, file_dlg, "DIRECTORY", dir );
  amy_IupSetAttribute( data, file_dlg, "NOCHANGEDIR", iupAttribGet( data, param, "NOCHANGEDIR" ));
  amy_IupSetAttribute( data, file_dlg, "NOOVERWRITEPROMPT", iupAttribGet( data, param, "NOOVERWRITEPROMPT" ));

  if (iupStrEqualNoCase( amy_IupGetAttribute( data, file_dlg, "DIALOGTYPE" ), "DIR" ) && ( ! dir || dir[0]==0))
    amy_IupSetStrAttribute( data, file_dlg, "DIRECTORY", iupAttribGet( data, param, "VALUE" ));

  amy_IupPopup( data, file_dlg, IUP_CENTER, IUP_CENTER );

  if ( amy_IupGetInt( data, file_dlg, "STATUS" ) != -1)
  {
    char *value = amy_IupGetAttribute( data, file_dlg, "VALUE" );
    iupAttribSetStr( data, param, "OLD_VALUE", iupAttribGet( data, param, "VALUE" ));
    iupAttribSetStr( data, param, "VALUE", value );

    if (cb && !cb(param_box, iupAttribGetInt( data, param, "INDEX" ), (void*) iupAttribGet( data, param_box, "USERDATA" )))
    {
      /* Undo */
      iupAttribSetStr( data, param, "VALUE", iupAttribGet( data, param, "OLD_VALUE" ));
    }
    else
    {
      amy_IupSetAttribute( data, ctrl, "VALUE", iupAttribGet( data, param, "VALUE" ));

      if (iupStrEqualNoCase( amy_IupGetAttribute( data, file_dlg, "DIALOGTYPE" ), "DIR" ))
        iupAttribSetStr( data, param, "DIRECTORY", value );
    }
  }

  amy_IupDestroy( data, file_dlg );

  return IUP_DEFAULT;
}

static int iParamColorButton_CB( struct libData *data, Ihandle *self)
{
  Ihandle *param   = (Ihandle*) iupAttribGetInherit( data, self, "PARAM" );
  Ihandle *ctrl = (Ihandle*) iupAttribGetInherit( data, self, "CONTROL" );
  Ihandle *param_box = (Ihandle*) iupAttribGetInherit( data, self, "PARAMBOX" );
  Iparamcb cb = (Iparamcb) amy_IupGetCallback( data, param_box, "PARAM_CB" );

  Ihandle *color_dlg = amy_IupColorDlg( data );
  amy_IupSetAttributeHandle( data, color_dlg, "PARENTDIALOG", amy_IupGetDialog( data, self ));
  amy_IupSetStrAttribute( data, color_dlg, "TITLE", iupAttribGet( data, param, "TITLE" ));
  amy_IupSetAttribute( data, color_dlg, "VALUE", iupAttribGet( data, param, "VALUE" ));

  amy_IupPopup( data, color_dlg, IUP_CENTER, IUP_CENTER );

  if ( amy_IupGetInt( data, color_dlg, "STATUS" ) == 1)
  {
    char *value = amy_IupGetAttribute( data, color_dlg, "VALUE" );
    iupAttribSetStr( data, param, "OLD_VALUE", iupAttribGet( data, param, "VALUE" ));
    iupAttribSetStr( data, param, "VALUE", value );

    if (cb && !cb(param_box, iupAttribGetInt( data, param, "INDEX" ), (void*) iupAttribGet( data, param_box, "USERDATA" )))
    {
      /* Undo */
      iupAttribSetStr( data, param, "VALUE", iupAttribGet( data, param, "OLD_VALUE" ));
    }
    else
    {
      amy_IupSetAttribute( data, ctrl, "VALUE", iupAttribGet( data, param, "VALUE" ));
      amy_IupStoreAttribute( data, self, "BGCOLOR", iupAttribGet( data, param, "VALUE" ));
    }
  }

  amy_IupDestroy( data, color_dlg );

  return IUP_DEFAULT;
}

static int iParamFontButton_CB( struct libData *data, Ihandle *self)
{
  Ihandle *param   = (Ihandle*) iupAttribGetInherit( data, self, "PARAM" );
  Ihandle *ctrl = (Ihandle*) iupAttribGetInherit( data, self, "CONTROL" );
  Ihandle *param_box = (Ihandle*) iupAttribGetInherit( data, self, "PARAMBOX" );
  Iparamcb cb = (Iparamcb) amy_IupGetCallback( data, param_box, "PARAM_CB" );

  Ihandle *font_dlg = amy_IupFontDlg( data );
  amy_IupSetAttributeHandle( data, font_dlg, "PARENTDIALOG", amy_IupGetDialog( data, self ));
  amy_IupSetStrAttribute( data, font_dlg, "TITLE", iupAttribGet( data, param, "TITLE" ));
  amy_IupSetAttribute( data, font_dlg, "VALUE", iupAttribGet( data, param, "VALUE" ));

  amy_IupPopup( data, font_dlg, IUP_CENTER, IUP_CENTER );

  if ( amy_IupGetInt( data, font_dlg, "STATUS" ) == 1)
  {
    char *value = amy_IupGetAttribute( data, font_dlg, "VALUE" );
    iupAttribSetStr( data, param, "OLD_VALUE", iupAttribGet( data, param, "VALUE" ));
    iupAttribSetStr( data, param, "VALUE", value );

    if (cb && !cb(param_box, iupAttribGetInt( data, param, "INDEX" ), (void*) iupAttribGet( data, param_box, "USERDATA" )))
    {
      /* Undo */
      iupAttribSetStr( data, param, "VALUE", iupAttribGet( data, param, "OLD_VALUE" ));
    }
    else
      amy_IupSetAttribute( data, ctrl, "VALUE", iupAttribGet( data, param, "VALUE" ));

    iupAttribSet( data, param, "OLD_VALUE", NULL );
  }

  amy_IupDestroy( data, font_dlg );

  return IUP_DEFAULT;
}

static int iParamSpinReal_CB( struct libData *data, Ihandle *self, int pos)
{
  Ihandle *param = (Ihandle*) iupAttribGetInherit( data, self, "PARAM" );
  Ihandle *param_box = (Ihandle*) iupAttribGetInherit( data, self, "PARAMBOX" );
  Iparamcb cb = (Iparamcb) amy_IupGetCallback( data, param_box, "PARAM_CB" );
  Ihandle *ctrl = (Ihandle*) iupAttribGet( data, param, "CONTROL" );
  double min = iupAttribGetDouble( data, param, "MIN" );
  double max = iupAttribGetDouble( data, param, "MAX" );
  double step = iupAttribGetDouble( data, ctrl, "_IUPGP_INCSTEP" );
  double old_value = iupAttribGetDouble( data, param, "VALUE" );

  /* here spin is always [0-spinmax] converted to [min-max] */
  double val = (double)pos*step + min;
  if (val < min)
    val = min;
  if (val > max)
    val = max;

  iupAttribSetDouble( data, param, "VALUE", val );

  if (cb) 
  {
    int ret;
    iupAttribSet( data, param_box, "SPINNING", "1" );
    ret = cb(param_box, iupAttribGetInt( data, param, "INDEX" ), (void*) iupAttribGet( data, param_box, "USERDATA" ));
    iupAttribSet( data, param_box, "SPINNING", NULL );
    if ( ! ret)
    {
      /* Undo */
      iupAttribSetDouble( data, param, "VALUE", old_value );
      return IUP_IGNORE;
    }
  }

  {
    int prec = amy_IupGetInt( data, param, "PRECISION" );
    iParamSetDoublePrec( data, ctrl, "VALUE", val, prec );
  }

  {
    Ihandle *aux = (Ihandle*) iupAttribGet( data, param, "AUXCONTROL" );
    if (aux)
      amy_IupSetDouble( data, aux, "VALUE", val );
  }

  return IUP_DEFAULT;
}

static int iParamSpinInt_CB( struct libData *data, Ihandle *self, int pos)
{
  Ihandle *param = (Ihandle*) iupAttribGetInherit( data, self, "PARAM" );
  Ihandle *param_box = (Ihandle*) iupAttribGetInherit( data, self, "PARAMBOX" );
  Iparamcb cb = (Iparamcb) amy_IupGetCallback( data, param_box, "PARAM_CB" );
  Ihandle *ctrl = (Ihandle*) iupAttribGet( data, param, "CONTROL" );
  int old_value = iupAttribGetInt( data, param, "VALUE" );

  /* here spin is always [min-max] */

  iupAttribSetInt( data, param, "VALUE", pos );

  if (cb) 
  {
    int ret;
    iupAttribSet( data, param_box, "SPINNING", "1" );
    ret = cb(param_box, iupAttribGetInt( data, param, "INDEX" ), (void*) iupAttribGet( data, param_box, "USERDATA" ));
    iupAttribSet( data, param_box, "SPINNING", NULL );
    if ( ! ret)
    {
      /* Undo */
      iupAttribSetInt( data, param, "VALUE", old_value );
      return IUP_IGNORE;
    }
  }

  amy_IupSetInt( data, ctrl, "VALUE", pos );

  {
    Ihandle *aux = (Ihandle*) iupAttribGet( data, param, "AUXCONTROL" );
    if (aux)
      amy_IupSetInt( data, aux, "VALUE", pos );
  }

  return IUP_DEFAULT;
}

/*******************************************************************************************
                    Creates a Parameter Control Box
*******************************************************************************************/

static int iParamDestroy_CB( struct libData *data, Ihandle *self)
{
  Ihandle *param = (Ihandle*) iupAttribGetInherit( data, self, "PARAM" );
  amy_IupDestroy( data, param );
  iupAttribSet( data, self, "PARAM", NULL );
  return IUP_DEFAULT;
}

static Ihandle *iParamCreateCtrlBox( struct libData *data, Ihandle *param, const char *type)
{
  Ihandle *box, *ctrl = NULL, *label;
  char *title = iupAttribGet( data, param, "TITLE" );

  label = amy_IupLabel( data, title );
  amy_IupSetCallback( data, label, "DESTROY_CB", iParamDestroy_CB );
  if ( ! title || title[0] == 0)
    amy_IupSetAttribute( data, label, "VISIBLE", "NO" );

  if (iupStrEqual(type, "SEPARATOR" ))
  {
    box = amy_IupHbox( data, label, NULL );
    amy_IupSetAttribute( data, box,"ALIGNMENT","ACENTER" );

    amy_IupSetAttribute( data, label, "FONTSTYLE", "Bold" );
  }
  else
  {
    if (iupStrEqual(type, "STRING" ) && iupAttribGetInt( data, param, "MULTILINE" ))
    {
      Ihandle *hbox1 = amy_IupHbox( data, amy_IupSetAttributes( data, amy_IupFill( data ), "SIZE=5" ), label, NULL );
      amy_IupSetAttribute( data, hbox1,"ALIGNMENT","ACENTER" );

      box = amy_IupVbox( data, hbox1, NULL );
      amy_IupSetAttribute( data, box,"ALIGNMENT","ALEFT" );
    }
    else
    {
      Ihandle *fill = amy_IupFill( data );
      int indent = iupAttribGetInt( data, param, "INDENT" );
      amy_IupSetInt( data, fill, "SIZE", 5 + 8*indent );
      box = amy_IupHbox( data, fill, label, NULL );
      amy_IupSetAttribute( data, box,"ALIGNMENT","ACENTER" );
    }
  }

  amy_IupSetAttribute( data, box,"MARGIN","0x0" );

  type = iupAttribGet( data, param, "TYPE" );
  if (iupStrEqual(type, "BOOLEAN" ))
  {
    int value = iupAttribGetInt( data, param, "VALUE" );
    if (value)
    {
      ctrl = amy_IupToggle( data, iupAttribGet( data, param, "TRUE" ), NULL );
      amy_IupSetAttribute( data, ctrl, "VALUE", "ON" );
    }
    else
    {
      ctrl = amy_IupToggle( data, iupAttribGet( data, param, "FALSE" ), NULL );
      amy_IupSetAttribute( data, ctrl, "VALUE", "OFF" );
    }
    amy_IupSetCallback( data, ctrl, "ACTION", (Icallback)iParamToggleAction_CB );
    amy_IupSetAttribute( data, ctrl, "EXPAND", "HORIZONTAL" );

    amy_IupAppend( data, box, ctrl );
  }
  else if (iupStrEqual(type, "SEPARATOR" ))
  {
    ctrl = amy_IupLabel( data, "" );
    amy_IupSetAttribute( data, ctrl, "SEPARATOR", "HORIZONTAL" );
    amy_IupSetAttribute( data, ctrl, "EXPAND", "HORIZONTAL" );

    amy_IupAppend( data, box, ctrl );
  }
  else if (iupStrEqual(type, "LIST" ))
  {
    int i = 0;
    ctrl = amy_IupList( data, NULL );
    amy_IupSetCallback( data, ctrl, "ACTION", (Icallback)iParamListAction_CB );
    amy_IupSetAttribute( data, ctrl, "DROPDOWN", "YES" );

    while (*iupAttribGetId( data, param, "", i) != 0)
    {
      amy_IupStoreAttributeId( data, ctrl, "", i+1, iupAttribGetId( data, param, "", i));
      i++;
    }
    amy_IupStoreAttributeId( data, ctrl, "", i+1, NULL );

    amy_IupSetInt( data, ctrl, "VALUE", iupAttribGetInt( data, param, "VALUE" ) + 1 );

    amy_IupAppend( data, box, ctrl );
  }
  else if (iupStrEqual(type, "OPTIONS" ))
  {
    Ihandle *tgl;
    int i = 0;
    ctrl = amy_IupHbox( data, NULL );
    amy_IupSetAttribute( data, ctrl, "GAP", "5" );

    while (*iupAttribGetId( data, param, "", i) != 0)
    {
      tgl = amy_IupToggle( data, iupAttribGetId( data, param, "", i), NULL );
      amy_IupSetInt( data, tgl, "OPT", i );
      amy_IupSetCallback( data, tgl, "ACTION", (Icallback)iParamOptionsAction_CB );

      amy_IupAppend( data, ctrl, tgl );

      i++;
    }

    amy_IupAppend( data, box, amy_IupRadio( data, ctrl ));
    tgl = amy_IupGetChild( data, ctrl, iupAttribGetInt( data, param, "VALUE" ));
    /* RADIO initial value */
    amy_IupSetAttribute( data, amy_IupGetParent( data, ctrl ), "VALUE_HANDLE", (char*)tgl );
    ctrl = tgl; /* allow TIP to go to the first toggle */
  }
  else if (iupStrEqual(type, "STRING" ))
  {
    if (iupAttribGetInt( data, param, "MULTILINE" ))
    {
      Ihandle *hbox;

      ctrl = amy_IupMultiLine( data, NULL );
      amy_IupSetAttribute( data, ctrl, "VISIBLECOLUMNS", "8" );
      amy_IupSetAttribute( data, ctrl, "VISIBLELINES", "6" );
      amy_IupSetAttribute( data, ctrl, "EXPAND", "YES" );

      hbox = amy_IupHbox( data, amy_IupSetAttributes( data, amy_IupFill( data ), "SIZE=5" ), ctrl, NULL );
      amy_IupSetAttribute( data, hbox,"ALIGNMENT","ACENTER" );

      amy_IupAppend( data, box, hbox );
    }
    else
    {
      char *visiblecolumns;

      ctrl = amy_IupText( data, NULL );
      amy_IupSetAttribute( data, ctrl, "VISIBLECOLUMNS", "8" );
      amy_IupAppend( data, box, ctrl );

      visiblecolumns = iupAttribGet( data, param, "VISIBLECOLUMNS" );
      if (visiblecolumns)
        amy_IupSetStrAttribute( data, ctrl, "VISIBLECOLUMNS", visiblecolumns );
      else
        amy_IupSetAttribute( data, ctrl, "EXPAND", "HORIZONTAL" );
    }
    amy_IupSetCallback( data, ctrl, "ACTION", (Icallback)iParamTextAction_CB );
    amy_IupStoreAttribute( data, ctrl, "VALUE", iupAttribGet( data, param, "VALUE" ));

    {
      char *mask = iupAttribGet( data, param, "MASK" );
      if (mask)
        amy_IupStoreAttribute( data, ctrl, "MASK", mask );
    }

    iupAttribSet( data, param, "TEXTEXPAND", "1" );
  }
  else if (iupStrEqual(type, "DATE" ))
  {
    char *value;

    ctrl = amy_IupDatePick( data );
    amy_IupAppend( data, box, ctrl );

    amy_IupSetCallback( data, ctrl, "VALUECHANGED_CB", (Icallback)iParamDateValueChanged_CB );
    amy_IupStoreAttribute( data, ctrl, "VALUE", iupAttribGet( data, param, "VALUE" ));

    value = iupAttribGet( data, param, "SEPARATOR" );
    if (value) amy_IupStoreAttribute( data, ctrl, "SEPARATOR", value );
    value = iupAttribGet( data, param, "ZEROPRECED" );
    if (value) amy_IupStoreAttribute( data, ctrl, "ZEROPRECED", value );
    value = iupAttribGet( data, param, "MONTHSHORTNAMES" );
    if (value) amy_IupStoreAttribute( data, ctrl, "MONTHSHORTNAMES", value );
    value = iupAttribGet( data, param, "ORDER" );
    if (value) amy_IupStoreAttribute( data, ctrl, "ORDER", value );
  }
  else if (iupStrEqual(type, "FILE" ))
  {
    Ihandle *aux;

    ctrl = amy_IupText( data, NULL );
    amy_IupSetAttribute( data, ctrl, "VISIBLECOLUMNS", "15" );
    amy_IupSetAttribute( data, ctrl, "EXPAND", "HORIZONTAL" );
    amy_IupAppend( data, box, ctrl );

    amy_IupSetCallback( data, ctrl, "ACTION", (Icallback)iParamTextAction_CB );
    amy_IupStoreAttribute( data, ctrl, "VALUE", iupAttribGet( data, param, "VALUE" ));

    iupAttribSet( data, param, "TEXTEXPAND", "1" );
    amy_IupSetAttribute( data, box, "NORMALIZESIZE", "VERTICAL" );

    aux = amy_IupButton( data, "...", "" );
    amy_IupStoreAttribute( data, aux, "FONT", "Times, Bold 10" );
    amy_IupSetAttribute( data, aux, "SIZE", "16x" );
    amy_IupSetCallback( data, aux, "ACTION", (Icallback)iParamFileButton_CB );
    iupAttribSet( data, aux, "PARAM", (char*)param );
    iupAttribSet( data, aux, "CONTROL", (char*)ctrl );
    iupAttribSet( data, param, "AUXCONTROL", (char*)aux );

    amy_IupAppend( data, box, aux );
  }
  else if (iupStrEqual(type, "COLOR" ))
  {
    Ihandle *aux;

    ctrl = amy_IupText( data, NULL );
    amy_IupSetAttribute( data, ctrl, "VISIBLECOLUMNS", "15" );
    amy_IupSetAttribute( data, ctrl, "EXPAND", "HORIZONTAL" );
    amy_IupAppend( data, box, ctrl );

    amy_IupSetCallback( data, ctrl, "ACTION", (Icallback)iParamTextAction_CB );
    amy_IupSetAttribute( data, ctrl, "MASK", "(/d|/d/d|1/d/d|2(0|1|2|3|4)/d|25(0|1|2|3|4|5)) (/d|/d/d|1/d/d|2(0|1|2|3|4)/d|25(0|1|2|3|4|5)) (/d|/d/d|1/d/d|2(0|1|2|3|4)/d|25(0|1|2|3|4|5)) (/d|/d/d|1/d/d|2(0|1|2|3|4)/d|25(0|1|2|3|4|5))" );
    amy_IupStoreAttribute( data, ctrl, "VALUE", iupAttribGet( data, param, "VALUE" ));

    iupAttribSet( data, param, "TEXTEXPAND", "1" );
    amy_IupSetAttribute( data, box,"NORMALIZESIZE","VERTICAL" );

    aux = amy_IupButton( data, NULL, NULL );
    amy_IupStoreAttribute( data, aux, "FONT", "Times, Bold Italic 11" );
    amy_IupSetAttribute( data, aux, "SIZE", "16x" );
    amy_IupStoreAttribute( data, aux, "BGCOLOR", iupAttribGet( data, param, "VALUE" ));
    amy_IupSetCallback( data, aux, "ACTION", (Icallback)iParamColorButton_CB );
    iupAttribSet( data, aux, "PARAM", (char*)param );
    iupAttribSet( data, aux, "CONTROL", (char*)ctrl );
    iupAttribSet( data, param, "AUXCONTROL", (char*)aux );

    amy_IupAppend( data, box, aux ); 
  }
  else if (iupStrEqual(type, "FONT" ))
  {
    Ihandle *aux;

    ctrl = amy_IupText( data, NULL );
    amy_IupSetAttribute( data, ctrl, "VISIBLECOLUMNS", "15" );
    amy_IupSetAttribute( data, ctrl, "EXPAND", "HORIZONTAL" );
    amy_IupAppend( data, box, ctrl );

    amy_IupSetCallback( data, ctrl, "ACTION", (Icallback)iParamTextAction_CB );
    amy_IupStoreAttribute( data, ctrl, "VALUE", iupAttribGet( data, param, "VALUE" ));

    iupAttribSet( data, param, "TEXTEXPAND", "1" );
    amy_IupSetAttribute( data, box,"NORMALIZESIZE","VERTICAL" );
      
    aux = amy_IupButton( data, "F", NULL );
    amy_IupStoreAttribute( data, aux, "FONT", "Times, Bold Italic 11" );
    amy_IupSetAttribute( data, aux, "SIZE", "16x" );

    amy_IupSetCallback( data, aux, "ACTION", (Icallback)iParamFontButton_CB );
    iupAttribSet( data, aux, "PARAM", (char*)param );
    iupAttribSet( data, aux, "CONTROL", (char*)ctrl );
    iupAttribSet( data, param, "AUXCONTROL", (char*)aux );

    amy_IupAppend( data, box, aux ); 
  }
  else /* INTEGER, REAL */
  {
    ctrl = amy_IupText( data, NULL );
    amy_IupSetAttribute( data, ctrl, "VISIBLECOLUMNS", "8" );
    amy_IupSetCallback( data, ctrl, "ACTION", (Icallback)iParamTextAction_CB );

    type = iupAttribGet( data, param, "TYPE" );
    if (iupStrEqual(type, "REAL" ))  /* REAL */
    {
      double val = iupAttribGetDouble( data, param, "VALUE" );
      int prec = amy_IupGetInt( data, param, "PRECISION" );
      iParamSetDoublePrec( data, ctrl, "VALUE", val, prec );

      amy_IupSetAttribute( data, ctrl, "MASKDECIMALSYMBOL", amy_IupGetGlobal( data, "DEFAULTDECIMALSYMBOL" ));

      if (iupAttribGetInt( data, param, "INTERVAL" ))
      {
        double min = iupAttribGetDouble( data, param, "MIN" );
        double max = iupAttribGetDouble( data, param, "MAX" );
        double step = iupAttribGetDouble( data, param, "STEP" );
        val = iupAttribGetDouble( data, param, "VALUE" );
        if (step == 0) step = (max-min)/100.0;
        amy_IupSetfAttribute( data, ctrl, "MASKFLOAT", IUP_DOUBLE2STR":"IUP_DOUBLE2STR, min, max );
                             
        /* here spin is always [0-spinmax] converted to [min-max] */

        amy_IupSetAttribute( data, ctrl, "SPIN", "YES" );   /* spin only for intervals */
        amy_IupSetAttribute( data, ctrl, "SPINAUTO", "NO" );
        amy_IupAppend( data, box, ctrl );
        amy_IupSetCallback( data, ctrl, "SPIN_CB", (Icallback)iParamSpinReal_CB );
        /* SPINMIN=0 and SPININC=1 */
        amy_IupSetInt( data, ctrl, "SPINMAX", iupRound( data, (max - min) / step));
        amy_IupSetInt( data, ctrl, "SPINVALUE", iupRound( data, (val - min) / step));

        iupAttribSetDouble( data, ctrl, "_IUPGP_INCSTEP", step );
        iupAttribSet( data, ctrl, "_IUPGP_SPINREAL", "1" );
      }
      else if (iupAttribGetInt( data, param, "PARTIAL" ))
      {
        double min = iupAttribGetDouble( data, param, "MIN" );
        if (min == 0)
          amy_IupSetAttribute( data, ctrl, "MASKREAL", "UNSIGNED" );
        else
          amy_IupSetfAttribute( data, ctrl, "MASKFLOAT", IUP_DOUBLE2STR":"IUP_DOUBLE2STR, min, 1.0e10 );

        amy_IupAppend( data, box, ctrl );
      }
      else
      {
        amy_IupSetAttribute( data, ctrl, "MASKREAL", "SIGNED" );
        amy_IupAppend( data, box, ctrl );
      }
    }
    else /* INTEGER*/
    {
      int val = iupAttribGetInt( data, param, "VALUE" );
      amy_IupSetInt( data, ctrl, "VALUE", val );

      amy_IupSetAttribute( data, ctrl, "SPIN", "YES" );   /* spin always */
      amy_IupSetAttribute( data, ctrl, "SPINAUTO", "NO" );  /* manually update spin so the callback can also updated it */
      amy_IupAppend( data, box, ctrl );
      amy_IupSetCallback( data, ctrl, "SPIN_CB", (Icallback)iParamSpinInt_CB );
      iupAttribSet( data, ctrl, "_IUPGP_INCSTEP", "1" );
      amy_IupSetInt( data, ctrl, "SPINVALUE", val );

      /* here spin is always [min-max] */

      if (iupAttribGetInt( data, param, "INTERVAL" ))
      {
        int min = iupAttribGetInt( data, param, "MIN" );
        int max = iupAttribGetInt( data, param, "MAX" );
        int step = iupAttribGetInt( data, param, "STEP" );
        if (step)
        {
          iupAttribSetInt( data, ctrl, "_IUPGP_INCSTEP", step );
          amy_IupSetInt( data, ctrl, "SPININC", step );
        }
        amy_IupSetInt( data, ctrl, "SPINMAX", max );
        amy_IupSetInt( data, ctrl, "SPINMIN", min );
        amy_IupSetfAttribute( data, ctrl, "MASKINT", "%d:%d", min, max );
      }
      else if (iupAttribGetInt( data, param, "PARTIAL" ))
      {
        int min = iupAttribGetInt( data, param, "MIN" );
        if (min == 0)
          amy_IupSetAttribute( data, ctrl, "MASK", IUP_MASK_UINT );
        else
          amy_IupSetfAttribute( data, ctrl, "MASKINT", "%d:2147483647", min );
        amy_IupSetInt( data, ctrl, "SPINMIN", min );
        amy_IupSetAttribute( data, ctrl, "SPINMAX", "2147483647" );
      }
      else                             
      {
        amy_IupSetAttribute( data, ctrl, "SPINMIN", "-2147483647" );
        amy_IupSetAttribute( data, ctrl, "SPINMAX", "2147483647" );
        amy_IupSetAttribute( data, ctrl, "MASK", IUP_MASK_INT );
      }
    }

    if (iupAttribGetInt( data, param, "INTERVAL" ) || iupAttribGetInt( data, param, "ANGLE" ))
    {
      Ihandle *aux;

      if (iupAttribGetInt( data, param, "ANGLE" ))
      {
        aux = amy_IupCreate( data, "dial" );  /* Use amy_IupCreate to avoid depending on the amy_IupControls library */
        if (aux)  /* If amy_IupControls library is not available it will fail */
        {
          amy_IupSetDouble( data, aux, "VALUE", iupAttribGetDouble( data, param, "VALUE" )/IUP_RAD2DEG );
          amy_IupSetAttribute( data, aux, "SIZE", "50x10" );
        }
      }
      else
      {
        char *step;

        aux = amy_IupVal( data, "HORIZONTAL" );
        amy_IupStoreAttribute( data, aux, "MIN", iupAttribGet( data, param, "MIN" ));
        amy_IupStoreAttribute( data, aux, "MAX", iupAttribGet( data, param, "MAX" ));
        amy_IupStoreAttribute( data, aux, "VALUE", iupAttribGet( data, param, "VALUE" ));
        amy_IupSetAttribute( data, aux, "EXPAND", "HORIZONTAL" );
        iupAttribSet( data, param, "AUXCONTROL", (char*)aux );
        step = iupAttribGet( data, param, "STEP" );  /* STEP here is increment, in amy_IupVal step=increment/(max-min) */
        if (step)
          amy_IupSetDouble( data, aux, "STEP", iupAttribGetDouble( data, param, "STEP" )/(iupAttribGetDouble( data, param, "MAX" )-iupAttribGetDouble( data, param, "MIN" )));
        else if (iupStrEqual(type, "INTEGER" ))
          amy_IupSetDouble( data, aux, "STEP", 1.0f/(iupAttribGetDouble( data, param, "MAX" )-iupAttribGetDouble( data, param, "MIN" )));
      }

      if (aux)
      {
        amy_IupSetCallback( data, aux, "VALUECHANGED_CB", (Icallback)iParamValAction_CB );
        iupAttribSet( data, aux, "PARAM", (char*)param );
        iupAttribSet( data, aux, "CONTROL", (char*)ctrl );

        amy_IupAppend( data, box, aux );
      }
    }
  }

  if (ctrl) amy_IupStoreAttribute( data, ctrl, "TIP", iupAttribGet( data, param, "TIP" ));
  iupAttribSet( data, box, "PARAM", (char*)param );
  iupAttribSet( data, param, "CONTROL", (char*)ctrl );
  iupAttribSet( data, param, "LABEL", (char*)label );
  return box;
}

/*******************************************************************************************
                    Creates the Dialog and Normalize Sizes
*******************************************************************************************/

static int iParamBoxSetLabelAlignAttrib( struct libData *data, Ihandle *param_box, const char *value)
{
  int i, count = iupAttribGetInt( data, param_box, "PARAMCOUNT" );

  for (i = 0; i < count; i++)
  {
    Ihandle *param = (Ihandle*) iupAttribGetId( data, param_box, "PARAM", i );
    Ihandle *label = (Ihandle*) iupAttribGet( data, param, "LABEL" );
    amy_IupSetStrAttribute( data, label, "ALIGNMENT", value );
  }

  return 1;
}

static int iParamBoxSetModifiableAttrib( struct libData *data, Ihandle *param_box, const char *value)
{
  int i, count = iupAttribGetInt( data, param_box, "PARAMCOUNT" );

  for (i = 0; i < count; i++)
  {
    Ihandle *param = (Ihandle*) iupAttribGetId( data, param_box, "PARAM", i );
    Ihandle *label = (Ihandle*) iupAttribGet( data, param, "LABEL" );
    Ihandle *ctrl = (Ihandle*) iupAttribGet( data, param, "CONTROL" );
    Ihandle *aux = (Ihandle*) iupAttribGet( data, param, "AUXCONTROL" );

    amy_IupSetStrAttribute( data, label, "ACTIVE", value );

    if ( amy_IupClassMatch( data, ctrl, "text" ))
    {
      if (iupStrBoolean(value))
        amy_IupSetStrAttribute( data, ctrl, "READONLY", "No" );
      else
        amy_IupSetStrAttribute( data, ctrl, "READONLY", "Yes" );
    }
    else
      amy_IupSetStrAttribute( data, ctrl, "ACTIVE", value );

    if (aux)
      amy_IupSetStrAttribute( data, aux, "ACTIVE", value );
  }

  return 1;
}

static void iParamBoxNormalizeSize( struct libData *data, Ihandle** params, int count)
{
  int i, lbl_width;

  /* get the largest label size and set INDEX */
  lbl_width = 0;
  for (i = 0; i < count; i++)
  {
    int w = amy_IupGetInt( data, (Ihandle*) iupAttribGet( data, params[i], "LABEL" ), "NATURALSIZE" );
    if (w > lbl_width)
      lbl_width = w;
  }

  for (i = 0; i < count; i++)
  {
    if ( ! iupStrEqualNoCase(iupAttribGet( data, params[i], "DATATYPE" ), "NONE" ))
    {
      char *type = iupAttribGet( data, params[i], "TYPE" );
      if (iupStrEqual(type, "LIST" ))
      {
        /* set a minimum size for lists */
        Ihandle *ctrl = (Ihandle*) iupAttribGet( data, params[i], "CONTROL" );
        int charwidth = amy_IupGetInt( data, ctrl, "CHARSIZE" );
        if ( amy_IupGetInt( data, ctrl, "NATURALSIZE" ) * 4 < 50 * charwidth)
          amy_IupSetInt( data, ctrl, "RASTERSIZE", (50 * charwidth) / 4 );
      }
      else if (iupStrEqual(type, "BOOLEAN" ))
      {
        /* reserve enough space for both strings */
        Ihandle *ctrl = (Ihandle*) iupAttribGet( data, params[i], "CONTROL" );
        int wf = iupdrvFontGetStringWidth( data, ctrl, iupAttribGet( data, params[i], "FALSE" ));
        int wt = iupdrvFontGetStringWidth( data, ctrl, iupAttribGet( data, params[i], "TRUE" ));
        int w = amy_IupGetInt( data, ctrl, "NATURALSIZE" );
        int v = amy_IupGetInt( data, ctrl, "VALUE" );
        if (v) /* True */
        {
          int box = w - wt;
          wf += box;
          if (wf > w)
            amy_IupSetfAttribute( data, ctrl, "RASTERSIZE", "%dx", wf + 8 );
        }
        else
        {
          int box = w - wf;
          wt += box;
          if (wt > w)
            amy_IupSetfAttribute( data, ctrl, "RASTERSIZE", "%dx", wt + 8 );
        }
      }

      /* set the same size for all labels so they will align the controls column */
      amy_IupSetfAttribute( data, (Ihandle*) iupAttribGet( data, params[i], "LABEL" ), "RASTERSIZE", "%dx", lbl_width );
    }
  }
}

static Ihandle *iupParamBoxDlg( struct libData *data, Ihandle *param_box, const char *title)
{
  Ihandle *button1, *button2;
  Ihandle *dlg = amy_IupDialog( data, param_box );

  if ( ! iupAttribGetInt( data, param_box, "TEXTEXPAND" ))
  {
    amy_IupSetAttribute( data, dlg, "DIALOGFRAME", "YES" );  /* RESIZE=NO, MINBOX=NO and MAXBOX=NO */
    amy_IupSetAttribute( data, dlg, "DIALOGHINT", "YES" );  /* GTK Only */
  }
  else
  {
    amy_IupSetAttribute( data, dlg, "MINBOX", "NO" );
    amy_IupSetAttribute( data, dlg, "MAXBOX", "NO" );
  }

  button1 = (Ihandle*) iupAttribGet( data, param_box, "BUTTON1" );
  amy_IupSetStrAttribute( data, button1, "TITLE", "_@IUP_OK" );
  button2 = (Ihandle*) iupAttribGet( data, param_box, "BUTTON2" );
  amy_IupSetStrAttribute( data, button2, "TITLE", "_@IUP_CANCEL" );

  amy_IupSetAttributeHandle( data, dlg, "DEFAULTENTER", button1 );
  amy_IupSetAttributeHandle( data, dlg, "DEFAULTESC", button2 );

  amy_IupSetAttribute( data, dlg, "PARENTDIALOG", amy_IupGetGlobal( data, "PARENTDIALOG" ));
  amy_IupSetAttribute( data, dlg, "ICON", amy_IupGetGlobal( data, "ICON" ));
  amy_IupSetStrAttribute( data, dlg, "TITLE", (char*)title );
  amy_IupSetCallback( data, dlg, "CLOSE_CB", (Icallback)iParamDlgClose_CB );
  iupAttribSet( data, dlg, "PARAMBOX", (char*)param_box );  /* found by inheritance */

  return dlg;
}

static int iParamBoxCreateMethod( struct libData *data, Ihandle *param_box, void** vparams)
{
  Ihandle** params = (Ihandle**)vparams;
  Ihandle *button_1, *button_2, *button_3 = NULL,
    *params_vbox, *button_box, *ctrl_box;
  int i, p, count = 0, noframe = 0;

  if (vparams)
  {
    while (*vparams)
    {
      amy_IupAppend( data, param_box, (Ihandle*)*vparams );
      vparams++;
      count++;
    }
  }

  if (count == 0)
    return IUP_ERROR;

  button_1 = amy_IupButton( data, "_@IUP_APPLY", NULL );
  amy_IupSetStrAttribute( data, button_1, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
  amy_IupSetCallback( data, button_1, "ACTION", (Icallback)iParamButton1_CB );

  button_2 = amy_IupButton( data, "_@IUP_RESET", NULL );
  amy_IupSetStrAttribute( data, button_2, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
  amy_IupSetCallback( data, button_2, "ACTION", (Icallback)iParamButton2_CB );
  
  ctrl_box = amy_IupVbox( data, NULL );

  for (i = 0; i < count; i++)
  {
    char *type = iupAttribGet( data, params[i], "TYPE" );

    if (iupStrEqual(type, "BUTTONNAMES" ))
    {
      char *value = iupAttribGet( data, params[i], "BUTTON1" );
      if (value && *value) amy_IupSetStrAttribute( data, button_1, "TITLE", value );
      value = iupAttribGet( data, params[i], "BUTTON2" );
      if (value && *value) amy_IupSetStrAttribute( data, button_2, "TITLE", value );
      value = iupAttribGet( data, params[i], "BUTTON3" );
      if (value && *value) 
      {
        button_3 = amy_IupButton( data, value, NULL );
        amy_IupSetStrAttribute( data, button_3, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" ));
        amy_IupSetCallback( data, button_3, "ACTION", (Icallback)iParamButton3_CB );
      }

      amy_IupSetCallback( data, button_1, "DESTROY_CB", iParamDestroy_CB );
      iupAttribSet( data, button_1, "PARAM", (char*)params[i] );
    }
    else if (iupStrEqual(type, "HANDLE" ))
    {
      Ihandle *param_ih = (Ihandle*) iupAttribGet( data, params[i], "VALUE" );
      amy_IupSetCallback( data, param_ih, "DESTROY_CB", iParamDestroy_CB );
      iupAttribSet( data, param_ih, "PARAM", (char*)params[i] );
      amy_IupAppend( data, ctrl_box, param_ih );
    }
    else if (iupStrEqual(type, "PARAMBOX" ))
    {
      noframe = amy_IupGetInt( data, params[i], "NOFRAME" );
    }
    else
      amy_IupAppend( data, ctrl_box, iParamCreateCtrlBox( data, params[i], type ));

    if ( amy_IupGetInt( data, params[i], "TEXTEXPAND" ))
      iupAttribSet( data, param_box, "TEXTEXPAND", "Yes" );
  }

  button_box = amy_IupHbox( data,
    amy_IupFill( data ),
    button_1,
    button_2,
    button_3,
    NULL );
  amy_IupSetAttribute( data, button_box,"MARGIN","0x0" );
  amy_IupSetAttribute( data, button_box, "NORMALIZESIZE", "HORIZONTAL" );

  params_vbox = amy_IupVbox( data,
    noframe? ctrl_box: amy_IupFrame( data, ctrl_box ),
    button_box,
    NULL );
  amy_IupSetAttribute( data, params_vbox, "MARGIN", "10x10" );
  amy_IupSetAttribute( data, params_vbox, "GAP", "5" );
  amy_IupInsert( data, param_box, NULL, params_vbox ); /* it will be the first child */

  /* set INDEX */
  p = 0;
  for (i = 0; i < count; i++)
  {
    if ( ! iupStrEqualNoCase(iupAttribGet( data, params[i], "DATATYPE" ), "NONE" ))
    {
      iupAttribSetId( data, param_box, "PARAM", p, (char*)params[i] );
      iupAttribSetInt( data, params[i], "INDEX", p );
      p++;
    }
  }

  iupAttribSetInt( data, param_box, "PARAMCOUNT", p );

  iupAttribSet( data, param_box, "BUTTON1", (char*)button_1 );
  iupAttribSet( data, param_box, "BUTTON2", (char*)button_2 );
  iupAttribSet( data, param_box, "BUTTON3", (char*)button_3 );

  /* trick to update the label and text sizes */
  iupLayoutCompute( data, param_box );

  iParamBoxNormalizeSize( data, params, count );

  iupAttribSet( data, param_box, "PARAMBOX", (char*)param_box );  /* found by inheritance */

  return IUP_NOERROR;
}

/*******************************************************************************************
                    Parameter String Parsing
*******************************************************************************************/

static char *iParamStrGetNextItem(char *line, char sep, int *count)
{
  int i = 0;

  while (line[i] != '\n' && line[i] != 0)
  {
    if (line[i] == sep)
    {
      line[i] = 0;
      *count = i+1;
      return line;
    }

    i++;
  }

  /* last item may not have the separator */
  line[i] = 0;
  *count = i;
  return line;
}

static void iParamStrSetBoolNames( struct libData *data, char *extra, Ihandle *param)
{
  char *falsestr = NULL, *truestr = NULL;
  int count;

  if (extra)
  {
    falsestr = iParamStrGetNextItem(extra, ',', &count );  extra += count;
    truestr = iParamStrGetNextItem(extra, ',', &count );
  }

  if (falsestr && truestr)
  {
    iupAttribSetStr( data, param, "TRUE", truestr );
    iupAttribSetStr( data, param, "FALSE", falsestr );
  }
  else
  {
    iupAttribSetStr( data, param, "TRUE", "" );
    iupAttribSetStr( data, param, "FALSE", "" );
  }
}

static void iParamStrSetInterval( struct libData *data, char *extra, Ihandle *param)
{
  char *min, *max, *step;
  int count;

  if ( ! extra)
    return;

  min = iParamStrGetNextItem(extra, ',', &count );  extra += count;
  max = iParamStrGetNextItem(extra, ',', &count );  extra += count;
  step = iParamStrGetNextItem(extra, ',', &count );  

  if (max[0] )
  {
    iupAttribSet( data, param, "INTERVAL", "Yes" );
    iupAttribSetStr( data, param, "MIN", min );
    iupAttribSetStr( data, param, "MAX", max );
    if (step[0] )
      iupAttribSetStr( data, param, "STEP", step );
  }
  else
  {
    iupAttribSet( data, param, "PARTIAL", "Yes" );
    iupAttribSetStr( data, param, "MIN", min );
  }
}

static void iParamStrSetFileOptions( struct libData *data, char *extra, Ihandle *param)
{
  char *type, *filter, *directory, *nochangedir, *nooverwriteprompt;
  int count;

  if ( ! extra)
    return;

  type = iParamStrGetNextItem(extra, '|', &count );  extra += count;
  filter = iParamStrGetNextItem(extra, '|', &count );  extra += count;
  directory = iParamStrGetNextItem(extra, '|', &count );  extra += count;
  nochangedir = iParamStrGetNextItem(extra, '|', &count );  extra += count;
  nooverwriteprompt = iParamStrGetNextItem(extra, '|', &count );  extra += count;

  iupAttribSetStr( data, param, "DIALOGTYPE", type );
  iupAttribSetStr( data, param, "FILTER", filter );
  iupAttribSetStr( data, param, "DIRECTORY", directory );
  iupAttribSetStr( data, param, "NOCHANGEDIR", nochangedir );
  iupAttribSetStr( data, param, "NOOVERWRITEPROMPT", nooverwriteprompt );
}

static void iParamStrSetMultiOptions( struct libData *data, char *extra, Ihandle *param)
{
  if ( ! extra)
    return;

  amy_IupSetAttributes( data, param, extra );
}

static void iParamStrSetButtonNames( struct libData *data, char *extra, Ihandle *param)
{
  char *button1, *button2, *button3;
  int count;

  if ( ! extra)
    return;

  button1 = iParamStrGetNextItem(extra, ',', &count );  extra += count;
  button2 = iParamStrGetNextItem(extra, ',', &count );  extra += count;
  button3 = iParamStrGetNextItem(extra, ',', &count );  extra += count;

  iupAttribSetStr( data, param, "BUTTON1", button1 );
  iupAttribSetStr( data, param, "BUTTON2", button2 );
  iupAttribSetStr( data, param, "BUTTON3", button3 );
}

static void iParamStrSetListItems( struct libData *data, char *extra, Ihandle *param )
{
  int i = 0, count;
  char *item;

  if ( ! extra)
    return;

  item = iParamStrGetNextItem(extra, '|', &count );  extra += count;
  while (*item)
  {
    iupAttribSetStrId( data, param, "", i, item );

    item = iParamStrGetNextItem(extra, '|', &count );  extra += count;
    i++;
  }

  iupAttribSetId( data, param, "", i, "" );
}

static char *iParamStrGetExtra( char *line, char start, char end, int *count )
{
  int i = 0, end_pos = -1;

  if (*line != start)
  {
    *count = 0;
    return NULL;
  }
  line++; /* skip start */

  while (line[i] != '\n' && line[i] != 0)
  {
    if (line[i] == end)
      end_pos = i;

    i++;
  }

  if (end_pos != -1)
  {
    line[end_pos] = 0;
    *count = 1+end_pos+1;
    return line;
  }
  else
  {
    *count = 0;
    return NULL;
  }
}

static int iParamStrLineSize(const char *format)
{
  int i = 0;
  while (format[i] != '\n' && format[i] != 0)
  {
    i++;
    if (i > 4094)   /* to avoid being bigger than the local array */
      break;
  }
  return i + 1;
}

static void iParamStrCopyLine(char *line, const char *format)
{
  int i = 0;
  while (format[i] != '\n' && format[i] != 0)
  {
    line[i] = format[i];
    i++;
    if (i > 4094)   /* to avoid being bigger than the local array */
      break;
  }
  line[i] = '\n';
  line[i+1] = 0;
}

static char *iParamStrGetType(const char *format)
{
  char *type = strchr(format, '%' );
  while (type && *(type+1)=='%')
    type = strchr(type+2, '%' );
  return type;
}

/* Used in amy_IupLua */
IUP_SDK_API char iupGetParamType(const char *format, int *line_size)
{
  char *type = iParamStrGetType(format );
  char *line_end = strchr(format, '\n' );
  if (line_end)
    *line_size = (int)(line_end-format) + 1;  /* include line separator */
  if (type)
    return *(type+1 );  /* skip separator */
  else
    return 0;
}

static char *iParamStrGetTitle(char *line_ptr, int count)
{
  int i, n;
  char *title = line_ptr;
  title[count] = 0;
  n = -1;
  for (i=0; i<count; i++)
  {
    if (title[i] != '%')
      n++;
    else /* if (title[i+1] == '%')  if equal to %, next is a %, because we are inside title only */
    {
      n++;
      i++;  /* skip second % */
    }

    if (i != n)  /* copy only if there is a second % */
      title[n] = title[i];
  }
  if (i-1 != n)
    title[n+1] = 0;
  return title;
}

static int iParamCreateMethod( struct libData *data, Ihandle *param, void** params)
{
  const char *format = NULL;
  char line[4096];
  char *line_ptr = &line[0], *title, *type, *tip, *extra, *mask;
  int count;

  if (params && params[0] )
    format = (char*)(params[0] );

  if ( ! format || format[0] == 0)
    return IUP_ERROR;

  iParamStrCopyLine(line, format );

  type = iParamStrGetType(line_ptr );
  if ( ! type)
    return IUP_ERROR;

  count = (int)(type-line_ptr );
  title = iParamStrGetTitle(line_ptr, count );
  line_ptr += count;

  type++; /* skip separator */
  line_ptr += 2;

  if (title[0] == '\t')
  {
    int indent = 0;
    while (title[0] == '\t')
    {
      indent++;
      title++;
    }
    iupAttribSetInt( data, param, "INDENT", indent );
  }
  iupAttribSetStr( data, param, "TITLE", title );
  
/**********************************************************************************
  REMEMBER: if a new parameter type is added
            then amy_IupLua must be also updated.
 **********************************************************************************/

  switch(*type)
  {
  case 'b':
    iupAttribSet( data, param, "TYPE", "BOOLEAN" );
    iupAttribSet( data, param, "DATATYPE", "INT" );
    extra = iParamStrGetExtra(line_ptr, '[', ']', &count );  line_ptr += count;
    iParamStrSetBoolNames( data, extra, param );
    break;
  case 'l':
    iupAttribSet( data, param, "TYPE", "LIST" );
    iupAttribSet( data, param, "DATATYPE", "INT" );
    extra = iParamStrGetExtra(line_ptr, '|', '|', &count );  line_ptr += count;
    iParamStrSetListItems( data, extra, param );
    break;
  case 'o':
    iupAttribSet( data, param, "TYPE", "OPTIONS" );
    iupAttribSet( data, param, "DATATYPE", "INT" );
    extra = iParamStrGetExtra(line_ptr, '|', '|', &count );  line_ptr += count;
    iParamStrSetListItems( data, extra, param );
    break;
  case 'A':
    iupAttribSet( data, param, "TYPE", "REAL" );
    iupAttribSet( data, param, "DATATYPE", "DOUBLE" );
    iupAttribSet( data, param, "ANGLE", "Yes" );
    extra = iParamStrGetExtra(line_ptr, '[', ']', &count );  line_ptr += count;
    iParamStrSetInterval( data, extra, param );
    break;
  case 'a':
    iupAttribSet( data, param, "TYPE", "REAL" );
    iupAttribSet( data, param, "DATATYPE", "FLOAT" );
    iupAttribSet( data, param, "ANGLE", "Yes" );
    extra = iParamStrGetExtra(line_ptr, '[', ']', &count );  line_ptr += count;
    iParamStrSetInterval( data, extra, param );
    break;
  case 'm':
    iupAttribSet( data, param, "MULTILINE", "Yes" );
    /* continue */
  case 's':
    iupAttribSet( data, param, "TYPE", "STRING" );
    iupAttribSet( data, param, "DATATYPE", "STRING" );
    mask = iParamStrGetNextItem(line_ptr, '{', &count );  
    if (*mask) 
      iupAttribSetStr( data, param, "MASK", mask );
    line_ptr += count-1; /* ignore the fake separator */
    line_ptr[0] = '{';   /* restore possible separator */
    break;
  case 'i':
    iupAttribSet( data, param, "TYPE", "INTEGER" );
    iupAttribSet( data, param, "DATATYPE", "INT" );
    extra = iParamStrGetExtra(line_ptr, '[', ']', &count );  line_ptr += count;
    iParamStrSetInterval( data, extra, param );
    break;
  case 'R':
    iupAttribSet( data, param, "TYPE", "REAL" );
    iupAttribSet( data, param, "DATATYPE", "DOUBLE" );
    extra = iParamStrGetExtra(line_ptr, '[', ']', &count );  line_ptr += count;
    iParamStrSetInterval( data, extra, param );
    break;
  case 'r':
    iupAttribSet( data, param, "TYPE", "REAL" );
    iupAttribSet( data, param, "DATATYPE", "FLOAT" );
    extra = iParamStrGetExtra(line_ptr, '[', ']', &count );  line_ptr += count;
    iParamStrSetInterval( data, extra, param );
    break;
  case 'd':
    iupAttribSet( data, param, "TYPE", "DATE" );
    iupAttribSet( data, param, "DATATYPE", "STRING" );
    extra = iParamStrGetExtra(line_ptr, '[', ']', &count );  line_ptr += count;
    iParamStrSetMultiOptions( data, extra, param );
    break;
  case 'f':
    iupAttribSet( data, param, "TYPE", "FILE" );
    iupAttribSet( data, param, "DATATYPE", "STRING" );
    extra = iParamStrGetExtra(line_ptr, '[', ']', &count );  line_ptr += count;
    iParamStrSetFileOptions( data, extra, param );
    break;
  case 'x':
    iupAttribSet( data, param, "TYPE", "PARAMBOX" );
    iupAttribSet( data, param, "DATATYPE", "NONE" );
    extra = iParamStrGetExtra(line_ptr, '[', ']', &count );  line_ptr += count;
    iParamStrSetMultiOptions( data, extra, param );
    break;
  case 'n':
    iupAttribSet( data, param, "TYPE", "FONT" );
    iupAttribSet( data, param, "DATATYPE", "STRING" );
    break;
  case 'c':
    iupAttribSet( data, param, "TYPE", "COLOR" );
    iupAttribSet( data, param, "DATATYPE", "STRING" );
    break;
  case 't':
    iupAttribSet( data, param, "TYPE", "SEPARATOR" );
    iupAttribSet( data, param, "DATATYPE", "NONE" );
    break;
  case 'u':
    iupAttribSet( data, param, "TYPE", "BUTTONNAMES" );
    iupAttribSet( data, param, "DATATYPE", "NONE" );
    extra = iParamStrGetExtra(line_ptr, '[', ']', &count );  line_ptr += count;
    iParamStrSetButtonNames( data, extra, param );
    break;
  case 'h':
    iupAttribSet( data, param, "TYPE", "HANDLE" );
    iupAttribSet( data, param, "DATATYPE", "HANDLE" );
    break;
  default:
    return IUP_ERROR;
  }

  tip = iParamStrGetExtra(line_ptr, '{', '}', &count );
  if (tip)
  {
    iupStrToUnix(tip );
    iupAttribSetStr( data, param, "TIP", tip );
  }

  amy_IupSetAttribute( data, param, "FLOATING", "IGNORE" );
  return IUP_NOERROR;
}

/* Used in amy_IupLua also */
IUP_SDK_API int iupGetParamCount( struct libData *data, const char *format, int *param_extra )
{
  int param_count = 0, extra = 0;
  const char *s = format;

  *param_extra = 0;
  while (*s)
  {
    if (*s == '%' && *(s + 1) == 't')  /* do not count separator lines */
    {
      extra = 1;
      (*param_extra)++;
    }

    if (*s == '%' && *(s + 1) == 'u')  /* do not count BUTTONNAMES lines */
    {
      extra = 1;
      (*param_extra)++;
    }

    if (*s == '\n')
    {
      if (extra)
        extra = 0;
      else
        param_count++;
    }

    s++;
  }

  return param_count;
}


/*******************************************************************************************
                    Dialog Functions
*******************************************************************************************/


IUP_API int amy_IupGetParamv( struct libData *data, const char *title, Iparamcb action, void* user_data, const char *format, int param_count, int param_extra, void** param_data )
{
  Ihandle *dlg, *param_box, **params;
  int i, line_size, p, count;

  iupASSERT(title && format );
  if ( ! title || !format)
    return 0;

  count = param_count + param_extra;
  params = malloc((count+1)*sizeof(Ihandle*));

  p = 0;
  for (i = 0; i < count; i++)
  {
    char *data_type;

    params[i] = amy_IupParam( data, format );
    iupASSERT(params[i] );
    if ( ! params[i] )
    {
      free( params );
      return 0;
    }

    data_type = iupAttribGet( data, params[i], "DATATYPE" );
    if (iupStrEqualNoCase(data_type, "FLOAT" ))
    {
      float *data_float = (float*)(param_data[p] );
      if ( ! data_float) { free( params ); return 0; }
      iupAttribSetFloat( data, params[i], "VALUE", *data_float );
      p++;
    }
    else if (iupStrEqualNoCase(data_type, "DOUBLE" ))
    {
      double *data_double = (double*)(param_data[p] );
      if ( ! data_double) { free( params ); return 0; }
      iupAttribSetDouble( data, params[i], "VALUE", *data_double );
      p++;
    }
    else if (iupStrEqualNoCase(data_type, "INT" ))
    {
      int *data_int = (int*)(param_data[p] );
      if ( ! data_int) { free( params ); return 0; }
      iupAttribSetInt( data, params[i], "VALUE", *data_int );
      p++;
    }
    else if (iupStrEqualNoCase(data_type, "STRING" ))
    {
      char *data_str = (char*)(param_data[p] );
      if ( ! data_str) { free( params ); return 0; }
      iupAttribSetStr( data, params[i], "VALUE", data_str );
      p++;
    }
    else if (iupStrEqualNoCase(data_type, "HANDLE" ))  /* Input Only */
    {
      Ihandle *data_ih = (Ihandle*)(param_data[p] );
      if ( ! data_ih) { free( params ); return 0; }
      iupAttribSet( data, params[i], "VALUE", (char*)data_ih );
      p++;
    }

    line_size = iParamStrLineSize(format );
    format += line_size;
  }
  params[i] = NULL;
  param_box = amy_IupParamBoxv( data, params );
  amy_IupSetCallback( data, param_box, "PARAM_CB", (Icallback)action );
  iupAttribSet( data, param_box, "USERDATA", (char*)user_data );

  dlg = iupParamBoxDlg( data, param_box, title );

  if (action)
  {
    action(param_box, IUP_GETPARAM_MAP, user_data );

    amy_IupMap( data, dlg );

    action(param_box, IUP_GETPARAM_INIT, user_data );
  }

  amy_IupPopup( data, dlg, IUP_CENTERPARENT, IUP_CENTERPARENT );

  if ( !  amy_IupGetInt( data, param_box, "STATUS" ))
  {
    amy_IupDestroy( data, dlg );
    free( params ); 
    return 0;
  }
  else
  {
    p = 0;
    for (i = 0; i < count; i++)
    {
      Ihandle *param = params[i];
      char *data_type = iupAttribGet( data, param, "DATATYPE" );
      if (iupStrEqualNoCase(data_type, "INT" ))
      {
        int *data_int = (int*)(param_data[p] );
        *data_int = iupAttribGetInt( data, param, "VALUE" );
        p++;
      }
      else if (iupStrEqualNoCase(data_type, "FLOAT" ))
      {
        float *data_float = (float*)(param_data[p] );
        *data_float = iupAttribGetFloat( data, param, "VALUE" );
        p++;
      }
      else if (iupStrEqualNoCase(data_type, "DOUBLE" ))
      {
        double *data_double = (double*)(param_data[p] );
        *data_double = iupAttribGetDouble( data, param, "VALUE" );
        p++;
      }
      else if (iupStrEqualNoCase(data_type, "STRING" ))
      {
        char *data_str = (char*)(param_data[p] );
        int max_str = iupAttribGetInt( data, param, "MAXSTR" );
        if ( ! max_str)
        {
          max_str = 512;
          if (iupStrEqual(iupAttribGet( data, param, "TYPE" ), "FILE" ))
            max_str = 4096;
          else if (iupStrEqual(iupAttribGet( data, param, "TYPE" ), "STRING" ) && iupAttribGetInt( data, param, "MULTILINE" ))
            max_str = 10240;
        }
        iupStrCopyN(data_str, max_str, iupAttribGet( data, param, "VALUE" ));
        p++;
      }
    }

    amy_IupDestroy( data, dlg );
    free( params );
    return 1;
  }
}

IUP_API int amy_IupGetParamV( struct libData *data, const char *title, Iparamcb action, void* user_data, const char *format, va_list arglist)
{
  int param_count, param_extra, i, ret;
  void** param_data;

  param_count = iupGetParamCount( data, format, & param_extra );

  param_data = malloc(param_count*sizeof(void*));

  for (i = 0; i < param_count; i++)
  {
    param_data[i] = (void*)(va_arg(arglist, void*));
  }

  ret = amy_IupGetParamv( data, title, action, user_data, format, param_count, param_extra, param_data );

  free( param_data );
  return ret;
}

IUP_API int amy_IupGetParam( struct libData *data, const char *title, Iparamcb action, void* user_data, const char *format, ... )
{
  va_list arglist;
  int ret;

  va_start( arglist, format );
  ret = amy_IupGetParamV( data, title, action, user_data, format, arglist );
  va_end( arglist );

  return ret;
}


/*******************************************************************************/


IUP_API Ihandle *amy_IupParam( struct libData *data, const char *format )
{
  void *params[2];
  params[0] = (void*)format;
  params[1] = NULL;
  return amy_IupCreatev( data, "param", params );
}

Iclass *iupParamNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, NULL );

  ic->name = "param";
  ic->format = "s"; /* one string */
  ic->nativetype = IUP_TYPEVOID;
  ic->childtype = IUP_CHILDNONE;
  ic->is_interactive = 0;

  ic->New = iupParamNewClass;
  ic->Create = iParamCreateMethod;
  ic->Map = iupBaseTypeVoidMapMethod;

  /* Base Callbacks */
  iupBaseRegisterBaseCallbacks( data, ic );

  iupClassRegisterAttribute( data, ic, "LABEL", NULL, NULL, NULL, NULL, IUPAF_IHANDLE|IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CONTROL", NULL, NULL, NULL, NULL, IUPAF_IHANDLE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "AUXCONTROL", NULL, NULL, NULL, NULL, IUPAF_IHANDLE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "INDEX", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "TITLE", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "INDENT", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "TYPE", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DATATYPE", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MULTILINE", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "ANGLE", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "TRUE", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "FALSE", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "INTERVAL", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MIN", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MAX", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "STEP", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "PARTIAL", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DIALOGTYPE", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "FILTER", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "DIRECTORY", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "NOCHANGEDIR", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "NOOVERWRITEPROMPT", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "BUTTON1", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "BUTTON2", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "BUTTON3", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MASK", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "TIP", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "VALUE", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "NOFRAME", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "PRECISION", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );

  return ic;
}

IUP_API Ihandle *amy_IupParamBoxv( struct libData *data, Ihandle **children)
{
  return amy_IupCreatev( data, "parambox", (void**)children );
}

IUP_API Ihandle *amy_IupParamBoxV( struct libData *data, Ihandle *child, va_list arglist)
{
  return amy_IupCreateV( data, "parambox", child, arglist );
}

IUP_API Ihandle *amy_IupParamBox( struct libData *data, Ihandle * child, ...)
{
  Ihandle *ih;

  va_list arglist;
  va_start(arglist, child );
  ih = amy_IupCreateV( data, "parambox", child, arglist );
  va_end(arglist );

  return ih;
}

static void iParamBoxComputeNaturalSizeMethod( struct libData *data, Ihandle *ih, int *w, int *h, int *children_expand)
{
  Ihandle *child = ih->firstchild;  /* only for the VBOX */
  if (child)
  {
    /* update child natural size only, when not canvas box */
    iupBaseComputeNaturalSize( data, child );

    *children_expand = child->expand;
    *w = child->naturalwidth;
    *h = child->naturalheight;
  }
}

static void iParamBoxSetChildrenCurrentSizeMethod( struct libData *data, Ihandle *ih, int shrink)
{
  Ihandle *child = ih->firstchild;  /* only for the VBOX */
  if (child)
    iupBaseSetCurrentSize( data, child, ih->currentwidth, ih->currentheight, shrink );
}

static void iParamBoxSetChildrenPositionMethod( struct libData *data, Ihandle *ih, int x, int y)
{
  Ihandle *child = ih->firstchild;  /* only for the VBOX */
  if (child)
    iupBaseSetPosition( data, child, x, y );
}

Iclass *iupParamBoxNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, NULL );

  ic->name = "parambox";
  ic->cons = "ParamBox";
  ic->format = "g"; /* array of Ihandle */
  ic->nativetype = IUP_TYPEVOID;
  ic->childtype = IUP_CHILDMANY;  /* can have children */
  ic->is_interactive = 0;

  ic->New = iupParamBoxNewClass;
  ic->Create = iParamBoxCreateMethod;
  ic->Map = iupBaseTypeVoidMapMethod;

  ic->ComputeNaturalSize = iParamBoxComputeNaturalSizeMethod;
  ic->SetChildrenCurrentSize = iParamBoxSetChildrenCurrentSizeMethod;
  ic->SetChildrenPosition = iParamBoxSetChildrenPositionMethod;

  /* Base Callbacks */
  iupBaseRegisterBaseCallbacks( data, ic );

  /* Callbacks */
  iupClassRegisterCallback( data, ic, "PARAM_CB", "iV" );

  /* Common */
  iupBaseRegisterCommonAttrib( data, ic );

  /* Base Container */
  iupClassRegisterAttribute( data, ic, "EXPAND", iupBaseContainerGetExpandAttrib, NULL, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CLIENTSIZE", iupBaseGetClientSizeAttrib, NULL, NULL, NULL, IUPAF_READONLY | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CLIENTOFFSET", iupBaseGetClientOffsetAttrib, NULL, NULL, NULL, IUPAF_READONLY | IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "STATUS", NULL, NULL, NULL, NULL, IUPAF_READONLY | IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "USERDATA", NULL, NULL, NULL, NULL, IUPAF_NO_STRING | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "LABELALIGN", NULL, iParamBoxSetLabelAlignAttrib, IUPAF_SAMEASSYSTEM, "ALEFT", IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "MODIFIABLE", NULL, iParamBoxSetModifiableAttrib, IUPAF_SAMEASSYSTEM, "ALEFT", IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );

  /* ATTENTION: can NOT set IUPAF_READONLY if get is not defined when attribute is used before map. 
     In iupAttribUpdate (called by amy_IupMap) store will be 0 for read-only attributes, then attribute will be removed from the hash table.

     The following are documented as read-only:
  */
  iupClassRegisterAttribute( data, ic, "PARAMCOUNT", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "BUTTON1", NULL, NULL, NULL, NULL, IUPAF_IHANDLE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "BUTTON2", NULL, NULL, NULL, NULL, IUPAF_IHANDLE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "BUTTON3", NULL, NULL, NULL, NULL, IUPAF_IHANDLE | IUPAF_NO_INHERIT );

  return ic;
}
