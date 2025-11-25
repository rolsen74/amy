
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
 * \brief Toggle Control
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdlib.h>

#include "iup.h"
#include "iupcbs.h"

#include "iup_object.h"
#include "iup_attrib.h"
#include "iup_str.h"
#include "iup_drv.h"
#include "iup_drvfont.h"
#include "iup_image.h"
#include "iup_stdcontrols.h"
#include "iup_register.h"
#include "iup_drvdraw.h"
#include "iup_draw.h"
#include "iup_drvinfo.h"
#include "iup_key.h"

#endif

#define ITOGGLE_BORDER 1
#define ITOGGLE_SPACE  2
#define ITOGGLE_MARGIN 2

/* from amy_IupRadio implementation */
IUP_SDK_API Ihandle *iupRadioFindToggleParent( struct libData *data, Ihandle *ih_toggle );


struct _IcontrolData
{
  iupCanvas canvas;  /* from amy_IupCanvas (must reserve it) */

  /* attributes */
  int horiz_padding, vert_padding;  /* button margin */
  int spacing, img_position;        /* used when both text and image are displayed */
  int horiz_alignment, vert_alignment;
  int border_width;
  int check_size, check_spacing;
  int value;

  /* aux */
  int has_focus,
    highlighted,
    pressed;
};


/****************************************************************/


