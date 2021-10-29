/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cstddef>	//std::size_t, std::ptrdiff_t
#include <new>		//operator new, align_val_t

#include "Refureku/Config.h"

namespace rfk
{
	template <typename T>
	class Allocator
	{
		public:
			using value_type		= T;
			using pointer			= T*;
			using const_pointer		= T const*;
			using reference			= T&;
			using const_reference	= T const&;

			/**
			*	@brief Allocate count * sizeof(T) bytes.
			* 
			*	@param count Number of elements T needed to fit in the allocated memory.
			* 
			*	@return A pointer to the allocated memory.
			*/
			RFK_NODISCARD constexpr T*	allocate(std::size_t count);

			/**
			*	@brief Deallocate count * sizeof(T) bytes at the specified memory.
			* 
			*	@param allocatedMemory	Pointer to the allocated memory to deallocate.
			*	@param count			Number of T elements to deallocate.
			*/
			constexpr void				deallocate(T*			allocatedMemory,
												   std::size_t	count);
	};

	#include "Refureku/Containers/Allocator.inl"
}