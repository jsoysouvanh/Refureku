/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Variables/VariableBase.h"
#include "Refureku/TypeInfo/Variables/EFieldFlags.h"
#include "Refureku/TypeInfo/EAccessSpecifier.h"

namespace rfk
{
	//Forward declaration
	class Struct;

	class FieldBase : public VariableBase
	{
		public:
			/**
			*	@brief Get the access specifier of this field in its owner struct/class.
			* 
			*	@return The access specifier of this field in its owner struct/class.
			*/
			RFK_NODISCARD REFUREKU_API EAccessSpecifier	getAccess()	const	noexcept;

			/**
			*	@brief	Check whether this field is static or not.
			*			If the field is static, it can safely be cast to StaticField.
			* 
			*	@return true if this field is static, else false.
			*/
			RFK_NODISCARD REFUREKU_API bool				isStatic()	const	noexcept;

			/**
			*	@brief Check whether this field is mutable or not.
			* 
			*	@return true if this field is mutable, else false.
			*/
			RFK_NODISCARD REFUREKU_API bool				isMutable()	const	noexcept;

			/**
			*	@brief Get the flags qualifying this field.
			* 
			*	@return The flags qualifying this field.
			*/
			RFK_NODISCARD REFUREKU_API EFieldFlags		getFlags()	const	noexcept;

			/**
			*	@brief Get the struct owning this field.
			* 
			*	@return The struct owning this field.
			*/
			RFK_NODISCARD REFUREKU_API Struct const*	getOwner()	const	noexcept;

		protected:
			//Forward declaration
			class FieldBaseImpl;

			REFUREKU_INTERNAL FieldBase(FieldBaseImpl* implementation)	noexcept;
			REFUREKU_INTERNAL FieldBase(FieldBase&&)					noexcept;
			REFUREKU_INTERNAL ~FieldBase()								noexcept;

			RFK_GEN_GET_PIMPL(FieldBaseImpl, Entity::getPimpl())
	};
}