static int iFlatToggleRedraw_CB( struct libData *data, Ihandle *ih )
{
  char *image = iupAttribGet( data, ih, "IMAGE" );
  char *title = iupAttribGet( data, ih, "TITLE" );
  int active = amy_IupGetInt( data, ih, "ACTIVE" );  /* native implementation */
  int selected = ih->data->value;
  char *fgcolor = iupAttribGetStr( data, ih, "FGCOLOR" );
  char *bgcolor = iupAttribGet( data, ih, "BGCOLOR" );
  char *bgimage = iupAttribGet( data, ih, "BACKIMAGE" );
  char *fgimage = iupAttribGet( data, ih, "FRONTIMAGE" );
  int text_flags = iupDrawGetTextFlags( data, ih, "TEXTALIGNMENT", "TEXTWRAP", "TEXTELLIPSIS" );
  double text_orientation = iupAttribGetDouble( data, ih, "TEXTORIENTATION" );
  int check_at_right = iupAttribGetInt( data, ih, "CHECKRIGHT" );
  Ihandle *radio = iupRadioFindToggleParent( data, ih );
  const char *draw_image;
  int border_width = ih->data->border_width;
  int draw_border = iupAttribGetBoolean( data, ih, "SHOWBORDER" );
  int focus_feedback = iupAttribGetBoolean( data, ih, "FOCUSFEEDBACK" );
  int image_pressed, icon_left, check_left, icon_width, icon_right;
  IdrawCanvas* dc = iupdrvDrawCreateCanvas( data, ih );
  int make_inactive = 0;

  iupDrawParentBackground( data, dc, ih );

  if ( ! bgcolor)
  {
    if (draw_border)
      bgcolor = iupFlatGetDarkerBgColor( data, ih );
    else
      bgcolor = iupBaseNativeParentGetBgColorAttrib( data, ih );
  }

  if (ih->data->check_size)
  {
    check_left = 0;
    icon_left = ih->data->check_size + ih->data->check_spacing;
    icon_right = ih->currentwidth - 1;
    if (check_at_right)
    {
      check_left = ih->currentwidth - ih->data->check_size;
      icon_left = 0;
      icon_right = ih->currentwidth -1 - ih->data->check_size - ih->data->check_spacing;
    }
    icon_width = ih->currentwidth - ih->data->check_size - ih->data->check_spacing;
  }
  else
  {
    if ((ih->data->pressed && ih->data->highlighted) || (selected && !ih->data->highlighted))
    {
      char *presscolor = iupAttribGetStr( data, ih, "PSCOLOR" );
      if (presscolor)
        bgcolor = presscolor;

      presscolor = iupAttribGetStr( data, ih, "TEXTPSCOLOR" );
      if (presscolor)
        fgcolor = presscolor;

      draw_border = 1;
    }
    else if (ih->data->highlighted)
    {
      char *hlcolor = iupAttribGetStr( data, ih, "HLCOLOR" );
      if (hlcolor)
        bgcolor = hlcolor;

      hlcolor = iupAttribGetStr( data, ih, "TEXTHLCOLOR" );
      if (hlcolor)
        fgcolor = hlcolor;

      draw_border = 1;
    }

    check_left = 0;
    icon_left = 0;
    icon_right = ih->currentwidth - 1;
    icon_width = ih->currentwidth;
  }

  /* draw border - can still be disabled setting border_width=0 */
  if (draw_border)
  {
    char *bordercolor = iupAttribGetStr( data, ih, "BORDERCOLOR" );

    if ((ih->data->pressed && ih->data->highlighted) || (selected && !ih->data->highlighted))
    {
      char *presscolor = iupAttribGetStr( data, ih, "BORDERPSCOLOR" );
      if (presscolor)
        bordercolor = presscolor;
    }
    else if (ih->data->highlighted)
    {
      char *hlcolor = iupAttribGetStr( data, ih, "BORDERHLCOLOR" );
      if (hlcolor)
        bordercolor = hlcolor;
    }

    iupFlatDrawBorder( data, dc, 0, ih->currentwidth - 1,
                          0, ih->currentheight - 1,
                          border_width, bordercolor, bgcolor, active );
  }

  /* simulate pressed when selected and has images (but colors and borders are not included) */
  image_pressed = ih->data->pressed && ih->data->highlighted;
  if (selected && !ih->data->pressed && (bgimage || image))
    image_pressed = 1;

  /* draw background */
  if (bgimage)
  {
    int backimage_zoom = iupAttribGetBoolean( data, ih, "BACKIMAGEZOOM" );
    draw_image = iupFlatGetImageName( data, ih, "BACKIMAGE", bgimage, image_pressed, ih->data->highlighted, 1, &make_inactive );
    if (backimage_zoom)
      iupdrvDrawImage( data, dc, draw_image, make_inactive, bgcolor, border_width, border_width, ih->currentwidth - border_width, ih->currentheight - border_width );
    else
      iupdrvDrawImage( data, dc, draw_image, make_inactive, bgcolor, border_width, border_width, -1, -1 );
  }
  else 
    iupFlatDrawBox( data, dc, border_width, ih->currentwidth - 1 - border_width,
                       border_width, ih->currentheight - 1 - border_width,
                       bgcolor, NULL, 1 );  /* background is always active */

  /* reserve space for focus feedback (after background draw) */
  if (iupAttribGetBoolean( data, ih, "CANFOCUS" ) && focus_feedback)
    border_width++;

  /* draw icon */
  draw_image = iupFlatGetImageName( data, ih, "IMAGE", image, image_pressed, ih->data->highlighted, active, &make_inactive );
  iupFlatDrawIcon( data, ih, dc, border_width + icon_left, border_width,
                          icon_width - 2 * border_width, ih->currentheight - 2 * border_width,
                          ih->data->img_position, ih->data->spacing, ih->data->horiz_alignment, ih->data->vert_alignment, ih->data->horiz_padding, ih->data->vert_padding,
                          draw_image, make_inactive, title, text_flags, text_orientation, fgcolor, bgcolor, active );

  if (fgimage)
  {
    draw_image = iupFlatGetImageName( data, ih, "FRONTIMAGE", fgimage, image_pressed, ih->data->highlighted, active, &make_inactive );
    iupdrvDrawImage( data, dc, draw_image, make_inactive, bgcolor, border_width, border_width + icon_left, -1, -1 );
  }
  else if ( ! image && !title)
  {
    int space = border_width + ITOGGLE_MARGIN;
    iupFlatDrawBorder( data, dc, space + icon_left, icon_right - space,
                          space, ih->currentheight - 1 - space,
                          1, "0 0 0", bgcolor, active );
    space++;
    iupFlatDrawBox( data, dc, space + icon_left, icon_right - space,
                       space, ih->currentheight - 1 - space,
                       fgcolor, bgcolor, active );
  }

  if (ih->data->check_size)
  {
    int check_alig = iupFlatGetVerticalAlignment( data, iupAttribGetStr( data, ih, "CHECKALIGN" ));
    int xc = check_left + ih->data->check_size / 2;
    int yc = ih->currentheight / 2;
    int radius = ih->data->check_size / 2 - ITOGGLE_MARGIN;
    int check_xmin = check_left + ITOGGLE_MARGIN;
    int check_ymin = (ih->currentheight - ih->data->check_size) / 2 + ITOGGLE_MARGIN;
    int check_size = ih->data->check_size - 2 * ITOGGLE_MARGIN;
    char *check_image = iupAttribGet( data, ih, "CHECKIMAGE" );

    if (check_alig == IUP_ALIGN_ABOTTOM)
    {
      check_ymin = ih->currentheight - 1 - ITOGGLE_MARGIN;
      yc = ih->currentheight - 1 - ITOGGLE_MARGIN - ih->data->check_size / 2;
    }
    else if (check_alig == IUP_ALIGN_ATOP)
    {
      check_ymin = ITOGGLE_MARGIN;
      yc = ih->data->check_size / 2;
    }

    if (check_image)
    {
      if (selected == -1)
        draw_image = iupFlatGetImageName( data, ih, "CHECKIMAGENOTDEF", NULL, ih->data->pressed, ih->data->highlighted, active, &make_inactive );
      else if (selected)
        draw_image = iupFlatGetImageName( data, ih, "CHECKIMAGEON", NULL, ih->data->pressed, ih->data->highlighted, active, &make_inactive );
      
      if ( ! draw_image)
        draw_image = iupFlatGetImageName( data, ih, "CHECKIMAGE", check_image, ih->data->pressed, ih->data->highlighted, active, &make_inactive );

      iupdrvDrawImage( data, dc, draw_image, make_inactive, bgcolor, check_xmin, check_ymin, -1, -1 );
    }
    else
    {
      char *check_fgcolor = iupAttribGet( data, ih, "CHECKFGCOLOR" );
      char *check_bgcolor = iupAttribGetStr( data, ih, "CHECKBGCOLOR" );
      char *bordercolor   = iupAttribGetStr( data, ih, "BORDERCOLOR" );

      if ( ! check_fgcolor)
        check_fgcolor = fgcolor;

      if ((ih->data->pressed && ih->data->highlighted) || (selected && !ih->data->highlighted))
      {
        char *presscolor = iupAttribGetStr( data, ih, "CHECKPSCOLOR" );
        if (presscolor)
          check_fgcolor = presscolor;
        else
        {
          if (ih->data->highlighted)
          {
            char *hlcolor = iupAttribGetStr( data, ih, "HLCOLOR" );
            if (hlcolor)
              check_bgcolor = hlcolor;

            check_fgcolor = bordercolor; /* only when highlighted */
          }
        }
      }
      else if (ih->data->highlighted)
      {
        char *hlcolor = iupAttribGetStr( data, ih, "CHECKHLCOLOR" );
        if (hlcolor)
          check_fgcolor = hlcolor;
        else
          check_fgcolor = bordercolor; /* only when highlighted */
      }

      /* check background */
      if (radio)
        iupFlatDrawDrawCircle( data, dc, xc, yc, radius, 1, 1, check_bgcolor, bgcolor, active );
      else
        iupFlatDrawBox( data, dc, check_xmin, check_xmin + check_size,
                           check_ymin, check_ymin + check_size,
                           check_bgcolor, bgcolor, active );

      /* check border */
      if (radio)
        iupFlatDrawDrawCircle( data, dc, xc, yc, radius, 0, ITOGGLE_BORDER, check_fgcolor, bgcolor, active );
      else
        iupFlatDrawBorder( data, dc, check_xmin, check_xmin + check_size,
                              check_ymin, check_ymin + check_size,
                              ITOGGLE_BORDER, check_fgcolor, bgcolor, active );

      /* check mark */
      if (selected)
      {
        if (radio)
          iupFlatDrawDrawCircle( data, dc, xc, yc, radius - ITOGGLE_SPACE - ITOGGLE_BORDER, 1, 1, check_fgcolor, check_bgcolor, active );
        else if (selected == -1)
          iupFlatDrawBox( data, dc, check_xmin + ITOGGLE_SPACE + ITOGGLE_BORDER, check_xmin + check_size - ITOGGLE_SPACE - ITOGGLE_BORDER,
                             check_ymin + ITOGGLE_SPACE + ITOGGLE_BORDER, check_ymin + check_size - ITOGGLE_SPACE - ITOGGLE_BORDER,
                             check_fgcolor, check_bgcolor, active );
        else
          iupFlatDrawCheckMark( data, dc, check_xmin + ITOGGLE_SPACE + ITOGGLE_BORDER, check_xmin + check_size - ITOGGLE_SPACE - ITOGGLE_BORDER,
                                   check_ymin + ITOGGLE_SPACE + ITOGGLE_BORDER, check_ymin + check_size - ITOGGLE_SPACE - ITOGGLE_BORDER,
                                   check_fgcolor, check_bgcolor, active );
      }
    }
  }

  if (ih->data->has_focus && focus_feedback)
  {
    border_width--;
    iupdrvDrawFocusRect( data, dc, border_width + icon_left, border_width,
                        icon_right - border_width, ih->currentheight - 1 - border_width );
  }

  iupdrvDrawFlush( data, dc );

  iupdrvDrawKillCanvas( data, dc );

  return IUP_DEFAULT;
}

