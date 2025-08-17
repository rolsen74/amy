
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2018-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef MAIN_H
#define MAIN_H

#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/AmyCLib.h>
#include <proto/Reactive.h>

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

// --

extern PTR RAAppObject;
extern STR DefaultScript;
extern STR CompileScript;
extern U32 Stat_Entries;
extern U32 Stat_Skipped;
extern U32 Stat_Passed;
extern U32 Stat_Failed;

// --

S32		BuildScript(	STR Script, STR FileName );
void	ScanDir(		STR path );
void	ScanFile(		STR path );
void	TestFile(		STR FileName, U32 CurrentEntry );

// --

#endif
