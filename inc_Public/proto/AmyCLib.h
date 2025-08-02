
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Portions based on clib2 by Olaf Barthel (2002–2016)
** Target OS: AmigaOS
*/

#ifndef AMYLIB_PROTO_AMYCLIB_H
#define AMYLIB_PROTO_AMYCLIB_H

// --

#include "Amy_Defines.h"

// --
// AmigaOS4

#ifdef __amigaos4__

 #include <libraries/AmyCLib.h>
 #include <interfaces/AmyCLib.h>

 #ifdef __USE_INLINE__
 #include <inline4/AmyCLib.h>
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