static void iFlatToggleNotify( struct libData *data, Ihandle *ih )
{
  IFni cb = (IFni) amy_IupGetCallback( data, ih, "FLAT_ACTION" );
  if (cb)
  {
    int ret = cb( data, ih, ih->data->value );
    if (ret == IUP_CLOSE)
      amy_IupExitLoop( data );
  }

  if (iupObjectCheck( data, ih ))
    iupBaseCallValueChangedCb( data, ih );
}

static int iFlatToggleUpdateHighlighted( struct libData *data, Ihandle *ih, int x, int y)
{
  /* handle when mouse is pressed and moved to/from inside the canvas */
  if (x < 0 || x > ih->currentwidth - 1 ||
      y < 0 || y > ih->currentheight - 1)
  {
    if (ih->data->highlighted)
    {
      ih->data->highlighted = 0;
      return 1;
    }
  }
  else
  {
    if ( ! ih->data->highlighted)
    {
      ih->data->highlighted = 1;
      return 1;
    }
  }

  return 0;
}

static int iFlatToggleButton_CB( struct libData *data, Ihandle *ih, int button, int pressed, int x, int y, char *status)
{
  IFniiiis cb = (IFniiiis) amy_IupGetCallback( data, ih, "FLAT_BUTTON_CB" );
  if (cb)
  {
    if (cb( data, ih, button, pressed, x, y, status) == IUP_IGNORE)
      return IUP_DEFAULT;
  }

  if (button == IUP_BUTTON1)
  {
    Ihandle *radio = iupRadioFindToggleParent( data, ih );
    Ihandle *last_tg = NULL;

    iFlatToggleUpdateHighlighted( data, ih, x, y );

    if ( ! pressed && ih->data->highlighted)  /* released inside the button area */
    {
      int selected = ih->data->value;
      if (selected > 0)  /* was ON */
      {
        if ( ! radio)
        {
          int tstate = iupAttribGetInt( data, ih, "3STATE" );
          if (tstate)
            ih->data->value = -1;
          else
            ih->data->value = 0;
        }
        else
          last_tg = ih;  /* to avoid the callback call */
      }
      else if (selected == -1)
      {
        ih->data->value = 0;
      }
      else  /* was OFF */
      {
        if (radio)
        {
          last_tg = (Ihandle*) iupAttribGet( data, radio, "_IUP_FLATTOGGLE_LASTTOGGLE" );
          if (iupObjectCheck( data, last_tg ) && last_tg != ih)
          {
            last_tg->data->value = 0;
            if (last_tg->handle)
              iupdrvRedrawNow( data, last_tg );
          }
          else
            last_tg = NULL;

          iupAttribSet( data, radio, "_IUP_FLATTOGGLE_LASTTOGGLE", (char*)ih );
        }

        ih->data->value = 1;
      }
    }

    ih->data->pressed = pressed;
    iupdrvRedrawNow( data, ih );

    if ( ! pressed && ih->data->highlighted)  /* released inside the button area */
    {
      if (last_tg && ih != last_tg)
        iFlatToggleNotify( data, last_tg );

      if ( ! radio || ih != last_tg)
        iFlatToggleNotify( data, ih );

      if (radio && ih == last_tg && iupAttribGetBoolean( data, ih, "SELECTEDNOTIFY" )) /* pressed the selected toggle in a radio */
        iFlatToggleNotify( data, ih );
    }
  }

  return IUP_DEFAULT;
}

