/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename T>
[[nodiscard]] constexpr T* Allocator<T>::allocate(std::size_t count)
{
	return reinterpret_cast<T*>(::operator new(count * sizeof(T), std::align_val_t{alignof(T)}));
}

template <typename T>
constexpr void Allocator<T>::deallocate(T* allocatedMemory, std::size_t count)
{
	::operator delete(allocatedMemory, count * sizeof(T), std::align_val_t{alignof(T)});
}