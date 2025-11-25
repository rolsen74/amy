
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
 * \brief Windows Driver Core
 *
 * See Copyright Notice in "iup.h"
 */

#include <stdio.h>             
#include <stdlib.h>

#include "iup.h"

#include "iup_str.h"
#include "iup_globalattrib.h"
#include "iup_names.h"
#include "iup_func.h"
#include "iup_drv.h"
#include "iup_drvinfo.h"
#include "iup_drvfont.h"
#include "iup_predialogs.h"
#include "iup_class.h"
#include "iup_register.h"
#include "iup_key.h"
#include "iup_image.h"
#include "iup_dlglist.h"
#include "iup_assert.h"
#include "iup_strmessage.h"

#endif


//static int iup_opened = 0;
static int iup_dummy_argc = 0;
static char** iup_dummy_argv = {0};

IUP_API int amy_IupIsOpened( struct libData *data )
{
  return data->iup_opened;
}

IUP_API int amy_IupOpen( struct libData *data, int *argc, char ***argv )
{
	if ( data->iup_opened )
		return IUP_OPENED;

	if ( ! argc || !(*argc) || !argv)
	{
		argc = &iup_dummy_argc;
		argv = &iup_dummy_argv;
	}

	iupNamesInit( data );
	iupFuncInit( data );
	iupStrMessageInit( data );
	iupGlobalAttribInit( data ); 
	iupRegisterInit( data );
	iupKeyInit( data );
	iupImageStockInit( data );

	amy_IupSetLanguage( data, "ENGLISH" );
	amy_IupSetGlobal( data, "VERSION", amy_IupVersion( data ));
	amy_IupSetGlobal( data, "COPYRIGHT",  IUP_COPYRIGHT );

	if (iupdrvOpen( data, argc, argv ) == IUP_NOERROR)
	{
		char *value;

		iupdrvFontInit( data );

		amy_IupStoreGlobal( data, "SYSTEM", iupdrvGetSystemName( data ));
		amy_IupStoreGlobal( data, "SYSTEMVERSION", iupdrvGetSystemVersion( data ));
		amy_IupStoreGlobal( data, "COMPUTERNAME", iupdrvGetComputerName( data ));
		amy_IupStoreGlobal( data, "USERNAME", iupdrvGetUserName( data ));

		amy_IupSetGlobal( data, "DEFAULTFONT", iupdrvGetSystemFont( data ));  /* Use SetGlobal because iupdrvGetSystemFont returns a static string */
		amy_IupSetGlobal( data, "DEFAULTPRECISION", "2" );
		amy_IupSetGlobal( data, "DEFAULTBUTTONPADDING", "12x4" );  /* used by pre-defined dialogs */

		iupRegisterInternalClasses( data );

		value = getenv("IUP_QUIET" );
		if (value && !iupStrBoolean(value)) /* if not defined do NOT print */
		printf("IUP %s %s\n", amy_IupVersion( data ), IUP_COPYRIGHT );

		value = getenv("IUP_VERSION" );
		if (iupStrBoolean(value))
		amy_IupVersionShow( data );

		data->iup_opened = 1;
		return IUP_NOERROR;
	}
	else
	{
	#ifdef  IUP_ASSERT
		/* can not use pre-defined dialogs here, so only output to console. */
		fprintf(stderr, "IUP ERROR: amy_IupOpen failed.\n" );
	#endif
		return IUP_ERROR;
	}
}

IUP_API void amy_IupClose( struct libData *data )
{
	if ( ! data->iup_opened)
		return;

	data->iup_opened = 0;

	iupdrvSetIdleFunction( data, NULL );  /* stop any idle */

	iupDlgListDestroyAll( data );    /* destroy all dialogs and their children */
	iupNamesDestroyHandles( data );  /* destroy everything that do not belong to a dialog */
	iupImageStockFinish( data );     /* release stock images hash table and the images */

	iupRegisterFinish( data );  /* release native classes */

	iupdrvFontFinish( data );   /* release font cache */
	iupdrvClose( data );        /* release native handles and allocated memory */

	iupGlobalAttribFinish( data );  /* release global hash table */
	iupStrMessageFinish( data );    /* release messages hash table */
	iupFuncFinish( data );          /* release callbacks hash table */
	iupNamesFinish( data );         /* release names hash table */

	iupStrGetMemory(-1 ); /* Frees internal buffer */
}
