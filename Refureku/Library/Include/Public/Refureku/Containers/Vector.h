/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cassert>
#include <memory>		//std::allocator_traits

#include "Refureku/Containers/Allocator.h"

namespace rfk
{
	template <typename T, typename Allocator = rfk::Allocator<T>>
	class Vector
	{
		//Friendship for move constructor from Vector holding another type of data
		template <typename U, typename UAllocator>
		friend class Vector;

		private:
			using AllocTraits = std::allocator_traits<Allocator>;

			/** Factor used to compute new memory size when a reallocation occurs. */
			static constexpr float const _growthFactor = 2.0f;

			/** Pointer to the allocated space. */
			T*			_data;

			/** Number of currently constructed T objects in vector. */
			std::size_t	_size;

			/** Current allocated capacity. */
			std::size_t	_capacity;

			/** Allocator used by this Vector. */
			Allocator	_allocator;

			/**
			*	@brief Construct (placement new) count elements starting at the specified address.
			* 
			*	@param from		Address of the first element to construct.
			*	@param count	Number of elements to construct.
			*/
			void		constructElements(T*			from,
										  std::size_t	count);

			/**
			*	@brief Copy count elements from from into to.
			* 
			*	@param from		Address of the source first element to copy.
			*	@param to		Address of the target first element receiving the copy.
			*	@param count	Number of elements to copy.
			*/
			void		copyElements(T const*	 from,
									 T*			 to,
									 std::size_t count);

			/**
			*	@brief	Copy count elements from from into to.
			*			Copy elements in reverse order, starting from the last element of from and finishing with the first element of from.
			* 
			*	@param from		Address of the source first element to copy.
			*	@param to		Address of the target first element receiving the copy.
			*	@param count	Number of elements to copy.
			*/
			void		copyElementsReverse(T const*	from,
											T*			to,
											std::size_t count);
			
			/**
			*	@brief Move count elements from from into to.
			* 
			*	@param from		Address of the source first element to move.
			*	@param to		Address of the target first element receiving the move.
			*	@param count	Number of elements to move.
			*/
			void		moveElements(T*			 from,
									 T*			 to,
									 std::size_t count);

			/**
			*	@brief	Move count elements from from into to.
			*			Move elements in reverse order, starting from the last element of from and finishing with the first element of from.
			* 
			*	@param from		Address of the source first element to move.
			*	@param to		Address of the target first element receiving the move.
			*	@param count	Number of elements to move.
			*/
			void		moveElementsReverse(T*			from,
											T*			to,
											std::size_t count);

			/**
			*	@brief Destroy manually count elements from from.
			* 
			*	@param from		Address of the first element to destroy.
			*	@param count	Number of elements to destroy.
			*/
			void		destroyElements(T*			from,
										std::size_t count);

			/**
			*	@brief Completely delete the allocated memory if it is non-nullptr.
			*/
			void		checkedDelete();

			/**
			*	@brief	Reallocate the underlying memory if the container capacity is < the provided capacity.
			*			The capacity is computed using Vector::computeNewCapacity.
			* 
			*	@param minCapacity The minimum capacity that should be allocated.
			*/
			void		reallocateIfNecessary(std::size_t minCapacity);

			/**
			*	@brief	Open free space for future elements at the provided index.
			*			Elements before the provided don't move, and elements after index are moved at index + count.
			*			If there's not enough capacity, the underlying memory is reallocated.
			* 
			*	@param index Starting index for free space.
			*	@param count Number of elements that should be able to fit from index.
			*/
			void		makeFreeSpaceForXElements(std::size_t index,
												  std::size_t count);

			/**
			*	@brief	Compute the new capacity of the vector using the _growthFactor.
			* 
			*	@param minCapacity The minimum capacity that should be allocated.
			*/
			std::size_t	computeNewCapacity(std::size_t minCapacity)	const noexcept;

		public:
			using value_type = T;
			using allocator_type = Allocator;
			using reference = value_type&;
			using const_reference = value_type const&;
			
			Vector(std::size_t initialCapacity = 0u)	noexcept;

			/** Retrieve data from another type U. NOT SAFE UNLESS YOU EXACTLY KNOW WHAT YOU DO. */
			template <typename U, typename UAlloc>
			Vector(Vector<U, UAlloc>&&)					noexcept;

