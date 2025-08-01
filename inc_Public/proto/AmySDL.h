
/*
** SPDX-License-Identifier: LGPL-2.1-or-later
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef __PROTO_AMYSDL_H__
#define __PROTO_AMYSDL_H__

// --

#ifndef __AMY_STANDARD_H__
#include "Amy_Standard.h"
#endif

// --
// AmigaOS4

#ifdef __amigaos4__

 #ifndef __LIBRARIES_AMYSDL_H__
 #include <libraries/AmyInput.h>
 #endif

 #ifndef __INTERFACES_AMYSDL_H__
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
