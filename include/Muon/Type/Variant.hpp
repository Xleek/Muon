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

#ifndef _MUON_VARIANT_H_INCLUDED
#define _MUON_VARIANT_H_INCLUDED

#include <cstring>
#include "Muon/System/Assert.hpp"
#include "Muon/Memory/DequeAllocator.hpp"
#include "Muon/Meta/MetaDatabase.hpp"
#include "Muon/Meta/TypeInfo.hpp"

namespace muon
{
	class MUON_API Variant
	{
	public:
		template<typename T> explicit Variant(const T& value);
		explicit Variant(meta::MetaData* meta, void* data);
		Variant(const Variant& rhs);
		Variant();

		Variant& operator=(const Variant& rhs);
		Variant& set(const Variant& rhs);

		meta::MetaData* getMeta() const;

		template<typename T> Variant& set(const typename std::enable_if<meta::MemCopyable<T>::value, T>::type& rhs);
		template<typename T> Variant& set(const typename std::enable_if<meta::NonMemCopyable<T>::value, T>::type& rhs);

		template<typename T> Variant& operator=(const T& rhs);

		template<typename T> T& get();
		template<typename T> const T& get() const;

	protected:
		meta::MetaData* _meta;
		void* _data;
	};

	template <typename T>
	Variant::Variant(const T& value)
	{
		set<T>(value);
	}

	template <typename T>
	T& Variant::get()
	{
		return *reinterpret_cast<T*>(_data);
	}

	template <typename T>
	const T& Variant::get() const
	{
		return *reinterpret_cast<T*>(_data);
	}

	template<typename T>
	Variant& Variant::operator=(const T& rhs)
	{
		return set<T>(rhs);
	}

	template<typename T>
	Variant& Variant::set(const typename std::enable_if<meta::MemCopyable<T>::value, T>::type& rhs)
	{
		meta::MetaData* m = MUON_META(T);
		MUON_ASSERT(m, "Cannot copy an NULL MetaData!");
		if (m == NULL)
		{
			// Resetting our Variant
			::free(_data);
			_meta = MUON_META(void);
			return *this;
		}

		// Meta are different, erase the stored one and replace by the new
		if (_meta != MUON_META(T))
		{
			::free(_data);
			_meta = m;
			_data = ::malloc(_meta->size());
			::memcpy(_data, &rhs, _meta->size());
		}
		else
		{
			// They are the same, just copy the value
			::memcpy(_data, &rhs, _meta->size());
		}

		return *this;
	}

	template<typename T>
	Variant& Variant::set(const typename std::enable_if<meta::NonMemCopyable<T>::value, T>::type& rhs)
	{
		meta::MetaData* m = MUON_META(T);
		MUON_ASSERT(m, "Cannot copy an NULL MetaData!");
		if (m == NULL)
		{
			// Resetting our Variant
			::free(_data);
			_meta = MUON_META(void);
			return *this;
		}

		// As we are non copyable, erase and re-allocate in any cases
		if (_data)
		{
			memory::DequeAllocator::destroy<T>((T*)_data);
			memory::DequeAllocator::deallocate<T>(1, (T*)_data);
		}
		_meta = m;
		// Allocate memory
		_data = memory::DequeAllocator::allocate<T>(1);
		new (_data)T(rhs);

		return *this;
	}
}

MUON_TRAITS(muon::Variant)

#endif