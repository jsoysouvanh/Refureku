/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <utility>	//std::forward

#include "Refureku/TypeInfo/Functions/ICallable.h"

namespace rfk
{
	template <typename FunctionPrototype>
	class NonMemberFunction;

	template <typename ReturnType, typename... ArgTypes>
	class NonMemberFunction<ReturnType(ArgTypes...)> : public ICallable
	{
		private:
			using FunctionPrototype = ReturnType (*)(ArgTypes...);

			/** Pointer to the underlying function. */
			FunctionPrototype _function = nullptr;

		public:
			template <typename Functor>
			NonMemberFunction(Functor f)					noexcept;

			NonMemberFunction(FunctionPrototype function)	noexcept;

			/**
			*	@brief Get a pointer to the underlying function.
			* 
			*	@return The pointer to the underlying function.
			*/
			FunctionPrototype getFunctionHandle()		const	noexcept;

			/**
			*	@brief Call the underlying function.
			* 
			*	@param args... Arguments to forward to the function call.
			* 
			*	@return The result of the underlying call.
			*/
			ReturnType operator()(ArgTypes&&... args)	const;
	};

	#include "Refureku/TypeInfo/Functions/NonMemberFunction.inl"
}