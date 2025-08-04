#ifndef _LIBC_STUB_H_
#define _LIBC_STUB_H_

#include <proto/AmyCLib.h>

#define LIBC_STUB(ret, name, iface_func, args_decl, ...) \
	ret name args_decl { return IAmyCLib->iface_func(__VA_ARGS__); }

#endif /* _LIBC_STUB_H_ */