#pragma once

#include <utility>	//std::forward

#include "Utility/ICallable.h"

namespace refureku
{
	template <typename FunctionPrototype>
	class NonMemberFunction
	{};

	template <typename ReturnType, typename... ArgTypes>
	class NonMemberFunction<ReturnType(ArgTypes...)> : public ICallable
	{
		private:
			using FunctionPrototype = ReturnType (*)(ArgTypes...);

			FunctionPrototype	_function;

		public:
			NonMemberFunction() = delete;

			NonMemberFunction(FunctionPrototype function) noexcept:
				_function{function}
			{}

			virtual ~NonMemberFunction() = default;

			ReturnType operator()(ArgTypes&&... args) const noexcept
			{
				return _function(std::forward<ArgTypes>(args)...);
			}
	};
}