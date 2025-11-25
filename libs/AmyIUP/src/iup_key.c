
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
 * \brief Manage keys encoding and decoding.
 *
 * See Copyright Notice in "iup.h"
 */

#include <memory.h>
#include <stdio.h> 
#include <string.h> 

#include "iup.h"
#include "iupkey.h"
#include "iupcbs.h"

#include "iup_key.h"
#include "iup_str.h"
#include "iup_object.h"
#include "iup_drv.h"
#include "iup_focus.h"
#include "iup_attrib.h"

#endif

typedef struct _IkeyMapASCII {
  const char *name;
  unsigned char mod;
} IkeyMapASCII;

static IkeyMapASCII ikey_map_ascii[126-32+1] = {  /* from 32 to 126 (inclusive) */
  {"K_SP",                  0},
  {"K_exclam",              2}, /* NO shift */
  {"K_quotedbl",            2}, /* NO shift */
  {"K_numbersign",          2}, /* NO shift */
  {"K_dollar",              2}, /* NO shift */
  {"K_percent",             2}, /* NO shift */
  {"K_ampersand",           2}, /* NO shift */
  {"K_apostrophe",          2}, /* NO shift */
  {"K_parentleft",          2}, /* NO shift */
  {"K_parentright",         2}, /* NO shift */
  {"K_asterisk",            0},                                 /* when in the numeric keypad have all the modifiers */
  {"K_plus",                0},
  {"K_comma",               0},
  {"K_minus",               0},
  {"K_period",              0},
  {"K_slash",               0},
  {"K_0",                   2}, /* NO shift */
  {"K_1",                   2}, /* NO shift */
  {"K_2",                   2}, /* NO shift */
  {"K_3",                   2}, /* NO shift */
  {"K_4",                   2}, /* NO shift */
  {"K_5",                   2}, /* NO shift */
  {"K_6",                   2}, /* NO shift */
  {"K_7",                   2}, /* NO shift */
  {"K_8",                   2}, /* NO shift */
  {"K_9",                   2}, /* NO shift */
  {"K_colon",               2}, /* NO shift */
  {"K_semicolon",           2}, /* NO shift */
  {"K_less",                2}, /* NO shift */
  {"K_equal",               2}, /* NO shift */
  {"K_greater",             2}, /* NO shift */
  {"K_question",            2}, /* NO shift */
  {"K_at",                  2}, /* NO shift */
  {"K_A",                   2}, /* NO shift */
  {"K_B",                   2}, /* NO shift */
  {"K_C",                   2}, /* NO shift */
  {"K_D",                   2}, /* NO shift */
  {"K_E",                   2}, /* NO shift */
  {"K_F",                   2}, /* NO shift */
  {"K_G",                   2}, /* NO shift */
  {"K_H",                   2}, /* NO shift */
  {"K_I",                   2}, /* NO shift */
  {"K_J",                   2}, /* NO shift */
  {"K_K",                   2}, /* NO shift */
  {"K_L",                   2}, /* NO shift */
  {"K_M",                   2}, /* NO shift */
  {"K_N",                   2}, /* NO shift */
  {"K_O",                   2}, /* NO shift */
  {"K_P",                   2}, /* NO shift */
  {"K_Q",                   2}, /* NO shift */
  {"K_R",                   2}, /* NO shift */
  {"K_S",                   2}, /* NO shift */
  {"K_T",                   2}, /* NO shift */
  {"K_U",                   2}, /* NO shift */
  {"K_V",                   2}, /* NO shift */
  {"K_W",                   2}, /* NO shift */
  {"K_X",                   2}, /* NO shift */
  {"K_Y",                   2}, /* NO shift */
  {"K_Z",                   2}, /* NO shift */
  {"K_bracketleft",         2}, /* NO shift */
  {"K_backslash",           2}, /* NO shift */
  {"K_bracketright",        2}, /* NO shift */
  {"K_circum",              2}, /* NO shift */
  {"K_underscore",          2}, /* NO shift */
  {"K_grave",               2}, /* NO shift */
  {"K_a",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_b",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_c",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_d",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_e",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_f",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_g",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_h",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_i",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_j",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_k",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_l",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_m",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_n",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_o",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_p",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_q",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_r",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_s",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_t",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_u",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_v",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_w",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_x",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_y",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_z",                   1}, /* NO shift,ctrl,alt,sys */
  {"K_braceleft",           2}, /* NO shift */
  {"K_bar",                 2}, /* NO shift */
  {"K_braceright",          2}, /* NO shift */
  {"K_tilde",               2}, /* NO shift */
};

static const char *ikey_map_ext[256];

void iupKeyInit( struct libData *data )
{
	memset((void*)data->ikey_map_ext, 0, 256*sizeof(char*));

	data->ikey_map_ext[0x0B] = "K_MIDDLE";
	data->ikey_map_ext[0x13] = "K_PAUSE";
	data->ikey_map_ext[0x14] = "K_SCROLL";
	data->ikey_map_ext[0x1B] = "K_ESC";
	data->ikey_map_ext[0x50] = "K_HOME";
	data->ikey_map_ext[0x51] = "K_LEFT";
	data->ikey_map_ext[0x52] = "K_UP";
	data->ikey_map_ext[0x53] = "K_RIGHT";
	data->ikey_map_ext[0x54] = "K_DOWN";
	data->ikey_map_ext[0x55] = "K_PGUP";
	data->ikey_map_ext[0x56] = "K_PGDN";
	data->ikey_map_ext[0x57] = "K_END";
	data->ikey_map_ext[0x61] = "K_Print";
	data->ikey_map_ext[0x63] = "K_INS";
	data->ikey_map_ext[0x67] = "K_Menu";
	data->ikey_map_ext[0x7F] = "K_NUM";

	data->ikey_map_ext[0xBE] = "K_F1";
	data->ikey_map_ext[0xBF] = "K_F2";
	data->ikey_map_ext[0xC0] = "K_F3";
	data->ikey_map_ext[0xC1] = "K_F4";
	data->ikey_map_ext[0xC2] = "K_F5";
	data->ikey_map_ext[0xC3] = "K_F6";
	data->ikey_map_ext[0xC4] = "K_F7";
	data->ikey_map_ext[0xC5] = "K_F8";
	data->ikey_map_ext[0xC6] = "K_F9";
	data->ikey_map_ext[0xC7] = "K_F10";
	data->ikey_map_ext[0xC8] = "K_F11";
	data->ikey_map_ext[0xC9] = "K_F12";

	data->ikey_map_ext[0xE1] = "K_LSHIFT";
	data->ikey_map_ext[0xE2] = "K_RSHIFT";
	data->ikey_map_ext[0xE3] = "K_LCTRL";
	data->ikey_map_ext[0xE4] = "K_RCTRL";
	data->ikey_map_ext[0xE5] = "K_CAPS";
	data->ikey_map_ext[0xE9] = "K_LALT";
	data->ikey_map_ext[0xEA] = "K_RALT";

	data->ikey_map_ext[0xFF] = "K_DEL";
}

static const char *iKeyBaseCodeToName(int code, unsigned char *mod)
{
  *mod = 0;  /* all modifiers */
  if (code == K_BS)
    return "K_BS";
  if (code == K_TAB)
    return "K_TAB";
  if (code == K_CR)
    return "K_CR";
  if (code < 32 || code==127)
    return NULL;
  if (code >= 32 && code <= 126)
  {
    *mod = ikey_map_ascii[code-32].mod;
    return ikey_map_ascii[code-32].name;
  }
  if (code <= 0xFFFF && ((0xFF00&code) == 0xFF00))
  {
    if ( ikey_map_ext[0x00FF&code] )
    {
      if ((code >= K_LSHIFT && code <= K_RALT) ||
           code == K_NUM || code == K_SCROLL)
        *mod = 1;  /* NO shift,ctrl,alt,sys */
      return ikey_map_ext[0x00FF&code];
    }
  }
  if (code == K_ccedilla)
  {
    *mod = 1; /* NO shift,ctrl,alt,sys */
    return "K_ccedilla";
  }
  if (code == K_Ccedilla)
  {
    *mod = 2; /* NO shift */
    return "K_Ccedilla";
  }
  if (code == K_acute)
  {
    *mod = 1; /* NO shift,ctrl,alt,sys */
    return "K_acute";
  }
  if (code == K_diaeresis)
  {
    *mod = 1; /* NO shift,ctrl,alt,sys */
    return "K_diaeresis";
  }
  return NULL;
}

#define iStrUpper(_c)  ((_c >= 'a' && _c <= 'z')? (_c - 'a') + 'A': _c)

#define iKeyMakeXName(_name, _prefix, _base_name) \
{                                                 \
  strcpy(_name, _prefix );                         \
  _name[3] = iStrUpper(_base_name[2] );            \
  strcpy(_name+4, _base_name+3 );                  \
}

#define iKeyReturnXName(_prefix, _base_name) \
{                                            \
  static char name[30];                      \
  iKeyMakeXName( name, _prefix, _base_name );  \
  return name;                               \
}

IUP_SDK_API char *iupKeyCodeToName( struct libData *data, int code )
{
  unsigned char mod = 0;
  const char *base_name;

  base_name = iKeyBaseCodeToName(iup_XkeyBase(code), &mod );
  if ( ! base_name)
  {
    static char code_name[30];
    sprintf(code_name, "K_0x%X", iup_XkeyBase(code));
    base_name = code_name;
  }

  if ( iup_XkeyBase(code)==code)  /* no modifiers */
    return (char*)base_name;

  if ( iup_isShiftXkey(code) && mod==0)
    iKeyReturnXName("K_s", base_name );

  if (mod==1)
    return (char*)base_name;

  if ( iup_isCtrlXkey(code)) 
    iKeyReturnXName("K_c", base_name );
  if ( iup_isAltXkey(code))  
    iKeyReturnXName("K_m", base_name );
  if ( iup_isSysXkey(code))
    iKeyReturnXName("K_y", base_name );

  return (char*)base_name;
}

static void iKeyCallFunc( struct libData *data, void (*func)(const char *name, int code, void *user_data), void *user_data, const char *name, int code, unsigned char mod)
{
  char mod_name[30];

  func( name, code, user_data );

  if (mod==0)
  {
    iKeyMakeXName(mod_name, "K_s", name );
    func(mod_name, iup_XkeyShift(code), user_data );
  }

  if (mod!=1) 
  {
    iKeyMakeXName(mod_name, "K_c", name );
    func(mod_name, iup_XkeyCtrl(code), user_data );

    iKeyMakeXName(mod_name, "K_m", name );
    func(mod_name, iup_XkeyAlt(code), user_data );

    iKeyMakeXName(mod_name, "K_y", name );
    func(mod_name, iup_XkeySys(code), user_data );
  }
}

IUP_SDK_API void iupKeyForEach( struct libData *data, void(*func)(struct libData *data, const char *name, int code, void *user_data), void *user_data)
{
  /* Used only by the amy_IupLua binding. */
  int code, map;

  iKeyCallFunc( data, func, user_data, "K_BS", K_BS, 0 );
  iKeyCallFunc( data, func, user_data, "K_TAB", K_TAB, 0 );
  iKeyCallFunc( data, func, user_data, "K_CR", K_CR, 0 );

  for (code=32; code <= 126; code++)
    iKeyCallFunc( data, func, user_data, ikey_map_ascii[code-32].name, code, ikey_map_ascii[code-32].mod );

  for (map=0; map < 256; map++)
  {
    if ( ikey_map_ext[map] )
    {
      unsigned char mod = 0;

      if (((0xFF00|map) >= K_LSHIFT && (0xFF00|map) <= K_RALT) ||
           (0xFF00|map) == K_NUM || (0xFF00|map) == K_SCROLL)
        mod=1;  /* NO shift,ctrl,alt,sys */

      iKeyCallFunc( data, func, user_data, ikey_map_ext[map], 0xFF00|map, mod );
    }
  }

  iKeyCallFunc( data, func, user_data, "K_ccedilla", K_ccedilla, 1 );  /* NO modifiers */
  iKeyCallFunc( data, func, user_data, "K_Ccedilla", K_Ccedilla, 2 );  /* NO shift */

  iKeyCallFunc( data, func, user_data, "K_acute", K_acute, 1 );
  iKeyCallFunc( data, func, user_data, "K_diaeresis", K_diaeresis, 1 );
}

IUP_SDK_API int iupKeyCallKeyCb( struct libData *data, Ihandle *ih, int code)
{
  char *name = iupKeyCodeToName( data, code );
  for (; ih; ih = ih->parent)
  {
    IFni cb = NULL;
    if (name)
      cb = (IFni) amy_IupGetCallback( data, ih, name );
    if ( ! cb)
      cb = (IFni) amy_IupGetCallback( data, ih, "K_ANY" );

    if (cb)
    {
      int ret = cb( data, ih, code );
      if (ret != IUP_CONTINUE)
        return ret;
    }
  }
  return IUP_DEFAULT;
}

IUP_SDK_API int iupKeyCallKeyPressCb( struct libData *data, Ihandle *ih, int code, int press)
{
  IFnii cb = (IFnii) amy_IupGetCallback( data, ih, "KEYPRESS_CB" );
  if (cb) return cb( data, ih, code, press );
  return IUP_DEFAULT;
}

static void iupKeyActivate( struct libData *data, Ihandle *ih )
{
  if ( ih->handle && iupdrvIsActive( data, ih ))
    iupdrvActivate( data, ih );
}

static void iupSetFontSizeChildren( struct libData *data, Ihandle *ih, int inc)
{
  /* if FONT is set at a child, 
     then it will not inherit the value set at the dialog.
     Must be manually increased or decreased. */
  Ihandle *child = ih->firstchild;
  while (child)
  {
    if (child->iclass->childtype == IUP_CHILDNONE &&  /* only for non-containers */
        iupTableGet( data, child->attrib, "FONT" ))  /* FONT must be defined */
    {
      int new_size;
      int size = amy_IupGetInt( data, child, "FONTSIZE" );

      if ( inc)
      {
        new_size = (size * 11) / 10; /* 10% increase */
        if (new_size == size) new_size++;
        inc = 1;
      }
      else
      {
        new_size = (size * 9) / 10; /* 10% decrease */
        if (new_size == size) new_size--;
        inc = 0;
      }

      amy_IupSetInt( data, child, "FONTSIZE", new_size );
    }

    iupSetFontSizeChildren( data, child, inc );

    child = child->brother;
  }
}

IUP_SDK_API int iupKeyProcessNavigation( struct libData *data, Ihandle *ih, int code, int shift)
{
  /* this is called after K_ANY is processed, 
     so the user may change its behavior */

  if (code == K_cTAB)
  {
    int is_multiline = iupAttribGetInt( data, ih, "_IUP_MULTILINE_TEXT" );
    if ( is_multiline)
    {
      if (shift)
        amy_IupPreviousField( data, ih );
      else
        amy_IupNextField( data, ih );
      return 1;
    }
  }
  else if (code == K_TAB || code == K_sTAB)
  {
    int is_multiline = iupAttribGetInt( data, ih, "_IUP_MULTILINE_TEXT" );
    if ( ! is_multiline)
    {
      if (code == K_sTAB || shift)
        amy_IupPreviousField( data, ih );
      else
        amy_IupNextField( data, ih );
      return 1;
    }
  }
  else if (code == K_UP || code == K_DOWN)
  {
    int is_button = (amy_IupClassMatch( data, ih, "button" ) || 
                     amy_IupClassMatch( data, ih, "flatbutton" ) ||
                     amy_IupClassMatch( data, ih, "toggle" ));
    if ( is_button)
    {
      if (code == K_UP)
        iupFocusPrevious( data, ih );
      else
        iupFocusNext( data, ih );
      return 1;
    }
  }
  else if (code==K_ESC)
  {
    Ihandle *bt = amy_IupGetAttributeHandle( data, amy_IupGetDialog( data, ih ), "DEFAULTESC" );
    if ( iupObjectCheck( data, bt ) && (amy_IupClassMatch( data, bt, "button" ) || amy_IupClassMatch( data, bt, "flatbutton" )))
    {
      iupKeyActivate( data, bt );
      return 1;
    }
  }
  else if (code==K_CR || code==K_cCR)
  {
    int is_multiline = iupAttribGetInt( data, ih, "_IUP_MULTILINE_TEXT" );
    /* when in a multiline accept Ctrl+Enter */
    /* when in a button does nothing because must activate the button itself. */
    if (((code == K_CR && !is_multiline) || (code == K_cCR && is_multiline)) && !(amy_IupClassMatch( data, ih, "button" ) || amy_IupClassMatch( data, ih, "flatbutton" )))
    {
      Ihandle *bt = amy_IupGetAttributeHandle( data, amy_IupGetDialog( data, ih ), "DEFAULTENTER" );
      if ( iupObjectCheck( data, bt ) && (amy_IupClassMatch( data, bt, "button" ) || amy_IupClassMatch( data, bt, "flatbutton" )))
      {
        iupKeyActivate( data, bt );
        return 1;
      }
    }
  }
  else if ( iup_isCtrlXkey(code) && iup_isShiftXkey(code) && iup_isAltXkey(code) && iup_XkeyBase(code) == K_L)
  {
    /* Ctrl+Shift+Alt+L */
    if ( iupStrBoolean(amy_IupGetGlobal( data, "GLOBALLAYOUTDLGKEY" )))
      amy_IupShow( data, amy_IupLayoutDialog( data, amy_IupGetDialog( data, ih )));
  }
  else if ( iup_isCtrlXkey(code) && (iup_XkeyBase(code) == K_plus || iup_XkeyBase(code) == K_minus || iup_XkeyBase(code) == K_equal))
  {
    /* Ctrl+'+' */
    if ( iupStrBoolean(amy_IupGetGlobal( data, "GLOBALLAYOUTRESIZEKEY" )))
    {
      int new_size;
      Ihandle *dialog = amy_IupGetDialog( data, ih );
      int size = amy_IupGetInt( data, dialog, "FONTSIZE" );
      int inc;

      if ( iup_XkeyBase(code) == K_plus || iup_XkeyBase(code) == K_equal)
      {
        new_size = (size * 11) / 10; /* 10% increase */
        if (new_size == size) new_size++;
        inc = 1;
      }
      else
      {
        new_size = (size * 9) / 10; /* 10% decrease */
        if (new_size == size) new_size--;
        inc = 0;
      }

      amy_IupSetInt( data, dialog, "FONTSIZE", new_size );
      iupSetFontSizeChildren( data, dialog, inc );

      amy_IupRefresh( data, ih );
    }
  }
  else if ( iup_isCtrlXkey(code) && (iup_XkeyBase(code) >= K_F1 && iup_XkeyBase(code) <= K_F12))
  {
    /* Ctrl+'F?' */
    IFi cb = (IFi) amy_IupGetFunction( data, "GLOBALCTRLFUNC_CB" );
    if (cb)
      cb(code );
  }

  return 0;
}

IUP_SDK_API int iupKeyProcessMnemonic( struct libData *data, Ihandle *ih, int code)
{
  Ihandle *ih_mnemonic, *dialog = amy_IupGetDialog( data, ih );
  char attrib[16] = "_IUP_MNEMONIC_ ";
  attrib[14] = (char)code;
  iupStrUpper(attrib, attrib );
  ih_mnemonic = (Ihandle*) amy_IupGetAttribute( data, dialog, attrib );
  if ( iupObjectCheck( data, ih_mnemonic))
  {
    if ( iupClassMatch( data, ih_mnemonic, "label" ))
    {
      Ihandle *ih_next = iupFocusNextInteractive( data, ih_mnemonic );
      if ( ih_next)
      {
        if ( iupClassMatch( data, ih_next, "button" ) || 
            amy_IupClassMatch( data, ih_next, "flatbutton" ) ||
            amy_IupClassMatch( data, ih_next, "toggle" ))
          iupKeyActivate( data, ih_next );
        else
          amy_IupSetFocus( data, ih_next );
      }
    }
    else if ( iupClassMatch( data, ih_mnemonic, "tabs" ))
      amy_IupSetAttribute( data, ih_mnemonic, "VALUEPOS", amy_IupGetAttribute( data, ih_mnemonic, attrib));
    else /* button or toggle */
      iupKeyActivate( data, ih_mnemonic );

    return 1;
  }

  return 0;
}

IUP_SDK_API void iupKeySetMnemonic( struct libData *data, Ihandle *ih, int code, int pos)
{
  Ihandle *ih_dialog = amy_IupGetDialog( data, ih );
  char attrib[16] = "_IUP_MNEMONIC_ ";
  attrib[14] = (char)code;
  iupStrUpper(attrib, attrib );

  amy_IupSetAttribute( data, ih_dialog, attrib, (char*)ih );
  if ( iupClassMatch( data, ih, "tabs" ))
    amy_IupSetInt( data, ih, attrib, pos );
}
