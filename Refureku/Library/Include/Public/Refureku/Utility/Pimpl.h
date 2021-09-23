/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <utility>	//std::move, std::forward

namespace rfk
{
	/**
	*	Utility class used for the pimpl (pointer to implementation) idiom.
	*	It propagates constness.
	*/
	template <typename T>
	class Pimpl
	{
		private:
			/** Underlying class instance. */
			T _implReference;

		public:
			template <typename... Args>
			explicit Pimpl(Args&&... arguments);

			Pimpl(Pimpl const&)	= default;
			Pimpl(Pimpl&&)		= default;

			/**
			*	@brief Retrieve the underlying object.
			* 
			*	@return The underlying object.
			*/
			T& get()				noexcept;

			/**
			*	@brief Retrieve the const underlying object.
			* 
			*	@return The const underlying object.
			*/
			T const& get()	const	noexcept;

			Pimpl&		operator=(Pimpl const&)	= default;
			Pimpl&		operator=(Pimpl&&)		= default;

			/**
			*	@brief Retrieve the underlying object.
			* 
			*	@return The underlying object.
			*/
			T&			operator->()			noexcept;

			/**
			*	@brief Retrieve the const underlying object.
			* 
			*	@return The const underlying object.
			*/
			T const&	operator->()	const	noexcept;
	};

	#include "Refureku/Utility/Pimpl.inl"
}