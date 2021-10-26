/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <utility>	//std::move, std::forward

namespace rfk
{
	/**
	*	Utility class used for the pimpl (pointer to implementation) idiom.
	*	It holds a pointer to the underlying class and propagates constness.
	*/
	template <typename T>
	class Pimpl
	{
		private:
			/** Underlying class instance. */
			T*		_implementation;

			/**
			*	@brief Destroy the underlying object if it is valid.
			*/
			void	checkedDelete();

		public:
			Pimpl(T* implementation)	noexcept;
			Pimpl(Pimpl const& other);
			Pimpl(Pimpl&& other)		noexcept;
			~Pimpl();

			/**
			*	@brief Retrieve a pointer to the underlying object.
			* 
			*	@return The underlying object.
			*/
			T*			get()							noexcept;

			/**
			*	@brief Retrieve a const pointer to the underlying object.
			* 
			*	@return The const underlying object.
			*/
			T const*	get()					const	noexcept;

			/**
			*	@brief	Set a new implementation without checking the state of the previous one.
			*			**WARNING**: If a valid implementation was set before, it is not deleted!!
			*/
			void		uncheckedSet(T* impl)			noexcept;

			Pimpl&		operator=(Pimpl const& other);
			Pimpl&		operator=(Pimpl&& other)		noexcept;

			/**
			*	@brief Retrieve a pointer to the underlying object.
			* 
			*	@return The underlying object.
			*/
			T*			operator->()					noexcept;

			/**
			*	@brief Retrieve a const pointer to the underlying object.
			* 
			*	@return The const underlying object.
			*/
			T const*	operator->()			const	noexcept;

			/**
			*	@brief Retrieve a reference to the underlying object.
			* 
			*	@return The underlying object.
			*/
			T&			operator*()						noexcept;

			/**
			*	@brief Retrieve a const reference to the underlying object.
			* 
			*	@return The const underlying object.
			*/
			T const&	operator*()				const	noexcept;
	};

	#include "Refureku/Misc/Pimpl.inl"
}