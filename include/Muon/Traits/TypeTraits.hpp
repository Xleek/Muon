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

#ifndef INCLUDE_MUON_TYPETRAITS_HPP
#define INCLUDE_MUON_TYPETRAITS_HPP

#include <type_traits>
#include "Muon/Traits/TypeInfo.hpp"
#include "Muon/Traits/RawType.hpp"
#include "Muon/Memory/Allocator.hpp"

#if defined(MUON_PLATFORM_WINDOWS) || defined(MUON_PLATFORM_WEB)
namespace priv
{
	MUON_INLINE m::u64 _traits_hash(const char* m_str)
	{
		// www.cse.yorku.ca/~oz/hash.html
		m::u64 v = 5381;
		if (m_str)
		{
			char* str = (char*)m_str;
			int c;
			while ((c = *str++) != 0)
			{
				v = ((v << 5) + v) + c;
			}
		}
		return v;
	}
#	define _MUON_TRAITS_ID_ATTRIB(Type) ::priv::_traits_hash(MUON_STR(Type))
}
#else
namespace priv
{
	MUON_CONSTEXPR m::u64 _traits_const_hash(const char* str)
	{
		return *str ? static_cast<m::u64>(*str) + 33 * _traits_const_hash(str + 1) : 5381;
	}

	MUON_CONSTEXPR m::u64 operator "" _traits_hash(const char* str, m::u64)
	{
		return _traits_const_hash(str);
	}
#	define _MUON_TRAITS_ID_ATTRIB(Type) #Type ## _traits_hash
}
#endif

#define _MUON_TRAITS_DECL_NAME(Type) static MUON_INLINE MUON_CONSTEXPR const char* name() { return MUON_STR(Type); }
#define _MUON_TRAITS_DECL_ID(Type) static MUON_INLINE MUON_CONSTEXPR ::m::u64 id() {using namespace ::priv; return ::m::traits::TYPE_ID_BASE_MASK & _MUON_TRAITS_ID_ATTRIB(Type); }
#define _MUON_TRAITS_DECL_SIZE(Type) static MUON_INLINE MUON_CONSTEXPR ::m::u32 size() { return sizeof(Type); }
#define _MUON_TRAITS_DECL_CREATE(Type) static MUON_INLINE Type* create() { return MUON_NEW(Type); }
#define _MUON_TRAITS_DECL_COPY(Type) static MUON_INLINE void copy(Type* ptr, Type* val) { *ptr = *val; }
#define _MUON_TRAITS_DECL_DESTROY(Type) static MUON_INLINE void destroy(Type* ptr) { MUON_DELETE(ptr); }

#define _MUON_TRAITS_FUNCTIONS_DECL(Type) _MUON_TRAITS_DECL_NAME(Type) _MUON_TRAITS_DECL_ID(Type) _MUON_TRAITS_DECL_SIZE(Type) _MUON_TRAITS_DECL_CREATE(Type) _MUON_TRAITS_DECL_COPY(Type) _MUON_TRAITS_DECL_DESTROY(Type);
#define _MUON_TRAITS_STRUCT(Type) template<> struct TypeTraits<Type> { _MUON_TRAITS_FUNCTIONS_DECL(Type) };
//! Register a Type Traits
#define MUON_TRAITS_DECL(Type) namespace m { namespace traits { _MUON_TRAITS_STRUCT(Type) } }
//! Access the TypeTraits struct
#define MUON_TRAITS(Type) ::m::traits::TypeTraits<Type>
//! Access the Type name from its TypeTraits (it must have been declared)
#define MUON_TRAITS_NAME(Type) ::m::traits::TypeTraits<Type>::name()
//! Access the Type ID from its TypeTraits (it must have been declared)
#define MUON_TRAITS_ID(Type) ::m::traits::TypeTraits<Type>::id()
//! Access the Type size from its TypeTraits (it must have been declared)
#define MUON_TRAITS_SIZE(Type) ::m::traits::TypeTraits<Type>::size()

namespace m
{
	namespace traits
	{
		enum TypeIDMask : u64
		{
			TYPE_ID_INVALID = 0x0FFFFFFFFFFFFFFF,
			TYPE_ID_BASE_MASK = 0x0FFFFFFFFFFFFFFF,
			TYPE_ID_CUSTOM_MASK = 0xF000000000000000,
		};

		static const char* TYPE_NAME_UNREGISTERED = "#Unregistered#";

		// Let the compiler not compile unregistered TypeTraits
		template<typename T> struct TypeTraits
		{
		};

		template<> struct TypeTraits<void>
		{
			static MUON_INLINE MUON_CONSTEXPR const char* name()
			{
				return "void";
			}
			static MUON_INLINE MUON_CONSTEXPR::m::u64 id()
			{
				return TYPE_ID_INVALID;
			}
			static MUON_INLINE MUON_CONSTEXPR::m::u32 size()
			{
				return 0;
			}
			static MUON_INLINE void* create()
			{
				return NULL;
			}
			static MUON_INLINE void copy(void*, void*)
			{
			}
			static MUON_INLINE void destroy(void*)
			{
			}
		};

		template<> struct TypeTraits<bool>
		{
			_MUON_TRAITS_FUNCTIONS_DECL(bool);
		};

		template<> struct TypeTraits<const char*>
		{
			_MUON_TRAITS_FUNCTIONS_DECL(const char*);
		};

		template<> struct TypeTraits<char*>
		{
			_MUON_TRAITS_FUNCTIONS_DECL(char*);
		};

		// Function which return a class member offset (works with virtual and abstract classes)
		template<typename Class, typename MemberType>
		MUON_CONSTEXPR u64 offset(MemberType Class::*member)
		{
			return (u64)(&(((Class*)0)->*member));
		}
	}
}

MUON_TRAITS_DECL(m::u8);
MUON_TRAITS_DECL(m::u16);
MUON_TRAITS_DECL(m::u32);
MUON_TRAITS_DECL(m::u64);

MUON_TRAITS_DECL(m::i8);
MUON_TRAITS_DECL(m::i16);
MUON_TRAITS_DECL(m::i32);
MUON_TRAITS_DECL(m::i64);

MUON_TRAITS_DECL(m::f32);
MUON_TRAITS_DECL(m::f64);

#endif
