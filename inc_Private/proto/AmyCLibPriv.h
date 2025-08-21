
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Portions based on clib2 by Olaf Barthel (2002–2016)
** Target OS: AmigaOS
*/

#ifndef AMYLIB_PROTO_AMYCLIBPRIV_H
#define AMYLIB_PROTO_AMYCLIBPRIV_H

// --

#include "Amy_Defines.h"

// --
// AmigaOS4

#ifdef __amigaos4__

 #include <libraries/AmyCLibPriv.h>
 #include <interfaces/AmyCLibPriv.h>

 #ifdef __USE_INLINE__
 #include <inline4/AmyCLibPriv.h>
 #endif

 #ifndef __NOLIBBASE__
 extern struct Library *AmyCLibPrivBase;
 #endif

 #ifndef __NOGLOBALIFACE__
 extern struct AmyCLibPrivIFace *IAmyCLibPriv;
 #endif

#else // Other platforms

  #error Only support for AmigaOS4 .. at the moment

#endif

// --

#endif
