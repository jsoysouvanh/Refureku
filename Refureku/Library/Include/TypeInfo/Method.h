#pragma once

#include "Config.h"

#include "TypeInfo/MethodBase.h"
#include "Utility/MemberFunction.h"

namespace refureku
{
	class Method : public MethodBase
	{
		private:
			class DummyClass {};

			template <typename ReturnType, typename... Args>
			ReturnType	internalInvoke(void* caller, Args&&... arguments)		const	noexcept;

			template <typename ReturnType, typename... Args>
			ReturnType	internalInvoke(void const* caller, Args&&... arguments)	const	noexcept;

		public:
			Method()							= delete;
			Method(ICallable* internalMethod)	noexcept;
			Method(Method const&)				= default;
			Method(Method&&)					noexcept;
			~Method()							= default;

			/**
			*	Invoke the method on the caller with the provided arguments if argument types match this method prototype
			*/
			template <typename... Args>
			void		invoke(void* caller, Args&&... arguments)			const noexcept(REFUREKU_RELEASE);

			/**
			*	Overload with const caller for
			*		void invoke(void* caller, Args&&... arguments) method
			*/
			template <typename... Args>
			void		invoke(void const* caller, Args&&... arguments)		const noexcept(REFUREKU_RELEASE);

			/**
			*	Invoke the method on the caller with the provided arguments if the return type and argument types match this method prototype
			*/
			template <typename ReturnType, typename... Args>
			ReturnType	invoke(void* caller, Args&&... arguments)			const noexcept(REFUREKU_RELEASE);

			/**
			*	Overload with const caller for
			*		ReturnType invoke(void* caller, Args&&... arguments) method
			*/
			template <typename ReturnType, typename... Args>
			ReturnType	invoke(void const* caller, Args&&... arguments)		const noexcept(REFUREKU_RELEASE);

			/**
			*	TODO
			*/
			template <typename... Args>
			void		safeInvoke(void* caller, Args&&... arguments)		const;

			/**
			*	Overload with const caller for
			*		void safeInvoke(void* caller, Args&&... arguments) method
			*/
			template <typename... Args>
			void		safeInvoke(void const* caller, Args&&... arguments)	const;

			/**
			*	TODO
			*/
			template <typename ReturnType, typename... Args>
			ReturnType	safeInvoke(void* caller, Args&&... arguments)		const;

			/**
			*	Overload with const caller for
			*		ReturnType safeInvoke(void* caller, Args&&... arguments) method
			*/
			template <typename ReturnType, typename... Args>
			ReturnType	safeInvoke(void const* caller, Args&&... arguments)	const;

			Method& operator=(Method const&)	= default;
			Method& operator=(Method&&)			= default;
	};

	#include "TypeInfo/Method.inl"
}