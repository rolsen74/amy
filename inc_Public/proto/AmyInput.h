
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen <renewolsen@gmail.com>
*/

#ifndef __PROTO_AMYINPUT_H__
#define __PROTO_AMYINPUT_H__

// --

#ifndef __AMY_STANDARD_H__
#include "Amy_Standard.h"
#endif

// --
// AmigaOS4

#ifdef __amigaos4__

 #ifndef __LIBRARIES_AMYINPUT_H__
 #include <libraries/AmyInput.h>
 #endif

 #ifndef __INTERFACES_AMYINPUT_H__
 #include <interfaces/AmyInput.h>
 #endif

 #ifdef __USE_INLINE__
 #include <inline4/AmyInput.h>
 #endif

 #ifndef __NOLIBBASE__
 extern struct Library *AmyInputBase;
 #endif

 #ifndef __NOGLOBALIFACE__
 extern struct AmyInputIFace *IAmyInput;
 #endif

#else // Other platforms

  #error Only support for AmigaOS4 .. at the moment

#endif

// --

#endif
