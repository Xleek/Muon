/*************************************************************************
* Muon
* C++ Core Library
*------------------------------------------------------------------------
* Copyright (c) 2015 Louis Schnellbach
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would
*    be appreciated but is not required.
*
* 2. Altered source versions must be plainly marked as such, and must not
*    be misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source
*    distribution.
*
*************************************************************************/

#ifndef _MUON_TYPEDEF_H_INCLUDED
#define _MUON_TYPEDEF_H_INCLUDED

#include "Muon/Core/Define.hpp"

namespace muon
{
	//! 1 Byte unsigned integer
	typedef unsigned char		u8;
	//! 2 Bytes unsigned integer
	typedef unsigned short		u16;
	//! 4 Bytes unsigned integer
	typedef unsigned int		u32;
	//! 8 Bytes unsigned integer
	typedef unsigned long long	u64;

	//! 1 Byte integer
	typedef char		i8;
	//! 2 Bytes integer
	typedef short		i16;
	//! 4 Bytes integer
	typedef int			i32;
	//! 8 Bytes integer
	typedef long long	i64;

	//! float
	typedef float	f32;
	//! double
	typedef double	f64;

	//! void*
	typedef void* RawPointer;
}

#endif
