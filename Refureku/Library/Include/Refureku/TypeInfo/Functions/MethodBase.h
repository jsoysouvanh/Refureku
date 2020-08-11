/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Functions/FunctionBase.h"
#include "Refureku/TypeInfo/EAccessSpecifier.h"
#include "Refureku/TypeInfo/Functions/EMethodFlags.h"

namespace rfk
{
	class MethodBase : public FunctionBase
	{
		protected:
			MethodBase()											= delete;
			MethodBase(std::string&&				name, 
					   uint64						id,
					   Type const&					returnType,
					   std::unique_ptr<ICallable>&&	internalMethod,
					   EMethodFlags					flags)			noexcept;
			MethodBase(MethodBase const&)							= default;
			MethodBase(MethodBase&&)								= default;
			~MethodBase()											= default;

		public:
			/** Flags describing this method. */
			EMethodFlags	flags = EMethodFlags::Default;

			/**
			*	@return Access specifier of this method in its owner struct/class.
			*/
			EAccessSpecifier	getAccess()			const	noexcept;

			/**
			*	@return true if this method is static, else false.
			*/
			inline bool			isStatic()			const	noexcept;

			/**
			*	@return true if this method is declared as inline, else false.
			*/
			inline bool			isInline()			const	noexcept;

			/**
			*	@return true if this method is virtual, else false.
			*/
			inline bool			isVirtual()			const	noexcept;

			/**
			*	@return true if this method is virtual pure, else false.
			*/
			inline bool			isPureVirtual()		const	noexcept;

			/**
			*	@return true if this method overrides a previous definition, else false.
			*/
			inline bool			isOverride()		const	noexcept;

			/**
			*	@return true if this method is marked as final, else false.
			*/
			inline bool			isFinal()			const	noexcept;

			/**
			*	@return true if this method is marked as const, else false.
			*/
			inline bool			isConst()			const	noexcept;
	};

	#include "Refureku/TypeInfo/Functions/MethodBase.inl"
}