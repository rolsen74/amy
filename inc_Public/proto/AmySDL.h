
/*
** SPDX-License-Identifier: LGPL-2.1-or-later
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_PROTO_AMYSDL_H
#define AMYLIB_PROTO_AMYSDL_H

// --

#include "Amy_Defines.h"

// --
// AmigaOS4

#ifdef __amigaos4__

 #include <libraries/AmySDL.h>
 #include <interfaces/AmySDL.h>

 #ifdef __USE_INLINE__
 #include <inline4/AmySDL.h>
 #endif

 #ifndef __NOLIBBASE__
 extern struct Library *AmySDLBase;
 #endif

 #ifndef __NOGLOBALIFACE__
 extern struct AmySDLIFace *IAmySDL;
 #endif

#else // Other platforms

  #error Only support for AmigaOS4 .. at the moment

#endif

// --

#endif
