#pragma once

#include <string>

#include "Config.h"

#include "Misc/FundamentalTypes.h"
#include "TypeInfo/Methods/MethodBase.h"
#include "Utility/MemberFunction.h"

namespace refureku
{
	class Struct;	//Forward declaration

	class Method : public MethodBase
	{
		private:
			class DummyClass {};

			template <typename ReturnType, typename... Args>
			ReturnType	internalInvoke(void* caller, Args&&... arguments)		const	noexcept;

			template <typename ReturnType, typename... Args>
			ReturnType	internalInvoke(void const* caller, Args&&... arguments)	const	noexcept;

		public:
			/** Class declaring this method */
			Struct const* ownerType;

			Method()																= default;
			Method(std::string&&				methodName,
				   uint64						methodId		= 0u,
				   EAccessSpecifier				accessSpecifier	= EAccessSpecifier::Undefined,
				   Struct const*				methodOwnerType	= nullptr,
				   std::shared_ptr<ICallable>&&	internalMethod	= nullptr)			noexcept;
			Method(Method const&)													= default;
			Method(Method&&)														= default;
			~Method()																= default;

			/**
			*	Overload with const caller for
			*		void invoke(void* caller, Args&&... arguments) method
			*/
			template <typename... Args>
			void		invoke(void const* caller, Args&&... arguments)		const noexcept(REFUREKU_RELEASE);

			/**
			*	Overload with const caller for
			*		ReturnType invoke(void* caller, Args&&... arguments) method
			*/
			template <typename ReturnType, typename... Args>
			ReturnType	invoke(void const* caller, Args&&... arguments)		const noexcept(REFUREKU_RELEASE);

			/**
			*	Overload with const caller for
			*		void safeInvoke(void* caller, Args&&... arguments) method
			*/
			template <typename... Args>
			void		safeInvoke(void const* caller, Args&&... arguments)	const;

			/**
			*	Overload with const caller for
			*		ReturnType safeInvoke(void* caller, Args&&... arguments) method
			*/
			template <typename ReturnType, typename... Args>
			ReturnType	safeInvoke(void const* caller, Args&&... arguments)	const;

			Method& operator=(Method const&)	= default;
			Method& operator=(Method&&)			= default;
	};

	#include "TypeInfo/Methods/Method.inl"
}