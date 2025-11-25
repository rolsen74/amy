
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

#ifndef AMYLIB_PROTO_AMYIUP_H
#define AMYLIB_PROTO_AMYIUP_H

// --

#include "Amy_Defines.h"

// --
// AmigaOS4

#ifdef __amigaos4__

 #include <IUP/iup.h>
 #include <interfaces/AmyIUP.h>

 #ifdef __USE_INLINE__
 #include <inline4/AmyIUP.h>
 #endif

 #ifndef __NOLIBBASE__
 extern struct Library *AmyIUPBase;
 #endif

 #ifndef __NOGLOBALIFACE__
 extern struct AmyIUPIFace *IAmyIUP;
 #endif

#else // Other platforms

  #error Only support for AmigaOS4 .. at the moment

#endif

// --

#endif
