
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Portions based on clib2 by Olaf Barthel (2002–2016)
** Target OS: AmigaOS
*/

#ifndef __PROTO_AMYCLIB_H__
#define __PROTO_AMYCLIB_H__

// --

#ifndef __AMY_STANDARD_H__
#include "Amy_Standard.h"
#endif

// --
// AmigaOS4

#ifdef __amigaos4__

 #ifndef __LIBRARIES_AMYCLIB_H__
 #include <libraries/AmyCLib.h>
 #endif

 #ifndef __INTERFACES_AMYCLIB_H__
 #include <interfaces/AmyCLib.h>
 #endif

 #ifdef __USE_INLINE__
 #ifndef __INLINE4_AMYCLIB_H__
 #include <inline4/AmyCLib.h>
 #endif
 #endif

 #ifndef __NOLIBBASE__
 extern struct Library *AmyCLibBase;
 #endif

 #ifndef __NOGLOBALIFACE__
 extern struct AmyCLibIFace *IAmyCLib;
 #endif

#else // Other platforms

  #error Only support for AmigaOS4 .. at the moment

#endif

// --

#endif
