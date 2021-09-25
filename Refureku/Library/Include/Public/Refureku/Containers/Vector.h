/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <cassert>
#include <memory>		//std::allocator_traits
#include <type_traits>	//std::is_nothrow_destructible_v

#include "Refureku/Containers/Allocator.h"

namespace rfk
{
	template <typename T, typename Allocator = rfk::Allocator<T>>
	class Vector
	{
		private:
			using AllocTraits = std::allocator_traits<Allocator>;

			/** Pointer to the allocated space. */
			T*			_data;
			//TODO: Small vector optimization

			/** Number of currently constructed T objects in vector. */
			std::size_t	_size;

			/** Current allocated capacity. */
			std::size_t	_capacity;

			/** Allocator used by this Vector. */
			Allocator	_allocator;

			/**
			*	TODO
			*/
			void constructElements(T*			from,
								   std::size_t	count)	noexcept(std::is_nothrow_default_constructible_v<T>);

			/**
			*	TODO
			*/
			void copyElements(T const*	  from,
							  T*		  to,
							  std::size_t count)		noexcept(std::is_nothrow_copy_constructible_v<T>);
			
			/**
			*	TODO
			*/
			void moveElements(T const*	  from,
							  T*		  to,
							  std::size_t count)		noexcept(std::is_nothrow_move_constructible_v<T>);

			/**
			*	TODO
			*/
			void destroyElements(T*			 from,
								 std::size_t count)		noexcept(std::is_nothrow_destructible_v<T>);

			/**
			*	TODO
			*/
			void checkedDelete()						noexcept(std::is_nothrow_destructible_v<T>);

		public:
			Vector()				noexcept;
			Vector(Vector const&)	noexcept(std::is_nothrow_destructible_v<T>);
			Vector(Vector&&)		noexcept;
			~Vector()				noexcept(std::is_nothrow_destructible_v<T>);

			/**
			*	@brief Get a reference to the first element of the vector.
			* 
			*	@return A reference to the first element of the vector.
			*/
			T&			front()			noexcept;

			/**
			*	@brief Get a const-reference to the first element of the vector.
			* 
			*	@return A const-reference to the first element of the vector.
			*/
			T const&	front()	const	noexcept;

			T&			back()			noexcept;
			T const&	back()	const	noexcept;

			T*			data()			noexcept;
			T const*	data()	const	noexcept;

			void		reserve(std::size_t capacity);

			void		resize(std::size_t size);

			std::size_t	size()		const	noexcept;
			std::size_t capacity()	const	noexcept;
			bool		empty()		const	noexcept;

			T&			operator[](std::size_t index)		noexcept;
			T const&	operator[](std::size_t index) const	noexcept;
	};

	#include "Refureku/Containers/Vector.inl"
}