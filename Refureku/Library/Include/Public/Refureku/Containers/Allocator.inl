/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <typename T>
constexpr T* Allocator<T>::allocate(std::size_t count)
{
	if constexpr (alignof(T) > __STDCPP_DEFAULT_NEW_ALIGNMENT__)
	{
		return static_cast<T*>(::operator new(count * sizeof(T), std::align_val_t{alignof(T)}));
	}
	else
	{
		return static_cast<T*>(::operator new(count * sizeof(T)));
	}
}

template <typename T>
constexpr void Allocator<T>::deallocate(T* allocatedMemory, [[maybe_unused]] std::size_t count)
{
	//For some reasons clang can't find the delete overload with count * sizeof(T) as second parameter

	if constexpr (alignof(T) > __STDCPP_DEFAULT_NEW_ALIGNMENT__)
	{
		::operator delete(allocatedMemory, std::align_val_t{alignof(T)});
	}
	else
	{
		::operator delete(allocatedMemory);
	}
}