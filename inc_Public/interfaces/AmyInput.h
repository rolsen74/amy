
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
	U32								AMYFUNC (*Obtain)(struct AmyInputIFace *Self);
	U32								AMYFUNC (*Release)(struct AmyInputIFace *Self);
	void							AMYFUNC (*Expunge)(struct AmyInputIFace *Self);
	struct Interface *				AMYFUNC (*Clone)(struct AmyInputIFace *Self);
	U32								AMYFUNC (*GetError)(struct AmyInputIFace *Self, PTR ctx);
	STR								AMYFUNC (*GetErrorString)(struct AmyInputIFace *Self, U32 error_code);
	PTR								AMYFUNC (*CreateContext)(struct AmyInputIFace *Self, U32 apiver, struct TagItem *tags);
	void							AMYFUNC (*DeleteContext)(struct AmyInputIFace *Self, PTR ctx);
	U32								AMYFUNC (*EnumDevices)(struct AmyInputIFace *Self, PTR ctx, PTR enumfunc, PTR user_data);
	U32								AMYFUNC (*Query)(struct AmyInputIFace *Self, PTR ctx, DeviceID device_id, U32 qParameter, U32 qArg, PTR result, U32 result_length);
	DeviceHandle *					AMYFUNC (*ObtainDevice)(struct AmyInputIFace *Self, PTR ctx, DeviceID device_id);
	void							AMYFUNC (*ReleaseDevice)(struct AmyInputIFace *Self, PTR ctx, DeviceHandle *handle);
	U32								AMYFUNC (*SetDeviceParameter)(struct AmyInputIFace *Self, PTR ctx, DeviceHandle *handle, U32 dParameter, U32 dArg);
	InputEvent *					AMYFUNC (*GetEvent)(struct AmyInputIFace *Self, PTR ctx);
	void 							AMYFUNC (*FreeEvent)(struct AmyInputIFace *Self, PTR ctx, InputEvent *event);
	U32								AMYFUNC (*ReadDevice)(struct AmyInputIFace *Self, PTR ctx, DeviceHandle *handle, PTR *data);
	U32								AMYFUNC (*Set)(struct AmyInputIFace *Self, PTR ctx, struct TagItem *tags);
	struct _RequesterResult *		AMYFUNC (*RequestDevice)(struct AmyInputIFace *Self, PTR ctx, struct TagItem *tags);
	void							AMYFUNC (*FreeRequest)(struct AmyInputIFace *Self, PTR ctx, struct _RequesterResult *result);
};

// --

#endif
