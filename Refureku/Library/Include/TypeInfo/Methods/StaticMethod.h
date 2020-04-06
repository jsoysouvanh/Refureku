#pragma once

#include "TypeInfo/Methods/MethodBase.h"
#include "Utility/NonMemberFunction.h"

namespace rfk
{
	class StaticMethod : public MethodBase
	{
		public:
			StaticMethod()																			= delete;
			StaticMethod(std::string&&					name,
						 uint64							id				= 0u,
						 EMethodFlags					flags			= EMethodFlags::Static,
						 std::shared_ptr<ICallable>&&	internalMethod	= nullptr)					noexcept;
			StaticMethod(StaticMethod const&)														= default;
			StaticMethod(StaticMethod&&)															= default;
			~StaticMethod()																			= default;

			/**
			*
			*	Invoke the method on the caller with the provided arguments if argument types match this method prototype.
			*	If the passed arguments are incorrect, the method throws an exception in DEBUG mode, but crashes in RELEASE mode.
			*	Consider using the StaticMethod::safeInvoke(...) method if you want to call a method safely even in RELEASE mode.
			*
			*	Be careful: you MUST be explicit about the types you use because there is no type deduction here.
			*	Example: 
			*		Method prototype: static void staticMethod3(std::string param);
			*			StaticMethod::invoke("example");				will not work because "example" is a char const*
			*			StaticMethod::invoke(std::string("example"));	will work
			*/
			template <typename... ArgTypes>
			void		invoke(ArgTypes&&... arguments)		const	noexcept(REFUREKU_RELEASE);

			/**
			*	TODO
			*/
			template <typename ReturnType, typename... ArgTypes>
			ReturnType	invoke(ArgTypes&&... arguments)		const	noexcept(REFUREKU_RELEASE);

			/**
			*	TODO
			*/
			template <typename... ArgTypes>
			void		safeInvoke(ArgTypes&&... arguments)	const;

			/**
			*	TODO
			*/
			template <typename ReturnType, typename... ArgTypes>
			ReturnType	safeInvoke(ArgTypes&&... arguments)	const;

			StaticMethod& operator=(StaticMethod const&)	= default;
			StaticMethod& operator=(StaticMethod&&)			= default;
	};

	#include "TypeInfo/Methods/StaticMethod.inl"
}