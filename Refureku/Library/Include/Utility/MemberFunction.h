#pragma once

#include <utility>	//std::forward

#include "Utility/ICallable.h"

namespace refureku
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

			union
			{
				CallerType*				_caller			= nullptr;
				CallerType const*		_constCaller;
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

			void setCaller(void* caller) noexcept
			{
				_caller = static_cast<CallerType*>(caller);
			}

			void setCaller(void const* caller) noexcept
			{
				_constCaller = static_cast<CallerType const*>(caller);
			}

			ReturnType operator()(ArgTypes&&... args) const noexcept
			{
				return (_caller->*_function)(std::forward<ArgTypes>(args)...);
			}

			//ReturnType operator()(ArgTypes&&... args) const noexcept
			//{
			//	return (_constCaller->*_constFunction)(std::forward<ArgTypes>(args)...);
			//	//return (callerInstance.*_constFunction)(std::forward<ArgTypes>(args)...);
			//}
	};
}