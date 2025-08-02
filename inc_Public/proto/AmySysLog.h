
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_PROTO_AMYSYSLOG_H
#define AMYLIB_PROTO_AMYSYSLOG_H

// --

#include "Amy_Defines.h"

// --
// AmigaOS4

#ifdef __amigaos4__

 #include <libraries/AmySysLog.h>
 #include <interfaces/AmySysLog.h>

 #ifdef __USE_INLINE__
 #include <inline4/AmySysLog.h>
 #endif

 #ifndef __NOLIBBASE__
 extern struct Library *AmySysLogBase;
 #endif

 #ifndef __NOGLOBALIFACE__
 extern struct AmySysLogIFace *IAmySysLog;
 #endif

#else // Other platforms

  #error Only support for AmigaOS4 .. at the moment

#endif

// --

#endif
