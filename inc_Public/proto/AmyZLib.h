
/*
** SPDX-License-Identifier: Zlib
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
**
** Licensed under the zlib license. See the LICENSE file for details.
*/

#ifndef __PROTO_AMYZLIB_H__
#define __PROTO_AMYZLIB_H__

// --

#ifndef __AMY_STANDARD_H__
#include "Amy_Standard.h"
#endif

// --
// AmigaOS4

#ifdef __amigaos4__

 #ifndef __LIBRARIES_AMYZLIB_H__
 #include <libraries/AmyZLib.h>
 #endif

 #ifndef __INTERFACES_AMYZLIB_H__
 #include <interfaces/AmyZLib.h>
 #endif

 #ifdef __USE_INLINE__
 #ifndef __INLINE4_AMYZLIB_H__
 #include <inline4/AmyZLib.h>
 #endif
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
