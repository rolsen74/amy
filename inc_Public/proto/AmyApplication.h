
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen <renewolsen@gmail.com>
*/

#ifndef __PROTO_AMYAPPLICATION_H__
#define __PROTO_AMYAPPLICATION_H__

// --

#ifndef __AMY_STANDARD_H__
#include "Amy_Standard.h"
#endif

// --
// AmigaOS4

#ifdef __amigaos4__

 #ifndef __LIBRARIES_AMYAPPLICATION_H__
 #include <libraries/AmyApplication.h>
 #endif

 #ifndef __INTERFACES_AMYAPPLICATION_H__
 #include <interfaces/AmyApplication.h>
 #endif

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