static int iFlatToggleMotion_CB( struct libData *data, Ihandle *ih, int x, int y, char *status)
{
  int redraw = 0;
  IFniis cb = (IFniis) amy_IupGetCallback( data, ih, "FLAT_MOTION_CB" );
  if (cb)
  {
    if (cb( data, ih, x, y, status) == IUP_IGNORE)
      return IUP_DEFAULT;
  }

  if (iup_isbutton1(status))
  {
    redraw = iFlatToggleUpdateHighlighted( data, ih, x, y );
  }

  if (redraw)
    iupdrvRedrawNow( data, ih );

  return IUP_DEFAULT;
}

static int iFlatToggleActivate_CB( struct libData *data, Ihandle *ih )
{
  char status[IUPKEY_STATUS_SIZE] = IUPKEY_STATUS_INIT;

  iFlatToggleButton_CB( data, ih, IUP_BUTTON1, 1, 0, 0, status );

  iupdrvSleep( data, 100 );

  iFlatToggleButton_CB( data, ih, IUP_BUTTON1, 0, 0, 0, status );

  return IUP_DEFAULT;
}

static int iFlatToggleFocus_CB( struct libData *data, Ihandle *ih, int focus)
{
  IFni cb = (IFni) amy_IupGetCallback( data, ih, "FLAT_FOCUS_CB" );
  if (cb)
  {
    if (cb( data, ih, focus) == IUP_IGNORE)
      return IUP_DEFAULT;
  }

  ih->data->has_focus = focus;
  iupdrvRedrawNow( data, ih );

  return IUP_DEFAULT;
}

static int iFlatToggleEnterWindow_CB( struct libData *data, Ihandle *ih )
{
  IFn cb = (IFn) amy_IupGetCallback( data, ih, "FLAT_ENTERWINDOW_CB" );
  if (cb)
  {
    if (cb( data,ih ) == IUP_IGNORE)
      return IUP_DEFAULT;
  }

  ih->data->highlighted = 1;
  iupdrvRedrawNow( data, ih );

  return IUP_DEFAULT;
}

static int iFlatToggleLeaveWindow_CB( struct libData *data, Ihandle *ih )
{
  IFn cb = (IFn) amy_IupGetCallback( data, ih, "FLAT_LEAVEWINDOW_CB" );
  if (cb)
  {
    if (cb( data,ih ) == IUP_IGNORE)
      return IUP_DEFAULT;
  }

  ih->data->highlighted = 0;
  iupdrvRedrawNow( data, ih );

  return IUP_DEFAULT;
}


/***********************************************************************************************/


static int iFlatToggleSetAlignmentAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  char value1[30], value2[30];

  iupStrToStrStr(value, value1, value2, ':' );

  ih->data->horiz_alignment = iupFlatGetHorizontalAlignment( data, value1 );
  ih->data->vert_alignment = iupFlatGetVerticalAlignment( data, value2 );

  if (ih->handle)
    iupdrvRedrawNow( data, ih );

  return 1;
}

static char *iFlatToggleGetAlignmentAttrib( struct libData *data, Ihandle *ih )
{
  char *horiz_align2str[3] = { "ALEFT", "ACENTER", "ARIGHT" };
  char *vert_align2str[3] = { "ATOP", "ACENTER", "ABOTTOM" };
  return iupStrReturnStrf("%s:%s", horiz_align2str[ih->data->horiz_alignment], vert_align2str[ih->data->vert_alignment] );
}

static int iFlatToggleSetPaddingAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if (iupStrEqual(value, "DEFAULTBUTTONPADDING" ))
    value = amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING" );

  iupStrToIntInt(value, &ih->data->horiz_padding, &ih->data->vert_padding, 'x' );
  if (ih->handle)
    iupdrvRedrawNow( data, ih );
  return 0;
}

static int iFlatToggleGetDefaultCheckSize( struct libData *data )
{
  if (iupIsHighDpi( data ))
    return 24;
  else
    return 16;
}

static int iFlatToggleSetCheckSizeAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  if ( ! value)
    ih->data->check_size = iFlatToggleGetDefaultCheckSize( data );
  else
    iupStrToInt(value, &ih->data->check_size );
  if (ih->handle)
    iupdrvRedrawNow( data, ih );
  return 0;
}

static char *iFlatToggleGetCheckSizeAttrib( struct libData *data, Ihandle *ih )
{
  return amy_iupStrReturnInt( data, ih->data->check_size );
}

static int iFlatToggleSetCheckSpacingAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  iupStrToInt(value, &ih->data->check_spacing );
  if (ih->handle)
    iupdrvRedrawNow( data, ih );
  return 0;
}

static char *iFlatToggleGetCheckSpacingAttrib( struct libData *data, Ihandle *ih )
{
  return amy_iupStrReturnInt( data, ih->data->check_spacing );
}

static int iFlatToggleSetAttribPostRedraw( struct libData *data, Ihandle *ih, const char *value)
{
  (void)value;
  if (ih->handle)
    iupdrvPostRedraw( data, ih );
  return 1;
}

static char *iFlatToggleGetBgColorAttrib( struct libData *data, Ihandle *ih )
{
  char *value = iupAttribGet( data, ih, "BGCOLOR" );
  if ( ! value)
    return iupBaseNativeParentGetBgColorAttrib( data, ih );
  else
    return value;
}

static char *iFlatToggleGetPaddingAttrib( struct libData *data, Ihandle *ih )
{
  return iupStrReturnIntInt(ih->data->horiz_padding, ih->data->vert_padding, 'x' );
}

static int iFlatToggleSetImagePositionAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  ih->data->img_position = iupFlatGetImagePosition( data, value );

  if (ih->handle)
    iupdrvRedrawNow( data, ih );

  return 0;
}

static char *iFlatToggleGetImagePositionAttrib( struct libData *data, Ihandle *ih )
{
  char *img_pos2str[4] = { "LEFT", "RIGHT", "TOP", "BOTTOM" };
  return iupStrReturnStr(img_pos2str[ih->data->img_position] );
}

static int iFlatToggleSetSpacingAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  iupStrToInt(value, &ih->data->spacing );
  if (ih->handle)
    iupdrvRedrawNow( data, ih );
  return 0;
}

static char *iFlatToggleGetSpacingAttrib( struct libData *data, Ihandle *ih )
{
  return amy_iupStrReturnInt( data, ih->data->spacing );
}

static int iFlatToggleSetBorderWidthAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  iupStrToInt(value, &ih->data->border_width );
  if (ih->handle)
    iupdrvRedrawNow( data, ih );
  return 0;
}

static char *iFlatToggleGetBorderWidthAttrib( struct libData *data, Ihandle *ih )
{
  return amy_iupStrReturnInt( data, ih->data->border_width );
}

static int iFlatToggleSetValueAttrib( struct libData *data, Ihandle *ih, const char *value)
{
  Ihandle *radio = iupRadioFindToggleParent( data, ih );
  if (radio)
  {
    /* can only set Radio to ON */
    if (iupStrBoolean(value))
    {
      Ihandle *last_tg = (Ihandle*) iupAttribGet( data, radio, "_IUP_FLATTOGGLE_LASTTOGGLE" );
      if (iupObjectCheck( data, last_tg ) && last_tg != ih)
      {
        last_tg->data->value = 0;
        if (last_tg->handle)
          iupdrvRedrawNow( data, last_tg );
      }

      iupAttribSet( data, radio, "_IUP_FLATTOGGLE_LASTTOGGLE", (char*)ih );
      ih->data->value = 1;
    }
    else
      return 0;
  }
  else
  {
    if (iupStrEqualNoCase(value, "TOGGLE" ))
    {
      if (ih->data->value)
        ih->data->value = 0;
      else
        ih->data->value = 1;
    }
    else
    {
      int tstate = iupAttribGetInt( data, ih, "3STATE" );
      if (tstate && iupStrEqualNoCase(value, "NOTDEF" ))
        ih->data->value = -1;
      else
      {
        if (iupStrBoolean(value))
          ih->data->value = 1;
        else
          ih->data->value = 0;
      }
    }

    if (ih->handle)
      iupdrvRedrawNow( data, ih );

    return 0;
  }

  if (ih->handle)
    iupdrvPostRedraw( data, ih );

  return 0;
}

