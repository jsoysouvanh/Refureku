#pragma once

#include "Config.h"

#include "TypeInfo/MethodBase.h"

namespace refureku
{
	class Method : public MethodBase
	{
		public:
			Method()				= default;
			Method(Method const&)	= default;
			Method(Method&&)		= default;
			~Method()				= default;

			/**
			*
			*	Invoke the method on the caller with the provided arguments if argument types match this method prototype
			*/
			template <typename... Args>
			void		invoke(void* caller, Args&&... arguments)		const noexcept;

			/**
			*	Invoke the method with the provided arguments if the return type and argument types match this method prototype
			*/
			template <typename ReturnType, typename... Args>
			ReturnType	invoke(void* caller, Args&&... arguments)		const noexcept;

			/**
			*	TODO
			*/
			template <typename... Args>
			void		safeInvoke(void* caller, Args&&... arguments)	const noexcept;

			/**
			*	TODO
			*/
			template <typename ReturnType, typename... Args>
			ReturnType	safeInvoke(void* caller, Args&&... arguments)	const noexcept;

			Method& operator=(Method const&)	= default;
			Method& operator=(Method&&)			= default;
	};

	#include "TypeInfo/Method.inl"
}