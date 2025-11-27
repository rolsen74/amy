
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
* \brief Register the Internal Controls
*
* See Copyright Notice in "iup.h"
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdarg.h>

#include "iup.h"

#include "iup_object.h"
#include "iup_register.h"
#include "iup_stdcontrols.h"


static Itable *data->iregister_table = NULL;   /* table indexed by name containing Iclass *address */

#endif

void iupRegisterInit( struct libData *data )
{
	data->iregister_table = iupTableCreate( data, IUPTABLE_STRINGINDEXED );
}

void iupRegisterFinish( struct libData *data )
{
  char *name = iupTableFirst( data, data->iregister_table );
  while (name)
  {
    Iclass *ic = (Iclass*) iupTableGetCurr( data, data->iregister_table );
    iupClassRelease( data, ic );
    name = iupTableNext( data, data->iregister_table );
  }

  iupTableDestroy( data, data->iregister_table );
  data->iregister_table = NULL;
}

IUP_API int amy_IupGetAllClasses( struct libData *data, char** list, int n )
{
  int i = 0;
  char *name;

  if ( ! list || n==0 || n==-1)
    return iupTableCount( data, data->iregister_table );

  name = iupTableFirst( data, data->iregister_table );
  while (name)
  {
    list[i] = name;
    i++;
    if ( i == n)
      break;

    name = iupTableNext( data, data->iregister_table );
  }

  return i;
}

IUP_SDK_API Iclass *iupRegisterFindClass( struct libData *data, const char *name)
{
  return (Iclass*) iupTableGet( data, data->iregister_table, name );
}

static void iupRegisterClassInternal( struct libData *data, Iclass *ic )
{
	if ( ! ic )
	{
		// rwo : Added check
		return;
	}

	Iclass *old_ic = (Iclass*) iupTableGet( data, data->iregister_table, ic->name );

	if ( old_ic )
	{
		iupClassRelease( data, old_ic );
	}

	ic->is_internal = 1;

	iupTableSet( data, data->iregister_table, ic->name, (void*)ic, IUPTABLE_POINTER );
}

IUP_SDK_API void iupRegisterClass( struct libData *data, Iclass *ic )
{
  Iclass *old_ic = (Iclass*) iupTableGet( data, data->iregister_table, ic->name );
  if (old_ic)
    iupClassRelease( data, old_ic );

  iupTableSet( data, data->iregister_table, ic->name, (void*)ic, IUPTABLE_POINTER );
}

void iupRegisterUpdateClasses( struct libData *data )
{
  char *name = iupTableFirst( data, data->iregister_table );
  while (name)
  {
    Iclass *ic = (Iclass*) iupTableGetCurr( data, data->iregister_table );
    iupClassUpdate( data, ic );
    name = iupTableNext( data, data->iregister_table );
  }
}


/***************************************************************/

