/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Variables/VariableBaseAPI.h"
#include "Refureku/TypeInfo/Variables/EFieldFlags.h"
#include "Refureku/TypeInfo/EAccessSpecifier.h"

namespace rfk
{
	//Forward declaration
	class StructAPI;

	class FieldBaseAPI : public VariableBaseAPI
	{
		public:
			/**
			*	@brief Get the access specifier of this field in its owner struct/class.
			* 
			*	@return The access specifier of this field in its owner struct/class.
			*/
			REFUREKU_API EAccessSpecifier	getAccess()	const	noexcept;

			/**
			*	@brief	Check whether this field is static or not.
			*			If the field is static, it can safely be cast to StaticField.
			* 
			*	@return true if this field is static, else false.
			*/
			REFUREKU_API bool				isStatic()	const	noexcept;

			/**
			*	@brief Check whether this field is mutable or not.
			* 
			*	@return true if this field is mutable, else false.
			*/
			REFUREKU_API bool				isMutable()	const	noexcept;

			/**
			*	@brief Get the flags qualifying this field.
			* 
			*	@return The flags qualifying this field.
			*/
			REFUREKU_API EFieldFlags		getFlags()	const	noexcept;

			/**
			*	@brief Get the struct owning this field.
			* 
			*	@return The struct owning this field.
			*/
			REFUREKU_API StructAPI const*	getOwner()	const	noexcept;

		protected:
			//Forward declaration
			class FieldBaseImpl;

			REFUREKU_INTERNAL FieldBaseAPI(FieldBaseImpl* implementation)	noexcept;
			REFUREKU_INTERNAL ~FieldBaseAPI()								noexcept;
	};
}