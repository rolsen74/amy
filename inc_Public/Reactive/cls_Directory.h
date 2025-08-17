
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#ifndef REACTIVE_CLS_DIRECTORY_H
#define REACTIVE_CLS_DIRECTORY_H

/****************************************************************************/

#define RAC_Directory						"Directory.ra"

/****************************************************************************/

#define RAA_DIR_Path						( RAB_Directory + 0 )  // [I...] STR

#define RAA_DIR_Pattern						( RAB_Directory + 1 )  // [I...] STR

#define RAA_DIR_DataFields					( RAB_Directory + 2 )  // [I...] U32

#define RAA_DIR_IOErr						( RAB_Directory + 3 )  // [..G.] U32

#define RAA_DIR_IOErrString					( RAB_Directory + 4 )  // [..G.] STR

#define RAA_DIR_Entries						( RAB_Directory + 5 )  // [..G.] U32

/****************************************************************************/

#define RAM_DIR_Scan						( RAB_Directory + 1000 )

struct  RAP_DIR_Scan
{
	U32 					MethodID;
};

/****************************************************************************/

#define RAM_DIR_Sort						( RAB_Directory + 1001 )

struct  RAP_DIR_Sort
{
	U32						MethodID;
	U32						SortMode;
};

/****************************************************************************/

#define RAM_DIR_GetEntry					( RAB_Directory + 1002 )

struct  RAP_DIR_GetEntry
{
	U32 					MethodID;
	U32 *					ID;
	struct ExamineData **	Dat;
};

/****************************************************************************/

#define RAM_DIR_Clear						( RAB_Directory + 1003 )

struct  RAP_DIR_Clear
{
	U32 					MethodID;
};

/****************************************************************************/

#define RAM_DIR_IsFile						( RAB_Directory + 1004 )

struct  RAP_DIR_IsFile
{
	U32 					MethodID;
	STR						FullPath;
};

/****************************************************************************/

#define RAM_DIR_IsDir						( RAB_Directory + 1005 )

struct  RAP_DIR_IsDir
{
	U32 					MethodID;
	STR						FullPath;
};

/****************************************************************************/

#endif