static char *iFlatToggleGetValueAttrib( struct libData *data, Ihandle *ih )
{
  return iupStrReturnChecked(ih->data->value );
}

static char *iFlatToggleGetRadioAttrib( struct libData *data, Ihandle *ih )
{
  Ihandle *radio = iupRadioFindToggleParent( data, ih );
  return iupStrReturnBoolean( radio != NULL );
}

static char *iFlatToggleGetHighlightedAttrib( struct libData *data, Ihandle *ih )
{
  return iupStrReturnBoolean( ih->data->highlighted );
}

static char *iFlatToggleGetPressedAttrib( struct libData *data, Ihandle *ih )
{
  return iupStrReturnBoolean( ih->data->pressed );
}

static char *iFlatToggleGetHasFocusAttrib( struct libData *data, Ihandle *ih )
{
  return iupStrReturnBoolean( ih->data->has_focus );
}


/*****************************************************************************************/

static int iFlatToggleCreateMethod( struct libData *data, Ihandle *ih, void** params)
{
  if (params && params[0] )
  {
    iupAttribSetStr( data, ih, "TITLE", (char*)(params[0] ));
  }

  /* free the data allocated by amy_IupCanvas */
  free(ih->data );
  ih->data = iupALLOCCTRLDATA();

  /* change the amy_IupCanvas default values */
  iupAttribSet( data, ih, "BORDER", "NO" );
  ih->expand = IUP_EXPAND_NONE;

  /* non zero default values */
  ih->data->spacing = 2;
  ih->data->border_width = 1;
  ih->data->horiz_alignment = IUP_ALIGN_ACENTER;
  ih->data->vert_alignment = IUP_ALIGN_ACENTER;
  ih->data->check_size = iFlatToggleGetDefaultCheckSize( data );
  ih->data->check_spacing = 5;

  /* initial values - don't use default so they can be set to NULL */
  iupAttribSet( data, ih, "HLCOLOR", IUP_FLAT_HIGHCOLOR );
  iupAttribSet( data, ih, "PSCOLOR", IUP_FLAT_PRESSCOLOR );

  /* internal callbacks */
  amy_IupSetCallback( data, ih, "ACTION", (Icallback)iFlatToggleRedraw_CB );
  amy_IupSetCallback( data, ih, "BUTTON_CB", (Icallback)iFlatToggleButton_CB );
  amy_IupSetCallback( data, ih, "MOTION_CB", (Icallback)iFlatToggleMotion_CB );
  amy_IupSetCallback( data, ih, "FOCUS_CB", (Icallback)iFlatToggleFocus_CB );
  amy_IupSetCallback( data, ih, "LEAVEWINDOW_CB", iFlatToggleLeaveWindow_CB );
  amy_IupSetCallback( data, ih, "ENTERWINDOW_CB", iFlatToggleEnterWindow_CB );
  amy_IupSetCallback( data, ih, "K_CR", (Icallback)iFlatToggleActivate_CB );
  amy_IupSetCallback( data, ih, "K_SP", (Icallback)iFlatToggleActivate_CB );

  return IUP_NOERROR;
}

static int iFlatToggleMapMethod( struct libData *data, Ihandle *ih )
{
  Ihandle *radio = iupRadioFindToggleParent( data, ih );
  if (radio)
  {
    if ( ! iupAttribGet( data, radio, "_IUP_FLATTOGGLE_LASTTOGGLE" ))
    {
      /* this is the first toggle in the radio, and then set it with VALUE=ON */
      ih->data->value = 1;
      /* value is already set, attribute will not be updated after map, must set last toggle here */
      iupAttribSet( data, radio, "_IUP_FLATTOGGLE_LASTTOGGLE", (char*)ih );
    }

    /* make sure it has at least one name */
    if ( ! iupAttribGetHandleName( data, ih ))
      iupAttribSetHandleName( data, ih );
  }
  return IUP_NOERROR;
}

