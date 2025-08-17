/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef _LIBC_STUB_H_
#define _LIBC_STUB_H_

#include <proto/AmyCLib.h>

/*
 * For fixed-argument functions
 */
#define LIBC_STUB(ret, name, iface_func, args_decl, ...) \
    ret name args_decl { return IAmyCLib->iface_func(__VA_ARGS__); }

/*
 * For variadic functions — supports optional __VA_ARGS__ using ##__VA_ARGS__
 */
#define LIBC_STUB_VARARGS(ret, name, iface_func, args_decl, call_fixed, ...) \
    ret name args_decl { return IAmyCLib->iface_func(call_fixed, ##__VA_ARGS__); }

#endif /* _LIBC_STUB_H_ */
