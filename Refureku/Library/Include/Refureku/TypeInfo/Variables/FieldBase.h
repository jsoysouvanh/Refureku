/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Variables/VariableBase.h"
#include "Refureku/TypeInfo/EAccessSpecifier.h"
#include "Refureku/TypeInfo/Variables/EFieldFlags.h"

namespace rfk
{
	class Struct;	//Forward declaration

	class FieldBase : public VariableBase
	{
		protected:
			FieldBase()									= delete;
			FieldBase(std::string&&		name,
					  uint64			id,
					  Type const&		type,
					  EFieldFlags		flags,
					  Struct const*		ownerStruct)	noexcept;
			FieldBase(FieldBase const&)					= delete;
			FieldBase(FieldBase&&)						= delete;
			~FieldBase()								= default;

		public:
			/** Flags describing this field. */
			EFieldFlags			flags	= EFieldFlags::Default;

			/** Struct this field belongs to. */
			Struct const*		ownerStruct;

			/**
			*	@return The access specifier of this field in its owner struct/class.
			*/
			EAccessSpecifier	getAccess()		const	noexcept;

			/**
			*	@return true if this field is static, else false.
			*/
			inline bool			isStatic()		const	noexcept;

			/**
			*	@return true if this field is mutable, else false
			*/
			inline bool			isMutable()		const	noexcept;
	};

	#include "Refureku/TypeInfo/Variables/FieldBase.inl"
}