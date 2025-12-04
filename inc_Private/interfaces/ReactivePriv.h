
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_INTERFACES_REACTIVEPRIV_H
#define AMYLIB_INTERFACES_REACTIVEPRIV_H

// --

#include "Amy_Defines.h"

// --

struct ReactivePrivIFace
{
	struct InterfaceData Data;
/* 0000 */	U32						AMY_FUNC (*Obtain)(struct ReactivePrivIFace *Self);
/* 0001 */	U32						AMY_FUNC (*Release)(struct ReactivePrivIFace *Self);
/* 0002 */	void					AMY_FUNC (*Expunge)(struct ReactivePrivIFace *Self);
/* 0003 */	struct Interface *		AMY_FUNC (*Clone)(struct ReactivePrivIFace *Self);

// -- Arguments
/*   81 */	PTR						AMY_FUNC (*Arguments_ParseList)( struct ReactivePrivIFace *Self, struct RAArguments *Args, struct TagItem *taglist );
/*   82 */	PTR						AMY_FUNC (*Arguments_ParseTags)( struct ReactivePrivIFace *Self, struct RAArguments *Args, ... );
/*   83 */	U32						AMY_FUNC (*Arguments_Free)( struct ReactivePrivIFace *Self, PTR Args );

// -- Attributes
/*  101 */	U32						AMY_FUNC (*Attr_Get)(struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, U32 AttrID, PTR Storage);
/*  102 */	U32						AMY_FUNC (*Attr_GetTags)(struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, ...);
/*  103 */	U32						AMY_FUNC (*Attr_GetList)(struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, struct TagItem * taglist);
/*  104 */	U32						AMY_FUNC (*Attr_GetSuper)(struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, U32 AttrID, PTR Storage);
/*  105 */	U32						AMY_FUNC (*Attr_GetSuperTags)(struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, ...);
/*  106 */	U32 					AMY_FUNC (*Attr_GetSuperList)(struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, struct TagItem * taglist);
/*  107 */	U32 					AMY_FUNC (*Attr_GetParent)(struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, U32 AttrID, PTR Storage);
/*  108 */	U32 					AMY_FUNC (*Attr_GetParentTags)(struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, ...);
/*  109 */	U32 					AMY_FUNC (*Attr_GetParentList)(struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, struct TagItem * taglist);
/*  110 */	U32 					AMY_FUNC (*Attr_Set)(struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, U32 AttrID, U32 AttrValue);
/*  111 */	U32 					AMY_FUNC (*Attr_SetTags)(struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, ...);
/*  112 */	U32 					AMY_FUNC (*Attr_SetList)(struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, struct TagItem * taglist);
/*  113 */	U32 					AMY_FUNC (*Attr_SetSuper)(struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, U32 AttrID, U32 AttrValue);
/*  114 */	U32 					AMY_FUNC (*Attr_SetSuperTags)(struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, ...);
/*  115 */	U32 					AMY_FUNC (*Attr_SetSuperList)(struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, struct TagItem * taglist);
/*  116 */	U32 					AMY_FUNC (*Attr_SetParent)(struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, U32 AttrID, U32 AttrValue);
/*  117 */	U32 					AMY_FUNC (*Attr_SetParentTags)(struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, ...);
/*  118 */	U32 					AMY_FUNC (*Attr_SetParentList)(struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, struct TagItem * taglist);

// -- Class
/*    1 */	U32						AMY_FUNC (*Class_Add)( struct ReactivePrivIFace *Self, struct RA_PrivClass *cl, STR PubName );
/*    2 */	struct RA_PrivClass *	AMY_FUNC (*Class_CreateTags)( struct ReactivePrivIFace *Self, struct RA_PrivClass *SuperClass, STR SuperName, U32 ObjectDataSize, PTR Dispatcher, ... );
/*    3 */	struct RA_PrivClass *	AMY_FUNC (*Class_CreateList)( struct ReactivePrivIFace *Self, struct RA_PrivClass *SuperClass, STR SuperName, U32 ObjectDataSize, PTR Dispatcher, struct TagItem *taglist );
/*    4 */	U32						AMY_FUNC (*Class_Delete)( struct ReactivePrivIFace *Self, struct RA_PrivClass *cl );
/*    5 */	struct RA_PrivClass *	AMY_FUNC (*Class_FindTags)( struct ReactivePrivIFace *Self, STR name, ... );
/*    6 */	struct RA_PrivClass *	AMY_FUNC (*Class_FindList)( struct ReactivePrivIFace *Self, STR name, struct TagItem *taglist );
/*    7 */	U32						AMY_FUNC (*Class_Lock)( struct ReactivePrivIFace *Self, struct RA_PrivClass *cl );
/*    8 */	U32						AMY_FUNC (*Class_Unlock)( struct ReactivePrivIFace *Self, struct RA_PrivClass *cl );

// -- Object
/*   21 */	struct RA_PrivObject *	AMY_FUNC (*Object_CreateTags)( struct ReactivePrivIFace *Self, struct RA_PrivClass *Class, STR ClassName, ... );
/*   22 */	struct RA_PrivObject *	AMY_FUNC (*Object_CreateList)( struct ReactivePrivIFace *Self, struct RA_PrivClass *Class, STR ClassName, struct TagItem *taglist );
/*   23 */	U32						AMY_FUNC (*Object_Delete)( struct ReactivePrivIFace *Self, struct RA_PrivObject *obj );

// -- Method
/*   41 */	U32						AMY_FUNC (*Method_DoTags)( struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, ... );
/*   42 */	U32						AMY_FUNC (*Method_DoList)( struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, struct RA_Method *method );
/*   43 */	U32						AMY_FUNC (*Method_DoParentTags)( struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, ... );
/*   44 */	U32						AMY_FUNC (*Method_DoParentList)( struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, struct RA_Method *method );
/*   45 */	U32						AMY_FUNC (*Method_DoSuperNew)( struct ReactivePrivIFace *Self, struct RA_PrivClass *cl, struct RA_PrivObject *obj, ... );
/*   46*/	U32						AMY_FUNC (*Method_DoSuperTags)( struct ReactivePrivIFace *Self, struct RA_PrivClass *cl, struct RA_PrivObject *obj, ... );
/*   47 */	U32						AMY_FUNC (*Method_DoSuperList)( struct ReactivePrivIFace *Self, struct RA_PrivClass *cl, struct RA_PrivObject *obj, struct RA_Method *method );
/*   48 */	U32						AMY_FUNC (*Method_RunFunc)( struct ReactivePrivIFace *Self, struct RA_PrivClass *cl, struct RA_PrivObject *obj, struct RA_Method *method );

// -- Misc
/*   61 */	PTR						AMY_FUNC (*Misc_GetTagData)( struct ReactivePrivIFace *Self, struct TagItem *tag, U32 id, PTR defval );
/*   62 */	U32						AMY_FUNC (*Misc_GetTagValue)( struct ReactivePrivIFace *Self, struct TagItem *tag, U32 id, U32 defval );
/*   63 */	struct RA_PrivClass *	AMY_FUNC (*Misc_Plugin_Open)( struct ReactivePrivIFace *Self, STR name );
/*   64 */	S32						AMY_FUNC (*Misc_Plugin_Free)( struct ReactivePrivIFace *Self, struct RA_Plugin *rap );
/*   65 */	S32						AMY_FUNC (*Misc_Valid_Class_Name)( struct ReactivePrivIFace *Self, STR name );
/*   66 */	struct TagItem *		AMY_FUNC (*Misc_NextTag)( struct ReactivePrivIFace *Self, struct TagItem *tag );
/*   67 */	U32						AMY_FUNC (*Misc_XGet)( struct ReactivePrivIFace *Self, struct RA_PrivObject *obj, U32 AttrID );
/*   68 */	S32						AMY_FUNC (*Misc_Valid_Base_Name)( struct ReactivePrivIFace *Self, STR name );
/*   69 */  PTR						AMY_FUNC (*Misc_LoadFile_32)( struct ReactivePrivIFace *Self, STR FileName, U32 *FileSize );
/*   70 */  PTR						AMY_FUNC (*Misc_LoadFile_64)( struct ReactivePrivIFace *Self, STR FileName, U64 *FileSize );

};

// --

#endif
