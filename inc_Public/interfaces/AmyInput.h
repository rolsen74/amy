
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_INTERFACES_AMYINPUT_H
#define AMYLIB_INTERFACES_AMYINPUT_H

// --

#include "Amy_Defines.h"

// --

struct AmyInputIFace
{
	struct InterfaceData Data;
	U32							AMY_FUNC (*Obtain)(struct AmyInputIFace *Self);
	U32							AMY_FUNC (*Release)(struct AmyInputIFace *Self);
	void						AMY_FUNC (*Expunge)(struct AmyInputIFace *Self);
	struct Interface *			AMY_FUNC (*Clone)(struct AmyInputIFace *Self);
	U32							AMY_FUNC (*GetError)(struct AmyInputIFace *Self, PTR ctx);
	STR							AMY_FUNC (*GetErrorString)(struct AmyInputIFace *Self, U32 error_code);
	PTR							AMY_FUNC (*CreateContext)(struct AmyInputIFace *Self, U32 apiver, struct TagItem *tags);
	void						AMY_FUNC (*DeleteContext)(struct AmyInputIFace *Self, PTR ctx);
	U32							AMY_FUNC (*EnumDevices)(struct AmyInputIFace *Self, PTR ctx, PTR enumfunc, PTR user_data);
	U32							AMY_FUNC (*Query)(struct AmyInputIFace *Self, PTR ctx, DeviceID device_id, U32 qParameter, U32 qArg, PTR result, U32 result_length);
	DeviceHandle *				AMY_FUNC (*ObtainDevice)(struct AmyInputIFace *Self, PTR ctx, DeviceID device_id);
	void						AMY_FUNC (*ReleaseDevice)(struct AmyInputIFace *Self, PTR ctx, DeviceHandle *handle);
	U32							AMY_FUNC (*SetDeviceParameter)(struct AmyInputIFace *Self, PTR ctx, DeviceHandle *handle, U32 dParameter, U32 dArg);
	InputEvent *				AMY_FUNC (*GetEvent)(struct AmyInputIFace *Self, PTR ctx);
	void 						AMY_FUNC (*FreeEvent)(struct AmyInputIFace *Self, PTR ctx, InputEvent *event);
	U32							AMY_FUNC (*ReadDevice)(struct AmyInputIFace *Self, PTR ctx, DeviceHandle *handle, PTR *data);
	U32							AMY_FUNC (*Set)(struct AmyInputIFace *Self, PTR ctx, struct TagItem *tags);
	struct _RequesterResult *	AMY_FUNC (*RequestDevice)(struct AmyInputIFace *Self, PTR ctx, struct TagItem *tags);
	void						AMY_FUNC (*FreeRequest)(struct AmyInputIFace *Self, PTR ctx, struct _RequesterResult *result);
};

// --

#endif
