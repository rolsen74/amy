
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen <renewolsen@gmail.com>
*/

#ifndef __INTERFACES_AMYINPUT_H__
#define __INTERFACES_AMYINPUT_H__

// --

#ifndef __AMY_STANDARD_H__
#include "Amy_Standard.h"
#endif

// --

struct AmyInputIFace
{
	struct InterfaceData Data;
	U32								APICALL (*Obtain)(struct AmyInputIFace *Self);
	U32								APICALL (*Release)(struct AmyInputIFace *Self);
	void							APICALL (*Expunge)(struct AmyInputIFace *Self);
	struct Interface *				APICALL (*Clone)(struct AmyInputIFace *Self);
	U32								APICALL (*GetError)(struct AmyInputIFace *Self, PTR ctx);
	STR								APICALL (*GetErrorString)(struct AmyInputIFace *Self, U32 error_code);
	PTR								APICALL (*CreateContext)(struct AmyInputIFace *Self, U32 apiver, struct TagItem *tags);
	void							APICALL (*DeleteContext)(struct AmyInputIFace *Self, PTR ctx);
	U32							APICALL (*EnumDevices)(struct AmyInputIFace *Self, PTR ctx, PTR enumfunc, PTR user_data);
	U32							APICALL (*Query)(struct AmyInputIFace *Self, PTR ctx, DeviceID device_id, U32 qParameter, U32 qArg, PTR result, U32 result_length);
	DeviceHandle *					APICALL (*ObtainDevice)(struct AmyInputIFace *Self, PTR ctx, DeviceID device_id);
	void							APICALL (*ReleaseDevice)(struct AmyInputIFace *Self, PTR ctx, DeviceHandle *handle);
	U32							APICALL (*SetDeviceParameter)(struct AmyInputIFace *Self, PTR ctx, DeviceHandle *handle, U32 dParameter, U32 dArg);
	InputEvent *					APICALL (*GetEvent)(struct AmyInputIFace *Self, PTR ctx);
	void 							APICALL (*FreeEvent)(struct AmyInputIFace *Self, PTR ctx, InputEvent *event);
	U32							APICALL (*ReadDevice)(struct AmyInputIFace *Self, PTR ctx, DeviceHandle *handle, PTR *data);
	U32							APICALL (*Set)(struct AmyInputIFace *Self, PTR ctx, struct TagItem *tags);
	struct _RequesterResult *		APICALL (*RequestDevice)(struct AmyInputIFace *Self, PTR ctx, struct TagItem *tags);
	void							APICALL (*FreeRequest)(struct AmyInputIFace *Self, PTR ctx, struct _RequesterResult *result);
};

// --

#endif
