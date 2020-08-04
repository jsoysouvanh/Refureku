/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <utility>	//std::forward

#include "Refureku/Utility/ICallable.h"

namespace rfk
{
	template <typename FunctionPrototype>
	class NonMemberFunction
	{};

	template <typename ReturnType, typename... ArgTypes>
	class NonMemberFunction<ReturnType(ArgTypes...)> : public ICallable
	{
		private:
			using FunctionPrototype = ReturnType (*)(ArgTypes...);

			FunctionPrototype	_function = nullptr;

		public:
			NonMemberFunction() = delete;

			NonMemberFunction(FunctionPrototype function) noexcept:
				_function{function}
			{}

			template <typename Functor>
			NonMemberFunction(Functor f) noexcept:
				_function{reinterpret_cast<FunctionPrototype>(f)}
			{}

			~NonMemberFunction() = default;

			inline ReturnType operator()(ArgTypes&&... args) const noexcept
			{
				return _function(std::forward<ArgTypes>(args)...);
			}
	};
}