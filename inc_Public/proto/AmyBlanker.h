
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef __PROTO_AMYBLANKER_H__
#define __PROTO_AMYBLANKER_H__

// --

#ifndef __AMY_STANDARD_H__
#include "Amy_Standard.h"
#endif

// --
// AmigaOS4

#ifdef __amigaos4__

 #ifndef __LIBRARIES_AMYBLANKER_H__
 #include <libraries/AmyBlanker.h>
 #endif

 #ifndef __INTERFACES_AMYBLANKER_H__
 #include <interfaces/AmyBlanker.h>
 #endif

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
