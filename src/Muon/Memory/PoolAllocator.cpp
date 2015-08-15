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

#include <fstream>
#include <map>
#include "Muon/Memory/PoolAllocator.hpp"
#include "Muon/System/Log.hpp"
#include "Muon/Type/String.hpp"

namespace
{
	using namespace muon;
	u32 _allocated = 0;
	u32 _allocatedTotal = 0;
	u32 _allocatedSize = 0;
}

namespace muon
{
	namespace memory
	{
		namespace pool
		{
			void* allocate(const char* file, const char* func, u32 line, u32 size, u32 count)
			{
				++_allocated;
				++_allocatedTotal;
				_allocatedSize += size*count;
				return malloc(size * count);
			}

			void deallocate(const char* file, const char* func, u32 line, u32 size, u32 count, void* ptr)
			{
				MUON_ASSERT(_allocated > 0, "Deallocating more memory than allocated!");
				--_allocated;
				free(ptr);
			}

			void info()
			{
				//Log(LOG_INFO, "[PoolAllocator] Alloc. Num: %d | Size Alloc.: %d", _allocatedTotal, _allocatedSize);
			}
		}
	}
}
