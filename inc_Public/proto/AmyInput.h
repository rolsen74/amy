
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_PROTO_AMYINPUT_H
#define AMYLIB_PROTO_AMYINPUT_H

// --

#include "Amy_Defines.h"

// --
// AmigaOS4

#ifdef __amigaos4__

 #include <libraries/AmyInput.h>
 #include <interfaces/AmyInput.h>

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
