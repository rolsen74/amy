
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
**
******************************************************************************
** This file is part of Amy C Lib
*/

/* --------------------------------------------------------------------------
** Always include Amy_Features.h FIRST — this defines feature macros like
** _FILE_OFFSET_BITS and _TIME_BITS before any typedefs depend on them.
** -------------------------------------------------------------------------- 
*/

#include <Amy_Features.h>
#include <Amy_Defines.h>

#ifndef AMYSYS_ENDIAN_H
#define AMYSYS_ENDIAN_H

#include <stdint.h>

AMY_EXTERN_C_BEGIN

/****************************************************************************/

#define BIG_ENDIAN		4321
#define LITTLE_ENDIAN	1234

// BSD
#define PDP_ENDIAN		3412  

/* -- */

#if defined(__BIG_ENDIAN__) || defined(_BIG_ENDIAN)

#define BYTE_ORDER		BIG_ENDIAN
#define htobe16(x)		BE_SWAP16(x)
#define htobe32(x)		BE_SWAP32(x)
#define htobe64(x)		BE_SWAP64(x)

#define be16toh(x)		BE_SWAP16(x)
#define be32toh(x)		BE_SWAP32(x)
#define be64toh(x)		BE_SWAP64(x)

#define htole16(x)		LE_SWAP16(x)
#define htole32(x)		LE_SWAP32(x)
#define htole64(x)		LE_SWAP64(x)

#define le16toh(x)		LE_SWAP16(x)
#define le32toh(x)		LE_SWAP32(x)
#define le64toh(x)		LE_SWAP64(x)

#elif defined(__LITTLE_ENDIAN__) || defined(_LITTLE_ENDIAN)

#define BYTE_ORDER		LITTLE_ENDIAN
#define htobe16(x)		LE_SWAP16(x)
#define htobe32(x)		LE_SWAP32(x)
#define htobe64(x)		LE_SWAP64(x)

#define be16toh(x)		LE_SWAP16(x)
#define be32toh(x)		LE_SWAP32(x)
#define be64toh(x)		LE_SWAP64(x)

#define htole16(x)		BE_SWAP16(x)
#define htole32(x)		BE_SWAP32(x)
#define htole64(x)		BE_SWAP64(x)

#define le16toh(x)		BE_SWAP16(x)
#define le32toh(x)		BE_SWAP32(x)
#define le64toh(x)		BE_SWAP64(x)

#else

#error "Cannot determine endianness"

#endif

/* -- */

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_ENDIAN_H */
