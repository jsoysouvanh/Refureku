/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/TypeInfo/Functions/FunctionBase.h"
#include "Refureku/TypeInfo/EAccessSpecifier.h"
#include "Refureku/TypeInfo/Functions/EMethodFlags.h"

namespace rfk
{
	class MethodBase : public FunctionBase
	{
		private:
			/** Flags describing this method. */
			EMethodFlags	_flags	= EMethodFlags::Default;

		protected:
			MethodBase(std::string&&				name, 
					   std::size_t					id,
					   Type const&					returnType,
					   std::unique_ptr<ICallable>&&	internalMethod,
					   EMethodFlags					flags,
					   Entity const*				outerEntity	= nullptr)	noexcept;
			MethodBase(MethodBase const&)									= delete;
			MethodBase(MethodBase&&)										= delete;

		public:
			/**
			*	@return Access specifier of this method in its owner struct/class.
			*/
			REFUREKU_API EAccessSpecifier	getAccess()			const	noexcept;

			/**
			*	@return true if this method is static, else false.
			*/
			inline bool						isStatic()			const	noexcept;

			/**
			*	@return true if this method is declared as inline, else false.
			*/
			inline bool						isInline()			const	noexcept;

			/**
			*	@return true if this method is virtual, else false.
			*/
			inline bool						isVirtual()			const	noexcept;

			/**
			*	@return true if this method is virtual pure, else false.
			*/
			inline bool						isPureVirtual()		const	noexcept;

			/**
			*	@return true if this method overrides a previous definition, else false.
			*/
			inline bool						isOverride()		const	noexcept;

			/**
			*	@return true if this method is marked as final, else false.
			*/
			inline bool						isFinal()			const	noexcept;

			/**
			*	@return true if this method is marked as const, else false.
			*/
			inline bool						isConst()			const	noexcept;

			/**
			*	@brief Getter for the field _flags.
			* 
			*	@return _flags.
			*/
			inline EMethodFlags				getFlags()			const	noexcept;


			MethodBase& operator=(MethodBase const&)	= delete;
			MethodBase& operator=(MethodBase&&)			= delete;
	};

	#include "Refureku/TypeInfo/Functions/MethodBase.inl"
}