			Vector(Vector const&);
			Vector(Vector&&)							noexcept;
			~Vector();

			/**
			*	@brief	Get a reference to the first element of the vector.
			*			The behaviour is undefined if the vector is empty.
			* 
			*	@return A reference to the first element of the vector.
			*/
			T&			front()			noexcept;
			T const&	front()	const	noexcept;

			/**
			*	@brief	Get a reference to the last element of the vector.
			*			The behaviour is undefined if the vector is empty.
			* 
			*	@return A reference to the last element of the vector.
			*/
			T&			back()			noexcept;
			T const&	back()	const	noexcept;

			/**
			*	@brief Get a pointer to the underlying allocated memory.
			* 
			*	@return A pointer to the underlying allocated memory.
			*/
			T*			data()			noexcept;
			T const*	data()	const	noexcept;

			/**
			*	@brief	Reallocate the underlying memory to have enough space to fit capacity elements.
			*			No reallocation happens if the provided capacity is equal or smaller than the current capacity.
			* 
			*	@param capacity New capacity.
			*/
			void		reserve(std::size_t capacity);

			/**
			*	@brief	Resize the vector so that it has exactly the specified size.
			*			Reallocation occurs if the size is greater than the current capacity.
			*			Objects are default constructed if the specified size is greater than the current size.
			* 
			*	@param size The new size.
			*/
			void		resize(std::size_t size);

			/**
			*	@brief Get the number of elements stored in the vector.
			* 
			*	@return The number of elements stored in the vector.
			*/
			std::size_t	size()			const	noexcept;

			/**
			*	@brief Get the maximum number of elements storable in the vector without reallocation.
			* 
			*	@return The maximum number of elements storable in the vector without reallocation.
			*/
			std::size_t capacity()		const	noexcept;

			/**
			*	@brief Check if the container contains no elements.
			* 
			*	@return true if there are no elements in the vector, else false.
			*/
			bool		empty()			const	noexcept;

			/**
			*	@brief Remove all elements from the vector.
			*/
			void		clear();

			/**
			*	@brief Add an element to the vector.
			* 
			*	@param value The object to copy.
			*/
			void		push_back(T const& value);

			/**
			*	@brief Add an element to the vector.
			* 
			*	@param value The object to forward.
			*/
			void		push_back(T&& value);

			/**
			*	@brief Add all elements from a vector at the end of this vector.
			* 
			*	@param other The vector which elements must be copied.
			*/
			void		push_back(Vector const& other);
			void		push_back(Vector&& other);

			/**
			*	@brief Insert an element at a specified index.
			* 
			*	@param index	Index of the element in the vector.
			*	@param element	Element to insert.
			*/
			void		insert(std::size_t	index,
							   T const&		element);

			/**
			*	@brief Insert an element at a specified index.
			* 
			*	@param index	Index of the element in the vector.
			*	@param element	Element to insert.
			*/
			void		insert(std::size_t	index,
							   T&&			element);

			/**
			*	@brief Construct in place an element at the end of the vector with the provided arguments.
			* 
			*	@param... args Args forwarded to the object constructor.
			* 
			*	@return A reference to the constructed element.
			*/
			template <typename... Args>
			T&			emplace_back(Args&&... args);

			/**
			*	@brief	Get a pointer to the first element.
			*			If the vector is empty, the pointed memory is undefined.
			* 
			*	@return A pointer to the first element.
			*/
			T*			begin()				noexcept;
			T const*	begin()		const	noexcept;
			T const*	cbegin()	const	noexcept;

			/**
			*	@brief Get a pointer past the last element.
			* 
			*	@return A pointer past the last element.
			*/
			T*			end()				noexcept;
			T const*	end()		const	noexcept;
			T const*	cend()		const	noexcept;

			/**
			*	@brief Access the index(th) element in the vector.
			* 
			*	@param index Index of the element to access.
			* 
			*	@return A reference to the index(th) element in the vector.
			*/
			T&				operator[](std::size_t index)		noexcept;
			T const&		operator[](std::size_t index) const	noexcept;

			Vector&			operator=(Vector const&);
			Vector&			operator=(Vector&&)					noexcept;
	};

	#include "Refureku/Containers/Vector.inl"
}