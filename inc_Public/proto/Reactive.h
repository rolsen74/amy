
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_PROTO_REACTIVE_H
#define AMYLIB_PROTO_REACTIVE_H

// --

#include "Amy_Defines.h"

// --
// AmigaOS4

#ifdef __amigaos4__

 #include <libraries/Reactive.h>
 #include <interfaces/Reactive.h>

 #ifdef __USE_INLINE__
 #include <inline4/Reactive.h>
 #endif

 #ifndef __NOLIBBASE__
 extern struct Library *ReactiveBase;
 #endif

 #ifndef __NOGLOBALIFACE__
 extern struct ReactiveIFace *IReactive;
 #endif

#else // Other platforms

  #error Only support for AmigaOS4 .. at the moment

#endif

// --

#endif
