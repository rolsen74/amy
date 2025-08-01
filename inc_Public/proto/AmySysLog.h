
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef __PROTO_AMYSYSLOG_H__
#define __PROTO_AMYSYSLOG_H__

// --

#ifndef __AMY_STANDARD_H__
#include "Amy_Standard.h"
#endif

// --
// AmigaOS4

#ifdef __amigaos4__

 #ifndef __LIBRARIES_AMYSYSLOG_H__
 #include <libraries/AmySysLog.h>
 #endif

 #ifndef __INTERFACES_AMYSYSLOG_H__
 #include <interfaces/AmySysLog.h>
 #endif

 #ifdef __USE_INLINE__
 #ifndef __INLINE4_AMYSYSLOG_H__
 #include <inline4/AmySysLog.h>
 #endif
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
