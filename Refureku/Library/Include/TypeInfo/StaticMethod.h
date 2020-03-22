#pragma once

#include "TypeInfo/MethodBase.h"

namespace refureku
{
	class StaticMethod : public MethodBase
	{
		public:
			StaticMethod()						= default;
			StaticMethod(StaticMethod const&)	= default;
			StaticMethod(StaticMethod&&)		= default;
			~StaticMethod()						= default;

			/**
			*
			*	Invoke the method on the caller with the provided arguments if argument types match this method prototype
			*/
			template <typename... Args>
			void		invoke(Args&&... arguments)		const noexcept;

			/**
			*	Invoke the method with the provided arguments if the return type and argument types match this method prototype
			*/
			template <typename ReturnType, typename... Args>
			ReturnType	invoke(Args&&... arguments)		const noexcept;

			/**
			*	TODO
			*/
			template <typename... Args>
			void		safeInvoke(Args&&... arguments)	const noexcept;

			/**
			*	TODO
			*/
			template <typename ReturnType, typename... Args>
			ReturnType	safeInvoke(Args&&... arguments)	const noexcept;

			StaticMethod& operator=(StaticMethod const&)	= default;
			StaticMethod& operator=(StaticMethod&&)			= default;
	};

	#include "TypeInfo/StaticMethod.inl"
}