
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_PROTO_REACTIVEPRIV_H
#define AMYLIB_PROTO_REACTIVEPRIV_H

// --

#include "Amy_Defines.h"

// --
// AmigaOS4

#ifdef __amigaos4__

 #include <libraries/ReactivePriv.h>
 #include <interfaces/ReactivePriv.h>

 #ifdef __USE_INLINE__
 #include <inline4/ReactivePriv.h>
 #endif

 #ifndef __NOLIBBASE__
 extern struct Library *ReactivePrivBase;
 #endif

 #ifndef __NOGLOBALIFACE__
 extern struct ReactivePrivIFace *IReactivePriv;
 #endif

#else // Other platforms

  #error Only support for AmigaOS4 .. at the moment

#endif

// --

#endif