void iupRegisterInternalClasses( struct libData *data )
{
	IExec->DebugPrintF( "iupRegisterInternalClasses : 1\n" ),
	iupRegisterClassInternal( data, iupDialogNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 2\n" ),
	iupRegisterClassInternal( data, iupMessageDlgNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 3\n" ),
	iupRegisterClassInternal( data, iupColorDlgNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 4\n" ),
	iupRegisterClassInternal( data, iupFontDlgNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 5\n" ),
	iupRegisterClassInternal( data, iupFileDlgNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 6\n" ),
	iupRegisterClassInternal( data, iupProgressDlgNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 7\n" ),
	iupRegisterClassInternal( data, iupParamBoxNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 8\n" ),
	iupRegisterClassInternal( data, iupParamNewClass( data ));

	IExec->DebugPrintF( "iupRegisterInternalClasses : 9\n" ),
	iupRegisterClassInternal( data, iupTimerNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 10\n" ),
	iupRegisterClassInternal( data, iupImageNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 11\n" ),
	iupRegisterClassInternal( data, iupImageRGBNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 12\n" ),
	iupRegisterClassInternal( data, iupImageRGBANewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 13\n" ),
	iupRegisterClassInternal( data, iupUserNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 14\n" ),
	iupRegisterClassInternal( data, iupClipboardNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 15\n" ),
	iupRegisterClassInternal( data, iupThreadNewClass( data ));

	IExec->DebugPrintF( "iupRegisterInternalClasses : 16\n" ),
	iupRegisterClassInternal( data, iupRadioNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 17\n" ),
	iupRegisterClassInternal( data, iupFillNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 18\n" ),
	iupRegisterClassInternal( data, iupHboxNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 19\n" ),
	iupRegisterClassInternal( data, iupVboxNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 20\n" ),
	iupRegisterClassInternal( data, iupZboxNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 21\n" ),
	iupRegisterClassInternal( data, iupCboxNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 22\n" ),
	iupRegisterClassInternal( data, iupSboxNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 23\n" ),
	iupRegisterClassInternal( data, iupNormalizerNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 24\n" ),
	iupRegisterClassInternal( data, iupSplitNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 25\n" ),
	iupRegisterClassInternal( data, iupExpanderNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 26\n" ),
	iupRegisterClassInternal( data, iupDetachBoxNewClass( data ));

	IExec->DebugPrintF( "iupRegisterInternalClasses : 27\n" ),
	iupRegisterClassInternal( data, iupMenuNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 28\n" ),
	iupRegisterClassInternal( data, iupItemNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 29\n" ),
	iupRegisterClassInternal( data, iupSeparatorNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 30\n" ),
	iupRegisterClassInternal( data, iupSubmenuNewClass( data ));

	IExec->DebugPrintF( "iupRegisterInternalClasses : 31\n" ),
	iupRegisterClassInternal( data, iupLabelNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 32\n" ),
	iupRegisterClassInternal( data, iupButtonNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 33\n" ),
	iupRegisterClassInternal( data, iupToggleNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 34\n" ),
	iupRegisterClassInternal( data, iupCanvasNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 35\n" ),
	iupRegisterClassInternal( data, iupFrameNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 36\n" ),
	iupRegisterClassInternal( data, iupTextNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 37\n" ),
	iupRegisterClassInternal( data, iupMultilineNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 38\n" ),
	iupRegisterClassInternal( data, iupListNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 39\n" ),
	iupRegisterClassInternal( data, iupFlatLabelNewClass( data ));
	IExec->DebugPrintF( "iupRegisterInternalClasses : 40\n" ),
	iupRegisterClassInternal( data, iupFlatButtonNewClass( data ));
	iupRegisterClassInternal( data, iupFlatToggleNewClass( data ));
	iupRegisterClassInternal( data, iupFlatSeparatorNewClass( data ));
	iupRegisterClassInternal( data, iupDropButtonNewClass( data ));
	iupRegisterClassInternal( data, iupCalendarNewClass( data ));
	iupRegisterClassInternal( data, iupDatePickNewClass( data ));
	iupRegisterClassInternal( data, iupSpaceNewClass( data ));

	iupRegisterClassInternal( data, iupProgressBarNewClass( data ));
	iupRegisterClassInternal( data, iupValNewClass( data ));
	iupRegisterClassInternal( data, iupTabsNewClass( data ));
	iupRegisterClassInternal( data, iupSpinNewClass( data ));
	iupRegisterClassInternal( data, iupSpinboxNewClass( data ));
	iupRegisterClassInternal( data, iupTreeNewClass( data ));
	iupRegisterClassInternal( data, iupScrollBoxNewClass( data ));
	iupRegisterClassInternal( data, iupBackgroundBoxNewClass( data ));
	iupRegisterClassInternal( data, iupLinkNewClass( data ));
	iupRegisterClassInternal( data, iupGridBoxNewClass( data ));
	iupRegisterClassInternal( data, iupAnimatedLabelNewClass( data ));
	iupRegisterClassInternal( data, iupFlatFrameNewClass( data ));
	iupRegisterClassInternal( data, iupFlatTabsNewClass( data ));
	iupRegisterClassInternal( data, iupFlatScrollBoxNewClass( data ));
	iupRegisterClassInternal( data, iupDialNewClass( data ));
	iupRegisterClassInternal( data, iupGaugeNewClass( data ));
	iupRegisterClassInternal( data, iupColorbarNewClass( data ));
	iupRegisterClassInternal( data, iupColorBrowserNewClass( data ));
	iupRegisterClassInternal( data, iupMultiBoxNewClass( data ));
	iupRegisterClassInternal( data, iupFlatListNewClass( data ));
	iupRegisterClassInternal( data, iupFlatValNewClass( data ));
	iupRegisterClassInternal( data, iupFlatTreeNewClass( data ));
}
