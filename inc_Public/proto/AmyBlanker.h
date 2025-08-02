
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_PROTO_AMYBLANKER_H
#define AMYLIB_PROTO_AMYBLANKER_H

// --

#include "Amy_Defines.h"

// --
// AmigaOS4

#ifdef __amigaos4__

 #include <libraries/AmyBlanker.h>
 #include <interfaces/AmyBlanker.h>

 #ifdef __USE_INLINE__
 #include <inline4/AmyBlanker.h>
 #endif

 #ifndef __NOLIBBASE__
 extern struct Library *AmyBlankerBase;
 #endif

 #ifndef __NOGLOBALIFACE__
 extern struct AmyBlankerIFace *IAmyBlanker;
 #endif

#else // Other platforms

  #error Only support for AmigaOS4 .. at the moment

#endif

// --

#endif
