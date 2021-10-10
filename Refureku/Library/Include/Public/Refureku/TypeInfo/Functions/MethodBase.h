/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Functions/FunctionBase.h"
#include "Refureku/TypeInfo/Functions/EMethodFlags.h"

namespace rfk
{
	class MethodBase : public FunctionBase
	{
		public:
			/**
			*	@brief Check if this method is static.
			* 
			*	@return true if this method is static, else false.
			*/
			RFK_NODISCARD REFUREKU_API bool				isStatic()		const	noexcept;

			/**
			*	@brief Check if this method is inline.
			* 
			*	@return true if this method is declared as inline, else false.
			*/
			RFK_NODISCARD REFUREKU_API bool				isInline()		const	noexcept;

			/**
			*	@brief Check if this method is virtual.
			* 
			*	@return true if this method is virtual, else false.
			*/
			RFK_NODISCARD REFUREKU_API bool				isVirtual()		const	noexcept;

			/**
			*	@brief Check if this method is pure virtual.
			* 
			*	@return true if this method is pure virtual, else false.
			*/
			RFK_NODISCARD REFUREKU_API bool				isPureVirtual()	const	noexcept;

			/**
			*	@brief Check if this method is override-qualified.
			* 
			*	@return true if this method is override-qualified, else false.
			*/
			RFK_NODISCARD REFUREKU_API bool				isOverride()	const	noexcept;

			/**
			*	@brief Check if this method is final-qualified.
			* 
			*	@return true if this method is final-qualified, else false.
			*/
			RFK_NODISCARD REFUREKU_API bool				isFinal()		const	noexcept;
			
			/**
			*	@brief Check if this method is const-qualified.
			* 
			*	@return true if this method is const-qualified, else false.
			*/
			RFK_NODISCARD REFUREKU_API bool				isConst()		const	noexcept;

			/**
			*	@brief Get the flags qualifying this method.
			* 
			*	@return The flags qualifying this method.
			*/
			RFK_NODISCARD REFUREKU_API EMethodFlags		getFlags()		const	noexcept;

			/**
			*	@brief Get the access specifier of this method in its owner struct/class.
			* 
			*	@return The access specifier of this method in its owner struct/class.
			*/
			RFK_NODISCARD REFUREKU_API EAccessSpecifier	getAccess()		const	noexcept;

		protected:
			//Forward declaration
			class MethodBaseImpl;

			REFUREKU_INTERNAL MethodBase(MethodBaseImpl* implementation)	noexcept;
			REFUREKU_INTERNAL MethodBase(MethodBase&&)						noexcept;
			REFUREKU_INTERNAL ~MethodBase()									noexcept;
	};
}