
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_INTERFACES_REACTIVE_H
#define AMYLIB_INTERFACES_REACTIVE_H

// --

#include "Amy_Defines.h"

// --

struct ReactiveIFace
{
	struct InterfaceData Data;
/* 0000 */	U32					AMY_FUNC (*Obtain)(struct ReactiveIFace *Self);
/* 0001 */	U32					AMY_FUNC (*Release)(struct ReactiveIFace *Self);
/* 0002 */	void				AMY_FUNC (*Expunge)(struct ReactiveIFace *Self);
/* 0003 */	struct Interface *	AMY_FUNC (*Clone)(struct ReactiveIFace *Self);

// -- Arguments
/*   81 */	PTR					AMY_FUNC (*RA_Arguments_ParseList)( struct ReactiveIFace *Self, struct RAArguments *Args, struct TagItem *taglist );
/*   82 */	PTR					AMY_FUNC (*RA_Arguments_ParseTags)( struct ReactiveIFace *Self, struct RAArguments *Args, ... );
/*   83 */	U32					AMY_FUNC (*RA_Arguments_Free)( struct ReactiveIFace *Self, PTR Args );

// -- Attributes
/*  101 */	U32					AMY_FUNC (*RA_Attr_Get)(struct ReactiveIFace *Self, struct RA_Object *obj, U32 AttrID, PTR Storage);
/*  102 */	U32					AMY_FUNC (*RA_Attr_GetTags)(struct ReactiveIFace *Self, struct RA_Object *obj, ...);
/*  103 */	U32					AMY_FUNC (*RA_Attr_GetList)(struct ReactiveIFace *Self, struct RA_Object *obj, struct TagItem * taglist);
/*  104 */	U32					AMY_FUNC (*RA_Attr_GetSuper)(struct ReactiveIFace *Self, struct RA_Object *obj, U32 AttrID, PTR Storage);
/*  105 */	U32					AMY_FUNC (*RA_Attr_GetSuperTags)(struct ReactiveIFace *Self, struct RA_Object *obj, ...);
/*  106 */	U32 				AMY_FUNC (*RA_Attr_GetSuperList)(struct ReactiveIFace *Self, struct RA_Object *obj, struct TagItem * taglist);
/*  107 */	U32 				AMY_FUNC (*RA_Attr_GetParent)(struct ReactiveIFace *Self, struct RA_Object *obj, U32 AttrID, PTR Storage);
/*  108 */	U32 				AMY_FUNC (*RA_Attr_GetParentTags)(struct ReactiveIFace *Self, struct RA_Object *obj, ...);
/*  109 */	U32 				AMY_FUNC (*RA_Attr_GetParentList)(struct ReactiveIFace *Self, struct RA_Object *obj, struct TagItem * taglist);
/*  110 */	U32 				AMY_FUNC (*RA_Attr_Set)(struct ReactiveIFace *Self, struct RA_Object *obj, U32 AttrID, U32 AttrValue);
/*  111 */	U32 				AMY_FUNC (*RA_Attr_SetTags)(struct ReactiveIFace *Self, struct RA_Object *obj, ...);
/*  112 */	U32 				AMY_FUNC (*RA_Attr_SetList)(struct ReactiveIFace *Self, struct RA_Object *obj, struct TagItem * taglist);
/*  113 */	U32 				AMY_FUNC (*RA_Attr_SetSuper)(struct ReactiveIFace *Self, struct RA_Object *obj, U32 AttrID, U32 AttrValue);
/*  114 */	U32 				AMY_FUNC (*RA_Attr_SetSuperTags)(struct ReactiveIFace *Self, struct RA_Object *obj, ...);
/*  115 */	U32 				AMY_FUNC (*RA_Attr_SetSuperList)(struct ReactiveIFace *Self, struct RA_Object *obj, struct TagItem * taglist);
/*  116 */	U32 				AMY_FUNC (*RA_Attr_SetParent)(struct ReactiveIFace *Self, struct RA_Object *obj, U32 AttrID, U32 AttrValue);
/*  117 */	U32 				AMY_FUNC (*RA_Attr_SetParentTags)(struct ReactiveIFace *Self, struct RA_Object *obj, ...);
/*  118 */	U32 				AMY_FUNC (*RA_Attr_SetParentList)(struct ReactiveIFace *Self, struct RA_Object *obj, struct TagItem * taglist);

// -- Class
/*    1 */	U32					AMY_FUNC (*RA_Class_Add)( struct ReactiveIFace *Self, struct RA_Class *cl, STR PubName );
/*    2 */	struct RA_Class *	AMY_FUNC (*RA_Class_CreateTags)( struct ReactiveIFace *Self, struct RA_Class *SuperClass, STR SuperName, U32 ObjectDataSize, PTR Dispatcher, ... );
/*    3 */	struct RA_Class *	AMY_FUNC (*RA_Class_CreateList)( struct ReactiveIFace *Self, struct RA_Class *SuperClass, STR SuperName, U32 ObjectDataSize, PTR Dispatcher, struct TagItem *taglist );
/*    4 */	U32					AMY_FUNC (*RA_Class_Delete)( struct ReactiveIFace *Self, struct RA_Class *cl );
/*    5 */	struct RA_Class *	AMY_FUNC (*RA_Class_FindTags)( struct ReactiveIFace *Self, STR name, ... );
/*    6 */	struct RA_Class *	AMY_FUNC (*RA_Class_FindList)( struct ReactiveIFace *Self, STR name, struct TagItem *taglist );
/*    7 */	U32					AMY_FUNC (*RA_Class_Lock)( struct ReactiveIFace *Self, struct RA_Class *cl );
/*    8 */	U32					AMY_FUNC (*RA_Class_Unlock)( struct ReactiveIFace *Self, struct RA_Class *cl );

// -- Object
/*   21 */	struct RA_Object *	AMY_FUNC (*RA_Object_CreateTags)( struct ReactiveIFace *Self, struct RA_Class *Class, STR ClassName, ... );
/*   22 */	struct RA_Object *	AMY_FUNC (*RA_Object_CreateList)( struct ReactiveIFace *Self, struct RA_Class *Class, STR ClassName, struct TagItem *taglist );
/*   23 */	U32					AMY_FUNC (*RA_Object_Delete)( struct ReactiveIFace *Self, struct RA_Object *obj );

// -- Method
/*   41 */	U32					AMY_FUNC (*RA_Method_DoTags)( struct ReactiveIFace *Self, struct RA_Object *obj, ... );
/*   42 */	U32					AMY_FUNC (*RA_Method_DoList)( struct ReactiveIFace *Self, struct RA_Object *obj, struct RA_Method *method );
/*   43 */	U32					AMY_FUNC (*RA_Method_DoParentTags)( struct ReactiveIFace *Self, struct RA_Object *obj, ... );
/*   44 */	U32					AMY_FUNC (*RA_Method_DoParentList)( struct ReactiveIFace *Self, struct RA_Object *obj, struct RA_Method *method );
/*   45 */	U32					AMY_FUNC (*RA_Method_DoSuperNew)( struct ReactiveIFace *Self, struct RA_Class *cl, struct RA_Object *obj, ... );
/*   46 */	U32					AMY_FUNC (*RA_Method_DoSuperTags)( struct ReactiveIFace *Self, struct RA_Class *cl, struct RA_Object *obj, ... );
/*   47 */	U32					AMY_FUNC (*RA_Method_DoSuperList)( struct ReactiveIFace *Self, struct RA_Class *cl, struct RA_Object *obj, struct RA_Method *method );
/*   48 */	U32					AMY_FUNC (*RA_Method_RunFunc)( struct ReactiveIFace *Self, struct RA_Class *cl, struct RA_Object *obj, struct RA_Method *method );

// -- Misc
/*   61 */	PTR					AMY_FUNC (*RA_Misc_GetTagData)( struct ReactiveIFace *Self, struct TagItem *tag, U32 id, PTR defval );
/*   62 */	U32					AMY_FUNC (*RA_Misc_GetTagValue)( struct ReactiveIFace *Self, struct TagItem *tag, U32 id, U32 defval );
/*   63 */	struct RA_Class *	AMY_FUNC (*RA_Misc_Plugin_Open)( struct ReactiveIFace *Self, STR name );
/*   64 */	S32					AMY_FUNC (*RA_Misc_Plugin_Free)( struct ReactiveIFace *Self, struct RA_Plugin *rap );
/*   65 */	S32					AMY_FUNC (*RA_Misc_Valid_Class_Name)( struct ReactiveIFace *Self, STR name );
/*   66 */	struct TagItem *	AMY_FUNC (*RA_Misc_NextTag)( struct ReactiveIFace *Self, struct TagItem *tag );
/*   67 */	U32					AMY_FUNC (*RA_Misc_XGet)( struct ReactiveIFace *Self, struct RA_Object *obj, U32 AttrID );
/*   68 */	S32					AMY_FUNC (*RA_Misc_Valid_Base_Name)( struct ReactiveIFace *Self, STR name );
/*   69 */  PTR					AMY_FUNC (*RA_Misc_LoadFile_32)( struct ReactiveIFace *Self, STR FileName, U32 *FileSize );
/*   70 */  PTR					AMY_FUNC (*RA_Misc_LoadFile_64)( struct ReactiveIFace *Self, STR FileName, U64 *FileSize );

};

// --

#endif
