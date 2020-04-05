#pragma once

#include <utility>	//std::forward

#include "Utility/ICallable.h"

namespace rfk
{
	template <typename CallerType, typename FunctionPrototype>
	class MemberFunction
	{};

	template <typename CallerType, typename ReturnType, typename... ArgTypes>
	class MemberFunction<CallerType, ReturnType(ArgTypes...)> : public ICallable
	{
		private:
			using FunctionPrototype			= ReturnType (CallerType::*)(ArgTypes...);
			using ConstFunctionPrototype	= ReturnType (CallerType::*)(ArgTypes...) const;

			union
			{
				FunctionPrototype		_function		= nullptr;
				ConstFunctionPrototype	_constFunction;
			};

		public:
			MemberFunction() = delete;

			MemberFunction(FunctionPrototype function) noexcept:
				_function{function}
			{}

			MemberFunction(ConstFunctionPrototype function) noexcept:
				_constFunction{function}
			{}

			~MemberFunction() = default;

			inline ReturnType operator()(void const* caller, ArgTypes&&... args) const noexcept
			{
				return (static_cast<CallerType const*>(caller)->*_constFunction)(std::forward<ArgTypes>(args)...);
			}
	};
}