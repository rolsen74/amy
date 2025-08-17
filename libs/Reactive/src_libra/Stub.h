/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef _LIBRA_STUB_H_
#define _LIBRA_STUB_H_

#include <proto/Reactive.h>

/*
 * For fixed-argument functions
 */
#define LIBRA_STUB(ret, name, iface_func, args_decl, ...) \
	ret name args_decl { return IReactive->iface_func(__VA_ARGS__); }

/*
 * For variadic functions — supports optional __VA_ARGS__ using ##__VA_ARGS__
 */
#define LIBRA_STUB_VARARGS(ret, name, iface_func, args_decl, call_fixed, ...) \
	ret name args_decl { return IReactive->iface_func(call_fixed, ##__VA_ARGS__); }

#endif /* _LIBRA_STUB_H_ */
