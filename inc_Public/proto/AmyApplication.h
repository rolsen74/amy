
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_PROTO_AMYAPPLICATION_H
#define AMYLIB_PROTO_AMYAPPLICATION_H

// --

#include "Amy_Defines.h"

// --
// AmigaOS4

#ifdef __amigaos4__

 #include <libraries/AmyApplication.h>
 #include <interfaces/AmyApplication.h>

 #ifdef __USE_INLINE__
 #include <inline4/AmyApplication.h>
 #endif

 #ifndef __NOLIBBASE__
 extern struct Library *AmyApplicationBase;
 #endif

 #ifndef __NOGLOBALIFACE__
 extern struct AmyApplicationIFace *IAmyApplication;
 #endif

#else // Other platforms

  #error Only support for AmigaOS4 .. at the moment

#endif

// --

#endif
