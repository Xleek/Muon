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

#ifndef INCLUDE_MUON_POOLALLOCATOR_HPP
#define INCLUDE_MUON_POOLALLOCATOR_HPP

#include "Muon/Memory/HeapAllocator.hpp"
#include "Muon/System/Assert.hpp"

/*
* @file PoolAllocator.hpp
*/
namespace m
{
	namespace memory
	{
		/*!
		* @brief
		*
		*/
		class MUON_API PoolAllocator
		{
			PoolAllocator& operator=(const PoolAllocator&);
		public:

			PoolAllocator(u32 elementSize, u32 blockSize);
			~PoolAllocator();
			PoolAllocator(const PoolAllocator&);

			void* alloc();
			void free(u32* ptr);

		private:
			u32 m_elementSize;
			u32 m_blockSize;
			void* m_free;
			void* m_data;
			void* m_end;
		};
	}
}

#endif
