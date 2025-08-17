
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#ifndef REACTIVE_RA_PLUGIN_H
#define REACTIVE_RA_PLUGIN_H

/***[ Plugin ]**************************************************************/

struct RA_Plugin
{
	// Unique Header for identifying a Plugin,
	//MatchWord must be set to ID_RA3Plugin
	U32							RA_Plugin_MatchWord;
	struct RA_Plugin *			RA_Plugin_MatchTag;

	// Memory pointers for DOS, those should be set to NULL.
	U32							RA_Plugin_LoadSeg;
	struct NotifyRequest *		RA_Plugin_NotifyRequest;
	STR							RA_Plugin_PathName;

	// If ClassDataSize is none zero, some memory will be allocated
	// and the pointer placed in Class/Style Data.
	PTR							RA_Plugin_Data;
	U32							RA_Plugin_DataSize;

	// Init will be called before its added to the system. A U32 will
	// indicate if Init Succeded or failed. Exit will be called before
	// expunge from memory.. One or Both can be NULL.

	U32							( *RA_Plugin_Init ) ( struct ExecIFace *, struct RA_Plugin * );
	U32							( *RA_Plugin_Exit ) ( struct ExecIFace *, struct RA_Plugin * );

	// Data used to create a Public Class.
	STR							RA_Plugin_Super;
	STR							RA_Plugin_PubName;
	U32							RA_Plugin_ObjectDataSize;

	PTR							RA_Plugin_Dispatcher;
};

#define ID_RAPlugin			(('P'<<24)+('l'<<16)+('g'<<8)+3)

/***************************************************************************/

#endif