static void iFlatToggleComputeNaturalSizeMethod( struct libData *data, Ihandle *ih, int *w, int *h, int *children_expand)
{
  int fit2backimage = iupAttribGetBoolean( data, ih, "FITTOBACKIMAGE" );
  char *bgimage = iupAttribGet( data, ih, "BACKIMAGE" );
  if (fit2backimage && bgimage)
    iupImageGetInfo( data, bgimage, w, h, NULL );
  else
  {
    char *imagename = iupAttribGet( data, ih, "IMAGE" );
    char *title = iupAttribGet( data, ih, "TITLE" );
    double text_orientation = iupAttribGetDouble( data, ih, "TEXTORIENTATION" );

    iupFlatDrawGetIconSize( data, ih, ih->data->img_position, ih->data->spacing, ih->data->horiz_padding, ih->data->vert_padding, imagename, title, w, h, text_orientation );

    if (ih->data->check_size)
    {
      *w += ih->data->check_size;
      *w += ih->data->check_spacing;
      if (ih->data->check_size > *h)
        *h = ih->data->check_size;
    }
  }

  *w += 2 * ih->data->border_width;
  *h += 2 * ih->data->border_width;

  (void)children_expand; /* unset if not a container */
}


/******************************************************************************/


Iclass *iupFlatToggleNewClass( struct libData *data )
{
  Iclass *ic = iupClassNew( data, iupRegisterFindClass( data, "canvas" ));

  ic->name = "flattoggle";
  ic->cons = "FlatToggle";
  ic->format = "s"; /* one string */
  ic->format_attr = "TITLE";
  ic->nativetype = IUP_TYPECANVAS;
  ic->childtype = IUP_CHILDNONE;
  ic->is_interactive = 1;

  /* Class functions */
  ic->New = iupFlatToggleNewClass;
  ic->Create = iFlatToggleCreateMethod;
  ic->ComputeNaturalSize = iFlatToggleComputeNaturalSizeMethod;
  ic->Map = iFlatToggleMapMethod;

  /* Callbacks */
  iupClassRegisterCallback( data, ic, "FLAT_ACTION", "i" );
  iupClassRegisterCallback( data, ic, "FLAT_BUTTON_CB", "iiiis" );
  iupClassRegisterCallback( data, ic, "FLAT_MOTION_CB", "iis" );
  iupClassRegisterCallback( data, ic, "FLAT_FOCUS_CB", "i" );
  iupClassRegisterCallback( data, ic, "FLAT_ENTERWINDOW_CB", "ii" );
  iupClassRegisterCallback( data, ic, "FLAT_LEAVEWINDOW_CB", "" );
  iupClassRegisterCallback( data, ic, "VALUECHANGED_CB", "" );

  /* Overwrite Visual */
  iupClassRegisterAttribute( data, ic, "ACTIVE", iupBaseGetActiveAttrib, iupFlatSetActiveAttrib, IUPAF_SAMEASSYSTEM, "YES", IUPAF_DEFAULT );

  /* Special */
  iupClassRegisterAttribute( data, ic, "TITLE", NULL, iFlatToggleSetAttribPostRedraw, NULL, NULL, IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );

  /* amy_IupButton only */
  iupClassRegisterAttribute( data, ic, "VALUE", iFlatToggleGetValueAttrib, iFlatToggleSetValueAttrib, NULL, NULL, IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "RADIO", iFlatToggleGetRadioAttrib, NULL, NULL, NULL, IUPAF_NOT_MAPPED | IUPAF_READONLY | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "ALIGNMENT", iFlatToggleGetAlignmentAttrib, iFlatToggleSetAlignmentAttrib, "ACENTER:ACENTER", NULL, IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "PADDING", iFlatToggleGetPaddingAttrib, iFlatToggleSetPaddingAttrib, IUPAF_SAMEASSYSTEM, "0x0", IUPAF_NOT_MAPPED );
  iupClassRegisterAttribute( data, ic, "CPADDING", iupBaseGetCPaddingAttrib, iupBaseSetCPaddingAttrib, NULL, NULL, IUPAF_NO_SAVE | IUPAF_NOT_MAPPED );
  iupClassRegisterAttribute( data, ic, "SPACING", iFlatToggleGetSpacingAttrib, iFlatToggleSetSpacingAttrib, IUPAF_SAMEASSYSTEM, "2", IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CSPACING", iupBaseGetCSpacingAttrib, iupBaseSetCSpacingAttrib, NULL, NULL, IUPAF_NO_SAVE | IUPAF_NOT_MAPPED );
  iupClassRegisterAttribute( data, ic, "IGNORERADIO", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "HIGHLIGHTED", iFlatToggleGetHighlightedAttrib, NULL, NULL, NULL, IUPAF_NOT_MAPPED | IUPAF_READONLY | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "PRESSED", iFlatToggleGetPressedAttrib, NULL, NULL, NULL, IUPAF_NOT_MAPPED | IUPAF_READONLY | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "HASFOCUS", iFlatToggleGetHasFocusAttrib, NULL, NULL, NULL, IUPAF_NOT_MAPPED | IUPAF_READONLY | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "SHOWBORDER", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "FOCUSFEEDBACK", NULL, NULL, IUPAF_SAMEASSYSTEM, "YES", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "SELECTEDNOTIFY", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "BORDERCOLOR", NULL, NULL, IUPAF_SAMEASSYSTEM, IUP_FLAT_BORDERCOLOR, IUPAF_DEFAULT );  /* inheritable */
  iupClassRegisterAttribute( data, ic, "BORDERPSCOLOR", NULL, NULL, NULL, NULL, IUPAF_DEFAULT );  /* inheritable */
  iupClassRegisterAttribute( data, ic, "BORDERHLCOLOR", NULL, NULL, NULL, NULL, IUPAF_DEFAULT );  /* inheritable */
  iupClassRegisterAttribute( data, ic, "BORDERWIDTH", iFlatToggleGetBorderWidthAttrib, iFlatToggleSetBorderWidthAttrib, IUPAF_SAMEASSYSTEM, "1", IUPAF_NOT_MAPPED );  /* inheritable */
  iupClassRegisterAttribute( data, ic, "FGCOLOR", NULL, NULL, "DLGFGCOLOR", NULL, IUPAF_DEFAULT );  /* force the new default value */
  iupClassRegisterAttribute( data, ic, "BGCOLOR", iFlatToggleGetBgColorAttrib, iFlatToggleSetAttribPostRedraw, IUPAF_SAMEASSYSTEM, "DLGBGCOLOR", IUPAF_NO_SAVE );
  iupClassRegisterAttribute( data, ic, "HLCOLOR", NULL, NULL, NULL, NULL, IUPAF_DEFAULT );  /* inheritable */
  iupClassRegisterAttribute( data, ic, "PSCOLOR", NULL, NULL, NULL, NULL, IUPAF_DEFAULT );  /* inheritable */
  iupClassRegisterAttribute( data, ic, "TEXTHLCOLOR", NULL, NULL, NULL, NULL, IUPAF_DEFAULT );  /* inheritable */
  iupClassRegisterAttribute( data, ic, "TEXTPSCOLOR", NULL, NULL, NULL, NULL, IUPAF_DEFAULT );  /* inheritable */

  iupClassRegisterAttribute( data, ic, "IMAGE", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "IMAGEPRESS", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "IMAGEHIGHLIGHT", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "IMAGEINACTIVE", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "IMAGEPOSITION", iFlatToggleGetImagePositionAttrib, iFlatToggleSetImagePositionAttrib, IUPAF_SAMEASSYSTEM, "LEFT", IUPAF_NOT_MAPPED | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "TEXTALIGNMENT", NULL, NULL, IUPAF_SAMEASSYSTEM, "ALEFT", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "TEXTWRAP", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "TEXTELLIPSIS", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "TEXTCLIP", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "TEXTORIENTATION", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "BACKIMAGE", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "BACKIMAGEPRESS", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "BACKIMAGEHIGHLIGHT", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "BACKIMAGEINACTIVE", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "BACKIMAGEZOOM", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "FITTOBACKIMAGE", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "FRONTIMAGE", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "FRONTIMAGEPRESS", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "FRONTIMAGEHIGHLIGHT", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "FRONTIMAGEINACTIVE", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "CHECKRIGHT", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CHECKSIZE", iFlatToggleGetCheckSizeAttrib, iFlatToggleSetCheckSizeAttrib, NULL, NULL, IUPAF_NOT_MAPPED );
  iupClassRegisterAttribute( data, ic, "CHECKSPACING", iFlatToggleGetCheckSpacingAttrib, iFlatToggleSetCheckSpacingAttrib, IUPAF_SAMEASSYSTEM, "5", IUPAF_NOT_MAPPED );
  iupClassRegisterAttribute( data, ic, "CHECKALIGN", NULL, NULL, IUPAF_SAMEASSYSTEM, "ACENTER", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CHECKBGCOLOR", NULL, NULL, IUPAF_SAMEASSYSTEM, "TXTBGCOLOR", IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CHECKFGCOLOR", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CHECKHLCOLOR", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CHECKPSCOLOR", NULL, NULL, NULL, NULL, IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "CHECKIMAGE", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CHECKIMAGEPRESS", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CHECKIMAGEHIGHLIGHT", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CHECKIMAGEINACTIVE", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "CHECKIMAGEON", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CHECKIMAGEONPRESS", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CHECKIMAGEONHIGHLIGHT", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CHECKIMAGEONINACTIVE", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );

  iupClassRegisterAttribute( data, ic, "CHECKIMAGENOTDEF", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CHECKIMAGENOTDEFPRESS", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CHECKIMAGENOTDEFHIGHLIGHT", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );
  iupClassRegisterAttribute( data, ic, "CHECKIMAGENOTDEFINACTIVE", NULL, NULL, NULL, NULL, IUPAF_IHANDLENAME | IUPAF_NO_DEFAULTVALUE | IUPAF_NO_INHERIT );

  return ic;
}

IUP_API Ihandle *amy_IupFlatToggle( struct libData *data, const char *title )
{
  void *params[2];
  params[0] = (void*)title;
  params[1] = NULL;
  return amy_IupCreatev( data, "flattoggle", params );
}
