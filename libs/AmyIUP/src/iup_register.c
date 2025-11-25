
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
  Iclass *old_ic = (Iclass*) iupTableGet( data, data->iregister_table, ic->name );
  if (old_ic)
    iupClassRelease( data, old_ic );

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
  iupRegisterClassInternal( data, iupDialogNewClass( data ));
  iupRegisterClassInternal( data, iupMessageDlgNewClass( data ));
  iupRegisterClassInternal( data, iupColorDlgNewClass( data ));
  iupRegisterClassInternal( data, iupFontDlgNewClass( data ));
  iupRegisterClassInternal( data, iupFileDlgNewClass( data ));
  iupRegisterClassInternal( data, iupProgressDlgNewClass( data ));
  iupRegisterClassInternal( data, iupParamBoxNewClass( data ));
  iupRegisterClassInternal( data, iupParamNewClass( data ));

  iupRegisterClassInternal( data, iupTimerNewClass( data ));
  iupRegisterClassInternal( data, iupImageNewClass( data ));
  iupRegisterClassInternal( data, iupImageRGBNewClass( data ));
  iupRegisterClassInternal( data, iupImageRGBANewClass( data ));
  iupRegisterClassInternal( data, iupUserNewClass( data ));
  iupRegisterClassInternal( data, iupClipboardNewClass( data ));
  iupRegisterClassInternal( data, iupThreadNewClass( data ));

  iupRegisterClassInternal( data, iupRadioNewClass( data ));
  iupRegisterClassInternal( data, iupFillNewClass( data ));
  iupRegisterClassInternal( data, iupHboxNewClass( data ));
  iupRegisterClassInternal( data, iupVboxNewClass( data ));
  iupRegisterClassInternal( data, iupZboxNewClass( data ));
  iupRegisterClassInternal( data, iupCboxNewClass( data ));
  iupRegisterClassInternal( data, iupSboxNewClass( data ));
  iupRegisterClassInternal( data, iupNormalizerNewClass( data ));
  iupRegisterClassInternal( data, iupSplitNewClass( data ));
  iupRegisterClassInternal( data, iupExpanderNewClass( data ));
  iupRegisterClassInternal( data, iupDetachBoxNewClass( data ));

  iupRegisterClassInternal( data, iupMenuNewClass( data ));
  iupRegisterClassInternal( data, iupItemNewClass( data ));
  iupRegisterClassInternal( data, iupSeparatorNewClass( data ));
  iupRegisterClassInternal( data, iupSubmenuNewClass( data ));

  iupRegisterClassInternal( data, iupLabelNewClass( data ));
  iupRegisterClassInternal( data, iupButtonNewClass( data ));
  iupRegisterClassInternal( data, iupToggleNewClass( data ));
  iupRegisterClassInternal( data, iupCanvasNewClass( data ));
  iupRegisterClassInternal( data, iupFrameNewClass( data ));
  iupRegisterClassInternal( data, iupTextNewClass( data ));
  iupRegisterClassInternal( data, iupMultilineNewClass( data ));
  iupRegisterClassInternal( data, iupListNewClass( data ));
  iupRegisterClassInternal( data, iupFlatLabelNewClass( data ));
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
