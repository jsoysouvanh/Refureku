#pragma once

#include <string>

#include "Config.h"

#include "Misc/FundamentalTypes.h"
#include "TypeInfo/Methods/MethodBase.h"
#include "Utility/MemberFunction.h"

namespace rfk
{
	class Struct;	//Forward declaration

	class Method : public MethodBase
	{
		private:
			class DummyClass {};

			template <typename ReturnType, typename... ArgTypes>
			ReturnType	internalInvoke(void* caller, ArgTypes&&... arguments)		const	noexcept;

			template <typename ReturnType, typename... ArgTypes>
			ReturnType	internalInvoke(void const* caller, ArgTypes&&... arguments)	const	noexcept;

		public:
			/** Class declaring this method */
			Struct const*	ownerType		= nullptr;

			/** Is this method virtual */
			bool			isVirtual		= false;
			
			/** Is this method virtual pure */
			bool			isPureVirtual	= false;
			
			/** Is this an overriden version of a parent method */
			bool			isOverride		= false;
			
			/** Is this method final */
			bool			isFinal			= false;
			
			/** Is this method const */
			bool			isConst			= false;

			Method()																		= delete;
			Method(std::string&&				methodName,
				   uint64						methodId		= 0u,
				   EMethodFlags					flags			= EMethodFlags::Default,
				   std::shared_ptr<ICallable>&&	internalMethod	= nullptr,
				   Struct const*				methodOwnerType	= nullptr)					noexcept;
			Method(Method const&)															= default;
			Method(Method&&)																= default;
			~Method()																		= default;

			/**
			*	Overload with const caller for
			*		void invoke(void* caller, ArgTypes&&... arguments) method
			*/
			template <typename... ArgTypes>
			void		invoke(void const* caller, ArgTypes&&... arguments)		const noexcept;

			/**
			*	Overload with const caller for
			*		ReturnType invoke(void* caller, ArgTypes&&... arguments) method
			*/
			template <typename ReturnType, typename... ArgTypes>
			ReturnType	invoke(void const* caller, ArgTypes&&... arguments)		const noexcept;

			/**
			*	Overload with const caller for
			*		void safeInvoke(void* caller, ArgTypes&&... arguments) method
			*/
			template <typename... ArgTypes>
			void		safeInvoke(void const* caller, ArgTypes&&... arguments)	const;

			/**
			*	Overload with const caller for
			*		ReturnType safeInvoke(void* caller, ArgTypes&&... arguments) method
			*/
			template <typename ReturnType, typename... ArgTypes>
			ReturnType	safeInvoke(void const* caller, ArgTypes&&... arguments)	const;

			Method& operator=(Method const&)	= default;
			Method& operator=(Method&&)			= default;
	};

	#include "TypeInfo/Methods/Method.inl"
}