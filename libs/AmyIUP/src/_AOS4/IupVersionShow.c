
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"

// --
// AmigaOS4 specific code

IUP_API void amy_IupVersionShow( struct libData *data )
{
	#if 0
	Ihandle* dlg, *info, *ok;
	char* value;

	info = IupText(NULL);
	IupSetAttribute(info, "MULTILINE", "Yes");
	IupSetAttribute(info, "EXPAND", "Yes");
	IupSetAttribute(info, "READONLY", "Yes");
	IupSetAttribute(info, "VISIBLELINES", "10");
	IupSetAttribute(info, "VISIBLECOLUMNS", "30");

	ok = IupButton("_@IUP_OK", NULL);
	IupSetStrAttribute(ok, "PADDING", amy_IupGetGlobal( data, "DEFAULTBUTTONPADDING"));
	IupSetCallback(ok, "ACTION", (Icallback)ok_action);

	dlg = IupDialog(IupVbox(info, ok, NULL));

	IupSetAttribute(dlg,"TITLE","IUP Version");
	IupSetAttribute(dlg,"DIALOGFRAME","YES");
	IupSetAttribute(dlg,"DIALOGHINT","YES");
	IupSetAttribute(dlg, "RESIZE", "YES");
	IupSetAttribute(dlg, "GAP", "10");
	IupSetAttribute(dlg,"MARGIN","10x10");
	IupSetAttribute(IupGetChild(dlg, 0), "ALIGNMENT", "ACENTER");
	IupSetAttribute(dlg, "PARENTDIALOG", amy_IupGetGlobal( data, "PARENTDIALOG"));
	IupSetAttribute(dlg, "ICON", amy_IupGetGlobal( data, "ICON"));
	IupSetAttributeHandle(dlg, "DEFAULTESC", ok);

	IupMap(dlg);

	IupSetAttribute(info, "APPEND", IUP_NAME);
	IupSetAttribute(info, "APPEND", IUP_COPYRIGHT);
	IupSetAttribute(info, "APPEND", "");

	IupSetStrf(info, "APPEND", "IUP %s - %s", IupVersion(), IupVersionDate());
	IupSetStrf(info, "APPEND", "   Driver: %s", amy_IupGetGlobal( data, "DRIVER"));
	IupSetStrf(info, "APPEND", "   System: %s", amy_IupGetGlobal( data, "SYSTEM"));
	IupSetStrf(info, "APPEND", "   System Version: %s", amy_IupGetGlobal( data, "SYSTEMVERSION"));

	value = amy_IupGetGlobal( data, "MOTIFVERSION");
	if (value) IupSetStrf(info, "APPEND", "   Motif Version: %s", value);

	value = amy_IupGetGlobal( data, "GTKVERSION");
	if (value) IupSetStrf(info, "APPEND", "   GTK Version: %s", value);

	IupSetStrf(info, "APPEND", "   Screen Size: %s", amy_IupGetGlobal( data, "SCREENSIZE"));
	IupSetStrf(info, "APPEND", "   Screen DPI: %d", IupGetInt(NULL, "SCREENDPI"));
	IupSetStrf(info, "APPEND", "   Default Font: %s", amy_IupGetGlobal( data, "DEFAULTFONT"));

	IupSetAttribute(info, "APPEND", "");
	IupSetAttribute(info, "APPEND", "Iup Libraries Open:");

	if (amy_IupGetGlobal( data, "_IUP_IMAGELIB_OPEN"))
		IupSetAttribute(info, "APPEND", "   IupImageLibOpen");

	if (amy_IupGetGlobal( data, "_IUP_CONTROLS_OPEN"))
	{
		IupSetAttribute(info, "APPEND", "   IupControlsOpen");

		IupSetStrf(info, "APPEND", "      CD %s - %s", amy_IupGetGlobal( data, "CD_VERSION"), amy_IupGetGlobal( data, "CD_VERSIONDATE"));
	}

	if (amy_IupGetGlobal( data, "_IUP_IM_OPEN"))
	{
		IupSetAttribute(info, "APPEND", "   IupImOpen");

		IupSetStrf(info, "APPEND", "      IM %s - %s", amy_IupGetGlobal( data, "IM_VERSION"), amy_IupGetGlobal( data, "IM_VERSIONDATE"));
	}

	if (amy_IupGetGlobal( data, "_IUP_GLCANVAS_OPEN"))
	{
		IupSetAttribute(info, "APPEND", "   IupGLCanvasOpen");

		if (amy_IupGetGlobal( data, "GL_VERSION"))
		{
		IupSetStrf(info, "APPEND", "      OpenGL Vendor: %s", amy_IupGetGlobal( data, "GL_VENDOR"));
		IupSetStrf(info, "APPEND", "      OpenGL Renderer: %s", amy_IupGetGlobal( data, "GL_RENDERER"));
		IupSetStrf(info, "APPEND", "      OpenGL Version: %s", amy_IupGetGlobal( data, "GL_VERSION"));
		}
	}

	if (amy_IupGetGlobal( data, "_IUP_GLCONTROLS_OPEN"))
		IupSetAttribute(info, "APPEND", "   IupGLControlsOpen");

	if (amy_IupGetGlobal( data, "_IUP_SCINTILLA_OPEN"))
	{
		IupSetAttribute(info, "APPEND", "   IupScintillaOpen");
		IupSetStrf(info, "APPEND", "      Scintilla %s", amy_IupGetGlobal( data, "SCINTILLA_VERSION"));
	}

	if (amy_IupGetGlobal( data, "_IUP_WEBBROWSER_OPEN"))
		IupSetAttribute(info, "APPEND", "   IupWebBrowserOpen");

	if (amy_IupGetGlobal( data, "_IUP_PLOT_OPEN"))
		IupSetAttribute(info, "APPEND", "   IupPlotOpen");

	if (amy_IupGetGlobal( data, "_IUP_MGLPLOT_OPEN"))
		IupSetAttribute(info, "APPEND", "   IupMglPlotOpen");

	IupPopup(dlg, IUP_CENTERPARENT, IUP_CENTERPARENT);
	IupDestroy(dlg);
	#endif
}
