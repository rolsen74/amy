
/*
** SPDX-License-Identifier: Zlib
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
**
** Licensed under the zlib license. See the LICENSE file for details.
*/

#ifndef AMYLIB_PROTO_AMYZLIB_H
#define AMYLIB_PROTO_AMYZLIB_H

// --

#include "Amy_Defines.h"

// --
// AmigaOS4

#ifdef __amigaos4__

 #include <libraries/AmyZLib.h>
 #include <interfaces/AmyZLib.h>

 #ifdef __USE_INLINE__
 #include <inline4/AmyZLib.h>
 #endif

 #ifndef __NOLIBBASE__
 extern struct Library *AmyZLibBase;
 #endif

 #ifndef __NOGLOBALIFACE__
 extern struct AmyZLibIFace *IAmyZLib;
 #endif

#else // Other platforms

  #error Only support for AmigaOS4 .. at the moment

#endif

// --

#endif
